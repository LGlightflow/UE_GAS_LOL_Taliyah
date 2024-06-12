// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/MyGameplayAbility.h"
#include "SummonAbility.generated.h"

/**
 * 
 */
UCLASS()
class ADVENTUREOFTALIYAH_API USummonAbility : public UMyGameplayAbility
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
		TArray<FVector> GetSpawnLocations();

	UFUNCTION(BlueprintPure, Category = "Summoning")
		TSubclassOf<APawn> GetRandomMinionClass();

	UPROPERTY(EditDefaultsOnly, Category = "Summoning")
		int32 NumMinions = 5;

	UPROPERTY(EditDefaultsOnly, Category = "Summoning")
		TArray<TSubclassOf<APawn>> MinionClasses;

	UPROPERTY(EditDefaultsOnly, Category = "Summoning")
		float MinSpawnDistance = 50.f;

	UPROPERTY(EditDefaultsOnly, Category = "Summoning")
		float MaxSpawnDistance = 250.f;

	UPROPERTY(EditDefaultsOnly, Category = "Summoning")
		float SpawnSpread = 90.f;
};
