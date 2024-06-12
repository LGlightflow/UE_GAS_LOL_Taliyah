// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Bullet.h"
#include "Components/SphereComponent.h"
// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SphereCollision = CreateDefaultSubobject<USphereComponent>("ShpereCollision");
	SphereCollision->InitSphereRadius(10.0f);
	SetRootComponent(SphereCollision);

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponent");
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
	MovementComponent->Velocity = GetActorForwardVector() * MovementComponent->InitialSpeed;
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

