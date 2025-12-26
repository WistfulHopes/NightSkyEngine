

# File NightSkyAnimMetaData.h

[**File List**](files.md) **>** [**Animation**](dir_9a82c917abb4553e2c2738125a0d5751.md) **>** [**NightSkyAnimMetaData.h**](_night_sky_anim_meta_data_8h.md)

[Go to the documentation of this file](_night_sky_anim_meta_data_8h.md)


```C++
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimMetaData.h"
#include "NightSkyAnimMetaData.generated.h"

class UNightSkyAnimSequenceUserData;
UCLASS(CollapseCategories, EditInlineNew)
class NIGHTSKYENGINE_API UNightSkyAnimMetaData : public UAnimMetaData
{
    GENERATED_BODY()

public:
    UNightSkyAnimMetaData();

    UPROPERTY(EditAnywhere, Category = "Baked Animation")
    TSet<FName> CachedBoneNames;

    UPROPERTY(BlueprintReadOnly, Category = "Baked Animation")
    TObjectPtr<UNightSkyAnimSequenceUserData> UserData;
};
```


