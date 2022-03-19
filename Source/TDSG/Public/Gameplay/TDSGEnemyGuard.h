// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TDSGEnemyGuard.generated.h"

UCLASS()
class TDSG_API ATDSGEnemyGuard : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATDSGEnemyGuard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = Movement)
		float RotationRate;

	float DeltaRotation;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Returns the duration for rotation
	UFUNCTION(BlueprintCallable, Category = Movement)
		float LookAt(FVector PointToLook);

	UFUNCTION(BlueprintCallable, Category = Movement)
		FORCEINLINE float GetRotationRate() { return RotationRate; };
};
