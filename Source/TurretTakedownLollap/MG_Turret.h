// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "MG_Turret.generated.h"

/**
 * 
 */
UCLASS()
class TURRETTAKEDOWNLOLLAP_API AMG_Turret : public ABasePawn
{
	GENERATED_BODY()

public: 
	// Sets default values for this pawn's properties
	virtual void Tick(float DeltaTime) override;

protected: 
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private: 
	//class ATurret* Turret; // Pointer to the turret actor

	class ATurretTakedownLollapCharacter* PlayerCharacter; // Pointer to the player character
	
	UPROPERTY(EditDefaultsOnly, Category = "Combat" )
	float FireRange = 1000.0f; // Range at which the turret can fire
	float FireRate = 1.0f; // Rate at which the turret fires
};
