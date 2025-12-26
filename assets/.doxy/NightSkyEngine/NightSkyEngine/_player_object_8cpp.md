

# File PlayerObject.cpp



[**FileList**](files.md) **>** [**Battle**](dir_59b3558fc0091a3111c9e7dd8d94b2ea.md) **>** [**Objects**](dir_e62046f165ace41a1907d5ab434ac45b.md) **>** [**PlayerObject.cpp**](_player_object_8cpp.md)

[Go to the source code of this file](_player_object_8cpp_source.md)



* `#include "PlayerObject.h"`
* `#include "NightSkyEngine/Battle/NightSkyGameState.h"`
* `#include "NightSkyEngine/Battle/Actors/LinkActor.h"`
* `#include "NightSkyEngine/Battle/Script/Subroutine.h"`
* `#include "NightSkyEngine/Data/LinkActorData.h"`
* `#include "NightSkyEngine/Data/ParticleData.h"`
* `#include "NightSkyEngine/Data/SubroutineData.h"`
* `#include "NightSkyEngine/Miscellaneous/NightSkyGameInstance.h"`
* `#include "Serialization/ObjectReader.h"`
* `#include "Serialization/ObjectWriter.h"`





































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**UE\_DEFINE\_GAMEPLAY\_TAG\_COMMENT**](#function-ue_define_gameplay_tag_comment) (State\_Label\_Blowback\_1, "State.Label.Blowback.1", "Blowback Label 1") <br> |
|   | [**UE\_DEFINE\_GAMEPLAY\_TAG\_COMMENT**](#function-ue_define_gameplay_tag_comment) (State\_Label\_Blowback\_2, "State.Label.Blowback.2", "Blowback Label 2") <br> |
|   | [**UE\_DEFINE\_GAMEPLAY\_TAG\_COMMENT**](#function-ue_define_gameplay_tag_comment) (State\_Label\_Blowback\_3, "State.Label.Blowback.3", "Blowback Label 3") <br> |
|   | [**UE\_DEFINE\_GAMEPLAY\_TAG\_COMMENT**](#function-ue_define_gameplay_tag_comment) (State\_Label\_Blowback\_4, "State.Label.Blowback.4", "Blowback Label 4") <br> |
|   | [**UE\_DEFINE\_GAMEPLAY\_TAG\_COMMENT**](#function-ue_define_gameplay_tag_comment) (State\_Label\_Block\_PreGuard, "State.Label.Block.PreGuard", "Block Label Pre Guard") <br> |
|   | [**UE\_DEFINE\_GAMEPLAY\_TAG\_COMMENT**](#function-ue_define_gameplay_tag_comment) (State\_Label\_Block\_Level1, "State.Label.Block.Level1", "Block Label Level 1") <br> |
|   | [**UE\_DEFINE\_GAMEPLAY\_TAG\_COMMENT**](#function-ue_define_gameplay_tag_comment) (State\_Label\_Block\_Level2, "State.Label.Block.Level2", "Block Label Level 2") <br> |
|   | [**UE\_DEFINE\_GAMEPLAY\_TAG\_COMMENT**](#function-ue_define_gameplay_tag_comment) (State\_Label\_Block\_Level3, "State.Label.Block.Level3", "Block Label Level 3") <br> |
|   | [**UE\_DEFINE\_GAMEPLAY\_TAG\_COMMENT**](#function-ue_define_gameplay_tag_comment) (Subroutine\_Cmn\_IsCorrectBlock, "Subroutine.Cmn.IsCorrectBlock", "Common Is Correct Block") <br> |
|   | [**UE\_DEFINE\_GAMEPLAY\_TAG\_COMMENT**](#function-ue_define_gameplay_tag_comment) (Subroutine\_Cmn\_HitCollision, "Subroutine.Cmn.HitCollision", "Common Hit Collision") <br> |
|   | [**UE\_DEFINE\_GAMEPLAY\_TAG\_COMMENT**](#function-ue_define_gameplay_tag_comment) (Subroutine\_Cmn\_OnBlock, "Subroutine.Cmn.OnBlock", "Common On Block") <br> |
|   | [**UE\_DEFINE\_GAMEPLAY\_TAG\_COMMENT**](#function-ue_define_gameplay_tag_comment) (Subroutine\_Cmn\_OnHit, "Subroutine.Cmn.OnHit", "Common On Hit") <br> |
|   | [**UE\_DEFINE\_GAMEPLAY\_TAG\_COMMENT**](#function-ue_define_gameplay_tag_comment) (Subroutine\_Cmn\_OnCounterHit, "Subroutine.Cmn.OnCounterHit", "Common On Counter Hit") <br> |




























## Public Functions Documentation




### function UE\_DEFINE\_GAMEPLAY\_TAG\_COMMENT 

```C++
UE_DEFINE_GAMEPLAY_TAG_COMMENT (
    State_Label_Blowback_1,
    "State.Label.Blowback.1",
    "Blowback Label 1"
) 
```




<hr>



### function UE\_DEFINE\_GAMEPLAY\_TAG\_COMMENT 

```C++
UE_DEFINE_GAMEPLAY_TAG_COMMENT (
    State_Label_Blowback_2,
    "State.Label.Blowback.2",
    "Blowback Label 2"
) 
```




<hr>



### function UE\_DEFINE\_GAMEPLAY\_TAG\_COMMENT 

```C++
UE_DEFINE_GAMEPLAY_TAG_COMMENT (
    State_Label_Blowback_3,
    "State.Label.Blowback.3",
    "Blowback Label 3"
) 
```




<hr>



### function UE\_DEFINE\_GAMEPLAY\_TAG\_COMMENT 

```C++
UE_DEFINE_GAMEPLAY_TAG_COMMENT (
    State_Label_Blowback_4,
    "State.Label.Blowback.4",
    "Blowback Label 4"
) 
```




<hr>



### function UE\_DEFINE\_GAMEPLAY\_TAG\_COMMENT 

```C++
UE_DEFINE_GAMEPLAY_TAG_COMMENT (
    State_Label_Block_PreGuard,
    "State.Label.Block.PreGuard",
    "Block Label Pre Guard"
) 
```




<hr>



### function UE\_DEFINE\_GAMEPLAY\_TAG\_COMMENT 

```C++
UE_DEFINE_GAMEPLAY_TAG_COMMENT (
    State_Label_Block_Level1,
    "State.Label.Block.Level1",
    "Block Label Level 1"
) 
```




<hr>



### function UE\_DEFINE\_GAMEPLAY\_TAG\_COMMENT 

```C++
UE_DEFINE_GAMEPLAY_TAG_COMMENT (
    State_Label_Block_Level2,
    "State.Label.Block.Level2",
    "Block Label Level 2"
) 
```




<hr>



### function UE\_DEFINE\_GAMEPLAY\_TAG\_COMMENT 

```C++
UE_DEFINE_GAMEPLAY_TAG_COMMENT (
    State_Label_Block_Level3,
    "State.Label.Block.Level3",
    "Block Label Level 3"
) 
```




<hr>



### function UE\_DEFINE\_GAMEPLAY\_TAG\_COMMENT 

```C++
UE_DEFINE_GAMEPLAY_TAG_COMMENT (
    Subroutine_Cmn_IsCorrectBlock,
    "Subroutine.Cmn.IsCorrectBlock",
    "Common Is Correct Block"
) 
```




<hr>



### function UE\_DEFINE\_GAMEPLAY\_TAG\_COMMENT 

```C++
UE_DEFINE_GAMEPLAY_TAG_COMMENT (
    Subroutine_Cmn_HitCollision,
    "Subroutine.Cmn.HitCollision",
    "Common Hit Collision"
) 
```




<hr>



### function UE\_DEFINE\_GAMEPLAY\_TAG\_COMMENT 

```C++
UE_DEFINE_GAMEPLAY_TAG_COMMENT (
    Subroutine_Cmn_OnBlock,
    "Subroutine.Cmn.OnBlock",
    "Common On Block"
) 
```




<hr>



### function UE\_DEFINE\_GAMEPLAY\_TAG\_COMMENT 

```C++
UE_DEFINE_GAMEPLAY_TAG_COMMENT (
    Subroutine_Cmn_OnHit,
    "Subroutine.Cmn.OnHit",
    "Common On Hit"
) 
```




<hr>



### function UE\_DEFINE\_GAMEPLAY\_TAG\_COMMENT 

```C++
UE_DEFINE_GAMEPLAY_TAG_COMMENT (
    Subroutine_Cmn_OnCounterHit,
    "Subroutine.Cmn.OnCounterHit",
    "Common On Counter Hit"
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/NightSkyEngine/Battle/Objects/PlayerObject.cpp`

