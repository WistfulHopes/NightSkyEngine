

# File Subroutine.h

[**File List**](files.md) **>** [**Battle**](dir_59b3558fc0091a3111c9e7dd8d94b2ea.md) **>** [**Script**](dir_0ca77fec7001245ae32841da8dbaa106.md) **>** [**Subroutine.h**](_subroutine_8h.md)

[Go to the documentation of this file](_subroutine_8h.md)


```C++
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "NightSkyEngine/Battle/Misc/SerializableObj.h"
#include "UObject/Object.h"
#include "Subroutine.generated.h"

class ABattleObject;

UCLASS(BlueprintType, Blueprintable)
class USubroutine : public USerializableObj
{
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadOnly)
    ABattleObject* Parent;
    UPROPERTY(BlueprintReadOnly, EditAnywhere)
    FGameplayTag Name;

    UFUNCTION(BlueprintNativeEvent)
    void Exec();
};
```


