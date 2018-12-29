// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Kismet/GameplayStatics.h"


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

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::AimAt(FVector AimLocation, float ProjectileSpeed)
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
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't find launch direction."));
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	FRotator BarrelRotation = Barrel->GetForwardVector().Rotation();
	FRotator AimRotation = AimDirection.Rotation();
	// get difference between barrels direction and launch direction
	FRotator DeltaRotation = AimRotation - BarrelRotation;
	
	Barrel->Elevate(DeltaRotation.Pitch);
}

