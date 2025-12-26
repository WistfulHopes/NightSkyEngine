

# Struct UdpProtocol::Event



[**ClassList**](annotated.md) **>** [**UdpProtocol**](class_udp_protocol.md) **>** [**Event**](struct_udp_protocol_1_1_event.md)






















## Public Types

| Type | Name |
| ---: | :--- |
| enum  | [**Type**](#enum-type)  <br> |




## Public Attributes

| Type | Name |
| ---: | :--- |
|  int | [**count**](#variable-count)  <br> |
|  int | [**disconnect\_timeout**](#variable-disconnect_timeout)  <br> |
|  [**GameInput**](struct_game_input.md) | [**input**](#variable-input-12)  <br> |
|  struct [**UdpProtocol::Event**](struct_udp_protocol_1_1_event.md) | [**input**](#variable-input-22)  <br> |
|  struct [**UdpProtocol::Event**](struct_udp_protocol_1_1_event.md) | [**network\_interrupted**](#variable-network_interrupted)  <br> |
|  struct [**UdpProtocol::Event**](struct_udp_protocol_1_1_event.md) | [**synchronizing**](#variable-synchronizing)  <br> |
|  int | [**total**](#variable-total)  <br> |
|  Type | [**type**](#variable-type)  <br> |
|  union [**UdpProtocol::Event**](struct_udp_protocol_1_1_event.md) | [**u**](#variable-u)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Event**](#function-event) (Type t=Unknown) <br> |




























## Public Types Documentation




### enum Type 

```C++
enum UdpProtocol::Event::Type {
    Unknown = -1,
    Connected,
    Synchronizing,
    Synchronzied,
    Input,
    Disconnected,
    NetworkInterrupted,
    NetworkResumed
};
```




<hr>
## Public Attributes Documentation




### variable count 

```C++
int UdpProtocol::Event::count;
```




<hr>



### variable disconnect\_timeout 

```C++
int UdpProtocol::Event::disconnect_timeout;
```




<hr>



### variable input [1/2]

```C++
GameInput UdpProtocol::Event::input;
```




<hr>



### variable input [2/2]

```C++
struct UdpProtocol::Event UdpProtocol::Event::input;
```




<hr>



### variable network\_interrupted 

```C++
struct UdpProtocol::Event UdpProtocol::Event::network_interrupted;
```




<hr>



### variable synchronizing 

```C++
struct UdpProtocol::Event UdpProtocol::Event::synchronizing;
```




<hr>



### variable total 

```C++
int UdpProtocol::Event::total;
```




<hr>



### variable type 

```C++
Type UdpProtocol::Event::type;
```




<hr>



### variable u 

```C++
union UdpProtocol::Event UdpProtocol::Event::u;
```




<hr>
## Public Functions Documentation




### function Event 

```C++
inline UdpProtocol::Event::Event (
    Type t=Unknown
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/GGPOUE4/Private/network/udp_proto.h`

