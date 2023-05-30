// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PaperFlipbook.h"
#include "FlipbookData.generated.h"

USTRUCT(BlueprintType)
struct FFlipbookStruct
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FString Name;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UPaperFlipbook* Flipbook;
};

/**
 * 
 */
UCLASS()
class NIGHTSKYENGINE_API UFlipbookData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<FFlipbookStruct> FlipbookStructs;
};
