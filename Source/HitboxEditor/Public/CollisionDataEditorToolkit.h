#pragma once

#include "CoreMinimal.h"
#include "Toolkits/AssetEditorToolkit.h"
#include "Toolkits/IToolkitHost.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Text/STextBlock.h"
#include "PropertyCustomizationHelpers.h"
#include "Data/CollisionData.h"
#include "Widgets/Input/SSlider.h"
#include "HitboxHandler.h"

class APlayerObject;
class FHitboxAnimationPreviewScene;
class SHitboxAnimationViewport;


//These aren't used yet
/**
 * The different modes of interaction in the Scene.
 */
enum ESceneInteractionMode
{
    Interaction_CameraMove,
    Interaction_EditCollisionBoxes
};

/**
 * The different modes of editing collision boxes.
 */
enum EBoxEditMode
{
    EditMode_None,
	EditMode_Add,
	EditMode_Move,
	EditMode_Delete
};
/**
 * Toolkit for editing collision data assets for Night Sky.
 */
class HITBOXEDITOR_API FCollisionDataEditorToolkit : public FAssetEditorToolkit
{
public:
    FCollisionDataEditorToolkit();
    virtual ~FCollisionDataEditorToolkit();

    // Move some of these to private

    // Initializes the editor with the asset to be edited
    void Initialize(UCollisionData* InCollisionData, const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost);

    // FAssetEditorToolkit interface
    virtual FName GetToolkitFName() const override;  // Unique name for this toolkit type
    virtual FText GetBaseToolkitName() const override; // Display name for the toolkit
    virtual FText GetToolkitName() const override;
    virtual FString GetWorldCentricTabPrefix() const override; // Prefix for tabs in world-centric mode
    virtual FLinearColor GetWorldCentricTabColorScale() const override;

    // Tab management
    virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
    virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;

    TSharedRef<SDockTab> SpawnTab_CollisionDataDetails(const FSpawnTabArgs& Args);
    TSharedRef<SDockTab> SpawnTab_PlayerObjectSelector(const FSpawnTabArgs& Args);
    TSharedRef<SDockTab> SpawnTab_ViewportTab(const FSpawnTabArgs& Args);
    TSharedRef<SDockTab> SpawnTab_Timeline(const FSpawnTabArgs& Args);

    // Do I need to initialize a scene?
    void InitializePreviewScene();
    void OnNumericEntryBox_XPos_Changed(int i);
    TOptional<int32> GetCurrentXPos() const;

    void InitializeAnimationTimeline();

    // Accessors
    // Get current animation name
    FText GetSelectedState() const;


private:
    TSharedPtr<IDetailsView> DetailsView;  // The details view widget for collision data
    TSharedPtr<SClassPropertyEntryBox> PlayerObjectBPPicker; // Picker for animation data assets

    // Scene and viewport for previewing animations
    TSharedPtr<FHitboxAnimationPreviewScene> PreviewScene;
    TSharedPtr<SHitboxAnimationViewport> PreviewViewportWidget;

    // As of now CollisionData and AnimationData are not not strictly tied
    // We need a way to get cel names from animations, or display states in the viewport somehow
    // And connect them to the collision data
    // I think animname_framenumber is a good cel naming scheme that we could make automatic
    UCollisionData* CollisionData;
    TArray<TSharedPtr<FName>> StateNames;
    TSharedPtr<SComboBox<TSharedPtr<FName>>> StateNameComboBox;  // Combo box for selecting an animation data struct
    TSharedPtr<STextBlock> NameDisplayTextBlock;  // Text block for displaying the current cel and animation names
    FName SelectedState;  // The name of the selected animation data asset, based on key in the AnimDatas map
    UClass* PlayerObjectClass = nullptr;  // The selected player object class
    APlayerObject* PlayerObject {};  // The current player object
    FText CurrentFrame = FText::FromString("0");  // The current frame of the animation sequence
    float MaxCelCount;

    //Timeline
    TSharedPtr<SSlider> TimelineSlider;  // Slider for selecting the frame of the animation sequence
    TSharedPtr<SButton> PreviousButton;
    TSharedPtr<SButton> NextButton;
    TSharedPtr<FHitboxHandler> HitboxHandler;

    // A cool feature that is a long way off would be a button to automatically place initial hitboxes
    // This would be based on bone positions in the designated cel frame, if that is possible

    void InitializeStateNameComboBox();
    void UpdateStateNameComboBox();
    void OnStateNameSelected(TSharedPtr<FName> SelectedItem, ESelectInfo::Type SelectInfo);
    TSharedRef<SWidget> MakeAnimationNameWidget(TSharedPtr<FName> InItem);

    void OnPlayerObjectBPSelected(const UClass* Class);
    void InitializePlayerObjectBPPicker();

    FName GetCurrentCelName() const;
    FName GetCurrentAnimName() const;
    FText GetCurrentNames() const;

    FReply OnUpdateNamesClicked();

    int32 CurrentFrameFromTimeline() const;
    int32 GetTotalFrames() const; // Implement
    void OnTimelineValueChanged(float NewValue);
    FReply OnPreviousClick();
    FReply OnNextClick();

    void UpdateAnimationPlayback(int32 frame);

protected:
    virtual void OnClose() override;
};
