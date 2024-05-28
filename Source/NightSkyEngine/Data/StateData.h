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
	FString DefaultStand = "Stand";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString DefaultCrouch = "Crouch";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString DefaultFall = "VJump";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString DefaultJumpLanding = "JumpLanding";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString DefaultStandFlip = "StandFlip";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString DefaultCrouchFlip = "CrouchFlip";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString DefaultJumpFlip = "JumpFlip";

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString DefaultStandBlock = "StandBlock";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString DefaultCrouchBlock = "CrouchBlock";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString DefaultAirBlock = "AirBlock";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString DefaultStandBlockEnd = "StandBlockEnd";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString DefaultCrouchBlockEnd = "CrouchBlockEnd";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString DefaultAirBlockEnd = "AirBlockEnd";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString DefaultGuardBreakStand = "GuardBreakStand";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString DefaultGuardBreakCrouch = "GuardBreakCrouch";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString DefaultGuardBreakAir = "GuardBreakAir";

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString DefaultStandHitstunPrefix = "Hitstun";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString DefaultCrouchHitstunPrefix = "CrouchHitstun";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString DefaultBLaunch = "BLaunch";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString DefaultVLaunch = "VLaunch";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString DefaultFLaunch = "FLaunch";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString DefaultBlowback = "Blowback";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString DefaultTailspin = "Tailspin";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString DefaultCrumple = "Crumple";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString DefaultFloatingCrumpleBody = "FloatingCrumpleBody";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString DefaultFloatingCrumpleHead = "FloatingCrumpleHead";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString DefaultWallBounce = "WallBounce";
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString DefaultFaceDownLoop = "FaceDownLoop";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString DefaultFaceUpLoop = "FaceUpLoop";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString DefaultFaceDownWakeUp = "FaceDownWakeUp";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString DefaultFaceUpWakeUp = "FaceUpWakeUp";
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString DefaultThrowLock = "ThrowLock";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString DefaultTagIn = "TagIn";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString DefaultRoundWin = "RoundWin";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString DefaultMatchWin = "MatchWin";

	UFUNCTION(BlueprintPure)
	UState* GetByStateName(const FString& StateName)
	{
		for (const auto& StateClass : StateArray)
		{
			const auto State = Cast<UState>(StateClass->ClassDefaultObject);
			if (State->Name == StateName) return State;
		}
		return nullptr;
	}
};
