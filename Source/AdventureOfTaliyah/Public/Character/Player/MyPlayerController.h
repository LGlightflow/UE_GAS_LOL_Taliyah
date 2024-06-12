// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "AbilitySystem/MyAbilitySystemComponent.h"
#include "UI/Widget/DamageTextComponent.h"
#include "MyPlayerController.generated.h"


class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UInputConfig;
/**
 * 
 */
UCLASS()
class ADVENTUREOFTALIYAH_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AMyPlayerController();

	UFUNCTION(Client, Reliable)
		void ShowDamageNumber(float DamageAmount, ACharacter* TargetCharacter, bool bCriticalHit);

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputMappingContext> Context;

	UMyAbilitySystemComponent* GetASC();

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* PassiveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* AttackAction;

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	UPROPERTY(EditDefaultsOnly, Category = "Input")
		TObjectPtr<UInputConfig> InputConfig;

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	void Jump();
	void StopJumping();

	TObjectPtr<AActor> LastActor;
	TObjectPtr<AActor> ThisActor;

private:
	
	void CursorTrace();

	UPROPERTY()
		TObjectPtr<UMyAbilitySystemComponent> MyAbilitySystemComponent;

	// …Ë÷√…À∫¶◊Èº˛
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<UDamageTextComponent> DamageTextComponentClass;
};
