// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystem/Data/LevelUpInfo.h"
#include "MyPlayerState.generated.h"

/**
 * 存储玩家相关信息（score、health，mana等）
 * 在对应character类的InitAbilityActorInfo方法中被GetPlayerState()获取
 * 在WidgetController的bp中被选择
 */

DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerStatChanged, int32 /*StatValue*/)
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnLevelChanged, int32 /*StatValue*/, bool /*bLevelUp*/)

UCLASS()
class ADVENTUREOFTALIYAH_API AMyPlayerState : public APlayerState,public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	AMyPlayerState();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttrubuteSet() const { return AttributeSet; }

	UPROPERTY(EditDefaultsOnly)
		TObjectPtr<ULevelUpInfo> LevelUpInfo;

	FOnPlayerStatChanged OnXPChangedDelegate;
	FOnLevelChanged OnLevelChangedDelegate;

	FORCEINLINE int32 GetPlayerLevel() const { return Level; }
	FORCEINLINE int32 GetXP() const { return XP; }


	void AddToXP(int32 InXP);
	void AddToLevel(int32 InLevel);

	void SetXP(int32 InXP);
	void SetLevel(int32 InLevel);
protected:
	UPROPERTY(VisibleAnywhere)
		TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere)
		UAttributeSet* AttributeSet;

private: 
	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_Level)
		int32 Level = 1;

	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_XP)
		int32 XP = 0;


	UFUNCTION()
		void OnRep_Level(int32 OldLevel);

	UFUNCTION()
		void OnRep_XP(int32 OldXP);
};
