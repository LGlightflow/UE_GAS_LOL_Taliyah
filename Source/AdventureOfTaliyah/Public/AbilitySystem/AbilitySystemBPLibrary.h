// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AbilitySystemBPLibrary.generated.h"

class UAbilitySystemComponent;
class UAttributeMenuWidgetController;
class UOverlayWidgetController;
/**
 * 
 */
UCLASS()
class ADVENTUREOFTALIYAH_API UAbilitySystemBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	

public:
	UFUNCTION(BlueprintPure, Category = "AbilitySystemBPLibrary|WidgetController", meta = (DefaultToSelf = "WorldContextObject"))
		static bool MakeWidgetControllerParams(const UObject* WorldContextObject, FWidgetControllerParams& OutWCParams, AMyHUD*& OutMyHUD);

	UFUNCTION(BlueprintPure, Category = "AbilitySystemBPLibrary|WidgetController", meta = (DefaultToSelf = "WorldContextObject"))
		static UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);


	UFUNCTION(BlueprintPure, Category = "AbilitySystemBPLibrary|WidgetController", meta = (DefaultToSelf = "WorldContextObject"))
		static UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "AbilitySystemBPLibrary|GameplayEffects")
		static bool IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintCallable, Category = "AbilitySystemBPLibrary|GameplayEffects")
		static void SetIsCriticalHit(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool bInIsCriticalHit);
	
	UFUNCTION(BlueprintCallable, Category = "AbilitySystemBPLibrary|GameplayMechanics")
		static void GetLivePlayersWithinRadius(const UObject* WorldContextObject, TArray<AActor*>& OutOverlappingActors, const TArray<AActor*>& ActorsToIgnore, float Radius, const FVector& SphereOrigin);

	UFUNCTION(BlueprintPure, Category = "AbilitySystemBPLibrary|GameplayMechanics")
		static bool IsNotFriend(AActor* FirstActor, AActor* SecondActor);
	
	UFUNCTION(BlueprintCallable, Category = "AbilitySystemBPLibrary|DamageEffect")
		static FGameplayEffectContextHandle ApplyDamageEffect(const FDamageEffectParams& DamageEffectParams);
	//static int32 GetXPRewardForClassAndLevel(const UObject* WorldContextObject, ECharacterClass CharacterClass, int32 CharacterLevel);

	UFUNCTION(BlueprintPure, Category = "AbilitySystemBPLibrary|GameplayEffects")
		static FGameplayTag GetDamageType(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure, Category = "AbilitySystemBPLibrary|GameplayEffects")
		static FGameplayTag GetDebuffType(const FGameplayEffectContextHandle& EffectContextHandle);

	

	UFUNCTION(BlueprintPure, Category = "AbilitySystemBPLibrary|GameplayEffects")
		static bool IsSuccessfulDebuff(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure, Category = "AbilitySystemBPLibrary|GameplayEffects")
		static float GetDebuffDamage(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure, Category = "AbilitySystemBPLibrary|GameplayEffects")
		static float GetDebuffDuration(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure, Category = "AbilitySystemBPLibrary|GameplayEffects")
		static float GetDebuffFrequency(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure, Category = "AbilitySystemBPLibrary|GameplayEffects")
		static FVector GetKnockbackForce(const FGameplayEffectContextHandle& EffectContextHandle);
	
	UFUNCTION(BlueprintCallable, Category = "AbilitySystemBPLibrary|GameplayEffects")
		static void SetDamageType(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, const FGameplayTag& InDamageType);

	UFUNCTION(BlueprintCallable, Category = "AbilitySystemBPLibrary|GameplayEffects")
		static void SetDebuffType(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, const FGameplayTag& InDebuffType);
	
	UFUNCTION(BlueprintCallable, Category = "AbilitySystemBPLibrary|GameplayEffects")
		static void SetIsSuccessfulDebuff(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool bInSuccessfulDebuff);

	UFUNCTION(BlueprintCallable, Category = "AbilitySystemBPLibrary|GameplayEffects")
		static void SetDebuffDamage(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, float InDamage);

	UFUNCTION(BlueprintCallable, Category = "AbilitySystemBPLibrary|GameplayEffects")
		static void SetDebuffDuration(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, float InDuration);

	UFUNCTION(BlueprintCallable, Category = "AbilitySystemBPLibrary|GameplayEffects")
		static void SetDebuffFrequency(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, float InFrequency);

	UFUNCTION(BlueprintCallable, Category = "AbilitySystemBPLibrary|GameplayEffects")
		static void SetKnockbackForce(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, const FVector& InForce);
	
	UFUNCTION(BlueprintPure, Category = "AbilitySystemBPLibrary|GameplayEffects")
		static void SetDeathImpulse(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, const FVector& InImpulse);

};
