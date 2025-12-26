

# File AssetTypeActions\_CollisionData.h

[**File List**](files.md) **>** [**CollisionEditor**](dir_940e8f38acfe3acbe44a727b0224043a.md) **>** [**Public**](dir_56ac83e1ee3de8bf475f92dfdd96fd55.md) **>** [**AssetTypeActions\_CollisionData.h**](_asset_type_actions___collision_data_8h.md)

[Go to the documentation of this file](_asset_type_actions___collision_data_8h.md)


```C++
#pragma once

// Note: My intellisense is not working so I'm just including everything I may need
#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"
#include "Math/Color.h"

class COLLISIONEDITOR_API FAssetTypeActions_CollisionData : public FAssetTypeActions_Base
{
public:

    FAssetTypeActions_CollisionData(EAssetTypeCategories::Type InAssetCategory)
        : AssetCategory(InAssetCategory){}

    virtual FColor GetTypeColor() const override;
    virtual UClass* GetSupportedClass() const override;

    virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor) override;

    virtual FText GetName() const override;

    virtual bool CanFilter() override { return true; }

    virtual uint32 GetCategories() override;

private:
    EAssetTypeCategories::Type AssetCategory;
};
```


