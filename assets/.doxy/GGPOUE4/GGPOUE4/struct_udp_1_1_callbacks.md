

# Struct Udp::Callbacks



[**ClassList**](annotated.md) **>** [**Udp**](class_udp.md) **>** [**Callbacks**](struct_udp_1_1_callbacks.md)










Inherited by the following classes: [Peer2PeerBackend](class_peer2_peer_backend.md),  [SpectatorBackend](class_spectator_backend.md)
































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual void | [**OnMsg**](#function-onmsg) (int connection\_id, [**UdpMsg**](struct_udp_msg.md) \* msg, int len) = 0<br> |
| virtual  | [**~Callbacks**](#function-callbacks) () <br> |




























## Public Functions Documentation




### function OnMsg 

```C++
virtual void Udp::Callbacks::OnMsg (
    int connection_id,
    UdpMsg * msg,
    int len
) = 0
```




<hr>



### function ~Callbacks 

```C++
inline virtual Udp::Callbacks::~Callbacks () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/GGPOUE4/Private/network/udp.h`

