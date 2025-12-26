

# File BattleObject.cpp



[**FileList**](files.md) **>** [**Battle**](dir_59b3558fc0091a3111c9e7dd8d94b2ea.md) **>** [**Objects**](dir_e62046f165ace41a1907d5ab434ac45b.md) **>** [**BattleObject.cpp**](_battle_object_8cpp.md)

[Go to the source code of this file](_battle_object_8cpp_source.md)



* `#include "BattleObject.h"`
* `#include "NiagaraComponent.h"`
* `#include "NiagaraFunctionLibrary.h"`
* `#include "NightSkyEngine/Battle/Misc/NightSkyBlueprintFunctionLibrary.h"`
* `#include "NightSkyEngine/Battle/NightSkyGameState.h"`
* `#include "NightSkyEngine/Battle/Actors/ParticleManager.h"`
* `#include "PlayerObject.h"`
* `#include "NightSkyEngine/Battle/Actors/LinkActor.h"`
* `#include "NightSkyEngine/Battle/Animation/NightSkyAnimMetaData.h"`
* `#include "NightSkyEngine/Battle/Animation/NightSkyAnimSequenceUserData.h"`
* `#include "NightSkyEngine/Battle/Misc/Bitflags.h"`
* `#include "NightSkyEngine/Battle/Misc/Globals.h"`
* `#include "NightSkyEngine/Battle/Script/Subroutine.h"`
* `#include "NightSkyEngine/Data/CameraShakeData.h"`
* `#include "NightSkyEngine/Data/ParticleData.h"`
* `#include "NightSkyEngine/Battle/Misc/RandomManager.h"`





































## Public Functions

| Type | Name |
| ---: | :--- |
|  bool | [**line\_box\_intersection**](#function-line_box_intersection) (const FVector2D & box\_min, const FVector2D & box\_max, const FVector2D & line\_a, const FVector2D & line\_b, float \* entry\_fraction, float \* exit\_fraction) <br> |
|  auto | [**max**](#function-max) (T a, T b) <br> |
|  auto | [**min**](#function-min) (T a, T b) <br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  void | [**clip\_line\_y**](#function-clip_line_y) (const FVector2D & line\_a, const FVector2D & line\_b, float min\_x, float max\_x, float \* min\_y, float \* max\_y) <br> |


























## Public Functions Documentation




### function line\_box\_intersection 

```C++
bool line_box_intersection (
    const FVector2D & box_min,
    const FVector2D & box_max,
    const FVector2D & line_a,
    const FVector2D & line_b,
    float * entry_fraction,
    float * exit_fraction
) 
```




<hr>



### function max 

```C++
template<typename T>
auto max (
    T a,
    T b
) 
```




<hr>



### function min 

```C++
template<typename T>
auto min (
    T a,
    T b
) 
```




<hr>
## Public Static Functions Documentation




### function clip\_line\_y 

```C++
static void clip_line_y (
    const FVector2D & line_a,
    const FVector2D & line_b,
    float min_x,
    float max_x,
    float * min_y,
    float * max_y
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/NightSkyEngine/Battle/Objects/BattleObject.cpp`

