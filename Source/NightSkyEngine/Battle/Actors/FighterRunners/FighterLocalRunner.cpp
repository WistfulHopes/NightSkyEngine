// Fill out your copyright notice in the Description page of Project Settings.


#include "FighterLocalRunner.h"

#include "NightSkyEngine/Battle/Actors/NightSkyGameState.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFighterLocalRunner::AFighterLocalRunner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bReplicates=false;
}

// Called when the game starts or when spawned
void AFighterLocalRunner::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> FoundFighterGameStates;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ANightSkyGameState::StaticClass(), FoundFighterGameStates);
	if(FoundFighterGameStates.Num()>0){
		GameState = Cast<ANightSkyGameState>(FoundFighterGameStates[0]);
	}
}

void AFighterLocalRunner::Update(float DeltaTime)
{
	if (GameState->bPauseGame)
		return;
	ElapsedTime += DeltaTime;
	while (ElapsedTime >= OneFrame)
	{
		//while elapsed time is greater than one frame...
		GameState->UpdateGameState();
		ElapsedTime -= OneFrame;
	}
}
