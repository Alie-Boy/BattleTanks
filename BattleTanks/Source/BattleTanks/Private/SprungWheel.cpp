// Fill out your copyright notice in the Description page of Project Settings.

#include "SprungWheel.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Components/SphereComponent.h"


// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostPhysics;

	MassAxleConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("MassAxleConstraint"));
	SetRootComponent(MassAxleConstraint); 

	Axle = CreateDefaultSubobject<USphereComponent>(FName("Axle"));
	Axle->SetupAttachment(MassAxleConstraint);

	AxleWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("AxleWheelConstraint"));
	AxleWheelConstraint->SetupAttachment(Axle);

	Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	Wheel->SetupAttachment(Axle);
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	SetpConstraints();

	Wheel->SetNotifyRigidBodyCollision(true);	// wheel can generate hit events? true
	Wheel->OnComponentHit.AddDynamic(this, &ASprungWheel::OnHit);
}

void ASprungWheel::SetpConstraints()
{
	if (!GetAttachParentActor()) return;
	UPrimitiveComponent* RootComp = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	if (!RootComp) return;
	MassAxleConstraint->SetConstrainedComponents(RootComp, NAME_None, Axle, NAME_None);
	AxleWheelConstraint->SetConstrainedComponents(Axle, NAME_None, Wheel, NAME_None);
}

void ASprungWheel::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
		Wheel->AddForce(Axle->GetForwardVector() * ForceMagnitude);
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetWorld()->TickGroup == TG_PostPhysics) 
	{
		ForceMagnitude = 0.f;
	}
}

void ASprungWheel::SetDrivingForce(float ForcePerWheel)
{
	ForceMagnitude = ForceMagnitude + ForcePerWheel;
}

