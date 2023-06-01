#include "RandomManager.h"
#include "GenericPlatform/GenericPlatformMath.h"

void FRandomManager::InitSeed(int32 InSeed)
{
	Seed = InSeed;
	FGenericPlatformMath::RandInit(Seed);
}

int32 FRandomManager::GenerateRandomNumber()
{
	return FGenericPlatformMath::Rand();
}
