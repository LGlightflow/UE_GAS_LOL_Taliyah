// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/Widget/UIUserWidget.h"
#include "MyHUD.generated.h"

/**
 * 显示静态界面，（不能像UI那样被点击与互动）
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

	// (蓝图中选择)显示UI的widget的类
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUIUserWidget> OverlayWidgetClass;

	UPROPERTY()
		TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

	// (蓝图中选择)DataTable,表中存放关于widget的message（例如捡到血瓶会有提示等）
	UPROPERTY(EditAnywhere)
		TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;

	UPROPERTY()
		TObjectPtr<UAttributeMenuWidgetController> AttributeMenuWidgetController;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UAttributeMenuWidgetController> AttributeMenuWidgetControllerClass;

protected:
	virtual void BeginPlay() override;
};
