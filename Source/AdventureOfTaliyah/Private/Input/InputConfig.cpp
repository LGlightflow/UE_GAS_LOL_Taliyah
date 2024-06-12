// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/InputConfig.h"

// 和UAttributeInfo的FindAttributeInfoForTag()类似
const UInputAction* UInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{	//遍历AbilityInputActions,返回
	for (const FMyInputAction& Action : AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag == InputTag)
		{
			return Action.InputAction;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find AbilityInputAction for InputTag [%s], on InputConfig [%s]"), *InputTag.ToString(), *GetNameSafe(this));
	}

	return nullptr;
}
