

# Struct Poll::PollPeriodicSinkCb



[**ClassList**](annotated.md) **>** [**Poll**](class_poll.md) **>** [**PollPeriodicSinkCb**](struct_poll_1_1_poll_periodic_sink_cb.md)








Inherits the following classes: [Poll::PollSinkCb](struct_poll_1_1_poll_sink_cb.md)






















## Public Attributes

| Type | Name |
| ---: | :--- |
|  int | [**interval**](#variable-interval)  <br> |
|  int | [**last\_fired**](#variable-last_fired)  <br> |


## Public Attributes inherited from Poll::PollSinkCb

See [Poll::PollSinkCb](struct_poll_1_1_poll_sink_cb.md)

| Type | Name |
| ---: | :--- |
|  void \* | [**cookie**](struct_poll_1_1_poll_sink_cb.md#variable-cookie)  <br> |
|  [**IPollSink**](class_i_poll_sink.md) \* | [**sink**](struct_poll_1_1_poll_sink_cb.md#variable-sink)  <br> |






























## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**PollPeriodicSinkCb**](#function-pollperiodicsinkcb-12) () <br> |
|   | [**PollPeriodicSinkCb**](#function-pollperiodicsinkcb-22) ([**IPollSink**](class_i_poll_sink.md) \* s, void \* c, int i) <br> |


## Public Functions inherited from Poll::PollSinkCb

See [Poll::PollSinkCb](struct_poll_1_1_poll_sink_cb.md)

| Type | Name |
| ---: | :--- |
|   | [**PollSinkCb**](struct_poll_1_1_poll_sink_cb.md#function-pollsinkcb-12) () <br> |
|   | [**PollSinkCb**](struct_poll_1_1_poll_sink_cb.md#function-pollsinkcb-22) ([**IPollSink**](class_i_poll_sink.md) \* s, void \* c) <br> |






















































## Public Attributes Documentation




### variable interval 

```C++
int Poll::PollPeriodicSinkCb::interval;
```




<hr>



### variable last\_fired 

```C++
int Poll::PollPeriodicSinkCb::last_fired;
```




<hr>
## Public Functions Documentation




### function PollPeriodicSinkCb [1/2]

```C++
inline Poll::PollPeriodicSinkCb::PollPeriodicSinkCb () 
```




<hr>



### function PollPeriodicSinkCb [2/2]

```C++
inline Poll::PollPeriodicSinkCb::PollPeriodicSinkCb (
    IPollSink * s,
    void * c,
    int i
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/GGPOUE4/Private/poll.h`

