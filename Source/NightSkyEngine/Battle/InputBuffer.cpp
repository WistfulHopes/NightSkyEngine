// Fill out your copyright notice in the Description page of Project Settings.


#include "InputBuffer.h"

void FInputBuffer::Update(int32 Input)
{
	for (int32 i = 0; i < InputBufferSize - 1; i++)
	{
		InputBufferInternal[i] = InputBufferInternal[i + 1];
		InputDisabled[i] = InputDisabled[i + 1];
	}
	InputBufferInternal[InputBufferSize - 1] = Input;
	InputDisabled[InputBufferSize - 1] = 0;
}

void FInputBuffer::Emplace(int32 Input, uint32 Index)
{
	if (Index > InputBufferSize - 1) return;

	InputBufferInternal[Index] |= Input;
	InputDisabled[Index] = 0;
}

bool FInputBuffer::CheckInputCondition(const FInputCondition& InputCondition, bool bIsKara)
{
	for (int i = 0; i < 20; i++)
	{
		if (i >= InputCondition.Sequence.Num())
		{
			InputSequence[i].InputFlag = -1;
			continue;
		}
		InputSequence[i] = InputCondition.Sequence[i];
	}
	ImpreciseInputCount = InputCondition.ImpreciseInputCount;
	bInputAllowDisable = bIsKara ? false : InputCondition.bInputAllowDisable;
	switch (InputCondition.Method)
	{
	case EInputMethod::Normal:
		return CheckInputSequence();
	case EInputMethod::Strict:
		return CheckInputSequenceStrict();
	case EInputMethod::Once:
		return CheckInputSequenceOnce();
	case EInputMethod::OnceStrict:
		return CheckInputSequenceOnceStrict();
	case EInputMethod::PressAndRelease:
		return CheckInputSequencePressAndRelease();
	case EInputMethod::PressAndReleaseStrict:
		return CheckInputSequencePressAndReleaseStrict();
	case EInputMethod::Negative:
		return CheckInputSequenceNegative();
	case EInputMethod::NegativeStrict:
		return CheckInputSequenceNegativeStrict();
	default:
		return false;
	}
}

bool FInputBuffer::CheckInputSequence() const
{
	int32 InputIndex = -10;
	for (int32 i = InputSequenceSize - 1; i > -1; i--)
	{
		if (InputSequence[i].InputFlag != -1)
		{
			InputIndex = i;
			break;
		}
	}
	int32 FramesSinceLastMatch = 0; //how long it's been since last input match
	int32 HoldDuration = 0;
	bool NoMatches = true;

	for (int32 i = InputBufferSize - 1; i >= 0; i--)
	{
		if (InputIndex == -1) //check if input sequence has been fully read
			return true;
		
		if (NoMatches && InputDisabled[i] == InputBufferInternal[i] && bInputAllowDisable)
			return false;
		
		const int32 NeededInput = InputSequence[InputIndex].InputFlag;
		if (FramesSinceLastMatch > InputSequence[InputIndex].Lenience)
			return false;
		FramesSinceLastMatch++;

		if ((InputBufferInternal[i] & NeededInput) == NeededInput) //if input matches...
		{
			NoMatches = false;
			if (HoldDuration < InputSequence[InputIndex].Hold) //if button held for less than required...
			{
				HoldDuration++;
				FramesSinceLastMatch--;
				continue;
			}
			HoldDuration = 0;
			InputIndex--; //advance sequence
			FramesSinceLastMatch = -InputSequence[InputIndex].TimeBetweenInputs; //reset last match
			i--;
		}
	}

	return false;
}

