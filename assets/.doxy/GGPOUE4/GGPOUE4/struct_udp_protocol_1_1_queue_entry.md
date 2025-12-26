

# Struct UdpProtocol::QueueEntry



[**ClassList**](annotated.md) **>** [**UdpProtocol**](class_udp_protocol.md) **>** [**QueueEntry**](struct_udp_protocol_1_1_queue_entry.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  int | [**connection\_id**](#variable-connection_id)  <br> |
|  [**UdpMsg**](struct_udp_msg.md) \* | [**msg**](#variable-msg)  <br> |
|  int | [**queue\_time**](#variable-queue_time)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**QueueEntry**](#function-queueentry-12) () <br> |
|   | [**QueueEntry**](#function-queueentry-22) (int time, int conn\_id, [**UdpMsg**](struct_udp_msg.md) \* m) <br> |




























## Public Attributes Documentation




### variable connection\_id 

```C++
int UdpProtocol::QueueEntry::connection_id;
```




<hr>



### variable msg 

```C++
UdpMsg* UdpProtocol::QueueEntry::msg;
```




<hr>



### variable queue\_time 

```C++
int UdpProtocol::QueueEntry::queue_time;
```




<hr>
## Public Functions Documentation




### function QueueEntry [1/2]

```C++
inline UdpProtocol::QueueEntry::QueueEntry () 
```




<hr>



### function QueueEntry [2/2]

```C++
inline UdpProtocol::QueueEntry::QueueEntry (
    int time,
    int conn_id,
    UdpMsg * m
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/GGPOUE4/Private/network/udp_proto.h`

