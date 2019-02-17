// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "GameFramework/Actor.h"
#include "TankAimingComponent.h"
#include "Tank.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	TankAimingComp = GetPawn()->FindComponentByClass<UTankAimingComponent>();
}


void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		ATank* PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
	}
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

void ATankAIController::OnTankDeath()
{
	FString TankName = Cast<ATank>(GetPawn())->GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s died."), *TankName);
}
