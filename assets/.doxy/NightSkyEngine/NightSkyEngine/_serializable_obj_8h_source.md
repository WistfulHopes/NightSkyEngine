

# File SerializableObj.h

[**File List**](files.md) **>** [**Battle**](dir_59b3558fc0091a3111c9e7dd8d94b2ea.md) **>** [**Misc**](dir_4fd921e402b7a240656c31e280e3875c.md) **>** [**SerializableObj.h**](_serializable_obj_8h.md)

[Go to the documentation of this file](_serializable_obj_8h.md)


```C++
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SerializableObj.generated.h"

UCLASS()
class NIGHTSKYENGINE_API USerializableObj : public UObject
{
    GENERATED_BODY()
    
public:
    TArray<uint8> SaveForRollback();
    void LoadForRollback(const TArray<uint8>& InBytes);
    void ResetToCDO();
};
```


