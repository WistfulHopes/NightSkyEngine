// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "NightSkyEditorBlueprintLibrary.generated.h"

/**
 * 
 */
UCLASS()
class NIGHTSKYENGINEEDITOR_API UNightSkyEditorBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Gameplay Tags")
	static FGameplayTag GetGameplayTagFromName(FName Name);
};
