// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Engine/DeveloperSettingsBackedByCVars.h"
#include "UObject/SoftObjectPath.h"

#include "CommonLoadingScreenSettings.generated.h"

class UObject;

/**
 * Settings for a loading screen system.
 */
UCLASS(config=Game, defaultconfig, meta=(DisplayName="Common Loading Screen"))
class UCommonLoadingScreenSettings : public UDeveloperSettingsBackedByCVars
{
	GENERATED_BODY()

public:
	UCommonLoadingScreenSettings();

public:
	
	// The widget to load for the loading screen.
	UPROPERTY(config, EditAnywhere, Category=Display, meta=(MetaClass="/Script/UMG.UserWidget"))
	FSoftClassPath LoadingScreenWidget;

	// The z-order of the loading screen widget in the viewport stack
	UPROPERTY(config, EditAnywhere, Category=Display)
	int32 LoadingScreenZOrder = 10000;

	// How long to hold the loading screen up after other loading finishes (in seconds) to
	// try to give texture streaming a chance to avoid blurriness
	//
	// Note: This is not normally applied in the editor for iteration time, but can be 
	// enabled via HoldLoadingScreenAdditionalSecsEvenInEditor
 	UPROPERTY(config, EditAnywhere, Category=Configuration, meta=(ForceUnits=s, ConsoleVariable="CommonLoadingScreen.HoldLoadingScreenAdditionalSecs"))
	float HoldLoadingScreenAdditionalSecs = 2.0f;

	// The interval in seconds beyond which the loading screen is considered permanently hung (if non-zero).
 	UPROPERTY(config, EditAnywhere, Category=Configuration, meta=(ForceUnits=s))
	float LoadingScreenHeartbeatHangDuration = 0.0f;

	// The interval in seconds between each log of what is keeping a loading screen up (if non-zero).
 	UPROPERTY(config, EditAnywhere, Category=Configuration, meta=(ForceUnits=s))
	float LogLoadingScreenHeartbeatInterval = 5.0f;

	// When true, the reason the loading screen is shown or hidden will be printed to the log every frame.
	UPROPERTY(Transient, EditAnywhere, Category=Debugging, meta=(ConsoleVariable="CommonLoadingScreen.LogLoadingScreenReasonEveryFrame"))
	bool LogLoadingScreenReasonEveryFrame = 0;

	// Force the loading screen to be displayed (useful for debugging)
	UPROPERTY(Transient, EditAnywhere, Category=Debugging, meta=(ConsoleVariable="CommonLoadingScreen.AlwaysShow"))
	bool ForceLoadingScreenVisible = false;

	// Should we apply the additional HoldLoadingScreenAdditionalSecs delay even in the editor
	// (useful when iterating on loading screens)
	UPROPERTY(Transient, EditAnywhere, Category=Debugging)
	bool HoldLoadingScreenAdditionalSecsEvenInEditor = false;

	// Should we apply the additional HoldLoadingScreenAdditionalSecs delay even in the editor
	// (useful when iterating on loading screens)
	UPROPERTY(config, EditAnywhere, Category=Configuration)
	bool ForceTickLoadingScreenEvenInEditor = true;
};

