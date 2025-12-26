

# File ReplayInfo.h

[**File List**](files.md) **>** [**Miscellaneous**](dir_3028ef8e315fbc532032c32a50fd3ba1.md) **>** [**ReplayInfo.h**](_replay_info_8h.md)

[Go to the documentation of this file](_replay_info_8h.md)


```C++
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NightSkyGameInstance.h"
#include "NightSkySaveInfo.h"
#include "ReplayInfo.generated.h"

UCLASS()
class NIGHTSKYENGINE_API UReplaySaveInfo : public UNightSkySaveInfo
{
    GENERATED_BODY()

public:
    UReplaySaveInfo()  
    {
        Timestamp = FDateTime::Now();
        BattleData = FBattleData();  
        Version = "";
        ReplayIndex = -1;
        LengthInFrames = 0;
    }
    
    UPROPERTY(BlueprintReadOnly)  
    FDateTime Timestamp;
    UPROPERTY(BlueprintReadOnly)  
    FBattleData BattleData;
    UPROPERTY(BlueprintReadOnly)  
    FString Version;
    UPROPERTY(BlueprintReadOnly)
    int32 ReplayIndex;
    UPROPERTY()
    int32 LengthInFrames;
    UPROPERTY()
    TArray<int32> InputsP1;
    UPROPERTY()
    TArray<int32> InputsP2;
    UPROPERTY()
    bool bIsTraining;
};
```


