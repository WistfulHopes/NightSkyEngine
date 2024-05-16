#include "CollisionDataEditorToolkit.h"
#include "Logging.h"
#include "Battle/Actors/PlayerObject.h"
#include "Data/CollisionData.h"
#include "Editor/PropertyEditor/Public/PropertyEditorModule.h"
#include "Viewport/HitboxAnimationPreviewScene.h"
#include "Viewport/HitboxAnimationViewport.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Text/STextBlock.h"


#define LOCTEXT_NAMESPACE "CollisionDataEditor"

FCollisionDataEditorToolkit::FCollisionDataEditorToolkit()
{
}

FCollisionDataEditorToolkit::~FCollisionDataEditorToolkit()
{
}

void FCollisionDataEditorToolkit::Initialize(UCollisionData* InCollisionData, const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost)
{
    CollisionData = InCollisionData;

    // We need to add a timeline somewhere

    // Setup details view
    FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
    FDetailsViewArgs DetailsViewArgs;
    DetailsViewArgs.bUpdatesFromSelection = true;
    DetailsViewArgs.bLockable = false;
    DetailsViewArgs.bAllowSearch = true;
    DetailsViewArgs.bHideSelectionTip = true;

    DetailsView = PropertyModule.CreateDetailView(DetailsViewArgs);
    DetailsView->SetObject(CollisionData);

    // Setup PlayerObject BP picker
    InitializePlayerObjectBPPicker();
    // Setup state name combo box
    InitializeStateNameComboBox();

    // Set up viewport
    InitializePreviewScene();

    // Set up the animation timeline
    InitializeAnimationTimeline();

    // Define the layout
    const TSharedRef<FTabManager::FLayout> StandaloneLayout = FTabManager::NewLayout("Standalone_CollisionDataEditor_Layout")
        ->AddArea
        (
            FTabManager::NewPrimaryArea()
            ->SetOrientation(Orient_Horizontal)
            ->Split
            (
                // Left side - Viewport and timeline stacked vertically
                FTabManager::NewSplitter()
                ->SetOrientation(Orient_Vertical)
                ->Split
                (
					FTabManager::NewStack()
					->AddTab("ViewportTab", ETabState::OpenedTab)
					->SetHideTabWell(true)
					->SetSizeCoefficient(0.8f)
				)
                ->Split
                (
					FTabManager::NewStack()
					->AddTab("TimelineTab", ETabState::OpenedTab)
					->SetSizeCoefficient(0.2f)
				)
            )
            ->Split
            (
                // Right side - Details and Selector stacked vertically
                FTabManager::NewSplitter()
                ->SetOrientation(Orient_Vertical)
                ->Split
                (
                    FTabManager::NewStack()
                    ->AddTab("CollisionDataDetailsTab", ETabState::OpenedTab)
                    ->SetSizeCoefficient(0.8f) // Adjust to manage how much space this takes up
                )
                ->Split
                (
                    FTabManager::NewStack()
                    ->AddTab("PlayerObjectSelectorTab", ETabState::OpenedTab)
                    ->SetSizeCoefficient(0.2f) // Adjust similarly
                )
            )
        );

    // Register tab spawners
    // Ensure the ToolkitHost is valid and has a valid TabManager
    if (InitToolkitHost.IsValid() && InitToolkitHost->GetTabManager().IsValid())
    {
        TabManager = InitToolkitHost->GetTabManager(); // Do I need to set this or is it already set?
        RegisterTabSpawners(TabManager.ToSharedRef());
    }
    else
    {
        // Handle the error condition here, e.g., log an error or assert
        UE_LOG(LogHitboxEditor, Warning, TEXT("Toolkit host or tab manager is not valid."));
    }

    InitAssetEditor(Mode, InitToolkitHost, FName("CollisionDataEditorApp"), StandaloneLayout, true, true, TArray<UObject*>({ CollisionData }));
    PreviewScene->SetupScene(CollisionData);
}

void FCollisionDataEditorToolkit::InitializePlayerObjectBPPicker()
{
    PlayerObjectBPPicker = SNew(SClassPropertyEntryBox)
        .MetaClass(APlayerObject::StaticClass())
        .SelectedClass(PlayerObjectClass)
        .OnSetClass(this, &FCollisionDataEditorToolkit::OnPlayerObjectBPSelected)
        .AllowNone(false);
}

FName FCollisionDataEditorToolkit::GetCurrentCelName() const
{
    if (PlayerObject && !PlayerObject->CelName.IsNone())
		return PlayerObject->CelName;

    return NAME_None;
}

