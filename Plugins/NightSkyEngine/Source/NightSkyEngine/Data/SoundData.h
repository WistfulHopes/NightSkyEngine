﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"
#include "Engine/DataAsset.h"
#include "SoundData.generated.h"

UE_DECLARE_GAMEPLAY_TAG_EXTERN(Sound_Hit_Punch_S);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Sound_Hit_Punch_M);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Sound_Hit_Punch_L);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Sound_Hit_Punch_SP);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Sound_Hit_Kick_S);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Sound_Hit_Kick_M);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Sound_Hit_Kick_L);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Sound_Hit_Kick_SP);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Sound_Hit_Slash_S);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Sound_Hit_Slash_M);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Sound_Hit_Slash_L);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Sound_Hit_Slash_SP);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Sound_Hit_Clash);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Sound_Guard);

USTRUCT()
struct FSoundStruct
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	FGameplayTag Name;
	UPROPERTY(EditAnywhere)
	USoundBase* SoundWave;
	UPROPERTY(EditAnywhere)
	float MaxDuration = 60;
	
};

/**
 * 
 */
UCLASS()
class NIGHTSKYENGINE_API USoundData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	TArray<FSoundStruct> SoundDatas;
};
