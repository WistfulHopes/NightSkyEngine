#pragma once

#include "CoreMinimal.h"
#include "SCommonEditorViewportToolbarBase.h"
#include "SEditorViewport.h"
#include "CollisionAnimationPreviewScene.h"
#include "CollisionDataEditorToolkit.h"
#include "CollisionAnimationViewportClient.h"

class SCollisionAnimationViewport : public SEditorViewport, public FGCObject, public ICommonEditorViewportToolbarInfoProvider
{
public:
    SLATE_BEGIN_ARGS(SCollisionAnimationViewport) {}
    SLATE_END_ARGS()

    // The scene
    TSharedPtr<FCollisionAnimationPreviewScene> PreviewScene;

    // Construct the viewport
    void Construct(const FArguments& InArgs, TSharedPtr<FCollisionDataEditorToolkit> InEditorToolkit, TSharedPtr<FCollisionAnimationPreviewScene> InPreviewScene);
    virtual ~SCollisionAnimationViewport() override;

    // FGCObject interface
    virtual void AddReferencedObjects(FReferenceCollector& Collector) override {};
    virtual FString GetReferencerName() const override;
    // Toolbar interface
    virtual TSharedRef<SEditorViewport> GetViewportWidget() override;
    virtual TSharedPtr<FExtender> GetExtenders() const override;
    virtual void OnFloatingButtonClicked() override;
    virtual void OnFocusViewportToSelection() override; // Not sure this is needed yet

    // Construct the viewport
    virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;

private:
    TSharedPtr<FCollisionAnimationViewportClient> ViewportClient;
    TWeakPtr<FCollisionDataEditorToolkit> EditorToolkit;
};
