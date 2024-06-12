// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "CharacterAttributeSet.generated.h"

/**
 * 
 */
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class ADVENTUREOFTALIYAH_API UCharacterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	//UCharacterAttributeSet();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Health and MaxHealth
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AttributeSet", ReplicatedUsing = OnRep_Health)//Category = "Abilities"，Rep为联机游戏的使用
		FGameplayAttributeData Health;
		ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, Health);



	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AttributeSet", ReplicatedUsing = OnRep_MaxHealth)//Category = "Abilities"
		FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, MaxHealth);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Mana)
		FGameplayAttributeData Mana;
		ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, Mana);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_MaxMana)
		FGameplayAttributeData MaxMana;
		ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, MaxMana);

	UFUNCTION()
		virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);

	UFUNCTION()
		virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);

	UFUNCTION()
		virtual void OnRep_Mana(const FGameplayAttributeData& OldMana);

	UFUNCTION()
		virtual void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana);
};
