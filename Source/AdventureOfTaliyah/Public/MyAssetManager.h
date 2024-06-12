// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "MyAssetManager.generated.h"

/**
 * 
 * ��DefaultEngine.ini�е�[/Script/Engine.Engine]��� AssetManagerClassName=/Script/AdventureOfTaliyah.MyAssetManager��/Script/[��Ŀ��].�ʲ�������������
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
