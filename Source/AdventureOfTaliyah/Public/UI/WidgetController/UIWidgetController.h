// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/MyAbilitySystemComponent.h"
#include "Character/Player/MyPlayerController.h"
#include "Character/Player/MyPlayerState.h"
#include "AbilitySystem/MyAttributeSet.h"
#include "UObject/NoExportTypes.h"

#include "UIWidgetController.generated.h"

/**
 * 设置四个模块（PC,PS,ASC,AS）的class，传给其他类 如MyHUD
 * 
 * 
 */

class AMyPlayerController;
class AMyPlayerState;
class UAbilitySystemComponent;
class UAttributeSet;


// 存储PC,PS,ASC,AS的指针
USTRUCT(BlueprintType)
struct FWidgetControllerParams {

	GENERATED_BODY()

	FWidgetControllerParams() {}
	FWidgetControllerParams(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS) 
		:PlayerController(PC),PlayerState(PS), AbilitySystemComponent(ASC), AttributeSet(AS){}
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<APlayerController> PlayerController = nullptr;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<APlayerState> PlayerState = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAttributeSet> AttributeSet = nullptr;
};


UCLASS()
class ADVENTUREOFTALIYAH_API UUIWidgetController : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetControllerParams(const FWidgetControllerParams WCParams);

	UFUNCTION(BlueprintCallable)
	virtual void BroadcastInitialValues();
	virtual void BindCallbacksToDependencies();

protected:
	UPROPERTY(BlueprintReadOnly,Category="WidgetController")
		TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
		TObjectPtr<APlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
		TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
		TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
		TObjectPtr<AMyPlayerController> MyPlayerController;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
		TObjectPtr<AMyPlayerState> MyPlayerState;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
		TObjectPtr<UMyAbilitySystemComponent> MyAbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
		TObjectPtr<UMyAttributeSet> MyAttributeSet;


	AMyPlayerController* GetMyPC();
	AMyPlayerState* GetMyPS();
	UMyAbilitySystemComponent* GetMyASC();
	UMyAttributeSet* GetMyAS();
};
