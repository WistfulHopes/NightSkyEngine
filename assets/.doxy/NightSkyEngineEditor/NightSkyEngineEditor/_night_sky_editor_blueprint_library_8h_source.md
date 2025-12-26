

# File NightSkyEditorBlueprintLibrary.h

[**File List**](files.md) **>** [**NightSkyEngine**](dir_01309b4faf1ec48651014f612e2b32bb.md) **>** [**Source**](dir_d32ee28216ed342fa25c01ae9dcd9cc4.md) **>** [**NightSkyEngineEditor**](dir_e38b96015bf9e01b06e1db3a9ecb109f.md) **>** [**Public**](dir_b1f934c454122ee63eeb5ca8173b113f.md) **>** [**NightSkyEditorBlueprintLibrary.h**](_night_sky_editor_blueprint_library_8h.md)

[Go to the documentation of this file](_night_sky_editor_blueprint_library_8h.md)


```C++
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "NightSkyEditorBlueprintLibrary.generated.h"

UCLASS()
class NIGHTSKYENGINEEDITOR_API UNightSkyEditorBlueprintLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Gameplay Tags")
    static FGameplayTag GetGameplayTagFromName(FName Name);
};
```


