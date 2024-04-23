// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bitflags.h"
#include "SerializableObj.h"
#include "State.generated.h"

class APlayerObject;
class ABattleObject;

/**
 * What stance the character must be in to enter this state.
 * Upon entering the state, the character will take this stance.
 */
UENUM(BlueprintType)
enum class EEntryStance : uint8
{
	/**
	 * No stance requirement; any state can enter.
	 */
	None,
	/**
	 * Must be grounded, and forces standing.
	 */
	Standing,
	/**
	 * Must be grounded, and forces crouching.
	 */
	Crouching,
	/**
	 * Must be airborne, and forces jumping.
	 */
	Jumping,
};

/**
 * The type of state. 
 * State types can have the ability to enter them toggled on and off.
 */
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
	NormalThrow,
	SpecialAttack,
	SuperAttack,
	Hitstun,
	Blockstun,
	Tech,
	Parry,
	Burst,
	SuperDash,
};

/**
 * A condition to enter the state.
 * 
 * @see APlayerObject::HandleStateCondition
 */
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
	FirstGaugeOneBar,
	FirstGaugeTwoBars,
	FirstGaugeThreeBars,
	FirstGaugeFourBars,
	FirstGaugeFiveBars,
	FirstGaugeSixBars,
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

/**
 * Determines the method of which the input will be read.
 */
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
};

/**
 * A container struct for input bitmasks.
 */
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

	/**
	 * The input flag.
	 *
	 * @see EInputFlags
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Bitmask, BitmaskEnum = EInputFlags))
	int InputFlag;
	
	/**
	 * How much buffer time there is for the input.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Lenience = 5;
	
	/**
	 * How much time is allowed between inputs.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 TimeBetweenInputs = 5;
};

/**
 * Contains an input condition.
 */
USTRUCT(BlueprintType)
struct FInputCondition
{
	GENERATED_BODY()

	/**
	 * A sequence of input bitmasks.
	 * Depending on lenience, the amount of time between inputs is increased or decreased.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FInputBitmask> Sequence;
	/**
	 * This value determines how many imprecise inputs are allowed in this condition.
	 * An imprecise input is a diagonal input that matches the cardinal direction.
	 * For use with the Strict or Once Strict input methods.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ImpreciseInputCount = 0;
	/**
	 * This value determines if the input buffer will consider disabled inputs.
	 * If true, and an input matches a disabled input on the same frame, the buffer will reject the sequence.
	 * Otherwise, the input sequence will be read as normal.
	 * @see APlayerObject::DisableLastInput
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bInputAllowDisable = true;
	/**
	 * The input method used for this condition. 
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EInputMethod Method = EInputMethod::Normal;
};

/**
 * A list of input conditions.
 * Every condition in this list must be met for the state to be entered.
 */
USTRUCT()
struct FInputConditionList
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	TArray<FInputCondition> InputConditions;
};

/**
 * @brief A character state that determines behavior.
 *
 * Provides functionality for the current character behavior, such as frame data, animations, and more.
 */
UCLASS(BlueprintType, Blueprintable)
class UState : public USerializableObj
{
	GENERATED_BODY()

public:
	/**
	 * The object that owns this state instance.
	 * For player states, this will always be the owning player.
	 * For object states, this value will change when a new object is activated and takes over this state.
	 */
	UPROPERTY(BlueprintReadOnly)
	ABattleObject* Parent;
	/**
	 * The current cel index.
	 * Used in Blueprint macros to determine which code to execute.
	 */
	UPROPERTY(BlueprintReadWrite)
	int32 CelIndex;
	/**
	 * The name of this state.
	 * For player states, this is used to jump to states directly.
	 * For object states, this is used to create an object by name.
	 */
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FString Name;
	/**
	 * The required stance to enter this state.
	 * Only used on player states.
	 */
	UPROPERTY(EditAnywhere)
	EEntryStance EntryStance;
	/**
	 * An array of input condition lists.
	 * Only the success of one input condition list is required to enter the state.
	 */
	UPROPERTY(EditAnywhere)
	TArray<FInputConditionList> InputConditionLists;
	/**
	 * The type of this state.
	 */
	UPROPERTY(EditAnywhere)
	EStateType StateType;
	/**
	 * An array of state conditions.
	 * All state conditions must be successful to enter this state.
	 */
	UPROPERTY(EditAnywhere)
	TArray<EStateCondition> StateConditions;
	/**
	 * A value that determines if this state can be entered directly, or must be canceled into. 
	 */
	UPROPERTY(EditAnywhere)
	bool IsFollowupState;
	/**
	 * A value that's set to match with spawned objects.
	 * If an owned object with this ID is active, this state can't be entered.
	 * For use with states that you do not wish to enter while the projectile is active.
	 * Only used on player states.
	 */
	UPROPERTY(EditAnywhere)
	int32 ObjectID;
	/**
	 * The maximum number of times this state can be used in a chain.
	 * For use with moves used in a combo that you wish to prevent cancelling into multiple times in sequence. 
	 */
	UPROPERTY(EditAnywhere)
	int32 MaxChain = -1;
	/**
	 * Determines how many of this state will be spawned.
	 * Only used on object states. Player states will ignore this value and always spawn one instance.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 MaxInstances = 1;

	/**
	 * Wrapper for Exec function that sets CelIndex to zero.
	 */
	void CallExec();

	/**
	 * Called every frame to update the state.
	 */
	UFUNCTION(BlueprintNativeEvent)
	void Exec();
};
