// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PrimaryCharaData.generated.h"

class APlayerObject;

/**
 * 
 */
UCLASS()
class NIGHTSKYENGINE_API UPrimaryCharaData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId("PrimaryCharaData");
	}

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FName CharaName;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FText CharaFriendlyName;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FText CharaDescription;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UTexture2D* CharaHUDIcon;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UTexture2D* CharaSelectIcon;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UTexture2D* CharaSplashIcon;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<APlayerObject> PlayerClass;
};
