

# File BattleObject.h



[**FileList**](files.md) **>** [**Battle**](dir_59b3558fc0091a3111c9e7dd8d94b2ea.md) **>** [**Objects**](dir_e62046f165ace41a1907d5ab434ac45b.md) **>** [**BattleObject.h**](_battle_object_8h.md)

[Go to the source code of this file](_battle_object_8h_source.md)



* `#include <fstream>`
* `#include "CoreMinimal.h"`
* `#include "GameplayTagContainer.h"`
* `#include "GameFramework/Pawn.h"`
* `#include "NightSkyEngine/Battle/Misc/CollisionBox.h"`
* `#include "NightSkyEngine/Data/CollisionData.h"`
* `#include "BattleObject.generated.h"`















## Classes

| Type | Name |
| ---: | :--- |
| class | [**ABattleObject**](class_a_battle_object.md) <br> |
| struct | [**FBattleObjectLog**](struct_f_battle_object_log.md) <br> |
| struct | [**FEventHandler**](struct_f_event_handler.md) <br> |
| struct | [**FGroundBounceData**](struct_f_ground_bounce_data.md) <br> |
| struct | [**FHitData**](struct_f_hit_data.md) <br> |
| struct | [**FHitDataCommon**](struct_f_hit_data_common.md) <br> |
| struct | [**FHitPosition**](struct_f_hit_position.md) <br> |
| struct | [**FHitValueOverTime**](struct_f_hit_value_over_time.md) <br> |
| struct | [**FHomingParams**](struct_f_homing_params.md) <br> |
| struct | [**FLinkedActorContainer**](struct_f_linked_actor_container.md) <br> |
| struct | [**FSuperArmorData**](struct_f_super_armor_data.md) <br> |
| struct | [**FWallBounceData**](struct_f_wall_bounce_data.md) <br> |


## Public Types

