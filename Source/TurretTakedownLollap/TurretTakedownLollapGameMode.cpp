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

void ATurretTakedownLollapGameMode::ActorDied(AActor* DeadActor)
{
	if(DeadActor == nullptr) return;
	
	ATurretTakedownLollapCharacter* DeadCharacter = Cast<ATurretTakedownLollapCharacter>(DeadActor);
	
	if (DeadCharacter)
	{
		DeadCharacter->HandleDestruction();
		// Disable player controls, show game over UI, etc.
		// Example: Disable input for the player character
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
		if (PlayerController)
		{
			PlayerController->DisableInput(PlayerController);
			UE_LOG(LogTemp, Warning, TEXT("Player %s has died!"), *DeadCharacter->GetName());
		}
		// Triggers blueprint game over logic
		GameOver(false); // Call GameOver with false to indicate player death
	
		FTimerHandle DestroyTimer;
		FTimerDelegate TimerDel;
			{
				if (DeadCharacter && !DeadCharacter->IsPendingKillPending())
				{
					DeadCharacter->Destroy();
					UE_LOG(LogTemp, Warning, TEXT("Player character destroyed: %s"), *DeadCharacter->GetName());
				}
			};
		GetWorld()->GetTimerManager().SetTimer(DestroyTimer, TimerDel, 2.0f, false); // Delay before destroying the character
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Non-player actor died: %s"), *DeadActor->GetName());
		DeadActor->Destroy(); // Handle non-player actor death
	}
}

void ATurretTakedownLollapGameMode::BeginPlay()
{
	Super::BeginPlay();
	HandleGameStart();
}

// Fixing the assignment issue by ensuring the correct type is assigned to DefaultPawnClass
void ATurretTakedownLollapGameMode::HandleGameStart()
{
    StartGame();
}

