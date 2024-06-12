// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "AbilitySystem/Abilities/MyGameplayAbility.h"
#include "AbilitySystem/Abilities/MyGameplayDamageAbility.h"
#include "Actor/RangedAttackProjectile.h"
#include "RangedAttack.generated.h"
/**
 * 
 */

UCLASS()
class ADVENTUREOFTALIYAH_API URangedAttack : public UMyGameplayDamageAbility//public UMyGameplayAbility
{
	GENERATED_BODY()
	
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION(BlueprintCallable, Category = "Projectile")
		void SpawnProjectile(const FGameplayTag& SocketTag, bool bOverrideRotation, FRotator RotationOverride);

	UFUNCTION(BlueprintCallable, Category = "Projectile")
	FRotator GetProjectileToTargetRotation(const FVector& ProjectileTargetLocation, const FGameplayTag& SocketTag);


	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TSubclassOf<ARangedAttackProjectile> ProjectileClass;


};
