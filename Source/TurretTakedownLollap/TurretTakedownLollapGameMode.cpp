// Copyright Epic Games, Inc. All Rights Reserved.

#include "TurretTakedownLollapGameMode.h"
#include "TurretTakedownLollapCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATurretTakedownLollapGameMode::ATurretTakedownLollapGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}

void ATurretTakedownLollapGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == nullptr) return;
//	// Check if the dead actor is a player character
//	ATurretTakedownLollapCharacter* DeadCharacter = Cast<ATurretTakedownLollapCharacter>(DeadActor);
//	DeadCharacter->HandleDeath(); // Call the HandleDeath function on the character
//	
//	if (DeadCharacter)
//	{
//		// Handle player death logic here
//		// For example, respawn the player or end the game
//		DeadCharacter
//		UE_LOG(LogTemp, Warning, TEXT("Player %s has died!"), *DeadCharacter->GetName());
//	}
//	else
//	{
//		// Handle other actor deaths (e.g., enemies, NPCs)
//	}
//}
//
//void ATurretTakedownLollapGameMode::HandleDeath(AActor* DeadActor)
//{
//	if (DeadActor == nullptr) return;
//	// Call the ActorDied function to handle the death logic
//	ActorDied(DeadActor);
//	
//	// Additional death handling logic can be added here if needed
//	UE_LOG(LogTemp, Warning, TEXT("Actor %s has died!"), *DeadActor->GetName());
}
