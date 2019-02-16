// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}


float ATank::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(Damage);
	int32 DamageToApply = FMath::Clamp<int32>(DamagePoints, 0.f, CurrentHealth);
	CurrentHealth -= DamageToApply;

	if (CurrentHealth <= 0)
		UE_LOG(LogTemp, Warning, TEXT("Tank died."));

	return DamageToApply;
}

float ATank::GetHealthPercent() const
{
	return (static_cast<float>(CurrentHealth) / static_cast<float>(StartingHealth));
}

