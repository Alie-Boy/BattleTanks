// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "CollisionQueryParams.h"
#include <TankAimingComponent.h>

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	TankAimingComp = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(TankAimingComp))
	{
		FoundAimingComponent(TankAimingComp);
	}
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
		GetLookVectorHitLocation(OutHitLocation, LookDirection);
	}


	return true;
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

void ATankPlayerController::GetLookVectorHitLocation(FVector & OutHitLocation, FVector LookDirection) const
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
			ECC_Visibility,
			QueryParams,
			ResponeParams)
		)
	{
		OutHitLocation = HitResult.Location;
	}
}
