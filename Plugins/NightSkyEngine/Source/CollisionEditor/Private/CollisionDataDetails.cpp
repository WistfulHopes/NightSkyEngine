#include "CollisionDataDetails.h"
#include "Data/CollisionData.h"
#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "PropertyHandle.h"
#include "ScopedTransaction.h"
#include "Styling/AppStyle.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"

#define LOCTEXT_NAMESPACE "CollisionDataDetails"

TSharedRef<IDetailCustomization> FCollisionDataDetails::MakeInstance()
{
	return MakeShareable(new FCollisionDataDetails);
}

void FCollisionDataDetails::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	CachedDetailBuilder = &DetailBuilder;

	TArray<TWeakObjectPtr<UObject>> ObjectsBeingCustomized;
	DetailBuilder.GetObjectsBeingCustomized(ObjectsBeingCustomized);

	if (ObjectsBeingCustomized.Num() != 1)
	{
		return;
	}

	CollisionDataPtr = Cast<UCollisionData>(ObjectsBeingCustomized[0].Get());
	if (!CollisionDataPtr.IsValid())
	{
		return;
	}

	CollisionFramesHandle = DetailBuilder.GetProperty(
		GET_MEMBER_NAME_CHECKED(UCollisionData, CollisionFrames));

	// Hide the default array display
	DetailBuilder.HideProperty(CollisionFramesHandle);

	// Also hide the transient editor property
	DetailBuilder.HideProperty(GET_MEMBER_NAME_CHECKED(UCollisionData, EditorSelectedIndex));

	IDetailCategoryBuilder& Category = DetailBuilder.EditCategory(
		"Selected Cel",
		LOCTEXT("SelectedCelCategory", "Selected Cel"),
		ECategoryPriority::Important);

	BuildSelectedCelView(DetailBuilder, Category);
}

void FCollisionDataDetails::BuildSelectedCelView(IDetailLayoutBuilder& DetailBuilder, IDetailCategoryBuilder& Category)
{
	UCollisionData* CollisionData = CollisionDataPtr.Get();
	if (!CollisionData)
	{
		return;
	}

	// Add "Add New Cel" button at the top
	Category.AddCustomRow(LOCTEXT("AddCelRow", "Add Cel"))
		.WholeRowContent()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.AutoWidth()
			[
				SNew(SButton)
				.Text(LOCTEXT("AddNewCel", "Add New Cel"))
				.OnClicked(this, &FCollisionDataDetails::OnAddNewCel)
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.Padding(2.f)
			[
				SNew(SButton)
				.Text(LOCTEXT("DeleteSelectedCel", "Delete Selected"))
				.IsEnabled(this, &FCollisionDataDetails::CanDeleteSelectedCel)
				.OnClicked(this, &FCollisionDataDetails::OnDeleteSelectedCel)
			]
		];
	
	Category.AddCustomRow(LOCTEXT("RefreshTreeRow", "Refresh Tree"))
		.WholeRowContent()
		[
			SNew(SButton)
			.Text(LOCTEXT("RefreshTree", "Refresh Tree"))
			.VAlign(VAlign_Center)
			.HAlign(HAlign_Center)
			.OnClicked(this, &FCollisionDataDetails::OnRefreshTree)
		];

#if WITH_EDITORONLY_DATA
	const int32 SelectedIndex = CollisionData->EditorSelectedIndex;

	if (SelectedIndex == INDEX_NONE || !CollisionData->CollisionFrames.IsValidIndex(SelectedIndex))
	{
		Category.AddCustomRow(LOCTEXT("NoSelectionRow", "No Selection"))
			.WholeRowContent()
			[
				SNew(SBox)
				.Padding(FMargin(8.f, 16.f))
				[
					SNew(STextBlock)
					.Text(LOCTEXT("SelectCelPrompt", "Select a cel from the tree to edit its properties"))
					.Font(FAppStyle::GetFontStyle("NormalFont"))
					.ColorAndOpacity(FSlateColor::UseSubduedForeground())
				]
			];
		return;
	}

	const FCollisionStruct& SelectedCel = CollisionData->CollisionFrames[SelectedIndex];

	// Show header with cel name
	Category.AddCustomRow(LOCTEXT("CelNameRow", "Tree View Name"))
		.NameContent()
		[
			SNew(STextBlock)
			.Text(LOCTEXT("CelNameLabel", "Registered Cel Name"))
			.Font(FAppStyle::GetFontStyle("NormalFontBold"))
		]
		.ValueContent()
		[
			SNew(STextBlock)
			.Text(FText::FromString(SelectedCel.CelName.ToString()))
			.Font(FAppStyle::GetFontStyle("NormalFont"))
		];

	// Get the property handle for this specific array element
	TSharedPtr<IPropertyHandle> ElementHandle = CollisionFramesHandle->GetChildHandle(SelectedIndex);
	if (!ElementHandle.IsValid())
	{
		return;
	}

	// Add all child properties
	uint32 NumChildren = 0;
	ElementHandle->GetNumChildren(NumChildren);

	for (uint32 ChildIdx = 0; ChildIdx < NumChildren; ++ChildIdx)
	{
		TSharedPtr<IPropertyHandle> ChildHandle = ElementHandle->GetChildHandle(ChildIdx);
		if (ChildHandle.IsValid())
		{
			// Show all properties including CelName (it's editable here)
			Category.AddProperty(ChildHandle);
		}
	}
#endif
}

