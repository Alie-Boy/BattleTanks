// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Elevate(float RelativeSpeed);
	
private:
	
	UPROPERTY(EditAnywhere, Category = "Barrel Movement Setup")
	float MaxDegreesPerSecond = 7.f;

	UPROPERTY(EditAnywhere, Category = "Barrel Movement Setup")
	float MaxElevation = 40.f;

	UPROPERTY(EditAnywhere, Category = "Barrel Movement Setup")
	float MinElevation = 0.f;
};
