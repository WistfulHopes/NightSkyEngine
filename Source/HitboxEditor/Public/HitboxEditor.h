// Copyright Screaming Goose Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AssetTypeCategories.h"
#include "Modules/ModuleManager.h"


class HITBOXEDITOR_API FHitboxEditor : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	void StartupModule() override;
	void ShutdownModule() override;

private:
	//TSharedRef<IAssetTypeActions> CollisionDataAssetTypeActions;
	// Do we need to store a reference to the specific asset type actions?
	// Or do we create a new instance when we unregister?

	EAssetTypeCategories::Type HitboxAssetCategoryBit;

	void RegisterAssetTools();

	// Do we need a ptr to a specific factory for creating new hitbox assets?
};
