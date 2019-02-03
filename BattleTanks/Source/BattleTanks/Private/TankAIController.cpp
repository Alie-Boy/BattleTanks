// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "GameFramework/Actor.h"
#include "TankAimingComponent.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	TankAimingComp = GetPawn()->FindComponentByClass<UTankAimingComponent>();
}


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APawn* PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!ensure(TankAimingComp)) { return; }
	TankAimingComp->AimAt(PlayerTank->GetActorLocation());

	MoveToActor(PlayerTank, AcceptanceRadius);

	if (TankAimingComp->GetFiringState() == EFiringStatus::Locked)
	{
		TankAimingComp->Fire();
	}
}
