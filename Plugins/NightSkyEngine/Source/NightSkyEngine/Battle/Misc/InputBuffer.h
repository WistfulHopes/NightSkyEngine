// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NightSkyEngine/Battle/Script/State.h"
#include "InputBuffer.generated.h"

constexpr int32 InputSequenceSize = 0x10;
constexpr int32 InputBufferSize = 0x20;

/**
 * @brief The input buffer for a player object.
 *
 * Stores inputs every frame, and handles input checking.
 */
USTRUCT()
struct FInputBuffer
{
	GENERATED_BODY()

private:
	/**
	 * @brief Extracts the sequence from the input condition and add buffer to it for comparison logic.
	 *
	 * @param Input The input condition being checked.
	 */
	static TArray<FInputBitmask> InitInputSequence(const FInputCondition& InputCondition, bool disallowDirections = false);

public:
	
	/**
	 * @brief Cleans simultaneous opposite cardinal direction inputs.
	 * 
	 * @param Input The input bitmask.
	 * @return Cleaned input bitmask.
	 */
	static int32 SOCDClean(int32 Input);
	
	/**
	 * All stored inputs.
	 * Inputs are stored with the newest at the end and the oldest at the beginning.
	 */
	int32 InputBufferInternal[InputBufferSize] = { 16 };
	/**
	 * All input times.
	 * Input times are looped over and incremented every actionable frame.
	 */
	int32 InputTime[InputBufferSize] = {};

	/**
	 * Writes an input condition to the buffer. For use with CPU.
	 * @param InputCondition The input condition to write.
	 */
	void WriteInputCondition(const FInputCondition& InputCondition);
	
	/**
	 * @brief Stores the input for this frame.
	 * 
	 * @param Input The input bitmask to store.
	 * @param bStopped If the owning object is in hitstop/super freeze.
	 */
	void Update(int32 Input, bool bStopped = false);
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
	bool CheckInputCondition(const FInputCondition& InputCondition);

	/**
	 * Checks the input against the buffer at index i with the Normal method.
	 * @see EInputMethod
	 *
	 * @return If the input sequence matches the buffer, return true. Otherwise return false.
	 */
	bool CheckInput(int32 NeededInput, int i) const;

	/**
	 * Checks the input against the buffer at index i with the Strict method.
	 * @see EInputMethod
	 *
	 * @return If the input sequence matches the buffer, return true. Otherwise return false.
	 */
	bool CheckInputStrictDirections(int32 NeededInput, int i, bool ignoreEmptyNeeded = false) const;

	/**
	 * Checks the if the check input function should return from too many frames since last match or
	 * being out of inputs to check.
	 * @see EInputMethod
	 *
	 * @return If the input sequence matches the buffer, return true. Otherwise return false.
	 */
	bool CheckLastMatchOrDisallowedInputs(int FramesSinceLastMatch, int InputIndex, int i, const FInputCondition& InputCondition, const TArray<FInputBitmask>& InputSequence) const;

	int GetInputIndex(const TArray<FInputBitmask>& InputSequence) const;

	/**
	 * Checks the input sequence against the buffer with the Normal method.
	 * @see EInputMethod
	 * 
	 * @return If the input sequence matches the buffer, return true. Otherwise return false. 
	 */
	bool CheckInputSequence(bool Strict, const FInputCondition& InputCondition) const;
	/**
	 * Checks the input sequence against the buffer with the is up method.
	 * @see EInputMethod
	 * 
	 * @return If the input sequence matches the buffer, return true. Otherwise return false. 
	 */
	bool CheckInputSequenceIsUp(bool Strict, const FInputCondition& InputCondition) const;
	/**
	 * Checks the input sequence against the buffer with the Once method.
	 * @see EInputMethod
	 * 
	 * @return If the input sequence matches the buffer, return true. Otherwise return false. 
	 */
	bool CheckInputSequencePositiveEdge(const FInputCondition& InputCondition) const;
	/**
	 * Checks the input sequence against the buffer with the Once method.
	 * @see EInputMethod
	 * 
	 * @return If the input sequence matches the buffer, return true. Otherwise return false. 
	 */
	bool CheckInputSequencePressAndRelease(const FInputCondition& InputCondition) const;
	/**
	 * Checks the input sequence against the buffer with the Negative method.
	 * @see EInputMethod
	 * 
	 * @return If the input sequence matches the buffer, return true. Otherwise return false. 
	 */
	bool CheckInputSequenceNegativeEdge(const FInputCondition& InputCondition) const;
	/**
	 * Flips the directional inputs in the buffer. For use after a character switches sides.
	 */
	void FlipInputsInBuffer();
	/**
	 * Resets the input buffer, as if it were the start of a match.
	 */
	void ResetBuffer();
};