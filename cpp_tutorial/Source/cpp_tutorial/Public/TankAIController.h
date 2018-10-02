// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
//#include "Tank.h"

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
class UTankAimingComponent;

UCLASS()
class CPP_TUTORIAL_API ATankAIController : public AAIController
{
	GENERATED_BODY()
protected:

	UTankAimingComponent* GetAimingController() const;

	//How close can the AI tank get to the player
	UPROPERTY(EditDefaultsOnly, Category = "Movement")
		float AcceptanceRadius = 8000;
	
private:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
};
