// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "NightSkyEngine/Miscellaneous/NightSkyGameInstance.h"
#include "NightSkyEditorSettings.generated.h"

/**
 * 
 */
UCLASS(Config = EditorPerProjectUserSettings, DefaultConfig, meta = (DisplayName = "Night Sky Engine Editor Settings"), MinimalAPI)
class UNightSkyEditorSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	UNightSkyEditorSettings(const FObjectInitializer& ObjectInitializer);
	
	UPROPERTY(Config, EditAnywhere, Category = "Battle")
	FBattleData BattleData = FBattleData();
	
	static NIGHTSKYENGINE_API UNightSkyEditorSettings* Get();
	static NIGHTSKYENGINE_API const UNightSkyEditorSettings* GetConst();
};
