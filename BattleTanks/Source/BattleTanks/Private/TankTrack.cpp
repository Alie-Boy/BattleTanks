// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"


void UTankTrack::SetThrottle(float RelativeThrottle)
{
	RelativeThrottle = FMath::Clamp<float>(RelativeThrottle, -1.f, +1.f);
	auto ForceApplied = GetForwardVector() * RelativeThrottle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

