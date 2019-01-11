// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"


void UTankTrack::SetThrottle(float RelativeThrottle)
{
	FString Name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s throttles at %f"), *Name, RelativeThrottle);

	auto ForceApplied = GetForwardVector() * RelativeThrottle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

