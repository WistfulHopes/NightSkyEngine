

# File CollisionAnimationViewportClient.cpp

[**File List**](files.md) **>** [**CollisionEditor**](dir_940e8f38acfe3acbe44a727b0224043a.md) **>** [**Private**](dir_b4aad7ce9c05cbacc2935f83ad755e41.md) **>** [**Viewport**](dir_29897cda01bed08dbaaebcd119403720.md) **>** [**CollisionAnimationViewportClient.cpp**](_collision_animation_viewport_client_8cpp.md)

[Go to the documentation of this file](_collision_animation_viewport_client_8cpp.md)


```C++
#include "Viewport/CollisionAnimationViewportClient.h"
#include "AdvancedPreviewScene.h"

FCollisionAnimationViewportClient::FCollisionAnimationViewportClient(const TSharedRef<SEditorViewport>& InEditorViewport, const TSharedRef<FAdvancedPreviewScene>& InPreviewScene)
    : FEditorViewportClient(nullptr, &InPreviewScene.Get(), StaticCastSharedRef<SEditorViewport>(InEditorViewport))
{
    AdvancedPreviewScene = static_cast<FAdvancedPreviewScene*>(PreviewScene);

    // Set initial viewport properties
    SetRealtime(true);
    DrawHelper.bDrawGrid = false;
    DrawHelper.bDrawPivot = false;
    DrawHelper.AxesLineThickness = 5;
    DrawHelper.PivotSize = 5;

    // Enable screen percentage rendering
    EngineShowFlags.SetScreenPercentage(true);

    // Set perspective as default view mode
    SetViewportType(LVT_Perspective);
    SetViewModes(VMI_Lit, VMI_Lit);
}

void FCollisionAnimationViewportClient::Tick(float DeltaSeconds)
{
    FEditorViewportClient::Tick(DeltaSeconds);

    // Set initial camera position and orientation
    SetViewLocation(FVector(0, 720, 175));
    SetViewRotation(FRotator(0, -90, 0));
    ViewFOV = 54;
}

FCollisionAnimationViewportClient::~FCollisionAnimationViewportClient()
{
    // Clean up code if necessary
}
```


