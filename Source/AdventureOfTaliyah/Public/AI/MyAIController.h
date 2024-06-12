// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MyAIController.generated.h"



/**
 * 
 */
UCLASS()
class ADVENTUREOFTALIYAH_API AMyAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AMyAIController();
protected:

	UPROPERTY()
		TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;
	
};

