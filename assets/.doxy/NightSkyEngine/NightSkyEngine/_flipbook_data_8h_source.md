

# File FlipbookData.h

[**File List**](files.md) **>** [**Data**](dir_856985a2681c172443de4762aa082512.md) **>** [**FlipbookData.h**](_flipbook_data_8h.md)

[Go to the documentation of this file](_flipbook_data_8h.md)


```C++
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "PaperFlipbook.h"
#include "FlipbookData.generated.h"

USTRUCT(BlueprintType)
struct FFlipbookStruct
{
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadOnly, EditAnywhere)
    FGameplayTag Name;
    UPROPERTY(BlueprintReadOnly, EditAnywhere)
    UPaperFlipbook* Flipbook;
};

UCLASS()
class NIGHTSKYENGINE_API UFlipbookData : public UDataAsset
{
    GENERATED_BODY()
    
public:
    UPROPERTY(BlueprintReadOnly, EditAnywhere)
    TArray<FFlipbookStruct> FlipbookStructs;
};
```


