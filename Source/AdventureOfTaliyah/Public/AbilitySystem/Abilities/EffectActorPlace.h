// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/MyGameplayDamageAbility.h"
#include "Actor/PlaceEffectActor.h"
#include "EffectActorPlace.generated.h"

/**
 * 
 */
UCLASS()
class ADVENTUREOFTALIYAH_API UEffectActorPlace : public UMyGameplayDamageAbility
{
	GENERATED_BODY()
protected:
		virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

		UFUNCTION(BlueprintCallable, Category = "Projectile")
			void SpawnEffectActor(bool bOverridetLocation, FVector LocationOverride, bool bOverrideRotation, FRotator RotationOverride);

		UPROPERTY(EditAnywhere, BlueprintReadOnly)
			TSubclassOf<APlaceEffectActor> EffectActorClass;

};
