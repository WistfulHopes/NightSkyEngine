// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "NightSkyEngine/Battle/CollisionBox.h"
#include "NightSkyEngine/Battle/FixedString.h"
#include "BattleObject.generated.h"

class ANightSkyGameState;
class UState;
class APlayerObject;
constexpr int32 CollisionArraySize = 64;

/*
 * Event handler data
 */
#pragma pack (push, 1)

UENUM()
enum EEventType
{
	EVT_Enter,
	EVT_Update,
	EVT_Exit,
	EVT_Landing,
	EVT_Hit,
	EVT_Block,
	EVT_HitOrBlock,
	EVT_CounterHit,
	EVT_SuperFreeze,
	EVT_SuperFreezeEnd,
	EVT_NUM UMETA(Hidden)
};

USTRUCT()
struct FEventHandler
{
	GENERATED_BODY()

	FixedString<32> FunctionName;
};

/*
 * Hit related data
 */

UENUM()
enum EBlockType
{
	BLK_Mid UMETA(DisplayName="Mid"),
	BLK_High UMETA(DisplayName="High"),
	BLK_Low UMETA(DisplayName="Low"),
	BLK_None UMETA(DisplayName="Unblockable"),
};

UENUM()
enum class EHitSFXType : uint8
{
	SFX_Punch,
	SFX_Kick,
	SFX_Slash,
};

UENUM()
enum class EHitVFXType : uint8
{
	VFX_Strike,
	VFX_Slash,
};

USTRUCT(BlueprintType)
struct FHitDataCommon
{
	GENERATED_BODY()

	/*
	 * This controls default values for hit data.
	 * The minimum attack level is 0, and the maximum is 5.
	 * Any values that are set to -1 by default will take on data from the attack level.
	 */
	UPROPERTY(BlueprintReadWrite)
	int32 AttackLevel = 0; 
	UPROPERTY(BlueprintReadWrite)
	TEnumAsByte<EBlockType> BlockType = BLK_Mid;
	UPROPERTY(BlueprintReadWrite)
	int32 BlockstopModifier = -1;
	UPROPERTY(BlueprintReadWrite)
	int32 EnemyBlockstopModifier = 0;
	UPROPERTY(BlueprintReadWrite)
	int32 Blockstun = 0;
	UPROPERTY(BlueprintReadWrite)
	int32 ChipDamagePercent = 0;
	UPROPERTY(BlueprintReadWrite)
	int32 GroundGuardPushbackX = -1;
	UPROPERTY(BlueprintReadWrite)
	int32 AirGuardPushbackX = -1;
	UPROPERTY(BlueprintReadWrite)
	int32 AirGuardPushbackY = -1;
	UPROPERTY(BlueprintReadWrite)
	int32 GuardGravity = -1;
	UPROPERTY(BlueprintReadWrite)
	int32 HitAngle = 0;
	UPROPERTY(BlueprintReadWrite)
	EHitSFXType SFXType = EHitSFXType::SFX_Punch;
	UPROPERTY(BlueprintReadWrite)
	EHitVFXType VFXType = EHitVFXType::VFX_Strike;

	FixedString<32> GuardSFXOverride;
	FixedString<32> GuardVFXOverride;
	FixedString<32> HitSFXOverride;
	FixedString<32> HitVFXOverride;
};

UENUM()
enum EHitAction
{
	HACT_None UMETA(DisplayName="None"),
	HACT_GroundNormal UMETA(DisplayName="Ground Normal"),
	HACT_Stagger  UMETA(DisplayName="Stagger"),
	HACT_Crumple UMETA(DisplayName="Crumple"),
	HACT_ForceCrouch UMETA(DisplayName="Force Crouch"),
	HACT_ForceStand UMETA(DisplayName="Force Stand"),
	HACT_AirFaceUp UMETA(DisplayName="Air Face Up"),
	HACT_AirVertical UMETA(DisplayName="Air Vertical"),
	HACT_AirFaceDown UMETA(DisplayName="Air Face Down"),
	HACT_Blowback UMETA(DisplayName="Blowback"),
	HACT_GuardBreak UMETA(DisplayName="Guard Break"),
	HACT_GuardBreakStand UMETA(DisplayName="Guard Break Stand"),
	HACT_GuardBreakCrouch UMETA(DisplayName="Guard Break Crouch"),
	HACT_GuardBreakAir UMETA(DisplayName="Guard Break Air"),
};

