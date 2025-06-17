// Copyright Epic Games, Inc. All Rights Reserved.

#include "TurretTakedownLollapGameMode.h"
#include "TurretTakedownLollapCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

ATurretTakedownLollapGameMode::ATurretTakedownLollapGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}

void ATurretTakedownLollapGameMode::BeginPlay()
{
	Super::BeginPlay();
	HandleGameStart();
	// Optional: Log or initialize things
	UE_LOG(LogTemp, Warning, TEXT("Game Mode BeginPlay called!"));
}

// Fixing the assignment issue by ensuring the correct type is assigned to DefaultPawnClass
void ATurretTakedownLollapGameMode::HandleGameStart()
{
    // Initialize game state, spawn enemies, set up UI, etc.
    UE_LOG(LogTemp, Warning, TEXT("Game has started! Initializing game state..."));

    // Correctly assign the class of the player pawn to DefaultPawnClass
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
    if (PlayerPawn)
    {
        DefaultPawnClass = PlayerPawn->GetClass();
    }

    StartGame();
}


void ATurretTakedownLollapGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == nullptr) return;
	ATurretTakedownLollapCharacter* DeadCharacter = Cast<ATurretTakedownLollapCharacter>(DeadActor);
	if (DeadCharacter)
	{
		/*DeadCharacter->HandleDeath();*/
		UE_LOG(LogTemp, Warning, TEXT("Player %s has died!"), *DeadCharacter->GetName());
		// TODO: Game over, restart level, show UI, etc.
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Non-player actor died: %s"), *DeadActor->GetName());
		// e.g., Destroy() enemy, spawn effects, drop loot
	}
}

//void ATurretTakedownLollapGameMode::HandleDeath(AActor* DeadActor)
//{
//	if (DeadActor == nullptr) return;
//	// Call the ActorDied function to handle the death logic
//	ActorDied(DeadActor);
//
//	// Additional death handling logic can be added here if needed
//	UE_LOG(LogTemp, Warning, TEXT("Actor %s has died!"), *DeadActor->GetName());
//}
