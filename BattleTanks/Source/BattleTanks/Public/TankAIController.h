// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class UTankAimingComponent;

UCLASS()
class BATTLETANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
private:
	virtual void BeginPlay() override;

	UTankAimingComponent* TankAimingComp;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000.f;

	float AcceptanceRadius = 2000.f;

	float ReloadTime = 3.f; // default

	double PreviousFireTime = 0;

public:
	virtual void Tick(float DeltaTime) override;
};
