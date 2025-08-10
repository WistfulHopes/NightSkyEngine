// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"
#include "Engine/DataAsset.h"
#include "NightSkyEngine/Battle/Subroutine.h"
#include "SubroutineData.generated.h"

UE_DECLARE_GAMEPLAY_TAG_EXTERN(Subroutine_Cmn_MatchInit);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Subroutine_MatchInit);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Subroutine_Cmn_RoundInit);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Subroutine_RoundInit);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Subroutine_Cmn_OnUpdate);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Subroutine_OnUpdate);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Subroutine_Cmn_OnStateChange);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Subroutine_OnStateChange);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Subroutine_Cmn_OnComboEnd);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Subroutine_OnComboEnd);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Subroutine_Cmn_AnyCancel_Air);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Subroutine_Cmn_OnLanding);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Subroutine_OnLanding);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Subroutine_ThrowParam_Ground);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Subroutine_ThrowParam_Air);


/**
 * 
 */
UCLASS()
class NIGHTSKYENGINE_API USubroutineData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TSubclassOf<USubroutine>> SubroutineArray;
};
