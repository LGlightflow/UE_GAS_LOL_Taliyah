// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
/**
 *  类的作用:定义（设置）project setting中的FGamePlayTag,并使Tags能在BP中使用
	
 * 
 */
struct  FMyGameplayTags
{

public:
	static const FMyGameplayTags& Get() { return GameplayTags; }
	static void InitializeNativeGameplayTags();

	 /*属性tags*/
	FGameplayTag Attributes_Primary_MaxHealth;
	FGameplayTag Attributes_Primary_MaxMana;

	FGameplayTag Attributes_Primary_AttackDamage;
	FGameplayTag Attributes_Primary_AbilityPower;
	FGameplayTag Attributes_Primary_Armor;
	FGameplayTag Attributes_Primary_MagicResistance;
	FGameplayTag Attributes_Primary_AttackSpeed;
	FGameplayTag Attributes_Primary_CriticalHitChance;

	FGameplayTag Attributes_Secondary_HealthRegeneration;
	FGameplayTag Attributes_Secondary_ManaRegeneration;
	
	FGameplayTag Attributes_Vital_Health;
	FGameplayTag Attributes_Vital_Mana;

	FGameplayTag Attributes_Meta_IncomingXP;

	/*input tags*/
	FGameplayTag InputTag_1;
	FGameplayTag InputTag_2;
	FGameplayTag InputTag_3;
	FGameplayTag InputTag_4;
	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_Shift;
	FGameplayTag InputTag_Q;
	FGameplayTag InputTag_E;
	FGameplayTag InputTag_R;

	FGameplayTag Player_Block_InputPressed;
	FGameplayTag Player_Block_InputHeld;
	FGameplayTag Player_Block_InputReleased;

	/*伤害类型tags*/
	//FGameplayTag BasicDamage;
	TArray<FGameplayTag> DamageTypes;

	FGameplayTag PhysicalDamage;
	FGameplayTag MagicDamage;
	FGameplayTag TrueDamage;

	/*ExecCalc的伤害系数*/
	FGameplayTag AttackDamageCoefficient;
	FGameplayTag AbilityPowerCoefficient;


	FGameplayTag Debuff_Burn;
	FGameplayTag Debuff_Stun;

	TArray<FGameplayTag> DebuffTypes;

	FGameplayTag Debuff_Chance;
	FGameplayTag Debuff_Damage;
	FGameplayTag Debuff_Duration;
	FGameplayTag Debuff_Frequency;

	FGameplayTag Abilities_MeleeAttack;
	FGameplayTag Abilities_RangedAttack;
	FGameplayTag Abilities_1;
	FGameplayTag Abilities_2;
	FGameplayTag Abilities_3;
	FGameplayTag Abilities_4;
	FGameplayTag Abilities_TargetConfirm;
	FGameplayTag Effects_HitReact;


	FGameplayTag Cooldown_1;
	FGameplayTag Cooldown_2;
	FGameplayTag Cooldown_3;
	FGameplayTag Cooldown_4;
	// 蒙太奇
	FGameplayTag Montage_Attack_1;
	FGameplayTag Montage_Attack_2;
	FGameplayTag Montage_Attack_3;
	FGameplayTag Montage_Attack_4;

	FGameplayTag CombatSocket_Weapon;
	FGameplayTag CombatSocket_RightHand;
	FGameplayTag CombatSocket_LeftHand;
	FGameplayTag CombatSocket_Tail;
private:
	static FMyGameplayTags GameplayTags;

};
