// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "NightSkyEngine/Battle/Subroutine.h"
#include "SubroutineData.generated.h"

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
