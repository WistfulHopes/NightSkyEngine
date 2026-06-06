// Fill out your copyright notice in the Description page of Project Settings.


#include "InputBuffer.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(InputBuffer)

void FInputBuffer::WriteInputCondition(const FInputCondition& InputCondition)
{
	switch (InputCondition.Method)
	{
	case EInputMethod::Normal:
	case EInputMethod::Strict:
		{
			for (int i = 0; i < InputCondition.Sequence.Num(); i++)
			{
				Update(InputCondition.Sequence[i].InputFlag);
			}
			break;
		}
	case EInputMethod::PositiveEdge:
		{
			Update(INP_Neutral);
			for (int i = 0; i < InputCondition.Sequence.Num(); i++)
			{
				Update(InputCondition.Sequence[i].InputFlag);
			}
			break;
		}
	case EInputMethod::PressAndRelease:
		{
			for (int i = 0; i < InputCondition.Sequence.Num(); i++)
			{
				for (int j = 0; j < InputCondition.Sequence[i].Hold; j++)
				{
					Update(InputCondition.Sequence[i].InputFlag);
				}
			}
			break;
		}
	case EInputMethod::NegativeEdge:
		{
			for (int i = 0; i < InputCondition.Sequence.Num(); i++)
			{
				Update(InputCondition.Sequence[i].InputFlag);
				Update(INP_Neutral);
			}
			break;
		}
	default:
		break;
	}
}

int32 FInputBuffer::SOCDClean(int32 Input)
{
	if ((Input & INP_Up) && (Input & INP_Down)) {
		Input = Input & ~INP_Up & ~INP_Down;
	}
	if ((Input & INP_Left) && (Input & INP_Right)) {
		Input = Input & ~INP_Left & ~INP_Right;
	}
	return Input;
}

void FInputBuffer::Update(int32 Input, bool bStopped)
{
	Input =	SOCDClean(Input);
	if (!bStopped)
	{
		for (auto& Window : InputTime)
		{
			Window++;
		}
	}

	if (Input == InputBufferInternal[InputBufferSize - 1]) 
		return;
	
	for (int32 i = 0; i < InputBufferSize - 1; i++)
	{
		InputBufferInternal[i] = InputBufferInternal[i + 1];
		InputTime[i] = InputTime[i + 1];
	}
	InputBufferInternal[InputBufferSize - 1] = (Input | INP_Valid);
	InputTime[InputBufferSize - 1] = 0;
}

void FInputBuffer::Emplace(int32 Input, uint32 Index)
{
	if (Index > InputBufferSize - 1) return;

	InputBufferInternal[Index] |= (Input | INP_Valid);
}

bool FInputBuffer::CheckInputCondition(const FInputCondition& InputCondition)
{
	switch (InputCondition.Method)
	{
	case EInputMethod::Normal:
		return CheckInputSequence(false, InputCondition);
	case EInputMethod::Strict:
		return CheckInputSequence(true, InputCondition);
	case EInputMethod::PositiveEdge:
		return CheckInputSequencePositiveEdge(InputCondition);
	case EInputMethod::PressAndRelease:
		return CheckInputSequencePressAndRelease(InputCondition);
	case EInputMethod::NegativeEdge:
		return CheckInputSequenceNegativeEdge(InputCondition);
	default:
		return false;
	}
}

bool FInputBuffer::CheckInput(int32 NeededInput, int i) const {
	return (InputBufferInternal[i] & NeededInput) == NeededInput || NeededInput == INP_None;
}

bool FInputBuffer::CheckInputStrictDirections(int32 NeededInput, int i, bool ignoreEmptyNeeded) const {
	if(ignoreEmptyNeeded){
		return ((InputBufferInternal[i] ^ NeededInput) & INP_Directions) == 0;
	}
	else {
		return ((InputBufferInternal[i] ^ NeededInput) & INP_Directions) == 0 || (!ignoreEmptyNeeded && NeededInput == INP_None);
	}
}

TArray <FInputBitmask> FInputBuffer::InitInputSequence(const FInputCondition& InputCondition, bool disallowDirections) {
	TArray<FInputBitmask> InputSequence;
	FInputBitmask Example;
	InputSequence.Reserve(InputSequenceSize);
	InputSequence.Init(Example, InputSequenceSize);
	for (int i = 0; i < InputSequenceSize; i++)
	{
		if (i >= InputCondition.Sequence.Num())
		{
			InputSequence[i].InputFlag = -1;
			continue;
		}
		InputSequence[i] = InputCondition.Sequence[i];
		if (disallowDirections && ((InputSequence[i].InputFlag & INP_Directions) > 0)) {
			UE_LOG(LogTemp, Error, TEXT("Direction requested in desired input sequence but method is not normal or strict."));
		}
	}
	return InputSequence;
}

