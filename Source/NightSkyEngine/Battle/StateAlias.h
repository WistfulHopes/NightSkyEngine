// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State.h"
#include "StateAlias.generated.h"

/**
 * An "alias" for an existing state. Allows giving different conditions for entering an existing state.
 */
UCLASS()
class NIGHTSKYENGINE_API UStateAlias : public UState
{
	GENERATED_BODY()

public:
	// Which state to enter from the alias
	UPROPERTY(EditAnywhere)
	FString StateToEnter;
	
	// Dummy CallExec, we don't want it to execute code
	virtual void CallExec() override {}
};
