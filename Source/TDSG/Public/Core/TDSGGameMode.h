// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TDSGGameMode.generated.h"

UCLASS(minimalapi)
class ATDSGGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATDSGGameMode();

	void OnPlayerDetected(class ATDSGCharacter* Player);

	UFUNCTION()
		void RestartLevel();

protected:
	UPROPERTY(EditDefaultsOnly, Category = Settings)
		float RestartLevelTimeout;
};



