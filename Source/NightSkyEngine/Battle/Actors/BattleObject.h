// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <fstream>

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "NightSkyEngine/Battle/CollisionBox.h"
#include "BattleObject.generated.h"

class ANightSkyCharaSelectGameState;
class UPaperFlipbookComponent;
class UNiagaraComponent;
class ANightSkyGameState;
class UState;
class APlayerObject;
constexpr int32 CollisionArraySize = 64;

// Event handler data.

/*
 * Event type. When a function is registered with an event handler, 
 * it will trigger at the event type specified.
 */
 
UENUM(BlueprintType)
enum EEventType
{
	EVT_Enter UMETA(DisplayName="Enter"),
	EVT_Update UMETA(DisplayName="Update"),
	EVT_Exit UMETA(DisplayName="Exit"),
	EVT_Landing UMETA(DisplayName="Landing"),
	EVT_Hit UMETA(DisplayName="Hit"),
	EVT_Block UMETA(DisplayName="Block"),
	EVT_HitOrBlock UMETA(DisplayName="Hit or Block"),
	EVT_CounterHit UMETA(DisplayName="Counter Hit"),
	EVT_SuperFreeze UMETA(DisplayName="Super Freeze"),
	EVT_SuperFreezeEnd UMETA(DisplayName="Super Freeze End"),
	EVT_Timer0 UMETA(DisplayName="Timer #0"),
	EVT_Timer1 UMETA(DisplayName="Timer #1"),
	EVT_NUM UMETA(Hidden)
};

USTRUCT()
struct FEventHandler
{
	GENERATED_BODY()

	FName FunctionName;
	FName SubroutineName;
};

// Hit related data.

// How the opponent must block the attack.
UENUM()
enum EBlockType
{
	BLK_Mid UMETA(DisplayName="Mid"),
	BLK_High UMETA(DisplayName="High"),
	BLK_Low UMETA(DisplayName="Low"),
	BLK_None UMETA(DisplayName="Unblockable"),
};

// Hit sound effect type.
UENUM()
enum class EHitSFXType : uint8
{
	SFX_Punch UMETA(DisplayName="Punch"),
	SFX_Kick UMETA(DisplayName="Kick"),
	SFX_Slash UMETA(DisplayName="Slash"),
};

// Hit visual effect type.
UENUM()
enum class EHitVFXType : uint8
{
	VFX_Strike UMETA(DisplayName="Strike"),
	VFX_Slash UMETA(DisplayName="Slash"),
	VFX_Special UMETA(DisplayName="Special"),
};

/*
 * Common data for attacks.
 * These values will be used for blocking, normal hit, and counter hit.
 * Values that are set to -1 will be replaced by a default value depending on attack level.
 */

USTRUCT(BlueprintType)
struct FHitDataCommon
{
	GENERATED_BODY()

	/*
	 * This controls default values for hit data.
	 * The minimum attack level is 0, and the maximum is 5.
	 */
	UPROPERTY(BlueprintReadWrite)
	int32 AttackLevel = 0;
	// How the opponent must block the attack.
	UPROPERTY(BlueprintReadWrite)
	TEnumAsByte<EBlockType> BlockType = BLK_Mid;
	// Hitstop modifier for self on block, relative to normal hit's hitstop.
	UPROPERTY(BlueprintReadWrite)
	int32 BlockstopModifier = -1;
	// Hitstop modifier for opponent on block, relative to normal hit's hitstop.
	UPROPERTY(BlueprintReadWrite)
	int32 EnemyBlockstopModifier = 0;
	// How long the opponent will be stunned while blocking.
	UPROPERTY(BlueprintReadWrite)
	int32 Blockstun = -1;
	// The percent of normal hit damage the opponent will take when blocking this attack.
	UPROPERTY(BlueprintReadWrite)
	int32 ChipDamagePercent = 0;
	/*
	 * Ground pushback for blocking.
	 * If the opponent is in the corner, this will instead apply to self,
	 * even if you are airborne.
	 */
	UPROPERTY(BlueprintReadWrite)
	int32 GroundGuardPushbackX = -1;
	// Air x pushback for blocking.
	UPROPERTY(BlueprintReadWrite)
	int32 AirGuardPushbackX = -1;
	// Air y pushback for blocking.
	UPROPERTY(BlueprintReadWrite)
	int32 AirGuardPushbackY = -1;
	// Gravity for blocking.
	UPROPERTY(BlueprintReadWrite)
	int32 GuardGravity = -1;
	// The angle at which hit effects will spawn.
	UPROPERTY(BlueprintReadWrite)
	int32 HitAngle = 0;
	// Sound effect type.
	UPROPERTY(BlueprintReadWrite)
	EHitSFXType SFXType = EHitSFXType::SFX_Punch;
	// Visual effect type.
	UPROPERTY(BlueprintReadWrite)
	EHitVFXType VFXType = EHitVFXType::VFX_Strike;
	UPROPERTY(BlueprintReadWrite)
	bool DeathCamOverride = false;
	
