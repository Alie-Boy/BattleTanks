// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Player Controller is possessing the %s"), *GetControlledTank()->GetName());
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick( DeltaTime );
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	FVector HitLocation;
	if (!GetSightRayHitLocation(HitLocation))
	{
		// TODO: Log out error.
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector & OutHitLocation)
{
	// Ray Cast to see if line hits something
	
	// if true
		// store hitlocation with param OutHitLocation
		// return true
	// else
		// return false

	return false;
}


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn() );
}


