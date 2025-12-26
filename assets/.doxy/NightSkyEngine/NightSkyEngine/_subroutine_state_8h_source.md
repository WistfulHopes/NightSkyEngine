

# File SubroutineState.h

[**File List**](files.md) **>** [**Battle**](dir_59b3558fc0091a3111c9e7dd8d94b2ea.md) **>** [**Script**](dir_0ca77fec7001245ae32841da8dbaa106.md) **>** [**SubroutineState.h**](_subroutine_state_8h.md)

[Go to the documentation of this file](_subroutine_state_8h.md)


```C++
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State.h"
#include "SubroutineState.generated.h"

UCLASS()
class NIGHTSKYENGINE_API USubroutineState : public UState
{
    GENERATED_BODY()

public:
    // Which subroutine to call from the state
    UPROPERTY(EditAnywhere)
    FGameplayTag SubroutineName;
    
    // Dummy CallExec, we don't want it to execute code
    virtual void CallExec() override {}
};
```


