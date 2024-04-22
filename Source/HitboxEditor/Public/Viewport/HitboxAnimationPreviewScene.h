#pragma once

#include "CoreMinimal.h"
#include "AdvancedPreviewScene.h"
#include "Components/SkeletalMeshComponent.h"
#include "Data/CollisionData.h"

class APlayerObject;
class FCollisionDataEditorToolkit;

class FHitboxAnimationPreviewScene : public FAdvancedPreviewScene
{
public:
    FHitboxAnimationPreviewScene(ConstructionValues CVS, const TSharedRef<FCollisionDataEditorToolkit>& EditorToolkit);
    virtual ~FHitboxAnimationPreviewScene() override;

    virtual void Tick(float InDeltaTime) override;

    // Switch skeletal mesh on component
    APlayerObject* SetPlayerObject(const UClass* Class);
    
    // Setup the scene with animation data
    void SetupScene(UCollisionData* CollisionData);

    // Update the animation hitboxes
    void UpdateAnimationHitboxes();

private:
    APlayerObject* PreviewPlayerObject = nullptr;
    TWeakPtr<FCollisionDataEditorToolkit> EditorPtr;
    UCollisionData* CurrentCollisionData = nullptr;
    
    // Functions to update mesh and animations
    void UpdateMeshAndAnimation(float DeltaTime);

    // Draw hitboxes based on loaded collision data
    void DrawCollisionData();
};
