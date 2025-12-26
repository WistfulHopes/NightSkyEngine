

# File NightSkyBlueprintFunctionLibrary.h

[**File List**](files.md) **>** [**Battle**](dir_59b3558fc0091a3111c9e7dd8d94b2ea.md) **>** [**Misc**](dir_4fd921e402b7a240656c31e280e3875c.md) **>** [**NightSkyBlueprintFunctionLibrary.h**](_night_sky_blueprint_function_library_8h.md)

[Go to the documentation of this file](_night_sky_blueprint_function_library_8h.md)


```C++
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "NightSkyBlueprintFunctionLibrary.generated.h"

UCLASS()
class NIGHTSKYENGINE_API UNightSkyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintPure)
    static int32 Vec2Angle_x1000(int32 x, int32 y);
    UFUNCTION(BlueprintPure)
    static int32 Cos_x1000(int32 Deg_x10);
    UFUNCTION(BlueprintPure)
    static int32 Sin_x1000(int32 Deg_x10);
};
```