USTRUCT(BlueprintType)
struct FWallBounceData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	int32 WallBounceCount = 0;
	UPROPERTY(BlueprintReadWrite)
	int32 WallBounceUntech = -1;
	UPROPERTY(BlueprintReadWrite)
	int32 WallBounceXSpeed = -1;
	UPROPERTY(BlueprintReadWrite)
	int32 WallBounceYSpeed = -1;
	UPROPERTY(BlueprintReadWrite)
	int32 WallBounceGravity = 1900;
	UPROPERTY(BlueprintReadWrite)
	bool WallBounceInCornerOnly = false;
};

USTRUCT(BlueprintType)
struct FGroundBounceData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	int32 GroundBounceCount = 0;
	UPROPERTY(BlueprintReadWrite)
	int32 GroundBounceUntech = -1;
	UPROPERTY(BlueprintReadWrite)
	int32 GroundBounceXSpeed = -1;
	UPROPERTY(BlueprintReadWrite)
	int32 GroundBounceYSpeed = -1;
	UPROPERTY(BlueprintReadWrite)
	int32 GroundBounceGravity = 1900;
};

USTRUCT(BlueprintType)
struct FHitData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	int32 Hitstop = -1;
	UPROPERTY(BlueprintReadWrite)
	int32 Hitstun = -1;
	UPROPERTY(BlueprintReadWrite)
	int32 Untech = -1;
	UPROPERTY(BlueprintReadWrite)
	int32 EnemyHitstopModifier = 0;
	UPROPERTY(BlueprintReadWrite)
	int32 Damage = -1;
	UPROPERTY(BlueprintReadWrite)
	int32 MinimumDamagePercent = 0;
	UPROPERTY(BlueprintReadWrite)
	int32 InitialProration = 100;
	UPROPERTY(BlueprintReadWrite)
	int32 ForcedProration = 90;
	UPROPERTY(BlueprintReadWrite)
	int32 GroundPushbackX = -1;
	UPROPERTY(BlueprintReadWrite)
	int32 AirPushbackX = -1;
	UPROPERTY(BlueprintReadWrite)
	int32 AirPushbackY = -1;
	UPROPERTY(BlueprintReadWrite)
	int32 Gravity = -1;
	UPROPERTY(BlueprintReadWrite)
	TEnumAsByte<EHitAction> GroundHitAction = HACT_GroundNormal;
	UPROPERTY(BlueprintReadWrite)
	TEnumAsByte<EHitAction> AirHitAction = HACT_AirFaceUp;
	int32 KnockdownTime = 12;
	UPROPERTY(BlueprintReadWrite)
	FGroundBounceData GroundBounce;
	UPROPERTY(BlueprintReadWrite)
	FWallBounceData WallBounce;
};

/*
 * Miscellaneous data
 */

UENUM()
enum EObjDir
{
	DIR_Right,
	DIR_Left,
};

