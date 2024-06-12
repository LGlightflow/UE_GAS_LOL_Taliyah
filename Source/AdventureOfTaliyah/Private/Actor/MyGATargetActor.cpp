// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/MyGATargetActor.h"
#include "Abilities/GameplayAbility.h"


/*
	���̣�1.start targeting 2.���confirm 3.����targeting����������
*/



AMyGATargetActor::AMyGATargetActor()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AMyGATargetActor::StartTargeting(UGameplayAbility* Ability)
{
	OwningAbility = Ability;
	PrimaryPC = Cast<APlayerController>(Ability->GetAvatarActorFromActorInfo()->GetInstigatorController());
	SourceActor = Ability->GetAvatarActorFromActorInfo();

	ConePoint = GetWorld()->SpawnActor<AActor>(ConePointClass, FVector::ZeroVector, FRotator::ZeroRotator);
}

void AMyGATargetActor::ConfirmTargetingAndContinue()
{
	// ViewLocation��������ײ����λ��
	FVector ViewLocation;
	GetPlayerLookingPoint(ViewLocation);

	TArray<FOverlapResult> OverlapResults;
	TArray<TWeakObjectPtr<AActor>> OverlapActors;

	FCollisionQueryParams QueryParams;
	QueryParams.bTraceComplex = false;
	QueryParams.bReturnPhysicalMaterial = false;
	if (SourceActor)
	{
		QueryParams.AddIgnoredActor(SourceActor->GetUniqueID());
	}

	bool TryOverlap = GetWorld()->OverlapMultiByObjectType(
		OverlapResults,
		ViewLocation,
		FQuat::Identity,
		FCollisionObjectQueryParams(ECC_Pawn),
		FCollisionShape::MakeSphere(Radius),
		QueryParams);

	if (TryOverlap)
	{
		for (FOverlapResult& OverlapResult : OverlapResults)
		{
			APawn* PawnOverlapped = Cast<APawn>(OverlapResult.GetActor());
			if (PawnOverlapped)
			{
				OverlapActors.AddUnique(PawnOverlapped);
			}
		}
	}

	FVector MeteorSpawnLocation = ConePoint->GetActorLocation();
	MeteorSpawnLocation += ConePoint->GetActorUpVector() * 100.0f;
	Meteor = GetWorld()->SpawnActor<AActor>(MeteorClass, MeteorSpawnLocation, ConePoint->GetActorRotation());
	ConePoint->Destroy();


	OverlapActors.Add(Meteor);
	FGameplayAbilityTargetDataHandle TargetData = StartLocation.MakeTargetDataHandleFromActors(OverlapActors);
	TargetDataReadyDelegate.Broadcast(TargetData);
}

void AMyGATargetActor::Tick(float DeltaSeconds)
{
	
	Super::Tick(DeltaSeconds);

	//��ȡLookLocation��
	FVector LookLocation;
	GetPlayerLookingPoint(LookLocation);

	//Ȼ�����ConePoint��λ��Ϊ���߿����λ��
	ConePoint->SetActorLocation(LookLocation);
}

bool AMyGATargetActor::GetPlayerLookingPoint(FVector& LookingPoint)
{
	// Get Player View Vector and View Rotation
	FVector ViewVector;
	FRotator ViewRotation;
	if (PrimaryPC)
		PrimaryPC->GetPlayerViewPoint(ViewVector, ViewRotation);

	FCollisionQueryParams QueryParams;
	QueryParams.bTraceComplex = false;
	if (SourceActor)
	{
		QueryParams.AddIgnoredActor(SourceActor->GetUniqueID());
	}

	FHitResult HitResult;

	bool TryTrace = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		ViewVector,
		ViewVector + ViewRotation.Vector() * 10000.0f,
		ECollisionChannel::ECC_Visibility,
		QueryParams);

	if (TryTrace)
	{
		LookingPoint = HitResult.ImpactPoint;
	}
	else
	{
		LookingPoint = FVector::ZeroVector;
	}

	return TryTrace;
}
