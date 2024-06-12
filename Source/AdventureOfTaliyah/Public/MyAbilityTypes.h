// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "MyAbilityTypes.generated.h"

class UGameplayEffect;


/**
 * 本类的函数与AbilitySystemBPLibrary关联比较强
 * 本类的函数一般不直接调用，通过AbilitySystemBPLibrary传入FGameplayEffectContextHandle调用此类的函数
 */

USTRUCT(BlueprintType)
struct FDamageEffectParams
{
	GENERATED_BODY()

		FDamageEffectParams() {}

	UPROPERTY(BlueprintReadWrite)
		TObjectPtr<UObject> WorldContextObject = nullptr;

	UPROPERTY(BlueprintReadWrite)
		TSubclassOf<UGameplayEffect> DamageGameplayEffectClass = nullptr;

	UPROPERTY(BlueprintReadWrite)
		TObjectPtr<UAbilitySystemComponent> SourceAbilitySystemComponent;

	UPROPERTY(BlueprintReadWrite)
		TObjectPtr<UAbilitySystemComponent> TargetAbilitySystemComponent;

	UPROPERTY(BlueprintReadWrite)
		float BaseDamage = 0.f;

	UPROPERTY(BlueprintReadWrite)
		float AbilityLevel = 1.f;

	UPROPERTY(BlueprintReadWrite)
		FGameplayTag DamageType = FGameplayTag();

	UPROPERTY(BlueprintReadWrite)
		float AttackDamageCoefficient = 0;

	UPROPERTY(BlueprintReadWrite)
		float AbilityPowerCoefficient = 0;
	
	UPROPERTY(BlueprintReadWrite)
		FGameplayTag DebuffType = FGameplayTag();

	UPROPERTY(BlueprintReadWrite)
		float DebuffChance = 0.f;

	UPROPERTY(BlueprintReadWrite)
		float DebuffDamage = 0.f;

	UPROPERTY(BlueprintReadWrite)
		float DebuffDuration = 0.f;

	UPROPERTY(BlueprintReadWrite)
		float DebuffFrequency = 0.f;

	UPROPERTY(BlueprintReadWrite)
		float DeathImpulseMagnitude = 0.f;

	UPROPERTY(BlueprintReadWrite)
		FVector DeathImpulse = FVector::ZeroVector;

	UPROPERTY(BlueprintReadWrite)
		float KnockbackForceMagnitude = 0.f;

	UPROPERTY(BlueprintReadWrite)
		float KnockbackChance = 0.f;

	UPROPERTY(BlueprintReadWrite)
		FVector KnockbackForce = FVector::ZeroVector;

	UPROPERTY(BlueprintReadWrite)
		bool bIsRadialDamage = false;

	UPROPERTY(BlueprintReadWrite)
		float RadialDamageInnerRadius = 0.f;

	UPROPERTY(BlueprintReadWrite)
		float RadialDamageOuterRadius = 0.f;

	UPROPERTY(BlueprintReadWrite)
		FVector RadialDamageOrigin = FVector::ZeroVector;

};



