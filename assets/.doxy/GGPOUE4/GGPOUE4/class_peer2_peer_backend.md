

# Class Peer2PeerBackend



[**ClassList**](annotated.md) **>** [**Peer2PeerBackend**](class_peer2_peer_backend.md)








Inherits the following classes: [GGPOSession](struct_g_g_p_o_session.md),  [IPollSink](class_i_poll_sink.md),  [Udp::Callbacks](struct_udp_1_1_callbacks.md)






























## Public Attributes

| Type | Name |
| ---: | :--- |
|  int | [**remoteplayerId**](#variable-remoteplayerid)  <br> |
|  int | [**remoteplayerQueueu**](#variable-remoteplayerqueueu)  <br> |
































































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual GGPOErrorCode | [**AddLocalInput**](#function-addlocalinput) (GGPOPlayerHandle player, void \* values, int size) <br> |
| virtual GGPOErrorCode | [**AddPlayer**](#function-addplayer) ([**GGPOPlayer**](struct_g_g_p_o_player.md) \* player, GGPOPlayerHandle \* handle) <br> |
| virtual GGPOErrorCode | [**DisconnectPlayer**](#function-disconnectplayer) (GGPOPlayerHandle handle) <br> |
| virtual GGPOErrorCode | [**DoPoll**](#function-dopoll) (int timeout) <br> |
| virtual GGPOErrorCode | [**GetNetworkStats**](#function-getnetworkstats) ([**FGGPONetworkStats**](struct_f_g_g_p_o_network_stats.md) \* stats, GGPOPlayerHandle handle) override<br> |
| virtual GGPOErrorCode | [**IncrementFrame**](#function-incrementframe) (void) <br> |
| virtual void | [**OnMsg**](#function-onmsg) (int connection\_id, [**UdpMsg**](struct_udp_msg.md) \* msg, int len) override<br> |
|   | [**Peer2PeerBackend**](#function-peer2peerbackend) ([**GGPOSessionCallbacks**](struct_g_g_p_o_session_callbacks.md) \* cb, const char \* gamename, [**ConnectionManager**](class_connection_manager.md) \* connection\_manager, int num\_players, int input\_size) <br> |
| virtual GGPOErrorCode | [**SetDisconnectNotifyStart**](#function-setdisconnectnotifystart) (int timeout) <br> |
| virtual GGPOErrorCode | [**SetDisconnectTimeout**](#function-setdisconnecttimeout) (int timeout) <br> |
| virtual GGPOErrorCode | [**SetFrameDelay**](#function-setframedelay) (GGPOPlayerHandle player, int delay) <br> |
| virtual GGPOErrorCode | [**SyncInput**](#function-syncinput) (void \* values, int size, int \* disconnect\_flags) <br> |
| virtual GGPOErrorCode | [**TrySynchronizeLocal**](#function-trysynchronizelocal) () override<br> |
| virtual  | [**~Peer2PeerBackend**](#function-peer2peerbackend) () <br> |


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
|  int | [**\_disconnect\_notify\_start**](#variable-_disconnect_notify_start)  <br> |
|  int | [**\_disconnect\_timeout**](#variable-_disconnect_timeout)  <br> |
|  [**UdpProtocol**](class_udp_protocol.md) \* | [**\_endpoints**](#variable-_endpoints)  <br> |
|  int | [**\_input\_size**](#variable-_input_size)  <br> |
|  [**UdpMsg::connect\_status**](struct_udp_msg_1_1connect__status.md) | [**\_local\_connect\_status**](#variable-_local_connect_status)  <br> |
|  int | [**\_next\_recommended\_sleep**](#variable-_next_recommended_sleep)  <br> |
|  int | [**\_next\_spectator\_frame**](#variable-_next_spectator_frame)  <br> |
|  int | [**\_num\_players**](#variable-_num_players)  <br> |
|  int | [**\_num\_spectators**](#variable-_num_spectators)  <br> |
|  [**Poll**](class_poll.md) | [**\_poll**](#variable-_poll)  <br> |
|  [**UdpProtocol**](class_udp_protocol.md) | [**\_spectators**](#variable-_spectators)  <br> |
|  [**Sync**](class_sync.md) | [**\_sync**](#variable-_sync)  <br> |
|  bool | [**\_synchronizing**](#variable-_synchronizing)  <br> |
|  [**Udp**](class_udp.md) | [**\_udp**](#variable-_udp)  <br> |
































































## Protected Functions

| Type | Name |
| ---: | :--- |
|  void | [**AddRemotePlayer**](#function-addremoteplayer) (int connection\_id, int queue) <br> |
|  GGPOErrorCode | [**AddSpectator**](#function-addspectator) (int connection\_id) <br> |
|  void | [**CheckInitialSync**](#function-checkinitialsync) (void) <br> |
|  void | [**DisconnectPlayerQueue**](#function-disconnectplayerqueue) (int queue, int syncto) <br> |
| virtual void | [**OnSyncEvent**](#function-onsyncevent) ([**Sync::Event**](struct_sync_1_1_event.md) & e) <br> |
| virtual void | [**OnUdpProtocolEvent**](#function-onudpprotocolevent) ([**UdpProtocol::Event**](struct_udp_protocol_1_1_event.md) & e, GGPOPlayerHandle handle) <br> |
| virtual void | [**OnUdpProtocolPeerEvent**](#function-onudpprotocolpeerevent) ([**UdpProtocol::Event**](struct_udp_protocol_1_1_event.md) & e, int queue) <br> |
| virtual void | [**OnUdpProtocolSpectatorEvent**](#function-onudpprotocolspectatorevent) ([**UdpProtocol::Event**](struct_udp_protocol_1_1_event.md) & e, int queue) <br> |
|  GGPOErrorCode | [**PlayerHandleToQueue**](#function-playerhandletoqueue) (GGPOPlayerHandle player, int \* queue) <br> |
|  int | [**Poll2Players**](#function-poll2players) (int current\_frame) <br> |
|  int | [**PollNPlayers**](#function-pollnplayers) (int current\_frame) <br> |
|  void | [**PollSyncEvents**](#function-pollsyncevents) (void) <br> |
|  void | [**PollUdpProtocolEvents**](#function-polludpprotocolevents) (void) <br> |
|  GGPOPlayerHandle | [**QueueToPlayerHandle**](#function-queuetoplayerhandle) (int queue) <br> |
|  GGPOPlayerHandle | [**QueueToSpectatorHandle**](#function-queuetospectatorhandle) (int queue) <br> |
















## Public Attributes Documentation




### variable remoteplayerId 

```C++
int Peer2PeerBackend::remoteplayerId;
```




<hr>



### variable remoteplayerQueueu 

```C++
int Peer2PeerBackend::remoteplayerQueueu;
```




<hr>
## Public Functions Documentation




### function AddLocalInput 

```C++
virtual GGPOErrorCode Peer2PeerBackend::AddLocalInput (
    GGPOPlayerHandle player,
    void * values,
    int size
) 
```



Implements [*GGPOSession::AddLocalInput*](struct_g_g_p_o_session.md#function-addlocalinput)


<hr>



### function AddPlayer 

```C++
virtual GGPOErrorCode Peer2PeerBackend::AddPlayer (
    GGPOPlayer * player,
    GGPOPlayerHandle * handle
) 
```



Implements [*GGPOSession::AddPlayer*](struct_g_g_p_o_session.md#function-addplayer)


<hr>



### function DisconnectPlayer 

```C++
virtual GGPOErrorCode Peer2PeerBackend::DisconnectPlayer (
    GGPOPlayerHandle handle
) 
```



Implements [*GGPOSession::DisconnectPlayer*](struct_g_g_p_o_session.md#function-disconnectplayer)


<hr>



### function DoPoll 

```C++
virtual GGPOErrorCode Peer2PeerBackend::DoPoll (
    int timeout
) 
```



Implements [*GGPOSession::DoPoll*](struct_g_g_p_o_session.md#function-dopoll)


<hr>



### function GetNetworkStats 

```C++
virtual GGPOErrorCode Peer2PeerBackend::GetNetworkStats (
    FGGPONetworkStats * stats,
    GGPOPlayerHandle handle
) override
```



Implements [*GGPOSession::GetNetworkStats*](struct_g_g_p_o_session.md#function-getnetworkstats)


<hr>



### function IncrementFrame 

```C++
virtual GGPOErrorCode Peer2PeerBackend::IncrementFrame (
    void
) 
```



Implements [*GGPOSession::IncrementFrame*](struct_g_g_p_o_session.md#function-incrementframe)


<hr>



### function OnMsg 

```C++
virtual void Peer2PeerBackend::OnMsg (
    int connection_id,
    UdpMsg * msg,
    int len
) override
```



Implements [*Udp::Callbacks::OnMsg*](struct_udp_1_1_callbacks.md#function-onmsg)


<hr>



### function Peer2PeerBackend 

```C++
Peer2PeerBackend::Peer2PeerBackend (
    GGPOSessionCallbacks * cb,
    const char * gamename,
    ConnectionManager * connection_manager,
    int num_players,
    int input_size
) 
```




<hr>



### function SetDisconnectNotifyStart 

```C++
virtual GGPOErrorCode Peer2PeerBackend::SetDisconnectNotifyStart (
    int timeout
) 
```



Implements [*GGPOSession::SetDisconnectNotifyStart*](struct_g_g_p_o_session.md#function-setdisconnectnotifystart)


<hr>



### function SetDisconnectTimeout 

```C++
virtual GGPOErrorCode Peer2PeerBackend::SetDisconnectTimeout (
    int timeout
) 
```



Implements [*GGPOSession::SetDisconnectTimeout*](struct_g_g_p_o_session.md#function-setdisconnecttimeout)


<hr>



### function SetFrameDelay 

```C++
virtual GGPOErrorCode Peer2PeerBackend::SetFrameDelay (
    GGPOPlayerHandle player,
    int delay
) 
```



Implements [*GGPOSession::SetFrameDelay*](struct_g_g_p_o_session.md#function-setframedelay)


<hr>



### function SyncInput 

```C++
virtual GGPOErrorCode Peer2PeerBackend::SyncInput (
    void * values,
    int size,
    int * disconnect_flags
) 
```



Implements [*GGPOSession::SyncInput*](struct_g_g_p_o_session.md#function-syncinput)


<hr>



### function TrySynchronizeLocal 

```C++
virtual GGPOErrorCode Peer2PeerBackend::TrySynchronizeLocal () override
```



Implements [*GGPOSession::TrySynchronizeLocal*](struct_g_g_p_o_session.md#function-trysynchronizelocal)


<hr>



### function ~Peer2PeerBackend 

```C++
virtual Peer2PeerBackend::~Peer2PeerBackend () 
```




<hr>
## Protected Attributes Documentation




### variable \_callbacks 

```C++
GGPOSessionCallbacks Peer2PeerBackend::_callbacks;
```




<hr>



### variable \_disconnect\_notify\_start 

```C++
int Peer2PeerBackend::_disconnect_notify_start;
```




<hr>



### variable \_disconnect\_timeout 

```C++
int Peer2PeerBackend::_disconnect_timeout;
```




<hr>



### variable \_endpoints 

```C++
UdpProtocol* Peer2PeerBackend::_endpoints;
```




<hr>



### variable \_input\_size 

```C++
int Peer2PeerBackend::_input_size;
```




<hr>



### variable \_local\_connect\_status 

```C++
UdpMsg::connect_status Peer2PeerBackend::_local_connect_status[UDP_MSG_MAX_PLAYERS];
```




<hr>



### variable \_next\_recommended\_sleep 

```C++
int Peer2PeerBackend::_next_recommended_sleep;
```




<hr>



### variable \_next\_spectator\_frame 

```C++
int Peer2PeerBackend::_next_spectator_frame;
```




<hr>



### variable \_num\_players 

```C++
int Peer2PeerBackend::_num_players;
```




<hr>



### variable \_num\_spectators 

```C++
int Peer2PeerBackend::_num_spectators;
```




<hr>



### variable \_poll 

```C++
Poll Peer2PeerBackend::_poll;
```




<hr>



### variable \_spectators 

```C++
UdpProtocol Peer2PeerBackend::_spectators[GGPO_MAX_SPECTATORS];
```




<hr>



### variable \_sync 

```C++
Sync Peer2PeerBackend::_sync;
```




<hr>



### variable \_synchronizing 

```C++
bool Peer2PeerBackend::_synchronizing;
```




<hr>



### variable \_udp 

```C++
Udp Peer2PeerBackend::_udp;
```




<hr>
## Protected Functions Documentation




### function AddRemotePlayer 

```C++
void Peer2PeerBackend::AddRemotePlayer (
    int connection_id,
    int queue
) 
```




<hr>



### function AddSpectator 

```C++
GGPOErrorCode Peer2PeerBackend::AddSpectator (
    int connection_id
) 
```




<hr>



### function CheckInitialSync 

```C++
void Peer2PeerBackend::CheckInitialSync (
    void
) 
```




<hr>



### function DisconnectPlayerQueue 

```C++
void Peer2PeerBackend::DisconnectPlayerQueue (
    int queue,
    int syncto
) 
```




<hr>



### function OnSyncEvent 

```C++
inline virtual void Peer2PeerBackend::OnSyncEvent (
    Sync::Event & e
) 
```




<hr>



### function OnUdpProtocolEvent 

```C++
virtual void Peer2PeerBackend::OnUdpProtocolEvent (
    UdpProtocol::Event & e,
    GGPOPlayerHandle handle
) 
```




<hr>



### function OnUdpProtocolPeerEvent 

```C++
virtual void Peer2PeerBackend::OnUdpProtocolPeerEvent (
    UdpProtocol::Event & e,
    int queue
) 
```




<hr>



### function OnUdpProtocolSpectatorEvent 

```C++
virtual void Peer2PeerBackend::OnUdpProtocolSpectatorEvent (
    UdpProtocol::Event & e,
    int queue
) 
```




<hr>



### function PlayerHandleToQueue 

```C++
GGPOErrorCode Peer2PeerBackend::PlayerHandleToQueue (
    GGPOPlayerHandle player,
    int * queue
) 
```




<hr>



### function Poll2Players 

```C++
int Peer2PeerBackend::Poll2Players (
    int current_frame
) 
```




<hr>



### function PollNPlayers 

```C++
int Peer2PeerBackend::PollNPlayers (
    int current_frame
) 
```




<hr>



### function PollSyncEvents 

```C++
void Peer2PeerBackend::PollSyncEvents (
    void
) 
```




<hr>



### function PollUdpProtocolEvents 

```C++
void Peer2PeerBackend::PollUdpProtocolEvents (
    void
) 
```




<hr>



### function QueueToPlayerHandle 

```C++
inline GGPOPlayerHandle Peer2PeerBackend::QueueToPlayerHandle (
    int queue
) 
```




<hr>



### function QueueToSpectatorHandle 

```C++
inline GGPOPlayerHandle Peer2PeerBackend::QueueToSpectatorHandle (
    int queue
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/GGPOUE4/Private/backends/p2p.h`

