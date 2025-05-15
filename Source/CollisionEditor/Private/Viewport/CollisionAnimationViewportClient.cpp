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