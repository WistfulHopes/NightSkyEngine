

# File SubroutineData.h

[**File List**](files.md) **>** [**Data**](dir_856985a2681c172443de4762aa082512.md) **>** [**SubroutineData.h**](_subroutine_data_8h.md)

[Go to the documentation of this file](_subroutine_data_8h.md)


```C++
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"
#include "Engine/DataAsset.h"
#include "NightSkyEngine/Battle/Script/Subroutine.h"
#include "SubroutineData.generated.h"

UE_DECLARE_GAMEPLAY_TAG_EXTERN(Subroutine_Cmn_MatchInit);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Subroutine_MatchInit);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Subroutine_Cmn_RoundInit);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Subroutine_RoundInit);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Subroutine_Cmn_OnUpdate);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Subroutine_OnUpdate);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Subroutine_Cmn_OnStateChange);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Subroutine_OnStateChange);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Subroutine_Cmn_PostStateChange);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Subroutine_PostStateChange);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Subroutine_Cmn_OnComboEnd);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Subroutine_OnComboEnd);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Subroutine_Cmn_AnyCancel_Air);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Subroutine_Cmn_OnLanding);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Subroutine_OnLanding);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Subroutine_ThrowParam_Ground);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Subroutine_ThrowParam_Air);


UCLASS()
class NIGHTSKYENGINE_API USubroutineData : public UDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TArray<TSubclassOf<USubroutine>> SubroutineArray;
};
```


