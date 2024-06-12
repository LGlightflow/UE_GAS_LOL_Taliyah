// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/Taliyah/TaliyahAnimInstance.h"
#include "Character/Player/Taliyah/TaliyahCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/Player/MyPlayerController.h"
void UTaliyahAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	taliyahCharacter = Cast<ATaliyahCharacter>(TryGetPawnOwner());
}

void UTaliyahAnimInstance::NativeUpdateAnimation(float deltaSeconds)
{
	Super::NativeUpdateAnimation(deltaSeconds);
	if (taliyahCharacter) {
		FVector velocity = taliyahCharacter->GetVelocity(); //get character velocity
		speed = velocity.Length();


		FRotator rotation = taliyahCharacter->GetActorRotation();

		direction = CalculateDirection(velocity, rotation);

		UCharacterMovementComponent* movement = taliyahCharacter->GetCharacterMovement();

		bIsFalling = movement->IsFalling();

		bIsPassiveActivited = taliyahCharacter->bIsPassiveActivited;

		if(AMyPlayerController * MyPC = Cast<AMyPlayerController>(taliyahCharacter->GetController())){
			UpperBodyRotation = MyPC->PlayerCameraManager->GetCameraRotation();
		}
	}

}