// Copyright Epic Games, Inc. All Rights Reserved.

#include "Core/TDSGGameMode.h"
#include "Player/TDSGPlayerController.h"
#include "Player/TDSGCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATDSGGameMode::ATDSGGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ATDSGPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if (PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}

	RestartLevelTimeout = 5.f;
}

void ATDSGGameMode::OnPlayerDetected(ATDSGCharacter* Player)
{
	FTimerHandle ResetHandle;

	GetWorldTimerManager().SetTimer(ResetHandle, this, &ATDSGGameMode::RestartLevel, RestartLevelTimeout, false);
}

void ATDSGGameMode::RestartLevel()
{
	RestartPlayer(GetWorld()->GetFirstPlayerController());
}