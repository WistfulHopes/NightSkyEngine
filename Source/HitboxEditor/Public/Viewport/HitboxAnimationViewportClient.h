#pragma once

#include "CoreMinimal.h"
#include "SEditorViewport.h"
#include "AdvancedPreviewScene.h"
#include "SCommonEditorViewportToolbarBase.h"

class UAnimationAsset;
class FHitboxAnimationPreviewScene;
class FCollisionDataEditorToolkit;

// Define the viewport client
class FHitboxAnimationViewportClient : public FEditorViewportClient
{
public:
    FHitboxAnimationViewportClient(const TSharedRef<SEditorViewport>& InEditorViewport, const TSharedRef<FAdvancedPreviewScene>& InPreviewScene);
    virtual void Tick(float DeltaSeconds) override;
    
    virtual ~FHitboxAnimationViewportClient();

    /*FRenderTarget* GetRenderTarget() { return Viewport->GetRenderTargetTexture(); }
    FSceneInterface* GetScene() const { return (FSceneInterface*)(GetWorld()->Scene); }*/

    // Current animation
    UPROPERTY()
    UAnimSequenceBase* Animation;

private:

    FAdvancedPreviewScene* AdvancedPreviewScene;
};