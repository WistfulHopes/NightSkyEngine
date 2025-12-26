

# File ggponet.h



[**FileList**](files.md) **>** [**GGPOUE4**](dir_61f8f2a9aed5edd4e8edeed0f59c7e8a.md) **>** [**Public**](dir_85b7962d70ed8e910f117d16fb4825fd.md) **>** [**include**](dir_a7503a859c0cbfef62dfa39920604457.md) **>** [**ggponet.h**](ggponet_8h.md)

[Go to the source code of this file](ggponet_8h_source.md)



* `#include "CoreMinimal.h"`
* `#include <stdarg.h>`
* `#include "connection_manager.h"`
* `#include <functional>`
* `#include "ggponet.generated.h"`















## Classes

| Type | Name |
| ---: | :--- |
| struct | [**FGGPONetworkInfo**](struct_f_g_g_p_o_network_info.md) <br> |
| struct | [**FGGPONetworkStats**](struct_f_g_g_p_o_network_stats.md) <br> |
| struct | [**FGGPOSyncInfo**](struct_f_g_g_p_o_sync_info.md) <br> |
| struct | [**GGPOEvent**](struct_g_g_p_o_event.md) <br> |
| struct | [**GGPOLocalEndpoint**](struct_g_g_p_o_local_endpoint.md) <br> |
| class | [**GGPONet**](class_g_g_p_o_net.md) <br> |
| struct | [**GGPOPlayer**](struct_g_g_p_o_player.md) <br> |
| struct | [**GGPOSessionCallbacks**](struct_g_g_p_o_session_callbacks.md) <br> |
| class | [**UGGPONetwork**](class_u_g_g_p_o_network.md) <br> |
| class | [**UGGPONetworkAddress**](class_u_g_g_p_o_network_address.md) <br> |


## Public Types

