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
	FVector Location = GetActorLocation();
	Location += Velocity * DeltaTime;

	SetActorLocation(Location);

	DistanceMoved = FVector::Dist(StartLocation, Location);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("%f"), DistanceMoved));

	if (DistanceMoved >= MoveDistance)
	{
		float OverShoot = DistanceMoved - MoveDistance;
		UE_LOG(LogTemp, Display, TEXT("\"%s\" OverShoot: %f"), *GetName(), OverShoot);

		FVector Direction = Velocity.GetSafeNormal();
		StartLocation += Direction * MoveDistance;
		SetActorLocation(StartLocation);

		Velocity = -Velocity;
	}
}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	FRotator Rotator = GetActorRotation();
	Rotator.Yaw += RotateSpeed * DeltaTime;

	SetActorRotation(Rotator);

	UE_LOG(LogTemp, Display, TEXT("%s is rotating..."), *GetName());
}

