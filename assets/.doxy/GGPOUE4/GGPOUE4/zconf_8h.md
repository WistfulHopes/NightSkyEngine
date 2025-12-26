

# File zconf.h



[**FileList**](files.md) **>** [**GGPOUE4**](dir_61f8f2a9aed5edd4e8edeed0f59c7e8a.md) **>** [**Private**](dir_37a60bd602479ee08f2dd49815e2e03d.md) **>** [**zconf.h**](zconf_8h.md)

[Go to the source code of this file](zconf_8h_source.md)




















## Public Types

| Type | Name |
| ---: | :--- |
| typedef unsigned char | [**Byte**](#typedef-byte)  <br> |
| typedef Byte FAR | [**Bytef**](#typedef-bytef)  <br> |
| typedef char FAR | [**charf**](#typedef-charf)  <br> |
| typedef int FAR | [**intf**](#typedef-intf)  <br> |
| typedef unsigned int | [**uInt**](#typedef-uint)  <br> |
| typedef uInt FAR | [**uIntf**](#typedef-uintf)  <br> |
| typedef unsigned long | [**uLong**](#typedef-ulong)  <br> |
| typedef uLong FAR | [**uLongf**](#typedef-ulongf)  <br> |
| typedef Byte \* | [**voidp**](#typedef-voidp)  <br> |
| typedef Byte FAR \* | [**voidpf**](#typedef-voidpf)  <br> |















































## Macros

| Type | Name |
| ---: | :--- |
| define  | [**FAR**](zconf_8h.md#define-far)  <br> |
| define  | [**MAX\_MEM\_LEVEL**](zconf_8h.md#define-max_mem_level)  `9`<br> |
| define  | [**MAX\_WBITS**](zconf_8h.md#define-max_wbits)  `15 /\* 32K LZ77 window \*/`<br> |
| define  | [**OF**](zconf_8h.md#define-of) (args) `()`<br> |
| define  | [**SEEK\_CUR**](zconf_8h.md#define-seek_cur)  `1       /\* Seek from current position.  \*/`<br> |
| define  | [**SEEK\_END**](zconf_8h.md#define-seek_end)  `2       /\* Set file pointer to EOF plus "offset" \*/`<br> |
| define  | [**SEEK\_SET**](zconf_8h.md#define-seek_set)  `0       /\* Seek from beginning of file.  \*/`<br> |
| define  | [**ZEXPORT**](zconf_8h.md#define-zexport)  `\_\_fastcall`<br> |
| define  | [**ZEXPORTVA**](zconf_8h.md#define-zexportva)  `\_\_cdecl`<br> |
| define  | [**ZEXTERN**](zconf_8h.md#define-zextern)  `extern`<br> |
| define  | [**const**](zconf_8h.md#define-const)  <br> |
| define  | [**z\_off\_t**](zconf_8h.md#define-z_off_t)  `long`<br> |

## Public Types Documentation




### typedef Byte 

```C++
typedef unsigned char Byte;
```




<hr>



### typedef Bytef 

```C++
typedef Byte FAR Bytef;
```




<hr>



### typedef charf 

```C++
typedef char FAR charf;
```




<hr>



### typedef intf 

```C++
typedef int FAR intf;
```




<hr>



### typedef uInt 

```C++
typedef unsigned int uInt;
```




<hr>



### typedef uIntf 

```C++
typedef uInt FAR uIntf;
```




<hr>



### typedef uLong 

```C++
typedef unsigned long uLong;
```




<hr>



### typedef uLongf 

```C++
typedef uLong FAR uLongf;
```




<hr>



### typedef voidp 

```C++
typedef Byte* voidp;
```




<hr>



### typedef voidpf 

```C++
typedef Byte FAR* voidpf;
```




<hr>
## Macro Definition Documentation





### define FAR 

```C++
#define FAR 
```




<hr>



### define MAX\_MEM\_LEVEL 

```C++
#define MAX_MEM_LEVEL `9`
```




<hr>



### define MAX\_WBITS 

```C++
#define MAX_WBITS `15 /* 32K LZ77 window */`
```




<hr>



### define OF 

```C++
#define OF (
    args
) `()`
```




<hr>



### define SEEK\_CUR 

```C++
#define SEEK_CUR `1       /* Seek from current position.  */`
```




<hr>



### define SEEK\_END 

```C++
#define SEEK_END `2       /* Set file pointer to EOF plus "offset" */`
```




<hr>



### define SEEK\_SET 

```C++
#define SEEK_SET `0       /* Seek from beginning of file.  */`
```




<hr>



### define ZEXPORT 

```C++
#define ZEXPORT `__fastcall`
```




<hr>



### define ZEXPORTVA 

```C++
#define ZEXPORTVA `__cdecl`
```




<hr>



### define ZEXTERN 

```C++
#define ZEXTERN `extern`
```




<hr>



### define const 

```C++
#define const 
```




<hr>



### define z\_off\_t 

```C++
#define z_off_t `long`
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/GGPOUE4/Private/zconf.h`

