

# File FighterReplayRunner.cpp

[**File List**](files.md) **>** [**Battle**](dir_59b3558fc0091a3111c9e7dd8d94b2ea.md) **>** [**FighterRunners**](dir_55fd23ec9dd9ced1aa4a37204be9832d.md) **>** [**FighterReplayRunner.cpp**](_fighter_replay_runner_8cpp.md)

[Go to the documentation of this file](_fighter_replay_runner_8cpp.md)


```C++
// Fill out your copyright notice in the Description page of Project Settings.


#include "FighterReplayRunner.h"

#include "NightSkyEngine/Battle/NightSkyGameState.h"
#include "NightSkyEngine/Miscellaneous/NightSkyGameInstance.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(FighterReplayRunner)

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
```


