

# File NightSkyBlueprintFunctionLibrary.cpp

[**File List**](files.md) **>** [**Battle**](dir_59b3558fc0091a3111c9e7dd8d94b2ea.md) **>** [**Misc**](dir_4fd921e402b7a240656c31e280e3875c.md) **>** [**NightSkyBlueprintFunctionLibrary.cpp**](_night_sky_blueprint_function_library_8cpp.md)

[Go to the documentation of this file](_night_sky_blueprint_function_library_8cpp.md)


```C++
// Fill out your copyright notice in the Description page of Project Settings.


#include "NightSkyBlueprintFunctionLibrary.h"

#include "Globals.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(NightSkyBlueprintFunctionLibrary)

int32 UNightSkyBlueprintFunctionLibrary::Vec2Angle_x1000(int32 x, int32 y)
{
    int32 Angle = static_cast<int>(atan2(y, x) * 57295.77791868204) % 360000;
    if (Angle < 0)
        Angle += 360000;
    return Angle;
}

int32 UNightSkyBlueprintFunctionLibrary::Cos_x1000(int32 Deg_x10)
{
    int32 Tmp1 = (Deg_x10 + 900) % 3600;
    int32 Tmp2 = Deg_x10 + 3600;
    if (Tmp1 >= 0)
        Tmp2 = Tmp1;
    if (Tmp2 < 900)
        return gSinTable[Tmp2];
    if (Tmp2 < 1800)
        return gSinTable[1799 - Tmp2];
    if (Tmp2 >= 2700)
        return -gSinTable[3599 - Tmp2];
    return -gSinTable[Tmp2 - 1800];
}

int32 UNightSkyBlueprintFunctionLibrary::Sin_x1000(int32 Deg_x10)
{
    int32 Tmp1 = Deg_x10 % 3600;
    int32 Tmp2 = Deg_x10 + 3600;
    if (Tmp1 >= 0)
        Tmp2 = Tmp1;
    if (Tmp2 < 900)
        return gSinTable[Tmp2];
    if (Tmp2 < 1800)
        return gSinTable[1799 - Tmp2];
    if (Tmp2 >= 2700)
        return -gSinTable[3599 - Tmp2];
    return -gSinTable[Tmp2 - 1800];
}
```


