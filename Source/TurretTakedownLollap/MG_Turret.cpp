// Fill out your copyright notice in the Description page of Project Settings.


#include "MG_Turret.h"
#include "TurretTakedownLollapCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void AMG_Turret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

   // Find the distance to the character
	if (PlayerCharacter) 
	{
		float Distance = FVector::Dist(GetActorLocation(), PlayerCharacter->GetActorLocation());

	// Check to see if the turret can see the character
		if (Distance <= FireRange)
		{
		  // If the turret can see the character, rotate towards it
			RotateTurret(PlayerCharacter->GetActorLocation());
		}
	}

	if (InFiringRange())
	{
		RotateTurret(PlayerCharacter->GetActorLocation());
	}
}


void AMG_Turret::BeginPlay() 
{
	Super::BeginPlay();


	// Get the character
	PlayerCharacter = Cast<ATurretTakedownLollapCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (!PlayerCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("Turret: Player character not found!"));
		return;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Turret: Player character found!"));
	}

	// Initialize the turret's fire range
	GetWorldTimerManager().SetTimer(FireRateTimer, this,  &AMG_Turret::CheckFireConditions, FireRate, true);
}

void AMG_Turret::CheckFireConditions()
{
 	// Check if the turret can fire at the character
	if (PlayerCharacter)
	{
		float Distance = FVector::Dist(GetActorLocation(), PlayerCharacter->GetActorLocation());
		if (Distance <= FireRange)
		{
			// If the turret can fire, call the FireTurret function
			FireProjectile();
		}
	}

	if (InFiringRange())
	{
		FireProjectile();
	}
}


bool AMG_Turret::InFiringRange()
{
	if (PlayerCharacter)
	{
	   float Distance = FVector::Dist(GetActorLocation(), PlayerCharacter->GetActorLocation());
	   if (Distance <= FireRange)
	   {
		   UE_LOG(LogTemp, Warning, TEXT("Turret: SpawnPoint Location + Player character in Range! Fired Bullet"));

		   return true;
	   }  
	}
	return false;
}
