// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "StageData.generated.h"

USTRUCT(BlueprintType)
struct FStageStruct
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FString StageName;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UTexture2D* StageTexture;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FString StageURL;
};

/**
 * 
 */
UCLASS()
class NIGHTSKYENGINE_API UStageData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<FStageStruct> StageStructs;
};
