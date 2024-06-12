// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "MyGameplayAbility.generated.h"

/**
 *  
 */
UCLASS()
class ADVENTUREOFTALIYAH_API UMyGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	// (键盘、鼠标)输入的Tags，通过配置tags实现按键启动ability
	UPROPERTY(EditDefaultsOnly, Category = "Input")
		FGameplayTag StartupInputTag;

};
