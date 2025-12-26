

# Class SpectatorBackend



[**ClassList**](annotated.md) **>** [**SpectatorBackend**](class_spectator_backend.md)








Inherits the following classes: [GGPOSession](struct_g_g_p_o_session.md),  [IPollSink](class_i_poll_sink.md),  [Udp::Callbacks](struct_udp_1_1_callbacks.md)






























































































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual GGPOErrorCode | [**AddLocalInput**](#function-addlocalinput) (GGPOPlayerHandle player, void \* values, int size) <br> |
| virtual GGPOErrorCode | [**AddPlayer**](#function-addplayer) ([**GGPOPlayer**](struct_g_g_p_o_player.md) \* player, GGPOPlayerHandle \* handle) <br> |
| virtual GGPOErrorCode | [**DisconnectPlayer**](#function-disconnectplayer) (GGPOPlayerHandle handle) <br> |
| virtual GGPOErrorCode | [**DoPoll**](#function-dopoll) (int timeout) <br> |
| virtual GGPOErrorCode | [**GetNetworkStats**](#function-getnetworkstats) ([**FGGPONetworkStats**](struct_f_g_g_p_o_network_stats.md) \* stats, GGPOPlayerHandle handle) <br> |
| virtual GGPOErrorCode | [**IncrementFrame**](#function-incrementframe) (void) <br> |
| virtual void | [**OnMsg**](#function-onmsg) (int connection\_id, [**UdpMsg**](struct_udp_msg.md) \* msg, int len) <br> |
| virtual GGPOErrorCode | [**SetDisconnectNotifyStart**](#function-setdisconnectnotifystart) (int timeout) <br> |
| virtual GGPOErrorCode | [**SetDisconnectTimeout**](#function-setdisconnecttimeout) (int timeout) <br> |
| virtual GGPOErrorCode | [**SetFrameDelay**](#function-setframedelay) (GGPOPlayerHandle player, int delay) <br> |
|   | [**SpectatorBackend**](#function-spectatorbackend) ([**GGPOSessionCallbacks**](struct_g_g_p_o_session_callbacks.md) \* cb, const char \* gamename, [**ConnectionManager**](class_connection_manager.md) \* connection\_manager, int num\_players, int input\_size, int connection\_id) <br> |
| virtual GGPOErrorCode | [**SyncInput**](#function-syncinput) (void \* values, int size, int \* disconnect\_flags) <br> |
| virtual  | [**~SpectatorBackend**](#function-spectatorbackend) () <br> |


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


## Public Functions inherited from IPollSink

See [IPollSink](class_i_poll_sink.md)

| Type | Name |
| ---: | :--- |
| virtual bool | [**OnHandlePoll**](class_i_poll_sink.md#function-onhandlepoll) (void \*) <br> |
| virtual bool | [**OnLoopPoll**](class_i_poll_sink.md#function-onlooppoll) (void \*) <br> |
| virtual bool | [**OnMsgPoll**](class_i_poll_sink.md#function-onmsgpoll) (void \*) <br> |
| virtual bool | [**OnPeriodicPoll**](class_i_poll_sink.md#function-onperiodicpoll) (void \*, int) <br> |
| virtual  | [**~IPollSink**](class_i_poll_sink.md#function-ipollsink) () <br> |


## Public Functions inherited from Udp::Callbacks

See [Udp::Callbacks](struct_udp_1_1_callbacks.md)

| Type | Name |
| ---: | :--- |
| virtual void | [**OnMsg**](struct_udp_1_1_callbacks.md#function-onmsg) (int connection\_id, [**UdpMsg**](struct_udp_msg.md) \* msg, int len) = 0<br> |
| virtual  | [**~Callbacks**](struct_udp_1_1_callbacks.md#function-callbacks) () <br> |


























## Protected Attributes

| Type | Name |
| ---: | :--- |
|  [**GGPOSessionCallbacks**](struct_g_g_p_o_session_callbacks.md) | [**\_callbacks**](#variable-_callbacks)  <br> |
|  [**UdpProtocol**](class_udp_protocol.md) | [**\_host**](#variable-_host)  <br> |
|  int | [**\_input\_size**](#variable-_input_size)  <br> |
|  [**GameInput**](struct_game_input.md) | [**\_inputs**](#variable-_inputs)  <br> |
|  int | [**\_next\_input\_to\_send**](#variable-_next_input_to_send)  <br> |
|  int | [**\_num\_players**](#variable-_num_players)  <br> |
|  [**Poll**](class_poll.md) | [**\_poll**](#variable-_poll)  <br> |
|  bool | [**\_synchronizing**](#variable-_synchronizing)  <br> |
|  [**Udp**](class_udp.md) | [**\_udp**](#variable-_udp)  <br> |
































































## Protected Functions

| Type | Name |
| ---: | :--- |
|  void | [**CheckInitialSync**](#function-checkinitialsync) (void) <br> |
|  void | [**OnUdpProtocolEvent**](#function-onudpprotocolevent) ([**UdpProtocol::Event**](struct_udp_protocol_1_1_event.md) & e) <br> |
|  void | [**PollUdpProtocolEvents**](#function-polludpprotocolevents) (void) <br> |
















## Public Functions Documentation




### function AddLocalInput 

```C++
inline virtual GGPOErrorCode SpectatorBackend::AddLocalInput (
    GGPOPlayerHandle player,
    void * values,
    int size
) 
```



Implements [*GGPOSession::AddLocalInput*](struct_g_g_p_o_session.md#function-addlocalinput)


<hr>



### function AddPlayer 

```C++
inline virtual GGPOErrorCode SpectatorBackend::AddPlayer (
    GGPOPlayer * player,
    GGPOPlayerHandle * handle
) 
```



Implements [*GGPOSession::AddPlayer*](struct_g_g_p_o_session.md#function-addplayer)


<hr>



### function DisconnectPlayer 

```C++
inline virtual GGPOErrorCode SpectatorBackend::DisconnectPlayer (
    GGPOPlayerHandle handle
) 
```



Implements [*GGPOSession::DisconnectPlayer*](struct_g_g_p_o_session.md#function-disconnectplayer)


<hr>



### function DoPoll 

```C++
virtual GGPOErrorCode SpectatorBackend::DoPoll (
    int timeout
) 
```



Implements [*GGPOSession::DoPoll*](struct_g_g_p_o_session.md#function-dopoll)


<hr>



### function GetNetworkStats 

```C++
inline virtual GGPOErrorCode SpectatorBackend::GetNetworkStats (
    FGGPONetworkStats * stats,
    GGPOPlayerHandle handle
) 
```



Implements [*GGPOSession::GetNetworkStats*](struct_g_g_p_o_session.md#function-getnetworkstats)


<hr>



### function IncrementFrame 

```C++
virtual GGPOErrorCode SpectatorBackend::IncrementFrame (
    void
) 
```



Implements [*GGPOSession::IncrementFrame*](struct_g_g_p_o_session.md#function-incrementframe)


<hr>



### function OnMsg 

```C++
virtual void SpectatorBackend::OnMsg (
    int connection_id,
    UdpMsg * msg,
    int len
) 
```



Implements [*Udp::Callbacks::OnMsg*](struct_udp_1_1_callbacks.md#function-onmsg)


<hr>



### function SetDisconnectNotifyStart 

```C++
inline virtual GGPOErrorCode SpectatorBackend::SetDisconnectNotifyStart (
    int timeout
) 
```



Implements [*GGPOSession::SetDisconnectNotifyStart*](struct_g_g_p_o_session.md#function-setdisconnectnotifystart)


<hr>



### function SetDisconnectTimeout 

```C++
inline virtual GGPOErrorCode SpectatorBackend::SetDisconnectTimeout (
    int timeout
) 
```



Implements [*GGPOSession::SetDisconnectTimeout*](struct_g_g_p_o_session.md#function-setdisconnecttimeout)


<hr>



### function SetFrameDelay 

```C++
inline virtual GGPOErrorCode SpectatorBackend::SetFrameDelay (
    GGPOPlayerHandle player,
    int delay
) 
```



Implements [*GGPOSession::SetFrameDelay*](struct_g_g_p_o_session.md#function-setframedelay)


<hr>



### function SpectatorBackend 

```C++
SpectatorBackend::SpectatorBackend (
    GGPOSessionCallbacks * cb,
    const char * gamename,
    ConnectionManager * connection_manager,
    int num_players,
    int input_size,
    int connection_id
) 
```




<hr>



### function SyncInput 

```C++
virtual GGPOErrorCode SpectatorBackend::SyncInput (
    void * values,
    int size,
    int * disconnect_flags
) 
```



Implements [*GGPOSession::SyncInput*](struct_g_g_p_o_session.md#function-syncinput)


<hr>



### function ~SpectatorBackend 

```C++
virtual SpectatorBackend::~SpectatorBackend () 
```




<hr>
## Protected Attributes Documentation




### variable \_callbacks 

```C++
GGPOSessionCallbacks SpectatorBackend::_callbacks;
```




<hr>



### variable \_host 

```C++
UdpProtocol SpectatorBackend::_host;
```




<hr>



### variable \_input\_size 

```C++
int SpectatorBackend::_input_size;
```




<hr>



### variable \_inputs 

```C++
GameInput SpectatorBackend::_inputs[SPECTATOR_FRAME_BUFFER_SIZE];
```




<hr>



### variable \_next\_input\_to\_send 

```C++
int SpectatorBackend::_next_input_to_send;
```




<hr>



### variable \_num\_players 

```C++
int SpectatorBackend::_num_players;
```




<hr>



### variable \_poll 

```C++
Poll SpectatorBackend::_poll;
```




<hr>



### variable \_synchronizing 

```C++
bool SpectatorBackend::_synchronizing;
```




<hr>



### variable \_udp 

```C++
Udp SpectatorBackend::_udp;
```




<hr>
## Protected Functions Documentation




### function CheckInitialSync 

```C++
void SpectatorBackend::CheckInitialSync (
    void
) 
```




<hr>



### function OnUdpProtocolEvent 

```C++
void SpectatorBackend::OnUdpProtocolEvent (
    UdpProtocol::Event & e
) 
```




<hr>



### function PollUdpProtocolEvents 

```C++
void SpectatorBackend::PollUdpProtocolEvents (
    void
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/GGPOUE4/Private/backends/spectator.h`

