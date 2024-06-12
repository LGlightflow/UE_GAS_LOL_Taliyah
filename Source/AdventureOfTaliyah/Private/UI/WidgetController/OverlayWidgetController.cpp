// Fill out your copyright notice in the Description page of Project Settings.
#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/MyAttributeSet.h"
#include "AbilitySystem/MyAbilitySystemComponent.h"
#include "AbilitySystem/Data/LevelUpInfo.h"




//��widget �㲥����������ֵ����ֵ
void UOverlayWidgetController::BroadcastInitialValues()
{

	//const UMyAttributeSet* MyAttributeSet = CastChecked<UMyAttributeSet>(AttributeSet);
	// һ���㲥��ֵ�����仯���ͻᴥ����Ӧ��ͼ����Ѫ��progressBar���Ķ�Ӧ�¼��磨OnHealthChanged��
	//OnHealthChanged.Broadcast(MyAttributeSet->GetHealth());
	//OnMaxHealthChanged.Broadcast(MyAttributeSet->GetMaxHealth());
	//OnManaChanged.Broadcast(MyAttributeSet->GetMana());
	//OnMaxManaChanged.Broadcast(MyAttributeSet->GetMaxMana());
	OnHealthChanged.Broadcast(GetMyAS()->GetHealth());
	OnMaxHealthChanged.Broadcast(GetMyAS()->GetMaxHealth());
	OnManaChanged.Broadcast(GetMyAS()->GetMana());
	OnMaxManaChanged.Broadcast(GetMyAS()->GetMaxMana());
}

// �󶨻ص�
//  "Broadcast()" ����ί�й㲥�����а󶨵Ķ��󣬵������ѹ��ڵĶ�����⡣
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
			[this /*������࣬Ϊ�˻�ȡGetDataTableRowByTag����*/](const FGameplayTagContainer& AssetTags) {
				for (const FGameplayTag& Tag : AssetTags)
				{
					// A.1ƥ��A����True����Aƥ��A.1����false ���磺"Message.HealthBottle".MathcerTag("Message")����true
					FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
					if (Tag.MatchesTag(MessageTag))
					{
						//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("GETag:%s"), *Tag.ToString()));
						//ע��Ҫ��OverlayWidgetController��BP������MessageWidgetRowDelegate��ѡ���Ӧdatatable
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
	//�������������Ա �޸� MyAbilitySystemComponentΪMyASC
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
	checkf(LevelUpInfo, TEXT("��Ҫ��BP_PLayerState����levelinfo"));

	const int32 Level = LevelUpInfo->FindLevelForXP(NewXP);
	const int32 MaxLevel = LevelUpInfo->LevelUpInformation.Num();

	if (Level <= MaxLevel && Level > 0)
	{
		const int32 LevelUpRequirement = LevelUpInfo->LevelUpInformation[Level].LevelUpRequirement; //��ǰ�ȼ�������Ҫ�����о���
		const int32 PreviousLevelUpRequirement = LevelUpInfo->LevelUpInformation[Level - 1].LevelUpRequirement;//��һ���ȼ�������Ҫ�����о���

		const int32 DeltaLevelRequirement = LevelUpRequirement - PreviousLevelUpRequirement;
		const int32 XPForThisLevel = NewXP - PreviousLevelUpRequirement;

		const float XPBarPercent = static_cast<float>(XPForThisLevel) / static_cast<float>(DeltaLevelRequirement);

		OnXPPercentChangedDelegate.Broadcast(XPBarPercent);
	}
}

