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
	// ����WidgetController�����˺����¼�����ʱ������ͼ
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
};
