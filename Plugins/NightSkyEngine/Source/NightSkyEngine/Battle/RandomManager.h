#pragma once
#include "CoreMinimal.h"
#include "RandomManager.generated.h"

USTRUCT()
struct FRandomManager
{
	GENERATED_BODY()
private:
	uint32 Seed = 1;
public:
	FRandomManager() {}
	FRandomManager(uint32 InSeed) : Seed(InSeed) {}

	int Rand()
	{
		Seed = Seed * 1103515245 + 12345;
		return Seed / 65536 % 32768;
	}

	int RandRange(int Min, int Max)
	{
		if (Min > Max)
		{
			const int32 Temp = Max;
			Max = Min;
			Min = Temp;
		}
		int32 Result = Rand();
		Result = Result % (Max - Min + 1) + Min;
		return Result;
	}
	
	void Reseed(uint32 InSeed)
	{
		Seed = InSeed;
	}

	uint32 GetSeed() const
	{
		return Seed;
	}

	int32 GenerateRandomNumber();
};