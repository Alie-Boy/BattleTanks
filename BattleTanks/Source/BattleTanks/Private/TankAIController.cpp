// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "GameFramework/Actor.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	if (GetPlayerTank())
	{
		FString AITankName = GetControlledTank()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("%s found %s"), *AITankName, *(GetPlayerTank()->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AITank can't find Player"));
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	APawn* PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerTank) { return nullptr; }
	return Cast<ATank>(PlayerTank);
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector PlayerTankLocation;
	if (GetPlayerTank())
	{
		PlayerTankLocation = GetPlayerTank()->GetActorLocation();
		GetControlledTank()->AimAt(PlayerTankLocation);
	}
}
