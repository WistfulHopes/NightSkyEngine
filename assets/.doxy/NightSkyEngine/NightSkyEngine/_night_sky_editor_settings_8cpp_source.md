

# File NightSkyEditorSettings.cpp

[**File List**](files.md) **>** [**Miscellaneous**](dir_3028ef8e315fbc532032c32a50fd3ba1.md) **>** [**NightSkyEditorSettings.cpp**](_night_sky_editor_settings_8cpp.md)

[Go to the documentation of this file](_night_sky_editor_settings_8cpp.md)


```C++
// Fill out your copyright notice in the Description page of Project Settings.


#include "NightSkyEditorSettings.h"

UNightSkyEditorSettings::UNightSkyEditorSettings(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    CategoryName = "Plugins";
    SectionName = "Night Sky Engine";
}

UNightSkyEditorSettings* UNightSkyEditorSettings::Get()
{
    return GetMutableDefault<UNightSkyEditorSettings>();
}

const UNightSkyEditorSettings* UNightSkyEditorSettings::GetConst()
{
    return GetDefault<UNightSkyEditorSettings>();
}
```


