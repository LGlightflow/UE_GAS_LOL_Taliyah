// Fill out your copyright notice in the Description page of Project Settings.

#include "Actor/RangedAttackProjectile.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

#include "Components/AudioComponent.h"

#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "AbilitySystem/AbilitySystemBPLibrary.h"


// Sets default values
ARangedAttackProjectile::ARangedAttackProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	bReplicates = true;

	PrimaryActorTick.bCanEverTick = false;
	SphereCollision = CreateDefaultSubobject<USphereComponent>("ShpereCollision");
	SetRootComponent(SphereCollision);
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::ProbeOnly);
	SphereCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereCollision->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap); // 这一项按需求删掉
	SphereCollision->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap); // 这一项按需求删掉
	SphereCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SphereCollision->InitSphereRadius(10.0f);
	 
	//以上用于所有投射物定义，以下是自定义（例如速度、重力等），可写在派生类中
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->ProjectileGravityScale = 0.00005f;
}


// Called when the game starts or when spawned
void ARangedAttackProjectile::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(LifeSpan);
	SetReplicateMovement(true);
	ProjectileMovement->Velocity = GetActorForwardVector() * ProjectileMovement->InitialSpeed;
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ARangedAttackProjectile::OnSphereOverlap);

	/**************声音和粒子系统，声音后期可能用wwise集成*******************/
	LoopingSoundComponent = UGameplayStatics::SpawnSoundAttached(LoopingSound, GetRootComponent());

}

void ARangedAttackProjectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsValidOverlap(OtherActor)) return;
	if (!bHit) OnHit();

	/**************声音和粒子系统，声音后期可能用wwise集成*******************/
	UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation(), FRotator::ZeroRotator);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffect, GetActorLocation());


	if (LoopingSoundComponent)
	{
		LoopingSoundComponent->Stop();
		LoopingSoundComponent->DestroyComponent();
	}
	/**************声音和粒子系统，声音后期可能用wwise集成*******************/


	//判断当前 Actor 是否在服务器上运行。当该函数返回 True 时，代表当前 Actor 在服务器上运行，可以执行服务器端的操作
	if (HasAuthority())
	{
		if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
		{
			//TargetASC->ApplyGameplayEffectSpecToSelf(*DamageEffectSpecHandle.Data.Get());
			const FVector DeathImpulse = GetActorForwardVector() * DamageEffectParams.DeathImpulseMagnitude;
			DamageEffectParams.DeathImpulse = DeathImpulse;
			const bool bKnockback = FMath::RandRange(1, 100) < DamageEffectParams.KnockbackChance;
			if (bKnockback)
			{
				FRotator Rotation = GetActorRotation();
				Rotation.Pitch = 45.f;

				const FVector KnockbackDirection = Rotation.Vector();
				const FVector KnockbackForce = KnockbackDirection * DamageEffectParams.KnockbackForceMagnitude;
				DamageEffectParams.KnockbackForce = KnockbackForce;
			}
			
			DamageEffectParams.TargetAbilitySystemComponent = TargetASC;
			UAbilitySystemBPLibrary::ApplyDamageEffect(DamageEffectParams);
		}
		Destroy();
	}
	else {
		bHit = true;
	}
}

bool ARangedAttackProjectile::IsValidOverlap(AActor* OtherActor)
{

	if (DamageEffectParams.SourceAbilitySystemComponent == nullptr) return false;
	AActor* SourceAvatarActor = DamageEffectParams.SourceAbilitySystemComponent->GetAvatarActor();
	if (SourceAvatarActor == OtherActor ) return false;
	if (OtherActor == this) return false; // 自己加的
	if (!UAbilitySystemBPLibrary::IsNotFriend(SourceAvatarActor, OtherActor)) return false;

	return true;
}



void ARangedAttackProjectile::OnHit()
{
	UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation(), FRotator::ZeroRotator);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffect, GetActorLocation());
	if (LoopingSoundComponent)
	{
		LoopingSoundComponent->Stop();
		LoopingSoundComponent->DestroyComponent();
	}
	bHit = true;
}

void ARangedAttackProjectile::Destroyed()
{
	if (LoopingSoundComponent)
	{
		LoopingSoundComponent->Stop();
		LoopingSoundComponent->DestroyComponent();
	}
	if (!bHit && !HasAuthority()) OnHit();
	Super::Destroyed();


	if (!bHit && !HasAuthority()) {
		UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation(), FRotator::ZeroRotator);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffect, GetActorLocation());
		
	}
	Super::Destroyed();
}

// Called every frame
void ARangedAttackProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

