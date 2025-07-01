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

	FString Name = GetName();

	UE_LOG(LogTemp, Display, TEXT("Configured Move Distance: %f"), MoveDistance);
	UE_LOG(LogTemp, Warning, TEXT("Name: %s"), *Name);
	UE_LOG(LogTemp, Error, TEXT("Your message"));
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
}

void AMovingPlatform::MovePlatform(float DeltaTime)
{
	if (ShouldPlatformReturn())
	{
		float OverShoot = GetDistanceMoved() - MoveDistance;
		UE_LOG(LogTemp, Display, TEXT("\"%s\" OverShoot: %f"), *GetName(), OverShoot);

		FVector Direction = Velocity.GetSafeNormal();
		StartLocation += Direction * MoveDistance;
		SetActorLocation(StartLocation);

		Velocity = -Velocity;
	}
	else
	{
		FVector Location = GetActorLocation();
		Location += Velocity * DeltaTime;

		SetActorLocation(Location);

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("%f"), GetDistanceMoved()));
	}
}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	AddActorLocalRotation(RotationVelocity * DeltaTime);
}

bool AMovingPlatform::ShouldPlatformReturn() const
{
	return GetDistanceMoved() >= MoveDistance;
}

float AMovingPlatform::GetDistanceMoved() const
{
	return FVector::Dist(StartLocation, GetActorLocation());
}

