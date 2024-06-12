// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "AttributeInfo.generated.h"

class UGameplayAbility;

USTRUCT(BlueprintType)
struct FMyAttributeInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FGameplayTag AttributeTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FText AttributeName = FText();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FText AttributeDescription = FText();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TObjectPtr<const UTexture2D> Icon = nullptr;

	UPROPERTY(BlueprintReadOnly)
		float AttributeValue = 0.f;

};

/**
 * 类的作用:通过此类创建的BP，来连接Attribute和tags（给attribute填上FMyAttributeInfo结构体中的内容）
 */
UCLASS()
class ADVENTUREOFTALIYAH_API UAttributeInfo : public UDataAsset
{
	GENERATED_BODY()

public:

	FMyAttributeInfo FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound = false) const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TArray<FMyAttributeInfo> AttributeInformation;
};
