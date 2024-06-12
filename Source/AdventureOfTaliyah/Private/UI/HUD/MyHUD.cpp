// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/MyHUD.h"
#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "UI/WidgetController//OverlayWidgetController.h"
//#include "MyHUD.h"

// ����OverlayWidgetController��OverlayWidgetController��PlayerController��PlayerState��ASC��AttributeSet������
UOverlayWidgetController* AMyHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (OverlayWidgetController == nullptr) {
		//"Outer"  ��ѡ��һ��Ҫ����Ϊ������������ⲿ"UObject"
		//"Class"   ��ѡ��һ������ָ���������������"UClass"��
		// return ָ��ָ���������ʵ��ָ��

		//��ȡ��ͼ��ѡ���Class
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		// ����PlayerController��PlayerState��ASC��AttributeSet
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

//��ʼ��HUD���棬�����Ƴ�����
void AMyHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass,TEXT("OverlayWidgetClass ��ͼ��δ����"));
	checkf(OverlayWidgetControllerClass, TEXT("OverlayWidgetControllerClass ��ͼ��δ����"));
	checkf(AttributeMenuWidgetControllerClass, TEXT("AttributeMenuWidgetControllerClass ��ͼ��δ����"));
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UUIUserWidget>(Widget);
	
	//��ȡPC, PS, ASC, AS����
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
