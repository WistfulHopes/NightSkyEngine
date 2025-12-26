

# Class ANightSkyCharaSelectGameState



[**ClassList**](annotated.md) **>** [**ANightSkyCharaSelectGameState**](class_a_night_sky_chara_select_game_state.md)








Inherits the following classes: AGameStateBase


















## Public Attributes

| Type | Name |
| ---: | :--- |
|  TArray&lt; [**APlayerObject**](class_a_player_object.md) \* &gt; | [**P1Charas**](#variable-p1charas)  <br> |
|  TArray&lt; FVector &gt; | [**P1Positions**](#variable-p1positions)  <br> |
|  TArray&lt; [**APlayerObject**](class_a_player_object.md) \* &gt; | [**P2Charas**](#variable-p2charas)  <br> |
|  TArray&lt; FVector &gt; | [**P2Positions**](#variable-p2positions)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**ANightSkyCharaSelectGameState**](#function-anightskycharaselectgamestate) () <br> |
|  void | [**AddColorIndex**](#function-addcolorindex) (int InColor, bool IsP1=true) <br> |
|  void | [**AddPlayerObject**](#function-addplayerobject) ([**UPrimaryCharaData**](class_u_primary_chara_data.md) \* Player, bool IsP1=true) <br> |
| virtual void | [**Tick**](#function-tick) (float DeltaTime) override<br> |
























## Protected Functions

| Type | Name |
| ---: | :--- |
| virtual void | [**BeginPlay**](#function-beginplay) () override<br> |




## Public Attributes Documentation




### variable P1Charas 

```C++
TArray<APlayerObject*> ANightSkyCharaSelectGameState::P1Charas;
```




<hr>



### variable P1Positions 

```C++
TArray<FVector> ANightSkyCharaSelectGameState::P1Positions;
```




<hr>



### variable P2Charas 

```C++
TArray<APlayerObject*> ANightSkyCharaSelectGameState::P2Charas;
```




<hr>



### variable P2Positions 

```C++
TArray<FVector> ANightSkyCharaSelectGameState::P2Positions;
```




<hr>
## Public Functions Documentation




### function ANightSkyCharaSelectGameState 

```C++
ANightSkyCharaSelectGameState::ANightSkyCharaSelectGameState () 
```




<hr>



### function AddColorIndex 

```C++
void ANightSkyCharaSelectGameState::AddColorIndex (
    int InColor,
    bool IsP1=true
) 
```




<hr>



### function AddPlayerObject 

```C++
void ANightSkyCharaSelectGameState::AddPlayerObject (
    UPrimaryCharaData * Player,
    bool IsP1=true
) 
```




<hr>



### function Tick 

```C++
virtual void ANightSkyCharaSelectGameState::Tick (
    float DeltaTime
) override
```




<hr>
## Protected Functions Documentation




### function BeginPlay 

```C++
virtual void ANightSkyCharaSelectGameState::BeginPlay () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/NightSkyEngine/CharaSelect/NightSkyCharaSelectGameState.h`

