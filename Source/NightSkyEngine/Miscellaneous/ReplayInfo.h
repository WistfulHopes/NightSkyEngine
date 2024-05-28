// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NightSkyGameInstance.h"
#include "NightSkySaveInfo.h"
#include "ReplayInfo.generated.h"

/**
 * 
 */
UCLASS()
class NIGHTSKYENGINE_API UReplaySaveInfo : public UNightSkySaveInfo
{
	GENERATED_BODY()

public:
	UReplaySaveInfo()  
	{
		Timestamp = FDateTime::Now();
		BattleData = FBattleData();  
		Version = "";
		ReplayIndex = -1;
		LengthInFrames = 0;
	}
	
	UPROPERTY(BlueprintReadOnly)  
	FDateTime Timestamp;
	UPROPERTY(BlueprintReadOnly)  
	FBattleData BattleData;
	UPROPERTY(BlueprintReadOnly)  
	FString Version;
	UPROPERTY(BlueprintReadOnly)
	int32 ReplayIndex;
	UPROPERTY()
	int32 LengthInFrames;
	UPROPERTY()
	TArray<int32> InputsP1;
	UPROPERTY()
	TArray<int32> InputsP2;
};
