// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AProjectile::AProjectile()
{
// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
PrimaryActorTick.bCanEverTick = false;

ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
RootComponent = ProjectileMesh;
	
ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
ProjectileMovementComponent->MaxSpeed = 3000.0f; // Set the maximum speed of the projectile
ProjectileMovementComponent->InitialSpeed = 3000.0f; // Set the initial speed of the projectile

ProjectileMovementComponent->bRotationFollowsVelocity = true;  // Make the projectile rotate with its velocity
ProjectileMovementComponent->bShouldBounce = false; // Disable bouncing for this projectile
	// Set the lifespan of the projectile to 3 seconds
	InitialLifeSpan = 3.0f;

	ProjectileMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogTemp, Warning, TEXT("Projectile velocity: %s"), *ProjectileMovementComponent->Velocity.ToString());
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

