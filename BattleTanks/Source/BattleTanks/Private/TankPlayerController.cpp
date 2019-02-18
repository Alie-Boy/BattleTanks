// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "CollisionQueryParams.h"
#include <TankAimingComponent.h>
#include "Tank.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	TankAimingComp = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(TankAimingComp))
	{
		FoundAimingComponent(TankAimingComp);
	}
}

void ATankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		ATank* PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnTankDeath);
	}
}

void ATankPlayerController::OnTankDeath()
{
	StartSpectatingOnly();
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick( DeltaTime );
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		TankAimingComp->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector & OutHitLocation) const
{
	int32 ViewportSizeX, ViewPortSizeY;
	GetViewportSize(ViewportSizeX, ViewPortSizeY);

	FVector2D ScreenLocation;
	ScreenLocation = FVector2D(
		ViewportSizeX * CrosshairXLocation,
		ViewPortSizeY * CrosshairYLocation
	);

	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		return GetLookVectorHitLocation(OutHitLocation, LookDirection);
	}

	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector & LookDirection) const
{
	FVector CameraLocation;  /// waste, but don't delete

	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraLocation,
		LookDirection
	);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector & OutHitLocation, FVector LookDirection) const
{
	FHitResult HitResult;
	FVector StartingPoint = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartingPoint + (LookDirection * LineTraceRange);
	FCollisionQueryParams QueryParams = FCollisionQueryParams(TEXT(""), false, this);
	FCollisionResponseParams ResponeParams = FCollisionResponseParams();

	if (GetWorld()->LineTraceSingleByChannel(
			HitResult,
			StartingPoint,
			EndLocation,
			ECC_Camera,
			QueryParams,
			ResponeParams)
		)
	{
		OutHitLocation = HitResult.Location;
		return true;
	}
	OutHitLocation = FVector(0.f);
	return false;
}
