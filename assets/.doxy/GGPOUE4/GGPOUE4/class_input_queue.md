

# Class InputQueue



[**ClassList**](annotated.md) **>** [**InputQueue**](class_input_queue.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**AddInput**](#function-addinput) ([**GameInput**](struct_game_input.md) & input) <br> |
|  void | [**DiscardConfirmedFrames**](#function-discardconfirmedframes) (int frame) <br> |
|  bool | [**GetConfirmedInput**](#function-getconfirmedinput) (int frame, [**GameInput**](struct_game_input.md) \* input) <br> |
|  int | [**GetFirstIncorrectFrame**](#function-getfirstincorrectframe) () <br> |
|  bool | [**GetInput**](#function-getinput) (int frame, [**GameInput**](struct_game_input.md) \* input) <br> |
|  int | [**GetLastConfirmedFrame**](#function-getlastconfirmedframe) () <br> |
|  int | [**GetLength**](#function-getlength) () <br> |
|  void | [**Init**](#function-init) (int id, int input\_size) <br> |
|   | [**InputQueue**](#function-inputqueue) (int input\_size=DEFAULT\_INPUT\_SIZE) <br> |
|  void | [**ResetPrediction**](#function-resetprediction) (int frame) <br> |
|  void | [**SetFrameDelay**](#function-setframedelay) (int delay) <br> |
|   | [**~InputQueue**](#function-inputqueue) () <br> |








## Protected Attributes

| Type | Name |
| ---: | :--- |
|  bool | [**\_first\_frame**](#variable-_first_frame)  <br> |
|  int | [**\_first\_incorrect\_frame**](#variable-_first_incorrect_frame)  <br> |
|  int | [**\_frame\_delay**](#variable-_frame_delay)  <br> |
|  int | [**\_head**](#variable-_head)  <br> |
|  int | [**\_id**](#variable-_id)  <br> |
|  [**GameInput**](struct_game_input.md) | [**\_inputs**](#variable-_inputs)  <br> |
|  int | [**\_last\_added\_frame**](#variable-_last_added_frame)  <br> |
|  int | [**\_last\_frame\_requested**](#variable-_last_frame_requested)  <br> |
|  int | [**\_last\_user\_added\_frame**](#variable-_last_user_added_frame)  <br> |
|  int | [**\_length**](#variable-_length)  <br> |
|  [**GameInput**](struct_game_input.md) | [**\_prediction**](#variable-_prediction)  <br> |
|  int | [**\_tail**](#variable-_tail)  <br> |
















## Protected Functions

| Type | Name |
| ---: | :--- |
|  void | [**AddDelayedInputToQueue**](#function-adddelayedinputtoqueue) ([**GameInput**](struct_game_input.md) & input, int i) <br> |
|  int | [**AdvanceQueueHead**](#function-advancequeuehead) (int frame) <br> |
|  void | [**Log**](#function-log) (const char \* fmt, ...) <br> |




## Public Functions Documentation




### function AddInput 

```C++
void InputQueue::AddInput (
    GameInput & input
) 
```




<hr>



### function DiscardConfirmedFrames 

```C++
void InputQueue::DiscardConfirmedFrames (
    int frame
) 
```




<hr>



### function GetConfirmedInput 

```C++
bool InputQueue::GetConfirmedInput (
    int frame,
    GameInput * input
) 
```




<hr>



### function GetFirstIncorrectFrame 

```C++
int InputQueue::GetFirstIncorrectFrame () 
```




<hr>



### function GetInput 

```C++
bool InputQueue::GetInput (
    int frame,
    GameInput * input
) 
```




<hr>



### function GetLastConfirmedFrame 

```C++
int InputQueue::GetLastConfirmedFrame () 
```




<hr>



### function GetLength 

```C++
inline int InputQueue::GetLength () 
```




<hr>



### function Init 

```C++
void InputQueue::Init (
    int id,
    int input_size
) 
```




<hr>



### function InputQueue 

```C++
InputQueue::InputQueue (
    int input_size=DEFAULT_INPUT_SIZE
) 
```




<hr>



### function ResetPrediction 

```C++
void InputQueue::ResetPrediction (
    int frame
) 
```




<hr>



### function SetFrameDelay 

```C++
inline void InputQueue::SetFrameDelay (
    int delay
) 
```




<hr>



### function ~InputQueue 

```C++
InputQueue::~InputQueue () 
```




<hr>
## Protected Attributes Documentation




### variable \_first\_frame 

```C++
bool InputQueue::_first_frame;
```




<hr>



### variable \_first\_incorrect\_frame 

```C++
int InputQueue::_first_incorrect_frame;
```




<hr>



### variable \_frame\_delay 

```C++
int InputQueue::_frame_delay;
```




<hr>



### variable \_head 

```C++
int InputQueue::_head;
```




<hr>



### variable \_id 

```C++
int InputQueue::_id;
```




<hr>



### variable \_inputs 

```C++
GameInput InputQueue::_inputs[INPUT_QUEUE_LENGTH];
```




<hr>



### variable \_last\_added\_frame 

```C++
int InputQueue::_last_added_frame;
```




<hr>



### variable \_last\_frame\_requested 

```C++
int InputQueue::_last_frame_requested;
```




<hr>



### variable \_last\_user\_added\_frame 

```C++
int InputQueue::_last_user_added_frame;
```




<hr>



### variable \_length 

```C++
int InputQueue::_length;
```




<hr>



### variable \_prediction 

```C++
GameInput InputQueue::_prediction;
```




<hr>



### variable \_tail 

```C++
int InputQueue::_tail;
```




<hr>
## Protected Functions Documentation




### function AddDelayedInputToQueue 

```C++
void InputQueue::AddDelayedInputToQueue (
    GameInput & input,
    int i
) 
```




<hr>



### function AdvanceQueueHead 

```C++
int InputQueue::AdvanceQueueHead (
    int frame
) 
```




<hr>



### function Log 

```C++
void InputQueue::Log (
    const char * fmt,
    ...
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/GGPOUE4/Private/input_queue.h`

