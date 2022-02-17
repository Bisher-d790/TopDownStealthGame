// Copyright Epic Games, Inc. All Rights Reserved.

#include "EnemyGuardsGameMode.h"
#include "EnemyGuardsPlayerController.h"
#include "EnemyGuardsCharacter.h"
#include "UObject/ConstructorHelpers.h"

AEnemyGuardsGameMode::AEnemyGuardsGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AEnemyGuardsPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}