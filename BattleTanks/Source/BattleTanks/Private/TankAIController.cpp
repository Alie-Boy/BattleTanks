// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "GameFramework/Actor.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	bool IsReloaded = (GetWorld()->GetTimeSeconds() - PreviousFireTime) > ReloadTime;

	ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	ATank* ControlledTank = Cast<ATank>(GetPawn());

	ControlledTank->AimAt(PlayerTank->GetActorLocation());

	MoveToActor(PlayerTank, AcceptanceRadius);
	if (ensure(PlayerTank) && IsReloaded)
	{
		ControlledTank->Fire();
		PreviousFireTime = GetWorld()->GetTimeSeconds();
	}
}
