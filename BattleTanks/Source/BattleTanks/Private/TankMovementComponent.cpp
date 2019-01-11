// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"


void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float RelativeDirection)
{
	//FString Name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("Track direction: %f"), RelativeDirection);
}
