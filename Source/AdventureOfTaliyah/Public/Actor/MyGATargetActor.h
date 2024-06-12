// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "MyGATargetActor.generated.h"

/**
 * 
 */
UCLASS()
class ADVENTUREOFTALIYAH_API AMyGATargetActor : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()
public:
	AMyGATargetActor();
	virtual void StartTargeting(UGameplayAbility* Ability) override;

	virtual void ConfirmTargetingAndContinue() override;

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Settings", meta = (ExposeOnSpawn = true))
		float Radius;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability Settings", meta = (ExposeOnSpawn = true))
		TSubclassOf<AActor> ConePointClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability Settings", meta = (ExposeOnSpawn = true))
		TSubclassOf<AActor> MeteorClass;

	// Get Player Looking Point Vector
	UFUNCTION(BlueprintCallable, Category = "Ability Settings")
		bool GetPlayerLookingPoint(FVector& LookingPoint);

protected:
	UPROPERTY()
		AActor* ConePoint;

	UPROPERTY()
		AActor* Meteor;
public:

	
};
