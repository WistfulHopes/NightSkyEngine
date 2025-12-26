

# File NightSkyBattleHudActor.h

[**File List**](files.md) **>** [**NightSkyEngine**](dir_01309b4faf1ec48651014f612e2b32bb.md) **>** [**Source**](dir_d32ee28216ed342fa25c01ae9dcd9cc4.md) **>** [**NightSkyEngine**](dir_a12a4fa09c295aab9e164f44221961f1.md) **>** [**UI**](dir_a40c408bd590fbad9d640bb5832ac49f.md) **>** [**NightSkyBattleHudActor.h**](_night_sky_battle_hud_actor_8h.md)

[Go to the documentation of this file](_night_sky_battle_hud_actor_8h.md)


```C++
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NightSkyBattleHudActor.generated.h"

class UNightSkyBattleWidget;

UCLASS()
class NIGHTSKYENGINE_API ANightSkyBattleHudActor : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ANightSkyBattleHudActor();

    UPROPERTY(BlueprintReadWrite)
    UNightSkyBattleWidget* TopWidget;
    UPROPERTY(BlueprintReadWrite)
    UNightSkyBattleWidget* BottomWidget;
};
```


