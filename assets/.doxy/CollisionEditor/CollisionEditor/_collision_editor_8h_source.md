

# File CollisionEditor.h

[**File List**](files.md) **>** [**CollisionEditor**](dir_940e8f38acfe3acbe44a727b0224043a.md) **>** [**Public**](dir_56ac83e1ee3de8bf475f92dfdd96fd55.md) **>** [**CollisionEditor.h**](_collision_editor_8h.md)

[Go to the documentation of this file](_collision_editor_8h.md)


```C++
#pragma once

#include "CoreMinimal.h"
#include "AssetTypeCategories.h"
#include "Modules/ModuleManager.h"


class COLLISIONEDITOR_API FCollisionEditor : public IModuleInterface
{
public:

    void StartupModule() override;
    void ShutdownModule() override;

private:
    EAssetTypeCategories::Type CollisionAssetCategoryBit;

    void RegisterAssetTools();
    void RegisterPropertyCustomizations();
    void UnregisterPropertyCustomizations();
};
```


