// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "NightSkyEngine/Battle/BattleExtension.h"
#include "BattleExtensionData.generated.h"

UE_DECLARE_GAMEPLAY_TAG_EXTERN(BattleExtension_MatchInit);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(BattleExtension_RoundInit);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(BattleExtension_Update);

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
