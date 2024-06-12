// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/MyHUD.h"
#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "UI/WidgetController//OverlayWidgetController.h"
//#include "MyHUD.h"

// 返回OverlayWidgetController，OverlayWidgetController有PlayerController，PlayerState，ASC，AttributeSet等属性
UOverlayWidgetController* AMyHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (OverlayWidgetController == nullptr) {
		//"Outer"  可选。一个要设置为待创建对象的外部"UObject"
		//"Class"   可选。一个用于指定待创建对象类的"UClass"。
		// return 指向指定类的生成实例指针

		//获取蓝图中选择的Class
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		// 设置PlayerController，PlayerState，ASC，AttributeSet
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		OverlayWidgetController->BindCallbacksToDependencies();
		return OverlayWidgetController;
	}

	return OverlayWidgetController;
}
UAttributeMenuWidgetController* AMyHUD::GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams)
{
	if (AttributeMenuWidgetController == nullptr)
	{
		AttributeMenuWidgetController = NewObject<UAttributeMenuWidgetController>(this, AttributeMenuWidgetControllerClass);
		AttributeMenuWidgetController->SetWidgetControllerParams(WCParams);
		AttributeMenuWidgetController->BindCallbacksToDependencies();
	}
	return AttributeMenuWidgetController;
}

//初始化HUD界面，并绘制出界面
void AMyHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass,TEXT("OverlayWidgetClass 蓝图中未设置"));
	checkf(OverlayWidgetControllerClass, TEXT("OverlayWidgetControllerClass 蓝图中未设置"));
	checkf(AttributeMenuWidgetControllerClass, TEXT("AttributeMenuWidgetControllerClass 蓝图中未设置"));
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UUIUserWidget>(Widget);
	
	//获取PC, PS, ASC, AS参数
	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);

	OverlayWidget->SetWidgetController(WidgetController);
	WidgetController->BroadcastInitialValues();
	Widget->AddToViewport();
}

void AMyHUD::BeginPlay()
{
	Super::BeginPlay();


}
