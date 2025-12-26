

# File State.h

[**File List**](files.md) **>** [**Battle**](dir_59b3558fc0091a3111c9e7dd8d94b2ea.md) **>** [**Script**](dir_0ca77fec7001245ae32841da8dbaa106.md) **>** [**State.h**](_state_8h.md)

[Go to the documentation of this file](_state_8h.md)


```C++
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NightSkyEngine/Battle/Misc/Bitflags.h"
#include "GameplayTagContainer.h"
#include "NightSkyEngine/Battle/Misc/SerializableObj.h"
#include "NightSkyEngine/Battle/Objects/BattleObject.h"
#include "State.generated.h"

class APlayerObject;
class ABattleObject;

UENUM(BlueprintType)
enum class EEntryStance : uint8
{
    None,
    Standing,
    Crouching,
    Jumping,
};

UENUM(BlueprintType)
enum class EStateType : uint8
{
    Standing,
    Crouching,
    NeutralJump,
    ForwardJump,
    BackwardJump,
    ForwardWalk,
    BackwardWalk,
    ForwardDash,
    BackwardDash,
    ForwardAirDash,
    BackwardAirDash,
    NormalAttack,
    SpecialAttack,
    SuperAttack,
    Hitstun,
    Blockstun,
    Tech,
    Burst,
    Tag,
    Assist,
    Custom,
};

UENUM(BlueprintType)
enum class EStateCondition : uint8
{
    None,
    AirJumpOk,
    AirJumpMinimumHeight,
    AirDashOk,
    AirDashMinimumHeight,
    IsAttacking,
    HitstopCancel,
    IsStunned,
    CloseNormal,
    FarNormal,
    CanTag2nd,
    CanTag3rd,
    MeterNotZero,
    MeterQuarterBar,
    MeterHalfBar,
    MeterOneBar,
    MeterTwoBars,
    MeterThreeBars,
    MeterFourBars,
    MeterFiveBars,
    PlayerReg1True,
    PlayerReg2True,
    PlayerReg3True,
    PlayerReg4True,
    PlayerReg5True,
    PlayerReg6True,
    PlayerReg7True,
    PlayerReg8True,
    PlayerReg1False,
    PlayerReg2False,
    PlayerReg3False,
    PlayerReg4False,
    PlayerReg5False,
    PlayerReg6False,
    PlayerReg7False,
    PlayerReg8False,
};

UENUM()
enum class EInputMethod : uint8
{
    /*
     * The button or direction may be held indefinitely.
     * Diagonal directions are counted as both of the cardinal directions it represents.
     */
    Normal,
    /*
     * The button or direction may be held indefinitely.
     * Diagonal directions are not counted as either of the cardinal directions it represents.
     */
    Strict,
    /*
     * The button or direction will only be counted on first press until release.
      * Diagonal directions are counted as both of the cardinal directions it represents.
     */
    Once,
    /*
     * The button or direction will only be counted on first press until release.
     * Diagonal directions are not counted as either of the cardinal directions it represents.
     * This is a combination of the Once and Strict methods.
     */
    OnceStrict,
    /*
     * The button or direction will only be counted when first pressed, then released.
      * Diagonal directions are counted as both of the cardinal directions it represents.
     */
    PressAndRelease,
    /*
     * The button or direction will only be counted when first pressed, then released.
     * Diagonal directions are not counted as either of the cardinal directions it represents.
     * This is a combination of the Once and Strict methods.
     */
    PressAndReleaseStrict,
    /*
     * The button or direction will only be counted at the moment of release.
      * Diagonal directions are counted as both of the cardinal directions it represents.
     */
    Negative,
    /*
     * The button or direction will only be counted at the moment of release.
     * Diagonal directions are not counted as either of the cardinal directions it represents.
     * This is a combination of the Negative and Strict methods.
     */
    NegativeStrict,
};

USTRUCT(BlueprintType)
struct FInputBitmask
{
    GENERATED_BODY()

    FInputBitmask()
    {
        InputFlag = INP_None;
    };
    FInputBitmask(EInputFlags Input)
    {
        InputFlag = Input;
    };

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Bitmask, BitmaskEnum = "/Script/NightSkyEngine.EInputFlags"))
    int InputFlag;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Lenience = 3;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Hold = 0;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<TEnumAsByte<EInputFlags>> DisallowedInputs;
};

USTRUCT(BlueprintType)
struct FInputCondition
{
    GENERATED_BODY()

    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FInputBitmask> Sequence;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<TEnumAsByte<EInputFlags>> DisallowedInputs;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int ImpreciseInputCount = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EInputMethod Method = EInputMethod::Normal;
};

USTRUCT(BlueprintType)
struct FInputConditionList
{
    GENERATED_BODY()
    
    UPROPERTY(EditAnywhere)
    TArray<FInputCondition> InputConditions;
};

UENUM()
enum ERangeType
{
    RAN_Near,
    RAN_Mid,
    RAN_Far,
};

UENUM()
enum EAttackSpeed
{
    ASPD_Fast,
    ASPD_Medium,
    ASPD_Slow,
};

USTRUCT()
struct FStateCPUData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere)
    int32 AttackXBeginRange = 0;
    UPROPERTY(EditAnywhere)
    int32 AttackXEndRange = 300000;
    UPROPERTY(EditAnywhere)
    int32 AttackYBeginRange = 120000;
    UPROPERTY(EditAnywhere)
    int32 AttackYEndRange = 360000;
    UPROPERTY(EditAnywhere)
    bool bAttack;
    UPROPERTY(EditAnywhere)
    bool bCombo;
    UPROPERTY(EditAnywhere)
    bool bNoCombo;
    UPROPERTY(EditAnywhere)
    bool bBlockstring;
    UPROPERTY(EditAnywhere)
    bool bPunish;
    UPROPERTY(EditAnywhere)
    bool bAntiAir;
    UPROPERTY(EditAnywhere)
    bool bThrow;
    UPROPERTY(EditAnywhere)
    bool bProjectile;
    UPROPERTY(EditAnywhere)
    TEnumAsByte<ERangeType> PunishRange;
    UPROPERTY(EditAnywhere)
    TEnumAsByte<EBlockType> BlockType;
    UPROPERTY(EditAnywhere)
    TEnumAsByte<EAttackSpeed> AttackSpeed;
    UPROPERTY(EditAnywhere)
    bool bBigDamage;
    UPROPERTY(EditAnywhere)
    bool bUsesResource;
    UPROPERTY(EditAnywhere)
    bool bInvuln;
};

UCLASS(BlueprintType, Blueprintable)
class UState : public USerializableObj
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadOnly)
    ABattleObject* Parent;
    UPROPERTY(BlueprintReadWrite)
    int32 CelIndex;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FGameplayTag Name;
    UPROPERTY(EditAnywhere)
    FGameplayTag ShareChainName;
    UPROPERTY(EditAnywhere)
    EEntryStance EntryStance;
    UPROPERTY(EditAnywhere)
    TArray<FInputConditionList> InputConditionLists;
    UPROPERTY(EditAnywhere)
    EStateType StateType;
    UPROPERTY(EditAnywhere)
    FGameplayTag CustomStateType;
    UPROPERTY(EditAnywhere)
    TArray<EStateCondition> StateConditions;
    UPROPERTY(EditAnywhere)
    bool IsFollowupState;
    UPROPERTY(EditAnywhere)
    int32 ObjectID;
    UPROPERTY(EditAnywhere)
    int32 MaxChain = -1;
    UPROPERTY(EditAnywhere)
    bool bEnableReverseBeat = true;
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int32 MaxInstances = 1;
    UPROPERTY(EditAnywhere)
    FStateCPUData CPUData;
    UPROPERTY(EditAnywhere)
    bool bHumanUsable = true;
    UPROPERTY(EditAnywhere)
    bool bCPUUsable = true;

    UFUNCTION(BlueprintImplementableEvent)
    void Init();
    
    virtual void CallExec();

    UFUNCTION(BlueprintNativeEvent)
    void Exec();
    
    UFUNCTION(BlueprintNativeEvent)
    bool CanEnterState();
};
```


