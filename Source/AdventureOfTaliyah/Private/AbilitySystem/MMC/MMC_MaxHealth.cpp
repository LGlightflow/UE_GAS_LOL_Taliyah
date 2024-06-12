// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/MMC/MMC_MaxHealth.h"
#include "AbilitySystem/MyAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxHealth::UMMC_MaxHealth()
{

	MaxHealthDef.AttributeToCapture = UMyAttributeSet::GetMaxHealthAttribute();
	MaxHealthDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	MaxHealthDef.bSnapshot = false;
	RelevantAttributesToCapture.Add(MaxHealthDef);
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Gather tags from source and target

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	//获得maxhealth的实际值
	float MaxHeath = 0.f;
	GetCapturedAttributeMagnitude(MaxHealthDef, Spec, EvaluationParameters, MaxHeath);
	MaxHeath = FMath::Max<float>(MaxHeath, 0.f);

	int32 PlayerLevel = 1;
	if (Spec.GetContext().GetSourceObject()->Implements<UCombatInterface>())
	{
		PlayerLevel = ICombatInterface::Execute_GetPlayerLevel(Spec.GetContext().GetSourceObject());
	}

	return 0.5f + 0.001f* MaxHeath + 0.2f * PlayerLevel;
}