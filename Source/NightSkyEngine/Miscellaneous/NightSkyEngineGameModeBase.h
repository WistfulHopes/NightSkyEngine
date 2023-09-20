// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NightSkyEngineGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class NIGHTSKYENGINE_API ANightSkyEngineGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
		
	bool bAllExistingPlayersRegistered;

	virtual void PostLogin(APlayerController* NewPlayer) override;

public:
	void RegisterExistingPlayers();
	void PreLogout(APlayerController *InPlayerController);
};
