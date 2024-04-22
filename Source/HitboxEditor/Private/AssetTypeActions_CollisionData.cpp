#include "AssetTypeActions_CollisionData.h"
#include "CollisionDataEditorToolkit.h"
#include "Toolkits/IToolkit.h"
#include "AssetTypeCategories.h"
#include "EditorStyleSet.h"
#include "Math/Color.h"
#include "Internationalization/Internationalization.h" // included to use LOCTEXT

#define LOCTEXT_NAMESPACE "AssetTypeActions_CollisionData"

FColor FAssetTypeActions_CollisionData::GetTypeColor() const
{
	return FColor(0, 255, 0);
}

UClass* FAssetTypeActions_CollisionData::GetSupportedClass() const
{
    return UCollisionData::StaticClass();
}

void FAssetTypeActions_CollisionData::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
    for (auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt)
    {
        auto CollisionData = Cast<UCollisionData>(*ObjIt);
        if (CollisionData != nullptr)
        {
            // Create an instance of the editor. Let Unreal manage the editor's lifecycle.
            TSharedRef<FCollisionDataEditorToolkit> Editor = MakeShareable(new FCollisionDataEditorToolkit());
            Editor->Initialize(CollisionData, EToolkitMode::Standalone, EditWithinLevelEditor);
        }
    }
}


FText FAssetTypeActions_CollisionData::GetName() const
{
    return NSLOCTEXT("AssetTypeActions", "FAssetTypeActionsCollisionDataName", "Collision Data");
}

uint32 FAssetTypeActions_CollisionData::GetCategories()
{
    return AssetCategory;
}

#undef LOCTEXT_NAMESPACE