// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "NightSkyEngine/Battle/State.h"
#include "StateData.generated.h"

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
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName DefaultStand = "Stand";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName DefaultCrouch = "Crouch";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName DefaultFall = "VJump";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName DefaultJumpLanding = "JumpLanding";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName DefaultStandFlip = "StandFlip";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName DefaultCrouchFlip = "CrouchFlip";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName DefaultJumpFlip = "JumpFlip";

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName DefaultStandBlock = "StandBlock";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName DefaultCrouchBlock = "CrouchBlock";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName DefaultAirBlock = "AirBlock";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName DefaultStandBlockEnd = "StandBlockEnd";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName DefaultCrouchBlockEnd = "CrouchBlockEnd";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName DefaultAirBlockEnd = "AirBlockEnd";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName DefaultGuardBreakStand = "GuardBreakStand";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName DefaultGuardBreakCrouch = "GuardBreakCrouch";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName DefaultGuardBreakAir = "GuardBreakAir";

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString DefaultStandHitstunPrefix = "Hitstun";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString DefaultCrouchHitstunPrefix = "CrouchHitstun";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName DefaultBLaunch = "BLaunch";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName DefaultVLaunch = "VLaunch";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName DefaultFLaunch = "FLaunch";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName DefaultBlowback = "Blowback";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName DefaultTailspin = "Tailspin";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName DefaultCrumple = "Crumple";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName DefaultFloatingCrumpleBody = "FloatingCrumpleBody";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName DefaultFloatingCrumpleHead = "FloatingCrumpleHead";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName DefaultWallBounce = "WallBounce";
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName DefaultFaceDownLoop = "FaceDownLoop";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName DefaultFaceUpLoop = "FaceUpLoop";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName DefaultFaceDownWakeUp = "FaceDownWakeUp";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName DefaultFaceUpWakeUp = "FaceUpWakeUp";
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName DefaultThrowLock = "ThrowLock";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName DefaultTagIn = "TagIn";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName DefaultRoundWin = "RoundWin";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName DefaultMatchWin = "MatchWin";

	UFUNCTION(BlueprintPure)
	UState* GetByStateName(const FName& StateName)
	{
		for (const auto& StateClass : StateArray)
		{
			const auto State = Cast<UState>(StateClass->ClassDefaultObject);
			if (State->Name == StateName) return State;
		}
		return nullptr;
	}
};
