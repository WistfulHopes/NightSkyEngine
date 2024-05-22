// Fill out your copyright notice in the Description page of Project Settings.


#include "FighterReplayRunner.h"

#include "NightSkyEngine/Battle/Actors/NightSkyGameState.h"
#include "NightSkyEngine/Miscellaneous/NightSkyGameInstance.h"


// Sets default values
AFighterReplayRunner::AFighterReplayRunner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AFighterReplayRunner::BeginPlay()
{
	Super::BeginPlay();
	GameInstance = Cast<UNightSkyGameInstance>(GetGameInstance());
}

void AFighterReplayRunner::Update(float DeltaTime)
{
	if (GameState->bPauseGame)
		return;
	ElapsedTime += DeltaTime;
	while (ElapsedTime >= OneFrame)
	{
		//while elapsed time is greater than one frame...
		int32 P1Input = 0;
		int32 P2Input = 0;

		GameInstance->PlayReplayToGameState(GameState->LocalFrame, P1Input, P2Input);
		
		GameState->UpdateGameState(P1Input, P2Input, false);
		ElapsedTime -= OneFrame;
	}
}

