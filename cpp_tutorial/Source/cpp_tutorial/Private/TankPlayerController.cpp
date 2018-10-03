// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"

void ATankPlayerController::BeginPlay() 
{
	Super::BeginPlay();

	auto AimingComponent = GetAimingController();
	if (!ensure(AimingComponent)) { return; }
	FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

UTankAimingComponent * ATankPlayerController::GetAimingController() const
{
	if (!ensure(GetPawn())) { return false; }
	return GetPawn()->FindComponentByClass<UTankAimingComponent>();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!ensure(GetAimingController())) { return; }

	FVector HitLocation; // out parameter
	bool bGotHitLocation = GetSightRayHitLocation(HitLocation);
	if (bGotHitLocation)
	{
		GetAimingController()->AimAt(HitLocation);
	}
}

//Get work location of linetrace through crosshair if it hits the landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector &OutHitLocation) const
{
	//Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	//deproject the scren position of the crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		return GetLookVectorHitLocation(LookDirection, OutHitLocation);
	}

	return false;
}

//line trace along that look direction, and see what we hit
bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector &HitLocation) const
{
	FHitResult HitResult;
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();

	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		StartLocation + (LookDirection * LineTraceRange),
		ECC_Visibility))
	{
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0, 0, 0);
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation;  //TODO discard
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		LookDirection);
}
