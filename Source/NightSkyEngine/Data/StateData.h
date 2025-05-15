// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"
#include "Engine/DataAsset.h"
#include "NightSkyEngine/Battle/State.h"
#include "StateData.generated.h"

UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Universal_Stand);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Universal_Crouch);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Universal_Jump_V);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Universal_JumpLanding);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Universal_StandFlip);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Universal_CrouchFlip);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Universal_JumpFlip);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Universal_StandBlock);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Universal_CrouchBlock);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Universal_AirBlock);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Universal_StandBlockEnd);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Universal_CrouchBlockEnd);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Universal_AirBlockEnd);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Universal_GuardBreakStand);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Universal_GuardBreakCrouch);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Universal_GuardBreakAir);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Universal_Hitstun_0);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Universal_Hitstun_1);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Universal_Hitstun_2);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Universal_Hitstun_3);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Universal_Hitstun_4);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Universal_Hitstun_5);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Universal_CrouchHitstun_0);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Universal_CrouchHitstun_1);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Universal_CrouchHitstun_2);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Universal_CrouchHitstun_3);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Universal_CrouchHitstun_4);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Universal_CrouchHitstun_5);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Universal_Launch_B);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Universal_Launch_V);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Universal_Launch_F);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Universal_Blowback);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Universal_Tailspin);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Universal_Crumple);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Universal_FloatingCrumpleBody);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Universal_FloatingCrumpleHead);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Universal_WallBounce);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Universal_FaceDownLoop);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Universal_FaceUpLoop);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Universal_FaceDownWakeUp);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Universal_FaceUpWakeUp);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Universal_Throw);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Universal_ThrowLock);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Universal_TagIn);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Universal_RoundWin);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Universal_MatchWin);

UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_BattleObject_KO_S);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_BattleObject_KO_M);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_BattleObject_KO_L);

/**
 * 
 */
UCLASS()
class NIGHTSKYENGINE_API UStateData : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TSubclassOf<UState>> StateArray;

	UFUNCTION(BlueprintPure)
	const UState* GetByStateName(const FGameplayTag& StateName) const
	{
		for (const auto& StateClass : StateArray)
		{
			const auto State = GetDefault<UState>(StateClass);
			if (State->Name == StateName) return State;
		}
		return nullptr;
	}
};
