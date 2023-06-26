#pragma once

#include "CoreMinimal.h"

UENUM(Meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum EInputFlags
{
	INP_None = 0x0,
	INP_Up = 0x1,
	INP_Down = 0x2,
	INP_Left = 0x4,
	INP_Right = 0x8,
	INP_UpLeft = INP_Up + INP_Left UMETA(Hidden),
	INP_UpRight = INP_Up + INP_Right UMETA(Hidden),
	INP_DownLeft = INP_Down + INP_Left UMETA(Hidden),
	INP_DownRight = INP_Down + INP_Right UMETA(Hidden),
	INP_Neutral = 0x10,
	INP_A = 0x20,
	INP_B = 0x40,
	INP_C = 0x80,
	INP_D = 0x100,
	INP_E = 0x200,
	INP_F = 0x400,
	INP_G = 0x800,
	INP_H = 0x1000,
};

ENUM_CLASS_FLAGS(EInputFlags);

UENUM(Meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum EEnableFlags
{
	ENB_None = 0x0 UMETA(Hidden),
	ENB_Standing = 0x1,
	ENB_Crouching = 0x2,
	ENB_Jumping = 0x4,
	ENB_ForwardWalk = 0x8,
	ENB_BackWalk = 0x10,
	ENB_ForwardDash = 0x20,
	ENB_BackDash = 0x40,
	ENB_ForwardAirDash = 0x80,
	ENB_BackAirDash = 0x100,
	ENB_NormalAttack = 0x200,
	ENB_SpecialAttack = 0x400,
	ENB_SuperAttack = 0x800,
	ENB_Block = 0x1000,
	ENB_ProximityBlock = 0x2000,
	ENB_Tech = 0x4000,
};

ENUM_CLASS_FLAGS(EEnableFlags);

UENUM()
enum EMiscFlags
{
	MISC_InertiaEnable = 0x1,
	MISC_FlipEnable = 0x2,
	MISC_WallCollisionActive = 0x4,
	MISC_FloorCollisionActive = 0x8,
	MISC_PushCollisionActive = 0x10,
	MISC_DeactivateOnNextUpdate = 0x20,
	MISC_DeactivateIfBeyondBounds = 0x40,
	MISC_DeactivateOnStateChange = 0x80,
	MISC_DeactivateOnReceiveHit = 0x100,
};

UENUM()
enum EAttackFlags
{
	ATK_HitActive = 0x1,
	ATK_IsAttacking = 0x2,
	ATK_AttackHeadAttribute = 0x4,
	ATK_AttackProjectileAttribute = 0x8,
	ATK_HasHit = 0x10,
	ATK_ProrateOnce = 0x20,
};

UENUM()
enum EPlayerFlags
{
	PLF_IsDead = 0x1,
	PLF_ThrowActive = 0x2,
	PLF_IsStunned = 0x4,
	PLF_IsThrowLock = 0x8,
	PLF_IsOnScreen = 0x10,
	PLF_DeathCamOverride = 0x20,
	PLF_IsKnockedDown = 0x40,
	PLF_IsHardKnockedDown = 0x80,
	PLF_RoundWinInputLock = 0x100,
	PLF_LockOpponentBurst = 0x200,
	PLF_DefaultLandingAction = 0x400,
	PLF_ForceEnableFarNormal = 0x800,
	PLF_TouchingWall = 0x1000,
};

UENUM()
enum ECancelFlags
{
	CNC_ChainCancelEnabled = 0x1,
	CNC_WhiffCancelEnabled = 0x2,
	CNC_SpecialCancel = 0x4,
	CNC_SuperCancel = 0x8,
	CNC_JumpCancel = 0x10,
	CNC_FAirDashCancel = 0x20, 
	CNC_BAirDashCancel = 0x40,
	CNC_EnableKaraCancel = 0x80,
	CNC_CancelIntoSelf = 0x100,
};

UENUM()
enum EInvulnFlags
{
	INV_StrikeInvulnerable = 0x1,
	INV_ThrowInvulnerable = 0x2,
	INV_ProjectileInvulnerable = 0x4,
	INV_HeadInvulnerable = 0x8,
};