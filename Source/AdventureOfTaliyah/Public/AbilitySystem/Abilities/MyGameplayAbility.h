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
	// (���̡����)�����Tags��ͨ������tagsʵ�ְ�������ability
	UPROPERTY(EditDefaultsOnly, Category = "Input")
		FGameplayTag StartupInputTag;

};
