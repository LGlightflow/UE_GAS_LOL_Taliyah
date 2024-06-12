// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/Widget/UIUserWidget.h"
#include "MyHUD.generated.h"

/**
 * ��ʾ��̬���棬��������UI����������뻥����
 */
class UAttributeMenuWidgetController;
class UOverlayWidgetController;
class UUIUserWidget;
class UAbilitySystemComponent;
class UAttributeSet;
struct FWidgetControllerParams;
UCLASS()
class ADVENTUREOFTALIYAH_API AMyHUD : public AHUD
{
	GENERATED_BODY()
	

public:


	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);
	UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams);


	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);
private:
	UPROPERTY()
		TObjectPtr<UUIUserWidget> OverlayWidget;

	// (��ͼ��ѡ��)��ʾUI��widget����
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUIUserWidget> OverlayWidgetClass;

	UPROPERTY()
		TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

	// (��ͼ��ѡ��)DataTable,���д�Ź���widget��message�������Ѫƿ������ʾ�ȣ�
	UPROPERTY(EditAnywhere)
		TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;

	UPROPERTY()
		TObjectPtr<UAttributeMenuWidgetController> AttributeMenuWidgetController;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UAttributeMenuWidgetController> AttributeMenuWidgetControllerClass;

protected:
	virtual void BeginPlay() override;
};