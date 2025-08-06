#pragma once

#include "CoreMinimal.h"
#include "SEditorViewport.h"
#include "AdvancedPreviewScene.h"
#include "SCommonEditorViewportToolbarBase.h"

class UAnimationAsset;
class FCollisionAnimationPreviewScene;
class FCollisionDataEditorToolkit;

// Define the viewport client
class FCollisionAnimationViewportClient : public FEditorViewportClient
{
public:
    FCollisionAnimationViewportClient(const TSharedRef<SEditorViewport>& InEditorViewport, const TSharedRef<FAdvancedPreviewScene>& InPreviewScene);
    virtual void Tick(float DeltaSeconds) override;
    
    virtual ~FCollisionAnimationViewportClient();

    /*FRenderTarget* GetRenderTarget() { return Viewport->GetRenderTargetTexture(); }
    FSceneInterface* GetScene() const { return (FSceneInterface*)(GetWorld()->Scene); }*/

private:

    FAdvancedPreviewScene* AdvancedPreviewScene;
};