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
};
