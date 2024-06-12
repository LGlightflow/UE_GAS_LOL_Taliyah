// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/MyGameplayDamageAbility.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

void UMyGameplayDamageAbility::CauseDamage(AActor* TargetActor)
{
	FGameplayEffectSpecHandle DamageSpecHandle = MakeOutgoingGameplayEffectSpec(DamageEffectClass, 1.f);
	const float ScaledDamage = Damage.GetValueAtLevel(GetAbilityLevel());
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(DamageSpecHandle, DamageType, ScaledDamage);
	GetAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(*DamageSpecHandle.Data.Get(), UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor));
}

//初始GE（包括debuff之类的）参数
FDamageEffectParams UMyGameplayDamageAbility::MakeDamageEffectParamsFromClassDefaults(AActor* TargetActor, FVector InRadialDamageOrigin, bool bOverrideKnockbackDirection, FVector KnockbackDirectionOverride, bool bOverrideDeathImpulse, FVector DeathImpulseDirectionOverride, bool bOverrideRotation, FRotator RotationOverride) const
{
	FDamageEffectParams Params;
	Params.WorldContextObject = GetAvatarActorFromActorInfo();
	Params.DamageGameplayEffectClass = DamageEffectClass;
	Params.SourceAbilitySystemComponent = GetAbilitySystemComponentFromActorInfo();
	Params.TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	Params.BaseDamage = Damage.GetValueAtLevel(GetAbilityLevel());
	Params.AbilityLevel = GetAbilityLevel();
	Params.DamageType = DamageType;
	Params.AttackDamageCoefficient = AttackDamageCoefficient;
	Params.AbilityPowerCoefficient = AbilityPowerCoefficient;
	Params.DebuffType = DebuffType;
	Params.DebuffChance = DebuffChance;
	Params.DebuffDamage = DebuffDamage;
	Params.DebuffDuration = DebuffDuration;
	Params.DebuffFrequency = DebuffFrequency;
	Params.DeathImpulseMagnitude = DeathImpulseMagnitude;
	Params.KnockbackForceMagnitude = KnockbackForceMagnitude;
	Params.KnockbackChance = KnockbackChance;

	if (IsValid(TargetActor))
	{
		FRotator Rotation = GetAvatarActorFromActorInfo()->GetInstigatorController()->GetControlRotation(); 
		if (bOverrideRotation)
		{
			Rotation = RotationOverride;
		}
		const FVector ToTarget = Rotation.Vector();
		if (!bOverrideKnockbackDirection)
		{
			Params.KnockbackForce = ToTarget * KnockbackForceMagnitude;
		}
		if (!bOverrideDeathImpulse)
		{
			Params.DeathImpulse = ToTarget * DeathImpulseMagnitude;
		}
	}


	if (bOverrideKnockbackDirection)
	{
		KnockbackDirectionOverride.Normalize();
		Params.KnockbackForce = KnockbackDirectionOverride * KnockbackForceMagnitude;
		if (bOverrideRotation)
		{
			FRotator KnockbackRotation = KnockbackDirectionOverride.Rotation();
			KnockbackRotation.Pitch = RotationOverride.Pitch;
			Params.KnockbackForce = KnockbackRotation.Vector() * KnockbackForceMagnitude;
		}
	}

	if (bOverrideDeathImpulse)
	{
		DeathImpulseDirectionOverride.Normalize();
		Params.DeathImpulse = DeathImpulseDirectionOverride * DeathImpulseMagnitude;
		if (bOverrideRotation)
		{
			FRotator DeathImpulseRotation = DeathImpulseDirectionOverride.Rotation();
			DeathImpulseRotation.Pitch = RotationOverride.Pitch;
			Params.DeathImpulse = DeathImpulseRotation.Vector() * DeathImpulseMagnitude;
		}
	}

	//if (bIsRadialDamage)
	//{
	//	Params.bIsRadialDamage = bIsRadialDamage;
	//	Params.RadialDamageOrigin = InRadialDamageOrigin;
	//	Params.RadialDamageInnerRadius = RadialDamageInnerRadius;
	//	Params.RadialDamageOuterRadius = RadialDamageOuterRadius;
	//}
	return Params;
}

float UMyGameplayDamageAbility::GetDamageAtLevel() const
{
	return Damage.GetValueAtLevel(GetAbilityLevel());
}

FTaggedMontage UMyGameplayDamageAbility::GetRandomTaggedMontageFromArray(const TArray<FTaggedMontage>& TaggedMontages) const
{
	if (TaggedMontages.Num() > 0)
	{
		const int32 Selection = FMath::RandRange(0, TaggedMontages.Num() - 1);
		return TaggedMontages[Selection];
	}

	return FTaggedMontage();
}
