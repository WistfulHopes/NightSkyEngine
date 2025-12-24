#include "RandomManager.h"
#include "GenericPlatform/GenericPlatformMath.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(RandomManager)

int32 FRandomManager::GenerateRandomNumber()
{
	return FGenericPlatformMath::Rand();
}
