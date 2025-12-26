

# File NightSkyAnimInstance.h

[**File List**](files.md) **>** [**Animation**](dir_9a82c917abb4553e2c2738125a0d5751.md) **>** [**NightSkyAnimInstance.h**](_night_sky_anim_instance_8h.md)

[Go to the documentation of this file](_night_sky_anim_instance_8h.md)


```C++
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "NightSkyAnimInstance.generated.h"

UCLASS()
class NIGHTSKYENGINE_API UNightSkyAnimInstance : public UAnimInstance
{
    GENERATED_BODY()

protected:
    virtual void Montage_Advance(float DeltaSeconds) override;
    
public:
    UPROPERTY(BlueprintReadWrite)
    UAnimMontage* RootMontage;
    
    UPROPERTY(BlueprintReadWrite)
    float CurrentAnimTime;

    UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
    void CreateRootMontage(UAnimSequenceBase* Asset, const FAlphaBlendArgs& BlendIn, const FAlphaBlendArgs& BlendOut);
};
```