bool FInputBuffer::CheckInputSequenceStrict() const
{
	int32 InputIndex = -10;
	for (int32 i = InputSequenceSize - 1; i > -1; i--)
	{
		if (InputSequence[i].InputFlag != -1)
		{
			InputIndex = i;
			break;
		}
	}
	int32 FramesSinceLastMatch = 0; //how long it's been since last input match
	int32 HoldDuration = 0;
	int32 ImpreciseMatches = 0;
	bool NoMatches = true;
	
	for (int32 i = InputBufferSize - 1; i >= 0; i--)
	{
		if (InputIndex == -1) //check if input sequence has been fully read
			return true;

		if (NoMatches && InputDisabled[i] == InputBufferInternal[i] && bInputAllowDisable)
			return false;
		
		const int32 NeededInput = InputSequence[InputIndex].InputFlag;
		if (FramesSinceLastMatch > InputSequence[InputIndex].Lenience)
			return false;
		FramesSinceLastMatch++;

		if ((InputBufferInternal[i] ^ NeededInput) << 27 == 0) //if input matches...
		{
			NoMatches = false;
			if (HoldDuration < InputSequence[InputIndex].Hold) //if button held for less than required...
			{
				HoldDuration++;
				FramesSinceLastMatch--;
				continue;
			}
			InputIndex--; //advance sequence
			FramesSinceLastMatch = -InputSequence[InputIndex].TimeBetweenInputs; //reset last match
			i--;
			continue;
		}
		if ((InputBufferInternal[i] & NeededInput) == NeededInput) //if input doesn't match precisely...
		{
			NoMatches = false;
			if (ImpreciseMatches >= ImpreciseInputCount)
				continue;
			if (HoldDuration < InputSequence[InputIndex].Hold) //if button held for less than required...
			{
				HoldDuration++;
				FramesSinceLastMatch--;
				continue;
			}
			ImpreciseMatches++;
			InputIndex--; //advance sequence
			FramesSinceLastMatch = -InputSequence[InputIndex].TimeBetweenInputs; //reset last match
			i--;
		}
	}

	return false;
}

bool FInputBuffer::CheckInputSequenceOnce() const
{
	int32 InputIndex = -10;
	for (int32 i = InputSequenceSize - 1; i > -1; i--)
	{
		if (InputSequence[i].InputFlag != -1)
		{
			InputIndex = i;
			break;
		}
	}
	int32 FramesSinceLastMatch = 0; //how long it's been since last input match
	int32 HoldDuration = 0;

	for (int32 i = InputBufferSize - 1; i >= 0; i--)
	{
		if (InputDisabled[i] == InputBufferInternal[i] && bInputAllowDisable)
			return false;

		if (InputIndex < 0) //check if input sequence has been fully read
		{
			if (!(InputBufferInternal[i] & InputSequence[0].InputFlag))
				return true;
			continue;
		}
		const int32 NeededInput = InputSequence[InputIndex].InputFlag;

		if (FramesSinceLastMatch > InputSequence[InputIndex].Lenience)
			return false;
		FramesSinceLastMatch++;

		if ((InputBufferInternal[i] & NeededInput) == NeededInput) //if input matches...
		{
			if (HoldDuration < InputSequence[InputIndex].Hold) //if button held for less than required...
			{
				HoldDuration++;
				FramesSinceLastMatch--;
				continue;
			}
			InputIndex--; //advance sequence
			FramesSinceLastMatch = -InputSequence[InputIndex].TimeBetweenInputs; //reset last match
			i--;
		}
	}

	return false;
}

bool FInputBuffer::CheckInputSequenceOnceStrict() const
{
	int32 InputIndex = -10;
	for (int32 i = InputSequenceSize - 1; i > -1; i--)
	{
		if (InputSequence[i].InputFlag!= -1)
		{
			InputIndex = i;
			break;
		}
	}
	int32 FramesSinceLastMatch = 0; //how long it's been since last input match
	int32 HoldDuration = 0;
	int32 ImpreciseMatches = 0;

	for (int32 i = InputBufferSize - 1; i >= 0; i--)
	{
		if (InputDisabled[i] == InputBufferInternal[i] && bInputAllowDisable)
			return false;

		if (InputIndex < 0) //check if input sequence has been fully read
		{
			if ((InputBufferInternal[i] ^ InputSequence[0].InputFlag) << 27 != 0)
				return true;
			continue;
		}
		const int32 NeededInput = InputSequence[InputIndex].InputFlag;

		if (FramesSinceLastMatch > InputSequence[InputIndex].Lenience)
			return false;
		FramesSinceLastMatch++;

		if ((InputBufferInternal[i] ^ NeededInput) << 27 == 0) //if input matches...
		{
			if (HoldDuration < InputSequence[InputIndex].Hold) //if button held for less than required...
			{
				HoldDuration++;
				FramesSinceLastMatch--;
				continue;
			}
			InputIndex--; //advance sequence
			FramesSinceLastMatch = -InputSequence[InputIndex].TimeBetweenInputs; //reset last match
			i--;
			continue;
		}
		if ((InputBufferInternal[i] & NeededInput) == NeededInput) //if input matches...
		{
			if (ImpreciseMatches >= ImpreciseInputCount)
				continue;
			if (HoldDuration < InputSequence[InputIndex].Hold) //if button held for less than required...
			{
				HoldDuration++;
				FramesSinceLastMatch--;
				continue;
			}
			ImpreciseMatches++;
			InputIndex--; //advance sequence
			FramesSinceLastMatch = -InputSequence[InputIndex].TimeBetweenInputs; //reset last match
			i--;
		}
	}

	return false;
}

