// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"


class UProjectileMovementComponent;
class UParticleSystemComponent;
class URadialForceComponent;

UCLASS()
class BATTLETANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// When projectile hits something, destroy it after DestroyDelay secs
	UPROPERTY(EditDefaultsOnly)
	float DestroyDelay = 5.f;

	UPROPERTY(EditDefaultsOnly)
	float ProjectileDamage = 20.f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void LaunchProjectile(float Speed);

private:
	UProjectileMovementComponent* ProjectileMovementComponent = nullptr;
	
	UPROPERTY(VisibleAnywhere, Category="Particle")
	UStaticMeshComponent*     CollisionMesh    = nullptr;
	
	// Reference to trail particle effect.
	UPROPERTY(VisibleAnywhere, Category = "Particle")
	UParticleSystemComponent* LaunchBlast      = nullptr;

	// Reference to Explosion effect which occurs after hitting something.
	UPROPERTY(VisibleAnywhere, Category = "Particle")
	UParticleSystemComponent* ImpactBlast      = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Particle")
	URadialForceComponent*    ExplosionForce   = nullptr;

	UFUNCTION()
	void DestroyProjectile();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
				FVector NormalImpulse, const FHitResult& OutHit);
};
