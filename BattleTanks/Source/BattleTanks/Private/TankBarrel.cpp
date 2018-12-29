// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"



void UTankBarrel::Elevate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	float DeltaElevation = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float NewElevation = RelativeRotation.Pitch + DeltaElevation;
	float Elevation = FMath::Clamp<float>(NewElevation, MinElevation, MaxElevation);
	SetRelativeRotation(FRotator(Elevation, 0.f, 0.f));
}
