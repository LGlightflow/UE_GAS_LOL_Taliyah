// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Character/BaseCharacter.h"
#include "Interaction/PlayerInterface.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class ADVENTUREOFTALIYAH_API APlayerCharacter : public ABaseCharacter, public IPlayerInterface //, public IAbilitySystemInterface //¼Ì³Ðgas½Ó¿Ú 
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputMappingContext* DefaultMappingContext;


	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* JumpAction;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* PassiveAction;



public:
	// Sets default values for this character's properties
	APlayerCharacter();
	
	/** Combat Interface */
	//virtual int32 GetPlayerLevel_Implementation() const override;
	/** Combat Interface */
	
	/** Player Interface */
	//virtual int32 GetXP_Implementation() const override;
	
protected:
	
	virtual void Passive(const FInputActionValue& Value);
	//virtual void Attack(const FInputActionValue& Value);
protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	// Called when the game starts or when spawned
	virtual void BeginPlay();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UFUNCTION(BlueprintCallable)
	FRotator GetCameraRotation() const;
	

};
