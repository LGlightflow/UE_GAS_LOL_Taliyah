// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/PlaceEffectActor.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "MyGameplayTags.h"
#include "AbilitySystem/AbilitySystemBPLibrary.h"

//void APlaceEffectActor::BeginPlay()
//{
//	Super::BeginPlay();
//}
//
//
//APlaceEffectActor::APlaceEffectActor()
//{
//	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
//}
//
//void APlaceEffectActor::Tick(float DeltaTime)
//{
//}
//
//
//
//void APlaceEffectActor::ApplyEffectToTarget(AActor* TargetActor, FDamageEffectParams& DamageEffectParams)
//{
//	if (!HasAuthority()) return;
//	if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor))
//	{ 
//		DamageEffectParams.TargetAbilitySystemComponent = TargetASC;
//	// 如果目标actor有enemy的tags，以及bApplyEffectsToEnemies设置为0（不对enemy应用GE），则返回
//		
//		if (TargetActor->ActorHasTag(FName("Enemy")) && !bApplyEffectsToEnemies || !TargetActor->ActorHasTag(FName("Enemy")) && !bApplyEffectsToPlayers) return;
//
//		const FMyGameplayTags& GameplayTags = FMyGameplayTags::Get();
//		const AActor* SourceAvatarActor = DamageEffectParams.SourceAbilitySystemComponent->GetAvatarActor();
//
//
//		if (TargetASC == nullptr) return;
//
//		//GameplayEffectContext结构体存有关于GameplayEffectSpec创建者(Instigator)和TargetData的信息
//		FGameplayEffectContextHandle EffectContexthandle = DamageEffectParams.SourceAbilitySystemComponent->MakeEffectContext();
//		EffectContexthandle.AddSourceObject(SourceAvatarActor);
//
//		UAbilitySystemBPLibrary::SetDebuffType(EffectContexthandle, DamageEffectParams.DebuffType);
//		UAbilitySystemBPLibrary::SetDeathImpulse(EffectContexthandle, DamageEffectParams.DeathImpulse);
//		UAbilitySystemBPLibrary::SetKnockbackForce(EffectContexthandle, DamageEffectParams.KnockbackForce);
//		const FGameplayEffectSpecHandle SpecHandle = DamageEffectParams.SourceAbilitySystemComponent->MakeOutgoingSpec(DamageEffectParams.DamageGameplayEffectClass, DamageEffectParams.AbilityLevel, EffectContexthandle);
//		const FActiveGameplayEffectHandle ActiveEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
//
//		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, FMyGameplayTags::Get().AbilityPowerCoefficient, DamageEffectParams.AbilityPowerCoefficient);
//		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, FMyGameplayTags::Get().AttackDamageCoefficient, DamageEffectParams.AttackDamageCoefficient);
//		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, DamageEffectParams.DamageType, DamageEffectParams.BaseDamage);
//		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.Debuff_Chance, DamageEffectParams.DebuffChance);
//		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.Debuff_Damage, DamageEffectParams.DebuffDamage);
//		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.Debuff_Duration, DamageEffectParams.DebuffDuration);
//		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.Debuff_Frequency, DamageEffectParams.DebuffFrequency);
//
//
//		const bool bIsInfinite = SpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;
//		if (bIsInfinite && InfiniteEffectRemovalPolicy == EEffectParamsRemovalPolicy::RemoveOnEndOverlap)
//		{
//			ActiveEffectHandles.Add(ActiveEffectHandle, TargetASC);
//		}
//
//		if (!bIsInfinite)
//		{
//			Destroy();
//		}
//	}
//
//
//}
//
//void APlaceEffectActor::OnOverlap(AActor* TargetActor)
//{
//	if (TargetActor->ActorHasTag(FName("Enemy")) && !bApplyEffectsToEnemies || TargetActor->ActorHasTag(FName("Player")) && !bApplyEffectsToPlayers) return;
//
//	if (InstantEffectApplicationPolicy == EEffectParamsApplicationPolicy::ApplyOnOverlap)
//	{
//		ApplyEffectToTarget(TargetActor, InstantGameplayDamageEffectParams);
//	}
//	if (DurationEffectApplicationPolicy == EEffectParamsApplicationPolicy::ApplyOnOverlap)
//	{
//		ApplyEffectToTarget(TargetActor, DurationGameplayDamageEffectParams);
//	}
//	if (InfiniteEffectApplicationPolicy == EEffectParamsApplicationPolicy::ApplyOnOverlap)
//	{
//		ApplyEffectToTarget(TargetActor, InfiniteGameplayDamageEffectParams);
//	}
//}
//
//void APlaceEffectActor::OnEndOverlap(AActor* TargetActor)
//{
//	if (TargetActor->ActorHasTag(FName("Enemy")) && !bApplyEffectsToEnemies || TargetActor->ActorHasTag(FName("Player")) && !bApplyEffectsToPlayers) return;
//
//	if (InstantEffectApplicationPolicy == EEffectParamsApplicationPolicy::ApplyOnEndOverlap)
//	{
//		ApplyEffectToTarget(TargetActor, InstantGameplayDamageEffectParams);
//	}
//	if (DurationEffectApplicationPolicy == EEffectParamsApplicationPolicy::ApplyOnEndOverlap)
//	{
//		ApplyEffectToTarget(TargetActor, DurationGameplayDamageEffectParams);
//	}
//	if (InfiniteEffectApplicationPolicy == EEffectParamsApplicationPolicy::ApplyOnEndOverlap)
//	{
//		ApplyEffectToTarget(TargetActor, InfiniteGameplayDamageEffectParams);
//	}
//	if (InfiniteEffectRemovalPolicy == EEffectParamsRemovalPolicy::RemoveOnEndOverlap)
//	{
//		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
//		if (!IsValid(TargetASC)) return;
//
//		TArray<FActiveGameplayEffectHandle> HandlesToRemove;
//		for (TTuple<FActiveGameplayEffectHandle, UAbilitySystemComponent*> HandlePair : ActiveEffectHandles)
//		{
//			if (TargetASC == HandlePair.Value)
//			{
//				TargetASC->RemoveActiveGameplayEffect(HandlePair.Key, 1);
//				HandlesToRemove.Add(HandlePair.Key);
//			}
//		}
//		for (FActiveGameplayEffectHandle& Handle : HandlesToRemove)
//		{
//			ActiveEffectHandles.FindAndRemoveChecked(Handle);
//		}
//	}
//
//}
APlaceEffectActor::APlaceEffectActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
	//PrimaryActorTick.bCanEverTick = true;
}

void APlaceEffectActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

// Called when the game starts or when spawned
void APlaceEffectActor::BeginPlay()
{
	Super::BeginPlay();
	//PrimaryActorTick.bCanEverTick = true; //在蓝图设置，避免报错
	
}

//void APlaceEffectActor::StartSinusoidalMovement()
//{
//}
//
//void APlaceEffectActor::StartRotation()
//{
//}

// 将GE应用到目标，
// 原本在蓝图中调用，现在被EffectActor类中的OnOverlap、OnEndOverlap函数调用
void APlaceEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	// 如果目标actor有enemy的tags，以及bApplyEffectsToEnemies设置为0（不对enemy应用GE），则返回
	if (TargetActor->ActorHasTag(FName("Enemy")) && !bApplyEffectsToEnemies || TargetActor->ActorHasTag(FName("Player")) && !bApplyEffectsToPlayers) return;

	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (TargetASC == nullptr) return;

	//check(GameplayEffectClass);
	//GameplayEffectContext结构体存有关于GameplayEffectSpec创建者(Instigator)和TargetData的信息
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	// 存储与FGameplayEffectContext有关的信息， 本UObject（即My）赋值给FGameplayEffectContext的成员
	// 用法：例如要知道是什么object调用了GE
	EffectContextHandle.AddSourceObject(this);
	//Get an outgoing GameplayEffectSpec that is ready to be applied to other things.
	//GameplayEffectSpec是设置好模板参数的GE，GameplayEffectSpecHandle
	//FGameplayEffectSpecHandle结构体中有一个指针变量指向FGameplayEffectSpec
	const FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass, ActorLevel, EffectContextHandle);
	const FActiveGameplayEffectHandle ActiveEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	ApplyDamageEffectParams(TargetActor);
	const bool bIsInfinite = EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;
	if (bIsInfinite && InfiniteEffectRemovalPolicy == EEffectRemovalPolicy1::RemoveOnEndOverlap)
	{
		ActiveEffectHandles.Add(ActiveEffectHandle, TargetASC);
	}

	if (!bIsInfinite)
	{
		Destroy();
	}
}
// 蓝图中调用,当碰撞发生时GE的动作
void APlaceEffectActor::OnOverlap(AActor* TargetActor)
{
	if (TargetActor->ActorHasTag(FName("Enemy")) && !bApplyEffectsToEnemies || TargetActor->ActorHasTag(FName("Player")) && !bApplyEffectsToPlayers) return;

	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy1::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
		
	}
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy1::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy1::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}

}
// 蓝图中调用,当碰撞结束时GE的动作
void APlaceEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (TargetActor->ActorHasTag(FName("Enemy")) && !bApplyEffectsToEnemies || TargetActor->ActorHasTag(FName("Player")) && !bApplyEffectsToPlayers) return;

	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy1::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
	}
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy1::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy1::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}
	if (InfiniteEffectRemovalPolicy == EEffectRemovalPolicy1::RemoveOnEndOverlap)
	{
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if (!IsValid(TargetASC)) return;

		TArray<FActiveGameplayEffectHandle> HandlesToRemove;
		for (TTuple<FActiveGameplayEffectHandle, UAbilitySystemComponent*> HandlePair : ActiveEffectHandles)
		{
			if (TargetASC == HandlePair.Value)
			{
				TargetASC->RemoveActiveGameplayEffect(HandlePair.Key, 1);
				HandlesToRemove.Add(HandlePair.Key);
			}
		}
		for (FActiveGameplayEffectHandle& Handle : HandlesToRemove)
		{
			ActiveEffectHandles.FindAndRemoveChecked(Handle);
		}
	}
}

void APlaceEffectActor::ApplyDamageEffectParams(AActor* TargetActor)
{
	if (HasAuthority())
	{
		if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor))
		{
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
	}
}