	// Guard sound effect name.
	FName GuardSFXOverride;
	// Guard visual effect name.
	FName GuardVFXOverride;
	// Hit sound effect name.
	FName HitSFXOverride;
	// Hit visual effect name.
	FName HitVFXOverride;
};

/*
 * List of hit actions.
 * Depending on the hit action, animations and behavior will change.
 */
 
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
	HACT_Tailspin UMETA(DisplayName="Tailspin"),
	HACT_GuardBreak UMETA(DisplayName="Guard Break"),
	HACT_GuardBreakStand UMETA(DisplayName="Guard Break Stand"),
	HACT_GuardBreakCrouch UMETA(DisplayName="Guard Break Crouch"),
	HACT_GuardBreakAir UMETA(DisplayName="Guard Break Air"),
	HACT_FloatingCrumple UMETA(DisplayName="Floating Crumple"),
};

// Used with the Floating Crumple hit action.
UENUM(BlueprintType)
enum EFloatingCrumpleType
{
	FLT_None UMETA(DisplayName="None"),
	FLT_Body UMETA(DisplayName="Body"),
	FLT_Head UMETA(DisplayName="Head"),
};

// Determines how the opponent's position immediately after hit will be calculated.
UENUM(BlueprintType)
enum EHitPositionType
{
	HPT_Non UMETA(DisplayName="None"),
	HPT_Rel,
	HPT_Abs,
	HPT_Add UMETA(DisplayName="Add"),
	HPT_RelNextFrame,
	HPT_AbsNextFrame,
	HPT_AddNextFrame UMETA(DisplayName="Add Next Frame"),
};

/*
 * Data for wall bounce.
 * Values that are set to -1 will be replaced by a default value.
 */
USTRUCT(BlueprintType)
struct FWallBounceData
{
	GENERATED_BODY()

	// How many times the opponent will wall bounce.
	UPROPERTY(BlueprintReadWrite)
	int32 WallBounceCount = -1;
	// If this value is not -1, it will override the current untech duration.
	UPROPERTY(BlueprintReadWrite)
	int32 WallBounceUntech = -1;
	// The hitstop upon wall bounce.
	UPROPERTY(BlueprintReadWrite)
	int32 WallBounceStop = -1;
	/*
	 * Wall bounce x speed.
	 * If this value is -1, it will be set to the current x speed.
	 */
	UPROPERTY(BlueprintReadWrite)
	int32 WallBounceXSpeed = -1;
	/*
	 * The percent of wall bounce x speed.
	 * If this value is -1, it will be set to 33%.
	 */
	UPROPERTY(BlueprintReadWrite)
	int32 WallBounceXRate = -1;
	/*
	 * Wall bounce y speed.
	 * If this value is -1, it will be set to the received y pushback.
	 */
	UPROPERTY(BlueprintReadWrite)
	int32 WallBounceYSpeed = -1;
	/*
     * The percent of wall bounce y speed.
     * If this value is -1, it will be set to 100%.
     */
	UPROPERTY(BlueprintReadWrite)
	int32 WallBounceYRate = -1;
	/*
	 * Wall bounce gravity.
	 * If this value is -1, it will be set to the received hit gravity.
	 */
	UPROPERTY(BlueprintReadWrite)
	int32 WallBounceGravity = -1;
	// Determines if wall bounce can happen anywhere, or only in stage corner.
	UPROPERTY(BlueprintReadWrite)
	bool WallBounceInCornerOnly = false;
};

