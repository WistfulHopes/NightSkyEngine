#pragma once

#include "CoreMinimal.h"
#include "SCommonEditorViewportToolbarBase.h"
#include "SEditorViewport.h"
#include "HitboxAnimationPreviewScene.h"
#include "CollisionDataEditorToolkit.h"
#include "HitboxAnimationViewportClient.h"

class SHitboxAnimationViewport : public SEditorViewport, public FGCObject, public ICommonEditorViewportToolbarInfoProvider
{
public:
    SLATE_BEGIN_ARGS(SHitboxAnimationViewport) {}
    SLATE_END_ARGS()

    // The scene
    TSharedPtr<FHitboxAnimationPreviewScene> PreviewScene;

    // Construct the viewport
    void Construct(const FArguments& InArgs, TSharedPtr<FCollisionDataEditorToolkit> InEditorToolkit, TSharedPtr<FHitboxAnimationPreviewScene> InPreviewScene);
    virtual ~SHitboxAnimationViewport() override;

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
    TSharedPtr<FHitboxAnimationViewportClient> ViewportClient;
    TWeakPtr<FCollisionDataEditorToolkit> EditorToolkit;
};
