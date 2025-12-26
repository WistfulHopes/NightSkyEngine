

# File BattleExtension.h

[**File List**](files.md) **>** [**Battle**](dir_59b3558fc0091a3111c9e7dd8d94b2ea.md) **>** [**Script**](dir_0ca77fec7001245ae32841da8dbaa106.md) **>** [**BattleExtension.h**](_battle_extension_8h.md)

[Go to the documentation of this file](_battle_extension_8h.md)


```C++
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NightSkyEngine/Battle/NightSkyGameState.h"
#include "NightSkyEngine/Battle/Misc/SerializableObj.h"
#include "BattleExtension.generated.h"

UCLASS(BlueprintType, Blueprintable)
class NIGHTSKYENGINE_API UBattleExtension : public USerializableObj
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadOnly)
    ANightSkyGameState* Parent;
    
    UPROPERTY(BlueprintReadOnly, EditAnywhere)
    FGameplayTag Name;

    UFUNCTION(BlueprintNativeEvent)
    void Exec();
};
```


