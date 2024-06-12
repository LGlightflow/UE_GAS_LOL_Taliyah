// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AbilityTask/TargetData.h"
#include "AbilitySystemComponent.h"


UTargetData* UTargetData::CreateTargetData(UGameplayAbility* OwningAbility)
{
	UTargetData* MyObj = NewAbilityTask<UTargetData>(OwningAbility);
	return MyObj;
}

void UTargetData::Activate()
{
	const bool bIsLocallyControlled = Ability->GetCurrentActorInfo()->IsLocallyControlled();
	if (bIsLocallyControlled)
	{
		//在客户端，发送获取到的数据
		SendMouseCursorData();
	}
	else
	{

		//在服务端 监听数据
	const FGameplayAbilitySpecHandle SpecHandle = GetAbilitySpecHandle();
	const FPredictionKey ActivationPredictionKey = GetActivationPredictionKey();
	AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(SpecHandle, ActivationPredictionKey).AddUObject(this, &UTargetData::OnTargetDataReplicatedCallback);
		const bool bCalledDelegate = AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(SpecHandle, ActivationPredictionKey);
		if (!bCalledDelegate)
		{
			SetWaitingOnRemotePlayerData();
		}
	}
}

void UTargetData::SendMouseCursorData()
{
	FScopedPredictionWindow ScopedPrediction(AbilitySystemComponent.Get());

	APlayerController* PC = Ability->GetCurrentActorInfo()->PlayerController.Get();
	FHitResult CursorHit;

	// 获取鼠标点击的位置
	PC->GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
//
	FGameplayAbilityTargetDataHandle DataHandle;
	FGameplayAbilityTargetData_SingleTargetHit* Data = new FGameplayAbilityTargetData_SingleTargetHit();
	// 这个data的hitresult可以改为所需要的值
	Data->HitResult = CursorHit;
	DataHandle.Add(Data);
	
	// 向服务端发送数据 Replicates targeting data to the server
	AbilitySystemComponent->ServerSetReplicatedTargetData(
		GetAbilitySpecHandle(),
		GetActivationPredictionKey(),
		DataHandle,
		FGameplayTag(),
		AbilitySystemComponent->ScopedPredictionKey);
//
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(DataHandle);
	}
}
//
void UTargetData::OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle, FGameplayTag ActivationTag)
{
	AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey());
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(DataHandle);
	}
}