/*
 * Data for ground bounce.
 * Values that are set to -1 will be replaced by a default value.
 */
USTRUCT(BlueprintType)
struct FGroundBounceData
{
	GENERATED_BODY()

	// How many times the opponent will ground bounce.
	UPROPERTY(BlueprintReadWrite)
	int32 GroundBounceCount = -1;
	// If this value is not -1, it will override the current untech duration.
	UPROPERTY(BlueprintReadWrite)
	int32 GroundBounceUntech = -1;
	// The hitstop upon ground bounce.
	UPROPERTY(BlueprintReadWrite)
	int32 GroundBounceStop = -1;
	/*
	 * Ground bounce x speed.
	 * If this value is -1, it will be set to the received x pushback.
	 */
	UPROPERTY(BlueprintReadWrite)
	int32 GroundBounceXSpeed = -1;
	/*
	 * The percent of ground bounce x speed.
	 * If this value is -1, it will be set to 100%.
	 */
	UPROPERTY(BlueprintReadWrite)
	int32 GroundBounceXRate = -1;
	/*
	 * Ground bounce y speed.
	 * If this value is -1, it will be set to the current y speed.
	 */
	UPROPERTY(BlueprintReadWrite)
	int32 GroundBounceYSpeed = -1;
	/*
	 * The percent of ground bounce y speed.
	 * If this value is -1, it will be set to 100%.
	 */
	UPROPERTY(BlueprintReadWrite)
	int32 GroundBounceYRate = -1;
	/*
	 * Ground bounce gravity.
	 * If this value is -1, it will be set to the received hit gravity.
	 */
	UPROPERTY(BlueprintReadWrite)
	int32 GroundBounceGravity = -1;
};

/*
 * Value is added to the specified hit value every frame,
 * from BeginFrame to EndFrame.
 */
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

// Determines the opponent's position after being hit.
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

/*
 * Hit data.
 * There is one for normal hit, and one for counter hit.
 * For normal hit, values that are set to -1 will be replaced by a default value depending on attack level.
 * For counter hit, values that are set to -1 will be replaced by the normal hit's value.
 */
USTRUCT(BlueprintType)
struct FHitData
{
	GENERATED_BODY()

