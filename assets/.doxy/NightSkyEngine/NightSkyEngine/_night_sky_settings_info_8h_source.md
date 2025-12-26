

# File NightSkySettingsInfo.h

[**File List**](files.md) **>** [**Miscellaneous**](dir_3028ef8e315fbc532032c32a50fd3ba1.md) **>** [**NightSkySettingsInfo.h**](_night_sky_settings_info_8h.md)

[Go to the documentation of this file](_night_sky_settings_info_8h.md)


```C++
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NightSkySaveInfo.h"
#include "NightSkySettingsInfo.generated.h"

class UInputAction;

UCLASS()
class NIGHTSKYENGINE_API UNightSkySettingsInfo : public UNightSkySaveInfo
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite)
    int32 AntiAliasingMethod;
    UPROPERTY(BlueprintReadWrite)
    int32 GlobalIlluminationMethod;
};
```


