// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CameraShakeData.generated.h"

USTRUCT(BlueprintType)
struct FCameraShakeStruct
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FString Name;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<UCameraShakeBase> CameraShake;
};


/**
 * 
 */
UCLASS()
class NIGHTSKYENGINE_API UCameraShakeData : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<FCameraShakeStruct> CamerShakeStructs;
};