	// Hitstop duration for attacker and defender.
	UPROPERTY(BlueprintReadWrite)
	int32 Hitstop = -1;
	// How long the opponent will be stunned if hit grounded.
	UPROPERTY(BlueprintReadWrite)
	int32 Hitstun = -1;
	// How long the opponent will be stunned if hit airborne.
	UPROPERTY(BlueprintReadWrite)
	int32 Untech = -1;
	// Hitstop modifier for the opponent on hit.
	UPROPERTY(BlueprintReadWrite)
	int32 EnemyHitstopModifier = -1;
	// How much damage the opponent will take.
	UPROPERTY(BlueprintReadWrite)
	int32 Damage = -1;
	/*
	 * The minimum damage percent.
	 * Damage scaling cannot bring damage lower than this.
	 */
	UPROPERTY(BlueprintReadWrite)
	int32 MinimumDamagePercent = -1;
	/*
	 * Initial proration for hit.
	 * This is scaling that is applied only as the first hit of a combo.
	 */
	UPROPERTY(BlueprintReadWrite)
	int32 InitialProration = -1;
	/*
	 * Initial proration for hit.
	 * This is scaling that is applied every hit.
	 */
	UPROPERTY(BlueprintReadWrite)
	int32 ForcedProration = -1;
	/*
	 * Ground pushback for hit.
     * If the opponent is in the corner, this will instead apply to self,
	 * even if you are airborne.
	 */
	UPROPERTY(BlueprintReadWrite)
	int32 GroundPushbackX = -1;
	// Air x pushback for hit.
	UPROPERTY(BlueprintReadWrite)
	int32 AirPushbackX = -1;
	// Air y pushback for hit.
	UPROPERTY(BlueprintReadWrite)
	int32 AirPushbackY = -1;
	// Gravity for hit.
	UPROPERTY(BlueprintReadWrite)
	int32 Gravity = -1;
	/*
	 * The hit value over time for air pushback x.
	 * The value is a percentage.
	 */
	UPROPERTY(BlueprintReadWrite)
	FHitValueOverTime AirPushbackXOverTime;
	/*
	 * The hit value over time for air pushback y.
	 * The value is a percentage.
	 */
	UPROPERTY(BlueprintReadWrite)
	FHitValueOverTime AirPushbackYOverTime;
	/*
	 * The hit value over time for gravity.
	 * The value is added to current gravity.
	 */
	UPROPERTY(BlueprintReadWrite)
	FHitValueOverTime GravityOverTime;
	// Opponent position after hit.
	UPROPERTY(BlueprintReadWrite)
	FHitPosition Position;
	// Ground hit action.
	UPROPERTY(BlueprintReadWrite)
	TEnumAsByte<EHitAction> GroundHitAction = HACT_GroundNormal;
	// Air hit action.
	UPROPERTY(BlueprintReadWrite)
	TEnumAsByte<EHitAction> AirHitAction = HACT_AirNormal;
	// Blowback animation level. Used with the Blowback hit action.
	UPROPERTY(BlueprintReadWrite)
	int32 BlowbackLevel = -1;
	// Floating crumple type. Used with the Floating Crumple hit action.
	UPROPERTY(BlueprintReadWrite)
	TEnumAsByte<EFloatingCrumpleType> FloatingCrumpleType;
	// How long the opponent will be knocked down for before recovery. Defaults to 12 frames.
	UPROPERTY(BlueprintReadWrite)
	int32 KnockdownTime = -1;
	// Determines if the opponent can tech after being knocked down. Default is soft knockdown.
	UPROPERTY(BlueprintReadWrite)
	int32 HardKnockdown = -1;
	// Ground bounce data.
	UPROPERTY(BlueprintReadWrite)
	FGroundBounceData GroundBounce;
	// Wall bounce data.
	UPROPERTY(BlueprintReadWrite)
	FWallBounceData WallBounce;
};

/*
 * Miscellaneous data.
 */

// The character's facing direction.
UENUM()
enum EObjDir
{
	DIR_Right,
	DIR_Left,
};

// Used for distance calculations.
UENUM()
enum EDistanceType
{
	DIST_Distance,
	DIST_DistanceX,
	DIST_DistanceY,
	DIST_FrontDistanceX,
};

// Used for homing calculations.
UENUM(BlueprintType)
enum EHomingType
{
	HOMING_DistanceAccel,
	HOMING_FixAccel,
	HOMING_ToSpeed,
};

// Determines the position type to check.
UENUM(BlueprintType)
enum EPosType
{
	POS_Player,
	POS_Self,
	POS_Center,
	POS_Enemy,
	POS_Hit,
};

// Determines object type.
UENUM(BlueprintType)
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

USTRUCT(BlueprintType)
struct FHomingParams
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	TEnumAsByte<EHomingType> Type;
	UPROPERTY(BlueprintReadWrite)
	TEnumAsByte<EObjType> Target = OBJ_Null;
	UPROPERTY(BlueprintReadWrite)
	TEnumAsByte<EPosType> Pos;
	UPROPERTY(BlueprintReadWrite)
	int32 OffsetX;
	UPROPERTY(BlueprintReadWrite)
	int32 OffsetY;
	UPROPERTY(BlueprintReadWrite)
	int32 ParamA;
	UPROPERTY(BlueprintReadWrite)
	int32 ParamB;
};

