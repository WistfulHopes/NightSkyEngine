// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimMetaData.h"
#include "NightSkyAnimMetaData.generated.h"

class UNightSkyAnimSequenceUserData;
/**
 * 
 */
UCLASS(CollapseCategories, EditInlineNew)
class NIGHTSKYENGINE_API UNightSkyAnimMetaData : public UAnimMetaData
{
	GENERATED_BODY()

public:
	UNightSkyAnimMetaData();

	UPROPERTY(EditAnywhere, Category = "Baked Animation")
	TSet<FName> CachedBoneNames;

	UPROPERTY(BlueprintReadOnly, Category = "Baked Animation")
	TObjectPtr<UNightSkyAnimSequenceUserData> UserData;
};
