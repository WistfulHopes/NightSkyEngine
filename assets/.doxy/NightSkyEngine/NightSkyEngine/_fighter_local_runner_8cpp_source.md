

# File FighterLocalRunner.cpp

[**File List**](files.md) **>** [**Battle**](dir_59b3558fc0091a3111c9e7dd8d94b2ea.md) **>** [**FighterRunners**](dir_55fd23ec9dd9ced1aa4a37204be9832d.md) **>** [**FighterLocalRunner.cpp**](_fighter_local_runner_8cpp.md)

[Go to the documentation of this file](_fighter_local_runner_8cpp.md)


```C++
// Fill out your copyright notice in the Description page of Project Settings.


#include "FighterLocalRunner.h"

#include "NightSkyEngine/Battle/NightSkyGameState.h"
#include "Kismet/GameplayStatics.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(FighterLocalRunner)

// Sets default values
AFighterLocalRunner::AFighterLocalRunner()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;
    bReplicates = false;
}

// Called when the game starts or when spawned
void AFighterLocalRunner::BeginPlay()
{
    Super::BeginPlay();
    TArray<AActor*> FoundFighterGameStates;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ANightSkyGameState::StaticClass(), FoundFighterGameStates);
    if (FoundFighterGameStates.Num() > 0)
    {
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
```