/*
 * A battle object.
 * These are any objects that affect gameplay, or need values to change after being spawned.
 */
UCLASS()
class NIGHTSKYENGINE_API ABattleObject : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABattleObject();
	
	//Starting from this until ObjSyncEnd, everything is saved/loaded for rollback.
	unsigned char ObjSync = 0;

	/*
	 * Movement and position values
	 */
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 PosX = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 PosY = 0;
	UPROPERTY(BlueprintReadWrite)
	int32 PosZ = 0;
	int32 PrevPosX = 0;
	int32 PrevPosY = 0;
	int32 PrevPosZ = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool BlendOffset = false;
	int32 PrevOffsetX = 0;
	int32 PrevOffsetY = 0;
	int32 NextOffsetX = 0;
	int32 NextOffsetY = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 SpeedX = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 SpeedY = 0;
	UPROPERTY(BlueprintReadWrite)
	int32 SpeedZ = 0;
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
	int32 Inertia = 0;
	// The minimum Y position before considered grounded.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 GroundHeight = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TEnumAsByte<EObjDir> Direction = DIR_Right;
	// Ground hit pushback.
	int32 Pushback = 0;
	
	/*
	 * Attack data
	 */
	
	UPROPERTY(BlueprintReadWrite)
	FHitDataCommon HitCommon = {};
	UPROPERTY(BlueprintReadWrite)
	FHitData NormalHit = {};
	UPROPERTY(BlueprintReadWrite)
	FHitData CounterHit = {};
	uint32 AttackFlags = 0;

	/*
	 * Received attack data
	 */

	FHitDataCommon ReceivedHitCommon = {};
	FHitData ReceivedHit = {};
	uint32 StunTime = 0;
	uint32 StunTimeMax = 0;
	uint32 Hitstop = 0;
	
	/*
	 * Registers
	*/

	//This value stores the return value for functions.
	bool ReturnReg = false;

	//The following values are per-action registers. Shared between the player and its child objects.
	UPROPERTY(BlueprintReadWrite)
	int32 ActionReg1 = 0;
	UPROPERTY(BlueprintReadWrite)
	int32 ActionReg2 = 0;
	UPROPERTY(BlueprintReadWrite)
	int32 ActionReg3 = 0;
	UPROPERTY(BlueprintReadWrite)
	int32 ActionReg4 = 0;
	UPROPERTY(BlueprintReadWrite)
	int32 ActionReg5 = 0;
	UPROPERTY(BlueprintReadWrite)
	int32 ActionReg6 = 0;
	UPROPERTY(BlueprintReadWrite)
	int32 ActionReg7 = 0;
	UPROPERTY(BlueprintReadWrite)
	int32 ActionReg8 = 0;

	//The following values are per-object registers.
	UPROPERTY(BlueprintReadWrite)
	int32 ObjectReg1 = 0;
	UPROPERTY(BlueprintReadWrite)
	int32 ObjectReg2 = 0;
	UPROPERTY(BlueprintReadWrite)
	int32 ObjectReg3 = 0;
	UPROPERTY(BlueprintReadWrite)
	int32 ObjectReg4 = 0;
	UPROPERTY(BlueprintReadWrite)
	int32 ObjectReg5 = 0;
	UPROPERTY(BlueprintReadWrite)
	int32 ObjectReg6 = 0;
	UPROPERTY(BlueprintReadWrite)
	int32 ObjectReg7 = 0;
	UPROPERTY(BlueprintReadWrite)
	int32 ObjectReg8 = 0;
	
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
	 * Action data
	 */

	UPROPERTY(BlueprintReadOnly)
	int32 ActionTime = 0;
	/*
	 * The current cel name.
	 * Cels map to collision data.
	 * The collision frame also stores animation data.
	 */
	FName CelName = {};
	/*
	 * The blend cel name.
	 * This is used to make traditional 3D animations.
	 */
	FName BlendCelName = {};
	/*
	 * The name of the label that is currently being jumped to.
	 */
	FName LabelName = {};
	// The current animation name.
	FName AnimName = {};
	// The current blend animation name.
	FName BlendAnimName = {};
	// Are we jumping to a label right now?
	UPROPERTY(BlueprintReadWrite)
	bool GotoLabelActive = false;
	UPROPERTY(BlueprintReadWrite)
	int32 AnimFrame = 0;
	UPROPERTY(BlueprintReadWrite)
	int32 BlendAnimFrame = 0;
	UPROPERTY(BlueprintReadWrite)
	float FrameBlendPosition = 0;
	// The index of the current cel in blueprint.
	UPROPERTY(BlueprintReadWrite)
	int32 CelIndex = 0;
	// How long until the next cel activates.
	UPROPERTY(BlueprintReadOnly)
	int32 TimeUntilNextCel = 0;
	// Max time of the cel.
	int32 MaxCelTime = 0;
	// Event handlers for every function.
	FEventHandler EventHandlers[EVT_NUM] = {};

	/*
	 * Action data for objects only.
	 */
	FName ObjectStateName = {};
	uint32 ObjectID = 0;
	
