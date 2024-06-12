// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/PlayerAnimInstance.h"
#include "Character/Player/PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	playerCharacter = Cast<APlayerCharacter>(TryGetPawnOwner());
}

void UPlayerAnimInstance::NativeUpdateAnimation(float deltaSeconds)
{
	Super::NativeUpdateAnimation(deltaSeconds);
	if (playerCharacter) {
		FVector velocity = playerCharacter->GetVelocity(); //get character velocity
		speed = velocity.Length();


		FRotator rotation = playerCharacter->GetActorRotation(); 

		direction = CalculateDirection(velocity,rotation);

		UCharacterMovementComponent* movement = playerCharacter->GetCharacterMovement();

		bIsFalling = movement->IsFalling();

		//bIsPassiveActivited = playerCharacter->bIsPassiveActivited;
	}

}

