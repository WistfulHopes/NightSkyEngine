// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/NightSkyGameState.h"
#include "UObject/Object.h"
#include "BattleExtension.generated.h"

/**
 * @brief A customizable extension to the battle ruleset.
 *
 * Allows modifying some general battle behavior.
 */
UCLASS(BlueprintType, Blueprintable)
class NIGHTSKYENGINE_API UBattleExtension : public USerializableObj
{
	GENERATED_BODY()

public:
	/**
     * The owning game state.
     */
	UPROPERTY(BlueprintReadOnly)
	ANightSkyGameState* Parent;
	
	/**
	 * The name of the subroutine.
	 * Used to call the subroutine.
	 */
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FString Name;

	/**
	 * The primary function of the subroutine.
	 */
	UFUNCTION(BlueprintNativeEvent)
	void Exec();
};
