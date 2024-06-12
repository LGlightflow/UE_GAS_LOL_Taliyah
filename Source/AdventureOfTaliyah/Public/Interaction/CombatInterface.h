// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

class UAbilitySystemComponent;
class UNiagaraSystem;
class UAnimMontage;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnASCRegistered, UAbilitySystemComponent*);  //如果ASC有效则从ownerCharacter进行广播
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeathSignature, AActor*, DeadActor);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnDamageSignature, float /*DamageAmount*/);

USTRUCT(BlueprintType)
struct FTaggedMontage
{
	GENERATED_BODY()

		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		UAnimMontage* Montage = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FGameplayTag MontageTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FGameplayTag SocketTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		USoundBase* ImpactSound = nullptr;
};


// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()

};

/**
 * 
 */
class ADVENTUREOFTALIYAH_API ICombatInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	UFUNCTION(BlueprintNativeEvent)
		int32 GetPlayerLevel() const;
	


	// 在baseCharacter中实现
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		//FVector GetCombatSocketLocation(const FGameplayTag& MontageTag);
		FVector GetCombatSocketLocation(const FGameplayTag& MontageTag);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		//FVector GetCombatSocketLocation(const FGameplayTag& MontageTag);
		FRotator GetCombatSocketRotation();


	//virtual void Die(const FVector& DeathImpulse) = 0;
	virtual void Die() = 0;
	virtual FOnDeathSignature& GetOnDeathDelegate() = 0;
	virtual FOnDamageSignature& GetOnDamageSignature() = 0;


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		bool IsDead() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		AActor* GetAvatar();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		TArray<FTaggedMontage> GetAttackMontages();
		 
	// 因为每个character都有不同的受击动画，故在character的蓝图中配置对应的蒙太奇
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		UAnimMontage* GetHitReactMontage();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void UpdateFacingTarget(const FVector& Target);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		FTaggedMontage GetTaggedMontageByTag(const FGameplayTag& MontageTag);

	virtual FOnASCRegistered& GetOnASCRegisteredDelegate() = 0;



	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		bool IsBeingStunned() const;

	//UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	//	void SetInStunLoop(bool bInLoop);


	//UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	//	void SetIsBeingStunned(bool bInStun);
};
