// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "MyAbilityTypes.h"
#include "RangedAttackProjectile.generated.h"

class UNiagaraSystem;
UCLASS()
class ADVENTUREOFTALIYAH_API ARangedAttackProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARangedAttackProjectile();

	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	FDamageEffectParams DamageEffectParams;
protected:
	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,bool bFromSweep,const FHitResult& SweepResult );

	// 将裸指针替换为TObjectPtr，提供编辑器下动态解析和访问追踪功能
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TObjectPtr<USphereComponent> SphereCollision;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
		virtual void OnHit();
	virtual void Destroyed() override;

	bool IsValidOverlap(AActor* OtherActor);

	// 是否击中
	bool bHit = false;

	UPROPERTY()
		TObjectPtr<UAudioComponent> LoopingSoundComponent;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:
	UPROPERTY(EditDefaultsOnly)
		float LifeSpan = 20.f;

	UPROPERTY(EditAnywhere)
		TObjectPtr<UNiagaraSystem> ImpactEffect;

	UPROPERTY(EditAnywhere)
		TObjectPtr<USoundBase> ImpactSound;

	UPROPERTY(EditAnywhere)
		TObjectPtr<USoundBase> LoopingSound;
};
