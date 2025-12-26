

# File NightSkyWTPlayerController.h

[**File List**](files.md) **>** [**NightSkyEngine**](dir_01309b4faf1ec48651014f612e2b32bb.md) **>** [**Source**](dir_d32ee28216ed342fa25c01ae9dcd9cc4.md) **>** [**NightSkyEngine**](dir_a12a4fa09c295aab9e164f44221961f1.md) **>** [**WT**](dir_cd88faa59062fd9190839afeb0d4d29a.md) **>** [**NightSkyWTPlayerController.h**](_night_sky_w_t_player_controller_8h.md)

[Go to the documentation of this file](_night_sky_w_t_player_controller_8h.md)


```C++
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NightSkyEngine/Battle/NightSkyPlayerController.h"
#include "NightSkyWTPlayerController.generated.h"

UCLASS()
class NIGHTSKYENGINE_API ANightSkyWTPlayerController : public ANightSkyPlayerController
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ANightSkyWTPlayerController();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;
};
```


