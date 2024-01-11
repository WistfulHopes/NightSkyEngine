﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BattleObject.h"
#include "NightSkyEngine/Battle/InputBuffer.h"
#include "NightSkyEngine/Battle/State.h"
#include "NightSkyEngine/Battle/StateMachine.h"
#include "NightSkyEngine/Data/CollisionData.h"
#include "NightSkyEngine/Data/FlipbookData.h"
#include "NightSkyEngine/Data/SequenceData.h"
#include "NightSkyEngine/Data/SoundData.h"
#include "NightSkyEngine/Data/StateData.h"
#include "PlayerObject.generated.h"

class USubroutine;
class UCameraShakeData;
constexpr int32 DamageReactionCelCount = 64;
constexpr int32 ExtraGaugeCount = 5;
constexpr int32 CancelArraySize = 64;
constexpr int32 MaxComponentCount = 64;

class USubroutineData;
class UStateData;
class UParticleData;
class UMaterialData;

UENUM(BlueprintType)
enum EActionStance
{
	ACT_Standing,
	ACT_Crouching,
	ACT_Jumping,
};

USTRUCT()
struct FExtraGauge
{
	GENERATED_BODY()

	uint32 Value;
	uint32 InitialValue;
	uint32 MaxValue;
	uint32 Sections;
};

USTRUCT()
struct FSavedInputCondition
{
	GENERATED_BODY()
	
	FInputBitmask Sequence[32];
	int Lenience = 8;
	int ImpreciseInputCount = 0;
	bool bInputAllowDisable = true;
	EInputMethod Method = EInputMethod::Normal;
};

/**
 * 
 */
UCLASS()
class NIGHTSKYENGINE_API APlayerObject : public ABattleObject
{
	GENERATED_BODY()

public:
	APlayerObject();
	
	//Starting from this until PlayerSyncEnd, everything is saved/loaded for rollback.
	unsigned char PlayerSync;
	
	/*
	 * Default values
	 */

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 FWalkSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BWalkSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 FDashInitSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 FDashAccel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 FDashMaxSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 FDashFriction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BDashSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BDashHeight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BDashGravity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 JumpHeight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 FJumpSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BJumpSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 JumpGravity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SuperJumpHeight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 FSuperJumpSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BSuperJumpSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SuperJumpGravity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AirDashMinimumHeight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 FAirDashSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BAirDashSpeed;
	// Time until forward air dash properties stop applying.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 FAirDashTime;
	// Time until backward air dash properties stop applying.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BAirDashTime;
	// Time until forward air dash can be cancelled.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 FAirDashNoAttackTime;
	// Time until backward air dash can be cancelled.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BAirDashNoAttackTime; 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AirJumpCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AirDashCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 StandPushWidth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 StandPushHeight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CrouchPushWidth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CrouchPushHeight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AirPushWidth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AirPushHeight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AirPushHeightLow;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CloseNormalRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxMeter = 10000;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ComboRate = 60;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 OtgProration = 80;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ForwardWalkMeterGain;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ForwardJumpMeterGain;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ForwardDashMeterGain;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ForwardAirDashMeterGain;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MeterPercentOnHit = 72;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MeterPercentOnHitGuard = 18;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MeterPercentOnReceiveHitGuard = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MeterPercentOnReceiveHit = 40;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool CanReverseBeat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool CanProximityThrow;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FInputCondition ProximityThrowInput;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ThrowTechWindow = 6;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ThrowResistAfterWakeUp = 5;	
	
	/*
	 * Player registers. These are only touched by the engine to reset per round.
	 * Use these to keep track of values (timers, toggles, counters, etc) that are character-specific.
	 */
	UPROPERTY(BlueprintReadWrite)
	int32 PlayerReg1 = 0;
	UPROPERTY(BlueprintReadWrite)
	int32 PlayerReg2 = 0;
	UPROPERTY(BlueprintReadWrite)
	int32 PlayerReg3 = 0;
	UPROPERTY(BlueprintReadWrite)
	int32 PlayerReg4 = 0;
	UPROPERTY(BlueprintReadWrite)
	int32 PlayerReg5 = 0;
	UPROPERTY(BlueprintReadWrite)
	int32 PlayerReg6 = 0;
	UPROPERTY(BlueprintReadWrite)
	int32 PlayerReg7 = 0;
	UPROPERTY(BlueprintReadWrite)
	int32 PlayerReg8 = 0;
	
