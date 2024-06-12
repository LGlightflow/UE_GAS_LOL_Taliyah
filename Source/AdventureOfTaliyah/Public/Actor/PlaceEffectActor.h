// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyAbilityTypes.h"
#include "PlaceEffectActor.generated.h"

/**
 * 
 */
class UAbilitySystemComponent;
class UGameplayEffect;

UENUM(BlueprintType)
enum class EEffectApplicationPolicy1 :uint8
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};

UENUM(BlueprintType)
enum class EEffectRemovalPolicy1 :uint8
{
	RemoveOnEndOverlap,
	DoNotRemove
};


UCLASS()
class ADVENTUREOFTALIYAH_API APlaceEffectActor : public AActor
{
	GENERATED_BODY()
	
public:
	APlaceEffectActor();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true))
		FDamageEffectParams DamageEffectParams;


protected:
	virtual void BeginPlay() override;


	//UPROPERTY(BlueprintReadWrite)
	//	FVector CalculatedLocation;
	//UPROPERTY(BlueprintReadWrite)
	//	FRotator CalculatedRotation;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup Movement")
	//	bool bRotates = false;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup Movement")
	//	float RotationRate = 45.f;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup Movement")
	//	bool bSinusoidalMovement = false;
	//UFUNCTION(BlueprintCallable)
	//	void StartSinusoidalMovement();
	//UFUNCTION(BlueprintCallable)
	//	void StartRotation();
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup Movement")
	//	float SineAmplitude = 1.f;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup Movement")
	//	float SinePeriodConstant = 1.f;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup Movement")
	//	FVector InitialLocation;

	UFUNCTION(BlueprintCallable)
		virtual void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);

	UFUNCTION(BlueprintCallable)
		virtual void OnOverlap(AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
		virtual void OnEndOverlap(AActor* TargetActor);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
		bool bDestroyOnEffectApplication = false;

	// 是否对敌人应用GE
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
		bool bApplyEffectsToEnemies = false;
	// 是否对玩家应用GE
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
		bool bApplyEffectsToPlayers = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
		TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
		EEffectApplicationPolicy1 InstantEffectApplicationPolicy = EEffectApplicationPolicy1::DoNotApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
		TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
		EEffectApplicationPolicy1 DurationEffectApplicationPolicy = EEffectApplicationPolicy1::DoNotApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
		TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
		EEffectApplicationPolicy1 InfiniteEffectApplicationPolicy = EEffectApplicationPolicy1::DoNotApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
		EEffectRemovalPolicy1 InfiniteEffectRemovalPolicy = EEffectRemovalPolicy1::RemoveOnEndOverlap;

	//键值对Map
	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveEffectHandles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
		float ActorLevel = 1.f;

	void ApplyDamageEffectParams(AActor* TargetActor);

private:

	float RunningTime = 0.f;
	void ItemMovement(float DeltaTime);

};
