// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NightSkySaveInfo.h"
#include "NightSkySettingsInfo.generated.h"

class UInputAction;

/**
 * 
 */
UCLASS()
class NIGHTSKYENGINE_API UNightSkySettingsInfo : public UNightSkySaveInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	int32 AntiAliasingMethod;
	UPROPERTY(BlueprintReadWrite)
	int32 GlobalIlluminationMethod;
	UPROPERTY(BlueprintReadWrite)
	TMap<UInputAction*, FKey> RemappedBattleKeys;
};
