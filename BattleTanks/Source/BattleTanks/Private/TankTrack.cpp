// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTankTrack::ReduceSidewaysForce()
{
	float StrafeSlipSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	float DeltaTime = GetWorld()->GetDeltaSeconds();
	FVector AntiSlipAccel = -StrafeSlipSpeed / DeltaTime * GetRightVector();
	UStaticMeshComponent* TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	FVector AntiSlipForce = AntiSlipAccel * (TankRoot->GetMass()) / 2; // 2 is used to nullify the effect of double retardation
	TankRoot->AddForce(AntiSlipForce);								   // because of two tracks.
}

void UTankTrack::SetThrottle(float RelativeThrottle)
{
	Throttle = FMath::Clamp<float>(RelativeThrottle+Throttle, -1.f, +1.f);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& OutHit)
{
	DriveTrack();
	ReduceSidewaysForce();
	Throttle = 0;
}

void UTankTrack::DriveTrack()
{
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
