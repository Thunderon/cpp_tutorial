// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"
//enum for aiming states
UENUM()
enum class EFiringStatus : uint8
{
	Reloading,
	Aiming,
	Locked
};


UENUM()
enum class EAmmunitionStatus : uint8
{
	Available,
	OutOfAmmo
};

//Forward declaration
class UTankBarrel;
class UTankTurret;
class AProjectile;

//Holds barrel's property and elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPP_TUTORIAL_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet);

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void Fire();

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus FiringState = EFiringStatus::Reloading;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EAmmunitionStatus AmmoState = EAmmunitionStatus::Available;

	UFUNCTION(BlueprintCallable, Category = "Ticking")
	void ChangeCrosshairColor();

	UPROPERTY(BlueprintReadOnly, Category = "Firing")
	int32 ActualAmmo;

	EFiringStatus GetFiringState() const;
protected:


private:
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	bool IsBarrelMoving();

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000;

	UPROPERTY(EditAnywhere, Category = "Firing")
	int32 StartingAmmunition = 3;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 3;

	UTankBarrel* Barrel = nullptr;

	UTankTurret* Turret = nullptr;

	double LastFireTime = 0;

	FVector AimDirection;

	//Called to Move Barrel when aiming
	void MoveBarrelTowards(FVector AimDirection);
};
