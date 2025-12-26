

# File ParticleData.h

[**File List**](files.md) **>** [**Data**](dir_856985a2681c172443de4762aa082512.md) **>** [**ParticleData.h**](_particle_data_8h.md)

[Go to the documentation of this file](_particle_data_8h.md)


```C++
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"
#include "Engine/DataAsset.h"
#include "ParticleData.generated.h"

UE_DECLARE_GAMEPLAY_TAG_EXTERN(Particle_Hit_S);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Particle_Hit_M);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Particle_Hit_L);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Particle_Hit_SP);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Particle_Hit_Clash);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Particle_Guard);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Particle_ThrowTech);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Particle_JumpSmoke_Land);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Particle_WallBounce);

USTRUCT(BlueprintType)
struct FParticleStruct
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadOnly, EditAnywhere)
    FGameplayTag Name;
    UPROPERTY(BlueprintReadOnly, EditAnywhere)
    class UNiagaraSystem* ParticleSystem;
};

UCLASS()
class NIGHTSKYENGINE_API UParticleData : public UDataAsset
{
    GENERATED_BODY()
    
public:
    UPROPERTY(BlueprintReadOnly, EditAnywhere)
    TArray<FParticleStruct> ParticleStructs;
};
```


