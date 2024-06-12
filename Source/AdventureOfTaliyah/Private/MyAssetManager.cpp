// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAssetManager.h"
#include "MyGameplayTags.h"
#include "AbilitySystemGlobals.h"
/* ��ȡ�ʲ�������
*/
UMyAssetManager& UMyAssetManager::Get()
{
	check(GEngine);

	UMyAssetManager* MyAssetManager = Cast<UMyAssetManager>(GEngine->AssetManager);
	return *MyAssetManager;
}

void UMyAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	//ͨ��InitializeNativeGameplayTags()����ʼ������Tags���ṩ��һ����C++����Tags�ķ�ʽ
	FMyGameplayTags::InitializeNativeGameplayTags();

	// This is required to use Target Data ���Ҫʹ��TargetData����Ҫȥ����ȫ�����ݵĳ�ʼ��
	UAbilitySystemGlobals::Get().InitGlobalData();
}
