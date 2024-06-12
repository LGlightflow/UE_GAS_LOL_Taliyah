// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "ExecCalc_Damage.generated.h"

/**
 *  ���ô�������˺����ܹ������׼����˺��������˺��ȱȽϸ��ӵ��߼���
 * ʹ�÷�����1.GE������
 2.modifier magnitude����Ϊset by caller, 
 * 3.data name��tagѡ��Damage
 * ע�⣺��������˺��ķ�������Ҫ��modifier!
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
