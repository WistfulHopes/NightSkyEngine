

# Class TimeSync



[**ClassList**](annotated.md) **>** [**TimeSync**](class_time_sync.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**TimeSync**](#function-timesync) () <br> |
|  void | [**advance\_frame**](#function-advance_frame) ([**GameInput**](struct_game_input.md) & input, int advantage, int radvantage) <br> |
|  int | [**recommend\_frame\_wait\_duration**](#function-recommend_frame_wait_duration) (bool require\_idle\_input) <br> |
| virtual  | [**~TimeSync**](#function-timesync) () <br> |








## Protected Attributes

| Type | Name |
| ---: | :--- |
|  [**GameInput**](struct_game_input.md) | [**\_last\_inputs**](#variable-_last_inputs)  <br> |
|  int | [**\_local**](#variable-_local)  <br> |
|  int | [**\_next\_prediction**](#variable-_next_prediction)  <br> |
|  int | [**\_remote**](#variable-_remote)  <br> |




















## Public Functions Documentation




### function TimeSync 

```C++
TimeSync::TimeSync () 
```




<hr>



### function advance\_frame 

```C++
void TimeSync::advance_frame (
    GameInput & input,
    int advantage,
    int radvantage
) 
```




<hr>



### function recommend\_frame\_wait\_duration 

```C++
int TimeSync::recommend_frame_wait_duration (
    bool require_idle_input
) 
```




<hr>



### function ~TimeSync 

```C++
virtual TimeSync::~TimeSync () 
```




<hr>
## Protected Attributes Documentation




### variable \_last\_inputs 

```C++
GameInput TimeSync::_last_inputs[MIN_UNIQUE_FRAMES];
```




<hr>



### variable \_local 

```C++
int TimeSync::_local[FRAME_WINDOW_SIZE];
```




<hr>



### variable \_next\_prediction 

```C++
int TimeSync::_next_prediction;
```




<hr>



### variable \_remote 

```C++
int TimeSync::_remote[FRAME_WINDOW_SIZE];
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/GGPOUE4/Private/timesync.h`

