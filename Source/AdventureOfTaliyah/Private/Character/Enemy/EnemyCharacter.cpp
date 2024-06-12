// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Enemy/EnemyCharacter.h"
#include "AbilitySystem/MyAttributeSet.h"
#include "AbilitySystem/MyAbilitySystemComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/Widget/UIUserWidget.h"
#include "MyGameplayTags.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AI/MyAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
AEnemyCharacter::AEnemyCharacter() {
	AbilitySystemComponent = CreateDefaultSubobject<UMyAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	//Mix模式: OwnerActor的拥有者必须是controller，对pawns来说，通过possessedby()自动设置；Playstate的拥有者自动设置为controller
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);


	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;


	AttributeSet = CreateDefaultSubobject<UMyAttributeSet>("AttributeSet");
	//服务端更新频率
	NetUpdateFrequency = 100.f;

	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());

	BaseWalkSpeed = 250.f;
}

void AEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!HasAuthority()) return;
	MyAIController = Cast<AMyAIController>(NewController);
	MyAIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	MyAIController->RunBehaviorTree(BehaviorTree);
	MyAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), false);
	MyAIController->GetBlackboardComponent()->SetValueAsBool(FName("RangedAttacker"), this->ActorHasTag(FName("RangedAttacker")));

}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	//holds information about who we are acting on and who controls us
	//OwnerActor is the actor that logically owns this component
	// AvatarActor is what physical actor in the world we are acting on
	// 
	// 移到AEnemyCharacter::InitAbilityActorInfo()
	//AbilitySystemComponent->InitAbilityActorInfo(this, this);

	
	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;

	InitAbilityActorInfo();
	
	AddCharacterAbilities();
	AddCharacterCommonAbilities();

	InitProgressBar();
	
}

void AEnemyCharacter::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	//当执行InitAbilityActorInfo()，使ASC可以执行绑定到委托的操作
	Cast<UMyAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
	//InitializeDefaultAttributes();
	AbilitySystemComponent->RegisterGameplayTagEvent(FMyGameplayTags::Get().Debuff_Stun, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &AEnemyCharacter::StunTagChanged);

	if (HasAuthority())
	{
		InitializeDefaultAttributes();
	}
	OnAscRegistered.Broadcast(AbilitySystemComponent);
	
}

void AEnemyCharacter::Die()
{

	SetLifeSpan(LifeSpan);
	if (MyAIController)
	{
		MyAIController->GetBlackboardComponent()->SetValueAsBool(FName("Dead"),true);
	}
	Super::Die();
	
}

void AEnemyCharacter::SetCombatTarget_Implementation(AActor* InCombatTarget)
{
	CombatTarget = InCombatTarget;
}

AActor* AEnemyCharacter::GetCombatTarget_Implementation() const
{
	return CombatTarget;
}

void AEnemyCharacter::InitProgressBar()
{	
	if (UUIUserWidget* UIUserWidget = Cast<UUIUserWidget>(HealthBar->GetUserWidgetObject()))
	{
		UIUserWidget->SetWidgetController(this);
	}
	if (const UMyAttributeSet* MyAS = Cast<UMyAttributeSet>(AttributeSet))
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MyAS->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnHealthChanged.Broadcast(Data.NewValue);
			}
		);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MyAS->GetMaxHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnMaxHealthChanged.Broadcast(Data.NewValue);
			}
		);

		/** NewOrRemoved:Event only happens when tag is new or completely removed */
		// 当tags添加或移除时注册事件
		AbilitySystemComponent->RegisterGameplayTagEvent(FMyGameplayTags::Get().Effects_HitReact, EGameplayTagEventType::NewOrRemoved).AddUObject(
			this,
			&AEnemyCharacter::HitReactTagChanged
		);

		OnHealthChanged.Broadcast(MyAS->GetHealth());
		OnMaxHealthChanged.Broadcast(MyAS->GetMaxHealth());
	}
}

int32 AEnemyCharacter::GetPlayerLevel_Implementation() const
{
	return Level;
}

void AEnemyCharacter::HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	bHitReacting = NewCount > 0;
	GetCharacterMovement()->MaxWalkSpeed = bHitReacting ? 0.f : BaseWalkSpeed;
	if (MyAIController && MyAIController->GetBlackboardComponent())
	{
		MyAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), bHitReacting);
	}
}

void AEnemyCharacter::StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	Super::StunTagChanged(CallbackTag,NewCount);
	if (MyAIController && MyAIController->GetBlackboardComponent())
	{
		MyAIController->GetBlackboardComponent()->SetValueAsBool(FName("Stunned"), bHitReacting);
	}
}
