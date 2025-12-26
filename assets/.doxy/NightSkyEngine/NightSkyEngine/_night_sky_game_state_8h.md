

# File NightSkyGameState.h



[**FileList**](files.md) **>** [**Battle**](dir_59b3558fc0091a3111c9e7dd8d94b2ea.md) **>** [**NightSkyGameState.h**](_night_sky_game_state_8h.md)

[Go to the source code of this file](_night_sky_game_state_8h_source.md)



* `#include "CoreMinimal.h"`
* `#include "Actors/AudioManager.h"`
* `#include "Objects/PlayerObject.h"`
* `#include "GameFramework/GameStateBase.h"`
* `#include "include/ggponet.h"`
* `#include "Misc/RandomManager.h"`
* `#include "NightSkyGameState.generated.h"`















## Classes

| Type | Name |
| ---: | :--- |
| class | [**ANightSkyGameState**](class_a_night_sky_game_state.md) <br> |
| struct | [**FAudioChannel**](struct_f_audio_channel.md) <br> |
| struct | [**FBattleState**](struct_f_battle_state.md) <br> |
| struct | [**FNetworkStats**](struct_f_network_stats.md) <br> |
| struct | [**FRollbackData**](struct_f_rollback_data.md) <br> |
| struct | [**FScreenData**](struct_f_screen_data.md) <br> |
| struct | [**FTeamData**](struct_f_team_data.md) <br> |


## Public Types

| Type | Name |
| ---: | :--- |
| enum uint8 | [**EBattleFormat**](#enum-ebattleformat)  <br> |
| enum  | [**EBattlePhase**](#enum-ebattlephase)  <br> |
| enum  | [**EIntroSide**](#enum-eintroside)  <br> |
| enum  | [**EScreenFlag**](#enum-escreenflag)  <br> |
| enum  | [**EWinSide**](#enum-ewinside)  <br> |




## Public Attributes

| Type | Name |
| ---: | :--- |
|  int32 | [**MaxRollbackFrames**](#variable-maxrollbackframes)   = `1`<br> |
|  float | [**OneFrame**](#variable-oneframe)   = `0.0166666666`<br> |
|  size\_t | [**SizeOfBattleState**](#variable-sizeofbattlestate)   = `/* multi line expression */`<br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**ENUM\_CLASS\_FLAGS**](#function-enum_class_flags) (EScreenFlag) <br> |




























## Public Types Documentation




### enum EBattleFormat 

```C++
enum EBattleFormat {
    Rounds,
    Tag,
    KOF
};
```




<hr>



### enum EBattlePhase 

```C++
enum EBattlePhase {
    Intro,
    Battle,
    RoundEnd,
    Fade,
    Outro,
    EndScreen
};
```




<hr>



### enum EIntroSide 

```C++
enum EIntroSide {
    INT_P1,
    INT_P2,
    INT_None
};
```




<hr>



### enum EScreenFlag 

```C++
enum EScreenFlag {
    SCR_None,
    SCR_Lock = 1 << 0,
    SCR_LockXPos = 1 << 1,
    SCR_LockYPos = 1 << 2,
    SCR_LockWidth = 1 << 3,
    SCR_DisableScreenSides = 1 << 4
};
```




<hr>



### enum EWinSide 

```C++
enum EWinSide {
    WIN_None,
    WIN_P1,
    WIN_P2,
    WIN_Draw
};
```




<hr>
## Public Attributes Documentation




### variable MaxRollbackFrames 

```C++
int32 MaxRollbackFrames;
```




<hr>



### variable OneFrame 

```C++
float OneFrame;
```




<hr>



### variable SizeOfBattleState 

```C++
size_t SizeOfBattleState;
```




<hr>
## Public Functions Documentation




### function ENUM\_CLASS\_FLAGS 

```C++
ENUM_CLASS_FLAGS (
    EScreenFlag
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/NightSkyEngine/Battle/NightSkyGameState.h`

