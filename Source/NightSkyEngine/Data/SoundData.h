// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SoundData.generated.h"

USTRUCT()
struct FSoundStruct
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	FString Name;
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
