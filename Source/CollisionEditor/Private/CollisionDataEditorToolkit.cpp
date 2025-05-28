#include "CollisionDataEditorToolkit.h"
#include "Logging.h"
#include "Battle/Actors/PlayerObject.h"
#include "Data/CollisionData.h"
#include "Editor/PropertyEditor/Public/PropertyEditorModule.h"
#include "Viewport/CollisionAnimationPreviewScene.h"
#include "Viewport/CollisionAnimationViewport.h"
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

void FCollisionDataEditorToolkit::Initialize(UCollisionData* InCollisionData, const EToolkitMode::Type Mode,
                                             const TSharedPtr<IToolkitHost>& InitToolkitHost)
{
	CollisionData = InCollisionData;
	
	for (auto& Collision : CollisionData->CollisionFrames)
	{
		for (auto& Box : Collision.Boxes)
		{
			Box.EditorInit();
		}
	}

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

	// Define the layout
	const TSharedRef<FTabManager::FLayout> StandaloneLayout = FTabManager::NewLayout(
			"Standalone_CollisionDataEditor_Layout")
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
		UE_LOG(LogCollisionEditor, Warning, TEXT("Toolkit host or tab manager is not valid."));
	}

	InitAssetEditor(Mode, InitToolkitHost, FName("CollisionDataEditorApp"), StandaloneLayout, true, true,
	                TArray<UObject*>({CollisionData}));
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

FGameplayTag FCollisionDataEditorToolkit::GetCurrentCelName() const
{
	if (PlayerObject && PlayerObject->CelName.IsValid())
		return PlayerObject->CelName;

	return FGameplayTag::EmptyTag;
}

void FCollisionDataEditorToolkit::OnClose()
{
	FAssetEditorToolkit::OnClose();
}

void FCollisionDataEditorToolkit::InitializeStateNameComboBox()
{
	// Add a single blank entry to AnimStructNames as a placeholder
	for (auto Frame : CollisionData->CollisionFrames)
	{
		CelNames.Add(MakeShared<FGameplayTag>(Frame.CelName));
	}
	
	SAssignNew(CelNameComboBox, SComboBox<TSharedPtr<FGameplayTag>>)
	.OptionsSource(&CelNames)
	.OnSelectionChanged(this, &FCollisionDataEditorToolkit::OnCelNameSelected)
	.OnGenerateWidget(this, &FCollisionDataEditorToolkit::MakeAnimationNameWidget)
	[
		SNew(STextBlock)
		.Text(this, &FCollisionDataEditorToolkit::GetSelectedState)
	];
}

void FCollisionDataEditorToolkit::OnCelNameSelected(TSharedPtr<FGameplayTag> SelectedItem,
                                                    ESelectInfo::Type SelectInfo)
{
	if (SelectedItem.IsValid() && SelectedItem->IsValid())
	{
		SelectedCel = *SelectedItem.Get();
		if (PlayerObject) PlayerObject->SetCelName(SelectedCel);
	}
}

TSharedRef<SWidget> FCollisionDataEditorToolkit::MakeAnimationNameWidget(TSharedPtr<FGameplayTag> InItem)
{
	return SNew(STextBlock)
		.Text(FText::FromString(*InItem.Get()->ToString()));
}

void FCollisionDataEditorToolkit::OnPlayerObjectBPSelected(const UClass* Class)
{
	if (!Class) return;
	PlayerObjectClass = const_cast<UClass*>(Class);
	PlayerObject = PreviewScene->SetPlayerObject(Class);
	PlayerObject->SetCelName(SelectedCel);
	UE_LOG(LogCollisionEditor, Log, TEXT("Selected PlayerObject: %s"), *PlayerObject->GetName());
}

TSharedRef<SDockTab> FCollisionDataEditorToolkit::SpawnTab_CollisionDataDetails(const FSpawnTabArgs& Args)
{
	return SNew(SDockTab)
		.Label(LOCTEXT("CollisionDataDetailsTabLabel", "Collision Data Details"))
		.TabRole(ETabRole::NomadTab)
		[
			SNew(SBorder)
			.Padding(4)
			[
				DetailsView->AsShared()
			]
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
					CelNameComboBox.ToSharedRef()
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
				PreviewViewportWidget.ToSharedRef() // Make sure to use the viewport widget
			]
		];
}

FText FCollisionDataEditorToolkit::GetSelectedState() const
{
	return FText::FromString(SelectedCel.ToString());
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
		PreviewScene = MakeShareable(new FCollisionAnimationPreviewScene(
			FPreviewScene::ConstructionValues()
			.AllowAudioPlayback(false)
			.ShouldSimulatePhysics(false)
			, SharedThis(this)
		));
	}

	PreviewViewportWidget = SNew(SCollisionAnimationViewport, SharedThis(this), PreviewScene);
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
	UE_LOG(LogCollisionEditor, Warning, TEXT("Registering Tab Spawners"));
	WorkspaceMenuCategory = InTabManager->AddLocalWorkspaceMenuCategory(
		LOCTEXT("WorkspaceMenu_CollisionDataEditor", "Collision Data Editor"));

	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	InTabManager->RegisterTabSpawner("CollisionDataDetailsTab",
	                                 FOnSpawnTab::CreateSP(
		                                 this, &FCollisionDataEditorToolkit::SpawnTab_CollisionDataDetails))
	            .SetDisplayName(LOCTEXT("CollisionDataDetailsTab", "Collision Data Details"))
	            .SetGroup(WorkspaceMenuCategory.ToSharedRef());

	InTabManager->RegisterTabSpawner("PlayerObjectSelectorTab",
	                                 FOnSpawnTab::CreateSP(
		                                 this, &FCollisionDataEditorToolkit::SpawnTab_PlayerObjectSelector))
	            .SetDisplayName(LOCTEXT("PlayerObjectSelectorTab", "Player Object Selector"))
	            .SetGroup(WorkspaceMenuCategory.ToSharedRef());

	InTabManager->RegisterTabSpawner("ViewportTab",
	                                 FOnSpawnTab::CreateSP(this, &FCollisionDataEditorToolkit::SpawnTab_ViewportTab))
	            .SetDisplayName(LOCTEXT("ViewportTab", "Viewport"))
	            .SetGroup(WorkspaceMenuCategory.ToSharedRef());
}

void FCollisionDataEditorToolkit::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);

	InTabManager->UnregisterTabSpawner("CollisionDataDetailsTab");
	InTabManager->UnregisterTabSpawner("PlayerObjectSelectorTab");
	InTabManager->UnregisterTabSpawner("ViewportTab");
}

#undef LOCTEXT_NAMESPACE
