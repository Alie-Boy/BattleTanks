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
	
	ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	ATank* ControlledTank = Cast<ATank>(GetPawn());

	bool IsReloaded = (GetWorld()->GetTimeSeconds() - PreviousFireTime) > ReloadTime;
	ControlledTank->AimAt(PlayerTank->GetActorLocation());

	MoveToActor(PlayerTank, AcceptanceRadius);

	if (PlayerTank && IsReloaded)
	{	
		ControlledTank->Fire();
		PreviousFireTime = GetWorld()->GetTimeSeconds();
	}
}
