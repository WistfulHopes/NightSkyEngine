

# File NightSkyEngineEditor.h

[**File List**](files.md) **>** [**NightSkyEngine**](dir_01309b4faf1ec48651014f612e2b32bb.md) **>** [**Source**](dir_d32ee28216ed342fa25c01ae9dcd9cc4.md) **>** [**NightSkyEngineEditor**](dir_e38b96015bf9e01b06e1db3a9ecb109f.md) **>** [**Public**](dir_b1f934c454122ee63eeb5ca8173b113f.md) **>** [**NightSkyEngineEditor.h**](_night_sky_engine_editor_8h.md)

[Go to the documentation of this file](_night_sky_engine_editor_8h.md)


```C++
#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FNightSkyEngineEditorModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};
```


