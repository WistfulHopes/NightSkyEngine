

# File NightSkyVSInfoGameState.h

[**File List**](files.md) **>** [**NightSkyEngine**](dir_01309b4faf1ec48651014f612e2b32bb.md) **>** [**Source**](dir_d32ee28216ed342fa25c01ae9dcd9cc4.md) **>** [**NightSkyEngine**](dir_a12a4fa09c295aab9e164f44221961f1.md) **>** [**VSInfo**](dir_0a96afba4f006b77d5cb7d94a414ba7d.md) **>** [**NightSkyVSInfoGameState.h**](_night_sky_v_s_info_game_state_8h.md)

[Go to the documentation of this file](_night_sky_v_s_info_game_state_8h.md)


```C++
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "NightSkyVSInfoGameState.generated.h"

class UNightSkyGameInstance;
UCLASS()
class NIGHTSKYENGINE_API ANightSkyVSInfoGameState : public AGameStateBase
{
    GENERATED_BODY()

    double VSInfoTime;
    bool MapLoaded;
    int32 LoadedCharaPackageCount;
    int32 TotalCharaPackageCount;

    UPROPERTY()
    TArray<TObjectPtr<UPackage>> Packages;
    UPROPERTY()
    TObjectPtr<UNightSkyGameInstance> GameInstance;

public:
    ANightSkyVSInfoGameState();
    
    UPROPERTY(EditAnywhere)
    double MaxVSInfoTime = 6;
    
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;
    
    void OnMapPackageLoaded(const FName& PackageName, UPackage* LoadedPackage, EAsyncLoadingResult::Type Result);
    void OnCharaPackageLoaded(const FName& PackageName, UPackage* LoadedPackage, EAsyncLoadingResult::Type Result);
};
```


