// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffect.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Bullet.generated.h"


class USphereComponent;

UCLASS()
class ADVENTUREOFTALIYAH_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Åö×²×é¼þ
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	USphereComponent* SphereCollision;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UProjectileMovementComponent* MovementComponent;

public:
	UPROPERTY(BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
		FGameplayEffectSpecHandle DamageEffectSpecHandle;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
