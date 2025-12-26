

# File PlayerObject.h



[**FileList**](files.md) **>** [**Battle**](dir_59b3558fc0091a3111c9e7dd8d94b2ea.md) **>** [**Objects**](dir_e62046f165ace41a1907d5ab434ac45b.md) **>** [**PlayerObject.h**](_player_object_8h.md)

[Go to the source code of this file](_player_object_8h_source.md)



* `#include "CoreMinimal.h"`
* `#include "BattleObject.h"`
* `#include "NativeGameplayTags.h"`
* `#include "NightSkyEngine/Battle/Misc/InputBuffer.h"`
* `#include "NightSkyEngine/Battle/Script/State.h"`
* `#include "NightSkyEngine/Battle/Script/StateMachine.h"`
* `#include "NightSkyEngine/Data/CollisionData.h"`
* `#include "NightSkyEngine/Data/SequenceData.h"`
* `#include "NightSkyEngine/Data/SoundData.h"`
* `#include "NightSkyEngine/Data/StateData.h"`
* `#include "PlayerObject.generated.h"`















## Classes

| Type | Name |
| ---: | :--- |
| class | [**APlayerObject**](class_a_player_object.md) <br> |
| struct | [**FExtraGauge**](struct_f_extra_gauge.md) <br> |
| struct | [**FPlayerObjectLog**](struct_f_player_object_log.md) <br> |


## Public Types

