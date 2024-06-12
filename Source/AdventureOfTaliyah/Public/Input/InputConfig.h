// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTags.h"
#include "InputConfig.generated.h"


USTRUCT(BlueprintType)
struct FMyInputAction
{
	GENERATED_BODY()

		UPROPERTY(EditDefaultsOnly)
		const class UInputAction* InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly)
		FGameplayTag InputTag = FGameplayTag();
};

/**
 *  ≈‰÷√input action ∫Õtagµƒ”≥…‰
 */
UCLASS()
class ADVENTUREOFTALIYAH_API UInputConfig : public UDataAsset
{
	GENERATED_BODY()
public:
	const UInputAction* FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = false) const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TArray<FMyInputAction> AbilityInputActions;

};
