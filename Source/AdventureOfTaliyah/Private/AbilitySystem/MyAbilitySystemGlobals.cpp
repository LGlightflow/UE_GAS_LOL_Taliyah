// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/MyAbilitySystemGlobals.h"
#include "MyAbilityTypes.h"

FGameplayEffectContext* UMyAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FMyGameplayEffectContext();
}
