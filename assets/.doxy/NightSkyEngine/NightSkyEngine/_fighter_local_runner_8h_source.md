

# File FighterLocalRunner.h

[**File List**](files.md) **>** [**Battle**](dir_59b3558fc0091a3111c9e7dd8d94b2ea.md) **>** [**FighterRunners**](dir_55fd23ec9dd9ced1aa4a37204be9832d.md) **>** [**FighterLocalRunner.h**](_fighter_local_runner_8h.md)

[Go to the documentation of this file](_fighter_local_runner_8h.md)


```C++
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FighterLocalRunner.generated.h"

UCLASS()
class NIGHTSKYENGINE_API AFighterLocalRunner : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AFighterLocalRunner();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Update(float DeltaTime);

protected:
    float ElapsedTime = 0;

    UPROPERTY()
    class ANightSkyGameState* GameState;
};
```


