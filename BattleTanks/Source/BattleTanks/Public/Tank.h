// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelgate);

UCLASS()
class BATTLETANKS_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

private:
	
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float StartingHealth = 100.f;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
	float CurrentHealth = 0.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:

	FTankDelgate OnDeath;

	UFUNCTION(BlueprintPure, Category = "Setup")
	float GetHealthPercent() const;
};
