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

	int Rand();

	int RandRange(int Min, int Max);
	
	void Reseed(uint32 InSeed)
	{
		Seed = InSeed;
	}

	uint32 GetSeed() const
	{
		return Seed;
	}
};