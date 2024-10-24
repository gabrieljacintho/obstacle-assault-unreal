// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetActorLocation();
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Location = GetActorLocation();
	Location += Velocity * DeltaTime;

	SetActorLocation(Location);

	DistanceMoved = FVector::Dist(StartLocation, Location);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("%f"), DistanceMoved));

	if (DistanceMoved >= MoveDistance)
	{
		FVector Direction = Velocity.GetSafeNormal();
		StartLocation += Direction * MoveDistance;
		SetActorLocation(StartLocation);

		Velocity = -Velocity;
	}
}

