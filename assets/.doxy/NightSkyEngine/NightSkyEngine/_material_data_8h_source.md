

# File MaterialData.h

[**File List**](files.md) **>** [**Data**](dir_856985a2681c172443de4762aa082512.md) **>** [**MaterialData.h**](_material_data_8h.md)

[Go to the documentation of this file](_material_data_8h.md)


```C++
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "MaterialData.generated.h"

USTRUCT(BlueprintType)
struct FMaterialStruct
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, EditAnywhere)
    FName Name;
    UPROPERTY(BlueprintReadOnly, EditAnywhere)
    TArray<UMaterialInterface*> Material;
    UPROPERTY(BlueprintReadOnly, EditAnywhere)
    UMaterialInterface* OverlayMaterial;
};

UCLASS()
class NIGHTSKYENGINE_API UMaterialData : public UDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadOnly, EditAnywhere)
    TArray<FMaterialStruct> MaterialStructs;
};
```


