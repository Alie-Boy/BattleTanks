// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Player Controller is possessing the %s"), *GetControlledTank()->GetName());
}


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn() );
}


