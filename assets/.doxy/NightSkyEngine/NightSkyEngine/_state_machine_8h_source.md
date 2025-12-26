

# File StateMachine.h

[**File List**](files.md) **>** [**Battle**](dir_59b3558fc0091a3111c9e7dd8d94b2ea.md) **>** [**Script**](dir_0ca77fec7001245ae32841da8dbaa106.md) **>** [**StateMachine.h**](_state_machine_8h.md)

[Go to the documentation of this file](_state_machine_8h.md)


```C++
#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"
#include "State.h"
#include "StateMachine.generated.h"

class APlayerObject;

UE_DECLARE_GAMEPLAY_TAG_EXTERN(StateMachine_Primary);

USTRUCT(BlueprintType)
struct NIGHTSKYENGINE_API FStateMachine
{
    GENERATED_BODY()
    
    UPROPERTY(SaveGame)
    bool bPrimary;
    UPROPERTY(EditDefaultsOnly, SaveGame)
    FGameplayTag StateMachineName;
    UPROPERTY(SaveGame, meta=(Bitmask, BitmaskEnum = "/Script/NightSkyEngine.EEnableFlags"))
    int32 EnableFlags = 0;
    UPROPERTY(SaveGame)
    TArray<FGameplayTag> EnabledCustomStateTypes;
    UPROPERTY(SaveGame)
    UState* CurrentState;
    UPROPERTY()
    TArray<UState*> States;
    UPROPERTY()
    TArray<FGameplayTag> StateNames;
    UPROPERTY()
    APlayerObject* Parent;

    void AddState(const FGameplayTag& Name, UState* Config);

    FORCEINLINE bool IsCurrentState(const FGameplayTag& Name) const
    {
        return CurrentState->Name == Name;
    }
    
    FGameplayTag GetStateName(int Index);
    int GetStateIndex(FGameplayTag Name) const;

    bool SetState(const FGameplayTag Name, bool bIsAlias = false);
    bool ForceSetState(const FGameplayTag Name, bool bIsAlias = false);
    bool ForceSetState(TSubclassOf<UState> Class, bool bIsAlias = false);
    bool ForceRollbackState(const FGameplayTag Name);

    static bool CheckStateStanceCondition(const EEntryStance StateStance, const int PlayerStance);

    void Update() const;
};
```


