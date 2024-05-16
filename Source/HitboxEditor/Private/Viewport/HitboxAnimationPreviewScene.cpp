#include "Viewport/HitboxAnimationPreviewScene.h"
#include "Components/SkeletalMeshComponent.h"
#include "Data/CollisionData.h"
#include "CollisionDataEditorToolkit.h"
#include "DrawDebugHelpers.h"
#include "Battle/Actors/PlayerObject.h"

FHitboxAnimationPreviewScene::FHitboxAnimationPreviewScene(ConstructionValues CVS, const TSharedRef<FCollisionDataEditorToolkit>& EditorToolkit)
    : FAdvancedPreviewScene(CVS), EditorPtr(EditorToolkit)
{
    // Disable the default floor to customize the scene
    SetFloorVisibility(true, true);

    // Setup events or additional components if necessary
}

FHitboxAnimationPreviewScene::~FHitboxAnimationPreviewScene()
{
    // Cleanup or unregister anything necessary
}

void FHitboxAnimationPreviewScene::Tick(float InDeltaTime)
{
    FAdvancedPreviewScene::Tick(InDeltaTime);

    // Update animations and hitboxes as needed
    UpdateMeshAndAnimation(InDeltaTime);
    UpdateAnimationHitboxes();
}

APlayerObject* FHitboxAnimationPreviewScene::SetPlayerObject(const UClass* Class)
{
    if (PreviewPlayerObject) PreviewPlayerObject->Destroy();

    const auto PlayerObject = GetWorld()->SpawnActor<APlayerObject>(const_cast<UClass*>(Class));
    PreviewPlayerObject = PlayerObject;
    PreviewPlayerObject->InitPlayer();
    PreviewPlayerObject->SetDefaultComponentVisibility();

    TArray<USkeletalMeshComponent*> SkeletalMeshComponents;
    PreviewPlayerObject->GetComponents(USkeletalMeshComponent::StaticClass(), SkeletalMeshComponents);
    for (const auto Component : SkeletalMeshComponents)
    {
        Component->InitAnim(true);
        Component->SetUpdateAnimationInEditor(true);
    }

    return PreviewPlayerObject;
}

void FHitboxAnimationPreviewScene::SetupScene(UCollisionData* CollisionData)
{
    CurrentCollisionData = CollisionData;
}

void FHitboxAnimationPreviewScene::UpdateMeshAndAnimation(float DeltaTime)
{
    if (!PreviewPlayerObject) return;
    PreviewPlayerObject->EditorUpdate();

    TArray<USkeletalMeshComponent*> SkeletalMeshComponents;
    PreviewPlayerObject->GetComponents(USkeletalMeshComponent::StaticClass(), SkeletalMeshComponents);
    for (const auto Component : SkeletalMeshComponents)
    {
        Component->TickComponent(DeltaTime, ELevelTick::LEVELTICK_ViewportsOnly, nullptr);
    }
}

void FHitboxAnimationPreviewScene::DrawCollisionData()
{
    PreviewPlayerObject->CollisionView();
}

void FHitboxAnimationPreviewScene::UpdateAnimationHitboxes()
{
    if (!CurrentCollisionData || !PreviewPlayerObject) // || !PreviewComponent)
      return;

  //Clear Debug Draw Debug Lines
  FlushPersistentDebugLines(GetWorld());

  // Get Cel name and call DrawCollisionData
  DrawCollisionData();
}
