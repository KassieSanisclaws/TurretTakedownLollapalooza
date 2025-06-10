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

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	// Function Bond to the OnHit event of the projectile mesh
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	UE_LOG(LogTemp, Warning, TEXT("Projectile velocity: %s"), *ProjectileMovementComponent->Velocity.ToString());
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("OnHit: %s"), *OtherActor->GetName());

	DrawDebugSphere(
		GetWorld(), 
		Hit.ImpactPoint, 
		20.0f, 
		12, 
		FColor::Orange, 
		false, 
		2.0f
	);
}

