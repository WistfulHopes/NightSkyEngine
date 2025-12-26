

# File NightSkyWTGameState.h

[**File List**](files.md) **>** [**NightSkyEngine**](dir_01309b4faf1ec48651014f612e2b32bb.md) **>** [**Source**](dir_d32ee28216ed342fa25c01ae9dcd9cc4.md) **>** [**NightSkyEngine**](dir_a12a4fa09c295aab9e164f44221961f1.md) **>** [**WT**](dir_cd88faa59062fd9190839afeb0d4d29a.md) **>** [**NightSkyWTGameState.h**](_night_sky_w_t_game_state_8h.md)

[Go to the documentation of this file](_night_sky_w_t_game_state_8h.md)


```C++
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NightSkyEngine/Battle/NightSkyGameState.h"
#include "NightSkyWTGameState.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBattleEndDelegate);

UCLASS()
class NIGHTSKYENGINE_API ANightSkyWTGameState : public ANightSkyGameState
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ANightSkyWTGameState();

    UPROPERTY(BlueprintReadWrite)
    bool bIsMatchEnd;
    
    UPROPERTY(BlueprintReadOnly)
    bool bIsBattling;

    UPROPERTY()
    FOnBattleEndDelegate OnBattleEndDelegate;
    
protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    
public:
    void Init(APlayerObject* P1, APlayerObject* P2);
    
    // Called every frame
    virtual void Tick(float DeltaTime) override;
};
```


