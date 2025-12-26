

# File NightSkyAIController.h

[**File List**](files.md) **>** [**Battle**](dir_59b3558fc0091a3111c9e7dd8d94b2ea.md) **>** [**CPU**](dir_0ffcc5e5c4d1b043480363e839fe227d.md) **>** [**NightSkyAIController.h**](_night_sky_a_i_controller_8h.md)

[Go to the documentation of this file](_night_sky_a_i_controller_8h.md)


```C++
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NightSkyEngine/Battle/Script/State.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "NightSkyAIController.generated.h"

class ANightSkyGameState;
class UState;
class APlayerObject;

UCLASS()
class NIGHTSKYENGINE_API ANightSkyAIController : public AAIController
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ANightSkyAIController();

    UPROPERTY(BlueprintReadOnly)
    TObjectPtr<APlayerObject> Player = nullptr;
    UPROPERTY(BlueprintReadOnly)
    TObjectPtr<ANightSkyGameState> GameState = nullptr;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

private:
    static constexpr int InputCountLimit = 2;

    UPROPERTY()
    UState* TargetState{};
    int WaitCount = 0;
    int WaitLimit = 7;
    int InputCount = 0;
    bool bBlock = false;
    
public:
    // Called every frame
    void Update();
    void ResetParams();
    bool SetInputs();
    
    UFUNCTION(BlueprintCallable)
    int32 GetEnemyDistanceX() const;
    UFUNCTION(BlueprintCallable)
    int32 GetEnemyDistanceY() const;

    UFUNCTION(BlueprintCallable)
    int32 CheckBasicWeight(const UState* State) const;
    UFUNCTION(BlueprintCallable)
    int32 CheckAttackWeight(const UState* State) const;
    UFUNCTION(BlueprintCallable)
    int32 CheckDefenseWeight(const UState* State);
};
```


