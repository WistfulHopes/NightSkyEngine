#pragma once

#include "CoreMinimal.h"
#include "CelAssetTreeNode.h"
#include "GameplayTagContainer.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Views/STreeView.h"

class UCollisionData;

DECLARE_DELEGATE_OneParam(FOnCelSelected, int32 /*SelectedCelIndex*/);

/**
 * Tree view widget for browsing cels grouped by GameplayTag hierarchy.
 */
class SCelAssetTree : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SCelAssetTree) {}
		SLATE_EVENT(FOnCelSelected, OnCelSelected)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UCollisionData* InCollisionData);

	void RefreshTree();
	void SetSelectedCel(const FGameplayTag& CelName);

private:
	TSharedRef<ITableRow> GenerateTreeRow(
		TSharedPtr<FCelAssetTreeNode> InNode,
		const TSharedRef<STableViewBase>& OwnerTable);

	void GetChildrenForNode(
		TSharedPtr<FCelAssetTreeNode> InNode,
		TArray<TSharedPtr<FCelAssetTreeNode>>& OutChildren);

	void OnSelectionChanged(
		TSharedPtr<FCelAssetTreeNode> SelectedNode,
		ESelectInfo::Type SelectInfo);

	void OnFilterTextChanged(const FText& InText);

	void BuildTreeFromCollisionData();
	
	// TODO: Search box filtering
	// void ApplyFilter(const FString& FilterString);

	TWeakObjectPtr<UCollisionData> CollisionData;
	TSharedPtr<STreeView<TSharedPtr<FCelAssetTreeNode>>> TreeView;
	TArray<TSharedPtr<FCelAssetTreeNode>> RootNodes;
	TArray<TSharedPtr<FCelAssetTreeNode>> AllNodes;

	FString CurrentFilterString;
	FOnCelSelected OnCelSelectedDelegate;

	// Maps cel index to its tree node for quick lookup
	TMap<int32, TSharedPtr<FCelAssetTreeNode>> CelIndexToNodeMap;
};
