#include "Viewport/CollisionAnimationPreviewScene.h"
#include "Components/SkeletalMeshComponent.h"
#include "Data/CollisionData.h"
#include "CollisionDataEditorToolkit.h"
#include "DrawDebugHelpers.h"
#include "Battle/Actors/PlayerObject.h"

FCollisionAnimationPreviewScene::FCollisionAnimationPreviewScene(ConstructionValues CVS, const TSharedRef<FCollisionDataEditorToolkit>& EditorToolkit)
    : FAdvancedPreviewScene(CVS), EditorPtr(EditorToolkit)
{
    // Disable the default floor to customize the scene
    SetFloorVisibility(true, true);

    // Setup events or additional components if necessary
}

FCollisionAnimationPreviewScene::~FCollisionAnimationPreviewScene()
{
    // Cleanup or unregister anything necessary
}

void FCollisionAnimationPreviewScene::Tick(float InDeltaTime)
{
    FAdvancedPreviewScene::Tick(InDeltaTime);

    // Update animations and Collisiones as needed
    UpdateMeshAndAnimation(InDeltaTime);
    UpdateCollisionView();
}

APlayerObject* FCollisionAnimationPreviewScene::SetPlayerObject(const UClass* Class)
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

void FCollisionAnimationPreviewScene::SetupScene(UCollisionData* CollisionData)
{
    CurrentCollisionData = CollisionData;
}

void FCollisionAnimationPreviewScene::UpdateMeshAndAnimation(float DeltaTime)
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

void FCollisionAnimationPreviewScene::DrawCollisionData()
{
    PreviewPlayerObject->CollisionView();
}

void FCollisionAnimationPreviewScene::UpdateCollisionView()
{
    if (!CurrentCollisionData || !PreviewPlayerObject) // || !PreviewComponent)
      return;

  //Clear Debug Draw Debug Lines
  FlushPersistentDebugLines(GetWorld());

  // Get Cel name and call DrawCollisionData
  DrawCollisionData();
}
