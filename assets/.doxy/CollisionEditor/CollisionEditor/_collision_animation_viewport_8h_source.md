

# File CollisionAnimationViewport.h

[**File List**](files.md) **>** [**CollisionEditor**](dir_940e8f38acfe3acbe44a727b0224043a.md) **>** [**Public**](dir_56ac83e1ee3de8bf475f92dfdd96fd55.md) **>** [**Viewport**](dir_d692cfa9987693da5da8910b9a0fc6c1.md) **>** [**CollisionAnimationViewport.h**](_collision_animation_viewport_8h.md)

[Go to the documentation of this file](_collision_animation_viewport_8h.md)


```C++
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
```


