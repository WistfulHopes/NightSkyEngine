// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "NightSkyEngine/Battle/CollisionBox.h"
#include "NightSkyEngine/Battle/FixedString.h"
#include "BattleObject.generated.h"

class UNiagaraComponent;
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
	VFX_Special,
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
	int32 Blockstun = -1;
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
	HACT_AirNormal UMETA(DisplayName="Air Normal"),
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
	HACT_FloatingCrumple UMETA(DisplayName="Floating Crumple"),
};

UENUM(BlueprintType)
enum EFloatingCrumpleType
{
	FLT_None,
	FLT_Body,
	FLT_Head,
};

UENUM(BlueprintType)
enum EHitPositionType
{
	HPT_Non,
	HPT_Rel,
	HPT_Abs,
	HPT_Add,
	HPT_RelNextFrame,
	HPT_AbsNextFrame,
	HPT_AddNextFrame,
};

USTRUCT(BlueprintType)
struct FWallBounceData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	int32 WallBounceCount = -1;
	UPROPERTY(BlueprintReadWrite)
	int32 WallBounceUntech = -1;
	UPROPERTY(BlueprintReadWrite)
	int32 WallBounceXSpeed = -1;
	UPROPERTY(BlueprintReadWrite)
	int32 WallBounceXRate = -1;
	UPROPERTY(BlueprintReadWrite)
	int32 WallBounceYSpeed = -1;
	UPROPERTY(BlueprintReadWrite)
	int32 WallBounceYRate = -1;
	UPROPERTY(BlueprintReadWrite)
	int32 WallBounceGravity = -1;
	UPROPERTY(BlueprintReadWrite)
	bool WallBounceInCornerOnly = false;
};

USTRUCT(BlueprintType)
struct FGroundBounceData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	int32 GroundBounceCount = -1;
	UPROPERTY(BlueprintReadWrite)
	int32 GroundBounceUntech = -1;
	UPROPERTY(BlueprintReadWrite)
	int32 GroundBounceXSpeed = -1;
	UPROPERTY(BlueprintReadWrite)
	int32 GroundBounceXRate = -1;
	UPROPERTY(BlueprintReadWrite)
	int32 GroundBounceYSpeed = -1;
	UPROPERTY(BlueprintReadWrite)
	int32 GroundBounceYRate = -1;
	UPROPERTY(BlueprintReadWrite)
	int32 GroundBounceGravity = -1;
};

USTRUCT(BlueprintType)
struct FHitValueOverTime
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	int32 Value = -1;
	UPROPERTY(BlueprintReadWrite)
	int32 BeginFrame = -1;
	UPROPERTY(BlueprintReadWrite)
	int32 EndFrame = -1;
};

USTRUCT(BlueprintType)
struct FHitPosition
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	TEnumAsByte<EHitPositionType> Type;
	UPROPERTY(BlueprintReadWrite)
	int32 PosX = -1;
	UPROPERTY(BlueprintReadWrite)
	int32 PosY = -1;
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
	FHitValueOverTime AirPushbackXOverTime;
	UPROPERTY(BlueprintReadWrite)
	FHitValueOverTime AirPushbackYOverTime;
	UPROPERTY(BlueprintReadWrite)
	FHitValueOverTime GravityOverTime;
	UPROPERTY(BlueprintReadWrite)
	FHitPosition Position;
	UPROPERTY(BlueprintReadWrite)
	TEnumAsByte<EHitAction> GroundHitAction = HACT_GroundNormal;
	UPROPERTY(BlueprintReadWrite)
	TEnumAsByte<EHitAction> AirHitAction = HACT_AirNormal;
	UPROPERTY(BlueprintReadWrite)
	int32 BlowbackLevel = -1;
	UPROPERTY(BlueprintReadWrite)
	TEnumAsByte<EFloatingCrumpleType> FloatingCrumpleType;
	UPROPERTY(BlueprintReadWrite)
	int32 KnockdownTime = -1;
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

UENUM()
enum EDistanceType
{
	DIST_Distance,
	DIST_DistanceX,
	DIST_DistanceY,
	DIST_FrontDistanceX,
};

UENUM()
enum EHomingType
{
	HOMING_DistanceAccel,
	HOMING_FixAccel,
	HOMING_ToSpeed,
};

UENUM()
enum EPosType
{
	POS_Player,
	POS_Self,
	POS_Center,
	POS_Enemy,
	POS_Hit,
};

UENUM()
enum EObjType
{
	OBJ_Self,
	OBJ_Enemy,
	OBJ_Parent,
	OBJ_Child0,
	OBJ_Child1,
	OBJ_Child2,
	OBJ_Child3,
	OBJ_Child4,
	OBJ_Child5,
	OBJ_Child6,
	OBJ_Child7,
	OBJ_Child8,
	OBJ_Child9,
	OBJ_Child10,
	OBJ_Child11,
	OBJ_Child12,
	OBJ_Child13,
	OBJ_Child14,
	OBJ_Child15,
	OBJ_Null,
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
	uint32 StunTimeMax = 0;
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
	int32 PushWidthExtend = 0;

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
	int32 DrawPriority; //the lower the number, the farther in front the character will be drawn

