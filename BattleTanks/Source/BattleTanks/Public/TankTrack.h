// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

class ASprungWheel;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

protected:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void BeginPlay() override;

public:

	UTankTrack();

	UFUNCTION(BlueprintCallable)
	void SetThrottle(float RelativeThrottle);

	void DriveTrack(float CurrentThrottle);

	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 40000000.f; //better default

private:

	TArray<ASprungWheel*> GetWheels() const;
};
