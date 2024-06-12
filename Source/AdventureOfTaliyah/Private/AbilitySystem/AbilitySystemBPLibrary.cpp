// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AbilitySystemBPLibrary.h"
#include "Character/Player/MyPlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "UI/HUD/MyHUD.h"
#include "UI/WidgetController/UIWidgetController.h"
#include "MyAbilityTypes.h"
#include "Interaction/CombatInterface.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "MyGameplayTags.h"

bool UAbilitySystemBPLibrary::MakeWidgetControllerParams(const UObject* WorldContextObject, FWidgetControllerParams& OutWCParams, AMyHUD*& OutMyHUD)
{
	return false;
}

UOverlayWidgetController* UAbilitySystemBPLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{

	//FWidgetControllerParams WCParams;
	//AMyHUD* MyHUD = nullptr;
	//if (MakeWidgetControllerParams(WorldContextObject, WCParams, MyHUD))
	//{
	//	return MyHUD->GetOverlayWidgetController(WCParams);
	//}
	//return nullptr;
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0)) 
	{
		if (AMyHUD* MyHUD = Cast<AMyHUD>(PC->GetHUD()))
		{
			AMyPlayerState* PS = PC->GetPlayerState<AMyPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttrubuteSet();
			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
			return MyHUD->GetOverlayWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
	
}

UAttributeMenuWidgetController* UAbilitySystemBPLibrary::GetAttributeMenuWidgetController(const UObject* WorldContextObject)
{
	//FWidgetControllerParams WCParams;
	//AMyHUD* MyHUD = nullptr;
	//if (MakeWidgetControllerParams(WorldContextObject, WCParams, MyHUD))
	//{
	//	return MyHUD->GetAttributeMenuWidgetController(WCParams);
	//}
	//return nullptr;

	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (AMyHUD* MyHUD = Cast<AMyHUD>(PC->GetHUD()))
		{
			AMyPlayerState* PS = PC->GetPlayerState<AMyPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttrubuteSet();
			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
			return MyHUD->GetAttributeMenuWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}

bool UAbilitySystemBPLibrary::IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FMyGameplayEffectContext* MyEffectContext = static_cast<const FMyGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return MyEffectContext->IsCriticalHit();
	}
	return false;
}

//获取半径内的player
void UAbilitySystemBPLibrary::GetLivePlayersWithinRadius(const UObject* WorldContextObject, TArray<AActor*>& OutOverlappingActors, const TArray<AActor*>& ActorsToIgnore, float Radius, const FVector& SphereOrigin)
{
	FCollisionQueryParams SphereParams;
	SphereParams.AddIgnoredActors(ActorsToIgnore);

	if (const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		TArray<FOverlapResult> Overlaps;
		World->OverlapMultiByObjectType(Overlaps, SphereOrigin, FQuat::Identity, FCollisionObjectQueryParams(FCollisionObjectQueryParams::InitType::AllDynamicObjects), FCollisionShape::MakeSphere(Radius), SphereParams);
		for (FOverlapResult& Overlap : Overlaps)
		{
			if (Overlap.GetActor()->Implements<UCombatInterface>() && !ICombatInterface::Execute_IsDead(Overlap.GetActor()))
			{
				OutOverlappingActors.AddUnique(ICombatInterface::Execute_GetAvatar(Overlap.GetActor()));
			}
		}
	}
}



void UAbilitySystemBPLibrary::SetIsCriticalHit(FGameplayEffectContextHandle& EffectContextHandle, bool bInIsCriticalHit)
{
	if (FMyGameplayEffectContext* MyEffectContext = static_cast<FMyGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		MyEffectContext->SetIsCriticalHit(bInIsCriticalHit);
	}
}

