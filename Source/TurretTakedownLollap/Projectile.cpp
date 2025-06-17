// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectile::AProjectile()
{
// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = false;
  // Create and set scene root
  RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
  SetRootComponent(RootScene);
  ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
  ProjectileMesh->SetupAttachment(RootScene);
 /* ProjectileMesh->SetRelativeLocation(FVector::ZeroVector);*/

  // Enable proper collision
  ProjectileMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
  ProjectileMesh->SetCollisionProfileName(TEXT("BlockAllDynamic"));
  ProjectileMesh->SetNotifyRigidBodyCollision(true);
	
  ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
  ProjectileMovementComponent->MaxSpeed = 3000.0f; // Set the maximum speed of the projectile
  ProjectileMovementComponent->InitialSpeed = 3000.0f; // Set the initial speed of the projectile
  ProjectileMovementComponent->bRotationFollowsVelocity = true;  // Make the projectile rotate with its velocity
  ProjectileMovementComponent->bShouldBounce = false; // Disable bouncing for this projectile

 // Set the lifespan of the projectile to 3 seconds
  InitialLifeSpan = 2.0f;

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	// Function Bond to the OnHit event of the projectile mesh
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	/*UE_LOG(LogTemp, Warning, TEXT("Projectile velocity: %s"), *ProjectileMovementComponent->Velocity.ToString());*/
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Check if the hit component is valid
	auto MyOwner = GetOwner();
	// Check if the owner is valid
	if (MyOwner == nullptr) return;
	// Get the instigator controller from the owner of the projectile
	auto MyOwnerInstigator = MyOwner->GetInstigatorController();

	auto DamageTypeClass = UDamageType::StaticClass(); // Use the default damage type

	if (OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		// Apply damage to the other actor
		UGameplayStatics::ApplyDamage(OtherActor, DamageAmount, MyOwnerInstigator, this, DamageTypeClass);
		Destroy(); // Destroy the projectile after hitting
	}

	UE_LOG(LogTemp, Warning, TEXT("OnHit"));
	UE_LOG(LogTemp, Warning, TEXT("OnHit: %s"), *HitComp->GetName());
	UE_LOG(LogTemp, Warning, TEXT("OnHit: %s"), *OtherActor->GetName());
	UE_LOG(LogTemp, Warning, TEXT("OnHit: %s"), *OtherComp->GetName());

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

