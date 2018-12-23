// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


class UTankBarrel;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Barrel only changes its elevation
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	// TODO SetTurretReference needed for Rotation

	void AimAt(FVector AimLocation, float ProjectileSpeed);
	
	void MoveBarrelTowards(FVector AimDirection);
private:


	UTankBarrel* Barrel = nullptr;

};
