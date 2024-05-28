#include "RandomManager.h"
#include "GenericPlatform/GenericPlatformMath.h"

int32 FRandomManager::GenerateRandomNumber()
{
	return FGenericPlatformMath::Rand();
}
