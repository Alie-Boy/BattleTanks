// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"


class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
private:
	virtual void BeginPlay() override;

	float ReloadTime = 3.f; // default

	UPROPERTY(EditDefaultsOnly)
	float AcceptanceRadius = 2000.f;

	double PreviousFireTime = 0;

public:
	virtual void Tick(float DeltaTime) override;
};
