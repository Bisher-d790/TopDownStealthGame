// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/TDSGEnemyGuard.h"

// Sets default values
ATDSGEnemyGuard::ATDSGEnemyGuard()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

}

// Called to bind functionality to input
void ATDSGEnemyGuard::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

