// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/Player/Taliyah/TaliyahCharacter.h"
#include "Abilities/GameplayAbility.h"
#include "AbilitySystem/MyAbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "NiagaraComponent.h"
#include "Components/InputComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/Player/MyPlayerController.h"
#include "UI/HUD/MyHUD.h"
#include "Net/UnrealNetwork.h"
#include "MyGameplayTags.h"



ATaliyahCharacter::ATaliyahCharacter():APlayerCharacter()
{
	LevelUpNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>("LevelUpNiagaraComponent");
	LevelUpNiagaraComponent->SetupAttachment(GetRootComponent());
	LevelUpNiagaraComponent->bAutoActivate = false;


	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 400.f;
	GetCharacterMovement()->AirControl = 0.35f; //When falling, control movement;1=max walk speed
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	GetCharacterMovement()->MaxAcceleration = 600.f;

	//// Create a camera boom (pulls in towards the player if there is a collision)
	//CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	//CameraBoom->SetupAttachment(RootComponent);
	//CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	//CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	//// Create a follow camera
	//FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	//FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	//FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	//// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	//// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

}




void ATaliyahCharacter::BeginPlay()
{
	Super::BeginPlay(); //调用父类beginplay

	//GiveAbilityByCpp();
}

void ATaliyahCharacter::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
}

void ATaliyahCharacter::AddToXP_Implementation(int32 InXP)
{
	AMyPlayerState* MyPlayerState = GetPlayerState<AMyPlayerState>();
	check(MyPlayerState);
	MyPlayerState->AddToXP(InXP);
}

void ATaliyahCharacter::LevelUp_Implementation() 
{
	MulticastLevelUpParticles_Implementation();
}

void ATaliyahCharacter::MulticastLevelUpParticles_Implementation()
{
	if (IsValid(LevelUpNiagaraComponent))
	{
		LevelUpNiagaraComponent->Activate(true);
	}
}

void ATaliyahCharacter::InitAbilityActorInfo()
{	//为服务端初始化ability actor info
	AMyPlayerState* MyPlayerState = GetPlayerState<AMyPlayerState>();
	check(MyPlayerState);
	MyPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(MyPlayerState, this);
	Cast<UMyAbilitySystemComponent>(MyPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();
	AbilitySystemComponent = MyPlayerState->GetAbilitySystemComponent();
	AttributeSet = MyPlayerState->GetAttrubuteSet();
	OnAscRegistered.Broadcast(AbilitySystemComponent);

	AbilitySystemComponent->RegisterGameplayTagEvent(FMyGameplayTags::Get().Debuff_Stun, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &ATaliyahCharacter::StunTagChanged);

	AbilitySystemComponent = MyPlayerState->GetAbilitySystemComponent();
	if (AMyPlayerController* MyPlayerController = Cast<AMyPlayerController>(GetController())) {
		if (AMyHUD* MyHUD = Cast<AMyHUD>(MyPlayerController->GetHUD())) {
			MyHUD->InitOverlay(MyPlayerController, MyPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}

	InitializeDefaultAttributes();
}




void ATaliyahCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitAbilityActorInfo();
	AddCharacterAbilities();
	AddCharacterCommonAbilities();
}

void ATaliyahCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	//为客户端初始化ability actor info
	InitAbilityActorInfo();
}

void ATaliyahCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ATaliyahCharacter, bIsPassiveActivited);
}

int32 ATaliyahCharacter::GetPlayerLevel_Implementation() const
{
	const AMyPlayerState* MyPlayerState = GetPlayerState<AMyPlayerState>();
	check(MyPlayerState);
	return MyPlayerState->GetPlayerLevel();
}

int32 ATaliyahCharacter::GetPlayerLevelFromPlayerInterface_Implementation() const
{
	const AMyPlayerState* MyPlayerState = GetPlayerState<AMyPlayerState>();
	check(MyPlayerState);
	return MyPlayerState->GetPlayerLevel();
}

// 从MyPlayerState 获取当前所拥有的经验
int32 ATaliyahCharacter::GetXP_Implementation() const
{
	const AMyPlayerState* MyPlayerState = GetPlayerState<AMyPlayerState>();
	check(MyPlayerState);
	int32 level = MyPlayerState->GetPlayerLevel();
	return MyPlayerState->GetXP();
}


int32 ATaliyahCharacter::FindLevelForXP_Implementation(int32 InXP) const
{
	const AMyPlayerState* MyPlayerState = GetPlayerState<AMyPlayerState>();
	check(MyPlayerState);
	return MyPlayerState->LevelUpInfo->FindLevelForXP(InXP);
}

void ATaliyahCharacter::AddToPlayerLevel_Implementation(int32 InPlayerLevel)
{
	AMyPlayerState* MyPlayerState = GetPlayerState<AMyPlayerState>();
	check(MyPlayerState);
	MyPlayerState->AddToLevel(InPlayerLevel);
	 
	//if (UMyAbilitySystemComponent* MyASC = Cast<UMyAbilitySystemComponent>(GetAbilitySystemComponent()))
	//{
	//	MyASC->UpdateAbilityStatuses(MyPlayerState->GetPlayerLevel());
	//}
}

// 应用升级后加属性的GE，modifier应该是Instant和add（可以参考DefaultAttribute）
void ATaliyahCharacter::AddToLevelUpAttributesReward_Implementation(int32 NewLevel)
{	
	if (IsValid(AttributesLevelUpReward))
	{
		ApplyEffectToSelf(AttributesLevelUpReward, NewLevel);
	}
	
}

// 对player进行stun的网络同步，使stun的block能在客户端生效
void ATaliyahCharacter::OnRep_Stunned()
{
	if (UMyAbilitySystemComponent* MyASC = Cast<UMyAbilitySystemComponent>(AbilitySystemComponent))
	{
		const FMyGameplayTags& GameplayTags = FMyGameplayTags::Get();
		FGameplayTagContainer BlockedTags;
		BlockedTags.AddTag(GameplayTags.Player_Block_InputHeld);
		BlockedTags.AddTag(GameplayTags.Player_Block_InputPressed);
		BlockedTags.AddTag(GameplayTags.Player_Block_InputReleased);
		if (bIsStunned)
		{
			MyASC->AddLooseGameplayTags(BlockedTags);
			//StunDebuffComponent->Activate();
		}
		else
		{
			MyASC->RemoveLooseGameplayTags(BlockedTags);
			//StunDebuffComponent->Deactivate();
		}
	}
}

void ATaliyahCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATaliyahCharacter::Passive_Implementation(const FInputActionValue& Value)
{
	if (Controller)
	{
		if (!bIsPassiveActivited) {
		
			GetCharacterMovement()->MaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed + 800.f;
			BaseWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
			GetCharacterMovement()->MaxAcceleration = GetCharacterMovement()->MaxAcceleration + 1000.f;
			GetCharacterMovement()->JumpZVelocity = GetCharacterMovement()->JumpZVelocity + 400;
			bIsPassiveActivited = true;

		}
		else {
			GetCharacterMovement()->MaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed - 800.f;
			BaseWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
			GetCharacterMovement()->MaxAcceleration = GetCharacterMovement()->MaxAcceleration - 1000.f;
			GetCharacterMovement()->JumpZVelocity = GetCharacterMovement()->JumpZVelocity - 400;
			bIsPassiveActivited = false;
		}
	}
}

