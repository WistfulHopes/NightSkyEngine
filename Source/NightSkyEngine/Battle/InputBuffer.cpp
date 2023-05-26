// Fill out your copyright notice in the Description page of Project Settings.


#include "InputBuffer.h"

void FInputBuffer::Tick(int32 Input)
{
	for (int32 i = 0; i < 89; i++)
	{
		InputBufferInternal[i] = InputBufferInternal[i + 1];
		InputDisabled[i] = InputDisabled[i + 1];
	}
	InputBufferInternal[89] = Input;
	InputDisabled[89] = 0;
}

bool FInputBuffer::CheckInputCondition(const FInputCondition& InputCondition)
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
	bInputAllowDisable = InputCondition.bInputAllowDisable;
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
	default:
		return false;
	}
}

bool FInputBuffer::CheckInputSequence() const
{
	int32 InputIndex = -10;
	for (int32 i = 19; i > -1; i--)
	{
		if (InputSequence[i].InputFlag != -1)
		{
			InputIndex = i;
			break;
		}
	}
	int32 FramesSinceLastMatch = 0; //how long it's been since last input match
	bool NoMatches = true;

	for (int32 i = 89; i >= 0; i--)
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
			InputIndex--; //advance sequence
			FramesSinceLastMatch = 0; //reset last match
			i--;
		}
	}

	return false;
}

bool FInputBuffer::CheckInputSequenceStrict() const
{
	int32 InputIndex = -10;
	for (int32 i = 19; i > -1; i--)
	{
		if (InputSequence[i].InputFlag != -1)
		{
			InputIndex = i;
			break;
		}
	}
	int32 FramesSinceLastMatch = 0; //how long it's been since last input match
	int32 ImpreciseMatches = 0;
	bool NoMatches = true;
	
	for (int32 i = 89; i >= 0; i--)
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
			InputIndex--; //advance sequence
			FramesSinceLastMatch = 0; //reset last match
			i--;
			continue;
		}
		if ((InputBufferInternal[i] & NeededInput) == NeededInput) //if input doesn't match precisely...
		{
			NoMatches = false;
			if (ImpreciseMatches >= ImpreciseInputCount)
				continue;
			ImpreciseMatches++;
			InputIndex--; //advance sequence
			FramesSinceLastMatch = 0; //reset last match
			i--;
		}
	}

	return false;
}

bool FInputBuffer::CheckInputSequenceOnce() const
{
	int32 InputIndex = -10;
	for (int32 i = 19; i > -1; i--)
	{
		if (InputSequence[i].InputFlag != -1)
		{
			InputIndex = i;
			break;
		}
	}
	int32 FramesSinceLastMatch = 0; //how long it's been since last input match

	for (int32 i = 89; i >= 0; i--)
	{
		if (InputDisabled[i] == InputBufferInternal[i] && bInputAllowDisable)
			return false;

		if (InputIndex < 0) //check if input sequence has been fully read
		{
			if (!(InputBufferInternal[i] & InputSequence[0].InputFlag))
				return true;
			return false;
		}
		const int32 NeededInput = InputSequence[InputIndex].InputFlag;

		if (FramesSinceLastMatch > InputSequence[InputIndex].Lenience)
			return false;
		FramesSinceLastMatch++;

		if ((InputBufferInternal[i] & NeededInput) == NeededInput) //if input matches...
		{
			InputIndex--; //advance sequence
			FramesSinceLastMatch = 0; //reset last match
			i--;
		}
	}

	return false;
}

bool FInputBuffer::CheckInputSequenceOnceStrict() const
{
	int32 InputIndex = -10;
	for (int32 i = 19; i > -1; i--)
	{
		if (InputSequence[i].InputFlag!= -1)
		{
			InputIndex = i;
			break;
		}
	}
	int32 FramesSinceLastMatch = 0; //how long it's been since last input match
	int32 ImpreciseMatches = 0;

	for (int32 i = 89; i >= 0; i--)
	{
		if (InputDisabled[i] == InputBufferInternal[i] && bInputAllowDisable)
			return false;

		if (InputIndex < 0) //check if input sequence has been fully read
		{
			if ((InputBufferInternal[i] ^ InputSequence[0].InputFlag) << 27 != 0)
				return true;
			return false;
		}
		const int32 NeededInput = InputSequence[InputIndex].InputFlag;

		if (FramesSinceLastMatch > InputSequence[InputIndex].Lenience)
			return false;
		FramesSinceLastMatch++;

		if ((InputBufferInternal[i] ^ NeededInput) << 27 == 0) //if input matches...
		{
			InputIndex--; //advance sequence
			FramesSinceLastMatch = 0; //reset last match
			i--;
			continue;
		}
		if ((InputBufferInternal[i] & NeededInput) == NeededInput) //if input matches...
		{
			if (ImpreciseMatches >= ImpreciseInputCount)
				continue;
			ImpreciseMatches++;
			InputIndex--; //advance sequence
			FramesSinceLastMatch = 0; //reset last match
			i--;
		}
	}

	return false;
}

void FInputBuffer::FlipInputsInBuffer()
{
	for (int i = 0; i < 90; i++)
	{
		const unsigned int Bit1 = (InputBufferInternal[i] >> 2) & 1;
		const unsigned int Bit2 = (InputBufferInternal[i] >> 3) & 1;
		unsigned int x = (Bit1 ^ Bit2);

		x = x << 2 | x << 3;

		InputBufferInternal[i] = InputBufferInternal[i] ^ x;
	}
}
