

# File CollisionDataEditorToolkit.h

[**File List**](files.md) **>** [**CollisionEditor**](dir_940e8f38acfe3acbe44a727b0224043a.md) **>** [**Public**](dir_56ac83e1ee3de8bf475f92dfdd96fd55.md) **>** [**CollisionDataEditorToolkit.h**](_collision_data_editor_toolkit_8h.md)

[Go to the documentation of this file](_collision_data_editor_toolkit_8h.md)


```C++
#pragma once

#include "CoreMinimal.h"
#include "Toolkits/AssetEditorToolkit.h"
#include "Toolkits/IToolkitHost.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Text/STextBlock.h"
#include "PropertyCustomizationHelpers.h"
#include "Data/CollisionData.h"

class APlayerObject;
class FCollisionAnimationPreviewScene;
class SCollisionAnimationViewport;
class SCelAssetTree;


//These aren't used yet
enum ESceneInteractionMode
{
    Interaction_CameraMove,
    Interaction_EditCollisionBoxes
};

enum EBoxEditMode
{
    EditMode_None,
    EditMode_Add,
    EditMode_Move,
    EditMode_Delete
};

class FCollisionDataEditorToolkit : public FAssetEditorToolkit
{
public:
    FCollisionDataEditorToolkit();
    virtual ~FCollisionDataEditorToolkit() override;

    // Move some of these to private

    // Initializes the editor with the asset to be edited
    void Initialize(UCollisionData* InCollisionData, const EToolkitMode::Type Mode,
                    const TSharedPtr<IToolkitHost>& InitToolkitHost);

    // FAssetEditorToolkit interface
    virtual FName GetToolkitFName() const override; // Unique name for this toolkit type
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

    // Do I need to initialize a scene?
    void InitializePreviewScene();

    // Accessors
    // Get current animation name
    FText GetSelectedState() const;

private:
    TSharedPtr<IDetailsView> DetailsView;
    TSharedPtr<SClassPropertyEntryBox> PlayerObjectBPPicker;

    TSharedPtr<FCollisionAnimationPreviewScene> PreviewScene;
    TSharedPtr<SCollisionAnimationViewport> PreviewViewportWidget;

    UCollisionData* CollisionData{};
    TSharedPtr<SCelAssetTree> CelAssetTree;
    FGameplayTag SelectedCel;
    UClass* PlayerObjectClass = nullptr;
    APlayerObject* PlayerObject{};

    void InitializeCelAssetTree();
    void OnCelSelected(int32 CelIndex);
    void OnCollisionFramesChanged();

    void OnPlayerObjectBPSelected(const UClass* Class);
    void InitializePlayerObjectBPPicker();

    FGameplayTag GetCurrentCelName() const;

    void UpdateAnimationPlayback(int32 frame);

protected:
    virtual void OnClose() override;
};
```


