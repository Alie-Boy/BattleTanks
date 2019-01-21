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
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATank::Initialise(UTankBarrel * BarrelToSet, UTankAimingComponent * TankAimingToSet)
{
	Barrel = BarrelToSet;
	TankAimingComponent = TankAimingToSet;
}


// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

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

