// Fill out your copyright notice in the Description page of Project Settings.

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

class UParticleData;
class UMaterialData;
constexpr int32 DamageReactionCelCount = 64;
constexpr int32 ExtraGaugeCount = 5;
constexpr int32 CancelArraySize = 64;
constexpr int32 MaxComponentCount = 64;

class USubroutineData;
class UStateData;

#pragma pack (push, 1)

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
	 * Subroutine registers. These are set when calling a subroutine, and reset upon round end.
	 */
	UPROPERTY(BlueprintReadOnly)
	int32 SubroutineReg1 = 0;
	UPROPERTY(BlueprintReadOnly)
	int32 SubroutineReg2 = 0;
	UPROPERTY(BlueprintReadOnly)
	int32 SubroutineReg3 = 0;
	UPROPERTY(BlueprintReadOnly)
	int32 SubroutineReg4 = 0;

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

	UPROPERTY(BlueprintReadOnly)
	TEnumAsByte<EActionStance> Stance;
	
	int32 CurrentHealth;
	int32 TotalProration = 10000;
	int32 ComboCounter;
	int32 ComboTimer;
	int32 ThrowTechWindow = 6;
	uint32 InvulnFlags = 0;
	uint32 PlayerFlags = 0;
	uint32 EnableFlags = 0;
	uint32 StrikeInvulnerableTimer = 0;
	uint32 ThrowInvulnerableTimer = 0;
	FExtraGauge ExtraGauges[ExtraGaugeCount];
	uint32 AirDashTimer = 0;
	int32 OTGCount;
	int32 RoundWinTimer = 300;
	int32 WallTouchTimer;
	
	/*
	 * Object pointers.
	 */
	
	UPROPERTY(BlueprintReadOnly)
	APlayerObject* Enemy;
	UPROPERTY()
	ABattleObject* ChildBattleObjects[32];
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
	FixedString<32> DamageReactionCelsInternal[DamageReactionCelCount];

	//Chain cancels (copied from TArray to static array)
	int32 ChainCancelOptionsInternal[CancelArraySize] = {};
	//Whiff cancels (copied from TArray to static array)
	int32 WhiffCancelOptionsInternal[CancelArraySize] = {};
	//checks state indices for moves used in current combo
	int32 MovesUsedInCombo[CancelArraySize] = {};
	FixedString<64> LastStateName;
	FixedString<64> ExeStateName;
	FixedString<64> BufferedStateName;
	
public:
	//Anything past here isn't saved or loaded for rollback.
	unsigned char PlayerSyncEnd; 

	/*
	 * Data to copy from blueprint TArray to internal object
	 */
	
	UPROPERTY(EditAnywhere)
	TArray<FString> DamageReactionCels;
	TArray<FString> ChainCancelOptions;
	TArray<FString> WhiffCancelOptions; 

	/*
	 * States and subroutines
	*/
	
	UPROPERTY()
	TArray<USubroutine*> CommonSubroutines;
	TArray<FString> CommonSubroutineNames;
	UPROPERTY()
	TArray<USubroutine*> Subroutines;
	TArray<FString> SubroutineNames;
	
	UPROPERTY()
	TArray<UState*> CommonObjectStates;
	TArray<FString> CommonObjectStateNames;	
	UPROPERTY()
	TArray<UState*> ObjectStates;
	TArray<FString> ObjectStateNames;	

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
	UPROPERTY(BlueprintReadWrite)
	int32 ColorIndex = 1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 MaxColorIndex = 2;
	
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
	USoundData* CommonSoundData;
	UPROPERTY(EditAnywhere)
	USoundData* SoundData;
	UPROPERTY(EditAnywhere)
	USoundData* VoiceData;

	UPROPERTY()
	TArray<USkeletalMeshComponent*> SkeletalMeshComponents;

private:
	virtual void BeginPlay() override;
	void HandleStateMachine(bool Buffer);

	//buffer state
	void HandleBufferedState();
	//check state conditions
	bool HandleStateCondition(EStateCondition StateCondition);
	//check if chain cancel option exists
	bool FindChainCancelOption(const FString& Name);
	//check if whiff cancel option exists
	bool FindWhiffCancelOption(const FString& Name);
	//check reverse beat
	bool CheckReverseBeat(const FString& Name);
	//checks moves used in combo
	bool CheckMovesUsedInCombo(const FString& Name);
	//checks kara cancel
	bool CheckKaraCancel(EStateType InStateType);
	//checks if a child object with a corresponding object id exists. if so, do not enter state 
	bool CheckObjectPreventingState(int InObjectID);
	//handles wall bounce
	void HandleWallBounce();
	//handles ground bounce
	void HandleGroundBounce();

public:
	//initialize player for match/round start
	void InitPlayer();
	//update object
	virtual void Update() override;
	//update object for non-battle modes (like character select)
	void UpdateNotBattle();
	//update object (editor only, compiled out otherwise)
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
	virtual void LogForSyncTestFile(FILE* file) override;

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
	//calls subroutine
	UFUNCTION(BlueprintCallable)
	void CallSubroutine(FString Name);
	//calls subroutine
	UFUNCTION(BlueprintCallable)
	void CallSubroutineWithArgs(FString Name, int32 Arg1, int32 Arg2, int32 Arg3, int32 Arg4);
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
	//is in block or hitstun
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
	UFUNCTION(BlueprintCallable)
	void AddChainCancelOption(FString Option);
	//add whiff cancel option, use this in OnEntry
	UFUNCTION(BlueprintCallable)
	void AddWhiffCancelOption(FString Option);
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
	//sets strike invulnerable enabled for time
	UFUNCTION(BlueprintCallable)
	void SetStrikeInvulnerableForTime(int32 Timer);
	//sets throw invulnerable enabled for time
	UFUNCTION(BlueprintCallable)
	void SetThrowInvulnerableForTime(int32 Timer);
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
	void StartSuperFreeze(int Duration);
	//toggles hud visibility
	UFUNCTION(BlueprintCallable)
	void BattleHudVisibility(bool Visible);
	//stores battle actor in slot
	UFUNCTION(BlueprintCallable)
	void AddBattleObjectToStorage(ABattleObject* InActor, int Index);
};
#pragma pack(pop)

constexpr size_t SizeOfPlayerObject = offsetof(APlayerObject, PlayerSyncEnd) - offsetof(APlayerObject, PlayerSync);