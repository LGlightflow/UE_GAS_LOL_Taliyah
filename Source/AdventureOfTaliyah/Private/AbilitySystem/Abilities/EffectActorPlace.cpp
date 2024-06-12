// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/EffectActorPlace.h"

void UEffectActorPlace::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UEffectActorPlace::SpawnEffectActor(bool bOverridetLocation, FVector LocationOverride, bool bOverrideRotation, FRotator RotationOverride)
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer) return;
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if (CombatInterface){
		FVector ActorLocation = GetAvatarActorFromActorInfo()->GetActorLocation();
		FRotator ActorRotation = GetAvatarActorFromActorInfo()->GetInstigator()->GetControlRotation();
		ActorRotation.Pitch = 0;
		ActorRotation.Roll = 0;
		if (bOverrideRotation && RotationOverride != FRotator())
		{
			ActorRotation = RotationOverride;
		}
		if (bOverridetLocation && LocationOverride != FVector())
		{
			ActorLocation = LocationOverride;
		}
		FTransform SpawnTransform(ActorRotation.Quaternion(),ActorLocation);

		APlaceEffectActor* PlaceEffectActor = GetWorld()->SpawnActorDeferred<APlaceEffectActor>(
			EffectActorClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		
		PlaceEffectActor->DamageEffectParams = MakeDamageEffectParamsFromClassDefaults();

		PlaceEffectActor->FinishSpawning(SpawnTransform);
	}
}
