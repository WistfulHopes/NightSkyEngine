#pragma once
#include "CoreMinimal.h"

struct FRandomManager
{
	int32 Seed;
	
	void InitSeed(int32 InSeed);
	static int32 GenerateRandomNumber();
};