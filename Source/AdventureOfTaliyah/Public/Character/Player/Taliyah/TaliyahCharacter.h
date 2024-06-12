// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
//#include "Character/Bullet.h"
//#include "Actor/RangedAttackProjectile.h"
#include "CoreMinimal.h"
#include "Character/Player/PlayerCharacter.h"
#include "Interaction/PlayerInterface.h"
#include "TaliyahCharacter.generated.h"


/**
 * 
 */
 class UNiagaraComponent;

UCLASS()
class ADVENTUREOFTALIYAH_API ATaliyahCharacter : public APlayerCharacter/*,public IPlayerInterface*/
{
	GENERATED_BODY()
		

public:
	ATaliyahCharacter();
	virtual void PossessedBy(AController* NewController)override;
	virtual void OnRep_PlayerState() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	/** Combat Interface */
	virtual int32 GetPlayerLevel_Implementation() const override;
	
	/** Combat Interface */

	/** player Interface */
	virtual int32 GetPlayerLevelFromPlayerInterface_Implementation() const override;
	virtual void AddToXP_Implementation(int32 InXP) override;
	virtual void LevelUp_Implementation() override;
	virtual int32 GetXP_Implementation() const override;
	virtual int32 FindLevelForXP_Implementation(int32 InXP) const override;
	virtual void AddToPlayerLevel_Implementation(int32 InPlayerLevel) override;
	virtual void AddToLevelUpAttributesReward_Implementation(int32 NewLevel) override;
	/** player Interface */

	virtual void OnRep_Stunned() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TObjectPtr<UNiagaraComponent> LevelUpNiagaraComponent;

private:
	virtual void InitAbilityActorInfo() ;

	UFUNCTION(NetMulticast, Reliable)
		void MulticastLevelUpParticles();

protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float deltaTime) override;
	//原本的增强输入
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
protected:
	//virtual 应该是隐式继承的
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Passive(const FInputActionValue& Value) override;

public:

	UPROPERTY(Replicated, BlueprintReadOnly)
	bool bIsPassiveActivited = false;


	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	//bool bAttackHand = false; //0 左手攻击，1右手

	
};
