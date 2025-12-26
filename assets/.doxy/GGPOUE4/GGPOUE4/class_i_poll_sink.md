

# Class IPollSink



[**ClassList**](annotated.md) **>** [**IPollSink**](class_i_poll_sink.md)










Inherited by the following classes: [Peer2PeerBackend](class_peer2_peer_backend.md),  [SpectatorBackend](class_spectator_backend.md),  [Udp](class_udp.md),  [UdpProtocol](class_udp_protocol.md)
































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual bool | [**OnHandlePoll**](#function-onhandlepoll) (void \*) <br> |
| virtual bool | [**OnLoopPoll**](#function-onlooppoll) (void \*) <br> |
| virtual bool | [**OnMsgPoll**](#function-onmsgpoll) (void \*) <br> |
| virtual bool | [**OnPeriodicPoll**](#function-onperiodicpoll) (void \*, int) <br> |
| virtual  | [**~IPollSink**](#function-ipollsink) () <br> |




























## Public Functions Documentation




### function OnHandlePoll 

```C++
inline virtual bool IPollSink::OnHandlePoll (
    void *
) 
```




<hr>



### function OnLoopPoll 

```C++
inline virtual bool IPollSink::OnLoopPoll (
    void *
) 
```




<hr>



### function OnMsgPoll 

```C++
inline virtual bool IPollSink::OnMsgPoll (
    void *
) 
```




<hr>



### function OnPeriodicPoll 

```C++
inline virtual bool IPollSink::OnPeriodicPoll (
    void *,
    int
) 
```




<hr>



### function ~IPollSink 

```C++
inline virtual IPollSink::~IPollSink () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/GGPOUE4/Private/poll.h`