| Type | Name |
| ---: | :--- |
| enum  | [**GGPOErrorCode**](#enum-ggpoerrorcode)  <br> |
| enum  | [**GGPOEventCode**](#enum-ggpoeventcode)  <br> |
| typedef struct GGPOLocalEndpoint | [**GGPOLocalEndpoint**](#typedef-ggpolocalendpoint)  <br> |
| typedef struct GGPOPlayer | [**GGPOPlayer**](#typedef-ggpoplayer)  <br> |
| typedef int32 | [**GGPOPlayerHandle**](#typedef-ggpoplayerhandle)  <br> |
| enum  | [**GGPOPlayerType**](#enum-ggpoplayertype)  <br> |
| typedef struct GGPOSession | [**GGPOSession**](#typedef-ggposession)  <br> |
| typedef long long | [**ggpo\_milliseconds\_t**](#typedef-ggpo_milliseconds_t)  <br> |















































## Macros

| Type | Name |
| ---: | :--- |
| define  | [**GGPONET\_CONVENTION**](ggponet_8h.md#define-ggponet_convention)  `\_\_cdecl`<br> |
| define  | [**GGPO\_API**](ggponet_8h.md#define-ggpo_api)  <br> |
| define  | [**GGPO\_ERRORLIST**](ggponet_8h.md#define-ggpo_errorlist)  `/* multi line expression */`<br> |
| define  | [**GGPO\_ERRORLIST\_ENTRY**](ggponet_8h.md#define-ggpo_errorlist_entry) (name, value) `name = value,`<br> |
| define  | [**GGPO\_INVALID\_HANDLE**](ggponet_8h.md#define-ggpo_invalid_handle)  `(-1)`<br> |
| define  | [**GGPO\_MAX\_PLAYERS**](ggponet_8h.md#define-ggpo_max_players)  `4`<br> |
| define  | [**GGPO\_MAX\_PREDICTION\_FRAMES**](ggponet_8h.md#define-ggpo_max_prediction_frames)  `8`<br> |
| define  | [**GGPO\_MAX\_SPECTATORS**](ggponet_8h.md#define-ggpo_max_spectators)  `32`<br> |
| define  | [**GGPO\_SPECTATOR\_INPUT\_INTERVAL**](ggponet_8h.md#define-ggpo_spectator_input_interval)  `4`<br> |
| define  | [**GGPO\_SUCCEEDED**](ggponet_8h.md#define-ggpo_succeeded) (result) `((result) == GGPO\_ERRORCODE\_SUCCESS)`<br> |

## Public Types Documentation




### enum GGPOErrorCode 

```C++
enum GGPOErrorCode {
    GGPO_ERRORLIST
};
```




<hr>



### enum GGPOEventCode 

```C++
enum GGPOEventCode {
    GGPO_EVENTCODE_CONNECTED_TO_PEER = 1000,
    GGPO_EVENTCODE_SYNCHRONIZING_WITH_PEER = 1001,
    GGPO_EVENTCODE_SYNCHRONIZED_WITH_PEER = 1002,
    GGPO_EVENTCODE_RUNNING = 1003,
    GGPO_EVENTCODE_DISCONNECTED_FROM_PEER = 1004,
    GGPO_EVENTCODE_TIMESYNC = 1005,
    GGPO_EVENTCODE_CONNECTION_INTERRUPTED = 1006,
    GGPO_EVENTCODE_CONNECTION_RESUMED = 1007,
    GGPO_EVENTCODE_TIMESYNC_BEHIND = 1008
};
```




<hr>



### typedef GGPOLocalEndpoint 

```C++
typedef struct GGPOLocalEndpoint GGPOLocalEndpoint;
```




<hr>



### typedef GGPOPlayer 

```C++
typedef struct GGPOPlayer GGPOPlayer;
```




<hr>



### typedef GGPOPlayerHandle 

```C++
typedef int32 GGPOPlayerHandle;
```




<hr>



### enum GGPOPlayerType 

```C++
enum GGPOPlayerType {
    GGPO_PLAYERTYPE_LOCAL,
    GGPO_PLAYERTYPE_REMOTE,
    GGPO_PLAYERTYPE_SPECTATOR
};
```




<hr>



### typedef GGPOSession 

```C++
typedef struct GGPOSession GGPOSession;
```




<hr>



### typedef ggpo\_milliseconds\_t 

```C++
typedef long long ggpo_milliseconds_t;
```




<hr>
## Macro Definition Documentation





### define GGPONET\_CONVENTION 

```C++
#define GGPONET_CONVENTION `__cdecl`
```




<hr>



### define GGPO\_API 

```C++
#define GGPO_API 
```




<hr>



### define GGPO\_ERRORLIST 

```C++
#define GGPO_ERRORLIST `/* multi line expression */`
```




<hr>



### define GGPO\_ERRORLIST\_ENTRY 

```C++
#define GGPO_ERRORLIST_ENTRY (
    name,
    value
) `name = value,`
```




<hr>



### define GGPO\_INVALID\_HANDLE 

```C++
#define GGPO_INVALID_HANDLE `(-1)`
```




<hr>



### define GGPO\_MAX\_PLAYERS 

```C++
#define GGPO_MAX_PLAYERS `4`
```




<hr>



### define GGPO\_MAX\_PREDICTION\_FRAMES 

```C++
#define GGPO_MAX_PREDICTION_FRAMES `8`
```




<hr>



### define GGPO\_MAX\_SPECTATORS 

```C++
#define GGPO_MAX_SPECTATORS `32`
```




<hr>



### define GGPO\_SPECTATOR\_INPUT\_INTERVAL 

```C++
#define GGPO_SPECTATOR_INPUT_INTERVAL `4`
```




<hr>



### define GGPO\_SUCCEEDED 

```C++
#define GGPO_SUCCEEDED (
    result
) `((result) == GGPO_ERRORCODE_SUCCESS)`
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/GGPOUE4/Public/include/ggponet.h`

