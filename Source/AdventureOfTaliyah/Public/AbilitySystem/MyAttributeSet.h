// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "MyAttributeSet.generated.h"
/**
 * This defines a set of helper functions for accessing and initializing attributes, to avoid having to manually write these functions.
 * It would creates the following functions, for attribute Health
 *
 *	static FGameplayAttribute UMyHealthSet::GetHealthAttribute();
 *	FORCEINLINE float UMyHealthSet::GetHealth() const;
 *	FORCEINLINE void UMyHealthSet::SetHealth(float NewVal);
 *	FORCEINLINE void UMyHealthSet::InitHealth(float NewVal);
 *
 * To use this in your game you can define something like this, and then add game-specific functions as necessary:
 *
 *	#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
 *	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
 *	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
 *	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
 *	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
 *
 *	ATTRIBUTE_ACCESSORS(UMyHealthSet, Health)
 */
//类似替换字符串，可以参考上面的注释
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

// 将属性封装到此结构体，因为在提交GE的更改时，以下的属性总是一起出现（且被需要）
USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()

		FEffectProperties() {}

	FGameplayEffectContextHandle EffectContextHandle;

	UPROPERTY()
		UAbilitySystemComponent* SourceASC = nullptr;

	UPROPERTY()
		AActor* SourceAvatarActor = nullptr;

	UPROPERTY()
		AController* SourceController = nullptr;

	UPROPERTY()
		ACharacter* SourceCharacter = nullptr;

	UPROPERTY()
		UAbilitySystemComponent* TargetASC = nullptr;

	UPROPERTY()
		AActor* TargetAvatarActor = nullptr;

	UPROPERTY()
		AController* TargetController = nullptr;

	UPROPERTY()
		ACharacter* TargetCharacter = nullptr;
};

// typedef is specific to the FGameplayAttribute() signature, but TStaticFunPtr is generic to any signature chosen
//typedef TBaseStaticDelegateInstance<FGameplayAttribute(), FDefaultDelegateUserPolicy>::FFuncPtr FAttributeFuncPtr;
//


template<class T>
using TStaticFuncPtr = typename TBaseStaticDelegateInstance<T, FDefaultDelegateUserPolicy>::FFuncPtr;

//DECLARE_DELEGATE_RetVal(FGameplayAttribute, FAttributeSignature);
/**
 * 
 */
UCLASS()
class ADVENTUREOFTALIYAH_API UMyAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UMyAttributeSet();

	//已定义成const的成员函数，一旦企图修改数据成员的值，则编译器按错误处理
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

	//TMap<FGameplayTag, FAttributeSignature> TagsToAttributes;
	TMap<FGameplayTag, TStaticFuncPtr<FGameplayAttribute()>> TagsToAttributes;


	/*
	
	人物属性：
	步骤1.声明在类中的属性(UPROPERTY) 
	2.声明好当属性改变的OnRep回调 
	3.定义步骤2提到的函数 
	4.在GetLifetimeReplicatedProps(网络同步函数的override)设置DOREPLIFETIME_CONDITION_NOTIFY(自定复制同步条件)
	5.可在BaseCharacter类中通过GE初始化attribute
	*/ 

	/*一级属性：最基础的属性*/


	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Primary Attributes")
		FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, MaxHealth);


	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Primary Attributes")
		FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, MaxMana);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_AttackDamage, Category = "Primary Attributes")
		FGameplayAttributeData AttackDamage;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, AttackDamage);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_AbilityPower, Category = "Primary Attributes")
		FGameplayAttributeData AbilityPower;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, AbilityPower);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Armor, Category = "Primary Attributes")
		FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, Armor);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MagicResistance, Category = "Primary Attributes")
		FGameplayAttributeData MagicResistance;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, MagicResistance);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_AttackSpeed, Category = "Primary Attributes")
		FGameplayAttributeData AttackSpeed;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, AttackSpeed);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitChance, Category = "Primary Attributes")
		FGameplayAttributeData CriticalHitChance;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, CriticalHitChance);

	//UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MoveSpeed, Category = "Primary Attributes")
	//	FGameplayAttributeData MoveSpeed;
	//ATTRIBUTE_ACCESSORS(UMyAttributeSet, MoveSpeed);

	/*二级属性：二级属性与一级属性的值相关
	用于初始化二级属性的GE的durationPolicy类型是infinite
	*/


	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealthRegeneration, Category = "Secondary Attributes")
		FGameplayAttributeData HealthRegeneration;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, HealthRegeneration);



	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ManaRegeneration, Category = "Secondary Attributes")
		FGameplayAttributeData ManaRegeneration;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, ManaRegeneration);

	/* 重要属性
	*/
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Vital Attributes")
		FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, Health);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Vital Attributes")
		FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, Mana);

	/*
	 * Meta Attributes
	 */

	// 即将到来的伤害，便于在服务器计算伤害以及应用暴击、是否命中等
	// 使用方法:在GE的modified magnitude中设置set by caller，将set by caller magnitude的tag设置为"Damage"
	UPROPERTY(BlueprintReadOnly, Category = "Meta Attributes")
		FGameplayAttributeData IncomingDamage;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, IncomingDamage);

	//获取到的EXP
	UPROPERTY(BlueprintReadOnly, Category = "Meta Attributes")
		FGameplayAttributeData IncomingXP;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, IncomingXP);


	UFUNCTION()
		void OnRep_AttackDamage(const FGameplayAttributeData& OldAttackDamage) const;

	UFUNCTION()
		void OnRep_AbilityPower(const FGameplayAttributeData& OldAbilityPower) const;

	UFUNCTION()
		void OnRep_Armor(const FGameplayAttributeData& OldArmor) const;

	UFUNCTION()
		void OnRep_MagicResistance(const FGameplayAttributeData& OldMagicResistance) const;

	UFUNCTION()
		void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;

	UFUNCTION()
		void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;

	UFUNCTION()
		void OnRep_AttackSpeed(const FGameplayAttributeData& OldAttackSpeed) const;

	UFUNCTION()
		void OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const;

	//UFUNCTION()
	//	void OnRep_MoveSpeed(const FGameplayAttributeData& OldMoveSpeed) const;

	UFUNCTION()
		void OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const;

	UFUNCTION()
		void OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const;




	UFUNCTION()
		void OnRep_Health(const FGameplayAttributeData& OldHealth) const;

	UFUNCTION()
		void OnRep_Mana(const FGameplayAttributeData& OldMana) const;


private:
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;

	void ShowFloatingText(const FEffectProperties& Props, float Damage,bool bCriticalHit) const;

	void SendXPEvent(const FEffectProperties& Props);
};
