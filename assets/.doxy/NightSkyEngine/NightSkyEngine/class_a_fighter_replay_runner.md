

# Class AFighterReplayRunner



[**ClassList**](annotated.md) **>** [**AFighterReplayRunner**](class_a_fighter_replay_runner.md)








Inherits the following classes: [AFighterLocalRunner](class_a_fighter_local_runner.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**AFighterReplayRunner**](#function-afighterreplayrunner) () <br> |
| virtual void | [**Update**](#function-update) (float DeltaTime) override<br> |


## Public Functions inherited from AFighterLocalRunner

See [AFighterLocalRunner](class_a_fighter_local_runner.md)

| Type | Name |
| ---: | :--- |
|   | [**AFighterLocalRunner**](class_a_fighter_local_runner.md#function-afighterlocalrunner) () <br> |
| virtual void | [**Update**](class_a_fighter_local_runner.md#function-update) (float DeltaTime) <br> |














## Protected Attributes

| Type | Name |
| ---: | :--- |
|  [**UNightSkyGameInstance**](class_u_night_sky_game_instance.md) \* | [**GameInstance**](#variable-gameinstance)  <br> |


## Protected Attributes inherited from AFighterLocalRunner

See [AFighterLocalRunner](class_a_fighter_local_runner.md)

| Type | Name |
| ---: | :--- |
|  float | [**ElapsedTime**](class_a_fighter_local_runner.md#variable-elapsedtime)   = `0`<br> |
|  class [**ANightSkyGameState**](class_a_night_sky_game_state.md) \* | [**GameState**](class_a_fighter_local_runner.md#variable-gamestate)  <br> |






























## Protected Functions

| Type | Name |
| ---: | :--- |
| virtual void | [**BeginPlay**](#function-beginplay) () override<br> |


## Protected Functions inherited from AFighterLocalRunner

See [AFighterLocalRunner](class_a_fighter_local_runner.md)

| Type | Name |
| ---: | :--- |
| virtual void | [**BeginPlay**](class_a_fighter_local_runner.md#function-beginplay) () override<br> |






## Public Functions Documentation




### function AFighterReplayRunner 

```C++
AFighterReplayRunner::AFighterReplayRunner () 
```




<hr>



### function Update 

```C++
virtual void AFighterReplayRunner::Update (
    float DeltaTime
) override
```



Implements [*AFighterLocalRunner::Update*](class_a_fighter_local_runner.md#function-update)


<hr>
## Protected Attributes Documentation




### variable GameInstance 

```C++
UNightSkyGameInstance* AFighterReplayRunner::GameInstance;
```




<hr>
## Protected Functions Documentation




### function BeginPlay 

```C++
virtual void AFighterReplayRunner::BeginPlay () override
```



Implements [*AFighterLocalRunner::BeginPlay*](class_a_fighter_local_runner.md#function-beginplay)


<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/NightSkyEngine/Battle/FighterRunners/FighterReplayRunner.h`

