// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	PreviousFireTime = GetWorld()->GetTimeSeconds();
}

int32 UTankAimingComponent::GetAmmoCount() const { return AmmoCount; }

void UTankAimingComponent::Initialise(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetAmmoCount() <= 0)				// Ammo check must be done firstly
		FiringState = EFiringStatus::NoAmmo;
	else if ((GetWorld()->GetTimeSeconds() - PreviousFireTime) < ReloadTime)
		FiringState = EFiringStatus::Reloading;
	else if (IsBarrelMoving())
		FiringState = EFiringStatus::Aiming;
	else
		FiringState = EFiringStatus::Locked;
}

void UTankAimingComponent::AimAt(FVector AimLocation)
{
	FVector OutProjectileVelocity(0.f);
	FVector StartingLocation = Barrel->GetSocketLocation(FName("ProjectileSpawn"));

	if (UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutProjectileVelocity,
		StartingLocation,
		AimLocation,
		ProjectileSpeed,
		false,
		0.f,
		0.f,
		ESuggestProjVelocityTraceOption::DoNotTrace)
		)
	{
		FVector AimDirection = OutProjectileVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
}

EFiringStatus UTankAimingComponent::GetFiringState() const { return FiringState; }

void UTankAimingComponent::MoveBarrelTowards(FVector HitDirection)
{
	AimDirection = HitDirection;
	if (!(ensure(Barrel) && ensure(Turret))) { return; }

	FRotator BarrelRotation = Barrel->GetForwardVector().Rotation();
	FRotator AimRotation = HitDirection.Rotation();
	// get difference between barrels direction and launch direction
	FRotator DeltaRotation = AimRotation - BarrelRotation;

	Barrel->Elevate(DeltaRotation.GetNormalized().Pitch);

	Turret->Rotate(DeltaRotation.GetNormalized().Yaw);

}

bool UTankAimingComponent::IsBarrelMoving() const
{
	if (!ensure(Barrel)) { return false; };
	if (Barrel->GetForwardVector().GetSafeNormal().Equals(AimDirection.GetSafeNormal(), AimTolerance))
		return false;

	return true;
}

void UTankAimingComponent::Fire()
{
	if (ensure(Barrel) && (FiringState != EFiringStatus::Reloading) && (FiringState != EFiringStatus::NoAmmo))
	{
		if (!ensure(ProjectileBP)) { return; }
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBP,
			Barrel->GetSocketTransform(FName("ProjectileSpawn")));

		Projectile->LaunchProjectile(ProjectileSpeed);

		PreviousFireTime = GetWorld()->GetTimeSeconds();

		AmmoCount--;
	}
}