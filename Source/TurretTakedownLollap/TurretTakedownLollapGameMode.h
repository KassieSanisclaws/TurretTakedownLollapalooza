// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TurretTakedownLollapGameMode.generated.h"

UCLASS(minimalapi)
class ATurretTakedownLollapGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATurretTakedownLollapGameMode();

	// Actor Character Dies and is removed from the game
	void ActorDied(AActor* DeadActor);

protected: 
	virtual void BeginPlay() override; 
    
	UFUNCTION()
	void HandleGameStart();

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver();

private:
	class ATurretTakedownLollapPlayer* PlayerControllerRef;
};



