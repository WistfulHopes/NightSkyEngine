#pragma once

#include "CoreMinimal.h"
#include "Toolkits/AssetEditorToolkit.h"
#include "Toolkits/IToolkitHost.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Text/STextBlock.h"
#include "PropertyCustomizationHelpers.h"
#include "Data/CollisionData.h"
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
    virtual ~FCollisionDataEditorToolkit() override;

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
    TSharedRef<SDockTab> SpawnTab_HandlerTab(const FSpawnTabArgs& Args);

    // Do I need to initialize a scene?
    void InitializePreviewScene();

    // Accessors
    // Get current animation name
    FText GetSelectedState() const;


private:
    TSharedPtr<IDetailsView> DetailsView;  // The details view widget for collision data
    TSharedPtr<SClassPropertyEntryBox> PlayerObjectBPPicker; // Picker for animation data assets

    // Scene and viewport for previewing animations
    TSharedPtr<FHitboxAnimationPreviewScene> PreviewScene;
    TSharedPtr<SHitboxAnimationViewport> PreviewViewportWidget;

    // As of now CollisionData and AnimationData are not strictly tied
    // We need a way to get cel names from animations, or display states in the viewport somehow
    // And connect them to the collision data
    // I think animname_framenumber is a good cel naming scheme that we could make automatic
    UCollisionData* CollisionData{};
    TArray<TSharedPtr<FGameplayTag>> CelNames;
    TSharedPtr<SComboBox<TSharedPtr<FGameplayTag>>> CelNameComboBox;  // Combo box for selecting an animation data struct
    FGameplayTag SelectedCel;  // The name of the selected animation data asset, based on key in the AnimDatas map
    UClass* PlayerObjectClass = nullptr;  // The selected player object class
    APlayerObject* PlayerObject {};  // The current player object

    //Timeline
    TSharedPtr<FHitboxHandler> HitboxHandler;

    // A cool feature that is a long way off would be a button to automatically place initial hitboxes
    // This would be based on bone positions in the designated cel frame, if that is possible

    void InitializeStateNameComboBox();
    void OnCelNameSelected(TSharedPtr<FGameplayTag> SelectedItem, ESelectInfo::Type SelectInfo);
    TSharedRef<SWidget> MakeAnimationNameWidget(TSharedPtr<FGameplayTag> InItem);

    void OnPlayerObjectBPSelected(const UClass* Class);
    void InitializePlayerObjectBPPicker();

    FGameplayTag GetCurrentCelName() const;
    
    void UpdateAnimationPlayback(int32 frame);

protected:
    virtual void OnClose() override;
};
