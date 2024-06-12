// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAssetManager.h"
#include "MyGameplayTags.h"
#include "AbilitySystemGlobals.h"
/* 获取资产管理器
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
	//通过InitializeNativeGameplayTags()来初始化本地Tags，提供了一种用C++处理Tags的方式
	FMyGameplayTags::InitializeNativeGameplayTags();

	// This is required to use Target Data 如果要使用TargetData，需要去进行全局数据的初始化
	UAbilitySystemGlobals::Get().InitGlobalData();
}