FReply FCollisionDataDetails::OnAddNewCel()
{
	UCollisionData* CollisionData = CollisionDataPtr.Get();
	if (!CollisionData)
	{
		return FReply::Handled();
	}

	FScopedTransaction Transaction(LOCTEXT("AddNewCelTransaction", "Add New Cel"));
	CollisionData->Modify();

	FCollisionStruct NewCel;
	CollisionData->CollisionFrames.Add(NewCel);

#if WITH_EDITORONLY_DATA
	// Select the new cel
	CollisionData->EditorSelectedIndex = CollisionData->CollisionFrames.Num() - 1;
	CollisionData->NotifyCollisionFramesChanged();
#endif

	if (CachedDetailBuilder)
	{
		CachedDetailBuilder->ForceRefreshDetails();
	}

	return FReply::Handled();
}

FReply FCollisionDataDetails::OnDeleteSelectedCel()
{
	UCollisionData* CollisionData = CollisionDataPtr.Get();
	if (!CollisionData)
	{
		return FReply::Handled();
	}

#if WITH_EDITORONLY_DATA
	const int32 SelectedIndex = CollisionData->EditorSelectedIndex;
	if (SelectedIndex == INDEX_NONE || !CollisionData->CollisionFrames.IsValidIndex(SelectedIndex))
	{
		return FReply::Handled();
	}

	FScopedTransaction Transaction(LOCTEXT("DeleteCelTransaction", "Delete Cel"));
	CollisionData->Modify();

	CollisionData->CollisionFrames.RemoveAt(SelectedIndex);

	// Adjust selection
	if (CollisionData->CollisionFrames.Num() == 0)
	{
		CollisionData->EditorSelectedIndex = INDEX_NONE;
	}
	else if (SelectedIndex >= CollisionData->CollisionFrames.Num())
	{
		CollisionData->EditorSelectedIndex = CollisionData->CollisionFrames.Num() - 1;
	}

	CollisionData->NotifyCollisionFramesChanged();

	if (CachedDetailBuilder)
	{
		CachedDetailBuilder->ForceRefreshDetails();
	}
#endif

	return FReply::Handled();
}

bool FCollisionDataDetails::CanDeleteSelectedCel() const
{
#if WITH_EDITORONLY_DATA
	UCollisionData* CollisionData = CollisionDataPtr.Get();
	if (CollisionData)
	{
		const int32 SelectedIndex = CollisionData->EditorSelectedIndex;
		return SelectedIndex != INDEX_NONE && CollisionData->CollisionFrames.IsValidIndex(SelectedIndex);
	}
#endif
	return false;
}

FReply FCollisionDataDetails::OnRefreshTree()
{
	UCollisionData* CollisionData = CollisionDataPtr.Get();
	if (!CollisionData)
	{
		return FReply::Handled();
	}

#if WITH_EDITORONLY_DATA
	CollisionData->NotifyCollisionFramesChanged();
#endif

	if (CachedDetailBuilder)
	{
		CachedDetailBuilder->ForceRefreshDetails();
	}

	return FReply::Handled();
}

void FCollisionDataDetails::OnCelSelected(const FGameplayTag& CelName)
{
	SelectedCelName = CelName;
	if (CachedDetailBuilder)
	{
		CachedDetailBuilder->ForceRefreshDetails();
	}
}

#undef LOCTEXT_NAMESPACE