FName FCollisionDataEditorToolkit::GetCurrentAnimName() const
{
    if (PlayerObject && !PlayerObject->AnimName.IsNone())
        return PlayerObject->AnimName;

    return FName(TEXT("No Animation Name"));
}

FText FCollisionDataEditorToolkit::GetCurrentNames() const
{
    if (NameDisplayTextBlock.IsValid())
    {
        // Generate the new text based on current data
        FString CurrentCelName = GetCurrentCelName().ToString();
        FString CurrentAnimName = GetCurrentAnimName().ToString();
        FText NewText = FText::Format(LOCTEXT("CurrentNamesFormat", "Cel: {0} - Anim: {1}"), FText::FromString(CurrentCelName), FText::FromString(CurrentAnimName));

        // Update the text block
        return NewText;
    }
    return LOCTEXT("NoNames", "No names available");
}

FReply FCollisionDataEditorToolkit::OnUpdateNamesClicked()
{
	NameDisplayTextBlock->SetText(GetCurrentNames());

    return FReply::Handled();
}

void FCollisionDataEditorToolkit::OnClose()
{
	FAssetEditorToolkit::OnClose();
}

void FCollisionDataEditorToolkit::InitializeStateNameComboBox()
{
    // Add a single blank entry to AnimStructNames as a placeholder
    StateNames.Add(MakeShareable(new FName(TEXT(""))));
    SAssignNew(StateNameComboBox, SComboBox<TSharedPtr<FName>>)
        .OptionsSource(&StateNames)
        .OnSelectionChanged(this, &FCollisionDataEditorToolkit::OnStateNameSelected)
        .OnGenerateWidget(this, &FCollisionDataEditorToolkit::MakeAnimationNameWidget)
        [
            SNew(STextBlock)
                .Text(this, &FCollisionDataEditorToolkit::GetSelectedState)
        ];
}

void FCollisionDataEditorToolkit::UpdateStateNameComboBox()
{
    if (!PlayerObject || PlayerObject->StoredStateMachine.States.Num() == 0)
        StateNames.Add(MakeShareable(new FName(TEXT(""))));

    StateNameComboBox->RefreshOptions();
}

void FCollisionDataEditorToolkit::OnStateNameSelected(TSharedPtr<FName> SelectedItem, ESelectInfo::Type SelectInfo)
{
    if (SelectedItem.IsValid() && !SelectedItem->IsNone())
    {
        SelectedState = *SelectedItem.Get();
        PlayerObject->StoredStateMachine.ForceSetState(SelectedState);
        PlayerObject->StoredStateMachine.Update();
        MaxCelCount = PlayerObject->StoredStateMachine.CurrentState->CelIndex;

        //Update HitboxHandler
        HitboxHandler->SetHitboxData(CollisionData->GetByCelName(GetCurrentCelName().ToString()).Boxes);
      OnUpdateNamesClicked();
    }
}

TSharedRef<SWidget> FCollisionDataEditorToolkit::MakeAnimationNameWidget(TSharedPtr<FName> InItem)
{
    return SNew(STextBlock)
        .Text(FText::FromName(*InItem.Get()));
}

void FCollisionDataEditorToolkit::OnPlayerObjectBPSelected(const UClass* Class)
{
    if (!Class) return;
    PlayerObjectClass = const_cast<UClass*>(Class);
    PlayerObject = PreviewScene->SetPlayerObject(Class);
    SelectedState = "Stand";
    PlayerObject->StoredStateMachine.ForceSetState(SelectedState);
    PlayerObject->StoredStateMachine.Update();
    if (PlayerObject->StoredStateMachine.CurrentState)
    {
        MaxCelCount = PlayerObject->StoredStateMachine.CurrentState->CelIndex;
    }
    UE_LOG(LogHitboxEditor, Log, TEXT("Selected PlayerObject: %s"), *PlayerObject->GetName());
    StateNames.Empty();
    for (const auto& StateName : PlayerObject->StoredStateMachine.StateNames)
    {
        StateNames.Add(MakeShareable(new FName(StateName)));
    }
    UpdateStateNameComboBox();

    HitboxHandler->SetHitboxData(CollisionData->GetByCelName(GetCurrentCelName().ToString()).Boxes);
  OnUpdateNamesClicked();
}

TSharedRef<SDockTab> FCollisionDataEditorToolkit::SpawnTab_CollisionDataDetails(const FSpawnTabArgs& Args)
{
    return SNew(SDockTab)
        .Label(LOCTEXT("CollisionDataDetailsTabLabel", "Collision Data Details"))
        .TabRole(ETabRole::NomadTab)
        [
            SNew(SBorder)
                .Padding(4)
                [DetailsView->AsShared()]
        ];
}

