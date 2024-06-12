// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "EffectActor.generated.h"

class UAbilitySystemComponent;
class UGameplayEffect;

UENUM(BlueprintType)
enum class EEffectApplicationPolicy:uint8
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};

UENUM(BlueprintType)
enum class EEffectRemovalPolicy:uint8
{
	RemoveOnEndOverlap,
	DoNotRemove
};

/**
 *  可以放置在world的actor，可触发GE
 *	在BP中设置
 */
UCLASS()
class ADVENTUREOFTALIYAH_API AEffectActor : public AActor
{
	GENERATED_BODY()
		
public:	
	// Sets default values for this actor's properties
	AEffectActor();
	virtual void Tick(float DeltaTime) override;
protected:

	// Called when the game starts or when spawned
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
		EEffectApplicationPolicy InstantEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
		TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
		EEffectApplicationPolicy DurationEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
		TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
		EEffectApplicationPolicy InfiniteEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
		EEffectRemovalPolicy InfiniteEffectRemovalPolicy = EEffectRemovalPolicy::RemoveOnEndOverlap;

	//键值对Map
	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveEffectHandles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
		float ActorLevel = 1.f;

private:

	float RunningTime = 0.f;
	void ItemMovement(float DeltaTime);
};
