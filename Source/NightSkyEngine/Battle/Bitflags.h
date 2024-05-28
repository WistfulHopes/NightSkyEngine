#pragma once

#include "CoreMinimal.h"

/**
 * Input bitmasks. A layer of abstraction between the physical controller and the internal battle state.
 */
UENUM(Meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum EInputFlags
{
	INP_None = 0x0 UMETA(DisplayName = "None"),
	INP_Up = 0x1 UMETA(DisplayName = "Up"),
	INP_Down = 0x2 UMETA(DisplayName = "Down"),
	INP_Left = 0x4 UMETA(DisplayName = "Left"),
	INP_Right = 0x8 UMETA(DisplayName = "Right"),
	INP_UpLeft = INP_Up + INP_Left UMETA(Hidden),
	INP_UpRight = INP_Up + INP_Right UMETA(Hidden),
	INP_DownLeft = INP_Down + INP_Left UMETA(Hidden),
	INP_DownRight = INP_Down + INP_Right UMETA(Hidden),
	INP_Neutral = 0x10 UMETA(DisplayName = "Neutral"),
	INP_A = 0x20 UMETA(DisplayName = "A"),
	INP_B = 0x40 UMETA(DisplayName = "B"),
	INP_C = 0x80 UMETA(DisplayName = "C"),
	INP_D = 0x100 UMETA(DisplayName = "D"),
	INP_E = 0x200 UMETA(DisplayName = "E"),
	INP_F = 0x400 UMETA(DisplayName = "F"),
	INP_G = 0x800 UMETA(DisplayName = "G"),
	INP_H = 0x1000 UMETA(DisplayName = "H"),
};

ENUM_CLASS_FLAGS(EInputFlags);

/**
 * Flags used to enable or disable specific states or actions.
 */
UENUM(Meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum EEnableFlags
{
	ENB_None = 0x0 UMETA(Hidden),
	ENB_Standing = 0x1 UMETA(DisplayName = "Standing"),
	ENB_Crouching = 0x2 UMETA(DisplayName = "Crouching"),
	ENB_Jumping = 0x4 UMETA(DisplayName = "Jumping"),
	ENB_ForwardWalk = 0x8 UMETA(DisplayName = "Forward Walk"),
	ENB_BackWalk = 0x10 UMETA(DisplayName = "Backward Walk"),
	ENB_ForwardDash = 0x20 UMETA(DisplayName = "Forward Dash"),
	ENB_BackDash = 0x40 UMETA(DisplayName = "Backward Dash"),
	ENB_ForwardAirDash = 0x80 UMETA(DisplayName = "Forward Air Dash"),
	ENB_BackAirDash = 0x100 UMETA(DisplayName = "Backward Air Dash"),
	ENB_NormalAttack = 0x200 UMETA(DisplayName = "Normal Attack"),
	ENB_SpecialAttack = 0x400 UMETA(DisplayName = "Special Attack"),
	ENB_SuperAttack = 0x800 UMETA(DisplayName = "Super Attack"),
	ENB_Block = 0x1000 UMETA(DisplayName = "Block"),
	ENB_ProximityBlock = 0x2000 UMETA(DisplayName = "Proximity Block"),
	ENB_Tech = 0x4000 UMETA(DisplayName = "Tech"),
	ENB_Burst = 0x8000 UMETA(DisplayName = "Burst"),
	ENB_Tag = 0x10000 UMETA(DisplayName = "Tag"),
	ENB_Assist = 0x20000 UMETA(DisplayName = "Assist"),
};

ENUM_CLASS_FLAGS(EEnableFlags);

/**
 * Miscellaneous object flags.
 */
UENUM()
enum EMiscFlags
{
	/**
	 * Flag sets if inertia is enabled.
	 * @see ABattleObject.Inertia
	 */
	MISC_InertiaEnable = 0x1 UMETA(DisplayName = "Inertia Enabled"),
	/**
	 * Flag sets if object can switch sides.
	 */
	MISC_FlipEnable = 0x2 UMETA(DisplayName = "Flip Enabled"),
	/**
	 * Flag sets if object is subject to wall collision.
	 */
	MISC_WallCollisionActive = 0x4 UMETA(DisplayName = "Wall Collision Active"),
	/**
	 * Flag sets if object is subject to floor collision.
	 */
	MISC_FloorCollisionActive = 0x8 UMETA(DisplayName = "Floor Collision Active"),
	/**
	 * Flag sets if object is subject to push collision.
	 */
	MISC_PushCollisionActive = 0x10 UMETA(DisplayName = "Push Collision Active"),
	/**
	 * Flag sets if object is to be deactivated next update.
	 */
	MISC_DeactivateOnNextUpdate = 0x20 UMETA(DisplayName = "Deactivate On Next Update"),
	/**
	 * Flag sets if object is to be deactivated upon leaving screen bounds.
	 */
	MISC_DeactivateIfBeyondBounds = 0x40 UMETA(DisplayName = "Deactivate If Beyond Bounds"),
	/**
	 * Flag sets if object is to be deactivated on the owning player object's state change.
	 */
	MISC_DeactivateOnStateChange = 0x80 UMETA(DisplayName = "Deactivate On State Change"),
	/**
	* Flag sets if object is to be deactivated when the owning player object takes damage.
	 */
	MISC_DeactivateOnReceiveHit = 0x100 UMETA(DisplayName = "Deactivate On Receive Hit"),
	/**
	* Flag sets if object will ignore super freeze.
	 */
	MISC_IgnoreSuperFreeze = 0x200 UMETA(DisplayName = "Ignore Super Freeze"),
};

/**
 * Object attack flags.
 */
UENUM()
enum EAttackFlags
{
	/**
	 * Flag sets if object can hit.
	 */
	ATK_HitActive = 0x1 UMETA(DisplayName = "Hit Active"),
	/**
	 * Flag sets if object is attacking.
	 */
	ATK_IsAttacking = 0x2 UMETA(DisplayName = "Is Attacking"),
	/**
	 * Flag sets if object has the head attack attribute. Used on air attacks.
	 */
	ATK_AttackHeadAttribute = 0x4 UMETA(DisplayName = "Head Attribute"),
	/**
	 * Flag sets if object has the projectile attack attribute.
	 */
	ATK_AttackProjectileAttribute = 0x8 UMETA(DisplayName = "Projectile Attribute"),
	/**
	 * Flag sets if object has hit an object with the active hit.
	 */
	ATK_HasHit = 0x10 UMETA(DisplayName = "Has Hit"),
	/**
	 * Flag sets if object will only prorate once this state.
	 */
	ATK_ProrateOnce = 0x20 UMETA(DisplayName = "Prorate Once"),
	/**
	 * Flag sets if object will ignore OTG limits and proration.
	 */
	ATK_IgnoreOTG = 0x40 UMETA(DisplayName = "Ignore OTG"),
	/**
	 * Flag sets if object will ignore pushback scaling.
	 */
	ATK_IgnorePushbackScaling = 0x80 UMETA(DisplayName = "Ignore Pushback Scaling"),
	/**
	 * Flag sets if object will ignore hitstun scaling.
	 */
	ATK_IgnoreHitstunScaling = 0x100 UMETA(DisplayName = "Ignore Hitstun Scaling"),
};

/**
 * Miscellaneous player flags.
 */
UENUM()
enum EPlayerFlags
{
	/**
	 * Flag sets if player is dead.
	 */
	PLF_IsDead = 0x1 UMETA(DisplayName = "Is Dead"),
	/**
	 * Flag sets if player can throw opponent.
	 */
	PLF_ThrowActive = 0x2 UMETA(DisplayName = "Throw Active"),
	/**
	 * Flag sets if player is stunned.
	 */
	PLF_IsStunned = 0x4 UMETA(DisplayName = "Is Stunned"),
	/**
	 * Flag sets if player is locked by a throw.
	 */
	PLF_IsThrowLock = 0x8 UMETA(DisplayName = "Is In Throw Lock"),
	/**
	 * Flag sets if player is on screen (e.g. not tagged out in a versus game).
	 */
	PLF_IsOnScreen = 0x10 UMETA(DisplayName = "Is On Screen"),
	/**
	 * Flag sets if player manually overrides the death camera animation.
	 */
	PLF_DeathCamOverride = 0x20 UMETA(DisplayName = "Override Death Camera Animation"),
	/**
	 * Flag sets if player is knocked down.
	 */
	PLF_IsKnockedDown = 0x40 UMETA(DisplayName = "Is Knocked Down"),
	/**
	 * Flag sets if player is hard knocked down.
	 */
	PLF_IsHardKnockedDown = 0x80 UMETA(DisplayName = "Is Hard Knocked Down"),
	/**
	 * Flag sets if player is unable to input actions because the round is over.
	 */
	PLF_RoundWinInputLock = 0x100 UMETA(DisplayName = "Is Round Win Input Lock"),
	/**
	 * Flag sets if player's current attack locks the opponent's burst on hit.
	 */
	PLF_LockOpponentBurst = 0x200 UMETA(DisplayName = "Is Opponent Burst Locked"),
	/**
	 * Flag sets if player jumps to the JumpLanding state upon landing.
	 */
	PLF_DefaultLandingAction = 0x400 UMETA(DisplayName = "Is Default Landing Action"),
	/**
	 * Flag sets if player's far proximity normals are forcibly enabled.
	 */
	PLF_ForceEnableFarNormal = 0x800 UMETA(DisplayName = "Force Enable Far Proximity Normal"),
	/**
	 * Flag sets if player is touching wall.
	 */
	PLF_TouchingWall = 0x1000 UMETA(DisplayName = "Is Touching Wall"),
	/**
	 * Flag sets if player's next hit is a hitgrab.
	 */
	PLF_HitgrabActive = 0x2000 UMETA(DisplayName = "Hitgrab Active"),
};

/**
 * Player cancel flags.
 */
UENUM()
enum ECancelFlags
{
	/**
	 * Flag sets if chain cancel is enabled.
	 */
	CNC_ChainCancelEnabled = 0x1 UMETA(DisplayName = "Is Chain Cancel Enabled"),
	/**
	 * Flag sets if whiff cancel is enabled.
	 */
	CNC_WhiffCancelEnabled = 0x2 UMETA(DisplayName = "Is Whiff Cancel Enabled"),
	/**
	 * Flag sets if special cancel is enabled.
	 */
	CNC_SpecialCancel = 0x4 UMETA(DisplayName = "Is Special Cancel Enabled"),
	/**
	 * Flag sets if super cancel is enabled.
	 */
	CNC_SuperCancel = 0x8 UMETA(DisplayName = "Is Super Cancel Enabled"),
	/**
	 * Flag sets if jump cancel is enabled.
	 */
	CNC_JumpCancel = 0x10 UMETA(DisplayName = "Is Jump Cancel Enabled"),
	/**
	 * Flag sets if forward air dash cancel is enabled.
	 */
	CNC_FAirDashCancel = 0x20 UMETA(DisplayName = "Is Forward Air Dash Cancel Enabled"), 
	/**
	 * Flag sets if backward air dash cancel is enabled.
	 */
	CNC_BAirDashCancel = 0x40 UMETA(DisplayName = "Is Backward Air Dash Cancel Enabled"),
	/**
	 * Flag sets if kara cancel is enabled.
	 */
	CNC_EnableKaraCancel = 0x80 UMETA(DisplayName = "Is Kara Cancel Enabled"),
	/**
	 * Flag sets if cancelling into the player's current state is enabled.
	 */
	CNC_CancelIntoSelf = 0x100 UMETA(DisplayName = "Is Cancel Into Self Enabled"),
};

/**
 * Player invulnerability flags.
 */
UENUM()
enum EInvulnFlags
{
	/**
	 * Flag sets if player is strike invulnerable.
	 */
	INV_StrikeInvulnerable = 0x1 UMETA(DisplayName = "Is Strike Invulnerable"),
	/**
	 * Flag sets if player is throw invulnerable.
	 */
	INV_ThrowInvulnerable = 0x2 UMETA(DisplayName = "Is Throw Invulnerable"),
	/**
	 * Flag sets if player is projectile invulnerable.
	 */
	INV_ProjectileInvulnerable = 0x4 UMETA(DisplayName = "Is Projectile Invulnerable"),
	/**
	 * Flag sets if player is invulnerable to head attribute attacks.
	 */
	INV_HeadInvulnerable = 0x8 UMETA(DisplayName = "Is Head Invulnerable"),
};