

# Struct UdpMsg



[**ClassList**](annotated.md) **>** [**UdpMsg**](struct_udp_msg.md)




















## Classes

| Type | Name |
| ---: | :--- |
| struct | [**connect\_status**](struct_udp_msg_1_1connect__status.md) <br> |


## Public Types

| Type | Name |
| ---: | :--- |
| enum  | [**MsgType**](#enum-msgtype)  <br> |




## Public Attributes

| Type | Name |
| ---: | :--- |
|  int | [**ack\_frame**](#variable-ack_frame)  <br> |
|  uint8 | [**bits**](#variable-bits)  <br> |
|  int | [**disconnect\_requested**](#variable-disconnect_requested)  <br> |
|  int8 | [**frame\_advantage**](#variable-frame_advantage)  <br> |
|  struct [**UdpMsg**](struct_udp_msg.md) | [**hdr**](#variable-hdr)  <br> |
|  struct [**UdpMsg**](struct_udp_msg.md) | [**input**](#variable-input)  <br> |
|  struct [**UdpMsg**](struct_udp_msg.md) | [**input\_ack**](#variable-input_ack)  <br> |
|  uint8 | [**input\_size**](#variable-input_size)  <br> |
|  uint16 | [**magic**](#variable-magic)  <br> |
|  uint16 | [**num\_bits**](#variable-num_bits)  <br> |
|  [**connect\_status**](struct_udp_msg_1_1connect__status.md) | [**peer\_connect\_status**](#variable-peer_connect_status)  <br> |
|  uint32 | [**ping**](#variable-ping)  <br> |
|  uint32 | [**pong**](#variable-pong)  <br> |
|  struct [**UdpMsg**](struct_udp_msg.md) | [**quality\_reply**](#variable-quality_reply)  <br> |
|  struct [**UdpMsg**](struct_udp_msg.md) | [**quality\_report**](#variable-quality_report)  <br> |
|  uint32 | [**random\_reply**](#variable-random_reply)  <br> |
|  uint32 | [**random\_request**](#variable-random_request)  <br> |
|  uint8 | [**remote\_endpoint**](#variable-remote_endpoint)  <br> |
|  uint16 | [**remote\_magic**](#variable-remote_magic)  <br> |
|  uint16 | [**sequence\_number**](#variable-sequence_number)  <br> |
|  uint32 | [**start\_frame**](#variable-start_frame)  <br> |
|  struct [**UdpMsg**](struct_udp_msg.md) | [**sync\_reply**](#variable-sync_reply)  <br> |
|  struct [**UdpMsg**](struct_udp_msg.md) | [**sync\_request**](#variable-sync_request)  <br> |
|  uint8 | [**type**](#variable-type)  <br> |
|  union [**UdpMsg**](struct_udp_msg.md) | [**u**](#variable-u)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  int | [**PacketSize**](#function-packetsize) () <br> |
|  int | [**PayloadSize**](#function-payloadsize) () <br> |
|   | [**UdpMsg**](#function-udpmsg) (MsgType t) <br> |




























## Public Types Documentation




### enum MsgType 

```C++
enum UdpMsg::MsgType {
    Invalid = 0,
    SyncRequest = 1,
    SyncReply = 2,
    Input = 3,
    QualityReport = 4,
    QualityReply = 5,
    KeepAlive = 6,
    InputAck = 7
};
```




<hr>
## Public Attributes Documentation




### variable ack\_frame 

```C++
int UdpMsg::ack_frame;
```




<hr>



### variable bits 

```C++
uint8 UdpMsg::bits[MAX_COMPRESSED_BITS];
```




<hr>



### variable disconnect\_requested 

```C++
int UdpMsg::disconnect_requested;
```




<hr>



### variable frame\_advantage 

```C++
int8 UdpMsg::frame_advantage;
```




<hr>



### variable hdr 

```C++
struct UdpMsg UdpMsg::hdr;
```




<hr>



### variable input 

```C++
struct UdpMsg UdpMsg::input;
```




<hr>



### variable input\_ack 

```C++
struct UdpMsg UdpMsg::input_ack;
```




<hr>



### variable input\_size 

```C++
uint8 UdpMsg::input_size;
```




<hr>



### variable magic 

```C++
uint16 UdpMsg::magic;
```




<hr>



### variable num\_bits 

```C++
uint16 UdpMsg::num_bits;
```




<hr>



### variable peer\_connect\_status 

```C++
connect_status UdpMsg::peer_connect_status[UDP_MSG_MAX_PLAYERS];
```




<hr>



### variable ping 

```C++
uint32 UdpMsg::ping;
```




<hr>



### variable pong 

```C++
uint32 UdpMsg::pong;
```




<hr>



### variable quality\_reply 

```C++
struct UdpMsg UdpMsg::quality_reply;
```




<hr>



### variable quality\_report 

```C++
struct UdpMsg UdpMsg::quality_report;
```




<hr>



### variable random\_reply 

```C++
uint32 UdpMsg::random_reply;
```




<hr>



### variable random\_request 

```C++
uint32 UdpMsg::random_request;
```




<hr>



### variable remote\_endpoint 

```C++
uint8 UdpMsg::remote_endpoint;
```




<hr>



### variable remote\_magic 

```C++
uint16 UdpMsg::remote_magic;
```




<hr>



### variable sequence\_number 

```C++
uint16 UdpMsg::sequence_number;
```




<hr>



### variable start\_frame 

```C++
uint32 UdpMsg::start_frame;
```




<hr>



### variable sync\_reply 

```C++
struct UdpMsg UdpMsg::sync_reply;
```




<hr>



### variable sync\_request 

```C++
struct UdpMsg UdpMsg::sync_request;
```




<hr>



### variable type 

```C++
uint8 UdpMsg::type;
```




<hr>



### variable u 

```C++
union UdpMsg UdpMsg::u;
```




<hr>
## Public Functions Documentation




### function PacketSize 

```C++
inline int UdpMsg::PacketSize () 
```




<hr>



### function PayloadSize 

```C++
inline int UdpMsg::PayloadSize () 
```




<hr>



### function UdpMsg 

```C++
inline UdpMsg::UdpMsg (
    MsgType t
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/GGPOUE4/Private/network/udp_msg.h`

