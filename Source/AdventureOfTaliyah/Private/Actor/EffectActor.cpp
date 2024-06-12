// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/EffectActor.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Kismet/KismetMathLibrary.h"
// Sets default values
AEffectActor::AEffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));

}

void AEffectActor::Tick(float DeltaTime)
{
}

// Called when the game starts or when spawned
void AEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
}

//void AEffectActor::StartSinusoidalMovement()
//{
//}
//
//void AEffectActor::StartRotation()
//{
//}

// ��GEӦ�õ�Ŀ�꣬
// ԭ������ͼ�е��ã����ڱ�EffectActor���е�OnOverlap��OnEndOverlap��������
void AEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	// ���Ŀ��actor��enemy��tags���Լ�bApplyEffectsToEnemies����Ϊ0������enemyӦ��GE�����򷵻�
	if (TargetActor->ActorHasTag(FName("Enemy")) && !bApplyEffectsToEnemies || TargetActor->ActorHasTag(FName("Player")) && !bApplyEffectsToPlayers) return;

	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (TargetASC == nullptr) return;

	check(GameplayEffectClass);
	//GameplayEffectContext�ṹ����й���GameplayEffectSpec������(Instigator)��TargetData����Ϣ
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	// �洢��FGameplayEffectContext�йص���Ϣ�� ��UObject����My����ֵ��FGameplayEffectContext�ĳ�Ա
	// �÷�������Ҫ֪����ʲôobject������GE
	EffectContextHandle.AddSourceObject(this);
	//Get an outgoing GameplayEffectSpec that is ready to be applied to other things.
	//GameplayEffectSpec�����ú�ģ�������GE��GameplayEffectSpecHandle
	//FGameplayEffectSpecHandle�ṹ������һ��ָ�����ָ��FGameplayEffectSpec
	const FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass, ActorLevel, EffectContextHandle);
	const FActiveGameplayEffectHandle ActiveEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

	const bool bIsInfinite = EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;
	if (bIsInfinite && InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		ActiveEffectHandles.Add(ActiveEffectHandle, TargetASC);
	}

	if (!bIsInfinite)
	{
		Destroy();
	}
}
// ��ͼ�е���,����ײ����ʱGE�Ķ���
void AEffectActor::OnOverlap(AActor* TargetActor)
{
	if (TargetActor->ActorHasTag(FName("Enemy")) && !bApplyEffectsToEnemies || TargetActor->ActorHasTag(FName("Player")) && !bApplyEffectsToPlayers) return;

	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
	}
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}

}
// ��ͼ�е���,����ײ����ʱGE�Ķ���
void AEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (TargetActor->ActorHasTag(FName("Enemy")) && !bApplyEffectsToEnemies || TargetActor->ActorHasTag(FName("Player")) && !bApplyEffectsToPlayers) return;

	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
	}
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}
	if (InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
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