bool FInputBuffer::CheckLastMatchOrDisallowedInputs(int FramesSinceLastMatch, int InputIndex, int i, const FInputCondition& InputCondition, const TArray<FInputBitmask> InputSequence) const {
	const TArray <TEnumAsByte<EInputFlags>> DisallowedInputs = InputCondition.DisallowedInputs;
	int32 DisallowedInputsMask = InputCondition.DisallowedInputsMask;

	if (FramesSinceLastMatch > InputSequence[InputIndex].Lenience)
		return false;

	for (auto DisallowedInput : DisallowedInputs)
	{
		if ((InputBufferInternal[i] & DisallowedInput) == DisallowedInput) return false;
	}

	if ((InputBufferInternal[i] & DisallowedInputsMask) != 0) return false;

	for (auto DisallowedInput : InputSequence[InputIndex].DisallowedInputs)
	{
		if ((InputBufferInternal[i] & DisallowedInput) == DisallowedInput) return false;
	}

	if ((InputBufferInternal[i] & InputSequence[InputIndex].DisallowedInputsMask) != 0) return false;

	return true;
}

int FInputBuffer::GetInputIndex(const TArray<FInputBitmask> InputSequence) const {
	for (int32 i = InputSequenceSize - 1; i > -1; i--)
	{
		if (InputSequence[i].InputFlag != -1)
		{
			return i;
		}
	}
	return -10;
}

bool FInputBuffer::CheckInputSequence(bool Strict, const FInputCondition& InputCondition) const
{
	const TArray<FInputBitmask> InputSequence = InitInputSequence(InputCondition);
	int32 InputIndex = GetInputIndex(InputSequence);
	int32 FramesSinceLastMatch = 0; //how long it's been since last input match
	int32 ImpreciseMatches = 0;
	int32 ImpreciseInputCount = InputCondition.ImpreciseInputCount;

	for (int32 i = InputBufferSize - 1; i >= 0;)
	{
		if (InputIndex < 0) //check if input sequence has been fully read
			return true;

		if (!CheckLastMatchOrDisallowedInputs(FramesSinceLastMatch, InputIndex, i, InputCondition, InputSequence)) {
			return false;
		}
		else {
			FramesSinceLastMatch += InputTime[i];
		}

		const int32 NeededInput = InputSequence[InputIndex].InputFlag;

		if (Strict ? CheckInputStrictDirections(NeededInput, i) : CheckInput(NeededInput, i)) //if input matches...
		{
			if (InputSequence[InputIndex].Hold > 0 && FramesSinceLastMatch < InputSequence[InputIndex].Hold) //if button held for less than required...
			{
				i--;
				continue;
			}
			FramesSinceLastMatch = FMath::Min(0, FramesSinceLastMatch - InputSequence[InputIndex].Lenience - InputSequence[InputIndex].Hold); //reset last match
			InputIndex--; //advance sequence
			i--;
			continue;
		}

		if (Strict && CheckInput(NeededInput, i)) //if input doesn't match precisely...
		{
			if (ImpreciseMatches >= ImpreciseInputCount)
			{
				FramesSinceLastMatch += InputTime[i];
				i--;
				continue;
			}
			if (InputSequence[InputIndex].Hold > 0 && FramesSinceLastMatch < InputSequence[InputIndex].Hold) //if button held for less than required...
			{
				i--;
				continue;
			}
			ImpreciseMatches++;
			FramesSinceLastMatch = FMath::Min(0, FramesSinceLastMatch - InputSequence[InputIndex].Lenience - InputSequence[InputIndex].Hold); //reset last match
			InputIndex--; //advance sequence
		}
		i--;
	}

	return false;
}

bool FInputBuffer::CheckInputSequencePositiveEdge(const FInputCondition& InputCondition) const
{
	const TArray<FInputBitmask> InputSequence = InitInputSequence(InputCondition, true);
	int32 InputIndex = GetInputIndex(InputSequence);
	int32 FramesSinceLastMatch = 0; //how long it's been since last input match
	
	// Do not let i become zero because we can't find a positive edge if we are out of inputs.
	for (int32 i = InputBufferSize - 1; i > 0;)
	{
		if (InputIndex < 0) //check if input sequence has been fully read
		{
			FramesSinceLastMatch += InputTime[i - 1];
			if (FramesSinceLastMatch > InputSequence[0].Lenience + InputSequence[0].Hold) return false;
			//Check the input is no longer held.
			if ((InputBufferInternal[i] & INP_Valid) && !(InputBufferInternal[i] & InputSequence[0].InputFlag))
				return true;
			i--;
			continue;
		}

		if (!CheckLastMatchOrDisallowedInputs(FramesSinceLastMatch, InputIndex, i, InputCondition, InputSequence)) {
			return false;
		}
		else {
			FramesSinceLastMatch += InputTime[i];
		}

		const int32 NeededInput = InputSequence[InputIndex].InputFlag;

		if (CheckInput(NeededInput, i)) //if input matches...
		{
			if (InputSequence[InputIndex].Hold > 0 && FramesSinceLastMatch < InputSequence[InputIndex].Hold) //if button held for less than required...
			{
				i--;
				continue;
			}
			FramesSinceLastMatch = FMath::Min(0, FramesSinceLastMatch - InputSequence[InputIndex].Lenience - InputSequence[InputIndex].Hold); //reset last match
			InputIndex--; //advance sequence
		}
		i--;
	}

	return false;
}

