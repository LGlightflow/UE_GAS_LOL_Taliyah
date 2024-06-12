// Fill out your copyright notice in the Description page of Project Settings.
#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/MyAttributeSet.h"
#include "AbilitySystem/MyAbilitySystemComponent.h"
#include "AbilitySystem/Data/LevelUpInfo.h"




//向widget 广播生命，法力值等数值
void UOverlayWidgetController::BroadcastInitialValues()
{

	//const UMyAttributeSet* MyAttributeSet = CastChecked<UMyAttributeSet>(AttributeSet);
	// 一旦广播的值发生变化，就会触发对应蓝图（如血条progressBar）的对应事件如（OnHealthChanged）
	//OnHealthChanged.Broadcast(MyAttributeSet->GetHealth());
	//OnMaxHealthChanged.Broadcast(MyAttributeSet->GetMaxHealth());
	//OnManaChanged.Broadcast(MyAttributeSet->GetMana());
	//OnMaxManaChanged.Broadcast(MyAttributeSet->GetMaxMana());
	OnHealthChanged.Broadcast(GetMyAS()->GetHealth());
	OnMaxHealthChanged.Broadcast(GetMyAS()->GetMaxHealth());
	OnManaChanged.Broadcast(GetMyAS()->GetMana());
	OnMaxManaChanged.Broadcast(GetMyAS()->GetMaxMana());
}

// 绑定回调
//  "Broadcast()" 将该委托广播给所有绑定的对象，但可能已过期的对象除外。
void UOverlayWidgetController::BindCallbacksToDependencies()
{
	//AMyPlayerState* MyPlayerState = CastChecked<AMyPlayerState>(PlayerState);
	//MyPlayerState->OnXPChangedDelegate.AddUObject(this, &UOverlayWidgetController::OnXPChanged);
	GetMyPS()->OnXPChangedDelegate.AddUObject(this, &UOverlayWidgetController::OnXPChanged);
	GetMyPS()->OnLevelChangedDelegate.AddLambda(
		[this](int32 NewLevel, bool bLevelUp)
		{
			OnPlayerLevelChangedDelegate.Broadcast(NewLevel, bLevelUp);
		}
	);
	const UMyAttributeSet* MyAtrributeSet = CastChecked<UMyAttributeSet>(AttributeSet);
	

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MyAtrributeSet->GetHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnHealthChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MyAtrributeSet->GetMaxHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxHealthChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MyAtrributeSet->GetManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnManaChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MyAtrributeSet->GetMaxManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxManaChanged.Broadcast(Data.NewValue);
		}
	);



	if (GetMyASC())
	{
		if (GetMyASC()->bStartupAbilitiesGiven)
		{
			OnInitializeStartupAbilities(GetMyASC());
		}
		else
		{
			GetMyASC()->AbilitiesGivenDelegate.AddUObject(this, &UOverlayWidgetController::OnInitializeStartupAbilities);
		}


		GetMyASC()->EffectAssetTags.AddLambda(
			[this /*捕获此类，为了获取GetDataTableRowByTag函数*/](const FGameplayTagContainer& AssetTags) {
				for (const FGameplayTag& Tag : AssetTags)
				{
					// A.1匹配A返回True，但A匹配A.1返回false 例如："Message.HealthBottle".MathcerTag("Message")返回true
					FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
					if (Tag.MatchesTag(MessageTag))
					{
						//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("GETag:%s"), *Tag.ToString()));
						//注：要在OverlayWidgetController的BP中配置MessageWidgetRowDelegate，选择对应datatable
						check(MessageWidgetDataTable);
						FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
						MessageWidgetRowDelegate.Broadcast(*Row);
					}

				}
			}
		);
	}


}


void UOverlayWidgetController::OnInitializeStartupAbilities(UMyAbilitySystemComponent* MyASC)
{
	//声明隐藏了类成员 修改 MyAbilitySystemComponent为MyASC
	if (!MyASC->bStartupAbilitiesGiven) return;
	FForEachAbility BroadcastDelegate;
	BroadcastDelegate.BindLambda([this, MyASC](const FGameplayAbilitySpec& AbilitySpec)
		{
			FMyAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(MyASC->GetAbilityTagFromSpec(AbilitySpec));
			Info.InputTag = MyASC->GetInputTagFromSpec(AbilitySpec);
			AbilityInfoDelegate.Broadcast(Info);
		}
	);
	MyASC->ForEachAbility(BroadcastDelegate);
}

void UOverlayWidgetController::OnXPChanged(int32 NewXP)
{
	const ULevelUpInfo* LevelUpInfo = GetMyPS()->LevelUpInfo;
	checkf(LevelUpInfo, TEXT("需要在BP_PLayerState配置levelinfo"));

	const int32 Level = LevelUpInfo->FindLevelForXP(NewXP);
	const int32 MaxLevel = LevelUpInfo->LevelUpInformation.Num();

	if (Level <= MaxLevel && Level > 0)
	{
		const int32 LevelUpRequirement = LevelUpInfo->LevelUpInformation[Level].LevelUpRequirement; //当前等级升级需要的所有经验
		const int32 PreviousLevelUpRequirement = LevelUpInfo->LevelUpInformation[Level - 1].LevelUpRequirement;//上一个等级升级需要的所有经验

		const int32 DeltaLevelRequirement = LevelUpRequirement - PreviousLevelUpRequirement;
		const int32 XPForThisLevel = NewXP - PreviousLevelUpRequirement;

		const float XPBarPercent = static_cast<float>(XPForThisLevel) / static_cast<float>(DeltaLevelRequirement);

		OnXPPercentChangedDelegate.Broadcast(XPBarPercent);
	}
}