bool FInputBuffer::CheckInputSequencePressAndRelease() const
{
	int32 InputIndex = -10;
	for (int32 i = InputSequenceSize - 1; i > -1; i--)
	{
		if (InputSequence[i].InputFlag != -1)
		{
			InputIndex = i;
			break;
		}
	}
	int32 FramesSinceLastMatch = 0; //how long it's been since last input match
	int32 HoldDuration = 0;
	int32 FirstMatch = -1;
	const int32 LastInputIndex = InputIndex;

	for (int32 i = InputBufferSize - 1; i >= 0; i--)
	{
		if (InputDisabled[i] == InputBufferInternal[i] && bInputAllowDisable)
			return false;

		if (InputIndex < 0) //check if input sequence has been fully read
		{
			if (!(InputBufferInternal[i] & InputSequence[0].InputFlag))
				break;
			continue;
		}
		
		const int32 NeededInput = InputSequence[InputIndex].InputFlag;
		if (FramesSinceLastMatch > InputSequence[InputIndex].Lenience)
			return false;
		FramesSinceLastMatch++;

		if ((InputBufferInternal[i] & NeededInput) == NeededInput) //if input matches...
		{
			if (HoldDuration < InputSequence[InputIndex].Hold) //if button held for less than required...
			{
				HoldDuration++;
				FramesSinceLastMatch--;
				continue;
			}
			if (FirstMatch == -1) FirstMatch = i;
			InputIndex--; //advance sequence
			FramesSinceLastMatch = -InputSequence[InputIndex].TimeBetweenInputs; //reset last match
			i--;
		}
	}

	if (FirstMatch == -1) return false;
	for (int i = FirstMatch + 1; i < InputBufferSize; i++)
	{
		if ((InputBufferInternal[InputBufferSize - 1] & InputSequence[LastInputIndex].InputFlag) != InputSequence[LastInputIndex].InputFlag) return true;
	}

	return false;
}

