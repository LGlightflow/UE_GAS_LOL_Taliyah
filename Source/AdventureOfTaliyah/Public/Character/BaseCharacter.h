// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "Interaction/CombatInterface.h"
#include "Player/MyPlayerState.h"
#include "AbilitySystem/MyAttributeSet.h"
//#include "Character/CharacterAttributeSet.h"

#include "GameFramework/Character.h"
#include "AbilitySystem/Debuff/DebuffNiagaraComponent.h"
#include "BaseCharacter.generated.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangeEvent, float, NewHealth);

UCLASS(Abstract)
class ADVENTUREOFTALIYAH_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	//virtual FVector GetCombatSocketLocation_Implementation(const FGameplayTag& MontageTag) override;
	virtual FVector GetCombatSocketLocation_Implementation(const FGameplayTag& MontageTag) override;

	virtual FRotator GetCombatSocketRotation_Implementation() override;

	virtual UAnimMontage* GetHitReactMontage_Implementation() override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/*ICombatInterface 中的 socket*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
		TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY(EditAnywhere, Category = "Combat")
		FName WeaponTipSocketName;

	/*ICombatInterface 的 socket*/

	UPROPERTY(EditAnywhere, Category = "Combat")
		FName LeftHandSocketName;

	UPROPERTY(EditAnywhere, Category = "Combat")
		FName RightHandSocketName;

	UPROPERTY(EditAnywhere, Category = "Combat")
		FName TailSocketName;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
		float BaseWalkSpeed = 400.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
		float LifeSpan = 5.f;


	UPROPERTY(VisibleAnywhere)
		TObjectPtr<UDebuffNiagaraComponent> BurnDebuffComponent;

	UPROPERTY(VisibleAnywhere)
		TObjectPtr<UDebuffNiagaraComponent> StunDebuffComponent;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;
	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/*CombatInterface*/
	virtual void Die() override;
	/*CombatInterface*/


	virtual bool IsDead_Implementation() const override;
	virtual AActor* GetAvatar_Implementation() override;

	virtual TArray<FTaggedMontage> GetAttackMontages_Implementation() override;
	virtual FOnASCRegistered& GetOnASCRegisteredDelegate() override;
	virtual FOnDamageSignature& GetOnDamageSignature() override;
	virtual FOnDeathSignature& GetOnDeathDelegate() override;


	FOnASCRegistered OnAscRegistered;
	FOnDeathSignature OnDeathDelegate;
	FOnDamageSignature OnDamageDelegate;
	UFUNCTION(NetMulticast,Reliable)
		virtual void MulticastHandleDeath();



	UPROPERTY(EditDefaultsOnly, Category = "Class Defaults")
		FScalableFloat XPReward = FScalableFloat();

	virtual FTaggedMontage GetTaggedMontageByTag_Implementation(const FGameplayTag& MontageTag) override;

	UPROPERTY(EditAnywhere, Category = "Combat")
		TArray<FTaggedMontage> AttackMontages;

	virtual bool IsBeingStunned_Implementation() const override;

protected:
	//声明asc
	UPROPERTY()
		TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
		UAttributeSet* AttributeSet;

	// 加载设置attributes的GE
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
		TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
		TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
		TSubclassOf<UGameplayEffect> DefaultVitalAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
		TSubclassOf<UGameplayEffect> AttributesLevelUpReward;

	UPROPERTY(BlueprintReadOnly)
		bool bDead = false;

	UPROPERTY(ReplicatedUsing = OnRep_Burned, BlueprintReadOnly)
		bool bIsBurned = false;

	UPROPERTY(ReplicatedUsing = OnRep_Stunned, BlueprintReadOnly)
		bool bIsStunned = false;
	
	virtual void StunTagChanged(const FGameplayTag CallbackTag,int32 NewCount);

	UFUNCTION()
		virtual void OnRep_Burned();

	UFUNCTION()
		virtual void OnRep_Stunned();
	

	//该类的this指针是const类型，不能改变成员变量的值
	UAttributeSet* GetAttrubuteSet() const { return AttributeSet; }

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const;
	virtual void InitAbilityActorInfo();

	virtual void InitializeDefaultAttributes() const;

	void AddCharacterAbilities();
	void AddCharacterCommonAbilities();

	
private:
	UPROPERTY(EditAnywhere, Category = "Abilities")
		TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	UPROPERTY(EditAnywhere, Category = "Abilities")
		TArray<TSubclassOf<UGameplayAbility>> StartupPassiveAbilities;

	UPROPERTY(EditAnywhere, Category = "Abilities")
		TArray<TSubclassOf<UGameplayAbility>> CommonAbilities;


	UPROPERTY(EditAnywhere, Category = "Combat")
		TObjectPtr<UAnimMontage> HitReactMontage;

	UPROPERTY(EditAnywhere, Category = "Combat")
		TObjectPtr<UAnimMontage> DeathMontage;

	


};
