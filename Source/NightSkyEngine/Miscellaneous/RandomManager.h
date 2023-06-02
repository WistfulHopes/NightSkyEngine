#pragma once
#include "CoreMinimal.h"
#include "RandomManager.generated.h"

USTRUCT()
struct FRandomManager
{
	GENERATED_BODY()
	
	UPROPERTY()
	int32 Seed;
	
	void InitSeed(int32 InSeed);
	static int32 GenerateRandomNumber();
};