UCLASS()
class NIGHTSKYENGINE_API ABattleObject : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABattleObject();
	
	//Starting from this until ObjSyncEnd, everything is saved/loaded for rollback.
	unsigned char ObjSync; 

	/*
	 * Movement and position values
	 */
	
	UPROPERTY(BlueprintReadWrite)
	int32 PosX;
	UPROPERTY(BlueprintReadWrite)
	int32 PosY;
	UPROPERTY(BlueprintReadWrite)
	int32 PosZ;
	int32 PrevPosX;
	int32 PrevPosY;
	int32 PrevPosZ;
	UPROPERTY(BlueprintReadWrite)
	int32 SpeedX;
	UPROPERTY(BlueprintReadWrite)
	int32 SpeedY;
	UPROPERTY(BlueprintReadWrite)
	int32 SpeedZ;
	UPROPERTY(BlueprintReadWrite)
	int32 SpeedXRate = 100;
	UPROPERTY(BlueprintReadWrite)
	int32 SpeedXRatePerFrame = 100;
	UPROPERTY(BlueprintReadWrite)
	int32 SpeedYRate = 100;
	UPROPERTY(BlueprintReadWrite)
	int32 SpeedYRatePerFrame = 100;
	UPROPERTY(BlueprintReadWrite)
	int32 SpeedZRate = 100;
	UPROPERTY(BlueprintReadWrite)
	int32 SpeedZRatePerFrame = 100;
	UPROPERTY(BlueprintReadWrite)
	int32 Gravity = 1900;
	// Inertia adds to the position every frame, but also decays every frame until it reaches zero.
	UPROPERTY(BlueprintReadWrite)
	int32 Inertia;
	// The minimum Y position before considered grounded.
	UPROPERTY(BlueprintReadWrite)
	int32 GroundHeight;
	UPROPERTY(BlueprintReadWrite)
	TEnumAsByte<EObjDir> Direction;
	// Ground hit pushback
	int32 Pushback;
	
	/*
	 * Attack data
	 */
	
	UPROPERTY(BlueprintReadWrite)
	FHitDataCommon HitCommon;
	UPROPERTY(BlueprintReadWrite)
	FHitData NormalHit;
	UPROPERTY(BlueprintReadWrite)
	FHitData CounterHit;
	uint32 AttackFlags;

	/*
	 * Received attack data
	 */

	FHitDataCommon ReceivedHitCommon;
	FHitData ReceivedHit;
	uint32 StunTime = 0;
	uint32 Hitstop = 0;
	
	/*
	 * Registers
	*/

	//This value stores the return value for functions.
	UPROPERTY(BlueprintReadOnly)
	bool ReturnReg;

	//The following values are per-action registers. Shared between the player and its child objects.
	UPROPERTY(BlueprintReadWrite)
	int32 ActionReg1;
	UPROPERTY(BlueprintReadWrite)
	int32 ActionReg2;
	UPROPERTY(BlueprintReadWrite)
	int32 ActionReg3;
	UPROPERTY(BlueprintReadWrite)
	int32 ActionReg4;
	UPROPERTY(BlueprintReadWrite)
	int32 ActionReg5;
	UPROPERTY(BlueprintReadWrite)
	int32 ActionReg6;
	UPROPERTY(BlueprintReadWrite)
	int32 ActionReg7;
	UPROPERTY(BlueprintReadWrite)
	int32 ActionReg8;

	//The following values are per-object registers.
	UPROPERTY(BlueprintReadWrite)
	int32 ObjectReg1;
	UPROPERTY(BlueprintReadWrite)
	int32 ObjectReg2;
	UPROPERTY(BlueprintReadWrite)
	int32 ObjectReg3;
	UPROPERTY(BlueprintReadWrite)
	int32 ObjectReg4;
	UPROPERTY(BlueprintReadWrite)
	int32 ObjectReg5;
	UPROPERTY(BlueprintReadWrite)
	int32 ObjectReg6;
	UPROPERTY(BlueprintReadWrite)
	int32 ObjectReg7;
	UPROPERTY(BlueprintReadWrite)
	int32 ObjectReg8;

	/*
	 * Action data
	 */

	UPROPERTY(BlueprintReadOnly)
	int32 ActionTime;
	FixedString<32> CelName;
	FixedString<32> LabelName;
	FixedString<32> AnimName;
	UPROPERTY(BlueprintReadWrite)
	bool GotoLabelActive;
	UPROPERTY(BlueprintReadWrite)
	int32 AnimFrame = 0;
	UPROPERTY(BlueprintReadWrite)
	int32 CelIndex = 0;
	UPROPERTY(BlueprintReadWrite)
	int32 TimeUntilNextCel = 0;
	FEventHandler EventHandlers[EVT_NUM];

	/*
	 * Action data for objects only.
	 */
	FixedString<32> ObjectStateName;
	uint32 ObjectID;
	
protected:
	/*
	 * Collision data
	 */
	int32 PushHeight = 0;
	int32 PushHeightLow = 0;
	int32 PushWidth = 0;
	int32 PushWidthFront = 0;

	int32 L;
	int32 R;
	int32 T;
	int32 B;
	
	FCollisionBox Boxes[CollisionArraySize] = {};

