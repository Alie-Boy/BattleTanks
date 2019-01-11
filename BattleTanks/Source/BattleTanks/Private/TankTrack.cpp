// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"


void UTankTrack::SetThrottle(float RelativeThrottle)
{
	FString Name = GetName();
	UE_LOG(LogTemp, Error, TEXT("%s throttles at %f"), *Name, RelativeThrottle);
}

