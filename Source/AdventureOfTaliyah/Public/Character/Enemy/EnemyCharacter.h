// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "AI/MyAIController.h"
#include "Interaction/EnemyInterface.h"
#include "EnemyCharacter.generated.h"


class UWidgetComponent; 
/**
 * 
 */
UCLASS()
class ADVENTUREOFTALIYAH_API AEnemyCharacter : public ABaseCharacter,public IEnemyInterface
{
	GENERATED_BODY()
	
public:
	AEnemyCharacter();
	virtual void PossessedBy(AController* NewController) override;
	UPROPERTY(BlueprintAssignable)
		FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
		FOnAttributeChangedSignature OnMaxHealthChanged;



protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
	virtual void Die() override;
	virtual void SetCombatTarget_Implementation(AActor* InCombatTarget) override;
	virtual AActor* GetCombatTarget_Implementation() const override;

	void InitProgressBar();


	/** Combat Interface */
	virtual int32 GetPlayerLevel_Implementation() const override;


	void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);
	virtual void StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount) override;


	UPROPERTY(BlueprintReadOnly, Category = "Combat")
		bool bHitReacting = false;

	UPROPERTY(BlueprintReadWrite, Category = "Combat")
	TObjectPtr<AActor> CombatTarget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
		int32 Level = 1;



	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TObjectPtr<UWidgetComponent> HealthBar;


	UPROPERTY(EditAnywhere, Category = "AI")
		TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY()
		TObjectPtr<AMyAIController> MyAIController;
};
