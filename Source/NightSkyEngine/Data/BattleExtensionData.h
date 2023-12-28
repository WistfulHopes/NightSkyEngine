// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "NightSkyEngine/Battle/BattleExtension.h"
#include "BattleExtensionData.generated.h"

/**
 * 
 */
UCLASS()
class NIGHTSKYENGINE_API UBattleExtensionData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TSubclassOf<UBattleExtension>> ExtensionArray;
};
