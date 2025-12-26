

# Class Udp



[**ClassList**](annotated.md) **>** [**Udp**](class_udp.md)








Inherits the following classes: [IPollSink](class_i_poll_sink.md)












## Classes

| Type | Name |
| ---: | :--- |
| struct | [**Callbacks**](struct_udp_1_1_callbacks.md) <br> |
| struct | [**Stats**](struct_udp_1_1_stats.md) <br> |










































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**Init**](#function-init) ([**Poll**](class_poll.md) \* p, [**Callbacks**](struct_udp_1_1_callbacks.md) \* callbacks, [**ConnectionManager**](class_connection_manager.md) \* connection\_manager) <br> |
| virtual bool | [**OnLoopPoll**](#function-onlooppoll) (void \* cookie) <br> |
|  void | [**SendTo**](#function-sendto) (char \* buffer, int len, int flags, int connection\_id) <br> |
|   | [**Udp**](#function-udp) () <br> |
|   | [**~Udp**](#function-udp) (void) <br> |


## Public Functions inherited from IPollSink

See [IPollSink](class_i_poll_sink.md)

| Type | Name |
| ---: | :--- |
| virtual bool | [**OnHandlePoll**](class_i_poll_sink.md#function-onhandlepoll) (void \*) <br> |
| virtual bool | [**OnLoopPoll**](class_i_poll_sink.md#function-onlooppoll) (void \*) <br> |
| virtual bool | [**OnMsgPoll**](class_i_poll_sink.md#function-onmsgpoll) (void \*) <br> |
| virtual bool | [**OnPeriodicPoll**](class_i_poll_sink.md#function-onperiodicpoll) (void \*, int) <br> |
| virtual  | [**~IPollSink**](class_i_poll_sink.md#function-ipollsink) () <br> |














## Protected Attributes

| Type | Name |
| ---: | :--- |
|  [**Callbacks**](struct_udp_1_1_callbacks.md) \* | [**\_callbacks**](#variable-_callbacks)  <br> |
|  [**ConnectionManager**](class_connection_manager.md) \* | [**\_connection\_manager**](#variable-_connection_manager)  <br> |
|  [**Poll**](class_poll.md) \* | [**\_poll**](#variable-_poll)  <br> |
































## Protected Functions

| Type | Name |
| ---: | :--- |
|  void | [**Log**](#function-log) (const char \* fmt, ...) <br> |








## Public Functions Documentation




### function Init 

```C++
void Udp::Init (
    Poll * p,
    Callbacks * callbacks,
    ConnectionManager * connection_manager
) 
```




<hr>



### function OnLoopPoll 

```C++
virtual bool Udp::OnLoopPoll (
    void * cookie
) 
```



Implements [*IPollSink::OnLoopPoll*](class_i_poll_sink.md#function-onlooppoll)


<hr>



### function SendTo 

```C++
void Udp::SendTo (
    char * buffer,
    int len,
    int flags,
    int connection_id
) 
```




<hr>



### function Udp 

```C++
Udp::Udp () 
```




<hr>



### function ~Udp 

```C++
Udp::~Udp (
    void
) 
```




<hr>
## Protected Attributes Documentation




### variable \_callbacks 

```C++
Callbacks* Udp::_callbacks;
```




<hr>



### variable \_connection\_manager 

```C++
ConnectionManager* Udp::_connection_manager;
```




<hr>



### variable \_poll 

```C++
Poll* Udp::_poll;
```




<hr>
## Protected Functions Documentation




### function Log 

```C++
void Udp::Log (
    const char * fmt,
    ...
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/GGPOUE4/Private/network/udp.h`

