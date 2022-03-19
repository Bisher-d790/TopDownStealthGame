// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/TDSGEnemyGuard.h"
#include "Kismet/KismetMathLibrary.h"
#include "Perception/PawnSensingComponent.h"
#include "Player/TDSGCharacter.h"
#include <AIController.h>
#include <Blueprint/AIBlueprintHelperLibrary.h>
#include "BehaviorTree/BehaviorTree.h"

// Sets default values
ATDSGEnemyGuard::ATDSGEnemyGuard()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("Pawn Sensing Component"));
	SensingComponent->OnSeePawn.AddDynamic(this, &ATDSGEnemyGuard::OnPawnDetected);

	RotationRate = 5.f;
}

// Called when the game starts or when spawned
void ATDSGEnemyGuard::BeginPlay()
{
	Super::BeginPlay();

	AIController = UAIBlueprintHelperLibrary::GetAIController(this);

	if (IsValid(AIController) && BehaviorTreeAsset)
		AIController->RunBehaviorTree(BehaviorTreeAsset);
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

void ATDSGEnemyGuard::OnPawnDetected(APawn* Pawn)
{
	ATDSGCharacter* PlayerPawn = Cast<ATDSGCharacter>(Pawn);

	if (!IsValid(PlayerPawn) || !PlayerPawn->IsLocallyControlled() || PlayerPawn->GetIsDetected())
		return;

	PlayerPawn->OnDetected(this);

	if (IsValid(AIController))
		AIController->StopMovement();

	OnPlayerDetectedFX(PlayerPawn);
}