| Type | Name |
| ---: | :--- |
| enum  | [**EActionStance**](#enum-eactionstance)  <br> |




## Public Attributes

| Type | Name |
| ---: | :--- |
|  int32 | [**MaxComponentCount**](#variable-maxcomponentcount)   = `64`<br> |
|  size\_t | [**SizeOfPlayerObject**](#variable-sizeofplayerobject)   = `offsetof([**APlayerObject**](class_a_player_object.md), PlayerSyncEnd) - offsetof([**APlayerObject**](class_a_player_object.md), PlayerSync)`<br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**UE\_DECLARE\_GAMEPLAY\_TAG\_EXTERN**](#function-ue_declare_gameplay_tag_extern) (State\_Label\_Blowback\_1) <br> |
|   | [**UE\_DECLARE\_GAMEPLAY\_TAG\_EXTERN**](#function-ue_declare_gameplay_tag_extern) (State\_Label\_Blowback\_2) <br> |
|   | [**UE\_DECLARE\_GAMEPLAY\_TAG\_EXTERN**](#function-ue_declare_gameplay_tag_extern) (State\_Label\_Blowback\_3) <br> |
|   | [**UE\_DECLARE\_GAMEPLAY\_TAG\_EXTERN**](#function-ue_declare_gameplay_tag_extern) (State\_Label\_Blowback\_4) <br> |
|   | [**UE\_DECLARE\_GAMEPLAY\_TAG\_EXTERN**](#function-ue_declare_gameplay_tag_extern) (State\_Label\_Block\_PreGuard) <br> |
|   | [**UE\_DECLARE\_GAMEPLAY\_TAG\_EXTERN**](#function-ue_declare_gameplay_tag_extern) (State\_Label\_Block\_Level1) <br> |
|   | [**UE\_DECLARE\_GAMEPLAY\_TAG\_EXTERN**](#function-ue_declare_gameplay_tag_extern) (State\_Label\_Block\_Level2) <br> |
|   | [**UE\_DECLARE\_GAMEPLAY\_TAG\_EXTERN**](#function-ue_declare_gameplay_tag_extern) (State\_Label\_Block\_Level3) <br> |
|   | [**UE\_DECLARE\_GAMEPLAY\_TAG\_EXTERN**](#function-ue_declare_gameplay_tag_extern) (Subroutine\_Cmn\_IsCorrectBlock) <br> |
|   | [**UE\_DECLARE\_GAMEPLAY\_TAG\_EXTERN**](#function-ue_declare_gameplay_tag_extern) (Subroutine\_Cmn\_HitCollision) <br> |
|   | [**UE\_DECLARE\_GAMEPLAY\_TAG\_EXTERN**](#function-ue_declare_gameplay_tag_extern) (Subroutine\_Cmn\_OnBlock) <br> |
|   | [**UE\_DECLARE\_GAMEPLAY\_TAG\_EXTERN**](#function-ue_declare_gameplay_tag_extern) (Subroutine\_Cmn\_OnHit) <br> |
|   | [**UE\_DECLARE\_GAMEPLAY\_TAG\_EXTERN**](#function-ue_declare_gameplay_tag_extern) (Subroutine\_Cmn\_OnCounterHit) <br> |




























## Public Types Documentation




### enum EActionStance 

```C++
enum EActionStance {
    ACT_Standing,
    ACT_Crouching,
    ACT_Jumping
};
```




<hr>
## Public Attributes Documentation




### variable MaxComponentCount 

```C++
int32 MaxComponentCount;
```




<hr>



### variable SizeOfPlayerObject 

```C++
size_t SizeOfPlayerObject;
```




<hr>
## Public Functions Documentation




### function UE\_DECLARE\_GAMEPLAY\_TAG\_EXTERN 

```C++
UE_DECLARE_GAMEPLAY_TAG_EXTERN (
    State_Label_Blowback_1
) 
```




<hr>



### function UE\_DECLARE\_GAMEPLAY\_TAG\_EXTERN 

```C++
UE_DECLARE_GAMEPLAY_TAG_EXTERN (
    State_Label_Blowback_2
) 
```




<hr>



### function UE\_DECLARE\_GAMEPLAY\_TAG\_EXTERN 

```C++
UE_DECLARE_GAMEPLAY_TAG_EXTERN (
    State_Label_Blowback_3
) 
```




<hr>



### function UE\_DECLARE\_GAMEPLAY\_TAG\_EXTERN 

```C++
UE_DECLARE_GAMEPLAY_TAG_EXTERN (
    State_Label_Blowback_4
) 
```




<hr>



### function UE\_DECLARE\_GAMEPLAY\_TAG\_EXTERN 

```C++
UE_DECLARE_GAMEPLAY_TAG_EXTERN (
    State_Label_Block_PreGuard
) 
```




<hr>



### function UE\_DECLARE\_GAMEPLAY\_TAG\_EXTERN 

```C++
UE_DECLARE_GAMEPLAY_TAG_EXTERN (
    State_Label_Block_Level1
) 
```




<hr>



### function UE\_DECLARE\_GAMEPLAY\_TAG\_EXTERN 

```C++
UE_DECLARE_GAMEPLAY_TAG_EXTERN (
    State_Label_Block_Level2
) 
```




<hr>



### function UE\_DECLARE\_GAMEPLAY\_TAG\_EXTERN 

```C++
UE_DECLARE_GAMEPLAY_TAG_EXTERN (
    State_Label_Block_Level3
) 
```




<hr>



### function UE\_DECLARE\_GAMEPLAY\_TAG\_EXTERN 

```C++
UE_DECLARE_GAMEPLAY_TAG_EXTERN (
    Subroutine_Cmn_IsCorrectBlock
) 
```




<hr>



### function UE\_DECLARE\_GAMEPLAY\_TAG\_EXTERN 

```C++
UE_DECLARE_GAMEPLAY_TAG_EXTERN (
    Subroutine_Cmn_HitCollision
) 
```




<hr>



### function UE\_DECLARE\_GAMEPLAY\_TAG\_EXTERN 

```C++
UE_DECLARE_GAMEPLAY_TAG_EXTERN (
    Subroutine_Cmn_OnBlock
) 
```




<hr>



### function UE\_DECLARE\_GAMEPLAY\_TAG\_EXTERN 

```C++
UE_DECLARE_GAMEPLAY_TAG_EXTERN (
    Subroutine_Cmn_OnHit
) 
```




<hr>



### function UE\_DECLARE\_GAMEPLAY\_TAG\_EXTERN 

```C++
UE_DECLARE_GAMEPLAY_TAG_EXTERN (
    Subroutine_Cmn_OnCounterHit
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/NightSkyEngine/Battle/Objects/PlayerObject.h`

