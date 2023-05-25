// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MaterialData.generated.h"

USTRUCT(BlueprintType)
struct FMaterialStruct
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FString Name;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UMaterialInterface*> Material;
};

/**
 * 
 */
UCLASS()
class NIGHTSKYENGINE_API UMaterialData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TArray<FMaterialStruct> MaterialStructs;
};
