// Fill out your copyright notice in the Description page of Project Settings.


#include "MG_Turret.h"
#include "TurretTakedownLollapCharacter.h"
#include "Kismet/GameplayStatics.h"

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


}
