// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::BeginPlay()
{
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	float StrafeSlipSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	FVector AntiSlipAccel = -StrafeSlipSpeed / DeltaTime * GetRightVector();
	UStaticMeshComponent* TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	FVector AntiSlipForce = AntiSlipAccel * (TankRoot->GetMass()) / 2; // 2 is used to nullify the effect of double retardation
	TankRoot->AddForce(AntiSlipForce);								   // because of two tracks.
}

void UTankTrack::SetThrottle(float RelativeThrottle)
{
	RelativeThrottle = FMath::Clamp<float>(RelativeThrottle, -1.f, +1.f);
	auto ForceApplied = GetForwardVector() * RelativeThrottle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& OutHit)
{
	UE_LOG(LogTemp, Warning, TEXT("%s hitting ground."), *GetName());
}


