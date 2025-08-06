// Fill out your copyright notice in the Description page of Project Settings.


#include "WTCharacter.h"

#include "NightSkyWTGameState.h"
#include "NightSkyEngine/Battle/Actors/PlayerObject.h"


// Sets default values
AWTCharacter::AWTCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AWTCharacter::BeginPlay()
{
	Super::BeginPlay();

	GameState = Cast<ANightSkyWTGameState>(GetWorld()->GetGameState());
	if (GameState)
		GameState->OnBattleEndDelegate.AddUniqueDynamic(this, &AWTCharacter::EndBattle);
	
	BattlePlayer = GetWorld()->SpawnActor<APlayerObject>(BattlePlayerClass);
	BattlePlayer->SetActorHiddenInGame(true);
}

// Called every frame
void AWTCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AWTCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AWTCharacter::StartBattle(AWTCharacter* Opponent)
{
	// Hide WT character and show battle player.
	SetActorHiddenInGame(true);
	BattlePlayer->SetActorHiddenInGame(false);
	Opponent->SetActorHiddenInGame(true);
	Opponent->BattlePlayer->SetActorHiddenInGame(false);

	GameState->Init(BattlePlayer, Opponent->BattlePlayer);
}

void AWTCharacter::EndBattle()
{
	SetActorHiddenInGame(false);
	BattlePlayer->SetActorHiddenInGame(true);
	EndBattle_BP();
}
