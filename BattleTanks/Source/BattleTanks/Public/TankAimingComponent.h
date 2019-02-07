// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


class AProjectile;


UENUM()
enum class EFiringStatus : uint8 {
	NoAmmo,
	Locked,
	Aiming,
	Reloading
};

class UTankBarrel;
class UTankTurret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBP;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "Aiming")
	EFiringStatus FiringState = EFiringStatus::Reloading;

public:

	UFUNCTION(BlueprintCallable, Category = "Firing")
	int32 GetAmmoCount() const;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AimAt(FVector AimLocation);

	EFiringStatus GetFiringState() const;

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();
	
	void MoveBarrelTowards(FVector AimDirection);
private:

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	int32 AmmoCount = 5;

	bool IsBarrelMoving() const;

	FVector AimDirection = FVector();

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ProjectileSpeed = 4000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float AimTolerance = 0.001f;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTime = 3.f; // default

	double PreviousFireTime = 0;

	UTankTurret* Turret = nullptr;

	UTankBarrel* Barrel = nullptr;

};
