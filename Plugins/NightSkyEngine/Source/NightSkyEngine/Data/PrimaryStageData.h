// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PrimaryStageData.generated.h"

/**
 * 
 */
UCLASS()
class NIGHTSKYENGINE_API UPrimaryStageData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId("PrimaryStageData", GetFName());
	}

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FName StageName;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FText StageFriendlyName;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FText StageDescription;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UTexture2D* StageSelectIcon;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UTexture2D* StageSplashIcon;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FString StageURL;
};
