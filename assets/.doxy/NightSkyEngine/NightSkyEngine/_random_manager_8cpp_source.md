

# File RandomManager.cpp

[**File List**](files.md) **>** [**Battle**](dir_59b3558fc0091a3111c9e7dd8d94b2ea.md) **>** [**Misc**](dir_4fd921e402b7a240656c31e280e3875c.md) **>** [**RandomManager.cpp**](_random_manager_8cpp.md)

[Go to the documentation of this file](_random_manager_8cpp.md)


```C++
#include "RandomManager.h"
#include "GenericPlatform/GenericPlatformMath.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(RandomManager)

int32 FRandomManager::GenerateRandomNumber()
{
    return FGenericPlatformMath::Rand();
}
```


