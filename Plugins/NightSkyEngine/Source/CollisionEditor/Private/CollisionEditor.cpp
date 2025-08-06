// Copyright Screaming Goose Games. All Rights Reserved.

#include "CollisionEditor.h"
#include "Logging.h"
#include "Modules/ModuleManager.h"
#include "IAssetTools.h"
#include "AssetToolsModule.h"
#include "AssetTypeActions_CollisionData.h"

#define LOCTEXT_NAMESPACE "FCollisionEditor" // Needed for LOCTEXT

void FCollisionEditor::StartupModule()
{
	UE_LOG(LogCollisionEditor, Log, TEXT("CollisionEditor Starting"));
	RegisterAssetTools();
}

void FCollisionEditor::ShutdownModule()
{
	// Unregister the asset tools
	if (FModuleManager::Get().IsModuleLoaded("AssetTools"))
	{
		IAssetTools& AssetTools = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools").Get();
		AssetTools.UnregisterAssetTypeActions(MakeShareable(new FAssetTypeActions_CollisionData(CollisionAssetCategoryBit)));
	}
}

void FCollisionEditor::RegisterAssetTools()
{
	// Register the asset tools
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	CollisionAssetCategoryBit = AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("CollisionData")), LOCTEXT("CollisionDataAssetCategory", "Collision Data"));
	//CollisionDataAssetTypeActions = MakeShareable(new FAssetTypeActions_CollisionData(CollisionAssetCategoryBit));
	TSharedRef<IAssetTypeActions> CollisionDataTypeActions = MakeShareable(new FAssetTypeActions_CollisionData(CollisionAssetCategoryBit));
	AssetTools.RegisterAssetTypeActions(CollisionDataTypeActions);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCollisionEditor, CollisionEditor);