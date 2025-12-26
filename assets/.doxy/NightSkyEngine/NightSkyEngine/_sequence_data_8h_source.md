

# File SequenceData.h

[**File List**](files.md) **>** [**Data**](dir_856985a2681c172443de4762aa082512.md) **>** [**SequenceData.h**](_sequence_data_8h.md)

[Go to the documentation of this file](_sequence_data_8h.md)


```C++
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "LevelSequence.h"
#include "SequenceData.generated.h"

USTRUCT(BlueprintType)
struct FSequenceStruct
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadOnly, EditAnywhere)
    FGameplayTag Name;
    UPROPERTY(BlueprintReadOnly, EditAnywhere)
    ULevelSequence* Sequence;
};

UCLASS()
class NIGHTSKYENGINE_API USequenceData : public UDataAsset
{
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadOnly, EditAnywhere)
    TArray<FSequenceStruct> SequenceStructs;
};
```


