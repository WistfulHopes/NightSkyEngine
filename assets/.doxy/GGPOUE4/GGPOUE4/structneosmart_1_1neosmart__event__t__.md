

# Struct neosmart::neosmart\_event\_t\_



[**ClassList**](annotated.md) **>** [**neosmart**](namespaceneosmart.md) **>** [**neosmart\_event\_t\_**](structneosmart_1_1neosmart__event__t__.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  bool | [**AutoReset**](#variable-autoreset)  <br> |
|  pthread\_cond\_t | [**CVariable**](#variable-cvariable)  <br> |
|  pthread\_mutex\_t | [**Mutex**](#variable-mutex)  <br> |
|  std::deque&lt; [**neosmart\_wfmo\_info\_t\_**](structneosmart_1_1neosmart__wfmo__info__t__.md) &gt; | [**RegisteredWaits**](#variable-registeredwaits)  <br> |
|  bool | [**State**](#variable-state)  <br> |












































## Public Attributes Documentation




### variable AutoReset 

```C++
bool neosmart::neosmart_event_t_::AutoReset;
```




<hr>



### variable CVariable 

```C++
pthread_cond_t neosmart::neosmart_event_t_::CVariable;
```




<hr>



### variable Mutex 

```C++
pthread_mutex_t neosmart::neosmart_event_t_::Mutex;
```




<hr>



### variable RegisteredWaits 

```C++
std::deque<neosmart_wfmo_info_t_> neosmart::neosmart_event_t_::RegisteredWaits;
```




<hr>



### variable State 

```C++
bool neosmart::neosmart_event_t_::State;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/GGPOUE4/Private/pevents.cpp`