TSharedRef<SDockTab> FCollisionDataEditorToolkit::SpawnTab_PlayerObjectSelector(const FSpawnTabArgs& Args)
{
    return SNew(SDockTab)
        .Label(LOCTEXT("PlayerObjectSelectorTabLabel", "Player Object Selector"))
        .TabRole(ETabRole::NomadTab)
        [
            SNew(SVerticalBox)
            + SVerticalBox::Slot()
            .AutoHeight()
            [
                SNew(SBorder)
                .Padding(4)
                [
                    PlayerObjectBPPicker.ToSharedRef()
                ]
            ]
            + SVerticalBox::Slot()
            .AutoHeight()
            [
                SNew(SBorder)
                .Padding(4)
                [
                    StateNameComboBox.ToSharedRef()
                ]
            ]
        ];
}

TSharedRef<SDockTab> FCollisionDataEditorToolkit::SpawnTab_ViewportTab(const FSpawnTabArgs& Args)
{
    return SNew(SDockTab)
        .Label(LOCTEXT("ViewportTabLabel", "Viewport"))
        .TabRole(ETabRole::MajorTab)
        [
            SNew(SBorder)
            .Padding(4)
            [
                PreviewViewportWidget.ToSharedRef()  // Make sure to use the viewport widget
            ]
        ];
}

TSharedRef<SDockTab> FCollisionDataEditorToolkit::SpawnTab_Timeline(const FSpawnTabArgs& Args)
{

    // If text block is not initialized, make a placeholder value
    if (!NameDisplayTextBlock.IsValid())
    {
		NameDisplayTextBlock = SNew(STextBlock)
			.Text(LOCTEXT("NoNames", "No names available"));
	}

    return SNew(SDockTab)
    .Label(LOCTEXT("TimelineTabLabel", "Timeline"))
    .TabRole(ETabRole::PanelTab)
    [
        SNew(SBorder)
        .Padding(4)
        [
            SNew(SHorizontalBox)
            //This slot will take 3/4 of the horizontal space
            +SHorizontalBox::Slot()
            [
                SNew(SHorizontalBox)
                +SHorizontalBox::Slot().AutoWidth()[PreviousButton.ToSharedRef()]
                +SHorizontalBox::Slot().FillWidth(1.0f)[TimelineSlider.ToSharedRef()]
                +SHorizontalBox::Slot().AutoWidth()[NextButton.ToSharedRef()]
                +SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center)[SNew(STextBlock).Text(FText::FromString("Cel Index: "))]
                +SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center)[SNew(STextBlock).Text_Lambda([this]()->FText { return CurrentFrame; })]
            ]

            //BoxControls
            +SHorizontalBox::Slot()
            .AutoWidth()
            .MaxWidth(300)
            .HAlign(HAlign_Right)
            .Padding(3)
            [
                SNew(SVerticalBox)
                +SVerticalBox::Slot().AutoHeight().Padding(3)
                [
                    SNew(SHorizontalBox)
                    +SHorizontalBox::Slot().MaxWidth(80.0f)[ SNew(STextBlock).Text(FText::FromString("X Position: "))]
                    +SHorizontalBox::Slot().MaxWidth(100.0f).AutoWidth() [HitboxHandler->NumericEntryBox_XPos.ToSharedRef()]
                ]
                +SVerticalBox::Slot().AutoHeight().Padding(3)
                [
                    SNew(SHorizontalBox)
                    +SHorizontalBox::Slot().MaxWidth(80.0f)[ SNew(STextBlock).Text(FText::FromString("Y Position: "))]
                    +SHorizontalBox::Slot().MaxWidth(100.0f).AutoWidth() [HitboxHandler->NumericEntryBox_YPos.ToSharedRef()]
                ]
                +SVerticalBox::Slot().AutoHeight().Padding(3)
                [
                    SNew(SHorizontalBox)
                    +SHorizontalBox::Slot().MaxWidth(80.0f)[ SNew(STextBlock).Text(FText::FromString("X Size: "))]
                    +SHorizontalBox::Slot().MaxWidth(100.0f).AutoWidth() [HitboxHandler->NumericEntryBox_XSize.ToSharedRef()]
                ]
                +SVerticalBox::Slot().AutoHeight().Padding(3)
                [
                    SNew(SHorizontalBox)
                    +SHorizontalBox::Slot().MaxWidth(80.0f)[ SNew(STextBlock).Text(FText::FromString("Y Size: "))]
                    +SHorizontalBox::Slot().AutoWidth() [HitboxHandler->NumericEntryBox_YSize.ToSharedRef()]
                ]

                //Button
                +SVerticalBox::Slot()
                .VAlign(VAlign_Bottom)
                [
                    SNew(SVerticalBox)
                    + SVerticalBox::Slot()
                    .FillHeight(1.0f)
                    .Padding(4)
                    + SVerticalBox::Slot()
                    .AutoHeight()
                    .Padding(4)
                    [
                        SNew(SVerticalBox)
                        + SVerticalBox::Slot()
                        .FillHeight(1.0f)
                        .HAlign(HAlign_Center)
                        [
                            SNew(SHorizontalBox)
                            + SHorizontalBox::Slot()
                            .AutoWidth()[SNew(STextBlock).Text_Lambda([this]()->FText { return FText::FromString("Hitbox Number: " + FString::FromInt(HitboxHandler->CurrentHitboxIndex)); })]
                            + SHorizontalBox::Slot()
                            .AutoWidth() [ HitboxHandler->DecreaseIndexButton.ToSharedRef() ]
                            + SHorizontalBox::Slot()
                            .AutoWidth() [ HitboxHandler->IncreaseIndexButton.ToSharedRef()]
                        ]
                        + SVerticalBox::Slot()
                        .FillHeight(1.0f)
                        .HAlign(HAlign_Right)
                        [
                            SAssignNew(NameDisplayTextBlock, STextBlock)  // Store the reference when creating the widget
                        ]
                    ]
                ]
            ]
        ]
    ];
}


