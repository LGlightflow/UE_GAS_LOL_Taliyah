// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "MyAbilitySystemGlobals.generated.h"

/**
 * 
 */
UCLASS()
class ADVENTUREOFTALIYAH_API UMyAbilitySystemGlobals : public UAbilitySystemGlobals
{
	GENERATED_BODY()
		virtual FGameplayEffectContext* AllocGameplayEffectContext() const override;
	
};
