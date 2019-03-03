// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"

class UPhysicsConstraintComponent;
class USphereComponent;

UCLASS()
class BATTLETANKS_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASprungWheel();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddDrivingForce(float ForceMagnitude);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetpConstraints();

private:

	UPROPERTY(VisibleAnywhere, Category = "Spring")
	UPhysicsConstraintComponent* MassAxleConstraint = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Spring")
	USphereComponent* Axle = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Spring")
	UPhysicsConstraintComponent* AxleWheelConstraint = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Spring")
	USphereComponent* Wheel = nullptr;
};
