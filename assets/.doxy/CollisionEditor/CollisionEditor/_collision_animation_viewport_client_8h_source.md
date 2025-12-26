

# File CollisionAnimationViewportClient.h

[**File List**](files.md) **>** [**CollisionEditor**](dir_940e8f38acfe3acbe44a727b0224043a.md) **>** [**Public**](dir_56ac83e1ee3de8bf475f92dfdd96fd55.md) **>** [**Viewport**](dir_d692cfa9987693da5da8910b9a0fc6c1.md) **>** [**CollisionAnimationViewportClient.h**](_collision_animation_viewport_client_8h.md)

[Go to the documentation of this file](_collision_animation_viewport_client_8h.md)


```C++
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
```


