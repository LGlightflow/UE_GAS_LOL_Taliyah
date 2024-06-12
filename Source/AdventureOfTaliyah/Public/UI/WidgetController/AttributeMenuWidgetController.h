// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/UIWidgetController.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "AttributeMenuWidgetController.generated.h"



class UAttributeInfo;
struct FMyAttributeInfo;
struct FGameplayTag;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoSignature, const FMyAttributeInfo&, Info);
/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class ADVENTUREOFTALIYAH_API UAttributeMenuWidgetController : public UUIWidgetController
{
	GENERATED_BODY()

public:
	virtual void BindCallbacksToDependencies() override;
	virtual void BroadcastInitialValues() override;
	void BroadcastAttributeInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute) const;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
		FAttributeInfoSignature AttributeInfoDelegate;

	//UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	//	FOnPlayerStatChangedSignature AttributePointsChangedDelegate;

	//UFUNCTION(BlueprintCallable)
	//	void UpgradeAttribute(const FGameplayTag& AttributeTag);

protected:

	UPROPERTY(EditDefaultsOnly)
		TObjectPtr<UAttributeInfo> AttributeInfo;

private:

	//void BroadcastAttributeInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute) const;
};
