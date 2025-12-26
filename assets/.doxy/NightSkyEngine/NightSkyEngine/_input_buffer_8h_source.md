

# File InputBuffer.h

[**File List**](files.md) **>** [**Battle**](dir_59b3558fc0091a3111c9e7dd8d94b2ea.md) **>** [**Misc**](dir_4fd921e402b7a240656c31e280e3875c.md) **>** [**InputBuffer.h**](_input_buffer_8h.md)

[Go to the documentation of this file](_input_buffer_8h.md)


```C++
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NightSkyEngine/Battle/Script/State.h"
#include "InputBuffer.generated.h"

constexpr int32 InputSequenceSize = 0x10;
constexpr int32 InputBufferSize = 0x20;

USTRUCT()
struct FInputBuffer
{
    GENERATED_BODY()
    
private:
    FInputBitmask InputSequence[InputSequenceSize] = {  };
    int32 ImpreciseInputCount = 0;
    TArray<TEnumAsByte<EInputFlags>> DisallowedInputs{};

    
public:
    int32 InputBufferInternal[InputBufferSize] = { 16 };
    int32 InputTime[InputBufferSize] = {};

    void WriteInputCondition(const FInputCondition& InputCondition);
    
    void Update(int32 Input, bool bStopped = false);
    void Emplace(int32 Input, uint32 Index);
    bool CheckInputCondition(const FInputCondition& InputCondition);

    bool CheckInputSequence() const;
    bool CheckInputSequenceStrict() const;
    bool CheckInputSequenceOnce() const;
    bool CheckInputSequenceOnceStrict() const;
    bool CheckInputSequencePressAndRelease() const;
    bool CheckInputSequencePressAndReleaseStrict() const;
    bool CheckInputSequenceNegative() const;
    bool CheckInputSequenceNegativeStrict() const;
    void FlipInputsInBuffer();
};
```


