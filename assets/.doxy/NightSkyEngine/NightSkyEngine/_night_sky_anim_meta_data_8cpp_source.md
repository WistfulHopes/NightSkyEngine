

# File NightSkyAnimMetaData.cpp

[**File List**](files.md) **>** [**Animation**](dir_9a82c917abb4553e2c2738125a0d5751.md) **>** [**NightSkyAnimMetaData.cpp**](_night_sky_anim_meta_data_8cpp.md)

[Go to the documentation of this file](_night_sky_anim_meta_data_8cpp.md)


```C++
// Fill out your copyright notice in the Description page of Project Settings.


#include "NightSkyAnimMetaData.h"

#include "NightSkyAnimSequenceUserData.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(NightSkyAnimMetaData)

UNightSkyAnimMetaData::UNightSkyAnimMetaData()
{
    const auto AnimSequence = Cast<UAnimSequence>(GetOuter());

    if (!AnimSequence) return;
    if (IsValid(AnimSequence->GetAssetUserData<UNightSkyAnimSequenceUserData>())) return;

    AnimSequence->AddAssetUserDataOfClass(UNightSkyAnimSequenceUserData::StaticClass());
    UserData = static_cast<UNightSkyAnimSequenceUserData*>(AnimSequence->GetAssetUserDataOfClass(
        UNightSkyAnimSequenceUserData::StaticClass()));
}
```


