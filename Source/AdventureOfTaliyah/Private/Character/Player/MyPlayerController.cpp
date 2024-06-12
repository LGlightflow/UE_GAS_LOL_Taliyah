// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/MyPlayerController.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputSubsystems.h" 
#include "EnhancedInputComponent.h" 
#include "Input/MyEnhancedInputComponent.h"
#include "GameFramework/Character.h"
#include "AbilitySystem/MyAbilitySystemComponent.h"
#include "MyGameplayTags.h"
#include "UI/Widget/DamageTextComponent.h"

AMyPlayerController::AMyPlayerController()
{
	//复制：将服务端上的实体变化（数据更新）发送给客户端 
	bReplicates = true;
}




void AMyPlayerController::BeginPlay() {
	Super::BeginPlay();
	// 检查Context是否已经设置好，如果没设置好，运行游戏会崩溃
	check(Context);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	//check(Subsystem);
	//Subsystem->AddMappingContext(Context, 0);
	if (Subsystem) {
		Subsystem->AddMappingContext(Context, 0);
	}
	
	/***********鼠标不锁定并显示鼠标，按需注释掉**************/
	//bShowMouseCursor = true;
	//DefaultMouseCursor = EMouseCursor::Default;

	//FInputModeGameAndUI InputModeData;
	//InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	//InputModeData.SetHideCursorDuringCapture(false);
	//SetInputMode(InputModeData);
	/***********鼠标不锁定并显示鼠标，按需注释掉**************/
}

// 显示 damageNumber组件
// 在myAttributeSet中调用
void AMyPlayerController::ShowDamageNumber_Implementation(float DamageAmount, ACharacter* TargetCharacter,bool bCriticalHit)
{
	if (IsValid(TargetCharacter) && DamageTextComponentClass && IsLocalController())
	{
		UDamageTextComponent* DamageText = NewObject<UDamageTextComponent>(TargetCharacter, DamageTextComponentClass);
		DamageText->RegisterComponent();
		DamageText->AttachToComponent(TargetCharacter->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		DamageText->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		DamageText->SetDamageText(DamageAmount,bCriticalHit);
	}
}

void AMyPlayerController::AbilityInputTagPressed(FGameplayTag InputTag) {
	if (GetASC() == nullptr)
		return;
	if(GetASC()->HasMatchingGameplayTag(FMyGameplayTags::Get().Player_Block_InputPressed))
		return;
	GetASC()->AbilityInputTagPressed(InputTag);
}

void AMyPlayerController::AbilityInputTagReleased(FGameplayTag InputTag) {
	if (GetASC() == nullptr)
		return;
	if (GetASC()->HasMatchingGameplayTag(FMyGameplayTags::Get().Player_Block_InputReleased))
		return;
	GetASC()->AbilityInputTagReleased(InputTag);
}

void AMyPlayerController::AbilityInputTagHeld(FGameplayTag InputTag) {
	if (GetASC() == nullptr)
		return;
	if (GetASC()->HasMatchingGameplayTag(FMyGameplayTags::Get().Player_Block_InputHeld))
		return;
	GetASC()->AbilityInputTagHeld(InputTag);
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	//if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent)
	if (UMyEnhancedInputComponent* MyEnhancedInputComponent = CastChecked<UMyEnhancedInputComponent>(InputComponent)) {

		//Jumping
		//EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AMyPlayerController::Jump);
		//EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AMyPlayerController::StopJumping);
		//Moving
		//EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyPlayerController::Move);
		////Looking
		//EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyPlayerController::Look);
		//EnhancedInputComponent->BindAction(PassiveAction, ETriggerEvent::Completed, this, &APlayerCharacter::Passive);
		//EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &APlayerCharacter::Attack);
		MyEnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyPlayerController::Move);

		//Looking
		MyEnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyPlayerController::Look);

		MyEnhancedInputComponent->BindAbilityActions(InputConfig,this,&ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
	}
}

UMyAbilitySystemComponent* AMyPlayerController::GetASC()
{
	if (MyAbilitySystemComponent == nullptr)
	{
		MyAbilitySystemComponent = Cast<UMyAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return MyAbilitySystemComponent;
}


void AMyPlayerController::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();


	// find out which way is forward
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// get forward vector
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	// get right vector 
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	// add movement 
	if (APawn* ContrlledPawn = GetPawn<APawn>()) {
		ContrlledPawn->AddMovementInput(ForwardDirection, MovementVector.Y);
		ContrlledPawn->AddMovementInput(RightDirection, MovementVector.X);
	}

	
}

void AMyPlayerController::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (APawn* ContrlledPawn = GetPawn<APawn>())
	{
		// add yaw and pitch input to controller
		ContrlledPawn->AddControllerYawInput(LookAxisVector.X);
		ContrlledPawn->AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AMyPlayerController::CursorTrace()
{

}
