// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BaseCharacter.h"
#include "Components/CapsuleComponent.h"
#include "AbilitySystem/MyAbilitySystemComponent.h"
#include "AbilitySystemComponent.h"
#include "MyGameplayTags.h"
#include "GameFramework/CharacterMovementComponent.h"
// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	/*AbilitySystemComponent = CreateDefaultSubobject<UMyAbilitySystemComponent>("AbilitySystemComponent");

	AttributeSet = CreateDefaultSubobject<UCharacterAttributeSet>("Attribute Set");*/
	const FMyGameplayTags& GameplayTags = FMyGameplayTags::Get();
	BurnDebuffComponent = CreateDefaultSubobject<UDebuffNiagaraComponent>("BurnDebuffComponent");
	BurnDebuffComponent->SetupAttachment(GetRootComponent());
	BurnDebuffComponent->DebuffTag = GameplayTags.Debuff_Burn;

	StunDebuffComponent = CreateDefaultSubobject<UDebuffNiagaraComponent>("StunDebuffComponent");
	StunDebuffComponent->SetupAttachment(GetRootComponent());
	StunDebuffComponent->DebuffTag = GameplayTags.Debuff_Stun;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

FVector ABaseCharacter::GetCombatSocketLocation_Implementation(const FGameplayTag& MontageTag)
{
	const FMyGameplayTags& GameplayTags = FMyGameplayTags::Get();
	if (MontageTag.MatchesTagExact(GameplayTags.CombatSocket_Weapon) && IsValid(Weapon))
	{
		return Weapon->GetSocketLocation(WeaponTipSocketName);
	}
	if (MontageTag.MatchesTagExact(GameplayTags.CombatSocket_LeftHand))
	{
		return GetMesh()->GetSocketLocation(LeftHandSocketName);
	}
	if (MontageTag.MatchesTagExact(GameplayTags.CombatSocket_RightHand))
	{
		return GetMesh()->GetSocketLocation(RightHandSocketName);
	}
	if (MontageTag.MatchesTagExact(GameplayTags.CombatSocket_Tail))
	{
		return GetMesh()->GetSocketLocation(TailSocketName);
	}

	return FVector();
	//check(Weapon);
	//return Weapon->GetSocketLocation(WeaponTipSocketName);
}

FRotator ABaseCharacter::GetCombatSocketRotation_Implementation()
{
	check(Weapon);
	return Weapon->GetSocketRotation(WeaponTipSocketName);
}

UAnimMontage* ABaseCharacter::GetHitReactMontage_Implementation()
{
	return HitReactMontage;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// 绑定OnHealthAttributeChanged与attribute
	//if (AbilitySystemComponent)
	//{
	//	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UCharacterAttributeSet::GetHealthAttribute())
	//		.AddUObject(this, &ABaseCharacter::OnHealthAttributeChanged);
	//}

}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABaseCharacter, bIsStunned);
	DOREPLIFETIME(ABaseCharacter, bIsBurned);
	//DOREPLIFETIME(ABaseCharacter, bIsStunned);
}

void ABaseCharacter::Die()
{	
	if(IsValid(Weapon)) Weapon->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld,true));
	
	MulticastHandleDeath_Implementation();
	PlayAnimMontage(DeathMontage);
}

bool ABaseCharacter::IsDead_Implementation() const
{
	return bDead;
}

AActor* ABaseCharacter::GetAvatar_Implementation()
{
	return this;
}

TArray<FTaggedMontage> ABaseCharacter::GetAttackMontages_Implementation()
{
	return AttackMontages;
}

FOnASCRegistered& ABaseCharacter::GetOnASCRegisteredDelegate()
{
	return OnAscRegistered;
}

FOnDamageSignature& ABaseCharacter::GetOnDamageSignature()
{
	return OnDamageDelegate;
}

FOnDeathSignature& ABaseCharacter::GetOnDeathDelegate()
{
	return OnDeathDelegate;
}

FTaggedMontage ABaseCharacter::GetTaggedMontageByTag_Implementation(const FGameplayTag& MontageTag)
{
	for (FTaggedMontage TaggedMontage : AttackMontages)
	{
		if (TaggedMontage.MontageTag == MontageTag)
		{
			return TaggedMontage;
		}
	}
	return FTaggedMontage();
}


bool ABaseCharacter::IsBeingStunned_Implementation() const
{
	return bIsStunned;
}

void ABaseCharacter::MulticastHandleDeath_Implementation()
{
	//UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation(), GetActorRotation());

	Weapon->SetSimulatePhysics(true);
	Weapon->SetEnableGravity(true);
	Weapon->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	//Weapon->AddImpulse(DeathImpulse * 0.1f, NAME_None, true);

	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetEnableGravity(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	//GetMesh()->AddImpulse(DeathImpulse, NAME_None, true);
	GetMesh()->SetPhysicsAsset(nullptr);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//Dissolve();
	bDead = true;
	BurnDebuffComponent->Deactivate();
	StunDebuffComponent->Deactivate();
	OnDeathDelegate.Broadcast(this);
}

void ABaseCharacter::StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	bIsStunned = NewCount >0;
	//BaseWalkSpeed = GetCharacterMovement()->MaxWalkSpeed; 
	GetCharacterMovement()->MaxWalkSpeed = bIsStunned?0.f:BaseWalkSpeed;
}

void ABaseCharacter::OnRep_Burned()
{
}

void ABaseCharacter::OnRep_Stunned()
{
}



//// Called to bind functionality to input
//void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);
//
//}
//
//
UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}



void ABaseCharacter::InitAbilityActorInfo()
{
//	AbilitySystemComponent->InitAbilityActorInfo(this, this);
//	Cast<UMyAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
}

// 对Character自身应用GE
void ABaseCharacter::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(GameplayEffectClass);
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass, Level, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}

//初始化attributes,在子类的InitAbilityActorInfo()函数中调用
void ABaseCharacter::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultPrimaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultSecondaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultVitalAttributes,1.f);
	//check(IsValid(GetAbilitySystemComponent()));
	//check(DefaultAttributes);
	//const FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	//const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(DefaultAttributes, 1, ContextHandle);
	//GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}

// 赋予GA（StartupAbilities和StartupPassiveAbilities）
// 在子类的possessedBy调用
void ABaseCharacter::AddCharacterAbilities()
{
	UMyAbilitySystemComponent* MyASC = CastChecked<UMyAbilitySystemComponent>(AbilitySystemComponent);
	if (!HasAuthority()) return;

	MyASC->AddCharacterAbilities(StartupAbilities);
	MyASC->AddCharacterPassiveAbilities(StartupPassiveAbilities);
}


// 主要给AI控制的
void ABaseCharacter::AddCharacterCommonAbilities()
{
	UMyAbilitySystemComponent* MyASC = CastChecked<UMyAbilitySystemComponent>(AbilitySystemComponent);
	if (!HasAuthority()) return;

	MyASC->GiveCommonAbilities(CommonAbilities);

}


