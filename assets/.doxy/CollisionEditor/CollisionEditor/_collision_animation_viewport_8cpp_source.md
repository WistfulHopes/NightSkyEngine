

# File CollisionAnimationViewport.cpp

[**File List**](files.md) **>** [**CollisionEditor**](dir_940e8f38acfe3acbe44a727b0224043a.md) **>** [**Private**](dir_b4aad7ce9c05cbacc2935f83ad755e41.md) **>** [**Viewport**](dir_29897cda01bed08dbaaebcd119403720.md) **>** [**CollisionAnimationViewport.cpp**](_collision_animation_viewport_8cpp.md)

[Go to the documentation of this file](_collision_animation_viewport_8cpp.md)


```C++
#include "Viewport/CollisionAnimationViewport.h"
#include "Viewport/CollisionAnimationPreviewScene.h"
#include "CollisionDataEditorToolkit.h"
#include "Viewport/CollisionAnimationViewportClient.h"
#include "Modules/ModuleManager.h"
#include "PropertyEditorModule.h"

#define LOCTEXT_NAMESPACE "NightSkyCollisionEditor"

SCollisionAnimationViewport::~SCollisionAnimationViewport()
{
    if (ViewportClient.IsValid())
    {
        ViewportClient->Viewport = nullptr;
    }
}

void SCollisionAnimationViewport::Construct(const FArguments& InArgs, TSharedPtr<FCollisionDataEditorToolkit> InEditorToolkit, TSharedPtr<FCollisionAnimationPreviewScene> InPreviewScene)
{
    EditorToolkit = InEditorToolkit;
    PreviewScene = InPreviewScene;

    SEditorViewport::Construct(SEditorViewport::FArguments());

    // What to put here?
}

FString SCollisionAnimationViewport::GetReferencerName() const
{
    return TEXT("SCollisionAnimationViewport");
}

TSharedRef<SEditorViewport> SCollisionAnimationViewport::GetViewportWidget()
{
    return SharedThis(this);
}

TSharedPtr<FExtender> SCollisionAnimationViewport::GetExtenders() const
{
    TSharedPtr<FExtender> Extender = MakeShareable(new FExtender);
    return Extender;
}

void SCollisionAnimationViewport::OnFloatingButtonClicked()
{
    // Handle special button actions here
}

void SCollisionAnimationViewport::OnFocusViewportToSelection()
{
    if (PreviewScene.IsValid())
    {
        // Implement FocusOnSelection
        //PreviewScene->FocusOnSelection();
    }
}

TSharedRef<FEditorViewportClient> SCollisionAnimationViewport::MakeEditorViewportClient()
{
    if (!ViewportClient.IsValid())
    {
        ViewportClient = MakeShareable(new FCollisionAnimationViewportClient(SharedThis(this), PreviewScene.ToSharedRef()));
    }

    return ViewportClient.ToSharedRef();
}

#undef LOCTEXT_NAMESPACE
```


