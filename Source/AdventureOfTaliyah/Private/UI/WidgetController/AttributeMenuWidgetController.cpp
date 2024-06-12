// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "AbilitySystem/MyAbilitySystemComponent.h"
#include "AbilitySystem/MYAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "Character/Player/MyPlayerState.h"
#include "MyGameplayTags.h"
void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	check(AttributeInfo);
	UMyAttributeSet* AS = CastChecked<UMyAttributeSet>(AttributeSet);
	for (auto& Pair : AS->TagsToAttributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
			[this, Pair,AS](const FOnAttributeChangeData& Data)
			{
				BroadcastAttributeInfo(Pair.Key, Pair.Value());
				FMyAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(Pair.Key);
				Info.AttributeValue = Pair.Value().GetNumericValue(AS);
				AttributeInfoDelegate.Broadcast(Info);
			}
		);
	}

}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	UMyAttributeSet* AS = CastChecked<UMyAttributeSet>(AttributeSet);
	check(AttributeInfo);
	
	/*测试功能*/
	//FMyAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(FMyGameplayTags::Get().Attributes_Primary_AbilityPower);
	//Info.AttributeValue = AS->GetAbilityPower();
	//AttributeInfoDelegate.Broadcast(Info);
	/*测试功能*/

	for (auto& Pair : AS->TagsToAttributes)
	{
		BroadcastAttributeInfo(Pair.Key, Pair.Value());
		FMyAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(Pair.Key);
		Info.AttributeValue = Pair.Value().GetNumericValue(AS);
		AttributeInfoDelegate.Broadcast(Info);

		//BroadcastAttributeInfo(Pair.Key, Pair.Value());
	}

	//AttributePointsChangedDelegate.Broadcast(GetMyPS()->GetAttributePoints());
}

void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute) const
{
	FMyAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(AttributeTag);
	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(Info);
}