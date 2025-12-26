

# Struct Poll::PollSinkCb



[**ClassList**](annotated.md) **>** [**Poll**](class_poll.md) **>** [**PollSinkCb**](struct_poll_1_1_poll_sink_cb.md)










Inherited by the following classes: [Poll::PollPeriodicSinkCb](struct_poll_1_1_poll_periodic_sink_cb.md)
















## Public Attributes

| Type | Name |
| ---: | :--- |
|  void \* | [**cookie**](#variable-cookie)  <br> |
|  [**IPollSink**](class_i_poll_sink.md) \* | [**sink**](#variable-sink)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**PollSinkCb**](#function-pollsinkcb-12) () <br> |
|   | [**PollSinkCb**](#function-pollsinkcb-22) ([**IPollSink**](class_i_poll_sink.md) \* s, void \* c) <br> |




























## Public Attributes Documentation




### variable cookie 

```C++
void* Poll::PollSinkCb::cookie;
```




<hr>



### variable sink 

```C++
IPollSink* Poll::PollSinkCb::sink;
```




<hr>
## Public Functions Documentation




### function PollSinkCb [1/2]

```C++
inline Poll::PollSinkCb::PollSinkCb () 
```




<hr>



### function PollSinkCb [2/2]

```C++
inline Poll::PollSinkCb::PollSinkCb (
    IPollSink * s,
    void * c
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/GGPOUE4/Private/poll.h`

