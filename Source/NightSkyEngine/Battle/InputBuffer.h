// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State.h"
#include "InputBuffer.generated.h"

#pragma pack (push, 1)

/**
 * 
 */
USTRUCT()
struct FInputBuffer
{
	GENERATED_BODY()
protected:
	FInputBitmask InputSequence[20] = {  };
	int32 ImpreciseInputCount = 0; //how much time is allowed between inputs
	bool bInputAllowDisable = true;
public:
	int32 InputBufferInternal[90] = { 16 };
	int32 InputDisabled[90] = { 0 };
	
	void Tick(int32 Input);
	bool CheckInputCondition(const FInputCondition& InputCondition);
	bool CheckInputSequence() const;
	bool CheckInputSequenceStrict() const; //directional inputs must be exact
	bool CheckInputSequenceOnce() const;
	bool CheckInputSequenceOnceStrict() const;
	void FlipInputsInBuffer();
};

#pragma pack(pop)