protected:
	/*
	 * Collision data
	 */
	int32 PushHeight = 0;
	int32 PushHeightLow = 0;
	int32 PushWidth = 0;
	int32 PushWidthExtend = 0;

	int32 L = 0;
	int32 R = 0;
	int32 T = 0;
	int32 B = 0;
	
	FCollisionBox Boxes[CollisionArraySize];

public:
	/*
	 * Socket data
	 */
	FName SocketName = {}; 
	EObjType SocketObj = OBJ_Self;
	FVector SocketOffset = FVector::ZeroVector;

	//material parameters
	UPROPERTY(BlueprintReadWrite)
	FLinearColor MulColor = FLinearColor(1,1,1,1);
	UPROPERTY(BlueprintReadWrite)
	FLinearColor AddColor = FLinearColor(0,0,0,1);
	UPROPERTY(BlueprintReadWrite)
	FLinearColor MulFadeColor = {};
	UPROPERTY(BlueprintReadWrite)
	FLinearColor AddFadeColor = {};
	UPROPERTY(BlueprintReadWrite)
	float MulFadeSpeed = 0;
	UPROPERTY(BlueprintReadWrite)
	float AddFadeSpeed = 0;

	/*
	 * Miscellaneous data
	 */
	int32 HitPosX = 0;
	int32 HitPosY = 0;
	int32 MiscFlags = 0;
	int32 Timer0 = 0;
	int32 Timer1 = 0;
	bool IsPlayer = false;
	bool IsActive = false;
	int32 DrawPriority = 0; // the higher the number, the farther in front the object will be drawn

	UPROPERTY(BlueprintReadWrite)
	FHomingParams HomingParams = FHomingParams();
	
	UPROPERTY(BlueprintReadOnly)
	int32 UpdateTime = 0;
	
	/*
	 * Link data (for object)
	 */
	UPROPERTY(BlueprintReadWrite)
	FVector ScaleForLink = FVector::One();

	/*
	 * Object pointers.
	 */
	
	// Pointer to player object. If this is not a player, it will point to the owning player.
	UPROPERTY(BlueprintReadOnly)
	APlayerObject* Player = nullptr;
	UPROPERTY(BlueprintReadOnly)
	ABattleObject* AttackTarget = nullptr;
	UPROPERTY(BlueprintReadWrite)
	ABattleObject* PositionLinkObj = nullptr;
	UPROPERTY(BlueprintReadWrite)
	ABattleObject* StopLinkObj = nullptr;
	UPROPERTY(BlueprintReadWrite)
	ABattleObject* MaterialLinkObj = nullptr;
	
	int32 ObjectStateIndex = 0;
	bool bIsCommonState = false;
	
	//Anything past here isn't saved or loaded for rollback.
	unsigned char ObjSyncEnd = 0;

	/*
	 * Link data (for object), not serialized
	 */
	UPROPERTY()
	TObjectPtr<UNiagaraComponent> LinkedParticle = nullptr;
	UPROPERTY()
	TObjectPtr<UPaperFlipbookComponent> LinkedFlipbook = nullptr;
	UPROPERTY()
	TObjectPtr<USkeletalMeshComponent> LinkedMeshes[8] = {};
	
	uint32 ObjNumber = 0;

	UPROPERTY(BlueprintReadOnly)
	float ScreenSpaceDepthOffset = 0;
	UPROPERTY(BlueprintReadOnly)
	float OrthoBlendActive = 0;
	
	UPROPERTY()
	TObjectPtr<ANightSkyGameState> GameState = nullptr;
	UPROPERTY()
	TObjectPtr<ANightSkyCharaSelectGameState> CharaSelectGameState = nullptr;
	
	UPROPERTY()
	TObjectPtr<UState> ObjectState = nullptr;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Moves object
	void Move();
	void CalculateHoming();

	// static helpers
	static int32 Vec2Angle_x1000(int32 x, int32 y);
	static int32 Cos_x1000(int32 Deg_x10);
	static int32 Sin_x1000(int32 Deg_x10);
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//calculate pushbox
	void CalculatePushbox();
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

	UFUNCTION(BlueprintCallable)
	void CollisionView();
	
	void SaveForRollback(unsigned char* Buffer) const;
	void LoadForRollback(const unsigned char* Buffer);
	virtual void LogForSyncTestFile(std::ofstream& file);
	
