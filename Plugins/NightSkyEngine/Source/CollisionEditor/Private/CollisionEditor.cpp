#include "CollisionEditor.h"
#include "AssetToolsModule.h"
#include "AssetTypeActions_CollisionData.h"
#include "CollisionDataDetails.h"
#include "IAssetTools.h"
#include "Logging.h"
#include "PropertyEditorModule.h"
#include "Data/CollisionData.h"
#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "NightSkyCollisionEditor"

void FCollisionEditor::StartupModule()
{
	UE_LOG(LogCollisionEditor, Log, TEXT("CollisionEditor Starting"));
	RegisterAssetTools();
	RegisterPropertyCustomizations();
}

void FCollisionEditor::ShutdownModule()
{
	UnregisterPropertyCustomizations();

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
	TSharedRef<IAssetTypeActions> CollisionDataTypeActions = MakeShareable(new FAssetTypeActions_CollisionData(CollisionAssetCategoryBit));
	AssetTools.RegisterAssetTypeActions(CollisionDataTypeActions);
}

void FCollisionEditor::RegisterPropertyCustomizations()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	PropertyModule.RegisterCustomClassLayout(
		UCollisionData::StaticClass()->GetFName(),
		FOnGetDetailCustomizationInstance::CreateStatic(&FCollisionDataDetails::MakeInstance)
	);

	PropertyModule.NotifyCustomizationModuleChanged();
}

void FCollisionEditor::UnregisterPropertyCustomizations()
{
	if (FModuleManager::Get().IsModuleLoaded("PropertyEditor"))
	{
		FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
		PropertyModule.UnregisterCustomClassLayout(UCollisionData::StaticClass()->GetFName());
	}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FCollisionEditor, CollisionEditor);