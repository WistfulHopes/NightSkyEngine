#pragma once

#include "CoreMinimal.h"

/**
 * Node for the cel asset tree view.
 * Can represent either a category (intermediate node) or a cel (leaf node).
 */
class FCelAssetTreeNode : public TSharedFromThis<FCelAssetTreeNode>
{
public:
	/** Category constructor */
	FCelAssetTreeNode(const FString& InDisplayName, int32 InCelIndex = INDEX_NONE)
		: DisplayName(InDisplayName)
		, CelIndex(InCelIndex)
		, bHasProblem(false)
	{
	}
	
	/** Cel node constructor, requires an index */
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
