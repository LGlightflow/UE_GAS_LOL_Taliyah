// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "MyAssetManager.generated.h"

/**
 * 
 * 在DefaultEngine.ini中的[/Script/Engine.Engine]添加 AssetManagerClassName=/Script/AdventureOfTaliyah.MyAssetManager（/Script/[项目名].资产管理器类名）
 */
UCLASS()
class ADVENTUREOFTALIYAH_API UMyAssetManager : public UAssetManager
{
	GENERATED_BODY()
	
public:

	static UMyAssetManager& Get();

protected:

	virtual void StartInitialLoading() override;
};
