

# File types.h



[**FileList**](files.md) **>** [**GGPOUE4**](dir_61f8f2a9aed5edd4e8edeed0f59c7e8a.md) **>** [**Private**](dir_37a60bd602479ee08f2dd49815e2e03d.md) **>** [**types.h**](types_8h.md)

[Go to the source code of this file](types_8h_source.md)



* `#include "log.h"`

















## Public Types

| Type | Name |
| ---: | :--- |
| typedef unsigned char | [**byte**](#typedef-byte)  <br> |















































## Macros

| Type | Name |
| ---: | :--- |
| define  | [**ARRAY\_SIZE**](types_8h.md#define-array_size) (a) `(sizeof(a) / sizeof((a)[0]))`<br> |
| define  | [**ASSERT**](types_8h.md#define-assert) (x) `/* multi line expression */`<br> |
| define  | [**MAX**](types_8h.md#define-max) (x, y) `(((x) &gt; (y)) ? (x) : (y))`<br> |
| define  | [**MAX\_INT**](types_8h.md#define-max_int)  `0xEFFFFFF`<br> |
| define  | [**MIN**](types_8h.md#define-min) (x, y) `(((x) &lt; (y)) ? (x) : (y))`<br> |

## Public Types Documentation




### typedef byte 

```C++
typedef unsigned char byte;
```




<hr>
## Macro Definition Documentation





### define ARRAY\_SIZE 

```C++
#define ARRAY_SIZE (
    a
) `(sizeof(a) / sizeof((a)[0]))`
```




<hr>



### define ASSERT 

```C++
#define ASSERT (
    x
) `/* multi line expression */`
```




<hr>



### define MAX 

```C++
#define MAX (
    x,
    y
) `(((x) > (y)) ? (x) : (y))`
```




<hr>



### define MAX\_INT 

```C++
#define MAX_INT `0xEFFFFFF`
```




<hr>



### define MIN 

```C++
#define MIN (
    x,
    y
) `(((x) < (y)) ? (x) : (y))`
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/GGPOUE4/Private/types.h`