bool FInputBuffer::CheckInputSequencePressAndRelease(const FInputCondition& InputCondition) const
{
	const TArray<FInputBitmask> InputSequence = InitInputSequence(InputCondition, true);
	int32 InputIndex = GetInputIndex(InputSequence);
	int32 FramesSinceLastMatch = 0; //how long it's been since last input match
	int32 FirstMatch = -1;
	const int32 LastInputIndex = InputIndex;

	// Do not let i become zero because we can't find a positive edge if we are out of inputs.
	// Start at -2 instead of -1, second to last entry in the buffer, because we cannot
	// possibly find a negative edge on the last element of the input buffer.
	for (int32 i = InputBufferSize - 2; i > 0;)
	{
		if (InputIndex < 0) //check if input sequence has been fully read
		{
			if (FramesSinceLastMatch > InputSequence[0].Lenience + InputSequence[0].Hold) return false;

			if (!(InputBufferInternal[i] & InputSequence[0].InputFlag)) //Looking for positive edge
				break;
			FramesSinceLastMatch += InputTime[i] - InputTime[i + 1];
			i--;
			continue;
		}

		if (!CheckLastMatchOrDisallowedInputs(FramesSinceLastMatch, InputIndex, i, InputCondition, InputSequence)) {
			return false;
		}
		else {
			FramesSinceLastMatch += InputTime[i];
		}

		const int32 NeededInput = InputSequence[InputIndex].InputFlag;

		if (CheckInput(NeededInput, i)) //if input matches...
		{
			if (InputSequence[InputIndex].Hold > 0 && FramesSinceLastMatch < InputSequence[InputIndex].Hold) //if button held for less than required...
			{
				i--;
				continue;
			}
			if (FirstMatch == -1) FirstMatch = i;
			FramesSinceLastMatch = FMath::Min(0, FramesSinceLastMatch - InputSequence[InputIndex].Lenience - InputSequence[InputIndex].Hold); //reset last match
			InputIndex--; //advance sequence
		}
		i--;
	}

	if (FirstMatch == -1) return false;
	for (int i = FirstMatch + 1; i < InputBufferSize; i++)
	{
		if ((InputBufferInternal[i] & InputSequence[LastInputIndex].InputFlag) != InputSequence[LastInputIndex].InputFlag) return true;
	}

	return false;
}

bool FInputBuffer::CheckInputSequenceNegativeEdge(const FInputCondition& InputCondition) const
{
	const TArray<FInputBitmask> InputSequence = InitInputSequence(InputCondition, true);
	int32 InputIndex = GetInputIndex(InputSequence);
	int32 FramesSinceLastMatch = 0; //how long it's been since last input match

	// Start at -2 instead of -1, second to last entry in the buffer, because we cannot
	// possibly find a negative edge on the last element of the input buffer.
	for (int32 i = InputBufferSize - 2; i >= 0;)
	{
		if (InputIndex < 0) //check if input sequence has been fully read
			return true;

		if (!CheckLastMatchOrDisallowedInputs(FramesSinceLastMatch, InputIndex, i, InputCondition, InputSequence)) {
			return false;
		}
		else {
			FramesSinceLastMatch += InputTime[i];
		}

		const int32 NeededInput = InputSequence[InputIndex].InputFlag;

		if ( CheckInput(NeededInput, i)) //if input matches...
		{
			// Check if the next value in the buffer is still the desired input
			// and if so, then this isn't a negative edge and we continue backward in the buffer.
			if (CheckInput(NeededInput, i + 1)) continue;
			FramesSinceLastMatch = FMath::Min(0, FramesSinceLastMatch - InputSequence[InputIndex].Lenience - InputSequence[InputIndex].Hold); //reset last match
			InputIndex--; //advance sequence
		}
		i--;
	}
	return false;
}

void FInputBuffer::FlipInputsInBuffer()
{
	for (int i = 0; i < InputBufferSize; i++)
	{
		const unsigned int Bit1 = (InputBufferInternal[i] >> 2) & 1;
		const unsigned int Bit2 = (InputBufferInternal[i] >> 3) & 1;
		unsigned int x = (Bit1 ^ Bit2);

		x = x << 2 | x << 3;

		InputBufferInternal[i] = InputBufferInternal[i] ^ x;
	}
}

void FInputBuffer::ResetBuffer()
{
	for (int i = 0; i < InputBufferSize; i++)
	{
		InputBufferInternal[i] = 0;
		InputTime[i] = 0;
	}
}