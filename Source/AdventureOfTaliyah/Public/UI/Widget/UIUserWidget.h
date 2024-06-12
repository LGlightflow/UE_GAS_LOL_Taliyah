// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UIUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class ADVENTUREOFTALIYAH_API UUIUserWidget : public UUserWidget
{
	GENERATED_BODY()


public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;

protected:
	// 关联WidgetController，当此函数事件触发时调用蓝图
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
};