void FCollisionDataEditorToolkit::InitializeAnimationTimeline()
{
    SAssignNew(TimelineSlider, SSlider)
        .Orientation(Orient_Horizontal)
        .Value(0.0f) // 0.0f by default
        .OnValueChanged(this, &FCollisionDataEditorToolkit::OnTimelineValueChanged);

    // Create left and right buttons
    SAssignNew(PreviousButton, SButton)
        .VAlign(VAlign_Center)
        .Text(FText::FromString("<"))
        .OnClicked(this, &FCollisionDataEditorToolkit::OnPreviousClick);

    SAssignNew(NextButton, SButton)
        .VAlign(VAlign_Center)
        .Text(FText::FromString(">"))
        .OnClicked(this, &FCollisionDataEditorToolkit::OnNextClick);

    HitboxHandler = MakeShareable(new FHitboxHandler());
    HitboxHandler->Init();
}

FText FCollisionDataEditorToolkit::GetSelectedState() const
{
    return FText::FromName(SelectedState);
}

int32 FCollisionDataEditorToolkit::CurrentFrameFromTimeline() const
{
	return FMath::RoundToInt(TimelineSlider->GetValue() * MaxCelCount);
}

// Set the current frame based on the slider value and update the animation playback
void FCollisionDataEditorToolkit::OnTimelineValueChanged(float NewValue)
{
    if (PlayerObject)
    {
        PlayerObject->TimeUntilNextCel = FMath::Lerp(PlayerObject->MaxCelTime, 0, NewValue);
    }
}

FReply FCollisionDataEditorToolkit::OnPreviousClick()
{
    UE_LOG(LogHitboxEditor, Display, TEXT("Previous button clicked."));
    if (!PlayerObject) return FReply::Handled();


    PlayerObject->CelIndex--;
    if (PlayerObject->CelIndex < 0) PlayerObject->StoredStateMachine.ForceSetState(SelectedState);
    else
    {
        PlayerObject->TimeUntilNextCel = 0;
        PlayerObject->StoredStateMachine.Update();
    }

  CurrentFrame = FText::FromString(FString::FromInt(PlayerObject->CelIndex));

  const FName CurrentCelName = GetCurrentCelName();
  if(CurrentCelName.IsNone())
  {
    UE_LOG(LogHitboxEditor, Error, TEXT("CurrentCelName is None"));
    return FReply::Handled();
  }

  HitboxHandler->SetHitboxData(CollisionData->GetByCelName(CurrentCelName.ToString()).Boxes);
  OnUpdateNamesClicked();
  return FReply::Handled();
}

