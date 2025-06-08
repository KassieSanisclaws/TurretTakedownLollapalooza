// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Create and set up components:
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

	TurretMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMeshComp->SetupAttachment(BaseMesh);

	ProjectileSpawnPointComp = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPointComp->SetupAttachment(TurretMeshComp);

}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	FVector TurretLocation = TurretMeshComp->GetComponentLocation();
	// Make LookAtTarget the same height as the turret to avoid pitching up/down
	FVector AdjustedTarget = FVector(LookAtTarget.X, LookAtTarget.Y, TurretLocation.Z);

	// Direction from turret to target (on same Z plane)
	FVector ToTarget = AdjustedTarget - TurretLocation;

	// Convert to rotation
	FRotator LookAtRotation = ToTarget.Rotation();

	// Apply only yaw rotation (so turret doesn't tilt)
	FRotator YawOnlyRotation(0.f, LookAtRotation.Yaw, 0.f);
	TurretMeshComp->SetWorldRotation(YawOnlyRotation);

	// Calculate the rotation needed to look at the target
	//FVector ToTarget = LookAtTarget - TurretMeshComp->GetComponentLocation();
	//FRotator LookAtRotation = ToTarget.Rotation();
	//LookAtRotation.Pitch = 0.0f; // Keep the pitch at 0 to avoid tilting the turret up or down.
	//LookAtRotation.Roll = 0.0f; // Keep the roll at 0 to avoid tilting the turret sideways.
	// Set the turret's rotation
	/*TurretMeshComp->SetWorldRotation(LookAtRotation);*/
}