protected:
	void FuncCall(const FName& FuncName) const;
	
public:	
	// Cannot be called on player objects. Initializes the object for use.
	void InitObject();
	// update object
	virtual void Update();
	// update visuals
	virtual void UpdateVisuals();
	
	void GetBoxes();
	
	// resets object for next use
	void ResetObject();
	
	/*
	 * Blueprint callable functions.
	 */

	UFUNCTION(BlueprintPure)
	bool IsStopped() const;
	UFUNCTION(BlueprintPure)
	bool IsTimerPaused() const;
	//calls subroutine
	UFUNCTION(BlueprintCallable)
	void CallSubroutine(FString Name);
	//calls subroutine
	UFUNCTION(BlueprintCallable)
	void CallSubroutineWithArgs(FString Name, int32 Arg1, int32 Arg2, int32 Arg3, int32 Arg4);
	//initializes event handler
	UFUNCTION(BlueprintCallable)
	void InitEventHandler(EEventType EventType, FName FuncName, int32 Value = 0, FString SubroutineName = "");
	//initializes event handler
	UFUNCTION(BlueprintCallable)
	void RemoveEventHandler(EEventType EventType);
	//gets cel name
	UFUNCTION(BlueprintPure)
	FString GetCelName() const;
	//gets anim name
	UFUNCTION(BlueprintPure)
	FString GetAnimName() const;
	//gets blend anim name
	UFUNCTION(BlueprintPure)
	FString GetBlendAnimName() const;
	//gets label name
	UFUNCTION(BlueprintPure)
	FString GetLabelName() const;
	//sets cel name
	UFUNCTION(BlueprintCallable)
	void SetCelName(FString InName);
	//sets cel name
	UFUNCTION(BlueprintCallable)
	void SetBlendCelName(FString InName);
	//jumps to label
	UFUNCTION(BlueprintCallable)
	void GotoLabel(FString InName, bool ResetState = true);
	//sets time until next cel
	UFUNCTION(BlueprintCallable)
	void SetTimeUntilNextCel(int32 InTime);
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
	UFUNCTION(BlueprintPure)
	int32 CalculateDistanceBetweenPoints(EDistanceType Type, EObjType Obj1, EPosType Pos1, EObjType Obj2, EPosType Pos2);
	//calculates angle between points
	UFUNCTION(BlueprintPure)
	int32 CalculateAngleBetweenPoints(EObjType Obj1, EPosType Pos1, EObjType Obj2, EPosType Pos2);
	//sets direction
	UFUNCTION(BlueprintCallable)
	void SetFacing(EObjDir NewDir);
	//flips character
	UFUNCTION(BlueprintCallable)
	void FlipObject();
	//forcibly face opponent
	UFUNCTION(BlueprintCallable)
	void FaceOpponent();
	//check if grounded
	UFUNCTION(BlueprintPure)
	bool CheckIsGrounded() const;
	//enables hit
	UFUNCTION(BlueprintCallable)
	void EnableHit(bool Enabled);
	//sets attacking. while this is true, you can be counter hit, but you can hit the opponent and chain cancel.
	UFUNCTION(BlueprintCallable)
	void SetAttacking(bool Attacking);
	UFUNCTION(BlueprintCallable)
	void SetProjectileAttribute(bool Attribute);
	UFUNCTION(BlueprintCallable)
	void SetProrateOnce(bool Once);
	UFUNCTION(BlueprintCallable)
	void SetIgnoreOTG(bool Ignore);
	UFUNCTION(BlueprintCallable)
	void SetIgnorePushbackScaling(bool Ignore);
	UFUNCTION(BlueprintCallable)
	void SetIgnoreHitstunScaling(bool Ignore);
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
	//should wall collision be used?
	UFUNCTION(BlueprintCallable)
	void SetWallCollisionActive(bool Active);
	//should push collision be used?
	UFUNCTION(BlueprintCallable)
	void SetPushCollisionActive(bool Active);
	//set push width extend
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
	//creates common flipbook and attaches it to the object. can only be used with non-player objects.
	UFUNCTION(BlueprintCallable)
	void LinkCommonFlipbook(FString Name);
	//creates character flipbook and attaches it to the object. can only be used with non-player objects.
	UFUNCTION(BlueprintCallable)
	void LinkCharaFlipbook(FString Name);
	//plays common sound
	UFUNCTION(BlueprintCallable)
	void PlayCommonSound(FString Name);
	//plays chara sound
	UFUNCTION(BlueprintCallable)
	void PlayCharaSound(FString Name);
	//attaches object to skeletal socket
	UFUNCTION(BlueprintCallable)
	void AttachToSocketOfObject(FString InSocketName, FVector Offset, EObjType ObjType);
	//detaches object from skeletal socket
	UFUNCTION(BlueprintCallable)
	void DetachFromSocket();
	UFUNCTION(BlueprintCallable)
	void CameraShake(FString PatternName, int32 Scale);
	//generate random number
	UFUNCTION(BlueprintPure)
	static int32 GenerateRandomNumber(int32 Min, int32 Max);
	//generate random number
	UFUNCTION(BlueprintCallable)
	void IgnoreSuperFreeze(bool Ignore);
	//sets object id
	UFUNCTION(BlueprintCallable)
	void SetObjectID(int InObjectID);
	//gets object by type
	UFUNCTION(BlueprintPure)
	ABattleObject* GetBattleObject(EObjType Type);
	//creates common object
	UFUNCTION(BlueprintCallable)
	ABattleObject* AddCommonBattleObject(FString InStateName, int32 PosXOffset = 0, int32 PosYOffset = 0, EPosType PosType = POS_Player);
	//creates object
	UFUNCTION(BlueprintCallable)
	ABattleObject* AddBattleObject(FString InStateName, int32 PosXOffset = 0, int32 PosYOffset = 0, EPosType PosType = POS_Player);
	//if object goes beyond screen bounds, deactivate
	UFUNCTION(BlueprintCallable)
	void EnableDeactivateIfBeyondBounds(bool Enable);
	//if player changes state, deactivate
	UFUNCTION(BlueprintCallable)
	void EnableDeactivateOnStateChange(bool Enable);
	//if player receives hit, deactivate
	UFUNCTION(BlueprintCallable)
	void EnableDeactivateOnReceiveHit(bool Enable);
	// Cannot be called on player objects. Deactivates the object and returns it to the pool.
	UFUNCTION(BlueprintCallable)
	void DeactivateObject();
};

constexpr size_t SizeOfBattleObject = offsetof(ABattleObject, ObjSyncEnd) - offsetof(ABattleObject, ObjSync);