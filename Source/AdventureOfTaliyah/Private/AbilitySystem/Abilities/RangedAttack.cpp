#include "AbilitySystem/Abilities/RangedAttack.h"
#include "AbilitySystemComponent.h"
#include "Interaction/CombatInterface.h"
#include "GameFramework/PlayerController.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "MyGameplayTags.h"
void URangedAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

}


//void URangedAttack::SpawnProjectile(const FVector& ProjectileTargetLocation, const FGameplayTag& SocketTag, bool bOverridePitch, float PitchOverride)
void URangedAttack::SpawnProjectile(const FGameplayTag& SocketTag, bool bOverrideRotation, FRotator RotationOverride)
{

	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer) return;


	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if (CombatInterface) {
		// 默认使用controller（对应player的camera）作旋转
		//FRotator ActorRotation = GetAvatarActorFromActorInfo()->GetActorRotation();
		FRotator SocketRotation = GetAvatarActorFromActorInfo()->GetInstigatorController()->GetControlRotation();
		const FVector SocketLocation = CombatInterface->GetCombatSocketLocation_Implementation(SocketTag);

		float BorderYaw = 75;
	
		if (bOverrideRotation && RotationOverride!= FRotator())
		{
			SocketRotation = RotationOverride;
		}

		FTransform SpawnTransform(SocketRotation.Quaternion(), SocketLocation);

		ARangedAttackProjectile* Projectile = GetWorld()->SpawnActorDeferred<ARangedAttackProjectile>(
			ProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		Projectile->DamageEffectParams = MakeDamageEffectParamsFromClassDefaults();
		Projectile->FinishSpawning(SpawnTransform);

	}
}

FRotator URangedAttack::GetProjectileToTargetRotation(const FVector& ProjectileTargetLocation, const FGameplayTag& SocketTag){
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if (CombatInterface) {
		const FVector SocketLocation = CombatInterface->GetCombatSocketLocation_Implementation(SocketTag);
		return (ProjectileTargetLocation - SocketLocation).Rotation();
	}
	return FRotator();
}


