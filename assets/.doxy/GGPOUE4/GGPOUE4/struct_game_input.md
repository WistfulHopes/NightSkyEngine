

# Struct GameInput



[**ClassList**](annotated.md) **>** [**GameInput**](struct_game_input.md)






















## Public Types

| Type | Name |
| ---: | :--- |
| enum  | [**Constants**](#enum-constants)  <br> |




## Public Attributes

| Type | Name |
| ---: | :--- |
|  char | [**bits**](#variable-bits)  <br> |
|  int | [**frame**](#variable-frame)  <br> |
|  int | [**size**](#variable-size)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**clear**](#function-clear) (int i) <br> |
|  void | [**desc**](#function-desc) (char \* buf, size\_t buf\_size, bool show\_frame=true) const<br> |
|  bool | [**equal**](#function-equal) ([**GameInput**](struct_game_input.md) & input, bool bitsonly=false) <br> |
|  void | [**erase**](#function-erase) () <br> |
|  void | [**init**](#function-init-12) (int frame, char \* bits, int size, int offset) <br> |
|  void | [**init**](#function-init-22) (int frame, char \* bits, int size) <br> |
|  bool | [**is\_null**](#function-is_null) () <br> |
|  void | [**log**](#function-log) (char \* prefix, bool show\_frame=true) const<br> |
|  void | [**set**](#function-set) (int i) <br> |
|  bool | [**value**](#function-value) (int i) const<br> |




























## Public Types Documentation




### enum Constants 

```C++
enum GameInput::Constants {
    NullFrame = -1
};
```




<hr>
## Public Attributes Documentation




### variable bits 

```C++
char GameInput::bits[GAMEINPUT_MAX_BYTES *GAMEINPUT_MAX_PLAYERS];
```




<hr>



### variable frame 

```C++
int GameInput::frame;
```




<hr>



### variable size 

```C++
int GameInput::size;
```




<hr>
## Public Functions Documentation




### function clear 

```C++
inline void GameInput::clear (
    int i
) 
```




<hr>



### function desc 

```C++
void GameInput::desc (
    char * buf,
    size_t buf_size,
    bool show_frame=true
) const
```




<hr>



### function equal 

```C++
bool GameInput::equal (
    GameInput & input,
    bool bitsonly=false
) 
```




<hr>



### function erase 

```C++
inline void GameInput::erase () 
```




<hr>



### function init [1/2]

```C++
void GameInput::init (
    int frame,
    char * bits,
    int size,
    int offset
) 
```




<hr>



### function init [2/2]

```C++
void GameInput::init (
    int frame,
    char * bits,
    int size
) 
```




<hr>



### function is\_null 

```C++
inline bool GameInput::is_null () 
```




<hr>



### function log 

```C++
void GameInput::log (
    char * prefix,
    bool show_frame=true
) const
```




<hr>



### function set 

```C++
inline void GameInput::set (
    int i
) 
```




<hr>



### function value 

```C++
inline bool GameInput::value (
    int i
) const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/GGPOUE4/Private/game_input.h`

