

# File FighterReplayRunner.h

[**File List**](files.md) **>** [**Battle**](dir_59b3558fc0091a3111c9e7dd8d94b2ea.md) **>** [**FighterRunners**](dir_55fd23ec9dd9ced1aa4a37204be9832d.md) **>** [**FighterReplayRunner.h**](_fighter_replay_runner_8h.md)

[Go to the documentation of this file](_fighter_replay_runner_8h.md)


```C++
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FighterLocalRunner.h"
#include "FighterReplayRunner.generated.h"

class UNightSkyGameInstance;

UCLASS()
class NIGHTSKYENGINE_API AFighterReplayRunner : public AFighterLocalRunner
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AFighterReplayRunner();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    UPROPERTY()
    UNightSkyGameInstance* GameInstance;

public:
    // Called every frame
    virtual void Update(float DeltaTime) override;
};
```


