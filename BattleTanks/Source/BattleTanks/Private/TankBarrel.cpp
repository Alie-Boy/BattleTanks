// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"



void UTankBarrel::Elevate(float DegreesPerSecond)
{
	// move barrel's direction towards launch direction slowly
	UE_LOG(LogTemp, Warning, TEXT("Barrel->Elevate(%f) called"), DegreesPerSecond);
		// with a constant speed per frame.
}