FReply FCollisionDataEditorToolkit::OnNextClick()
{
  UE_LOG(LogHitboxEditor, Display, TEXT("Next button clicked."));
  if (!PlayerObject) return FReply::Handled();
  if (PlayerObject->CelIndex >= MaxCelCount) return FReply::Handled();

  PlayerObject->CelIndex++;
  PlayerObject->TimeUntilNextCel = 0;
  PlayerObject->StoredStateMachine.Update();

  CurrentFrame = FText::FromString(FString::FromInt(PlayerObject->CelIndex));

  const FName CurrentCelName = GetCurrentCelName();
  UE_LOG(LogHitboxEditor, Display, TEXT("CurrentCelName: %s"), *CurrentCelName.ToString());
  if(CurrentCelName.IsNone())
  {
    UE_LOG(LogHitboxEditor, Error, TEXT("CurrentCelName is None"));
    return FReply::Handled();
  }
  HitboxHandler->SetHitboxData(CollisionData->GetByCelName(CurrentCelName.ToString()).Boxes);
  OnUpdateNamesClicked();

  return FReply::Handled();
}

// Code to set the animation to a specific frames
void FCollisionDataEditorToolkit::UpdateAnimationPlayback(int32 Frame)
{
    if (PlayerObject)
    {
        PlayerObject->CelIndex = Frame;
	  }
}

void FCollisionDataEditorToolkit::InitializePreviewScene()
{
    if (!PreviewScene.IsValid())
    {
        PreviewScene = MakeShareable(new FHitboxAnimationPreviewScene(
            FPreviewScene::ConstructionValues()
            .AllowAudioPlayback(false)
            .ShouldSimulatePhysics(false)
            , SharedThis(this)
        ));
    }

    PreviewViewportWidget = SNew(SHitboxAnimationViewport, SharedThis(this), PreviewScene);
}

FName FCollisionDataEditorToolkit::GetToolkitFName() const
{
    return FName("CollisionDataEditor");
}

FText FCollisionDataEditorToolkit::GetBaseToolkitName() const
{
    return LOCTEXT("AppLabel", "Collision Data Editor");
}

FText FCollisionDataEditorToolkit::GetToolkitName() const
{
    return FText::FromString(CollisionData->GetName());
}

FString FCollisionDataEditorToolkit::GetWorldCentricTabPrefix() const
{
    return FString("CollisionDataEditor");
}

FLinearColor FCollisionDataEditorToolkit::GetWorldCentricTabColorScale() const
{
    return FLinearColor::White;
}

void FCollisionDataEditorToolkit::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
    UE_LOG(LogHitboxEditor, Warning, TEXT("Registering Tab Spawners"));
	WorkspaceMenuCategory = InTabManager->AddLocalWorkspaceMenuCategory(LOCTEXT("WorkspaceMenu_CollisionDataEditor", "Collision Data Editor"));

	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	InTabManager->RegisterTabSpawner("CollisionDataDetailsTab", FOnSpawnTab::CreateSP(this, &FCollisionDataEditorToolkit::SpawnTab_CollisionDataDetails))
		.SetDisplayName(LOCTEXT("CollisionDataDetailsTab", "Collision Data Details"))
		.SetGroup(WorkspaceMenuCategory.ToSharedRef());

	InTabManager->RegisterTabSpawner("PlayerObjectSelectorTab", FOnSpawnTab::CreateSP(this, &FCollisionDataEditorToolkit::SpawnTab_PlayerObjectSelector))
		.SetDisplayName(LOCTEXT("PlayerObjectSelectorTab", "Player Object Selector"))
		.SetGroup(WorkspaceMenuCategory.ToSharedRef());

    InTabManager->RegisterTabSpawner("ViewportTab", FOnSpawnTab::CreateSP(this, &FCollisionDataEditorToolkit::SpawnTab_ViewportTab))
        .SetDisplayName(LOCTEXT("ViewportTab", "Viewport"))
        .SetGroup(WorkspaceMenuCategory.ToSharedRef());

    InTabManager->RegisterTabSpawner("TimelineTab", FOnSpawnTab::CreateSP(this, &FCollisionDataEditorToolkit::SpawnTab_Timeline))
        .SetDisplayName(LOCTEXT("TimelineTab", "Timeline"))
        .SetGroup(WorkspaceMenuCategory.ToSharedRef());
}

void FCollisionDataEditorToolkit::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
    FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);

	InTabManager->UnregisterTabSpawner("CollisionDataDetailsTab");
	InTabManager->UnregisterTabSpawner("PlayerObjectSelectorTab");
	InTabManager->UnregisterTabSpawner("ViewportTab");
	InTabManager->UnregisterTabSpawner("TimelineTab");
}

#undef LOCTEXT_NAMESPACE
