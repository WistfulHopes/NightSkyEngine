

# Struct neosmart::neosmart\_wfmo\_t\_



[**ClassList**](annotated.md) **>** [**neosmart**](namespaceneosmart.md) **>** [**neosmart\_wfmo\_t\_**](structneosmart_1_1neosmart__wfmo__t__.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  pthread\_cond\_t | [**CVariable**](#variable-cvariable)  <br> |
|  int | [**EventsLeft**](#variable-eventsleft)  <br> |
|  int | [**FiredEvent**](#variable-firedevent)  <br> |
|  pthread\_mutex\_t | [**Mutex**](#variable-mutex)  <br> |
|  int | [**RefCount**](#variable-refcount)  <br> |
|  union [**neosmart::neosmart\_wfmo\_t\_**](structneosmart_1_1neosmart__wfmo__t__.md) | [**Status**](#variable-status)  <br> |
|  bool | [**StillWaiting**](#variable-stillwaiting)  <br> |
|  bool | [**WaitAll**](#variable-waitall)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**Destroy**](#function-destroy) () <br> |




























## Public Attributes Documentation




### variable CVariable 

```C++
pthread_cond_t neosmart::neosmart_wfmo_t_::CVariable;
```




<hr>



### variable EventsLeft 

```C++
int neosmart::neosmart_wfmo_t_::EventsLeft;
```




<hr>



### variable FiredEvent 

```C++
int neosmart::neosmart_wfmo_t_::FiredEvent;
```




<hr>



### variable Mutex 

```C++
pthread_mutex_t neosmart::neosmart_wfmo_t_::Mutex;
```




<hr>



### variable RefCount 

```C++
int neosmart::neosmart_wfmo_t_::RefCount;
```




<hr>



### variable Status 

```C++
union neosmart::neosmart_wfmo_t_ neosmart::neosmart_wfmo_t_::Status;
```




<hr>



### variable StillWaiting 

```C++
bool neosmart::neosmart_wfmo_t_::StillWaiting;
```




<hr>



### variable WaitAll 

```C++
bool neosmart::neosmart_wfmo_t_::WaitAll;
```




<hr>
## Public Functions Documentation




### function Destroy 

```C++
inline void neosmart::neosmart_wfmo_t_::Destroy () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/GGPOUE4/Private/pevents.cpp`

