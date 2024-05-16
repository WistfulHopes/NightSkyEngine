#include "Viewport/HitboxAnimationViewport.h"
#include "Viewport/HitboxAnimationPreviewScene.h"
#include "CollisionDataEditorToolkit.h"
#include "Viewport/HitboxAnimationViewportClient.h"
#include "Modules/ModuleManager.h"
#include "PropertyEditorModule.h"

#define LOCTEXT_NAMESPACE "HitboxAnimationViewport"

SHitboxAnimationViewport::~SHitboxAnimationViewport()
{
    if (ViewportClient.IsValid())
    {
        ViewportClient->Viewport = nullptr;
    }
}

void SHitboxAnimationViewport::Construct(const FArguments& InArgs, TSharedPtr<FCollisionDataEditorToolkit> InEditorToolkit, TSharedPtr<FHitboxAnimationPreviewScene> InPreviewScene)
{
    EditorToolkit = InEditorToolkit;
    PreviewScene = InPreviewScene;

    SEditorViewport::Construct(SEditorViewport::FArguments());

    // What to put here?
}

FString SHitboxAnimationViewport::GetReferencerName() const
{
    return TEXT("SHitboxAnimationViewport");
}

TSharedRef<SEditorViewport> SHitboxAnimationViewport::GetViewportWidget()
{
    return SharedThis(this);
}

TSharedPtr<FExtender> SHitboxAnimationViewport::GetExtenders() const
{
    TSharedPtr<FExtender> Extender = MakeShareable(new FExtender);
    return Extender;
}

void SHitboxAnimationViewport::OnFloatingButtonClicked()
{
    // Handle special button actions here
}

void SHitboxAnimationViewport::OnFocusViewportToSelection()
{
    if (PreviewScene.IsValid())
    {
        // Implement FocusOnSelection
        //PreviewScene->FocusOnSelection();
    }
}

TSharedRef<FEditorViewportClient> SHitboxAnimationViewport::MakeEditorViewportClient()
{
    if (!ViewportClient.IsValid())
    {
        ViewportClient = MakeShareable(new FHitboxAnimationViewportClient(SharedThis(this), PreviewScene.ToSharedRef()));
    }

    return ViewportClient.ToSharedRef();
}

#undef LOCTEXT_NAMESPACE