public:
	/*
	 * Miscellaneous data
	 */
	int32 HitPosX;
	int32 HitPosY;
	int32 MiscFlags;
	int32 SuperFreezeTimer;
	bool IsPlayer;
	bool IsActive;
	//Pointer to player object. If this is not a player, it will point to the owning player.
	UPROPERTY(BlueprintReadOnly)
	APlayerObject* Player; 

	//Anything past here isn't saved or loaded for rollback.
	unsigned char ObjSyncEnd;

	uint32 ObjNumber;
	
	UPROPERTY()
	ANightSkyGameState* GameState;
	
	UPROPERTY()
	UState* ObjectState;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Moves object
	void Move();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//handles pushing objects
	void HandlePushCollision(const ABattleObject* OtherObj);
	//handles hitting objects
	void HandleHitCollision(APlayerObject* OtherChar);
	//initializes hit data by attack level
	FHitData InitHitDataByAttackLevel(bool IsCounter);
	//handles object clashes
	void HandleClashCollision(ABattleObject* OtherObj);
	//handles flip
	void HandleFlip();
	void TriggerEvent(EEventType EventType);
	void SaveForRollback(unsigned char* Buffer) const;
	void LoadForRollback(unsigned char* Buffer);
	virtual void LogForSyncTestFile(FILE* file);
	
protected:
	void UpdateVisualLocation();
	void FuncCall(FName FuncName) const;
	void GetBoxes();
	
public:	
	// Cannot be called on player objects. Initializes the object for use.
	void InitObject();
	virtual void Update();
	
	//resets object for next use
	void ResetObject();
	
	/*
	 * Blueprint callable functions.
	 */

	//initializes event handler
	UFUNCTION(BlueprintCallable)
	void InitEventHandler(EEventType EventType, FName FuncName);
	//gets cel name
	UFUNCTION(BlueprintPure)
	FString GetCelName();
	//gets anim name
	UFUNCTION(BlueprintPure)
	FString GetAnimName();
	//gets label name
	UFUNCTION(BlueprintPure)
	FString GetLabelName();
	//sets cel name
	UFUNCTION(BlueprintCallable)
	void SetCelName(FString InName);
	//jumps to label
	UFUNCTION(BlueprintCallable)
	void GotoLabel(FString InName, bool ResetState = true);
	//adds x position
	UFUNCTION(BlueprintCallable)
	void AddPosXWithDir(int InPosX);
	//sets x speed
	UFUNCTION(BlueprintCallable)
	void SetSpeedXRaw(int InSpeedX);
	//adds x speed
	UFUNCTION(BlueprintCallable)
	void AddSpeedXRaw(int InSpeedX);
	//sets direction
	UFUNCTION(BlueprintCallable)
	void SetFacing(EObjDir NewDir);
	//flips character
	UFUNCTION(BlueprintCallable)
	void FlipCharacter();
	//forcibly face opponent
	UFUNCTION(BlueprintCallable)
	void FaceOpponent();
	//enables hit
	UFUNCTION(BlueprintCallable)
	void EnableHit(bool Enabled);
	//sets attacking. while this is true, you can be counter hit, but you can hit the opponent and chain cancel.
	UFUNCTION(BlueprintCallable)
	void SetAttacking(bool Attacking);
	//enables flip
	UFUNCTION(BlueprintCallable)
	void EnableFlip(bool Enabled);
	//enables inertia
	UFUNCTION(BlueprintCallable)
	void EnableInertia();
	//disables inertia
	UFUNCTION(BlueprintCallable)
	void DisableInertia();
	//halts momentum
	UFUNCTION(BlueprintCallable)
	void HaltMomentum();
	// Cannot be called on player objects. Deactivates the object and returns it to the pool.
	UFUNCTION(BlueprintCallable)
	void DeactivateObject();
};
#pragma pack(pop)

constexpr size_t SizeOfBattleObject = offsetof(ABattleObject, ObjSyncEnd) - offsetof(ABattleObject, ObjSync);