	/*
	 * Action data.
	 */

	UPROPERTY()
	FStateMachine StoredStateMachine;

	/*
	 * Input data.
	 */
	uint32 Inputs;
	
	UPROPERTY()
	FInputBuffer StoredInputBuffer;
	
	/*
	 * Miscellaneous values.
	 */
	
	// If true, inputs will operate as if the character is facing the opposite direction.
	UPROPERTY(BlueprintReadWrite)
	bool FlipInputs;
	UPROPERTY(EditAnywhere)
	int32 MaxOTGCount;
	
	UPROPERTY(BlueprintReadOnly)
	int32 PlayerIndex;
	UPROPERTY(BlueprintReadOnly)
	int32 TeamIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TEnumAsByte<EActionStance> Stance;
	
	int32 CurrentHealth;
	int32 TotalProration = 10000;
	int32 ComboCounter;
	int32 ComboTimer;
	uint32 InvulnFlags = 0;
	uint32 PlayerFlags = 0;
	uint32 EnableFlags = 0;
	uint32 StrikeInvulnerableTimer = 0;
	uint32 ThrowInvulnerableTimer = 0;
	uint32 ThrowResistTimer = 0;
	FExtraGauge ExtraGauges[ExtraGaugeCount];
	uint32 AirDashTimer = 0;
	int32 OTGCount;
	int32 RoundWinTimer = 180;
	int32 WallTouchTimer;
	
	/*
	 * Object pointers.
	 */
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	APlayerObject* Enemy;
	UPROPERTY(BlueprintReadOnly)
	ABattleObject* AttackOwner;
	UPROPERTY()
	ABattleObject* ChildBattleObjects[64];
	UPROPERTY()
	ABattleObject* StoredBattleObjects[16];

	bool ComponentVisible[MaxComponentCount];
	FSavedInputCondition SavedInputCondition;

protected:
	/*
	 * Internal values.
	 */
	uint32 CurrentAirJumpCount = 0;
	uint32 CurrentAirDashCount = 0;
	uint32 AirDashTimerMax = 0;
	uint32 CancelFlags = 0;
	uint32 AirDashNoAttackTime = 0;
	uint32 InstantBlockLockoutTimer = 0;
	uint32 MeterCooldownTimer = 0;
	int32 ThrowRange;
	int32 ThrowTechTimer;

	//Chain cancels (copied from TArray to static array)
	int32 ChainCancelOptionsInternal[CancelArraySize] = {};
	//Whiff cancels (copied from TArray to static array)
	int32 WhiffCancelOptionsInternal[CancelArraySize] = {};
	//checks state indices for moves used in current combo
	int32 MovesUsedInCombo[CancelArraySize] = {};
	FName LastStateName;
	FName ExeStateName;
	FName BufferedStateName;
	
public:
	//Anything past here isn't saved or loaded for rollback.
	unsigned char PlayerSyncEnd; 

	UPROPERTY(EditAnywhere)
	TArray<FString> DamageReactionCels;

	/*
	 * Data to copy from blueprint TArray to internal object
	 */
	
	TArray<FName> ChainCancelOptions;
	TArray<FName> WhiffCancelOptions; 

	/*
	 * States and subroutines
	*/
	
	UPROPERTY()
	TArray<USubroutine*> CommonSubroutines;
	TArray<FName> CommonSubroutineNames;
	UPROPERTY()
	TArray<USubroutine*> Subroutines;
	TArray<FName> SubroutineNames;
	
	UPROPERTY()
	TArray<UState*> CommonObjectStates;
	TArray<FName> CommonObjectStateNames;	
	TArray<bool> CommonObjectStateUsed;	
	UPROPERTY()
	TArray<UState*> ObjectStates;
	TArray<FName> ObjectStateNames;	
	TArray<bool> ObjectStateUsed;	

