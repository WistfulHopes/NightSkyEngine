

# File CelAssetTreeNode.h

[**File List**](files.md) **>** [**CollisionEditor**](dir_940e8f38acfe3acbe44a727b0224043a.md) **>** [**Public**](dir_56ac83e1ee3de8bf475f92dfdd96fd55.md) **>** [**CelAssetTreeNode.h**](_cel_asset_tree_node_8h.md)

[Go to the documentation of this file](_cel_asset_tree_node_8h.md)


```C++
#pragma once

#include "CoreMinimal.h"

class FCelAssetTreeNode : public TSharedFromThis<FCelAssetTreeNode>
{
public:
    FCelAssetTreeNode(const FString& InDisplayName, int32 InCelIndex = INDEX_NONE)
        : DisplayName(InDisplayName)
        , CelIndex(InCelIndex)
        , bHasProblem(false)
    {
    }
    
    FCelAssetTreeNode(int32 InCelIndex, const FString& InDisplayName, bool bInHasProblem = false)
        : DisplayName(InDisplayName)
        , CelIndex(InCelIndex)
        , bHasProblem(bInHasProblem) {}

    bool IsCategory() const { return CelIndex == INDEX_NONE; }
    bool IsCel() const { return CelIndex != INDEX_NONE; }
    bool IsValid() const { return bHasProblem; }

    FString GetDisplayName() const { return DisplayName; }
    int32 GetCelIndex() const { return CelIndex; }
    void SetCelIndex(int32 InCelIndex) { CelIndex = InCelIndex; }

    TSharedPtr<FCelAssetTreeNode> FindOrCreateChild(const FString& ChildName, int32 ChildCelIndex = INDEX_NONE);

    TWeakPtr<FCelAssetTreeNode> Parent;
    TArray<TSharedPtr<FCelAssetTreeNode>> Children;

private:
    FString DisplayName;
    int32 CelIndex;
    bool bHasProblem;
};
```