| Type | Name |
| ---: | :--- |
| enum  | [**EBlockType**](#enum-eblocktype)  <br> |
| enum  | [**EDistanceType**](#enum-edistancetype)  <br> |
| enum  | [**EEventType**](#enum-eeventtype)  <br> |
| enum  | [**EFloatingCrumpleType**](#enum-efloatingcrumpletype)  <br> |
| enum  | [**EHitAction**](#enum-ehitaction)  <br> |
| enum  | [**EHitPositionType**](#enum-ehitpositiontype)  <br> |
| enum uint8 | [**EHitSFXType**](#enum-ehitsfxtype)  <br> |
| enum uint8 | [**EHitVFXType**](#enum-ehitvfxtype)  <br> |
| enum  | [**EHomingType**](#enum-ehomingtype)  <br> |
| enum  | [**EObjDir**](#enum-eobjdir)  <br> |
| enum  | [**EObjType**](#enum-eobjtype)  <br> |
| enum  | [**EPosType**](#enum-epostype)  <br> |
| enum  | [**ESuperArmorType**](#enum-esuperarmortype)  <br> |




## Public Attributes

| Type | Name |
| ---: | :--- |
|  int32 | [**MaxDrawPriority**](#variable-maxdrawpriority)   = `4`<br> |
|  size\_t | [**SizeOfBattleObject**](#variable-sizeofbattleobject)   = `offsetof([**ABattleObject**](class_a_battle_object.md), ObjSyncEnd) - offsetof([**ABattleObject**](class_a_battle_object.md), ObjSync)`<br> |












































## Public Types Documentation




### enum EBlockType 

```C++
enum EBlockType {
    UMETA =(DisplayName="Update"),
    UMETA =(DisplayName="Update"),
    UMETA =(DisplayName="Update"),
    UMETA =(DisplayName="Update")
};
```




<hr>



### enum EDistanceType 

```C++
enum EDistanceType {
    DIST_Distance,
    DIST_DistanceX,
    DIST_DistanceY,
    DIST_FrontDistanceX
};
```




<hr>



### enum EEventType 

```C++
enum EEventType {
    UMETA =(DisplayName="Update"),
    UMETA =(DisplayName="Update"),
    UMETA =(DisplayName="Update"),
    UMETA =(DisplayName="Update"),
    UMETA =(DisplayName="Update"),
    UMETA =(DisplayName="Update"),
    UMETA =(DisplayName="Update"),
    UMETA =(DisplayName="Update"),
    UMETA =(DisplayName="Update"),
    UMETA =(DisplayName="Update"),
    UMETA =(DisplayName="Update"),
    UMETA =(DisplayName="Update"),
    UMETA =(DisplayName="Update"),
    UMETA =(DisplayName="Update"),
    UMETA =(DisplayName="Update"),
    UMETA =(DisplayName="Update"),
    UMETA =(DisplayName="Update"),
    UMETA =(DisplayName="Update"),
    UMETA =(DisplayName="Update"),
    UMETA =(DisplayName="Update")
};
```




<hr>



### enum EFloatingCrumpleType 

```C++
enum EFloatingCrumpleType {
    UMETA =(DisplayName="Update"),
    UMETA =(DisplayName="Update"),
    UMETA =(DisplayName="Update")
};
```




<hr>



### enum EHitAction 

```C++
enum EHitAction {
    UMETA =(DisplayName="Update"),
    UMETA =(DisplayName="Update"),
    UMETA =(DisplayName="Update"),
    UMETA =(DisplayName="Update"),
    UMETA =(DisplayName="Update"),
    UMETA =(DisplayName="Update"),
    UMETA =(DisplayName="Update"),
    UMETA =(DisplayName="Update"),
    UMETA =(DisplayName="Update"),
    UMETA =(DisplayName="Update"),
    UMETA =(DisplayName="Update"),
    UMETA =(DisplayName="Update"),
    UMETA =(DisplayName="Update"),
    UMETA =(DisplayName="Update"),
    UMETA =(DisplayName="Update"),
    UMETA =(DisplayName="Update"),
    UMETA =(DisplayName="Update"),
    UMETA =(DisplayName="Update")
};
```




<hr>



### enum EHitPositionType 

```C++
enum EHitPositionType {
    UMETA =(DisplayName="Update"),
    HPT_Rel,
    HPT_Abs,
    UMETA =(DisplayName="Update"),
    HPT_RelNextFrame,
    HPT_AbsNextFrame,
    UMETA =(DisplayName="Update")
};
```




<hr>



### enum EHitSFXType 

```C++
enum EHitSFXType {
    UMETA =(DisplayName="Punch"),
    UMETA =(DisplayName="Kick"),
    UMETA =(DisplayName="Slash")
};
```




<hr>



### enum EHitVFXType 

```C++
enum EHitVFXType {
    UMETA =(DisplayName="Strike"),
    UMETA =(DisplayName="Slash"),
    UMETA =(DisplayName="Special")
};
```




<hr>



### enum EHomingType 

```C++
enum EHomingType {
    HOMING_DistanceAccel,
    HOMING_FixAccel,
    HOMING_ToSpeed
};
```




<hr>



### enum EObjDir 

```C++
enum EObjDir {
    DIR_Right,
    DIR_Left
};
```




<hr>



### enum EObjType 

```C++
enum EObjType {
    OBJ_Self,
    OBJ_MainPlayer,
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
    OBJ_Null
};
```




<hr>



### enum EPosType 

```C++
enum EPosType {
    POS_Player,
    POS_Self,
    POS_Center,
    POS_Ground,
    POS_Enemy,
    POS_Col
};
```




<hr>



### enum ESuperArmorType 

```C++
enum ESuperArmorType {
    ARM_None,
    ARM_Guard,
    ARM_Dodge
};
```




<hr>
## Public Attributes Documentation




### variable MaxDrawPriority 

```C++
int32 MaxDrawPriority;
```




<hr>



### variable SizeOfBattleObject 

```C++
size_t SizeOfBattleObject;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/NightSkyEngine/Battle/Objects/BattleObject.h`

