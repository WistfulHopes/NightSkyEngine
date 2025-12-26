

# Class AWTCharacter



[**ClassList**](annotated.md) **>** [**AWTCharacter**](class_a_w_t_character.md)








Inherits the following classes: ACharacter


















## Public Attributes

| Type | Name |
| ---: | :--- |
|  [**APlayerObject**](class_a_player_object.md) \* | [**BattlePlayer**](#variable-battleplayer)  <br> |
|  TSubclassOf&lt; [**APlayerObject**](class_a_player_object.md) &gt; | [**BattlePlayerClass**](#variable-battleplayerclass)  <br> |
|  [**ANightSkyWTGameState**](class_a_night_sky_w_t_game_state.md) \* | [**GameState**](#variable-gamestate)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**AWTCharacter**](#function-awtcharacter) () <br> |
|  void | [**EndBattle**](#function-endbattle) () <br> |
|  void | [**EndBattle\_BP**](#function-endbattle_bp) () <br> |
| virtual void | [**SetupPlayerInputComponent**](#function-setupplayerinputcomponent) (class UInputComponent \* PlayerInputComponent) override<br> |
|  void | [**StartBattle**](#function-startbattle) ([**AWTCharacter**](class_a_w_t_character.md) \* Opponent) <br> |
| virtual void | [**Tick**](#function-tick) (float DeltaTime) override<br> |
























## Protected Functions

| Type | Name |
| ---: | :--- |
| virtual void | [**BeginPlay**](#function-beginplay) () override<br> |




## Public Attributes Documentation




### variable BattlePlayer 

```C++
APlayerObject* AWTCharacter::BattlePlayer;
```




<hr>



### variable BattlePlayerClass 

```C++
TSubclassOf<APlayerObject> AWTCharacter::BattlePlayerClass;
```




<hr>



### variable GameState 

```C++
ANightSkyWTGameState* AWTCharacter::GameState;
```




<hr>
## Public Functions Documentation




### function AWTCharacter 

```C++
AWTCharacter::AWTCharacter () 
```




<hr>



### function EndBattle 

```C++
void AWTCharacter::EndBattle () 
```




<hr>



### function EndBattle\_BP 

```C++
void AWTCharacter::EndBattle_BP () 
```




<hr>



### function SetupPlayerInputComponent 

```C++
virtual void AWTCharacter::SetupPlayerInputComponent (
    class UInputComponent * PlayerInputComponent
) override
```




<hr>



### function StartBattle 

```C++
void AWTCharacter::StartBattle (
    AWTCharacter * Opponent
) 
```




<hr>



### function Tick 

```C++
virtual void AWTCharacter::Tick (
    float DeltaTime
) override
```




<hr>
## Protected Functions Documentation




### function BeginPlay 

```C++
virtual void AWTCharacter::BeginPlay () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/NightSkyEngine/WT/WTCharacter.h`

