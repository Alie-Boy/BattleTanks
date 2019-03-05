// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "SprungWheel.h"
#include "SpawnPoint.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTankTrack::SetThrottle(float RelativeThrottle)
{
	float CurrentThrottle = FMath::Clamp<float>(RelativeThrottle, -1.f, +1.f);
	DriveTrack(CurrentThrottle);
}

void UTankTrack::DriveTrack(float CurrentThrottle)
{
	float ForceApplied = CurrentThrottle * TrackMaxDrivingForce;
	TArray<ASprungWheel*> Wheels = GetWheels();
	float ForcePerWheel = ForceApplied / Wheels.Num();
	for (ASprungWheel* Wheel : Wheels)
	{
		Wheel->SetDrivingForce(ForcePerWheel);
	}
}

TArray<ASprungWheel*> UTankTrack::GetWheels() const
{
	TArray<USceneComponent*> Children;
	TArray<ASprungWheel*> Wheels;
	GetChildrenComponents(true, Children);
	for (USceneComponent* Child : Children)
	{
		USpawnPoint* SpawnPoint = Cast<USpawnPoint>(Child);
		if (!SpawnPoint) continue;

		AActor* SpawnedActor = SpawnPoint->GetSpawnedActor();
		ASprungWheel* SprungWheel = Cast<ASprungWheel>(SpawnedActor);
		if (!SprungWheel) continue;
		Wheels.Add(Cast<ASprungWheel>(SprungWheel));
	}

	return Wheels;
}
