// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	if (BarrelToSet)
	{
		TankAimingComponent->SetBarrelReference(BarrelToSet);
		Barrel = BarrelToSet;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("SetBarrelReference has no valid Barrel To Set."));
	}
	
}

void ATank::SetTurretReference(UTankTurret * TurretToSet)
{
	if (TurretToSet)
	{
		TankAimingComponent->SetTurretReference(TurretToSet);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("SetTurretReference has no valid Turret To Set."));
	}

}

void ATank::Fire()
{
	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBP,
																  Barrel->GetSocketTransform(FName("ProjectileSpawn")));
	Projectile->LaunchProjectile(LaunchSpeed);
}

void ATank::AimAt(FVector HitLocation)
{
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

