#include "CollisionDataDetails.h"
#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "GameplayTagsEditorModule.h"
#include "PropertyHandle.h"
#include "ScopedTransaction.h"
#include "Data/CollisionData.h"
#include "Styling/AppStyle.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SUniformGridPanel.h"
#include "Widgets/Text/STextBlock.h"

#define LOCTEXT_NAMESPACE "NightSkyCollisionEditor"

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
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
				.OnClicked(this, &FCollisionDataDetails::OnAddNewCel)
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.Padding(2.f)
			[
				SNew(SButton)
				.Text(LOCTEXT("DeleteSelectedCel", "Delete Selected"))
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
				.IsEnabled(this, &FCollisionDataDetails::CanDeleteSelectedCel)
				.OnClicked(this, &FCollisionDataDetails::OnDeleteSelectedCel)
			]
		];
	
	Category.AddCustomRow(LOCTEXT("TemplateSelectedCelRow", "New Cel From Selected"))
		.WholeRowContent()
		[
			SNew(SButton)
			.Text(LOCTEXT("NewCelFromSelected", "New Cel From Selected"))
			.VAlign(VAlign_Center)
			.HAlign(HAlign_Center)
			.IsEnabled(this, &FCollisionDataDetails::CanTemplateSelectedCel)
			.OnClicked(this, &FCollisionDataDetails::OnTemplateSelectedCel)
		];
	
	Category.AddCustomRow(LOCTEXT("RefreshTreeRow", "Refresh Tree"))
		.WholeRowContent()
		[
			SNew(SButton)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
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

FReply FCollisionDataDetails::OnTemplateSelectedCel()
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

	const FCollisionStruct& SourceCel = CollisionData->CollisionFrames[SelectedIndex];

	// Default name: same as original but without the ending index (numbers) portion of the tag
	FGameplayTag NewCelDefaultName;
	if (SourceCel.CelName.IsValid())
	{
		FString TagString = SourceCel.CelName.ToString();
		int32 LastPeriodIndex;
		TagString.FindLastChar('.', LastPeriodIndex);
		if (LastPeriodIndex != INDEX_NONE)
		{
			// If the last portion of the tag is numeric, we use its parent as the default name
			auto LastTagString = TagString.RightChop(TagString.Len() - LastPeriodIndex);
			if (LastTagString.IsNumeric())
			{
				NewCelDefaultName = SourceCel.CelName.RequestDirectParent();
			}
			else
			{
				NewCelDefaultName = SourceCel.CelName;
			}
		}
		else
		{
			NewCelDefaultName = SourceCel.CelName;
		}
	}

	// ---- Dialog window for selecting the new tag name ----

	// Store result
	bool bUserConfirmed = false;
	
	const FVector2D InitialSize(450.0f, 500.0f);
	
	FWindowSizeLimits WindowSizeLimits;
	WindowSizeLimits.SetMinWidth(InitialSize.X).SetMinHeight(InitialSize.Y);
	
	// Need a shared ptr for the window so we can close it from button handlers
	TSharedRef<SWindow> PickerWindow = SNew(SWindow)
		.Title(LOCTEXT("PickCelTagTitle", "Pick Cel Tag"))
		.ClientSize(InitialSize)
		.SupportsMinimize(false)
		.SupportsMaximize(false)
		.SizingRule(ESizingRule::Autosized);

	PickerWindow->SetSizeLimits(WindowSizeLimits);
	
	// Build tag widget
	// IGameplayTagsEditorModule::Get invokes LoadModuleChecked
	IGameplayTagsEditorModule& TagsEditorModule = IGameplayTagsEditorModule::Get();

	// Editable single-tag field
	TSharedPtr<FGameplayTag> EditableNewName = MakeShared<FGameplayTag>(NewCelDefaultName);

	// Build widget
	TSharedRef<SWidget> TagWidget =
		TagsEditorModule.MakeGameplayTagWidget(
			FOnSetGameplayTag::CreateLambda(
				[&EditableNewName](FGameplayTag InTag)
				{
					*EditableNewName = InTag;
				}),
			EditableNewName,
			FString("") // TODO: second button with filtering
		);
	
	// Compose window content with tag widget + OK/Cancel
	PickerWindow->SetContent(
		SNew(SBorder)
		.BorderImage(FAppStyle::GetBrush("ToolPanel.GroupBorder"))
		[
			SNew(SVerticalBox)

			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(8.0f)
			[
				SNew(STextBlock)
				.Text(LOCTEXT("PickCelTagLabel", "Select a new cel tag"))
			]

			+ SVerticalBox::Slot()
			.FillHeight(1.0f)
			.Padding(8.0f)
			[
				TagWidget
			]

			+ SVerticalBox::Slot()
			.AutoHeight()
			.HAlign(HAlign_Right)
			.Padding(8.0f)
			[
				SNew(SUniformGridPanel)
				.SlotPadding(FMargin(2.0f))

				+ SUniformGridPanel::Slot(0, 0)
				[
					SNew(SButton)
					.Text(LOCTEXT("OK", "OK"))
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
					.OnClicked_Lambda(
						[&PickerWindow, &bUserConfirmed]()
						{
							bUserConfirmed = true;
							FSlateApplication::Get().RequestDestroyWindow(PickerWindow);
							return FReply::Handled();
						})
				]

				+ SUniformGridPanel::Slot(1, 0)
				[
					SNew(SButton)
					.Text(LOCTEXT("Cancel", "Cancel"))
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
					.OnClicked_Lambda(
						[&PickerWindow]()
						{
							FSlateApplication::Get().RequestDestroyWindow(PickerWindow);
							return FReply::Handled();
						})
				]
			]
		]);

	// This call BLOCKS until the modal window is closed
	FSlateApplication::Get().AddModalWindow(PickerWindow, nullptr);
	
	if (bUserConfirmed && EditableNewName.IsValid() && EditableNewName->IsValid())
	{
		// Re-validate after the modal dialog closes in case the array changed
		if (!CollisionData->CollisionFrames.IsValidIndex(SelectedIndex))
		{
			return FReply::Handled();
		}
		
		FScopedTransaction Transaction(LOCTEXT("TemplateSelectedCelTransaction", "New Cel From Selected"));
		CollisionData->Modify();
		
		FCollisionStruct NewCel = CollisionData->CollisionFrames[SelectedIndex];
		NewCel.CelName = *EditableNewName;

		const int32 NewIndex = CollisionData->CollisionFrames.Add(NewCel);
		CollisionData->EditorSelectedIndex = NewIndex;
		
		// Notify tree view and refresh the details panel to prevent stale property handles
		CollisionData->NotifyCollisionFramesChanged();
		
		if (CachedDetailBuilder)
		{
			CachedDetailBuilder->ForceRefreshDetails();
		}
	}
#endif
	
	return FReply::Handled();
}

bool FCollisionDataDetails::CanTemplateSelectedCel() const
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