USTRUCT(BlueprintType)
struct FMyGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()
public:
	bool IsCriticalHit() const { return bIsCriticalHit; }
	//bool IsBlockedHit() const { return bIsBlockedHit; }
	bool IsSuccessfulDebuff() const { return bIsSuccessfulDebuff; }
	float GetDebuffDamage() const { return DebuffDamage; }
	float GetDebuffDuration() const { return DebuffDuration; }
	float GetDebuffFrequency() const { return DebuffFrequency; }
	TSharedPtr<FGameplayTag> GetDamageType() const { return DamageType; }
	TSharedPtr<FGameplayTag> GetDebuffType() const { return DebuffType; }
	FVector GetDeathImpulse() const { return DeathImpulse; }
	FVector GetKnockbackForce() const { return KnockbackForce; }
	//bool IsRadialDamage() const { return bIsRadialDamage; }
	//float GetRadialDamageInnerRadius() const { return RadialDamageInnerRadius; }
	//float GetRadialDamageOuterRadius() const { return RadialDamageOuterRadius; }
	//FVector GetRadialDamageOrigin() const { return RadialDamageOrigin; }

	void SetIsCriticalHit(bool bInIsCriticalHit) { bIsCriticalHit = bInIsCriticalHit; }
	//void SetIsBlockedHit(bool bInIsBlockedHit) { bIsBlockedHit = bInIsBlockedHit; }
	void SetIsSuccessfulDebuff(bool bInIsDebuff) { bIsSuccessfulDebuff = bInIsDebuff; }
	void SetDebuffDamage(float InDamage) { DebuffDamage = InDamage; }
	void SetDebuffDuration(float InDuration) { DebuffDuration = InDuration; }
	void SetDebuffFrequency(float InFrequency) { DebuffFrequency = InFrequency; }
	void SetDamageType(TSharedPtr<FGameplayTag> InDamageType) { DamageType = InDamageType; }
	void SetDebuffType(TSharedPtr<FGameplayTag> InDebuffType) { DebuffType = InDebuffType; }
	void SetDeathImpulse(const FVector& InImpulse) { DeathImpulse = InImpulse; }
	void SetKnockbackForce(const FVector& InForce) { KnockbackForce = InForce; }
	/*void SetIsRadialDamage(bool bInIsRadialDamage) { bIsRadialDamage = bInIsRadialDamage; }
	void SetRadialDamageInnerRadius(float InRadialDamageInnerRadius) { RadialDamageInnerRadius = InRadialDamageInnerRadius; }
	void SetRadialDamageOuterRadius(float InRadialDamageOuterRadius) { RadialDamageOuterRadius = InRadialDamageOuterRadius; }
	void SetRadialDamageOrigin(const FVector& InRadialDamageOrigin) { RadialDamageOrigin = InRadialDamageOrigin; }*/


	/*
	* 重载函数，直接从GameplayEffectTypes.h复制即可
	*/

	/** Returns the actual struct used for serialization, subclasses must override this! */
	virtual UScriptStruct* GetScriptStruct() const
	{
		return FGameplayEffectContext::StaticStruct();
	}

	/** Creates a copy of this context, used to duplicate for later modifications */
	virtual FGameplayEffectContext* Duplicate() const
	{
		FGameplayEffectContext* NewContext = new FGameplayEffectContext();
		*NewContext = *this;
		if (GetHitResult())
		{
			// Does a deep copy of the hit result
			NewContext->AddHitResult(*GetHitResult(), true);
		}
		return NewContext;
	}

	/** Custom serialization, subclasses must override this */
	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);

protected:

	/*UPROPERTY()
		bool bIsBlockedHit = false;*/

	UPROPERTY()
		bool bIsCriticalHit = false;

	UPROPERTY()
		bool bIsSuccessfulDebuff = false;

	
	TSharedPtr<FGameplayTag> DebuffType;

	UPROPERTY()
		float DebuffDamage = 0.f;

	UPROPERTY()
		float DebuffDuration = 0.f;

	UPROPERTY()
		float DebuffFrequency = 0.f;

	TSharedPtr<FGameplayTag> DamageType;

	UPROPERTY()
		FVector DeathImpulse = FVector::ZeroVector;

	UPROPERTY()
		FVector KnockbackForce = FVector::ZeroVector;

	UPROPERTY()
		bool bIsRadialDamage = false;

	UPROPERTY()
		float RadialDamageInnerRadius = 0.f;

	UPROPERTY()
		float RadialDamageOuterRadius = 0.f;

	UPROPERTY()
		FVector RadialDamageOrigin = FVector::ZeroVector;

};

template<>
struct TStructOpsTypeTraits<FMyGameplayEffectContext> : public TStructOpsTypeTraitsBase2<FMyGameplayEffectContext>
{
	enum
	{
		WithNetSerializer = true,
		WithCopy = true
	};
};