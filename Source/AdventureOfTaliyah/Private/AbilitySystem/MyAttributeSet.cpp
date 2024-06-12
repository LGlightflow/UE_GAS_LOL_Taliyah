// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/MyAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "MyGameplayTags.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Character/Player/MyPlayerController.h"
#include "AbilitySystem/AbilitySystemBPLibrary.h"
#include "Character/BaseCharacter.h"
#include "Interaction/CombatInterface.h"
#include "Interaction/PlayerInterface.h"
#include "MyAbilityTypes.h"

// 初始化attribute的值有3种方法：
// 1.在MyAttributeSet的构造函数进行设置:InitXXX(value)
// 2.通过BaseCharacter或其子类的BP中的DefaultAttributes,选择DataTable
// 3.通过BaseCharacter中定义的InitializeDefaultAttributes()函数进行设置，此函数通过BPGE进行属性的设置
UMyAttributeSet::UMyAttributeSet()
{
	//InitHealth(75.f);
	//InitMaxHealth(100.f);
	//InitMana(80.f);
	//InitMaxMana(100.f);
	const FMyGameplayTags& GameplayTags = FMyGameplayTags::Get();
	

	//FAttributeSignature AbilityPowerDelegate;
	//AbilityPowerDelegate.BindStatic(GetAbilityPowerAttribute);
	//TagsToAttributes.Add(GameplayTags.Attributes_Primary_AbilityPower, AbilityPowerDelegate);

	//FAttributeSignature ArmorDelegate;
	//ArmorDelegate.BindStatic(GetArmorAttribute);
	//TagsToAttributes.Add(GameplayTags.Attributes_Primary_Armor, ArmorDelegate);

	//FAttributeSignature AttackDamageDelegate;
	//AttackDamageDelegate.BindStatic(GetAttackDamageAttribute);
	//TagsToAttributes.Add(GameplayTags.Attributes_Primary_AttackDamage, AttackDamageDelegate);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_AbilityPower, GetAbilityPowerAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Armor, GetArmorAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_MagicResistance, GetMagicResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_AttackDamage, GetAttackDamageAttribute);

	TagsToAttributes.Add(GameplayTags.Attributes_Primary_MaxHealth, GetMaxHealthAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_MaxMana, GetMaxManaAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_AttackSpeed, GetAttackSpeedAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_CriticalHitChance, GetCriticalHitChanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_HealthRegeneration, GetHealthRegenerationAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_ManaRegeneration, GetManaRegenerationAttribute);
}


void UMyAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const 
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet, AttackDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet, AbilityPower, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet, MagicResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet, AttackSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet, CriticalHitChance, COND_None, REPNOTIFY_Always);

	/**/
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet, HealthRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet, ManaRegeneration, COND_None, REPNOTIFY_Always);

	/**/
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet, Mana, COND_None, REPNOTIFY_Always);
}

// 限定生命值不会超过最大生命值（法力值也一样）
void UMyAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{

	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{	
		//将一个数字限定在另外两个数字之间（包含）
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
		
	}
	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
	}


}
// 提交GE的处理
// 重载了AttributeSet 的 PostGameplayEffectExecute函数
/**
 *	Called just before a GameplayEffect is executed to modify the base value of an attribute. No more changes can be made.
 *	Note this is only called during an 'execute'. E.g., a modification to the 'base value' of an attribute. It is not called during an application of a GameplayEffect, such as a 5 ssecond +10 movement speed buff.
 */
void UMyAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectProperties Props;
	SetEffectProperties(Data, Props);

	if (Props.TargetCharacter->Implements<UCombatInterface>() && ICombatInterface::Execute_IsDead(Props.TargetCharacter)) return;
	//// EvaluatedData : The 'flat'/computed data to be applied to the target
	////Data.EvaluatedData.Magnitude 可用于获取attribute的属性的变化幅度
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, FString::Printf(TEXT("Name:%s,Health:%f"), *Props.TargetAvatarActor->GetName(), GetHealth() ));
	}
	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
	}

	if (Data.EvaluatedData.Attribute == GetIncomingDamageAttribute())
	{
		const float LocalIncomingDamage = GetIncomingDamage();
		SetIncomingDamage(0.f);

		if (LocalIncomingDamage > 0)
		{
			const float NewHealth = GetHealth() - LocalIncomingDamage;
			SetHealth(FMath::Clamp(NewHealth, 0.f, GetMaxHealth()));
			const bool bFatal = NewHealth <= 0.f;
			if (!bFatal)
			{	

				// 激活HitReact(受击) 的 GA
				FGameplayTagContainer TagContainer;
				TagContainer.AddTag(FMyGameplayTags::Get().Effects_HitReact);
				Props.TargetASC->TryActivateAbilitiesByTag(TagContainer);

				const FVector& KnockbackForce = UAbilitySystemBPLibrary::GetKnockbackForce(Props.EffectContextHandle);
				if (!KnockbackForce.IsNearlyZero(1.f))
				{
					Props.TargetCharacter->LaunchCharacter(KnockbackForce, true, true);
				}
			}
			else
			{
				ICombatInterface* CombatInterface = Cast<ICombatInterface>(Props.TargetAvatarActor);
				if (CombatInterface)
				{
					CombatInterface->Die();
				}
				SendXPEvent(Props);
			}
			const bool bCriticalHit = UAbilitySystemBPLibrary::IsCriticalHit(Props.EffectContextHandle);

			ShowFloatingText(Props, LocalIncomingDamage,bCriticalHit);
			if (UAbilitySystemBPLibrary::IsSuccessfulDebuff(Props.EffectContextHandle))
			{
				const FMyGameplayTags& GameplayTags = FMyGameplayTags::Get();
				FGameplayEffectContextHandle EffectContext = Props.SourceASC->MakeEffectContext();
				EffectContext.AddSourceObject(Props.SourceAvatarActor);

				const FGameplayTag DebuffType = UAbilitySystemBPLibrary::GetDebuffType(Props.EffectContextHandle); //测试用
				const float DebuffDamage = UAbilitySystemBPLibrary::GetDebuffDamage(Props.EffectContextHandle);
				const float DebuffDuration = UAbilitySystemBPLibrary::GetDebuffDuration(Props.EffectContextHandle);
				const float DebuffFrequency = UAbilitySystemBPLibrary::GetDebuffFrequency(Props.EffectContextHandle);

				//FString DebuffName = FString::Printf(TEXT("DynamicDebuff_%s"), *DamageType.ToString());
				FString DebuffName = FString::Printf(TEXT("%s"), *DebuffType.ToString());
				UGameplayEffect* Effect = NewObject<UGameplayEffect>(GetTransientPackage(), FName(DebuffName));

				//设置Effect的属性
				Effect->DurationPolicy = EGameplayEffectDurationType::HasDuration;
				Effect->Period = DebuffFrequency;
				Effect->DurationMagnitude = FScalableFloat(DebuffDuration);

				const FGameplayTag DebuffTag = DebuffType;
				Effect->InheritableOwnedTagsContainer.AddTag(DebuffTag);

				const FMyGameplayTags& AllTags = FMyGameplayTags::Get();
				if (DebuffTag.MatchesTagExact(FMyGameplayTags::Get().Debuff_Stun))
				{
					Effect->InheritableOwnedTagsContainer.AddTag(AllTags.Player_Block_InputHeld);
					Effect->InheritableOwnedTagsContainer.AddTag(AllTags.Player_Block_InputPressed);
					Effect->InheritableOwnedTagsContainer.AddTag(AllTags.Player_Block_InputReleased);
				}

				Effect->StackingType = EGameplayEffectStackingType::AggregateBySource;
				Effect->StackLimitCount = 1;

				const int32 Index = Effect->Modifiers.Num();
				Effect->Modifiers.Add(FGameplayModifierInfo());
				FGameplayModifierInfo& ModifierInfo = Effect->Modifiers[Index];

				ModifierInfo.ModifierMagnitude = FScalableFloat(DebuffDamage);
				ModifierInfo.ModifierOp = EGameplayModOp::Additive;
				ModifierInfo.Attribute = UMyAttributeSet::GetIncomingDamageAttribute();

				if (FGameplayEffectSpec* MutableSpec = new FGameplayEffectSpec(Effect, EffectContext, 1.f))
				{
					FMyGameplayEffectContext* MyContext = static_cast<FMyGameplayEffectContext*>(MutableSpec->GetContext().Get());
					TSharedPtr<FGameplayTag> DebuffDamageType = MakeShareable(new FGameplayTag(DebuffType));
					MyContext->SetDamageType(DebuffDamageType);

					Props.TargetASC->ApplyGameplayEffectSpecToSelf(*MutableSpec);
				}
			}
		}
	}

	if (Data.EvaluatedData.Attribute == GetIncomingXPAttribute())
	{
		const float LocalIncomingXP = GetIncomingXP();
		SetIncomingXP(0.f);
		// UE_LOG(LogTemp,Log,TEXT("XP:%f"), GetIncomingXP());
		if (Props.SourceCharacter->Implements<UPlayerInterface>() && Props.SourceCharacter->Implements<UCombatInterface>())
		{
			// ICombatInterface 有一个奇怪的bug导致此函数不生效
			// 值得一提的是，在Enemy上的实现正常，在PlayerCharacter下的TaliyahCharacter子类没有调用相应的重载
			//const int32 CurrentLevel = ICombatInterface::Execute_GetPlayerLevel(Props.SourceCharacter);
			const int32 CurrentLevel = IPlayerInterface::Execute_GetPlayerLevelFromPlayerInterface(Props.SourceCharacter);
			const int32 CurrentXP = IPlayerInterface::Execute_GetXP(Props.SourceCharacter);

			const int32 NewLevel = IPlayerInterface::Execute_FindLevelForXP(Props.SourceCharacter, CurrentXP + LocalIncomingXP);
			//新等级与当前等级的差值（升了多少级）
			const int32 NumLevelUps = NewLevel - CurrentLevel;

			if (NumLevelUps > 0)
			{
				IPlayerInterface::Execute_AddToPlayerLevel(Props.SourceCharacter, NumLevelUps);

				int32 AttributePointsReward = 0;
				int32 SpellPointsReward = 0;

				//for (int32 i = 0; i < NumLevelUps; ++i)
				//{
				//	SpellPointsReward += IPlayerInterface::Execute_GetSpellPointsReward(Props.SourceCharacter, CurrentLevel + i);
				//	AttributePointsReward += IPlayerInterface::Execute_GetAttributePointsReward(Props.SourceCharacter, CurrentLevel + i);
				//}

				//IPlayerInterface::Execute_AddToAttributePoints(Props.SourceCharacter, AttributePointsReward);
				//IPlayerInterface::Execute_AddToSpellPoints(Props.SourceCharacter, SpellPointsReward);

				//bTopOffHealth = true;
				//bTopOffMana = true;

				IPlayerInterface::Execute_LevelUp(Props.SourceCharacter);
				IPlayerInterface::Execute_AddToLevelUpAttributesReward(Props.SourceCharacter, NewLevel);
			}


			IPlayerInterface::Execute_AddToXP(Props.SourceCharacter, LocalIncomingXP);
		}
		
		//HandleIncomingXP(Props);
	}
}

void UMyAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
}

// 设置FEffectProperties的内容
void UMyAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const
{
	// Source:Effect的发起者;
	Props.EffectContextHandle = Data.EffectSpec.GetContext();
	Props.SourceASC = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	if (IsValid(Props.SourceASC) && Props.SourceASC->AbilityActorInfo.IsValid() && Props.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.SourceAvatarActor = Props.SourceASC->AbilityActorInfo->AvatarActor.Get();
		Props.SourceController = Props.SourceASC->AbilityActorInfo->PlayerController.Get();
		//设置SourceController
		if (Props.SourceController == nullptr && Props.SourceAvatarActor != nullptr)
		{
			if (const APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
			{
				Props.SourceController = Pawn->GetController();
			}
		}
		//设置SourceCharacter
		if (Props.SourceController)
		{
			Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
		}
	}
	//设置TargetAvatarActor，TargetController，TargetCharacter，TargetASC
	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);
		Props.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);
	}
}

void UMyAttributeSet::ShowFloatingText(const FEffectProperties& Props, float Damage, bool bCriticalHit) const
{
	if (Props.SourceCharacter != Props.TargetCharacter)
	{
		if (AMyPlayerController* PC = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(Props.SourceCharacter, 0)))
		{
			PC->ShowDamageNumber(Damage, Props.TargetCharacter,bCriticalHit);
			return;
		}

		if (AMyPlayerController* PC = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(Props.TargetCharacter, 0)))
		{
			PC->ShowDamageNumber(Damage, Props.TargetCharacter, bCriticalHit);
		}
	}
}

