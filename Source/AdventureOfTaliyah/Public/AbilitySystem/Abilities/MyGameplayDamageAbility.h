// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/MyGameplayAbility.h"
#include "Interaction/CombatInterface.h"
#include "MyAbilityTypes.h"
#include "MyGameplayDamageAbility.generated.h"

/**
 * 
 */
UCLASS()
class ADVENTUREOFTALIYAH_API UMyGameplayDamageAbility : public UMyGameplayAbility
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable)
		void CauseDamage(AActor* TargetActor);

	UFUNCTION(BlueprintPure)
		FDamageEffectParams MakeDamageEffectParamsFromClassDefaults(
			AActor* TargetActor = nullptr,
			FVector InRadialDamageOrigin = FVector::ZeroVector,
			bool bOverrideKnockbackDirection = false,
			FVector KnockbackDirectionOverride = FVector::ZeroVector,
			bool bOverrideDeathImpulse = false,
			FVector DeathImpulseDirectionOverride = FVector::ZeroVector,
			bool bOverrideRotaion = false,
			FRotator RotationOverride = FRotator(0,0,0)) const;

	UFUNCTION(BlueprintPure)
		float GetDamageAtLevel() const;
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TSubclassOf<UGameplayEffect> DamageEffectClass;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
		FGameplayTag DamageType;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
		FScalableFloat Damage;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
		float AttackDamageCoefficient = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
		float AbilityPowerCoefficient = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
		FGameplayTag DebuffType;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
		float DebuffChance = 20.f;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
		float DebuffDamage = 5.f;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
		float DebuffFrequency = 1.f;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
		float DebuffDuration = 5.f;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
		float DeathImpulseMagnitude = 1000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
		float KnockbackForceMagnitude = 1000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
		float KnockbackChance = 0.f;

	/*UPROPERTY(EditDefaultsOnly, Category = "Damage")
		bool bIsRadialDamage = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
		float RadialDamageInnerRadius = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
		float RadialDamageOuterRadius = 0.f;*/

	UFUNCTION(BlueprintPure)
		FTaggedMontage GetRandomTaggedMontageFromArray(const TArray<FTaggedMontage>& TaggedMontages) const;

};
