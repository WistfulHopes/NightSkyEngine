

# File Globals.h



[**FileList**](files.md) **>** [**Battle**](dir_59b3558fc0091a3111c9e7dd8d94b2ea.md) **>** [**Misc**](dir_4fd921e402b7a240656c31e280e3875c.md) **>** [**Globals.h**](_globals_8h.md)

[Go to the source code of this file](_globals_8h_source.md)
























## Public Attributes

| Type | Name |
| ---: | :--- |
|  int | [**gSinTable**](#variable-gsintable)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  uint32 | [**isqrt**](#function-isqrt) (uint64 const n) <br> |
|  uint32 | [**isqrt\_impl**](#function-isqrt_impl) (uint64 const n, uint64 const xk) <br> |



























## Macros

| Type | Name |
| ---: | :--- |
| define  | [**COORD\_SCALE**](_globals_8h.md#define-coord_scale)  `((double)1000 / 0.43)`<br> |

## Public Attributes Documentation




### variable gSinTable 

```C++
int gSinTable[900];
```




<hr>
## Public Functions Documentation




### function isqrt 

```C++
uint32 isqrt (
    uint64 const n
) 
```



Takes the square root of an integer n without floats.




**Parameters:**


* `n` The integer to take the square root of. 



**Returns:**

Returns the square root of n. 





        

<hr>



### function isqrt\_impl 

```C++
uint32 isqrt_impl (
    uint64 const n,
    uint64 const xk
) 
```



Implementation of integer square root. 


        

<hr>
## Macro Definition Documentation





### define COORD\_SCALE 

```C++
#define COORD_SCALE `((double)1000 / 0.43)`
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/NightSkyEngine/Battle/Misc/Globals.h`

