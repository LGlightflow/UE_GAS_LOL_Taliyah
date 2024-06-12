// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraComponent.h"
#include "GameplayTagContainer.h"
#include "DebuffNiagaraComponent.generated.h"

/**
 * 
 */
UCLASS()
class ADVENTUREOFTALIYAH_API UDebuffNiagaraComponent : public UNiagaraComponent
{
	GENERATED_BODY()
// Fill out your copyright notice in the Description page of Project Settings.
public:
	UDebuffNiagaraComponent();

	UPROPERTY(VisibleAnywhere)
		FGameplayTag DebuffTag;

protected:
	virtual void BeginPlay() override;
	void DebuffTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

};