bool FInputBuffer::CheckInputSequencePressAndReleaseStrict() const
{
	int32 InputIndex = -10;
	for (int32 i = InputSequenceSize - 1; i > -1; i--)
	{
		if (InputSequence[i].InputFlag!= -1)
		{
			InputIndex = i;
			break;
		}
	}
	int32 FramesSinceLastMatch = 0; //how long it's been since last input match
	int32 HoldDuration = 0;
	int32 ImpreciseMatches = 0;
	int32 FirstMatch = -1;
	const int32 LastInputIndex = InputIndex;

	for (int32 i = InputBufferSize - 1; i >= 0; i--)
	{
		if (InputDisabled[i] == InputBufferInternal[i] && bInputAllowDisable)
			return false;

		if (InputIndex < 0) //check if input sequence has been fully read
		{
			if ((InputBufferInternal[i] ^ InputSequence[0].InputFlag) << 27 != 0)
				break;
			continue;
		}
		
		const int32 NeededInput = InputSequence[InputIndex].InputFlag;
		if (FramesSinceLastMatch > InputSequence[InputIndex].Lenience)
			return false;
		FramesSinceLastMatch++;

		if ((InputBufferInternal[i] ^ NeededInput) << 27 == 0) //if input matches...
		{
			if (HoldDuration < InputSequence[InputIndex].Hold) //if button held for less than required...
			{
				HoldDuration++;
				FramesSinceLastMatch--;
				continue;
			}
			if (FirstMatch == -1) FirstMatch = i;
			InputIndex--; //advance sequence
			FramesSinceLastMatch = -InputSequence[InputIndex].TimeBetweenInputs; //reset last match
			i--;
			continue;
		}
		if ((InputBufferInternal[i] & NeededInput) == NeededInput) //if input matches...
		{
			if (ImpreciseMatches >= ImpreciseInputCount)
				continue;
			if (HoldDuration < InputSequence[InputIndex].Hold) //if button held for less than required...
			{
				HoldDuration++;
				FramesSinceLastMatch--;
				continue;
			}
			if (FirstMatch == -1) FirstMatch = i;
			ImpreciseMatches++;
			InputIndex--; //advance sequence
			FramesSinceLastMatch = -InputSequence[InputIndex].TimeBetweenInputs; //reset last match
			i--;
		}
	}

	if (FirstMatch == -1) return false;
	for (int i = FirstMatch + 1; i < InputBufferSize; i++)
	{
		if ((InputBufferInternal[i + 1] & InputSequence[LastInputIndex].InputFlag) != InputSequence[LastInputIndex].InputFlag) return true;
	}
	
	return false;
}

bool FInputBuffer::CheckInputSequenceNegative() const
{
	int32 InputIndex = -10;
	for (int32 i = InputSequenceSize - 1; i > -1; i--)
	{
		if (InputSequence[i].InputFlag != -1)
		{
			InputIndex = i;
			break;
		}
	}
	int32 FramesSinceLastMatch = 0; //how long it's been since last input match
	
	for (int32 i = InputBufferSize - 1; i >= 0; i--)
	{
		if (InputIndex == -1) //check if input sequence has been fully read
			return true;

		const int32 NeededInput = InputSequence[InputIndex].InputFlag;

		if (FramesSinceLastMatch > InputSequence[InputIndex].Lenience)
			return false;
		FramesSinceLastMatch++;

		if ((InputBufferInternal[i] & NeededInput) == NeededInput) //if input matches...
		{
			if ((InputBufferInternal[i + 1] & NeededInput) == NeededInput) continue;
			InputIndex--; //advance sequence
			FramesSinceLastMatch = -InputSequence[InputIndex].TimeBetweenInputs; //reset last match
			i--;
		}
	}

	return false;
}

bool FInputBuffer::CheckInputSequenceNegativeStrict() const
{
	int32 InputIndex = -10;
	for (int32 i = InputSequenceSize - 1; i > -1; i--)
	{
		if (InputSequence[i].InputFlag!= -1)
		{
			InputIndex = i;
			break;
		}
	}
	int32 FramesSinceLastMatch = 0; //how long it's been since last input match
	int32 ImpreciseMatches = 0;

	for (int32 i = InputBufferSize - 2; i >= 0; i--)
	{
		if (InputIndex == -1) //check if input sequence has been fully read
			return true;

		const int32 NeededInput = InputSequence[InputIndex].InputFlag;

		if (FramesSinceLastMatch > InputSequence[InputIndex].Lenience)
			return false;
		FramesSinceLastMatch++;

		if ((InputBufferInternal[i] ^ NeededInput) << 27 == 0) //if input matches...
		{
			if ((InputBufferInternal[i + 1] & NeededInput) == NeededInput) continue;
			InputIndex--; //advance sequence
			FramesSinceLastMatch = -InputSequence[InputIndex].TimeBetweenInputs; //reset last match
			i--;
			continue;
		}
		if ((InputBufferInternal[i] & NeededInput) == NeededInput) //if input matches...
		{
			if (ImpreciseMatches >= ImpreciseInputCount)
				continue;
			if ((InputBufferInternal[i + 1] & NeededInput) == NeededInput) continue;
			ImpreciseMatches++;
			InputIndex--; //advance sequence
			FramesSinceLastMatch = -InputSequence[InputIndex].TimeBetweenInputs; //reset last match
			i--;
		}
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
