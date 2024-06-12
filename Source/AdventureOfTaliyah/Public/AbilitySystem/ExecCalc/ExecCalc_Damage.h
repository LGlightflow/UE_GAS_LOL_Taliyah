// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "ExecCalc_Damage.generated.h"

/**
 *  利用此类计算伤害，能够处理护甲减免伤害，暴击伤害等比较复杂的逻辑，
 * 使用方法：1.GE中设置
 2.modifier magnitude设置为set by caller, 
 * 3.data name的tag选择Damage
 * 注意：这个计算伤害的方法不需要用modifier!
 */
UCLASS()
class ADVENTUREOFTALIYAH_API UExecCalc_Damage : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

protected:
	


public:
	UExecCalc_Damage();
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;

	

};
