

# Class SyncTestBackend



[**ClassList**](annotated.md) **>** [**SyncTestBackend**](class_sync_test_backend.md)








Inherits the following classes: [GGPOSession](struct_g_g_p_o_session.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual GGPOErrorCode | [**AddLocalInput**](#function-addlocalinput) (GGPOPlayerHandle player, void \* values, int size) <br> |
| virtual GGPOErrorCode | [**AddPlayer**](#function-addplayer) ([**GGPOPlayer**](struct_g_g_p_o_player.md) \* player, GGPOPlayerHandle \* handle) <br> |
| virtual GGPOErrorCode | [**DoPoll**](#function-dopoll) (int timeout) <br> |
| virtual GGPOErrorCode | [**IncrementFrame**](#function-incrementframe) (void) <br> |
| virtual GGPOErrorCode | [**Logv**](#function-logv) (const char \* fmt, va\_list list) override<br> |
| virtual GGPOErrorCode | [**SyncInput**](#function-syncinput) (void \* values, int size, int \* disconnect\_flags) <br> |
|   | [**SyncTestBackend**](#function-synctestbackend) ([**GGPOSessionCallbacks**](struct_g_g_p_o_session_callbacks.md) \* cb, const char \* gamename, int frames, int num\_players) <br> |
| virtual  | [**~SyncTestBackend**](#function-synctestbackend) () <br> |


## Public Functions inherited from GGPOSession

See [GGPOSession](struct_g_g_p_o_session.md)

| Type | Name |
| ---: | :--- |
| virtual GGPOErrorCode | [**AddLocalInput**](struct_g_g_p_o_session.md#function-addlocalinput) (GGPOPlayerHandle player, void \* values, int size) = 0<br> |
| virtual GGPOErrorCode | [**AddPlayer**](struct_g_g_p_o_session.md#function-addplayer) ([**GGPOPlayer**](struct_g_g_p_o_player.md) \* player, GGPOPlayerHandle \* handle) = 0<br> |
| virtual GGPOErrorCode | [**Chat**](struct_g_g_p_o_session.md#function-chat) (char \* text) <br> |
| virtual GGPOErrorCode | [**DisconnectPlayer**](struct_g_g_p_o_session.md#function-disconnectplayer) (GGPOPlayerHandle handle) <br> |
| virtual GGPOErrorCode | [**DoPoll**](struct_g_g_p_o_session.md#function-dopoll) (int timeout) <br> |
| virtual GGPOErrorCode | [**GetNetworkStats**](struct_g_g_p_o_session.md#function-getnetworkstats) ([**FGGPONetworkStats**](struct_f_g_g_p_o_network_stats.md) \* stats, GGPOPlayerHandle handle) <br> |
| virtual GGPOErrorCode | [**IncrementFrame**](struct_g_g_p_o_session.md#function-incrementframe) (void) <br> |
| virtual GGPOErrorCode | [**Logv**](struct_g_g_p_o_session.md#function-logv) (const char \* fmt, va\_list list) <br> |
| virtual GGPOErrorCode | [**SetDisconnectNotifyStart**](struct_g_g_p_o_session.md#function-setdisconnectnotifystart) (int timeout) <br> |
| virtual GGPOErrorCode | [**SetDisconnectTimeout**](struct_g_g_p_o_session.md#function-setdisconnecttimeout) (int timeout) <br> |
| virtual GGPOErrorCode | [**SetFrameDelay**](struct_g_g_p_o_session.md#function-setframedelay) (GGPOPlayerHandle player, int delay) <br> |
| virtual GGPOErrorCode | [**SyncInput**](struct_g_g_p_o_session.md#function-syncinput) (void \* values, int size, int \* disconnect\_flags) = 0<br> |
| virtual GGPOErrorCode | [**TrySynchronizeLocal**](struct_g_g_p_o_session.md#function-trysynchronizelocal) () <br> |
| virtual  | [**~GGPOSession**](struct_g_g_p_o_session.md#function-ggposession) () <br> |














## Protected Attributes

| Type | Name |
| ---: | :--- |
|  [**GGPOSessionCallbacks**](struct_g_g_p_o_session_callbacks.md) | [**\_callbacks**](#variable-_callbacks)  <br> |
|  int | [**\_check\_distance**](#variable-_check_distance)  <br> |
|  [**GameInput**](struct_game_input.md) | [**\_current\_input**](#variable-_current_input)  <br> |
|  char | [**\_game**](#variable-_game)  <br> |
|  [**GameInput**](struct_game_input.md) | [**\_last\_input**](#variable-_last_input)  <br> |
|  int | [**\_last\_verified**](#variable-_last_verified)  <br> |
|  FILE \* | [**\_logfp**](#variable-_logfp)  <br> |
|  int | [**\_num\_players**](#variable-_num_players)  <br> |
|  bool | [**\_rollingback**](#variable-_rollingback)  <br> |
|  bool | [**\_running**](#variable-_running)  <br> |
|  [**RingBuffer**](class_ring_buffer.md)&lt; [**SavedInfo**](struct_sync_test_backend_1_1_saved_info.md), 32 &gt; | [**\_saved\_frames**](#variable-_saved_frames)  <br> |
|  [**Sync**](class_sync.md) | [**\_sync**](#variable-_sync)  <br> |
































## Protected Functions

| Type | Name |
| ---: | :--- |
|  void | [**BeginLog**](#function-beginlog) (int saving) <br> |
|  void | [**EndLog**](#function-endlog) () <br> |
|  void | [**LogSaveStates**](#function-logsavestates) ([**SavedInfo**](struct_sync_test_backend_1_1_saved_info.md) & info) <br> |
|  void | [**RaiseSyncError**](#function-raisesyncerror) (const char \* fmt, ...) <br> |








## Public Functions Documentation




### function AddLocalInput 

```C++
virtual GGPOErrorCode SyncTestBackend::AddLocalInput (
    GGPOPlayerHandle player,
    void * values,
    int size
) 
```



Implements [*GGPOSession::AddLocalInput*](struct_g_g_p_o_session.md#function-addlocalinput)


<hr>



### function AddPlayer 

```C++
virtual GGPOErrorCode SyncTestBackend::AddPlayer (
    GGPOPlayer * player,
    GGPOPlayerHandle * handle
) 
```



Implements [*GGPOSession::AddPlayer*](struct_g_g_p_o_session.md#function-addplayer)


<hr>



### function DoPoll 

```C++
virtual GGPOErrorCode SyncTestBackend::DoPoll (
    int timeout
) 
```



Implements [*GGPOSession::DoPoll*](struct_g_g_p_o_session.md#function-dopoll)


<hr>



### function IncrementFrame 

```C++
virtual GGPOErrorCode SyncTestBackend::IncrementFrame (
    void
) 
```



Implements [*GGPOSession::IncrementFrame*](struct_g_g_p_o_session.md#function-incrementframe)


<hr>



### function Logv 

```C++
virtual GGPOErrorCode SyncTestBackend::Logv (
    const char * fmt,
    va_list list
) override
```



Implements [*GGPOSession::Logv*](struct_g_g_p_o_session.md#function-logv)


<hr>



### function SyncInput 

```C++
virtual GGPOErrorCode SyncTestBackend::SyncInput (
    void * values,
    int size,
    int * disconnect_flags
) 
```



Implements [*GGPOSession::SyncInput*](struct_g_g_p_o_session.md#function-syncinput)


<hr>



### function SyncTestBackend 

```C++
SyncTestBackend::SyncTestBackend (
    GGPOSessionCallbacks * cb,
    const char * gamename,
    int frames,
    int num_players
) 
```




<hr>



### function ~SyncTestBackend 

```C++
virtual SyncTestBackend::~SyncTestBackend () 
```




<hr>
## Protected Attributes Documentation




### variable \_callbacks 

```C++
GGPOSessionCallbacks SyncTestBackend::_callbacks;
```




<hr>



### variable \_check\_distance 

```C++
int SyncTestBackend::_check_distance;
```




<hr>



### variable \_current\_input 

```C++
GameInput SyncTestBackend::_current_input;
```




<hr>



### variable \_game 

```C++
char SyncTestBackend::_game[128];
```




<hr>



### variable \_last\_input 

```C++
GameInput SyncTestBackend::_last_input;
```




<hr>



### variable \_last\_verified 

```C++
int SyncTestBackend::_last_verified;
```




<hr>



### variable \_logfp 

```C++
FILE* SyncTestBackend::_logfp;
```




<hr>



### variable \_num\_players 

```C++
int SyncTestBackend::_num_players;
```




<hr>



### variable \_rollingback 

```C++
bool SyncTestBackend::_rollingback;
```




<hr>



### variable \_running 

```C++
bool SyncTestBackend::_running;
```




<hr>



### variable \_saved\_frames 

```C++
RingBuffer<SavedInfo, 32> SyncTestBackend::_saved_frames;
```




<hr>



### variable \_sync 

```C++
Sync SyncTestBackend::_sync;
```




<hr>
## Protected Functions Documentation




### function BeginLog 

```C++
void SyncTestBackend::BeginLog (
    int saving
) 
```




<hr>



### function EndLog 

```C++
void SyncTestBackend::EndLog () 
```




<hr>



### function LogSaveStates 

```C++
void SyncTestBackend::LogSaveStates (
    SavedInfo & info
) 
```




<hr>



### function RaiseSyncError 

```C++
void SyncTestBackend::RaiseSyncError (
    const char * fmt,
    ...
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/GGPOUE4/Private/backends/synctest.h`

