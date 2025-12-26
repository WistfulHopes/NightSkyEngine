

# File NightSkyWTPlayerController.cpp

[**File List**](files.md) **>** [**NightSkyEngine**](dir_01309b4faf1ec48651014f612e2b32bb.md) **>** [**Source**](dir_d32ee28216ed342fa25c01ae9dcd9cc4.md) **>** [**NightSkyEngine**](dir_a12a4fa09c295aab9e164f44221961f1.md) **>** [**WT**](dir_cd88faa59062fd9190839afeb0d4d29a.md) **>** [**NightSkyWTPlayerController.cpp**](_night_sky_w_t_player_controller_8cpp.md)

[Go to the documentation of this file](_night_sky_w_t_player_controller_8cpp.md)


```C++
// Fill out your copyright notice in the Description page of Project Settings.


#include "NightSkyWTPlayerController.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(NightSkyWTPlayerController)

// Sets default values
ANightSkyWTPlayerController::ANightSkyWTPlayerController()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ANightSkyWTPlayerController::BeginPlay()
{
    Super::BeginPlay();
    
}

// Called every frame
void ANightSkyWTPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

```


