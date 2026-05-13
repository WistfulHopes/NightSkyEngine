#include "RandomManager.h"
#include "GenericPlatform/GenericPlatformMath.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(RandomManager)

int FRandomManager::Rand()
{
	Seed = Seed * 1103515245 + 12345;
	return Seed / 65536 % 32768;
}

int FRandomManager::RandRange(int Min, int Max)
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
