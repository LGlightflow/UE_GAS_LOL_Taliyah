// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameplayTags.h"
#include "GameplayTagsManager.h"

FMyGameplayTags FMyGameplayTags::GameplayTags;

void FMyGameplayTags::InitializeNativeGameplayTags() 
{
	/*
		一级属性
	*/
	GameplayTags.Attributes_Primary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.MaxHealth"),
		FString("最大生命值")
	);

	GameplayTags.Attributes_Primary_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.MaxMana"),
		FString("最大法力值")
	);

	GameplayTags.Attributes_Primary_AttackDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.AttackDamage"),
		FString("攻击力")
	);

	GameplayTags.Attributes_Primary_AbilityPower = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.AbilityPower"),
		FString("法术强度")
	);

	GameplayTags.Attributes_Primary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Armor"),
		FString("护甲")
	);

	GameplayTags.Attributes_Primary_MagicResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.MagicResistance"),
		FString("魔法抵抗")
	);

	GameplayTags.Attributes_Primary_AttackSpeed = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.AttackSpeed"),
		FString("攻击速度")
	);

	GameplayTags.Attributes_Primary_CriticalHitChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.CriticalHitChance"),
		FString("暴击率")
	);

	/*
		二级属性
	*/

	GameplayTags.Attributes_Secondary_HealthRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.HealthRegeneration"),
		FString("")
	);

	GameplayTags.Attributes_Secondary_ManaRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.ManaRegeneration"),
		FString("")
	);
	
	/*
	* 元属性
	*/
	GameplayTags.Attributes_Meta_IncomingXP = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Meta.IncomingXP"),
		FString("")
	);

	/*input tags*/
	GameplayTags.InputTag_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.1"),
		FString("1的inputtag")
	);
	GameplayTags.InputTag_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.2"),
		FString("2的inputtag")
	);

	GameplayTags.InputTag_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.3"),
		FString("3的inputtag")
	);
	GameplayTags.InputTag_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.4"),
		FString("4的inputtag")
	);
	GameplayTags.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.LMB"),
		FString("鼠标左键的inputtag")
	);

	GameplayTags.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.RMB"),
		FString("鼠标右键的inputtag")
	);
	GameplayTags.InputTag_Shift = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.Shift"),
		FString("Shift inputtag")
	);

	GameplayTags.InputTag_Q = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.Q"),
		FString("Q inputtag")
	);

	GameplayTags.InputTag_E = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.E"),
		FString("E inputtag")
	);

	GameplayTags.InputTag_R = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.R"),
		FString("R inputtag")
	);



	/*play tags*/
	GameplayTags.Player_Block_InputHeld = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Player.Block.InputHeld"),
		FString("Block Input Held callback for input")
	);

	GameplayTags.Player_Block_InputPressed = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Player.Block.InputPressed"),
		FString("Block Input Pressed callback for input")
	);

	GameplayTags.Player_Block_InputReleased = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Player.Block.InputReleased"),
		FString("Block Input Released callback for input")
	);


	/*伤害类型*/

	GameplayTags.PhysicalDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.PhysicalDamage"),
		FString("PhysicalDamage")
	);

	GameplayTags.MagicDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.MagicalDamage"),
		FString("MagicalDamage")
	);

	GameplayTags.TrueDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.TrueDamage"),
		FString("TrueDamage")
	);

	GameplayTags.AttackDamageCoefficient = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Coefficient.AttackDamage"),
		FString("AttackDamageCoefficient")
	);

	GameplayTags.AbilityPowerCoefficient = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Coefficient.AbilityPower"),
		FString("AbilityPowerCoefficient")
	);

	GameplayTags.Abilities_MeleeAttack = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.MeleeAttack"),
		FString("")
	);

	GameplayTags.Abilities_RangedAttack = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.RangedAttack"),
		FString("")
	);

	GameplayTags.Abilities_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.1"),
		FString("")
	);

	GameplayTags.Abilities_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.2"),
		FString("")
	);
	GameplayTags.Abilities_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.3"),
		FString("")
	);

	GameplayTags.Abilities_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.4"),
		FString("")
	);

	GameplayTags.Abilities_TargetConfirm = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.TargetConfirm"),
		FString("")
	);
	
	GameplayTags.Cooldown_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Cooldown.1"),
		FString("")
	);

	GameplayTags.Cooldown_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Cooldown.2"),
		FString("")
	);

	GameplayTags.Cooldown_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Cooldown.3"),
		FString("")
	);

	GameplayTags.Cooldown_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Cooldown.4"),
		FString("")
	);

	GameplayTags.DamageTypes.Add(GameplayTags.PhysicalDamage);
	GameplayTags.DamageTypes.Add(GameplayTags.MagicDamage);
	GameplayTags.DamageTypes.Add(GameplayTags.TrueDamage);

	GameplayTags.Effects_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Effects.HitReact"),
		FString("当受击时授予此tags")
	);

	GameplayTags.Debuff_Burn = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Debuff.Burn"),
		FString("Debuff Burn")
	);

	GameplayTags.Debuff_Stun = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Debuff.Stun"),
		FString("Debuff Stun")
	);

	GameplayTags.DebuffTypes.Add(GameplayTags.Debuff_Burn);
	GameplayTags.DebuffTypes.Add(GameplayTags.Debuff_Stun);
	


	GameplayTags.Debuff_Chance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Debuff.Chance"),
		FString("Debuff Chance")
	);

	GameplayTags.Debuff_Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Debuff.Damage"),
		FString("Debuff Stun")
	);
	GameplayTags.Debuff_Duration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Debuff.Duration"),
		FString("Debuff Duration")
	);

	GameplayTags.Debuff_Frequency = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Debuff.Frequency"),
		FString("Debuff Frequency")
	);

	GameplayTags.Montage_Attack_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Montage.Attack.1"),
		FString("Attack 1")
	);

	GameplayTags.Montage_Attack_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Montage.Attack.2"),
		FString("Attack 2")
	);

	GameplayTags.Montage_Attack_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Montage.Attack.3"),
		FString("Attack 3")
	);

	GameplayTags.Montage_Attack_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Montage.Attack.4"),
		FString("Attack 4")
	);


	GameplayTags.CombatSocket_Weapon = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("CombatSocket.Weapon"),
		FString("Weapon")
	);

	GameplayTags.CombatSocket_RightHand = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("CombatSocket.RightHand"),
		FString("Right Hand")
	);

	GameplayTags.CombatSocket_LeftHand = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("CombatSocket.LeftHand"),
		FString("Left Hand")
	);
	GameplayTags.CombatSocket_Tail = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("CombatSocket.Tail"),
		FString("Tail")
	);

}