// Copyright Screaming Goose Games. All Rights Reserved.

#include "HitboxEditor.h"
#include "Logging.h"
#include "Modules/ModuleManager.h"
#include "IAssetTools.h"
#include "AssetToolsModule.h"
#include "AssetTypeActions_CollisionData.h"
#include "Logging.h"

#define LOCTEXT_NAMESPACE "FHitboxEditor" // Needed for LOCTEXT

void FHitboxEditor::StartupModule()
{
	UE_LOG(LogHitboxEditor, Log, TEXT("HitboxEditor Starting"));
	RegisterAssetTools();
}

void FHitboxEditor::ShutdownModule()
{
	// Unregister the asset tools
	if (FModuleManager::Get().IsModuleLoaded("AssetTools"))
	{
		IAssetTools& AssetTools = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools").Get();
		AssetTools.UnregisterAssetTypeActions(MakeShareable(new FAssetTypeActions_CollisionData(HitboxAssetCategoryBit)));
	}
}

void FHitboxEditor::RegisterAssetTools()
{
	// Register the asset tools
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	HitboxAssetCategoryBit = AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("CollisionData")), LOCTEXT("CollisionDataAssetCategory", "Collision Data"));
	//CollisionDataAssetTypeActions = MakeShareable(new FAssetTypeActions_CollisionData(HitboxAssetCategoryBit));
	TSharedRef<IAssetTypeActions> CollisionDataTypeActions = MakeShareable(new FAssetTypeActions_CollisionData(HitboxAssetCategoryBit));
	AssetTools.RegisterAssetTypeActions(CollisionDataTypeActions);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FHitboxEditor, HitboxEditor);