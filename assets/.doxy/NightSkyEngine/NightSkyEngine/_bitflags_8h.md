

# File Bitflags.h



[**FileList**](files.md) **>** [**Battle**](dir_59b3558fc0091a3111c9e7dd8d94b2ea.md) **>** [**Misc**](dir_4fd921e402b7a240656c31e280e3875c.md) **>** [**Bitflags.h**](_bitflags_8h.md)

[Go to the source code of this file](_bitflags_8h_source.md)



* `#include "CoreMinimal.h"`

















## Public Types

| Type | Name |
| ---: | :--- |
| enum  | [**EAttackFlags**](#enum-eattackflags)  <br> |
| enum  | [**ECancelFlags**](#enum-ecancelflags)  <br> |
| enum  | [**EEnableFlags**](#enum-eenableflags)  <br> |
| enum  | [**EInputFlags**](#enum-einputflags)  <br> |
| enum  | [**EInvulnFlags**](#enum-einvulnflags)  <br> |
| enum  | [**EMiscFlags**](#enum-emiscflags)  <br> |
| enum  | [**EPlayerFlags**](#enum-eplayerflags)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**ENUM\_CLASS\_FLAGS**](#function-enum_class_flags) (EInputFlags) <br> |
|   | [**ENUM\_CLASS\_FLAGS**](#function-enum_class_flags) (EEnableFlags) <br> |




























## Public Types Documentation




### enum EAttackFlags 

```C++
enum EAttackFlags {
    ATK_HitActive = 0x1 UMETA(DisplayName = "Hit Active"),
    ATK_IsAttacking = 0x2 UMETA(DisplayName = "Is Attacking"),
    ATK_AttackHeadAttribute = 0x4 UMETA(DisplayName = "Head Attribute"),
    ATK_AttackProjectileAttribute = 0x8 UMETA(DisplayName = "Projectile Attribute"),
    ATK_HasHit = 0x10 UMETA(DisplayName = "Has Hit"),
    ATK_ProrateOnce = 0x20 UMETA(DisplayName = "Prorate Once"),
    ATK_IgnoreOTG = 0x40 UMETA(DisplayName = "Ignore OTG"),
    ATK_IgnorePushbackScaling = 0x80 UMETA(DisplayName = "Ignore Pushback Scaling"),
    ATK_IgnoreHitstunScaling = 0x100 UMETA(DisplayName = "Ignore Hitstun Scaling"),
    ATK_SetPlayerHit = 0x200 UMETA(DisplayName = "Ignore Hitstun Scaling"),
    ATK_HitOTG = 0x400 UMETA(DisplayName = "Hit OTG")
};
```



Object attack flags. 


        

<hr>



### enum ECancelFlags 

```C++
enum ECancelFlags {
    CNC_ChainCancelEnabled = 0x1 UMETA(DisplayName = "Is Chain Cancel Enabled"),
    CNC_WhiffCancelEnabled = 0x2 UMETA(DisplayName = "Is Whiff Cancel Enabled"),
    CNC_SpecialCancel = 0x4 UMETA(DisplayName = "Is Special Cancel Enabled"),
    CNC_SuperCancel = 0x8 UMETA(DisplayName = "Is Super Cancel Enabled"),
    CNC_JumpCancel = 0x10 UMETA(DisplayName = "Is Jump Cancel Enabled"),
    CNC_FAirDashCancel = 0x20 UMETA(DisplayName = "Is Forward Air Dash Cancel Enabled"),
    CNC_BAirDashCancel = 0x40 UMETA(DisplayName = "Is Backward Air Dash Cancel Enabled"),
    CNC_EnableKaraCancel = 0x80 UMETA(DisplayName = "Is Kara Cancel Enabled"),
    CNC_CancelIntoSelf = 0x100 UMETA(DisplayName = "Is Cancel Into Self Enabled"),
    CNC_EnableReverseBeat = 0x200 UMETA(DisplayName = "Is Reverse Beat Enabled")
};
```



Player cancel flags. 


        

<hr>



### enum EEnableFlags 

```C++
enum EEnableFlags {
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
    ENB_Assist = 0x20000 UMETA(DisplayName = "Assist")
};
```



Flags used to enable or disable specific states or actions. 


        

<hr>



### enum EInputFlags 

```C++
enum EInputFlags {
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
    INP_ResetTraining = 0x40000000 UMETA(Hidden),
    INP_Rematch = 0x80000000 UMETA(Hidden)
};
```



Input bitmasks. A layer of abstraction between the physical controller and the internal battle state. 


        

<hr>



### enum EInvulnFlags 

```C++
enum EInvulnFlags {
    INV_StrikeInvulnerable = 0x1 UMETA(DisplayName = "Is Strike Invulnerable"),
    INV_ThrowInvulnerable = 0x2 UMETA(DisplayName = "Is Throw Invulnerable"),
    INV_ProjectileInvulnerable = 0x4 UMETA(DisplayName = "Is Projectile Invulnerable"),
    INV_HeadInvulnerable = 0x8 UMETA(DisplayName = "Is Head Invulnerable")
};
```



Player invulnerability flags. 


        

<hr>



### enum EMiscFlags 

```C++
enum EMiscFlags {
    MISC_InertiaEnable = 0x1 UMETA(DisplayName = "Inertia Enabled"),
    MISC_FlipEnable = 0x2 UMETA(DisplayName = "Flip Enabled"),
    MISC_WallCollisionActive = 0x4 UMETA(DisplayName = "Wall Collision Active"),
    MISC_FloorCollisionActive = 0x8 UMETA(DisplayName = "Floor Collision Active"),
    MISC_PushCollisionActive = 0x10 UMETA(DisplayName = "Push Collision Active"),
    MISC_DeactivateOnNextUpdate = 0x20 UMETA(DisplayName = "Deactivate On Next Update"),
    MISC_DeactivateIfBeyondBounds = 0x40 UMETA(DisplayName = "Deactivate If Beyond Bounds"),
    MISC_DeactivateOnStateChange = 0x80 UMETA(DisplayName = "Deactivate On State Change"),
    MISC_DeactivateOnReceiveHit = 0x100 UMETA(DisplayName = "Deactivate On Receive Hit"),
    MISC_IgnoreSuperFreeze = 0x200 UMETA(DisplayName = "Ignore Super Freeze")
};
```



Miscellaneous object flags. 


        

<hr>



### enum EPlayerFlags 

```C++
enum EPlayerFlags {
    PLF_IsDead = 0x1 UMETA(DisplayName = "Is Dead"),
    PLF_ThrowActive = 0x2 UMETA(DisplayName = "Throw Active"),
    PLF_IsStunned = 0x4 UMETA(DisplayName = "Is Stunned"),
    PLF_IsThrowLock = 0x8 UMETA(DisplayName = "Is In Throw Lock"),
    PLF_IsOnScreen = 0x10 UMETA(DisplayName = "Is On Screen"),
    PLF_DeathCamOverride = 0x20 UMETA(DisplayName = "Override Death Camera Animation"),
    PLF_IsKnockedDown = 0x40 UMETA(DisplayName = "Is Knocked Down"),
    PLF_IsHardKnockedDown = 0x80 UMETA(DisplayName = "Is Hard Knocked Down"),
    PLF_RoundWinInputLock = 0x100 UMETA(DisplayName = "Is Round Win Input Lock"),
    PLF_LockOpponentBurst = 0x200 UMETA(DisplayName = "Is Opponent Burst Locked"),
    PLF_DefaultLandingAction = 0x400 UMETA(DisplayName = "Is Default Landing Action"),
    PLF_ForceEnableFarNormal = 0x800 UMETA(DisplayName = "Force Enable Far Proximity Normal"),
    PLF_TouchingWall = 0x1000 UMETA(DisplayName = "Is Touching Wall"),
    PLF_HitgrabActive = 0x2000 UMETA(DisplayName = "Hitgrab Active"),
    PLF_ReceivedCounterHit = 0x4000 UMETA(DisplayName = "Received Counter Hit"),
    PLF_DidKaraCancel = 0x8000 UMETA(DisplayName = "Did Kara Cancel")
};
```



Miscellaneous player flags. 


        

<hr>
## Public Functions Documentation




### function ENUM\_CLASS\_FLAGS 

```C++
ENUM_CLASS_FLAGS (
    EInputFlags
) 
```




<hr>



### function ENUM\_CLASS\_FLAGS 

```C++
ENUM_CLASS_FLAGS (
    EEnableFlags
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/NightSkyEngine/Battle/Misc/Bitflags.h`

