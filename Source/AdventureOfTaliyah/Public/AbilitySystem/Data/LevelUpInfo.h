// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LevelUpInfo.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FMyLevelUpInfo
{
	GENERATED_BODY()
		
		// LevelUpRequirement：升级需要的总经验，例如
		//LevelUpInformation[1].LevelUpRequirement = 40，level=1需要40点经验才能升级
		//level=0 时LevelUpRequirement=0，
		UPROPERTY(EditDefaultsOnly)
		int32 LevelUpRequirement = 0;

	//UPROPERTY(EditDefaultsOnly)
	//	int32 AttributePointAward = 1;

	UPROPERTY(EditDefaultsOnly)
		int32 SpellPointAward = 1;
};
UCLASS()
class ADVENTUREOFTALIYAH_API ULevelUpInfo : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
		TArray<FMyLevelUpInfo> LevelUpInformation;

	int32 FindLevelForXP(int32 XP) const;
};
