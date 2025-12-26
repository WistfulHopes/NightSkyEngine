

# Struct GGPOSessionCallbacks



[**ClassList**](annotated.md) **>** [**GGPOSessionCallbacks**](struct_g_g_p_o_session_callbacks.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  unsigned char \* | [**buffer**](#variable-buffer)  <br> |
|  int int \* | [**checksum**](#variable-checksum)  <br> |
|  int int int | [**frame**](#variable-frame)  <br> |
|  int \* | [**len**](#variable-len-13)  <br> |
|  int | [**len**](#variable-len-23)  <br> |
|  unsigned char int | [**len**](#variable-len-33)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**bool**](#function-bool-16) (\_\_cdecl \* begin\_game) const<br> |
|   | [**bool**](#function-bool-26) (\_\_cdecl \* save\_game\_state) <br> |
|   | [**bool**](#function-bool-36) (\_\_cdecl \* load\_game\_state) <br> |
|   | [**bool**](#function-bool-46) (\_\_cdecl \* log\_game\_state) <br> |
|   | [**bool**](#function-bool-56) (\_\_cdecl \* advance\_frame) <br> |
|   | [**bool**](#function-bool-66) (\_\_cdecl \* on\_event) <br> |
|   | [**void**](#function-void) (\_\_cdecl \* free\_buffer) <br> |




























## Public Attributes Documentation




### variable buffer 

```C++
unsigned char* GGPOSessionCallbacks::buffer;
```




<hr>



### variable checksum 

```C++
int int* GGPOSessionCallbacks::checksum;
```




<hr>



### variable frame 

```C++
int int int GGPOSessionCallbacks::frame;
```




<hr>



### variable len [1/3]

```C++
int* GGPOSessionCallbacks::len;
```




<hr>



### variable len [2/3]

```C++
int GGPOSessionCallbacks::len;
```




<hr>



### variable len [3/3]

```C++
unsigned char int GGPOSessionCallbacks::len;
```




<hr>
## Public Functions Documentation




### function bool [1/6]

```C++
GGPOSessionCallbacks::bool (
    __cdecl * begin_game
) const
```




<hr>



### function bool [2/6]

```C++
GGPOSessionCallbacks::bool (
    __cdecl * save_game_state
) 
```




<hr>



### function bool [3/6]

```C++
GGPOSessionCallbacks::bool (
    __cdecl * load_game_state
) 
```




<hr>



### function bool [4/6]

```C++
GGPOSessionCallbacks::bool (
    __cdecl * log_game_state
) 
```




<hr>



### function bool [5/6]

```C++
GGPOSessionCallbacks::bool (
    __cdecl * advance_frame
) 
```




<hr>



### function bool [6/6]

```C++
GGPOSessionCallbacks::bool (
    __cdecl * on_event
) 
```




<hr>



### function void 

```C++
GGPOSessionCallbacks::void (
    __cdecl * free_buffer
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/GGPOUE4/Public/include/ggponet.h`

