// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/UIWidgetController.h"
#include "AbilitySystem/Data/AbilityInfo.h"
#include "OverlayWidgetController.generated.h"

USTRUCT(BlueprintType)
struct FUIWidgetRow : public FTableRowBase
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FGameplayTag MessageTag = FGameplayTag();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FText Message = FText();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TSubclassOf<class UUIUserWidget> MessageWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UTexture2D* Image = nullptr;
};

// 创建attributeset属性的多播委托
// 在UOverlayWidgetController进行声明，（如OnHealthChanged）

class UUIUserWidget;
class UAbilityInfo;
class UMyAbilitySystemComponent;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedSignature, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLevelChangedSignature, int32, NewLevel, bool, bLevelUp);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMessageWidgetRowSignature, FUIWidgetRow, Row);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAbilityInfoSignature, const FMyAbilityInfo&, Info);




/**
 *
 */
UCLASS(BlueprintType, Blueprintable)
class ADVENTUREOFTALIYAH_API UOverlayWidgetController : public UUIWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
		FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
		FOnAttributeChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
		FOnAttributeChangedSignature OnManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
		FOnAttributeChangedSignature OnMaxManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Messages")
		FMessageWidgetRowSignature MessageWidgetRowDelegate;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Messages")
		FAbilityInfoSignature AbilityInfoDelegate;

	UPROPERTY(BlueprintAssignable, Category = "GAS|XP")
		FOnAttributeChangedSignature OnXPPercentChangedDelegate;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Level")
		FOnLevelChangedSignature OnPlayerLevelChangedDelegate;
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widget Data")
		TObjectPtr<UDataTable> MessageWidgetDataTable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widget Data")
		TObjectPtr<UAbilityInfo> AbilityInfo;

	void OnInitializeStartupAbilities(UMyAbilitySystemComponent* MyAbilitySystemComponent);
	void OnXPChanged(int32 NewXP);
	template<typename T>
	T* GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag);



	//响应attribute改变的回调
	/*protected:
		void HealthChanged(const FOnAttributeChangeData& Data) const;
		void MaxHealthChanged(const FOnAttributeChangeData& Data) const;
		void ManaChanged(const FOnAttributeChangeData& Data) const;
		void MaxManaChanged(const FOnAttributeChangeData& Data) const;
	*/

};



template <typename T>
T* UOverlayWidgetController::GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag)
{
	// 根据tag名字返回其在data_table的行
	return DataTable->FindRow<T>(Tag.GetTagName(), TEXT(""));
}
