// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/MyAttributeSet.h"
#include "MyGameplayTags.h"
#include "AbilitySystem/AbilitySystemBPLibrary.h"

//����������Ҫ�����target��source�ı���
struct SDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(MagicResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitChance);

	DECLARE_ATTRIBUTE_CAPTUREDEF(AbilityPower);
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackDamage);


	SDamageStatics()
	{
		

		//target�Ļ���
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMyAttributeSet, Armor, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMyAttributeSet, MagicResistance, Target, false);

		//source�ı�����
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMyAttributeSet, CriticalHitChance, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMyAttributeSet, AbilityPower, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMyAttributeSet, AttackDamage, Source, false);
	}
};

// ��̬����������SDamageStatics�ṹ�壬���ض�Ӧ�ṹ��
static const SDamageStatics& DamageStatics()
{
	static SDamageStatics DStatics;
	return DStatics;
}

UExecCalc_Damage::UExecCalc_Damage()
{
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
	RelevantAttributesToCapture.Add(DamageStatics().MagicResistanceDef);

	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().AbilityPowerDef);
	RelevantAttributesToCapture.Add(DamageStatics().AttackDamageDef);
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition> TagsToCaptureDefs;
	const FMyGameplayTags& Tags = FMyGameplayTags::Get();
	TagsToCaptureDefs.Add(Tags.Attributes_Primary_Armor, DamageStatics().ArmorDef);
	TagsToCaptureDefs.Add(Tags.Attributes_Primary_MagicResistance, DamageStatics().MagicResistanceDef);

	TagsToCaptureDefs.Add(Tags.Attributes_Primary_CriticalHitChance, DamageStatics().CriticalHitChanceDef);
	TagsToCaptureDefs.Add(Tags.Attributes_Primary_AbilityPower, DamageStatics().AbilityPowerDef);
	TagsToCaptureDefs.Add(Tags.Attributes_Primary_AttackDamage, DamageStatics().AttackDamageDef);


	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	AActor* SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	AActor* TargetAvatar = TargetASC ? TargetASC->GetAvatarActor() : nullptr;

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;


	/*debuff*/
	const FMyGameplayTags& GameplayTags = FMyGameplayTags::Get();
	for (FGameplayTag DebuffType:GameplayTags.DebuffTypes)
	{
	}

	const float SourceDebuffChance = Spec.GetSetByCallerMagnitude(GameplayTags.Debuff_Chance, false, -1.f);  //debuff����
	const bool bDebuff = FMath::RandRange(1, 100) < SourceDebuffChance;
	if (bDebuff)
	{
		FGameplayEffectContextHandle ContextHandle = Spec.GetContext();

		UAbilitySystemBPLibrary::SetIsSuccessfulDebuff(ContextHandle, true);
		//UAbilitySystemBPLibrary::SetDamageType(ContextHandle, DamageType);

		//�������Ҫ�ĳɺ��˺�����һ����if�ж�
		//UAbilitySystemBPLibrary::SetDebuffType(ContextHandle, DebuffType);
		//FGameplayTag GameplayTag = (UAbilitySystemBPLibrary::GetDebuffType(ContextHandle)); ����debufftag��
		const float DebuffDamage = Spec.GetSetByCallerMagnitude(GameplayTags.Debuff_Damage, false, -1.f);
		const float DebuffDuration = Spec.GetSetByCallerMagnitude(GameplayTags.Debuff_Duration, false, -1.f);
		const float DebuffFrequency = Spec.GetSetByCallerMagnitude(GameplayTags.Debuff_Frequency, false, -1.f);

		UAbilitySystemBPLibrary::SetDebuffDamage(ContextHandle, DebuffDamage);
		UAbilitySystemBPLibrary::SetDebuffDuration(ContextHandle, DebuffDuration);
		UAbilitySystemBPLibrary::SetDebuffFrequency(ContextHandle, DebuffFrequency);
	}

	/*debuff*/

	/* �����˺�����*/
	float Damage = 0;

	// ����DamageTypes�����Tag�����˺�����
	for (FGameplayTag DamageTypeTag:FMyGameplayTags::Get().DamageTypes)
	{
		// ��ȡĳ���˺��������õ��˺�ֵ
		//const float DamageTypeValue = Spec.GetSetByCallerMagnitude(DamageTypeTag);


		// ��ð��ж��е�����װΪ�������������أ�ʹ�˺����Ը��ݹ������ͷ�ǿ��������
		if (DamageTypeTag == FMyGameplayTags::Get().PhysicalDamage)
		{	
			float SourceAttackDamage = 0.f;
			ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().AttackDamageDef, EvaluationParameters, SourceAttackDamage);
			SourceAttackDamage = FMath::Max<float>(0, SourceAttackDamage);

			// ��ȡ��GE�����õ�PhysicalDamageValue
			const float PhysicalDamageValue = Spec.GetSetByCallerMagnitude(DamageTypeTag)+
												SourceAttackDamage*Spec.GetSetByCallerMagnitude(FMyGameplayTags::Get().AttackDamageCoefficient);


			//��ȡĿ��Ļ��� 
			float TargetArmor = 0.f;
			ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorDef, EvaluationParameters, TargetArmor);
			TargetArmor = FMath::Max<float>(0, TargetArmor);
			
			// ���㻤�׼����������˺�
			Damage += (1 / (1 + FMath::Log2(TargetArmor) / 8))* PhysicalDamageValue;

		}

		if (DamageTypeTag == FMyGameplayTags::Get().MagicDamage)
		{
			float SourceAbilityPower = 0.f;
			ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().AbilityPowerDef, EvaluationParameters, SourceAbilityPower);
			SourceAbilityPower = FMath::Max<float>(0, SourceAbilityPower);


			// ��ȡ��GE�����õ�MagicalDamageValue
			const float MagicDamageValue = Spec.GetSetByCallerMagnitude(DamageTypeTag)+
				SourceAbilityPower* Spec.GetSetByCallerMagnitude(FMyGameplayTags::Get().AbilityPowerCoefficient);

			//��ȡĿ���ħ��
			float TargetMagicResistance = 0.f;
			ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().MagicResistanceDef, EvaluationParameters, TargetMagicResistance);
			TargetMagicResistance = FMath::Max<float>(0, TargetMagicResistance);

			// ���㻤�׼�����ħ���˺�
			Damage += (1 / (1 + TargetMagicResistance/100 )) * MagicDamageValue;

		}

		if (DamageTypeTag == FMyGameplayTags::Get().TrueDamage)
		{
			// ��ȡ��GE�����õ�MagicalDamageValue
			const float TrueDamageValue = Spec.GetSetByCallerMagnitude(DamageTypeTag);
			Damage += TrueDamageValue;
		}

		
	}

	// �����˺�����
	float SourceCriticalHitChance = 0;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitChanceDef, EvaluationParameters, SourceCriticalHitChance);
	SourceCriticalHitChance = FMath::Max<float>(0, SourceCriticalHitChance);
	const bool bCriticalHit = FMath::RandRange(0, 1) < SourceCriticalHitChance;

	FGameplayEffectContextHandle EffectContextHandle = Spec.GetContext();
	UAbilitySystemBPLibrary::SetIsCriticalHit(EffectContextHandle, bCriticalHit);

	
	Damage = bCriticalHit ? 1.5 * Damage : Damage;
	

	const FGameplayModifierEvaluatedData EvaluatedData(UMyAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);


}
