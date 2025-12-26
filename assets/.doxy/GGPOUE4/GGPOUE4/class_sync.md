

# Class Sync



[**ClassList**](annotated.md) **>** [**Sync**](class_sync.md)




















## Classes

| Type | Name |
| ---: | :--- |
| struct | [**Config**](struct_sync_1_1_config.md) <br> |
| struct | [**Event**](struct_sync_1_1_event.md) <br> |






















## Public Functions

| Type | Name |
| ---: | :--- |
|  bool | [**AddLocalInput**](#function-addlocalinput) (int queue, [**GameInput**](struct_game_input.md) & input) <br> |
|  void | [**AddRemoteInput**](#function-addremoteinput) (int queue, [**GameInput**](struct_game_input.md) & input) <br> |
|  void | [**AdjustSimulation**](#function-adjustsimulation) (int seek\_to) <br> |
|  void | [**CheckSimulation**](#function-checksimulation) (int timeout) <br> |
|  int | [**GetConfirmedInputs**](#function-getconfirmedinputs) (void \* values, int size, int frame) <br> |
|  bool | [**GetEvent**](#function-getevent) ([**Event**](struct_sync_1_1_event.md) & e) <br> |
|  int | [**GetFrameCount**](#function-getframecount) () <br> |
|  bool | [**InRollback**](#function-inrollback) () <br> |
|  void | [**IncrementFrame**](#function-incrementframe) (void) <br> |
|  void | [**Init**](#function-init) ([**Config**](struct_sync_1_1_config.md) & config) <br> |
|  void | [**SetFrameDelay**](#function-setframedelay) (int queue, int delay) <br> |
|  void | [**SetLastConfirmedFrame**](#function-setlastconfirmedframe) (int frame) <br> |
|   | [**Sync**](#function-sync) ([**UdpMsg::connect\_status**](struct_udp_msg_1_1connect__status.md) \* connect\_status) <br> |
|  int | [**SynchronizeInputs**](#function-synchronizeinputs) (void \* values, int size) <br> |
| virtual  | [**~Sync**](#function-sync) () <br> |








## Protected Attributes

| Type | Name |
| ---: | :--- |
|  friend | [**SyncTestBackend**](#variable-synctestbackend)  <br> |
|  [**GGPOSessionCallbacks**](struct_g_g_p_o_session_callbacks.md) | [**\_callbacks**](#variable-_callbacks)  <br> |
|  [**Config**](struct_sync_1_1_config.md) | [**\_config**](#variable-_config)  <br> |
|  [**RingBuffer**](class_ring_buffer.md)&lt; [**Event**](struct_sync_1_1_event.md), 32 &gt; | [**\_event\_queue**](#variable-_event_queue)  <br> |
|  int | [**\_framecount**](#variable-_framecount)  <br> |
|  [**InputQueue**](class_input_queue.md) \* | [**\_input\_queues**](#variable-_input_queues)  <br> |
|  int | [**\_last\_confirmed\_frame**](#variable-_last_confirmed_frame)  <br> |
|  [**UdpMsg::connect\_status**](struct_udp_msg_1_1connect__status.md) \* | [**\_local\_connect\_status**](#variable-_local_connect_status)  <br> |
|  int | [**\_max\_prediction\_frames**](#variable-_max_prediction_frames)  <br> |
|  bool | [**\_rollingback**](#variable-_rollingback)  <br> |
|  [**SavedState**](struct_sync_1_1_saved_state.md) | [**\_savedstate**](#variable-_savedstate)  <br> |
















## Protected Functions

| Type | Name |
| ---: | :--- |
|  bool | [**CheckSimulationConsistency**](#function-checksimulationconsistency) (int \* seekTo) <br> |
|  bool | [**CreateQueues**](#function-createqueues) ([**Config**](struct_sync_1_1_config.md) & config) <br> |
|  int | [**FindSavedFrameIndex**](#function-findsavedframeindex) (int frame) <br> |
|  [**SavedFrame**](struct_sync_1_1_saved_frame.md) & | [**GetLastSavedFrame**](#function-getlastsavedframe) () <br> |
|  void | [**LoadFrame**](#function-loadframe) (int frame) <br> |
|  void | [**ResetPrediction**](#function-resetprediction) (int frameNumber) <br> |
|  void | [**SaveCurrentFrame**](#function-savecurrentframe) () <br> |




## Public Functions Documentation




### function AddLocalInput 

```C++
bool Sync::AddLocalInput (
    int queue,
    GameInput & input
) 
```




<hr>



### function AddRemoteInput 

```C++
void Sync::AddRemoteInput (
    int queue,
    GameInput & input
) 
```




<hr>



### function AdjustSimulation 

```C++
void Sync::AdjustSimulation (
    int seek_to
) 
```




<hr>



### function CheckSimulation 

```C++
void Sync::CheckSimulation (
    int timeout
) 
```




<hr>



### function GetConfirmedInputs 

```C++
int Sync::GetConfirmedInputs (
    void * values,
    int size,
    int frame
) 
```




<hr>



### function GetEvent 

```C++
bool Sync::GetEvent (
    Event & e
) 
```




<hr>



### function GetFrameCount 

```C++
inline int Sync::GetFrameCount () 
```




<hr>



### function InRollback 

```C++
inline bool Sync::InRollback () 
```




<hr>



### function IncrementFrame 

```C++
void Sync::IncrementFrame (
    void
) 
```




<hr>



### function Init 

```C++
void Sync::Init (
    Config & config
) 
```




<hr>



### function SetFrameDelay 

```C++
void Sync::SetFrameDelay (
    int queue,
    int delay
) 
```




<hr>



### function SetLastConfirmedFrame 

```C++
void Sync::SetLastConfirmedFrame (
    int frame
) 
```




<hr>



### function Sync 

```C++
Sync::Sync (
    UdpMsg::connect_status * connect_status
) 
```




<hr>



### function SynchronizeInputs 

```C++
int Sync::SynchronizeInputs (
    void * values,
    int size
) 
```




<hr>



### function ~Sync 

```C++
virtual Sync::~Sync () 
```




<hr>
## Protected Attributes Documentation




### variable SyncTestBackend 

```C++
friend Sync::SyncTestBackend;
```




<hr>



### variable \_callbacks 

```C++
GGPOSessionCallbacks Sync::_callbacks;
```




<hr>



### variable \_config 

```C++
Config Sync::_config;
```




<hr>



### variable \_event\_queue 

```C++
RingBuffer<Event, 32> Sync::_event_queue;
```




<hr>



### variable \_framecount 

```C++
int Sync::_framecount;
```




<hr>



### variable \_input\_queues 

```C++
InputQueue* Sync::_input_queues;
```




<hr>



### variable \_last\_confirmed\_frame 

```C++
int Sync::_last_confirmed_frame;
```




<hr>



### variable \_local\_connect\_status 

```C++
UdpMsg::connect_status* Sync::_local_connect_status;
```




<hr>



### variable \_max\_prediction\_frames 

```C++
int Sync::_max_prediction_frames;
```




<hr>



### variable \_rollingback 

```C++
bool Sync::_rollingback;
```




<hr>



### variable \_savedstate 

```C++
SavedState Sync::_savedstate;
```




<hr>
## Protected Functions Documentation




### function CheckSimulationConsistency 

```C++
bool Sync::CheckSimulationConsistency (
    int * seekTo
) 
```




<hr>



### function CreateQueues 

```C++
bool Sync::CreateQueues (
    Config & config
) 
```




<hr>



### function FindSavedFrameIndex 

```C++
int Sync::FindSavedFrameIndex (
    int frame
) 
```




<hr>



### function GetLastSavedFrame 

```C++
SavedFrame & Sync::GetLastSavedFrame () 
```




<hr>



### function LoadFrame 

```C++
void Sync::LoadFrame (
    int frame
) 
```




<hr>



### function ResetPrediction 

```C++
void Sync::ResetPrediction (
    int frameNumber
) 
```




<hr>



### function SaveCurrentFrame 

```C++
void Sync::SaveCurrentFrame () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/GGPOUE4/Private/sync.h`

