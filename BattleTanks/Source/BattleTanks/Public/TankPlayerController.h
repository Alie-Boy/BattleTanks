// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:

	UTankAimingComponent* TankAimingComp;

	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 100000.f;

	UPROPERTY(EditDefaultsOnly)
	float CrosshairXLocation = 0.5f;
	
	UPROPERTY(EditDefaultsOnly)
	float CrosshairYLocation = 0.387f;

protected:

	UFUNCTION(BlueprintImplementableEvent)
	void FoundAimingComponent(UTankAimingComponent* TankAimingComp);

private:

	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector & LookDirection) const;

	void GetLookVectorHitLocation(FVector & OutHitLocation, FVector LookDirection) const;

public:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

};
