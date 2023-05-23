// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bitflags.h"
#include "State.generated.h"

class APlayerObject;
class ABattleObject;

UENUM(BlueprintType)
enum class EEntryState : uint8 //character state required to enter state
{
	None, //any
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
	NormalThrow,
	SpecialAttack,
	SuperAttack,
	Hitstun,
	Blockstun,
	Tech,
	Parry,
	Burst,
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
	Normal,
	Strict,
	Once,
	OnceStrict,
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Bitmask, BitmaskEnum = EInputFlags))
	int InputFlag;
};

USTRUCT(BlueprintType)
struct FInputCondition
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FInputBitmask> Sequence;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Lenience = 8;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ImpreciseInputCount = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bInputAllowDisable = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EInputMethod Method = EInputMethod::Normal;
};

USTRUCT()
struct FInputConditionList
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	TArray<FInputCondition> InputConditions;
};

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class UState : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	ABattleObject* Parent;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FString Name;
	UPROPERTY(EditAnywhere)
	EEntryState EntryState;
	UPROPERTY(EditAnywhere)
	TArray<FInputConditionList> InputConditionList;
	UPROPERTY(EditAnywhere)
	EStateType StateType;
	UPROPERTY(EditAnywhere)
	TArray<EStateCondition> StateConditions;
	UPROPERTY(EditAnywhere)
	bool IsFollowupState;
	UPROPERTY(EditAnywhere)
	int ObjectID;
	
	UFUNCTION(BlueprintNativeEvent)
	void Exec();
};
