

# File WTCharacter.cpp

[**File List**](files.md) **>** [**NightSkyEngine**](dir_01309b4faf1ec48651014f612e2b32bb.md) **>** [**Source**](dir_d32ee28216ed342fa25c01ae9dcd9cc4.md) **>** [**NightSkyEngine**](dir_a12a4fa09c295aab9e164f44221961f1.md) **>** [**WT**](dir_cd88faa59062fd9190839afeb0d4d29a.md) **>** [**WTCharacter.cpp**](_w_t_character_8cpp.md)

[Go to the documentation of this file](_w_t_character_8cpp.md)


```C++
// Fill out your copyright notice in the Description page of Project Settings.


#include "WTCharacter.h"

#include "NightSkyWTGameState.h"
#include "NightSkyEngine/Battle/Objects/PlayerObject.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(WTCharacter)

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

    if (!IsPlayerControlled())
    {
        BattlePlayer->SpawnDefaultController();
        BattlePlayer->bIsCpu = true;
    }
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
```


