

# Class UdpProtocol



[**ClassList**](annotated.md) **>** [**UdpProtocol**](class_udp_protocol.md)








Inherits the following classes: [IPollSink](class_i_poll_sink.md)












## Classes

| Type | Name |
| ---: | :--- |
| struct | [**Event**](struct_udp_protocol_1_1_event.md) <br> |
| struct | [**Stats**](struct_udp_protocol_1_1_stats.md) <br> |










## Public Attributes

| Type | Name |
| ---: | :--- |
|  int | [**connection\_id**](#variable-connection_id)  <br> |
|  uint32 | [**last\_input\_packet\_recv\_time**](#variable-last_input_packet_recv_time)  <br> |
|  uint32 | [**last\_network\_stats\_interval**](#variable-last_network_stats_interval)  <br> |
|  uint32 | [**last\_quality\_report\_time**](#variable-last_quality_report_time)  <br> |
|  [**UdpMsg**](struct_udp_msg.md) \* | [**msg**](#variable-msg)  <br> |
|  uint32 | [**random**](#variable-random)  <br> |
|  uint32 | [**roundtrips\_remaining**](#variable-roundtrips_remaining)  <br> |
|  struct [**UdpProtocol**](class_udp_protocol.md) | [**running**](#variable-running)  <br> |
|  int | [**send\_time**](#variable-send_time)  <br> |
|  struct [**UdpProtocol**](class_udp_protocol.md) | [**sync**](#variable-sync)  <br> |
































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**Disconnect**](#function-disconnect) () <br> |
|  void | [**GGPONetworkStats**](#function-ggponetworkstats) ([**Stats**](struct_udp_protocol_1_1_stats.md) \* stats) <br> |
|  bool | [**GetEvent**](#function-getevent) ([**UdpProtocol::Event**](struct_udp_protocol_1_1_event.md) & e) <br> |
|  void | [**GetNetworkStats**](#function-getnetworkstats) (struct [**FGGPONetworkStats**](struct_f_g_g_p_o_network_stats.md) \* stats) <br> |
|  bool | [**GetPeerConnectStatus**](#function-getpeerconnectstatus) (int id, int \* frame) <br> |
|  bool | [**HandlesMsg**](#function-handlesmsg) (int connection\_id, [**UdpMsg**](struct_udp_msg.md) \* msg) <br> |
|  void | [**Init**](#function-init) ([**Udp**](class_udp.md) \* udp, [**Poll**](class_poll.md) & p, int queue, int connection\_id, [**UdpMsg::connect\_status**](struct_udp_msg_1_1connect__status.md) \* status) <br> |
|  bool | [**IsInitialized**](#function-isinitialized) () <br> |
|  bool | [**IsRunning**](#function-isrunning) () <br> |
|  bool | [**IsSynchronized**](#function-issynchronized) () <br> |
| virtual bool | [**OnLoopPoll**](#function-onlooppoll) (void \* cookie) <br> |
|  void | [**OnMsg**](#function-onmsg) ([**UdpMsg**](struct_udp_msg.md) \* msg, int len) <br> |
|  int | [**RecommendFrameDelay**](#function-recommendframedelay) () <br> |
|  void | [**SendInput**](#function-sendinput) ([**GameInput**](struct_game_input.md) & input) <br> |
|  void | [**SendInputAck**](#function-sendinputack) () <br> |
|  void | [**SetDisconnectNotifyStart**](#function-setdisconnectnotifystart) (int timeout) <br> |
|  void | [**SetDisconnectTimeout**](#function-setdisconnecttimeout) (int timeout) <br> |
|  void | [**SetLocalFrameNumber**](#function-setlocalframenumber) (int num) <br> |
|  void | [**Synchronize**](#function-synchronize) () <br> |
|   | [**UdpProtocol**](#function-udpprotocol) () <br> |
| virtual  | [**~UdpProtocol**](#function-udpprotocol) () <br> |


## Public Functions inherited from IPollSink

See [IPollSink](class_i_poll_sink.md)

| Type | Name |
| ---: | :--- |
| virtual bool | [**OnHandlePoll**](class_i_poll_sink.md#function-onhandlepoll) (void \*) <br> |
| virtual bool | [**OnLoopPoll**](class_i_poll_sink.md#function-onlooppoll) (void \*) <br> |
| virtual bool | [**OnMsgPoll**](class_i_poll_sink.md#function-onmsgpoll) (void \*) <br> |
| virtual bool | [**OnPeriodicPoll**](class_i_poll_sink.md#function-onperiodicpoll) (void \*, int) <br> |
| virtual  | [**~IPollSink**](class_i_poll_sink.md#function-ipollsink) () <br> |






## Protected Types

| Type | Name |
| ---: | :--- |
| enum  | [**State**](#enum-state)  <br> |








## Protected Attributes

| Type | Name |
| ---: | :--- |
|  int | [**\_bytes\_sent**](#variable-_bytes_sent)  <br> |
|  bool | [**\_connected**](#variable-_connected)  <br> |
|  int | [**\_connection\_id**](#variable-_connection_id)  <br> |
|  State | [**\_current\_state**](#variable-_current_state)  <br> |
|  unsigned int | [**\_disconnect\_event\_sent**](#variable-_disconnect_event_sent)  <br> |
|  bool | [**\_disconnect\_notify\_sent**](#variable-_disconnect_notify_sent)  <br> |
|  unsigned int | [**\_disconnect\_notify\_start**](#variable-_disconnect_notify_start)  <br> |
|  unsigned int | [**\_disconnect\_timeout**](#variable-_disconnect_timeout)  <br> |
|  [**RingBuffer**](class_ring_buffer.md)&lt; [**UdpProtocol::Event**](struct_udp_protocol_1_1_event.md), 64 &gt; | [**\_event\_queue**](#variable-_event_queue)  <br> |
|  int | [**\_kbps\_sent**](#variable-_kbps_sent)  <br> |
|  [**GameInput**](struct_game_input.md) | [**\_last\_acked\_input**](#variable-_last_acked_input)  <br> |
|  [**GameInput**](struct_game_input.md) | [**\_last\_received\_input**](#variable-_last_received_input)  <br> |
|  unsigned int | [**\_last\_recv\_time**](#variable-_last_recv_time)  <br> |
|  unsigned int | [**\_last\_send\_time**](#variable-_last_send_time)  <br> |
|  [**GameInput**](struct_game_input.md) | [**\_last\_sent\_input**](#variable-_last_sent_input)  <br> |
|  [**UdpMsg::connect\_status**](struct_udp_msg_1_1connect__status.md) \* | [**\_local\_connect\_status**](#variable-_local_connect_status)  <br> |
|  int | [**\_local\_frame\_advantage**](#variable-_local_frame_advantage)  <br> |
|  uint16 | [**\_magic\_number**](#variable-_magic_number)  <br> |
|  uint16 | [**\_next\_recv\_seq**](#variable-_next_recv_seq)  <br> |
|  uint16 | [**\_next\_send\_seq**](#variable-_next_send_seq)  <br> |
|  struct [**UdpProtocol**](class_udp_protocol.md) | [**\_oo\_packet**](#variable-_oo_packet)  <br> |
|  int | [**\_oop\_percent**](#variable-_oop_percent)  <br> |
|  int | [**\_packets\_sent**](#variable-_packets_sent)  <br> |
|  [**UdpMsg::connect\_status**](struct_udp_msg_1_1connect__status.md) | [**\_peer\_connect\_status**](#variable-_peer_connect_status)  <br> |
|  [**RingBuffer**](class_ring_buffer.md)&lt; [**GameInput**](struct_game_input.md), 64 &gt; | [**\_pending\_output**](#variable-_pending_output)  <br> |
|  int | [**\_queue**](#variable-_queue)  <br> |
|  int | [**\_remote\_frame\_advantage**](#variable-_remote_frame_advantage)  <br> |
|  uint16 | [**\_remote\_magic\_number**](#variable-_remote_magic_number)  <br> |
|  int | [**\_round\_trip\_time**](#variable-_round_trip_time)  <br> |
|  int | [**\_send\_latency**](#variable-_send_latency)  <br> |
|  [**RingBuffer**](class_ring_buffer.md)&lt; [**QueueEntry**](struct_udp_protocol_1_1_queue_entry.md), 64 &gt; | [**\_send\_queue**](#variable-_send_queue)  <br> |
|  unsigned int | [**\_shutdown\_timeout**](#variable-_shutdown_timeout)  <br> |
|  union [**UdpProtocol**](class_udp_protocol.md) | [**\_state**](#variable-_state)  <br> |
|  int | [**\_stats\_start\_time**](#variable-_stats_start_time)  <br> |
|  [**TimeSync**](class_time_sync.md) | [**\_timesync**](#variable-_timesync)  <br> |
|  [**Udp**](class_udp.md) \* | [**\_udp**](#variable-_udp)  <br> |
|  [**ConnectionManager**](class_connection_manager.md) \* | [**connection\_manager**](#variable-connection_manager)  <br> |
































## Protected Functions

| Type | Name |
| ---: | :--- |
|  void | [**ClearSendQueue**](#function-clearsendqueue) (void) <br> |
|  bool | [**CreateSocket**](#function-createsocket) (int retries) <br> |
|  void | [**DispatchMsg**](#function-dispatchmsg) (uint8 \* buffer, int len) <br> |
|  void | [**Log**](#function-log) (const char \* fmt, ...) <br> |
|  void | [**LogEvent**](#function-logevent) (const char \* prefix, const [**UdpProtocol::Event**](struct_udp_protocol_1_1_event.md) & evt) <br> |
|  void | [**LogMsg**](#function-logmsg) (const char \* prefix, [**UdpMsg**](struct_udp_msg.md) \* msg) <br> |
|  bool | [**OnInput**](#function-oninput) ([**UdpMsg**](struct_udp_msg.md) \* msg, int len) <br> |
|  bool | [**OnInputAck**](#function-oninputack) ([**UdpMsg**](struct_udp_msg.md) \* msg, int len) <br> |
|  bool | [**OnInvalid**](#function-oninvalid) ([**UdpMsg**](struct_udp_msg.md) \* msg, int len) <br> |
|  bool | [**OnKeepAlive**](#function-onkeepalive) ([**UdpMsg**](struct_udp_msg.md) \* msg, int len) <br> |
|  bool | [**OnQualityReply**](#function-onqualityreply) ([**UdpMsg**](struct_udp_msg.md) \* msg, int len) <br> |
|  bool | [**OnQualityReport**](#function-onqualityreport) ([**UdpMsg**](struct_udp_msg.md) \* msg, int len) <br> |
|  bool | [**OnSyncReply**](#function-onsyncreply) ([**UdpMsg**](struct_udp_msg.md) \* msg, int len) <br> |
|  bool | [**OnSyncRequest**](#function-onsyncrequest) ([**UdpMsg**](struct_udp_msg.md) \* msg, int len) <br> |
|  void | [**PumpSendQueue**](#function-pumpsendqueue) () <br> |
|  void | [**QueueEvent**](#function-queueevent) (const [**UdpProtocol::Event**](struct_udp_protocol_1_1_event.md) & evt) <br> |
|  void | [**SendMsg**](#function-sendmsg) ([**UdpMsg**](struct_udp_msg.md) \* msg) <br> |
|  void | [**SendPendingOutput**](#function-sendpendingoutput) () <br> |
|  void | [**SendSyncRequest**](#function-sendsyncrequest) () <br> |
|  void | [**UpdateNetworkStats**](#function-updatenetworkstats) (void) <br> |








## Public Attributes Documentation




### variable connection\_id 

```C++
int UdpProtocol::connection_id;
```




<hr>



### variable last\_input\_packet\_recv\_time 

```C++
uint32 UdpProtocol::last_input_packet_recv_time;
```




<hr>



### variable last\_network\_stats\_interval 

```C++
uint32 UdpProtocol::last_network_stats_interval;
```




<hr>



### variable last\_quality\_report\_time 

```C++
uint32 UdpProtocol::last_quality_report_time;
```




<hr>



### variable msg 

```C++
UdpMsg* UdpProtocol::msg;
```




<hr>



### variable random 

```C++
uint32 UdpProtocol::random;
```




<hr>



### variable roundtrips\_remaining 

```C++
uint32 UdpProtocol::roundtrips_remaining;
```




<hr>



### variable running 

```C++
struct UdpProtocol UdpProtocol::running;
```




<hr>



### variable send\_time 

```C++
int UdpProtocol::send_time;
```




<hr>



### variable sync 

```C++
struct UdpProtocol UdpProtocol::sync;
```




<hr>
## Public Functions Documentation




### function Disconnect 

```C++
void UdpProtocol::Disconnect () 
```




<hr>



### function GGPONetworkStats 

```C++
void UdpProtocol::GGPONetworkStats (
    Stats * stats
) 
```




<hr>



### function GetEvent 

```C++
bool UdpProtocol::GetEvent (
    UdpProtocol::Event & e
) 
```




<hr>



### function GetNetworkStats 

```C++
void UdpProtocol::GetNetworkStats (
    struct FGGPONetworkStats * stats
) 
```




<hr>



### function GetPeerConnectStatus 

```C++
bool UdpProtocol::GetPeerConnectStatus (
    int id,
    int * frame
) 
```




<hr>



### function HandlesMsg 

```C++
bool UdpProtocol::HandlesMsg (
    int connection_id,
    UdpMsg * msg
) 
```




<hr>



### function Init 

```C++
void UdpProtocol::Init (
    Udp * udp,
    Poll & p,
    int queue,
    int connection_id,
    UdpMsg::connect_status * status
) 
```




<hr>



### function IsInitialized 

```C++
inline bool UdpProtocol::IsInitialized () 
```




<hr>



### function IsRunning 

```C++
inline bool UdpProtocol::IsRunning () 
```




<hr>



### function IsSynchronized 

```C++
inline bool UdpProtocol::IsSynchronized () 
```




<hr>



### function OnLoopPoll 

```C++
virtual bool UdpProtocol::OnLoopPoll (
    void * cookie
) 
```



Implements [*IPollSink::OnLoopPoll*](class_i_poll_sink.md#function-onlooppoll)


<hr>



### function OnMsg 

```C++
void UdpProtocol::OnMsg (
    UdpMsg * msg,
    int len
) 
```




<hr>



### function RecommendFrameDelay 

```C++
int UdpProtocol::RecommendFrameDelay () 
```




<hr>



### function SendInput 

```C++
void UdpProtocol::SendInput (
    GameInput & input
) 
```




<hr>



### function SendInputAck 

```C++
void UdpProtocol::SendInputAck () 
```




<hr>



### function SetDisconnectNotifyStart 

```C++
void UdpProtocol::SetDisconnectNotifyStart (
    int timeout
) 
```




<hr>



### function SetDisconnectTimeout 

```C++
void UdpProtocol::SetDisconnectTimeout (
    int timeout
) 
```




<hr>



### function SetLocalFrameNumber 

```C++
void UdpProtocol::SetLocalFrameNumber (
    int num
) 
```




<hr>



### function Synchronize 

```C++
void UdpProtocol::Synchronize () 
```




<hr>



### function UdpProtocol 

```C++
UdpProtocol::UdpProtocol () 
```




<hr>



### function ~UdpProtocol 

```C++
virtual UdpProtocol::~UdpProtocol () 
```




<hr>
## Protected Types Documentation




### enum State 

```C++
enum UdpProtocol::State {
    Syncing,
    Synchronzied,
    Running,
    Disconnected
};
```




<hr>
## Protected Attributes Documentation




### variable \_bytes\_sent 

```C++
int UdpProtocol::_bytes_sent;
```




<hr>



### variable \_connected 

```C++
bool UdpProtocol::_connected;
```




<hr>



### variable \_connection\_id 

```C++
int UdpProtocol::_connection_id;
```




<hr>



### variable \_current\_state 

```C++
State UdpProtocol::_current_state;
```




<hr>



### variable \_disconnect\_event\_sent 

```C++
unsigned int UdpProtocol::_disconnect_event_sent;
```




<hr>



### variable \_disconnect\_notify\_sent 

```C++
bool UdpProtocol::_disconnect_notify_sent;
```




<hr>



### variable \_disconnect\_notify\_start 

```C++
unsigned int UdpProtocol::_disconnect_notify_start;
```




<hr>



### variable \_disconnect\_timeout 

```C++
unsigned int UdpProtocol::_disconnect_timeout;
```




<hr>



### variable \_event\_queue 

```C++
RingBuffer<UdpProtocol::Event, 64> UdpProtocol::_event_queue;
```




<hr>



### variable \_kbps\_sent 

```C++
int UdpProtocol::_kbps_sent;
```




<hr>



### variable \_last\_acked\_input 

```C++
GameInput UdpProtocol::_last_acked_input;
```




<hr>



### variable \_last\_received\_input 

```C++
GameInput UdpProtocol::_last_received_input;
```




<hr>



### variable \_last\_recv\_time 

```C++
unsigned int UdpProtocol::_last_recv_time;
```




<hr>



### variable \_last\_send\_time 

```C++
unsigned int UdpProtocol::_last_send_time;
```




<hr>



### variable \_last\_sent\_input 

```C++
GameInput UdpProtocol::_last_sent_input;
```




<hr>



### variable \_local\_connect\_status 

```C++
UdpMsg::connect_status* UdpProtocol::_local_connect_status;
```




<hr>



### variable \_local\_frame\_advantage 

```C++
int UdpProtocol::_local_frame_advantage;
```




<hr>



### variable \_magic\_number 

```C++
uint16 UdpProtocol::_magic_number;
```




<hr>



### variable \_next\_recv\_seq 

```C++
uint16 UdpProtocol::_next_recv_seq;
```




<hr>



### variable \_next\_send\_seq 

```C++
uint16 UdpProtocol::_next_send_seq;
```




<hr>



### variable \_oo\_packet 

```C++
struct UdpProtocol UdpProtocol::_oo_packet;
```




<hr>



### variable \_oop\_percent 

```C++
int UdpProtocol::_oop_percent;
```




<hr>



### variable \_packets\_sent 

```C++
int UdpProtocol::_packets_sent;
```




<hr>



### variable \_peer\_connect\_status 

```C++
UdpMsg::connect_status UdpProtocol::_peer_connect_status[UDP_MSG_MAX_PLAYERS];
```




<hr>



### variable \_pending\_output 

```C++
RingBuffer<GameInput, 64> UdpProtocol::_pending_output;
```




<hr>



### variable \_queue 

```C++
int UdpProtocol::_queue;
```




<hr>



### variable \_remote\_frame\_advantage 

```C++
int UdpProtocol::_remote_frame_advantage;
```




<hr>



### variable \_remote\_magic\_number 

```C++
uint16 UdpProtocol::_remote_magic_number;
```




<hr>



### variable \_round\_trip\_time 

```C++
int UdpProtocol::_round_trip_time;
```




<hr>



### variable \_send\_latency 

```C++
int UdpProtocol::_send_latency;
```




<hr>



### variable \_send\_queue 

```C++
RingBuffer<QueueEntry, 64> UdpProtocol::_send_queue;
```




<hr>



### variable \_shutdown\_timeout 

```C++
unsigned int UdpProtocol::_shutdown_timeout;
```




<hr>



### variable \_state 

```C++
union UdpProtocol UdpProtocol::_state;
```




<hr>



### variable \_stats\_start\_time 

```C++
int UdpProtocol::_stats_start_time;
```




<hr>



### variable \_timesync 

```C++
TimeSync UdpProtocol::_timesync;
```




<hr>



### variable \_udp 

```C++
Udp* UdpProtocol::_udp;
```




<hr>



### variable connection\_manager 

```C++
ConnectionManager* UdpProtocol::connection_manager;
```




<hr>
## Protected Functions Documentation




### function ClearSendQueue 

```C++
void UdpProtocol::ClearSendQueue (
    void
) 
```




<hr>



### function CreateSocket 

```C++
bool UdpProtocol::CreateSocket (
    int retries
) 
```




<hr>



### function DispatchMsg 

```C++
void UdpProtocol::DispatchMsg (
    uint8 * buffer,
    int len
) 
```




<hr>



### function Log 

```C++
void UdpProtocol::Log (
    const char * fmt,
    ...
) 
```




<hr>



### function LogEvent 

```C++
void UdpProtocol::LogEvent (
    const char * prefix,
    const UdpProtocol::Event & evt
) 
```




<hr>



### function LogMsg 

```C++
void UdpProtocol::LogMsg (
    const char * prefix,
    UdpMsg * msg
) 
```




<hr>



### function OnInput 

```C++
bool UdpProtocol::OnInput (
    UdpMsg * msg,
    int len
) 
```




<hr>



### function OnInputAck 

```C++
bool UdpProtocol::OnInputAck (
    UdpMsg * msg,
    int len
) 
```




<hr>



### function OnInvalid 

```C++
bool UdpProtocol::OnInvalid (
    UdpMsg * msg,
    int len
) 
```




<hr>



### function OnKeepAlive 

```C++
bool UdpProtocol::OnKeepAlive (
    UdpMsg * msg,
    int len
) 
```




<hr>



### function OnQualityReply 

```C++
bool UdpProtocol::OnQualityReply (
    UdpMsg * msg,
    int len
) 
```




<hr>



### function OnQualityReport 

```C++
bool UdpProtocol::OnQualityReport (
    UdpMsg * msg,
    int len
) 
```




<hr>



### function OnSyncReply 

```C++
bool UdpProtocol::OnSyncReply (
    UdpMsg * msg,
    int len
) 
```




<hr>



### function OnSyncRequest 

```C++
bool UdpProtocol::OnSyncRequest (
    UdpMsg * msg,
    int len
) 
```




<hr>



### function PumpSendQueue 

```C++
void UdpProtocol::PumpSendQueue () 
```




<hr>



### function QueueEvent 

```C++
void UdpProtocol::QueueEvent (
    const UdpProtocol::Event & evt
) 
```




<hr>



### function SendMsg 

```C++
void UdpProtocol::SendMsg (
    UdpMsg * msg
) 
```




<hr>



### function SendPendingOutput 

```C++
void UdpProtocol::SendPendingOutput () 
```




<hr>



### function SendSyncRequest 

```C++
void UdpProtocol::SendSyncRequest () 
```




<hr>



### function UpdateNetworkStats 

```C++
void UdpProtocol::UpdateNetworkStats (
    void
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/GGPOUE4/Private/network/udp_proto.h`

