

# Class Poll



[**ClassList**](annotated.md) **>** [**Poll**](class_poll.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Poll**](#function-poll) (void) <br> |
|  bool | [**Pump**](#function-pump) (int timeout) <br> |
|  void | [**RegisterHandle**](#function-registerhandle) ([**IPollSink**](class_i_poll_sink.md) \* sink, HANDLE h, void \* cookie=NULL) <br> |
|  void | [**RegisterLoop**](#function-registerloop) ([**IPollSink**](class_i_poll_sink.md) \* sink, void \* cookie=NULL) <br> |
|  void | [**RegisterMsgLoop**](#function-registermsgloop) ([**IPollSink**](class_i_poll_sink.md) \* sink, void \* cookie=NULL) <br> |
|  void | [**RegisterPeriodic**](#function-registerperiodic) ([**IPollSink**](class_i_poll_sink.md) \* sink, int interval, void \* cookie=NULL) <br> |
|  void | [**Run**](#function-run) () <br> |








## Protected Attributes

| Type | Name |
| ---: | :--- |
|  int | [**\_handle\_count**](#variable-_handle_count)  <br> |
|  [**PollSinkCb**](struct_poll_1_1_poll_sink_cb.md) | [**\_handle\_sinks**](#variable-_handle_sinks)  <br> |
|  HANDLE | [**\_handles**](#variable-_handles)  <br> |
|  [**StaticBuffer**](class_static_buffer.md)&lt; [**PollSinkCb**](struct_poll_1_1_poll_sink_cb.md), 16 &gt; | [**\_loop\_sinks**](#variable-_loop_sinks)  <br> |
|  [**StaticBuffer**](class_static_buffer.md)&lt; [**PollSinkCb**](struct_poll_1_1_poll_sink_cb.md), 16 &gt; | [**\_msg\_sinks**](#variable-_msg_sinks)  <br> |
|  [**StaticBuffer**](class_static_buffer.md)&lt; [**PollPeriodicSinkCb**](struct_poll_1_1_poll_periodic_sink_cb.md), 16 &gt; | [**\_periodic\_sinks**](#variable-_periodic_sinks)  <br> |
|  int | [**\_start\_time**](#variable-_start_time)  <br> |
















## Protected Functions

| Type | Name |
| ---: | :--- |
|  int | [**ComputeWaitTime**](#function-computewaittime) (int elapsed) <br> |




## Public Functions Documentation




### function Poll 

```C++
Poll::Poll (
    void
) 
```




<hr>



### function Pump 

```C++
bool Poll::Pump (
    int timeout
) 
```




<hr>



### function RegisterHandle 

```C++
void Poll::RegisterHandle (
    IPollSink * sink,
    HANDLE h,
    void * cookie=NULL
) 
```




<hr>



### function RegisterLoop 

```C++
void Poll::RegisterLoop (
    IPollSink * sink,
    void * cookie=NULL
) 
```




<hr>



### function RegisterMsgLoop 

```C++
void Poll::RegisterMsgLoop (
    IPollSink * sink,
    void * cookie=NULL
) 
```




<hr>



### function RegisterPeriodic 

```C++
void Poll::RegisterPeriodic (
    IPollSink * sink,
    int interval,
    void * cookie=NULL
) 
```




<hr>



### function Run 

```C++
void Poll::Run () 
```




<hr>
## Protected Attributes Documentation




### variable \_handle\_count 

```C++
int Poll::_handle_count;
```




<hr>



### variable \_handle\_sinks 

```C++
PollSinkCb Poll::_handle_sinks[MAX_POLLABLE_HANDLES];
```




<hr>



### variable \_handles 

```C++
HANDLE Poll::_handles[MAX_POLLABLE_HANDLES];
```




<hr>



### variable \_loop\_sinks 

```C++
StaticBuffer<PollSinkCb, 16> Poll::_loop_sinks;
```




<hr>



### variable \_msg\_sinks 

```C++
StaticBuffer<PollSinkCb, 16> Poll::_msg_sinks;
```




<hr>



### variable \_periodic\_sinks 

```C++
StaticBuffer<PollPeriodicSinkCb, 16> Poll::_periodic_sinks;
```




<hr>



### variable \_start\_time 

```C++
int Poll::_start_time;
```




<hr>
## Protected Functions Documentation




### function ComputeWaitTime 

```C++
int Poll::ComputeWaitTime (
    int elapsed
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/GGPOUE4/Private/poll.h`

