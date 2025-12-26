

# File PrimaryStageData.h

[**File List**](files.md) **>** [**Data**](dir_856985a2681c172443de4762aa082512.md) **>** [**PrimaryStageData.h**](_primary_stage_data_8h.md)

[Go to the documentation of this file](_primary_stage_data_8h.md)


```C++
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PrimaryStageData.generated.h"

UCLASS()
class NIGHTSKYENGINE_API UPrimaryStageData : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    virtual FPrimaryAssetId GetPrimaryAssetId() const override
    {
        return FPrimaryAssetId("PrimaryStageData", GetFName());
    }

    UPROPERTY(BlueprintReadOnly, EditAnywhere)
    FName StageName;
    UPROPERTY(BlueprintReadOnly, EditAnywhere)
    FText StageFriendlyName;
    UPROPERTY(BlueprintReadOnly, EditAnywhere)
    FText StageDescription;
    UPROPERTY(BlueprintReadOnly, EditAnywhere)
    UTexture2D* StageSelectIcon;
    UPROPERTY(BlueprintReadOnly, EditAnywhere)
    UTexture2D* StageSplashIcon;
    UPROPERTY(BlueprintReadOnly, EditAnywhere)
    FString StageURL;
};
```