//判断友方，用于关闭友伤等操作
bool UAbilitySystemBPLibrary::IsNotFriend(AActor* FirstActor, AActor* SecondActor)
{
	const bool bBothArePlayers = FirstActor->ActorHasTag(FName("Player")) && SecondActor->ActorHasTag(FName("Player"));
	const bool bBothAreEnemies = FirstActor->ActorHasTag(FName("Enemy")) && SecondActor->ActorHasTag(FName("Enemy"));
	const bool bFriends = bBothArePlayers || bBothAreEnemies;
	return !bFriends;
}

FGameplayEffectContextHandle UAbilitySystemBPLibrary::ApplyDamageEffect(const FDamageEffectParams& DamageEffectParams)
{
	const FMyGameplayTags& GameplayTags = FMyGameplayTags::Get();
	const AActor* SourceAvatarActor = DamageEffectParams.SourceAbilitySystemComponent->GetAvatarActor();

	FGameplayEffectContextHandle EffectContexthandle = DamageEffectParams.SourceAbilitySystemComponent->MakeEffectContext();
	EffectContexthandle.AddSourceObject(SourceAvatarActor);

	SetDebuffType(EffectContexthandle, DamageEffectParams.DebuffType);

	SetDeathImpulse(EffectContexthandle, DamageEffectParams.DeathImpulse);
	SetKnockbackForce(EffectContexthandle, DamageEffectParams.KnockbackForce);

	

	/*SetIsRadialDamage(EffectContexthandle, DamageEffectParams.bIsRadialDamage);
	SetRadialDamageInnerRadius(EffectContexthandle, DamageEffectParams.RadialDamageInnerRadius);
	SetRadialDamageOuterRadius(EffectContexthandle, DamageEffectParams.RadialDamageOuterRadius);
	SetRadialDamageOrigin(EffectContexthandle, DamageEffectParams.RadialDamageOrigin);*/

	const FGameplayEffectSpecHandle SpecHandle = DamageEffectParams.SourceAbilitySystemComponent->MakeOutgoingSpec(DamageEffectParams.DamageGameplayEffectClass, DamageEffectParams.AbilityLevel, EffectContexthandle);

	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, FMyGameplayTags::Get().AbilityPowerCoefficient, DamageEffectParams.AbilityPowerCoefficient);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, FMyGameplayTags::Get().AttackDamageCoefficient, DamageEffectParams.AttackDamageCoefficient);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, DamageEffectParams.DamageType, DamageEffectParams.BaseDamage);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.Debuff_Chance, DamageEffectParams.DebuffChance);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.Debuff_Damage, DamageEffectParams.DebuffDamage);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.Debuff_Duration, DamageEffectParams.DebuffDuration);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.Debuff_Frequency, DamageEffectParams.DebuffFrequency);

	DamageEffectParams.TargetAbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data);
	return EffectContexthandle;
}



//int32 UAbilitySystemBPLibrary::GetXPRewardForClassAndLevel(const UObject* WorldContextObject, ECharacterClass CharacterClass, int32 CharacterLevel)
//{
//	UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
//	if (CharacterClassInfo == nullptr) return 0;
//
//	const FCharacterClassDefaultInfo& Info = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);
//	const float XPReward = Info.XPReward.GetValueAtLevel(CharacterLevel);
//
//	return static_cast<int32>(XPReward);;
//}

void UAbilitySystemBPLibrary::SetDamageType(FGameplayEffectContextHandle& EffectContextHandle, const FGameplayTag& InDamageType)
{
	if (FMyGameplayEffectContext* MyEffectContext = static_cast<FMyGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		const TSharedPtr<FGameplayTag> DamageType = MakeShared<FGameplayTag>(InDamageType);
		MyEffectContext->SetDamageType(DamageType);
	}
}


void UAbilitySystemBPLibrary::SetDebuffType(FGameplayEffectContextHandle& EffectContextHandle, const FGameplayTag& InDebuffType)
{
	if (FMyGameplayEffectContext* MyEffectContext = static_cast<FMyGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		const TSharedPtr<FGameplayTag> DebuffType = MakeShared<FGameplayTag>(InDebuffType);
		MyEffectContext->SetDebuffType(DebuffType);
	}
}