	/*
	 * Data assets
	 */
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UCollisionData* CommonCollisionData;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UCollisionData* CollisionData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USubroutineData* CommonSubroutineData;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USubroutineData* CharaSubroutineData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStateData* CommonObjectStateData;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStateData* ObjectStateData;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStateData* CharaStateData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialData* MaterialData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ColorIndex = 1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 MaxColorIndex = 2;
	
	UPROPERTY(EditAnywhere)
	UFlipbookData* CommonFlipbookData;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UFlipbookData* FlipbookData;
	
	UPROPERTY(EditAnywhere)
	UParticleData* CommonParticleData;
	UPROPERTY(EditAnywhere)
	UParticleData* CharaParticleData;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USequenceData* CommonSequenceData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USequenceData* SequenceData;
	UPROPERTY(EditAnywhere)
	UCameraShakeData* CameraShakeData;

	UPROPERTY(EditAnywhere)
	USoundData* CommonSoundData;
	UPROPERTY(EditAnywhere)
	USoundData* SoundData;
	UPROPERTY(EditAnywhere)
	USoundData* VoiceData;

	UPROPERTY()
	TArray<USkeletalMeshComponent*> SkeletalMeshComponents;

private:
	virtual void BeginPlay() override;
	
	//check state conditions
	bool HandleStateCondition(EStateCondition StateCondition);
	//check if chain cancel option exists
	bool FindChainCancelOption(const FName Name);
	//check if whiff cancel option exists
	bool FindWhiffCancelOption(const FName Name);
	//check reverse beat
	bool CheckReverseBeat(const FName Name);
	//checks moves used in combo
	bool CheckMovesUsedInCombo(const FName Name);
	//upon successful throw, jump to state
	void ThrowExe();
	//handles throwing objects
	void HandleThrowCollision();
	//checks kara cancel
	bool CheckKaraCancel(EStateType InStateType);
	//checks if a child object with a corresponding object id exists. if so, do not enter state 
	bool CheckObjectPreventingState(int InObjectID);
	//handles wall bounce
	void HandleWallBounce();
	//handles ground bounce
	void HandleGroundBounce();
	void SetComponentVisibility() const;
	virtual void UpdateVisuals() override;

public:
	//initialize player for match/round start
	void InitPlayer();
	//update object
	virtual void Update() override;
	// handle state machine
	void HandleStateMachine(bool Buffer);
	//buffer state
	void HandleBufferedState();
	//update object for non-battle modes (like character select)
	void UpdateNotBattle();
	//update object (editor only, compiled out otherwise)
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void EditorUpdate();
	//based on received hit action, choose state
	void HandleHitAction(EHitAction HACT);
	//set hit values over time
	void SetHitValuesOverTime();
	//check attack against block stance
	bool IsCorrectBlock(EBlockType BlockType);
	//jump to correct block state
	void HandleBlockAction();
	//handles proximity blocking
	void HandleProximityBlock();
	//called right before state changes
	void OnStateChange();
	//called right after state changes
	void PostStateChange();
	//resets object for next round
	void ResetForRound();
	//disables last input
	void DisableLastInput();
	
	void SaveForRollbackPlayer(unsigned char* Buffer) const;
	void LoadForRollbackPlayer(const unsigned char* Buffer);
	virtual void LogForSyncTestFile(std::ofstream& file) override;

	//ONLY CALL WHEN INITIALIZING MATCH! OTHERWISE THE GAME WILL CRASH
	UFUNCTION(BlueprintImplementableEvent)
	void InitBP();
	//ONLY CALL AT THE START OF InitStateMachine! OTHERWISE THE GAME WILL CRASH
	UFUNCTION(BlueprintCallable)
	void EmptyStateMachine();
	
