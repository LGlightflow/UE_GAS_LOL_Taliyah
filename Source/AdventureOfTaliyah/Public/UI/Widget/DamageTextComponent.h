// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "DamageTextComponent.generated.h"

/**
 * 
 */
UCLASS()
class ADVENTUREOFTALIYAH_API UDamageTextComponent : public UWidgetComponent
{
	GENERATED_BODY()
public:
	//MyplayerControllerÖÐµ÷ÓÃ
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void SetDamageText(float Damage,bool bCriticalHit);
};
