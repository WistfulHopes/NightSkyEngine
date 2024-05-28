// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State.h"
#include "SubroutineState.generated.h"

/**
 * Attempting to enter the state will actually call a subroutine instead.
 */
UCLASS()
class NIGHTSKYENGINE_API USubroutineState : public UState
{
	GENERATED_BODY()

public:
	// Which subroutine to call from the state
	UPROPERTY(EditAnywhere)
	FString SubroutineName;
	
	// Dummy CallExec, we don't want it to execute code
	virtual void CallExec() override {}
};
