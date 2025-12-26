

# Class ANightSkyAIController



[**ClassList**](annotated.md) **>** [**ANightSkyAIController**](class_a_night_sky_a_i_controller.md)








Inherits the following classes: AAIController


















## Public Attributes

| Type | Name |
| ---: | :--- |
|  TObjectPtr&lt; [**ANightSkyGameState**](class_a_night_sky_game_state.md) &gt; | [**GameState**](#variable-gamestate)   = `nullptr`<br> |
|  TObjectPtr&lt; [**APlayerObject**](class_a_player_object.md) &gt; | [**Player**](#variable-player)   = `nullptr`<br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**ANightSkyAIController**](#function-anightskyaicontroller) () <br> |
|  int32 | [**CheckAttackWeight**](#function-checkattackweight) (const [**UState**](class_u_state.md) \* State) const<br> |
|  int32 | [**CheckBasicWeight**](#function-checkbasicweight) (const [**UState**](class_u_state.md) \* State) const<br> |
|  int32 | [**CheckDefenseWeight**](#function-checkdefenseweight) (const [**UState**](class_u_state.md) \* State) <br> |
|  int32 | [**GetEnemyDistanceX**](#function-getenemydistancex) () const<br> |
|  int32 | [**GetEnemyDistanceY**](#function-getenemydistancey) () const<br> |
|  void | [**ResetParams**](#function-resetparams) () <br> |
|  bool | [**SetInputs**](#function-setinputs) () <br> |
|  void | [**Update**](#function-update) () <br> |
























## Protected Functions

| Type | Name |
| ---: | :--- |
| virtual void | [**BeginPlay**](#function-beginplay) () override<br> |




## Public Attributes Documentation




### variable GameState 

```C++
TObjectPtr<ANightSkyGameState> ANightSkyAIController::GameState;
```




<hr>



### variable Player 

```C++
TObjectPtr<APlayerObject> ANightSkyAIController::Player;
```




<hr>
## Public Functions Documentation




### function ANightSkyAIController 

```C++
ANightSkyAIController::ANightSkyAIController () 
```




<hr>



### function CheckAttackWeight 

```C++
int32 ANightSkyAIController::CheckAttackWeight (
    const UState * State
) const
```




<hr>



### function CheckBasicWeight 

```C++
int32 ANightSkyAIController::CheckBasicWeight (
    const UState * State
) const
```




<hr>



### function CheckDefenseWeight 

```C++
int32 ANightSkyAIController::CheckDefenseWeight (
    const UState * State
) 
```




<hr>



### function GetEnemyDistanceX 

```C++
int32 ANightSkyAIController::GetEnemyDistanceX () const
```




<hr>



### function GetEnemyDistanceY 

```C++
int32 ANightSkyAIController::GetEnemyDistanceY () const
```




<hr>



### function ResetParams 

```C++
void ANightSkyAIController::ResetParams () 
```




<hr>



### function SetInputs 

```C++
bool ANightSkyAIController::SetInputs () 
```




<hr>



### function Update 

```C++
void ANightSkyAIController::Update () 
```




<hr>
## Protected Functions Documentation




### function BeginPlay 

```C++
virtual void ANightSkyAIController::BeginPlay () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/NightSkyEngine/Battle/CPU/NightSkyAIController.h`

