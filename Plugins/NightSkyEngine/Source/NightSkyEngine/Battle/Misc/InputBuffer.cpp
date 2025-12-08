// Fill out your copyright notice in the Description page of Project Settings.


#include "InputBuffer.h"

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
	case EInputMethod::Once:
	case EInputMethod::OnceStrict:
		{
			Update(INP_Neutral);
			for (int i = 0; i < InputCondition.Sequence.Num(); i++)
			{
				Update(InputCondition.Sequence[i].InputFlag);
			}
			break;
		}
	case EInputMethod::PressAndRelease:
	case EInputMethod::PressAndReleaseStrict:
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
	case EInputMethod::Negative:
	case EInputMethod::NegativeStrict:
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

void FInputBuffer::Update(int32 Input, bool bStopped)
{
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
		InputDisabled[i] = InputDisabled[i + 1];
		InputTime[i] = InputTime[i + 1];
	}
	InputBufferInternal[InputBufferSize - 1] = Input;
	InputDisabled[InputBufferSize - 1] = 0;
	InputTime[InputBufferSize - 1] = 0;
}

void FInputBuffer::Emplace(int32 Input, uint32 Index)
{
	if (Index > InputBufferSize - 1) return;

	InputBufferInternal[Index] |= Input;
	InputDisabled[Index] = 0;
}

