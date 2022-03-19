// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/TDSGEnemyGuard.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ATDSGEnemyGuard::ATDSGEnemyGuard()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RotationRate = 5.f;
}

// Called when the game starts or when spawned
void ATDSGEnemyGuard::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ATDSGEnemyGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!FMath::IsNearlyZero(DeltaRotation))
	{
		FRotator Rotation = GetActorRotation();

		if (DeltaRotation > 0)
		{
			Rotation.Yaw = FMath::Clamp(DeltaRotation - RotationRate, 0, RotationRate);
			DeltaRotation -= Rotation.Yaw;
		}
		else
		{
			Rotation.Yaw = FMath::Clamp(RotationRate - DeltaRotation, -RotationRate, 0);
			DeltaRotation += Rotation.Yaw;
		}

		AddActorWorldRotation(Rotation);
	}
}

// Called to bind functionality to input
void ATDSGEnemyGuard::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ATDSGEnemyGuard::LookAt(FVector PointToLook)
{
	FRotator OriginalRotation = GetActorRotation();
	FRotator TargetRotation = OriginalRotation;

	TargetRotation.Yaw = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), PointToLook).Yaw;

	// Speed = Distance / Time
	DeltaRotation = TargetRotation.Yaw - OriginalRotation.Yaw;

	return FMath::Abs(RotationRate / DeltaRotation);
}