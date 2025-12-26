

# File log.cpp



[**FileList**](files.md) **>** [**GGPOUE4**](dir_61f8f2a9aed5edd4e8edeed0f59c7e8a.md) **>** [**Private**](dir_37a60bd602479ee08f2dd49815e2e03d.md) **>** [**log.cpp**](log_8cpp.md)

[Go to the source code of this file](log_8cpp_source.md)



* `#include "log.h"`
* `#include "types.h"`























## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  char | [**logbuf**](#variable-logbuf)  <br> |
|  FILE \* | [**logfile**](#variable-logfile)   = `NULL`<br> |














## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**Log**](#function-log) (const char \* fmt, ...) <br> |
|  void | [**LogFlush**](#function-logflush) () <br> |
|  void | [**Logv**](#function-logv) (const char \* fmt, va\_list args) <br> |
|  void | [**Logv**](#function-logv) (FILE \* fp, const char \* fmt, va\_list args) <br> |




























## Public Static Attributes Documentation




### variable logbuf 

```C++
char logbuf[4 *1024 *1024];
```




<hr>



### variable logfile 

```C++
FILE* logfile;
```




<hr>
## Public Functions Documentation




### function Log 

```C++
void Log (
    const char * fmt,
    ...
) 
```




<hr>



### function LogFlush 

```C++
void LogFlush () 
```




<hr>



### function Logv 

```C++
void Logv (
    const char * fmt,
    va_list args
) 
```




<hr>



### function Logv 

```C++
void Logv (
    FILE * fp,
    const char * fmt,
    va_list args
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/GGPOUE4/Private/log.cpp`

