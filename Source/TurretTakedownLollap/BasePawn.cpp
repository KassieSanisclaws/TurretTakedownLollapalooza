// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"
#include "Projectile.h"
#include <Kismet/GameplayStatics.h>
#include "GameFramework/Character.h" // Include this to resolve the incomplete type error for ACharacter
#include "GameFramework/ProjectileMovementComponent.h"

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

	// Testing Dummy Root to fix rotation on turret from model import into engine:
	TurretRotationRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Turret Rotation Root"));
	TurretRotationRoot->SetupAttachment(BaseMesh);

	// Attach turret mesh to the dummy root instead of directly to the BaseMesh directly:
	TurretMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMeshComp->SetupAttachment(TurretRotationRoot);
	//TurretMeshComp->SetRelativeLocation(FVector(0.f, 3223.0f, 1441.0f)); // Adjust height if needed

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

// HandleDestroyed is called when the pawn is destroyed
void ABasePawn::HandleDestruction()
{
	// TODO: Handle Pawnm visual/sound effects here:

	UE_LOG(LogTemp, Warning, TEXT("Base Pawn destroyed!"));
}

void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	FVector ToTarget = LookAtTarget - TurretRotationRoot->GetComponentLocation();
	FRotator LookAtRotation = ToTarget.Rotation();
	LookAtRotation.Roll = 0.0f; // Keep the roll at 0 to avoid tilting the turret sideways.
	LookAtRotation.Pitch = 0.0f; // Keep the pitch at 0 to avoid tilting the turret up or down.
	// Rotate the turret mesh to face the target
	LookAtRotation.Yaw += -90.0f;
	BaseMesh->SetWorldRotation(LookAtRotation);

}

void ABasePawn::FireProjectile()
{
   // Get the spawn location of the projectile
	FVector ProjectileSpawnLocation = ProjectileSpawnPointComp->GetComponentLocation();
   // Get the player character to aim at
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);  
	if (!PlayerCharacter || !ProjectileClass || !ProjectileSpawnPointComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to fire projectile: PlayerCharacter or ProjectileClass is null!"));
		return;
	}

	FVector TargetLoc = PlayerCharacter->GetActorLocation();
	FVector ToTarget = (TargetLoc - ProjectileSpawnLocation).GetSafeNormal();
	FRotator FireRotation = ToTarget.Rotation();

	// SPawn the projectile at the spawn location with the specified rotation
	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnLocation, FireRotation);
	
	if(Projectile && Projectile->GetProjectileMovementComponent()) {
	  // Set the projectile velocitry manually after spawning
		Projectile->GetProjectileMovementComponent()->Velocity = ToTarget * Projectile->GetProjectileMovementComponent()->InitialSpeed;
        Projectile->SetOwner(this); // Set the owner of the projectile to this pawn
		UE_LOG(LogTemp, Warning, TEXT("Projectile spawned successfully at location: %s"), *ProjectileSpawnLocation.ToString());
	}

	Projectile->SetOwner(this); // Set the owner of the projectile to this pawn

	// Visual debug
	DrawDebugLine(
		GetWorld(), 
		ProjectileSpawnLocation, 
		TargetLoc, 
		FColor::Turquoise, 
		false, 
		1.5f, 
		0, 
		2.f
	);

}