bool FInputBuffer::CheckInputCondition(const FInputCondition& InputCondition)
{
	for (int i = 0; i < InputSequenceSize; i++)
	{
		if (i >= InputCondition.Sequence.Num())
		{
			InputSequence[i].InputFlag = -1;
			continue;
		}
		InputSequence[i] = InputCondition.Sequence[i];
	}
	DisallowedInputs = InputCondition.DisallowedInputs;
	ImpreciseInputCount = InputCondition.ImpreciseInputCount;
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

	for (int32 i = InputBufferSize - 1; i >= 0;)
	{
		if (InputIndex == -1) //check if input sequence has been fully read
			return true;
		
		const int32 NeededInput = InputSequence[InputIndex].InputFlag;
		if (FramesSinceLastMatch > InputSequence[InputIndex].Lenience)
			return false;

		for (auto DisallowedInput : DisallowedInputs)
		{
			if ((InputBufferInternal[i] & DisallowedInput) == DisallowedInput) return false;
		}
		
		if ((InputBufferInternal[i] & NeededInput) == NeededInput) //if input matches...
		{
			if (HoldDuration < InputSequence[InputIndex].Hold) //if button held for less than required...
			{
				HoldDuration++;
				FramesSinceLastMatch--;
				continue;
			}
			HoldDuration = 0;
			InputIndex--; //advance sequence
			FramesSinceLastMatch = InputTime[i] - InputSequence[InputIndex].Lenience; //reset last match
		}
		else
		{
			FramesSinceLastMatch += InputTime[i];
		}
		i--;
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

	for (int32 i = InputBufferSize - 1; i >= 0;)
	{
		if (InputIndex == -1) //check if input sequence has been fully read
			return true;
		
		const int32 NeededInput = InputSequence[InputIndex].InputFlag;
		if (FramesSinceLastMatch > InputSequence[InputIndex].Lenience)
			return false;

		for (auto DisallowedInput : DisallowedInputs)
		{
			if ((InputBufferInternal[i] & DisallowedInput) == DisallowedInput) return false;
		}

		if ((InputBufferInternal[i] ^ NeededInput) << 27 == 0) //if input matches...
		{
			if (HoldDuration < InputSequence[InputIndex].Hold) //if button held for less than required...
			{
				HoldDuration++;
				FramesSinceLastMatch--;
				continue;
			}
			InputIndex--; //advance sequence
			FramesSinceLastMatch = InputTime[i] - InputSequence[InputIndex].Lenience; //reset last match
			i--;
			continue;
		}
		if ((InputBufferInternal[i] & NeededInput) == NeededInput) //if input doesn't match precisely...
		{
			if (ImpreciseMatches >= ImpreciseInputCount)
			{
				FramesSinceLastMatch += InputTime[i];
				i--;
				continue;
			}
			if (HoldDuration < InputSequence[InputIndex].Hold) //if button held for less than required...
			{
				HoldDuration++;
				FramesSinceLastMatch--;
				continue;
			}
			ImpreciseMatches++;
			InputIndex--; //advance sequence
			FramesSinceLastMatch = InputTime[i] - InputSequence[InputIndex].Lenience; //reset last match
		}
		else
		{
			FramesSinceLastMatch += InputTime[i];
		}
		i--;
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

	for (int32 i = InputBufferSize - 1; i >= 0;)
	{
		if (InputIndex < 0) //check if input sequence has been fully read
		{
			FramesSinceLastMatch += InputTime[i + 1];
			if (FramesSinceLastMatch > InputSequence[0].Lenience) return false;
			if (!(InputBufferInternal[i] & InputSequence[0].InputFlag))
				return true;
			i--;
			continue;
		}
		
		if (FramesSinceLastMatch > InputSequence[InputIndex].Lenience)
			return false;
		
		const int32 NeededInput = InputSequence[InputIndex].InputFlag;

		for (auto DisallowedInput : DisallowedInputs)
		{
			if ((InputBufferInternal[i] & DisallowedInput) == DisallowedInput) return false;
		}

		if ((InputBufferInternal[i] & NeededInput) == NeededInput) //if input matches...
		{
			if (HoldDuration < InputSequence[InputIndex].Hold) //if button held for less than required...
			{
				HoldDuration++;
				FramesSinceLastMatch--;
				continue;
			}
			InputIndex--; //advance sequence
			FramesSinceLastMatch = InputTime[i] - InputSequence[InputIndex].Lenience; //reset last match
		}
		else
		{
			FramesSinceLastMatch += InputTime[i];
		}
		i--;
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

	for (int32 i = InputBufferSize - 1; i >= 0;)
	{
		if (InputIndex < 0) //check if input sequence has been fully read
		{
			FramesSinceLastMatch += InputTime[i + 1];
			if (FramesSinceLastMatch > InputSequence[0].Lenience) return false;
			if (!(InputBufferInternal[i] & InputSequence[0].InputFlag))
				return true;
			i--;
			continue;
		}
		
		if (FramesSinceLastMatch > InputSequence[InputIndex].Lenience)
			return false;
		
		const int32 NeededInput = InputSequence[InputIndex].InputFlag;

		for (auto DisallowedInput : DisallowedInputs)
		{
			if ((InputBufferInternal[i] & DisallowedInput) == DisallowedInput) return false;
		}

		if ((InputBufferInternal[i] ^ NeededInput) << 27 == 0) //if input matches...
		{
			if (HoldDuration < InputSequence[InputIndex].Hold) //if button held for less than required...
			{
				HoldDuration++;
				FramesSinceLastMatch--;
				continue;
			}
			InputIndex--; //advance sequence
			FramesSinceLastMatch = InputTime[i] - InputSequence[InputIndex].Lenience; //reset last match
			i--;
			continue;
		}
		if ((InputBufferInternal[i] & NeededInput) == NeededInput) //if input matches...
		{
			if (ImpreciseMatches >= ImpreciseInputCount)
			{
				FramesSinceLastMatch += InputTime[i];
				i--;
				continue;
			}
			if (HoldDuration < InputSequence[InputIndex].Hold) //if button held for less than required...
			{
				HoldDuration++;
				FramesSinceLastMatch--;
				continue;
			}
			ImpreciseMatches++;
			InputIndex--; //advance sequence
			FramesSinceLastMatch = InputTime[i] - InputSequence[InputIndex].Lenience; //reset last match
		}
		else
		{
			FramesSinceLastMatch += InputTime[i];
		}
		i--;
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

	for (int32 i = InputBufferSize - 1; i >= 0;)
	{
		if (InputIndex < 0) //check if input sequence has been fully read
		{
			if (!(InputBufferInternal[i] & InputSequence[0].InputFlag))
				break;
			continue;
		}
		
		const int32 NeededInput = InputSequence[InputIndex].InputFlag;
		if (FramesSinceLastMatch > InputSequence[InputIndex].Lenience)
			return false;

		for (auto DisallowedInput : DisallowedInputs)
		{
			if ((InputBufferInternal[i] & DisallowedInput) == DisallowedInput) return false;
		}

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
			FramesSinceLastMatch = InputTime[i] - InputSequence[InputIndex].Lenience; //reset last match
		}
		else
		{
			FramesSinceLastMatch += InputTime[i];
		}
		i--;
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

	for (int32 i = InputBufferSize - 1; i >= 0;)
	{
		if (InputIndex < 0) //check if input sequence has been fully read
		{
			if ((InputBufferInternal[i] ^ InputSequence[0].InputFlag) << 27 != 0)
				break;
			continue;
		}
		
		const int32 NeededInput = InputSequence[InputIndex].InputFlag;
		if (FramesSinceLastMatch > InputSequence[InputIndex].Lenience)
			return false;

		for (auto DisallowedInput : DisallowedInputs)
		{
			if ((InputBufferInternal[i] & DisallowedInput) == DisallowedInput) return false;
		}

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
			FramesSinceLastMatch = InputTime[i] - InputSequence[InputIndex].Lenience; //reset last match
			i--;
			continue;
		}
		if ((InputBufferInternal[i] & NeededInput) == NeededInput) //if input matches...
		{
			if (ImpreciseMatches >= ImpreciseInputCount)
			{
				FramesSinceLastMatch += InputTime[i];
				i--;
				continue;
			}
			if (HoldDuration < InputSequence[InputIndex].Hold) //if button held for less than required...
			{
				HoldDuration++;
				FramesSinceLastMatch--;
				continue;
			}
			if (FirstMatch == -1) FirstMatch = i;
			ImpreciseMatches++;
			InputIndex--; //advance sequence
			FramesSinceLastMatch = InputTime[i] - InputSequence[InputIndex].Lenience; //reset last match
		}
		else
		{
			FramesSinceLastMatch += InputTime[i];
		}
		i--;
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
	
	for (int32 i = InputBufferSize - 2; i >= 0;)
	{
		if (InputIndex == -1) //check if input sequence has been fully read
			return true;

		const int32 NeededInput = InputSequence[InputIndex].InputFlag;

		if (FramesSinceLastMatch > InputSequence[InputIndex].Lenience)
			return false;

		for (auto DisallowedInput : DisallowedInputs)
		{
			if ((InputBufferInternal[i] & DisallowedInput) == DisallowedInput) return false;
		}

		if ((InputBufferInternal[i] & NeededInput) == NeededInput) //if input matches...
		{
			if ((InputBufferInternal[i + 1] & NeededInput) == NeededInput) continue;
			InputIndex--; //advance sequence
			FramesSinceLastMatch = InputTime[i] - InputSequence[InputIndex].Lenience; //reset last match
		}
		else
		{
			FramesSinceLastMatch += InputTime[i];
		}
		i--;
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

	for (int32 i = InputBufferSize - 2; i >= 0;)
	{
		if (InputIndex == -1) //check if input sequence has been fully read
			return true;

		const int32 NeededInput = InputSequence[InputIndex].InputFlag;

		if (FramesSinceLastMatch > InputSequence[InputIndex].Lenience)
			return false;

		for (auto DisallowedInput : DisallowedInputs)
		{
			if ((InputBufferInternal[i] & DisallowedInput) == DisallowedInput) return false;
		}

		if ((InputBufferInternal[i] ^ NeededInput) << 27 == 0) //if input matches...
		{
			if ((InputBufferInternal[i + 1] & NeededInput) == NeededInput) continue;
			InputIndex--; //advance sequence
			FramesSinceLastMatch = InputTime[i] - InputSequence[InputIndex].Lenience; //reset last match
			i--;
			continue;
		}
		if ((InputBufferInternal[i] & NeededInput) == NeededInput) //if input matches...
		{
			if (ImpreciseMatches >= ImpreciseInputCount)
			{
				FramesSinceLastMatch += InputTime[i];
				i--;
				continue;
			}
			if ((InputBufferInternal[i + 1] & NeededInput) == NeededInput) continue;
			ImpreciseMatches++;
			InputIndex--; //advance sequence
			FramesSinceLastMatch = InputTime[i] - InputSequence[InputIndex].Lenience; //reset last match
		}
		else
		{
			FramesSinceLastMatch += InputTime[i];
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
