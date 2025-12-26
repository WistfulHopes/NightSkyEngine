

# File GGPOUE4.h

[**File List**](files.md) **>** [**GGPOUE4**](dir_61f8f2a9aed5edd4e8edeed0f59c7e8a.md) **>** [**Public**](dir_85b7962d70ed8e910f117d16fb4825fd.md) **>** [**GGPOUE4.h**](_g_g_p_o_u_e4_8h.md)

[Go to the documentation of this file](_g_g_p_o_u_e4_8h.md)


```C++
// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

DECLARE_LOG_CATEGORY_EXTERN(GGPOLOG, Log, All);

class FGGPOUE4Module : public IModuleInterface
{
public:

    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};
```


