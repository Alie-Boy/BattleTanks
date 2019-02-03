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
	float AcceptanceRadius = 2000.f;

public:
	virtual void Tick(float DeltaTime) override;
};
