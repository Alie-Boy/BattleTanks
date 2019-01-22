// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"
#include "Engine/World.h"
#include "CollisionQueryParams.h"
#include <TankAimingComponent.h>
//#include "DrawDebugHelpers.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UTankAimingComponent* TankAimingComp = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(TankAimingComp)) {FoundAimingComponent(TankAimingComp);}
	else UE_LOG(LogTemp, Warning, TEXT("Tank Aiming Component could not be found in Begin Play"));
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
		GetControlledTank()->AimAt(HitLocation);
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

//	DrawDebugLine(GetWorld(), StartingPoint, LookDirection * LineTraceRange, FColor(255, 0, 0));

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


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn() );
}


