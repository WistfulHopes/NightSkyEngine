// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "LoadingProcessInterface.generated.h"

/** Interface for things that might cause loading to happen which requires a loading screen to be displayed */
UINTERFACE(BlueprintType)
class COMMONLOADINGSCREEN_API ULoadingProcessInterface : public UInterface
{
	GENERATED_BODY()
};

class COMMONLOADINGSCREEN_API ILoadingProcessInterface
{
	GENERATED_BODY()

public:
	// Checks to see if this object implements the interface, and if so asks whether or not we should
	// be currently showing a loading screen
	static bool ShouldShowLoadingScreen(UObject* TestObject, FString& OutReason);

	virtual bool ShouldShowLoadingScreen(FString& OutReason) const
	{
		return false;
	}
};
