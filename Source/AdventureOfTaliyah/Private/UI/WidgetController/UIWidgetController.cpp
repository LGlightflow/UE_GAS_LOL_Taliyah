// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/UIWidgetController.h"

// 给UIWidgetController的属性（在UIWidgetController.h的头文件声明的属性）赋值
// 即获取PC,PS,ASC,AS
void UUIWidgetController::SetWidgetControllerParams(const FWidgetControllerParams WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;

}

void UUIWidgetController::BroadcastInitialValues()
{
	

}

void UUIWidgetController::BindCallbacksToDependencies()
{
}

AMyPlayerController* UUIWidgetController::GetMyPC()
{
	if (MyPlayerController == nullptr)
	{
		MyPlayerController = Cast<AMyPlayerController>(PlayerController);
	}
	return MyPlayerController;
}

AMyPlayerState* UUIWidgetController::GetMyPS()
{
	if (MyPlayerState == nullptr)
	{
		MyPlayerState = Cast<AMyPlayerState>(PlayerState);
	}
	return MyPlayerState;
}

UMyAbilitySystemComponent* UUIWidgetController::GetMyASC()
{
	if (MyAbilitySystemComponent == nullptr)
	{
		MyAbilitySystemComponent = Cast<UMyAbilitySystemComponent>(AbilitySystemComponent);
	}
	return MyAbilitySystemComponent;
}

UMyAttributeSet* UUIWidgetController::GetMyAS()
{
	if (MyAttributeSet == nullptr)
	{
		MyAttributeSet = Cast<UMyAttributeSet>(AttributeSet);
	}
	return MyAttributeSet;
}
