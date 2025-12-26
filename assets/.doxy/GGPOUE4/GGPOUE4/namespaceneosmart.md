

# Namespace neosmart



[**Namespace List**](namespaces.md) **>** [**neosmart**](namespaceneosmart.md)




















## Classes

| Type | Name |
| ---: | :--- |
| struct | [**neosmart\_event\_t\_**](structneosmart_1_1neosmart__event__t__.md) <br> |
| struct | [**neosmart\_wfmo\_info\_t\_**](structneosmart_1_1neosmart__wfmo__info__t__.md) <br> |
| struct | [**neosmart\_wfmo\_t\_**](structneosmart_1_1neosmart__wfmo__t__.md) <br> |


## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**neosmart\_event\_t\_**](structneosmart_1_1neosmart__event__t__.md) \* | [**neosmart\_event\_t**](#typedef-neosmart_event_t)  <br> |
| typedef [**neosmart\_wfmo\_info\_t\_**](structneosmart_1_1neosmart__wfmo__info__t__.md) \* | [**neosmart\_wfmo\_info\_t**](#typedef-neosmart_wfmo_info_t)  <br> |
| typedef [**neosmart\_wfmo\_t\_**](structneosmart_1_1neosmart__wfmo__t__.md) \* | [**neosmart\_wfmo\_t**](#typedef-neosmart_wfmo_t)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|  [**neosmart\_event\_t**](structneosmart_1_1neosmart__event__t__.md) | [**CreateEvent**](#function-createevent) (bool manualReset, bool initialState) <br> |
|  int | [**DestroyEvent**](#function-destroyevent) ([**neosmart\_event\_t**](structneosmart_1_1neosmart__event__t__.md) event) <br> |
|  bool | [**RemoveExpiredWaitHelper**](#function-removeexpiredwaithelper) ([**neosmart\_wfmo\_info\_t\_**](structneosmart_1_1neosmart__wfmo__info__t__.md) wait) <br> |
|  int | [**ResetEvent**](#function-resetevent) ([**neosmart\_event\_t**](structneosmart_1_1neosmart__event__t__.md) event) <br> |
|  int | [**SetEvent**](#function-setevent) ([**neosmart\_event\_t**](structneosmart_1_1neosmart__event__t__.md) event) <br> |
|  int | [**UnlockedWaitForEvent**](#function-unlockedwaitforevent) ([**neosmart\_event\_t**](structneosmart_1_1neosmart__event__t__.md) event, uint64\_t milliseconds) <br> |
|  int | [**WaitForEvent**](#function-waitforevent) ([**neosmart\_event\_t**](structneosmart_1_1neosmart__event__t__.md) event, uint64\_t milliseconds) <br> |
|  int | [**WaitForMultipleEvents**](#function-waitformultipleevents) ([**neosmart\_event\_t**](structneosmart_1_1neosmart__event__t__.md) \* events, int count, bool waitAll, uint64\_t milliseconds) <br> |
|  int | [**WaitForMultipleEvents**](#function-waitformultipleevents) ([**neosmart\_event\_t**](structneosmart_1_1neosmart__event__t__.md) \* events, int count, bool waitAll, uint64\_t milliseconds, int & waitIndex) <br> |




























## Public Types Documentation




### typedef neosmart\_event\_t 

```C++
typedef neosmart_event_t_* neosmart::neosmart_event_t;
```




<hr>



### typedef neosmart\_wfmo\_info\_t 

```C++
typedef neosmart_wfmo_info_t_* neosmart::neosmart_wfmo_info_t;
```




<hr>



### typedef neosmart\_wfmo\_t 

```C++
typedef neosmart_wfmo_t_* neosmart::neosmart_wfmo_t;
```




<hr>
## Public Functions Documentation




### function CreateEvent 

```C++
neosmart_event_t neosmart::CreateEvent (
    bool manualReset,
    bool initialState
) 
```




<hr>



### function DestroyEvent 

```C++
int neosmart::DestroyEvent (
    neosmart_event_t event
) 
```




<hr>



### function RemoveExpiredWaitHelper 

```C++
bool neosmart::RemoveExpiredWaitHelper (
    neosmart_wfmo_info_t_ wait
) 
```




<hr>



### function ResetEvent 

```C++
int neosmart::ResetEvent (
    neosmart_event_t event
) 
```




<hr>



### function SetEvent 

```C++
int neosmart::SetEvent (
    neosmart_event_t event
) 
```




<hr>



### function UnlockedWaitForEvent 

```C++
int neosmart::UnlockedWaitForEvent (
    neosmart_event_t event,
    uint64_t milliseconds
) 
```




<hr>



### function WaitForEvent 

```C++
int neosmart::WaitForEvent (
    neosmart_event_t event,
    uint64_t milliseconds
) 
```




<hr>



### function WaitForMultipleEvents 

```C++
int neosmart::WaitForMultipleEvents (
    neosmart_event_t * events,
    int count,
    bool waitAll,
    uint64_t milliseconds
) 
```




<hr>



### function WaitForMultipleEvents 

```C++
int neosmart::WaitForMultipleEvents (
    neosmart_event_t * events,
    int count,
    bool waitAll,
    uint64_t milliseconds,
    int & waitIndex
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/GGPOUE4/Private/pevents.cpp`

