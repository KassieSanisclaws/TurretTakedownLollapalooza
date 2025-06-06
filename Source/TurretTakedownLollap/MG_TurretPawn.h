// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MG_TurretPawn.generated.h"

// Forward declaration of the MG_TurretPawn class
class UStaticMeshComponent;
class UPawnSensingComponent;

UCLASS()
class TURRETTAKEDOWNLOLLAP_API AMG_TurretPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMG_TurretPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    
	// Function to handle sensing of pawns
	UFUNCTION()
	void OnPawnSeen(APawn* SeenPawn);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Mesh component for the turret for visual representation
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UPawnSensingComponent* PawnSensingComp;

};
