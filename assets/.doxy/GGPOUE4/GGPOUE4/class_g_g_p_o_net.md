

# Class GGPONet



[**ClassList**](annotated.md) **>** [**GGPONet**](class_g_g_p_o_net.md)












































## Public Static Functions

| Type | Name |
| ---: | :--- |
|  GGPO\_API GGPOErrorCode \_\_cdecl | [**ggpo\_add\_local\_input**](#function-ggpo_add_local_input) ([**GGPOSession**](struct_g_g_p_o_session.md) \* ggpo, GGPOPlayerHandle player, void \* values, int size) <br> |
|  GGPO\_API GGPOErrorCode \_\_cdecl | [**ggpo\_add\_player**](#function-ggpo_add_player) ([**GGPOSession**](struct_g_g_p_o_session.md) \* session, [**GGPOPlayer**](struct_g_g_p_o_player.md) \* player, GGPOPlayerHandle \* handle) <br> |
|  GGPO\_API GGPOErrorCode \_\_cdecl | [**ggpo\_advance\_frame**](#function-ggpo_advance_frame) ([**GGPOSession**](struct_g_g_p_o_session.md) \* ggpo) <br> |
|  GGPO\_API GGPOErrorCode \_\_cdecl | [**ggpo\_close\_session**](#function-ggpo_close_session) ([**GGPOSession**](struct_g_g_p_o_session.md) \* ggpo) <br> |
|  GGPO\_API GGPOErrorCode \_\_cdecl | [**ggpo\_disconnect\_player**](#function-ggpo_disconnect_player) ([**GGPOSession**](struct_g_g_p_o_session.md) \* ggpo, GGPOPlayerHandle player) <br> |
|  GGPO\_API GGPOErrorCode \_\_cdecl | [**ggpo\_get\_network\_stats**](#function-ggpo_get_network_stats) ([**GGPOSession**](struct_g_g_p_o_session.md) \* ggpo, GGPOPlayerHandle player, [**FGGPONetworkStats**](struct_f_g_g_p_o_network_stats.md) \* stats) <br> |
|  GGPO\_API GGPOErrorCode \_\_cdecl | [**ggpo\_idle**](#function-ggpo_idle) ([**GGPOSession**](struct_g_g_p_o_session.md) \* ggpo, int timeout) <br> |
|  GGPO\_API GGPOErrorCode \_\_cdecl | [**ggpo\_set\_disconnect\_notify\_start**](#function-ggpo_set_disconnect_notify_start) ([**GGPOSession**](struct_g_g_p_o_session.md) \* ggpo, int timeout) <br> |
|  GGPO\_API GGPOErrorCode \_\_cdecl | [**ggpo\_set\_disconnect\_timeout**](#function-ggpo_set_disconnect_timeout) ([**GGPOSession**](struct_g_g_p_o_session.md) \* ggpo, int timeout) <br> |
|  GGPO\_API GGPOErrorCode \_\_cdecl | [**ggpo\_set\_frame\_delay**](#function-ggpo_set_frame_delay) ([**GGPOSession**](struct_g_g_p_o_session.md) \* ggpo, GGPOPlayerHandle player, int frame\_delay) <br> |
|  GGPO\_API GGPOErrorCode \_\_cdecl | [**ggpo\_start\_session**](#function-ggpo_start_session) ([**GGPOSession**](struct_g_g_p_o_session.md) \*\* session, [**GGPOSessionCallbacks**](struct_g_g_p_o_session_callbacks.md) \* cb, [**ConnectionManager**](class_connection_manager.md) \* connection\_manager, const char \* game, int num\_players, int input\_size) <br> |
|  GGPO\_API GGPOErrorCode \_\_cdecl | [**ggpo\_start\_spectating**](#function-ggpo_start_spectating) ([**GGPOSession**](struct_g_g_p_o_session.md) \*\* session, [**GGPOSessionCallbacks**](struct_g_g_p_o_session_callbacks.md) \* cb, [**ConnectionManager**](class_connection_manager.md) \* connection\_manager, const char \* game, int num\_players, int input\_size, int connection\_id) <br> |
|  GGPO\_API GGPOErrorCode \_\_cdecl | [**ggpo\_start\_synctest**](#function-ggpo_start_synctest) ([**GGPOSession**](struct_g_g_p_o_session.md) \*\* session, [**GGPOSessionCallbacks**](struct_g_g_p_o_session_callbacks.md) \* cb, const char \* game, int num\_players, int input\_size, int frames) <br> |
|  GGPO\_API GGPOErrorCode \_\_cdecl | [**ggpo\_synchronize\_input**](#function-ggpo_synchronize_input) ([**GGPOSession**](struct_g_g_p_o_session.md) \* ggpo, void \* values, int size, int \* disconnect\_flags) <br> |
|  GGPO\_API GGPOErrorCode \_\_cdecl | [**ggpo\_try\_synchronize\_local**](#function-ggpo_try_synchronize_local) ([**GGPOSession**](struct_g_g_p_o_session.md) \* ggpo) <br> |


























## Public Static Functions Documentation




### function ggpo\_add\_local\_input 

```C++
static GGPO_API GGPOErrorCode __cdecl GGPONet::ggpo_add_local_input (
    GGPOSession * ggpo,
    GGPOPlayerHandle player,
    void * values,
    int size
) 
```




<hr>



### function ggpo\_add\_player 

```C++
static GGPO_API GGPOErrorCode __cdecl GGPONet::ggpo_add_player (
    GGPOSession * session,
    GGPOPlayer * player,
    GGPOPlayerHandle * handle
) 
```




<hr>



### function ggpo\_advance\_frame 

```C++
static GGPO_API GGPOErrorCode __cdecl GGPONet::ggpo_advance_frame (
    GGPOSession * ggpo
) 
```




<hr>



### function ggpo\_close\_session 

```C++
static GGPO_API GGPOErrorCode __cdecl GGPONet::ggpo_close_session (
    GGPOSession * ggpo
) 
```




<hr>



### function ggpo\_disconnect\_player 

```C++
static GGPO_API GGPOErrorCode __cdecl GGPONet::ggpo_disconnect_player (
    GGPOSession * ggpo,
    GGPOPlayerHandle player
) 
```




<hr>



### function ggpo\_get\_network\_stats 

```C++
static GGPO_API GGPOErrorCode __cdecl GGPONet::ggpo_get_network_stats (
    GGPOSession * ggpo,
    GGPOPlayerHandle player,
    FGGPONetworkStats * stats
) 
```




<hr>



### function ggpo\_idle 

```C++
static GGPO_API GGPOErrorCode __cdecl GGPONet::ggpo_idle (
    GGPOSession * ggpo,
    int timeout
) 
```




<hr>



### function ggpo\_set\_disconnect\_notify\_start 

```C++
static GGPO_API GGPOErrorCode __cdecl GGPONet::ggpo_set_disconnect_notify_start (
    GGPOSession * ggpo,
    int timeout
) 
```




<hr>



### function ggpo\_set\_disconnect\_timeout 

```C++
static GGPO_API GGPOErrorCode __cdecl GGPONet::ggpo_set_disconnect_timeout (
    GGPOSession * ggpo,
    int timeout
) 
```




<hr>



### function ggpo\_set\_frame\_delay 

```C++
static GGPO_API GGPOErrorCode __cdecl GGPONet::ggpo_set_frame_delay (
    GGPOSession * ggpo,
    GGPOPlayerHandle player,
    int frame_delay
) 
```




<hr>



### function ggpo\_start\_session 

```C++
static GGPO_API GGPOErrorCode __cdecl GGPONet::ggpo_start_session (
    GGPOSession ** session,
    GGPOSessionCallbacks * cb,
    ConnectionManager * connection_manager,
    const char * game,
    int num_players,
    int input_size
) 
```




<hr>



### function ggpo\_start\_spectating 

```C++
static GGPO_API GGPOErrorCode __cdecl GGPONet::ggpo_start_spectating (
    GGPOSession ** session,
    GGPOSessionCallbacks * cb,
    ConnectionManager * connection_manager,
    const char * game,
    int num_players,
    int input_size,
    int connection_id
) 
```




<hr>



### function ggpo\_start\_synctest 

```C++
static GGPO_API GGPOErrorCode __cdecl GGPONet::ggpo_start_synctest (
    GGPOSession ** session,
    GGPOSessionCallbacks * cb,
    const char * game,
    int num_players,
    int input_size,
    int frames
) 
```




<hr>



### function ggpo\_synchronize\_input 

```C++
static GGPO_API GGPOErrorCode __cdecl GGPONet::ggpo_synchronize_input (
    GGPOSession * ggpo,
    void * values,
    int size,
    int * disconnect_flags
) 
```




<hr>



### function ggpo\_try\_synchronize\_local 

```C++
static GGPO_API GGPOErrorCode __cdecl GGPONet::ggpo_try_synchronize_local (
    GGPOSession * ggpo
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/GGPOUE4/Public/include/ggponet.h`

