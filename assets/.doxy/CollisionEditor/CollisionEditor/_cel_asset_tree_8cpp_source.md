

# File CelAssetTree.cpp

[**File List**](files.md) **>** [**CollisionEditor**](dir_940e8f38acfe3acbe44a727b0224043a.md) **>** [**Private**](dir_b4aad7ce9c05cbacc2935f83ad755e41.md) **>** [**CelAssetTree.cpp**](_cel_asset_tree_8cpp.md)

[Go to the documentation of this file](_cel_asset_tree_8cpp.md)


```C++
#include "CelAssetTree.h"

#include "Logging.h"
#include "Data/CollisionData.h"
#include "Styling/AppStyle.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Text/STextBlock.h"

TSharedPtr<FCelAssetTreeNode> FCelAssetTreeNode::FindOrCreateChild(const FString& ChildName, int32 ChildCelIndex)
{
    // Look for existing child with this name
    for (const TSharedPtr<FCelAssetTreeNode>& Child : Children)
    {
        if (Child->GetDisplayName() == ChildName)
        {
            // If we're trying to set a cel index on an existing category node, update it
            // This happens when e.g. "Attack" exists as both a parent for "Attack.00" and as a cel itself
            if (ChildCelIndex != INDEX_NONE && Child->IsCategory())
            {
                Child->SetCelIndex(ChildCelIndex);
            }
            return Child;
        }
    }

    // Create new child
    TSharedPtr<FCelAssetTreeNode> NewChild = MakeShared<FCelAssetTreeNode>(ChildName, ChildCelIndex);
    NewChild->Parent = AsShared();
    Children.Add(NewChild);
    return NewChild;
}

void SCelAssetTree::Construct(const FArguments& InArgs, UCollisionData* InCollisionData)
{
    CollisionData = InCollisionData;
    OnCelSelectedDelegate = InArgs._OnCelSelected;

    ChildSlot
    [
        // TODO: When we implement filtering, add a new SVerticalBox at the top
        SNew(SVerticalBox)
        + SVerticalBox::Slot()
        .FillHeight(1.f)
        [
            SNew(SBorder)
            .BorderImage(FAppStyle::GetBrush("ToolPanel.GroupBorder"))
            .Padding(2.f)
            [
                SAssignNew(TreeView, STreeView<TSharedPtr<FCelAssetTreeNode>>)
                .TreeItemsSource(&RootNodes)
                .SelectionMode(ESelectionMode::Single)
                .OnGenerateRow(this, &SCelAssetTree::GenerateTreeRow)
                .OnGetChildren(this, &SCelAssetTree::GetChildrenForNode)
                .OnSelectionChanged(this, &SCelAssetTree::OnSelectionChanged)
            ]
        ]
    ];

    RefreshTree();
}

void SCelAssetTree::RefreshTree()
{
    RootNodes.Empty();
    AllNodes.Empty();
    CelIndexToNodeMap.Empty();

    BuildTreeFromCollisionData();

    if (TreeView.IsValid())
    {
        TreeView->RequestTreeRefresh();

        // Expand all root nodes by default
        for (const TSharedPtr<FCelAssetTreeNode>& RootNode : RootNodes)
        {
            TreeView->SetItemExpansion(RootNode, true);
        }
    }
}

void SCelAssetTree::BuildTreeFromCollisionData()
{
    UCollisionData* Data = CollisionData.Get();
    if (!Data)
    {
        return;
    }

    // Build a map of category paths to nodes
    TMap<FString, TSharedPtr<FCelAssetTreeNode>> CategoryMap;
    
    TMap<FGameplayTag, int32> SeenTags;  // For duplicate detection
    TSharedPtr<FCelAssetTreeNode> ProblemsCategory;

    for (int32 CelIdx = 0; CelIdx < Data->CollisionFrames.Num(); ++CelIdx)
    {
        const FCollisionStruct& Cel = Data->CollisionFrames[CelIdx];
        
        // Check for problems
        bool bIsUnnamed = !Cel.CelName.IsValid();
        bool bIsDuplicate = false;
        if (!bIsUnnamed)
        {
            if (SeenTags.Find(Cel.CelName))
            {
                bIsDuplicate = true;
            }
            else
            {
                SeenTags.Add(Cel.CelName, CelIdx);
            }
        }
        
        if (bIsUnnamed || bIsDuplicate)
        {
            // Create Problems category on first problematic cel
            if (!ProblemsCategory.IsValid())
            {
                ProblemsCategory = MakeShared<FCelAssetTreeNode>(TEXT("Problems"));
                RootNodes.Insert(ProblemsCategory, 0);  // Always at the top
            }
            
            FString ProblemName = bIsUnnamed 
                ? FString::Printf(TEXT("Unnamed Cel at Index [%d]"), CelIdx)
                : FString::Printf(TEXT("[%s] Duplicate at [%d])"), *Cel.CelName.ToString(), CelIdx);
            
            const TCHAR* ProblemChars = *ProblemName;
            UE_LOG(LogCollisionEditor, Error, TEXT("%s"), ProblemChars);
            
            auto ProblemNode = MakeShared<FCelAssetTreeNode>(CelIdx, ProblemName, true);
            ProblemNode->Parent = ProblemsCategory;
            ProblemsCategory->Children.Add(ProblemNode);
            CelIndexToNodeMap.Add(CelIdx, ProblemNode);
            continue;
        }

        // Parse the GameplayTag path
        // We currently use the form Character.StateCategory[.Subcategory].State.[Substate].[Index]
        FString TagString = Cel.CelName.ToString();
        TArray<FString> PathParts;
        TagString.ParseIntoArray(PathParts, TEXT("."));

        if (PathParts.Num() == 0)
        {
            continue;
        }

        // Build tree structure from path
        // Skip the first part if it's a common prefix like "Cel"
        int32 StartIndex = 0;
        if (PathParts.Num() > 1 && PathParts[0].Equals(TEXT("Cel"), ESearchCase::IgnoreCase))
        {
            StartIndex = 1;
        }

        TSharedPtr<FCelAssetTreeNode> CurrentParent;
        FString CurrentPath;

        for (int32 i = StartIndex; i < PathParts.Num(); ++i)
        {
            const FString& Part = PathParts[i];
            CurrentPath = CurrentPath.IsEmpty() ? Part : (CurrentPath + TEXT(".") + Part);

            bool bIsLeaf = (i == PathParts.Num() - 1);

            if (!CurrentParent.IsValid())
            {
                // Looking for/creating a root node
                TSharedPtr<FCelAssetTreeNode>* ExistingRoot = CategoryMap.Find(CurrentPath);
                if (ExistingRoot && ExistingRoot->IsValid())
                {
                    // If this is a leaf and the existing node is a category, update its CelIndex
                    if (bIsLeaf && (*ExistingRoot)->IsCategory())
                    {
                        (*ExistingRoot)->SetCelIndex(CelIdx);
                        CelIndexToNodeMap.Add(CelIdx, *ExistingRoot);
                    }
                    CurrentParent = *ExistingRoot;
                }
                else
                {
                    TSharedPtr<FCelAssetTreeNode> NewNode = MakeShared<FCelAssetTreeNode>(
                        Part,
                        bIsLeaf ? CelIdx : INDEX_NONE
                    );
                    RootNodes.Add(NewNode);
                    AllNodes.Add(NewNode);
                    CategoryMap.Add(CurrentPath, NewNode);
                    CurrentParent = NewNode;

                    if (bIsLeaf)
                    {
                        CelIndexToNodeMap.Add(CelIdx, NewNode);
                    }
                }
            }
            else
            {
                // Creating/finding a child node
                TSharedPtr<FCelAssetTreeNode>* ExistingNode = CategoryMap.Find(CurrentPath);
                if (ExistingNode && ExistingNode->IsValid())
                {
                    // If this is a leaf and the existing node is a category, update its CelIndex
                    if (bIsLeaf && (*ExistingNode)->IsCategory())
                    {
                        (*ExistingNode)->SetCelIndex(CelIdx);
                        CelIndexToNodeMap.Add(CelIdx, *ExistingNode);
                    }
                    CurrentParent = *ExistingNode;
                }
                else
                {
                    TSharedPtr<FCelAssetTreeNode> NewNode = CurrentParent->FindOrCreateChild(
                        Part,
                        bIsLeaf ? CelIdx : INDEX_NONE
                    );
                    AllNodes.Add(NewNode);
                    CategoryMap.Add(CurrentPath, NewNode);
                    CurrentParent = NewNode;

                    if (bIsLeaf)
                    {
                        CelIndexToNodeMap.Add(CelIdx, NewNode);
                    }
                }
            }
        }
    }

    // Sort root nodes and their children alphabetically
    auto SortNodes = [](TArray<TSharedPtr<FCelAssetTreeNode>>& Nodes)
    {
        Nodes.Sort([](const TSharedPtr<FCelAssetTreeNode>& A, const TSharedPtr<FCelAssetTreeNode>& B)
        {
            // Categories before cels, then alphabetical
            if (A->IsCategory() != B->IsCategory())
            {
                return A->IsCategory();
            }
            return A->GetDisplayName() < B->GetDisplayName();
        });
    };

    TFunction<void(TSharedPtr<FCelAssetTreeNode>&)> SortRecursive = [&](TSharedPtr<FCelAssetTreeNode>& Node)
    {
        SortNodes(Node->Children);
        for (TSharedPtr<FCelAssetTreeNode>& Child : Node->Children)
        {
            SortRecursive(Child);
        }
    };

    SortNodes(RootNodes);
    for (TSharedPtr<FCelAssetTreeNode>& RootNode : RootNodes)
    {
        SortRecursive(RootNode);
    }
}

void SCelAssetTree::SetSelectedCel(const FGameplayTag& CelName)
{
    if (!TreeView.IsValid() || !CollisionData.IsValid())
    {
        return;
    }

    // Find cel index
    UCollisionData* Data = CollisionData.Get();
    for (int32 i = 0; i < Data->CollisionFrames.Num(); ++i)
    {
        if (Data->CollisionFrames[i].CelName == CelName)
        {
            TSharedPtr<FCelAssetTreeNode>* NodePtr = CelIndexToNodeMap.Find(i);
            if (NodePtr && NodePtr->IsValid())
            {
                // Expand parents
                TSharedPtr<FCelAssetTreeNode> Parent = (*NodePtr)->Parent.Pin();
                while (Parent.IsValid())
                {
                    TreeView->SetItemExpansion(Parent, true);
                    Parent = Parent->Parent.Pin();
                }

                TreeView->SetSelection(*NodePtr);
                TreeView->RequestScrollIntoView(*NodePtr);
            }
            break;
        }
    }
}

TSharedRef<ITableRow> SCelAssetTree::GenerateTreeRow(
    TSharedPtr<FCelAssetTreeNode> InNode,
    const TSharedRef<STableViewBase>& OwnerTable)
{
    FText DisplayText = FText::FromString(InNode->GetDisplayName());

    // Use different styling for categories vs cels
    FSlateFontInfo Font = InNode->IsCategory()
        ? FAppStyle::GetFontStyle("NormalFontBold")
        : FAppStyle::GetFontStyle("NormalFont");

    return SNew(STableRow<TSharedPtr<FCelAssetTreeNode>>, OwnerTable)
        [
            SNew(SHorizontalBox)
            + SHorizontalBox::Slot()
            .AutoWidth()
            .Padding(2.f, 1.f)
            .VAlign(VAlign_Center)
            [
                SNew(STextBlock)
                .Text(DisplayText)
                .Font(Font)
            ]
        ];
}

void SCelAssetTree::GetChildrenForNode(
    TSharedPtr<FCelAssetTreeNode> InNode,
    TArray<TSharedPtr<FCelAssetTreeNode>>& OutChildren)
{
    if (InNode.IsValid())
    {
        OutChildren = InNode->Children;
    }
}

void SCelAssetTree::OnSelectionChanged(
    TSharedPtr<FCelAssetTreeNode> SelectedNode,
    ESelectInfo::Type SelectInfo)
{
    if (!SelectedNode.IsValid() || !SelectedNode->IsCel())
    {
        return;
    }

    UCollisionData* Data = CollisionData.Get();
    if (!Data)
    {
        return;
    }

    int32 CelIdx = SelectedNode->GetCelIndex();
    if (Data->CollisionFrames.IsValidIndex(CelIdx))
    {
        OnCelSelectedDelegate.ExecuteIfBound(CelIdx);
    }
}

void SCelAssetTree::OnFilterTextChanged(const FText& InText)
{
    CurrentFilterString = InText.ToString();
    RefreshTree();
}
```


