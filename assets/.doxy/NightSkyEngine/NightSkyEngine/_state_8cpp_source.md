

# File State.cpp

[**File List**](files.md) **>** [**Battle**](dir_59b3558fc0091a3111c9e7dd8d94b2ea.md) **>** [**Script**](dir_0ca77fec7001245ae32841da8dbaa106.md) **>** [**State.cpp**](_state_8cpp.md)

[Go to the documentation of this file](_state_8cpp.md)


```C++
// Fill out your copyright notice in the Description page of Project Settings.


#include "State.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(State)

void UState::Exec_Implementation()
{
}

void UState::CallExec()
{
    CelIndex = 0;
    Exec();
}

bool UState::CanEnterState_Implementation()
{
    return true;
}
```


