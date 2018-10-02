// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
//Depends on movement component via pathfinding

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

UTankAimingComponent * ATankAIController::GetAimingController() const
{
	return GetPawn()->FindComponentByClass<UTankAimingComponent>();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = GetPawn();

	if (PlayerTank)
	{
		// TODO Move towards player
		MoveToActor(PlayerTank, AcceptanceRadius); //TODO check radius is in cm
		// Aim towards the player
		GetAimingController()->AimAt(PlayerTank->GetActorLocation());

		if(GetAimingController()->GetFiringState() == EFiringStatus::Locked)
		{
			GetAimingController()->Fire(); //TODO limit firing rate
		}
	}
}