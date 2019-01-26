// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

protected:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintCallable)
	void SetThrottle(float RelativeThrottle);
	
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 400000.f;

private:

	UTankTrack();

	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
				FVector NormalImpulse, const FHitResult& OutHit);
};
