// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"


void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float RelativeDirection)
{
	LeftTrack->SetThrottle(RelativeDirection/2);
	RightTrack->SetThrottle(RelativeDirection/2); 
}

void UTankMovementComponent::IntendRotateClockwise(float RelativeDirection)
{
	LeftTrack->SetThrottle(RelativeDirection);
	RightTrack->SetThrottle(-RelativeDirection);
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	FVector  TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector MoveDirectionIntention = MoveVelocity.GetSafeNormal();
//	UE_LOG(LogTemp, Warning, TEXT("%s trying to go to %s"), *Name, *MoveDirection);

	float RelativeForwardIntent = FVector::DotProduct(TankForward,  MoveDirectionIntention);
	IntendMoveForward(RelativeForwardIntent);

	FVector RelativeRotateIntent = FVector::CrossProduct(MoveDirectionIntention, TankForward);
	IntendRotateClockwise(RelativeRotateIntent.Z);
}
