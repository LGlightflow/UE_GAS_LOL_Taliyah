// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class ADVENTUREOFTALIYAH_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float deltaSeconds) override;

protected:
	UPROPERTY(BluePrintReadOnly,Category="AnimValue");
	class APlayerCharacter* playerCharacter;

	UPROPERTY(BluePrintReadOnly, Category = "AnimValue");
	float speed;

	UPROPERTY(BluePrintReadOnly, Category = "AnimValue");
	float direction;

	UPROPERTY(BluePrintReadOnly, Category = "AnimValue");
	bool bIsFalling;

	//UPROPERTY(BluePrintReadOnly, Category = "AnimValue");
	//bool bIsPassiveActivited;
};
