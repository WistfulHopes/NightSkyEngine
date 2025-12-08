#pragma once

#include "CoreMinimal.h"
#include "AssetTypeCategories.h"
#include "Modules/ModuleManager.h"


class COLLISIONEDITOR_API FCollisionEditor : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	void StartupModule() override;
	void ShutdownModule() override;

private:
	EAssetTypeCategories::Type CollisionAssetCategoryBit;

	void RegisterAssetTools();
	void RegisterPropertyCustomizations();
	void UnregisterPropertyCustomizations();
};
