

# File CollisionAnimationPreviewScene.h

[**File List**](files.md) **>** [**CollisionEditor**](dir_940e8f38acfe3acbe44a727b0224043a.md) **>** [**Public**](dir_56ac83e1ee3de8bf475f92dfdd96fd55.md) **>** [**Viewport**](dir_d692cfa9987693da5da8910b9a0fc6c1.md) **>** [**CollisionAnimationPreviewScene.h**](_collision_animation_preview_scene_8h.md)

[Go to the documentation of this file](_collision_animation_preview_scene_8h.md)


```C++
#pragma once

#include "CoreMinimal.h"
#include "AdvancedPreviewScene.h"
#include "Components/SkeletalMeshComponent.h"
#include "Data/CollisionData.h"

class APlayerObject;
class FCollisionDataEditorToolkit;

class FCollisionAnimationPreviewScene : public FAdvancedPreviewScene
{
public:
    FCollisionAnimationPreviewScene(ConstructionValues CVS, const TSharedRef<FCollisionDataEditorToolkit>& EditorToolkit);
    virtual ~FCollisionAnimationPreviewScene() override;

    virtual void Tick(float InDeltaTime) override;

    // Switch skeletal mesh on component
    APlayerObject* SetPlayerObject(const UClass* Class);
    
    // Setup the scene with animation data
    void SetupScene(UCollisionData* CollisionData);

    // Update the animation hitboxes
    void UpdateCollisionView();

private:
    APlayerObject* PreviewPlayerObject = nullptr;
    TWeakPtr<FCollisionDataEditorToolkit> EditorPtr;
    UCollisionData* CurrentCollisionData = nullptr;
    
    // Functions to update mesh and animations
    void UpdateMeshAndAnimation(float DeltaTime);

    // Draw hitboxes based on loaded collision data
    void DrawCollisionData();
};
```