	/*
	 * Link data (for object)
	 */
	UPROPERTY(BlueprintReadWrite)
	FVector ScaleForLink = FVector::One();
	UPROPERTY()
	UNiagaraComponent* LinkedParticle;
	UPROPERTY()
	USkeletalMeshComponent* LinkedMeshes[8];
	
	//Pointer to player object. If this is not a player, it will point to the owning player.
	UPROPERTY(BlueprintReadOnly)
	APlayerObject* Player;
	
	//Anything past here isn't saved or loaded for rollback.
	unsigned char ObjSyncEnd;

	uint32 ObjNumber;

	UPROPERTY(BlueprintReadOnly)
	float ScreenSpaceDepthOffset;
	UPROPERTY(BlueprintReadOnly)
	float OrthoBlendActive;
	
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
	void HandlePushCollision(ABattleObject* OtherObj);
	//handles hitting objects
	void HandleHitCollision(APlayerObject* OtherChar);
	//initializes hit data by attack level
	FHitData InitHitDataByAttackLevel(bool IsCounter);
	//handles object clashes
	void HandleClashCollision(ABattleObject* OtherObj);
	//handles flip
	void HandleFlip();
	//gets position from pos type
	void PosTypeToPosition(EPosType Type, int32* OutPosX, int32* OutPosY) const;
	void TriggerEvent(EEventType EventType);

	void CollisionView();
	
	void SaveForRollback(unsigned char* Buffer) const;
	void LoadForRollback(const unsigned char* Buffer);
	virtual void LogForSyncTestFile(FILE* file);
	
protected:
	void UpdateVisuals();
	void FuncCall(const FName& FuncName) const;
	void GetBoxes();
	
public:	
	// Cannot be called on player objects. Initializes the object for use.
	void InitObject();
	//update object
	virtual void Update();
	
	//resets object for next use
	void ResetObject();
	
	/*
	 * Blueprint callable functions.
	 */

	//initializes event handler
	UFUNCTION(BlueprintCallable)
	void InitEventHandler(EEventType EventType, FName FuncName);
	//initializes event handler
	UFUNCTION(BlueprintCallable)
	void RemoveEventHandler(EEventType EventType);
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
	//calculates distance between points
	UFUNCTION(BlueprintCallable)
	int32 CalculateDistanceBetweenPoints(EDistanceType Type, EObjType Obj1, EPosType Pos1, EObjType Obj2, EPosType Pos2);
	//sets direction
	UFUNCTION(BlueprintCallable)
	void SetFacing(EObjDir NewDir);
	//flips character
	UFUNCTION(BlueprintCallable)
	void FlipCharacter();
	//forcibly face opponent
	UFUNCTION(BlueprintCallable)
	void FaceOpponent();
	//check if grounded
	UFUNCTION(BlueprintPure)
	bool CheckIsGrounded();
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
	//should push collision be used?
	UFUNCTION(BlueprintCallable)
	void SetPushCollisionActive(bool Active);
	//set push width front
	UFUNCTION(BlueprintCallable)
	void SetPushWidthExtend(int32 Extend);
	//creates common particle
	UFUNCTION(BlueprintCallable)
	void CreateCommonParticle(FString Name, EPosType PosType, FVector Offset = FVector::ZeroVector, FRotator Rotation = FRotator::ZeroRotator);
	//creates character particle
	UFUNCTION(BlueprintCallable)
	void CreateCharaParticle(FString Name, EPosType PosType, FVector Offset = FVector::ZeroVector, FRotator Rotation = FRotator::ZeroRotator);
	//creates common particle and attaches it to the object. can only be used with non-player objects.
	UFUNCTION(BlueprintCallable)
	void LinkCommonParticle(FString Name);
	//creates character particle and attaches it to the object. can only be used with non-player objects.
	UFUNCTION(BlueprintCallable)
	void LinkCharaParticle(FString Name);
	//plays common sound
	UFUNCTION(BlueprintCallable)
	void PlayCommonSound(FString Name);
	//plays chara sound
	UFUNCTION(BlueprintCallable)
	void PlayCharaSound(FString Name);
	//initializes event handler
	UFUNCTION(BlueprintCallable)
	int32 GenerateRandomNumber(int32 Min, int32 Max);
	//gets object by type
	UFUNCTION(BlueprintPure)
	ABattleObject* GetBattleObject(EObjType Type);
	//creates common object
	UFUNCTION(BlueprintCallable)
	ABattleObject* AddCommonBattleObject(FString InStateName, int32 PosXOffset, int32 PosYOffset, EPosType PosType);
	//creates object
	UFUNCTION(BlueprintCallable)
	ABattleObject* AddBattleObject(FString InStateName, int32 PosXOffset, int32 PosYOffset, EPosType PosType);
	// Cannot be called on player objects. Deactivates the object and returns it to the pool.
	UFUNCTION(BlueprintCallable)
	void DeactivateObject();
};
#pragma pack(pop)

constexpr size_t SizeOfBattleObject = offsetof(ABattleObject, ObjSyncEnd) - offsetof(ABattleObject, ObjSync);