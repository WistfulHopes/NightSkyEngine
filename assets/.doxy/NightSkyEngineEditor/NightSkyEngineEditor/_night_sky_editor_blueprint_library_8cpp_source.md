

# File NightSkyEditorBlueprintLibrary.cpp

[**File List**](files.md) **>** [**NightSkyEngine**](dir_01309b4faf1ec48651014f612e2b32bb.md) **>** [**Source**](dir_d32ee28216ed342fa25c01ae9dcd9cc4.md) **>** [**NightSkyEngineEditor**](dir_e38b96015bf9e01b06e1db3a9ecb109f.md) **>** [**Private**](dir_bb140671b05e9cd1d3ff0c1fb32f057e.md) **>** [**NightSkyEditorBlueprintLibrary.cpp**](_night_sky_editor_blueprint_library_8cpp.md)

[Go to the documentation of this file](_night_sky_editor_blueprint_library_8cpp.md)


```C++
// Fill out your copyright notice in the Description page of Project Settings.


#include "NightSkyEditorBlueprintLibrary.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(NightSkyEditorBlueprintLibrary)

FGameplayTag UNightSkyEditorBlueprintLibrary::GetGameplayTagFromName(FName Name)
{
    return FGameplayTag::RequestGameplayTag(Name);
}
```


