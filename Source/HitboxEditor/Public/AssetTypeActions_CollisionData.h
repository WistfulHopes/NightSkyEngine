#pragma once

// Note: My intellisense is not working so I'm just including everything I may need
#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"
#include "Math/Color.h"

class HITBOXEDITOR_API FAssetTypeActions_CollisionData : public FAssetTypeActions_Base
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