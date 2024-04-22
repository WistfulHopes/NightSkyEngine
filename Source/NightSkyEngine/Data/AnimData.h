// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AnimData.generated.h"

USTRUCT(BlueprintType)
struct FAnimStruct
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FString Name;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UAnimSequenceBase* AnimSequence;
};

/**
 * 
 */
UCLASS(BlueprintType)
class NIGHTSKYENGINE_API UAnimData : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<FAnimStruct> AnimDatas;
};
