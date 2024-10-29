// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharaSelectData.generated.h"

class APlayerObject;

USTRUCT(BlueprintType)
struct FCharaSelectStruct
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FString CharaName;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UTexture2D* CharaTexture;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<APlayerObject> PlayerClass;
};

/**
 * 
 */
UCLASS()
class NIGHTSKYENGINE_API UCharaSelectData : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<FCharaSelectStruct> CharaSelectStructs;
};
