// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State.h"
#include "InputBuffer.generated.h"

constexpr int32 InputSequenceSize = 20;
constexpr int32 InputBufferSize = 90;

/**
 * @brief The input buffer for a player object.
 *
 * Stores inputs every frame, and handles input checking.
 */
USTRUCT()
struct FInputBuffer
{
	GENERATED_BODY()
protected:
	/**
	 * The input sequence. Updated by the input being checked.
	 */
	FInputBitmask InputSequence[InputSequenceSize] = {  };
	/**
	 * How much time is allowed between inputs. Updated by the input being checked.
	 */
	int32 ImpreciseInputCount = 0;
	/**
	 * This value determines if the input buffer will consider disabled inputs.
	 * If true, and an input matches a disabled input on the same frame, the buffer will reject the sequence.
	 * Otherwise, the input sequence will be read as normal.
	 * Updated by the input being checked.
	 */
	bool bInputAllowDisable = true;
	
public:
	/**
	 * All stored inputs.
	 * Inputs are stored with the newest at the end and the oldest at the beginning.
	 */
	int32 InputBufferInternal[InputBufferSize] = { 16 };
	/**
	 * All disabled inputs.
	 * Upon a successful state transition, the last input will be disabled.
	 * If an input being checked matches a disabled input on the same frame,
	 * the input check will fail.
	 */
	int32 InputDisabled[InputBufferSize] = { 0 };

	/**
	 * @brief Stores the input for this frame.
	 * 
	 * @param Input The input bitmask to store.
	 */
	void Update(int32 Input);
	/**
	 * @brief Stores the input at an arbitrary buffer position. Intended for CPU usage.
	 * 
	 * @param Input The input bitmask to store.
	 * @param Index The index of the buffer to store at.
	 */
	void Emplace(int32 Input, uint32 Index);
	/**
	 * @brief Checks an input condition against the buffer.
	 * 
	 * @param InputCondition The input condition to check.
	 * @return If the input condition matches the buffer, return true. Otherwise return false.
	 */
	bool CheckInputCondition(const FInputCondition& InputCondition, bool bIsKara = false);

	/**
	 * Checks the input sequence against the buffer with the Normal method.
	 * @see EInputMethod
	 * 
	 * @return If the input sequence matches the buffer, return true. Otherwise return false. 
	 */
	bool CheckInputSequence() const;
	/**
	 * Checks the input sequence against the buffer with the Strict method.
	 * @see EInputMethod
	 * 
	 * @return If the input sequence matches the buffer, return true. Otherwise return false. 
	 */
	bool CheckInputSequenceStrict() const;
	/**
	 * Checks the input sequence against the buffer with the Once method.
	 * @see EInputMethod
	 * 
	 * @return If the input sequence matches the buffer, return true. Otherwise return false. 
	 */
	bool CheckInputSequenceOnce() const;
	/**
	 * Checks the input sequence against the buffer with the Once Strict method.
	 * @see EInputMethod
	 * 
	 * @return If the input sequence matches the buffer, return true. Otherwise return false. 
	 */
	bool CheckInputSequenceOnceStrict() const;
	/**
	 * Checks the input sequence against the buffer with the Once method.
	 * @see EInputMethod
	 * 
	 * @return If the input sequence matches the buffer, return true. Otherwise return false. 
	 */
	bool CheckInputSequencePressAndRelease() const;
	/**
	 * Checks the input sequence against the buffer with the Once Strict method.
	 * @see EInputMethod
	 * 
	 * @return If the input sequence matches the buffer, return true. Otherwise return false. 
	 */
	bool CheckInputSequencePressAndReleaseStrict() const;
	/**
	 * Checks the input sequence against the buffer with the Negative method.
	 * @see EInputMethod
	 * 
	 * @return If the input sequence matches the buffer, return true. Otherwise return false. 
	 */
	bool CheckInputSequenceNegative() const;
	/**
	 * Checks the input sequence against the buffer with the Negative Strict method.
	 * @see EInputMethod
	 * 
	 * @return If the input sequence matches the buffer, return true. Otherwise return false. 
	 */
	bool CheckInputSequenceNegativeStrict() const;
	/**
	 * Flips the directional inputs in the buffer. For use after a character switches sides.
	 */
	void FlipInputsInBuffer();
};