// 杀死敌人后获取到经验值，将此经验值交由蓝图处理
void UMyAttributeSet::SendXPEvent(const FEffectProperties& Props)
{
	if (Props.TargetCharacter->Implements<UCombatInterface>())
	{
		const int32 TargetLevel = ICombatInterface::Execute_GetPlayerLevel(Props.TargetCharacter);
		
		// 获取对应BaseCharacter(或其子类)的经验值
		// 按照Actor获取经验如何处理？
		int32 XPReward = 0;
		if (ABaseCharacter* TargetBaseCharacter = Cast<ABaseCharacter>(Props.TargetCharacter))
		{
			XPReward = TargetBaseCharacter->XPReward.GetValueAtLevel(TargetLevel);
		}else{
			XPReward = 0;
		}

		// 给Payload赋值
		const FMyGameplayTags& GameplayTags = FMyGameplayTags::Get();
		FGameplayEventData Payload;
		Payload.EventTag = GameplayTags.Attributes_Meta_IncomingXP;
		Payload.EventMagnitude = XPReward;
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Props.SourceCharacter, GameplayTags.Attributes_Meta_IncomingXP, Payload);
	}
}


void UMyAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet, Health, OldHealth);
}

void UMyAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet, MaxHealth, OldMaxHealth);
}

void UMyAttributeSet::OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet, HealthRegeneration, OldHealthRegeneration);
}

void UMyAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet, Mana, OldMana);
}

void UMyAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet, MaxMana, OldMaxMana);
}

void UMyAttributeSet::OnRep_AttackSpeed(const FGameplayAttributeData& OldAttackSpeed) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet, AttackSpeed, OldAttackSpeed);
}

void UMyAttributeSet::OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet, CriticalHitChance, OldCriticalHitChance);
}

//void UMyAttributeSet::OnRep_MoveSpeed(const FGameplayAttributeData& OldMoveSpeed) const
//{
//	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet, MoveSpeed, OldMoveSpeed);
//}

void UMyAttributeSet::OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet, ManaRegeneration, OldManaRegeneration);
}

void UMyAttributeSet::OnRep_AttackDamage(const FGameplayAttributeData& OldAttackDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet, AttackDamage, OldAttackDamage);
}

void UMyAttributeSet::OnRep_AbilityPower(const FGameplayAttributeData& OldAbilityPower) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet, AbilityPower, OldAbilityPower);
}

void UMyAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet, Armor, OldArmor);
}

void UMyAttributeSet::OnRep_MagicResistance(const FGameplayAttributeData& OldMagicResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet, MagicResistance, OldMagicResistance);
}