	/*
	 * Blueprint callable functions.
	 */
	//add state to state machine
	UFUNCTION(BlueprintCallable)
	void AddState(FString Name, UState* State); 
	//add object state
	UFUNCTION(BlueprintCallable)
	void AddObjectState(FString Name, UState* State, bool IsCommon); 
	//add subroutine to state machine
	UFUNCTION(BlueprintCallable)
	void AddSubroutine(FString Name, USubroutine* Subroutine, bool IsCommon);
	//use meter
	UFUNCTION(BlueprintCallable)
	void UseMeter(int Use);
	//add meter
	UFUNCTION(BlueprintCallable)
	void AddMeter(int Meter);
	//sets meter gain cooldown timer
	UFUNCTION(BlueprintCallable)
	void SetMeterCooldownTimer(int Timer);
	UFUNCTION(BlueprintPure)
	int32 GetGauge(int32 Index) const;
	UFUNCTION(BlueprintCallable)
	void SetGauge(int32 Index, int Value);
	UFUNCTION(BlueprintCallable)
	void UseGauge(int32 Index, int Use);
	//set stance
	UFUNCTION(BlueprintCallable)
	void SetStance(EActionStance InStance);
	//force set state
	UFUNCTION(BlueprintCallable, CallInEditor)
	void JumpToState(FString NewName, bool IsLabel = false);
	//gets current state name
	UFUNCTION(BlueprintPure)
	FString GetCurrentStateName() const;
	//gets current state name
	UFUNCTION(BlueprintPure)
	FString GetLastStateName();
	//check if state can be entered
	UFUNCTION(BlueprintPure)
	bool CheckStateEnabled(EStateType StateType);
	//enable state type
	UFUNCTION(BlueprintCallable)
	void EnableState(UPARAM(meta = (Bitmask, BitmaskEnum = EEnableFlags)) int32 Bitmask);
	//disables state type
	UFUNCTION(BlueprintCallable)
	void DisableState(UPARAM(meta = (Bitmask, BitmaskEnum = EEnableFlags)) int32 Bitmask);
	//enable all attacks only
	UFUNCTION(BlueprintCallable)
	void EnableAttacks();
	//enable cancelling into same state
	UFUNCTION(BlueprintCallable)
	void EnableCancelIntoSelf(bool Enable);
	//enables all state types besides tech
	UFUNCTION(BlueprintCallable)
	void EnableAll();
	//disable all state types besides tech
	UFUNCTION(BlueprintCallable)
	void DisableAll();
	//checks input condition
	UFUNCTION(BlueprintPure)
	bool CheckInput(const FInputCondition& Input);
	//is attacking
	UFUNCTION(BlueprintPure)
	bool CheckIsAttacking() const;
	UFUNCTION(BlueprintPure)
	bool CheckIsStunned() const;
	//temporarily adds air jump
	UFUNCTION(BlueprintCallable)
	void AddAirJump(int32 NewAirJump);
	//temporarily adds air dash
	UFUNCTION(BlueprintCallable)
	void AddAirDash(int32 NewAirDash);
	//set air dash timer (set is forward for forward airdashes)
	UFUNCTION(BlueprintCallable)
	void SetAirDashTimer(bool IsForward);
	//set air dash timer (set is forward for forward airdashes)
	UFUNCTION(BlueprintCallable)
	void SetAirDashNoAttackTimer(bool IsForward);
	//add chain cancel option, use this in Init
	UFUNCTION(BlueprintCallable)
	void AddChainCancelOption(FString Option);
	//add whiff cancel option, use this in Init
	UFUNCTION(BlueprintCallable)
	void AddWhiffCancelOption(FString Option);
	//add chain cancel option, use this in Init
	UFUNCTION(BlueprintCallable)
	void RemoveChainCancelOption(FString Option);
	//add whiff cancel option, use this in Init
	UFUNCTION(BlueprintCallable)
	void RemoveWhiffCancelOption(FString Option);
	UFUNCTION(BlueprintCallable)
	void EnableChainCancel(bool Enable);
	//sets whiff cancel options enabled. off by default
	UFUNCTION(BlueprintCallable)
	void EnableWhiffCancel(bool Enable);
	//enables jump cnacel
	UFUNCTION(BlueprintCallable)
	void EnableJumpCancel(bool Enable);
	//sets special cancel enabled. off by default
	UFUNCTION(BlueprintCallable)
	void EnableSpecialCancel(bool Enable);
	//sets super cancel enabled. off by default
	UFUNCTION(BlueprintCallable)
	void EnableSuperCancel(bool Enable);
	//enables forward airdash cnacel
	UFUNCTION(BlueprintCallable)
	void EnableForwardAirdashCancel(bool Enable);
	//toggles default landing action. if true, landing will go to JumpLanding state. if false, define your own landing.
	UFUNCTION(BlueprintCallable)
	void SetDefaultLandingAction(bool Enable);
	//sets strike invulnerable enabled
	UFUNCTION(BlueprintCallable)
	void SetStrikeInvulnerable(bool Invulnerable);
	//sets throw invulnerable enabled
	UFUNCTION(BlueprintCallable)
	void SetThrowInvulnerable(bool Invulnerable);
	UFUNCTION(BlueprintCallable)
	void SetHeadInvulnerable(bool Invulnerable);
	UFUNCTION(BlueprintCallable)
	void SetProjectileInvulnerable(bool Invulnerable);
	//sets strike invulnerable enabled for time
	UFUNCTION(BlueprintCallable)
	void SetStrikeInvulnerableForTime(int32 Timer);
	//sets throw invulnerable enabled for time
	UFUNCTION(BlueprintCallable)
	void SetThrowInvulnerableForTime(int32 Timer);
	//sets throw resist enabled for time
	UFUNCTION(BlueprintCallable)
	void SetThrowResistForTime(int32 Timer);
	//sets projectile invulnerable enabled
	//set stun time
	UFUNCTION(BlueprintCallable)
	void SetStunTime(int32 NewTime);
	//based on received hit data, set values
	UFUNCTION(BlueprintCallable)
	void SetHitValues();
	//force enables far proximity normals
	UFUNCTION(BlueprintCallable)
	void ForceEnableFarNormal(bool Enable);
	UFUNCTION(BlueprintCallable)
	void SetHeadAttribute(bool Attribute);
	//initiate throw
	UFUNCTION(BlueprintCallable)
	void SetThrowActive(bool Active);
	//end throw
	UFUNCTION(BlueprintCallable)
	void ThrowEnd(); 
	//initiate throw range
	UFUNCTION(BlueprintCallable)
	void SetThrowRange(int32 InThrowRange);
	//sets throw execution state
	UFUNCTION(BlueprintCallable)
	void SetThrowExeState(FString ExeState);
	//sets grip position for throw
	UFUNCTION(BlueprintCallable)
	void SetThrowPosition(int32 ThrowPosX, int32 ThrowPosY);
	//sets grip position for throw
	UFUNCTION(BlueprintCallable)
	void SetDamageReactionCel(int32 Index);
	//plays voice line
	UFUNCTION(BlueprintCallable)
	void PlayVoiceLine(FString Name);
	//plays common level sequence
	UFUNCTION(BlueprintCallable)
	void PlayCommonLevelSequence(FString Name);
	//plays character level sequence
	UFUNCTION(BlueprintCallable)
	void PlayLevelSequence(FString Name);
	//starts super freeze
	UFUNCTION(BlueprintCallable)
	void StartSuperFreeze(int Duration, int SelfDuration = 0);
	//toggles hud visibility
	UFUNCTION(BlueprintCallable)
	void BattleHudVisibility(bool Visible);
	//pauses round timer
	UFUNCTION(BlueprintCallable)
	void PauseRoundTimer(bool Pause);
	//stores battle actor in slot
	UFUNCTION(BlueprintCallable)
	void AddBattleObjectToStorage(ABattleObject* InActor, int Index);
	UFUNCTION(BlueprintCallable)
	void ToggleComponentVisibility(FString ComponentName, bool Visible);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetDefaultComponentVisibility();
};

constexpr size_t SizeOfPlayerObject = offsetof(APlayerObject, PlayerSyncEnd) - offsetof(APlayerObject, PlayerSync);