void UAbilitySystemBPLibrary::SetIsSuccessfulDebuff(FGameplayEffectContextHandle& EffectContextHandle,
	bool bInSuccessfulDebuff)
{
	if (FMyGameplayEffectContext* MyEffectContext = static_cast<FMyGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		MyEffectContext->SetIsSuccessfulDebuff(bInSuccessfulDebuff);
	}
}

void UAbilitySystemBPLibrary::SetDebuffDamage(FGameplayEffectContextHandle& EffectContextHandle, float InDamage)
{
	if (FMyGameplayEffectContext* MyEffectContext = static_cast<FMyGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		MyEffectContext->SetDebuffDamage(InDamage);
	}
}



void UAbilitySystemBPLibrary::SetDebuffDuration(FGameplayEffectContextHandle& EffectContextHandle, float InDuration)
{
	if (FMyGameplayEffectContext* MyEffectContext = static_cast<FMyGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		MyEffectContext->SetDebuffDuration(InDuration);
	}
}

void UAbilitySystemBPLibrary::SetDebuffFrequency(FGameplayEffectContextHandle& EffectContextHandle, float InFrequency)
{
	if (FMyGameplayEffectContext* MyEffectContext = static_cast<FMyGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		MyEffectContext->SetDebuffFrequency(InFrequency);
	}
}

void UAbilitySystemBPLibrary::SetDeathImpulse(FGameplayEffectContextHandle& EffectContextHandle,
	const FVector& InImpulse)
{
	if (FMyGameplayEffectContext* MyEffectContext = static_cast<FMyGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		MyEffectContext->SetDeathImpulse(InImpulse);
	}
}

void UAbilitySystemBPLibrary::SetKnockbackForce(FGameplayEffectContextHandle& EffectContextHandle, const FVector& InForce)
{
	if (FMyGameplayEffectContext* MyEffectContext = static_cast<FMyGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		MyEffectContext->SetKnockbackForce(InForce);
	}
}

bool UAbilitySystemBPLibrary::IsSuccessfulDebuff(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FMyGameplayEffectContext* MyEffectContext = static_cast<const FMyGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return MyEffectContext->IsSuccessfulDebuff();
	}
	return false;
}

float UAbilitySystemBPLibrary::GetDebuffDamage(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FMyGameplayEffectContext* MyEffectContext = static_cast<const FMyGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return MyEffectContext->GetDebuffDamage();
	}
	return 0.f;
}

float UAbilitySystemBPLibrary::GetDebuffDuration(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FMyGameplayEffectContext* MyEffectContext = static_cast<const FMyGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return MyEffectContext->GetDebuffDuration();
	}
	return 0.f;
}

float UAbilitySystemBPLibrary::GetDebuffFrequency(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FMyGameplayEffectContext* MyEffectContext = static_cast<const FMyGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return MyEffectContext->GetDebuffFrequency();
	}
	return 0.f;
}


FGameplayTag UAbilitySystemBPLibrary::GetDamageType(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FMyGameplayEffectContext* MyEffectContext = static_cast<const FMyGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		if (MyEffectContext->GetDamageType().IsValid())
		{
			return *MyEffectContext->GetDamageType();
		}
	}
	return FGameplayTag();
}

FGameplayTag UAbilitySystemBPLibrary::GetDebuffType(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FMyGameplayEffectContext* MyEffectContext = static_cast<const FMyGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		if (MyEffectContext->GetDebuffType().IsValid())
		{
			return *MyEffectContext->GetDebuffType();
		}
	}
	return FGameplayTag();
}

FVector UAbilitySystemBPLibrary::GetKnockbackForce(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FMyGameplayEffectContext* MyEffectContext = static_cast<const FMyGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return MyEffectContext->GetKnockbackForce();
	}
	return FVector::ZeroVector;
}
