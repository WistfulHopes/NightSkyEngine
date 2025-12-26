

# File zlib.h



[**FileList**](files.md) **>** [**GGPOUE4**](dir_61f8f2a9aed5edd4e8edeed0f59c7e8a.md) **>** [**Private**](dir_37a60bd602479ee08f2dd49815e2e03d.md) **>** [**zlib.h**](zlib_8h.md)

[Go to the source code of this file](zlib_8h_source.md)



* `#include "zconf.h"`















## Classes

| Type | Name |
| ---: | :--- |
| struct | [**internal\_state**](structinternal__state.md) <br> |
| struct | [**z\_stream\_s**](structz__stream__s.md) <br> |


## Public Types

| Type | Name |
| ---: | :--- |
| typedef voidpf alloc\_func | [**OF**](#typedef-of)  <br> |
| typedef voidp | [**gzFile**](#typedef-gzfile)  <br> |
| typedef struct [**z\_stream\_s**](structz__stream__s.md) | [**z\_stream**](#typedef-z_stream)  <br> |
| typedef [**z\_stream**](structz__stream__s.md) FAR \* | [**z\_streamp**](#typedef-z_streamp)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|  ZEXTERN const char \*ZEXPORT zlibVersion | [**OF**](#function-of) ((void)) <br> |
|  ZEXTERN int ZEXPORT deflate | [**OF**](#function-of) ((z\_streamp strm, int flush)) <br> |
|  ZEXTERN int ZEXPORT deflateEnd | [**OF**](#function-of) ((z\_streamp strm)) <br> |
|  ZEXTERN int ZEXPORT deflateSetDictionary | [**OF**](#function-of) ((z\_streamp strm, const Bytef \*dictionary, uInt dictLength)) <br> |
|  ZEXTERN int ZEXPORT deflateCopy | [**OF**](#function-of) ((z\_streamp dest, z\_streamp source)) <br> |
|  ZEXTERN int ZEXPORT deflateParams | [**OF**](#function-of) ((z\_streamp strm, int level, int strategy)) <br> |
|  ZEXTERN int ZEXPORT compress | [**OF**](#function-of) ((Bytef \*dest, uLongf \*destLen, const Bytef \*source, uLong sourceLen)) <br> |
|  ZEXTERN int ZEXPORT compress2 | [**OF**](#function-of) ((Bytef \*dest, uLongf \*destLen, const Bytef \*source, uLong sourceLen, int level)) <br> |
|  ZEXTERN gzFile ZEXPORT gzopen | [**OF**](#function-of) ((const char \*path, const char \*mode)) <br> |
|  ZEXTERN gzFile ZEXPORT gzdopen | [**OF**](#function-of) ((int fd, const char \*mode)) <br> |
|  ZEXTERN int ZEXPORT gzsetparams | [**OF**](#function-of) ((gzFile file, int level, int strategy)) <br> |
|  ZEXTERN int ZEXPORT gzread | [**OF**](#function-of) ((gzFile file, voidp buf, unsigned len)) <br> |
|  ZEXTERN int ZEXPORTVA gzprintf | [**OF**](#function-of) ((gzFile file, const char \*format,...)) <br> |
|  ZEXTERN int ZEXPORT gzputs | [**OF**](#function-of) ((gzFile file, const char \*s)) <br> |
|  ZEXTERN char \*ZEXPORT gzgets | [**OF**](#function-of) ((gzFile file, char \*buf, int len)) <br> |
|  ZEXTERN int ZEXPORT gzputc | [**OF**](#function-of) ((gzFile file, int c)) <br> |
|  ZEXTERN int ZEXPORT gzgetc | [**OF**](#function-of) ((gzFile file)) <br> |
|  ZEXTERN int ZEXPORT gzflush | [**OF**](#function-of) ((gzFile file, int flush)) <br> |
|  ZEXTERN z\_off\_t ZEXPORT gzseek | [**OF**](#function-of) ((gzFile file, z\_off\_t offset, int whence)) <br> |
|  ZEXTERN const char \*ZEXPORT gzerror | [**OF**](#function-of) ((gzFile file, int \*errnum)) <br> |
|  ZEXTERN uLong ZEXPORT adler32 | [**OF**](#function-of) ((uLong adler, const Bytef \*buf, uInt len)) <br> |
|  ZEXTERN uLong ZEXPORT crc32 | [**OF**](#function-of) ((uLong crc, const Bytef \*buf, uInt len)) <br> |
|  ZEXTERN int ZEXPORT deflateInit\_ | [**OF**](#function-of) ((z\_streamp strm, int level, const char \*version, int stream\_size)) <br> |
|  ZEXTERN int ZEXPORT inflateInit\_ | [**OF**](#function-of) ((z\_streamp strm, const char \*version, int stream\_size)) <br> |
|  ZEXTERN int ZEXPORT deflateInit2\_ | [**OF**](#function-of) ((z\_streamp strm, int level, int method, int windowBits, int memLevel, int strategy, const char \*version, int stream\_size)) <br> |
|  ZEXTERN int ZEXPORT inflateInit2\_ | [**OF**](#function-of) ((z\_streamp strm, int windowBits, const char \*version, int stream\_size)) <br> |
|  ZEXTERN const char \*ZEXPORT zError | [**OF**](#function-of) ((int err)) <br> |
|  ZEXTERN int ZEXPORT inflateSyncPoint | [**OF**](#function-of) ((z\_streamp z)) <br> |



























## Macros

| Type | Name |
| ---: | :--- |
| define  | [**ZLIB\_VERSION**](zlib_8h.md#define-zlib_version)  `"1.1.4"`<br> |
| define  | [**Z\_ASCII**](zlib_8h.md#define-z_ascii)  `1`<br> |
| define  | [**Z\_BEST\_COMPRESSION**](zlib_8h.md#define-z_best_compression)  `9`<br> |
| define  | [**Z\_BEST\_SPEED**](zlib_8h.md#define-z_best_speed)  `1`<br> |
| define  | [**Z\_BINARY**](zlib_8h.md#define-z_binary)  `0`<br> |
| define  | [**Z\_BUF\_ERROR**](zlib_8h.md#define-z_buf_error)  `(-5)`<br> |
| define  | [**Z\_DATA\_ERROR**](zlib_8h.md#define-z_data_error)  `(-3)`<br> |
| define  | [**Z\_DEFAULT\_COMPRESSION**](zlib_8h.md#define-z_default_compression)  `(-1)`<br> |
| define  | [**Z\_DEFAULT\_STRATEGY**](zlib_8h.md#define-z_default_strategy)  `0`<br> |
| define  | [**Z\_DEFLATED**](zlib_8h.md#define-z_deflated)  `8`<br> |
| define  | [**Z\_ERRNO**](zlib_8h.md#define-z_errno)  `(-1)`<br> |
| define  | [**Z\_FILTERED**](zlib_8h.md#define-z_filtered)  `1`<br> |
| define  | [**Z\_FINISH**](zlib_8h.md#define-z_finish)  `4`<br> |
| define  | [**Z\_FULL\_FLUSH**](zlib_8h.md#define-z_full_flush)  `3`<br> |
| define  | [**Z\_HUFFMAN\_ONLY**](zlib_8h.md#define-z_huffman_only)  `2`<br> |
| define  | [**Z\_MEM\_ERROR**](zlib_8h.md#define-z_mem_error)  `(-4)`<br> |
| define  | [**Z\_NEED\_DICT**](zlib_8h.md#define-z_need_dict)  `2`<br> |
| define  | [**Z\_NO\_COMPRESSION**](zlib_8h.md#define-z_no_compression)  `0`<br> |
| define  | [**Z\_NO\_FLUSH**](zlib_8h.md#define-z_no_flush)  `0`<br> |
| define  | [**Z\_NULL**](zlib_8h.md#define-z_null)  `0  /\* for initializing zalloc, zfree, opaque \*/`<br> |
| define  | [**Z\_OK**](zlib_8h.md#define-z_ok)  `0`<br> |
| define  | [**Z\_PARTIAL\_FLUSH**](zlib_8h.md#define-z_partial_flush)  `1 /\* will be removed, use Z\_SYNC\_FLUSH instead \*/`<br> |
| define  | [**Z\_STREAM\_END**](zlib_8h.md#define-z_stream_end)  `1`<br> |
| define  | [**Z\_STREAM\_ERROR**](zlib_8h.md#define-z_stream_error)  `(-2)`<br> |
| define  | [**Z\_SYNC\_FLUSH**](zlib_8h.md#define-z_sync_flush)  `2`<br> |
| define  | [**Z\_UNKNOWN**](zlib_8h.md#define-z_unknown)  `2`<br> |
| define  | [**Z\_VERSION\_ERROR**](zlib_8h.md#define-z_version_error)  `(-6)`<br> |
| define  | [**deflateInit**](zlib_8h.md#define-deflateinit) (strm, level) `deflateInit\_((strm), (level),       ZLIB\_VERSION, sizeof([**z\_stream**](structz__stream__s.md)))`<br> |
| define  | [**deflateInit2**](zlib_8h.md#define-deflateinit2) (strm, level, method, windowBits, memLevel, strategy) `/* multi line expression */`<br> |
| define  | [**inflateInit**](zlib_8h.md#define-inflateinit) (strm) `inflateInit\_((strm),                ZLIB\_VERSION, sizeof([**z\_stream**](structz__stream__s.md)))`<br> |
| define  | [**inflateInit2**](zlib_8h.md#define-inflateinit2) (strm, windowBits) `inflateInit2\_((strm), (windowBits), ZLIB\_VERSION, sizeof([**z\_stream**](structz__stream__s.md)))`<br> |
| define  | [**zlib\_version**](zlib_8h.md#define-zlib_version)  `zlibVersion()`<br> |

## Public Types Documentation




### typedef OF 

```C++
ZEXTERN const uLongf *ZEXPORT get_crc_table OF;
```




<hr>



### typedef gzFile 

```C++
typedef voidp gzFile;
```




<hr>



### typedef z\_stream 

```C++
typedef struct z_stream_s z_stream;
```




<hr>



### typedef z\_streamp 

```C++
typedef z_stream FAR* z_streamp;
```




<hr>
## Public Functions Documentation




### function OF 

```C++
ZEXTERN const char *ZEXPORT zlibVersion OF (
    (void)
) 
```




<hr>



### function OF 

```C++
ZEXTERN int ZEXPORT deflate OF (
    (z_streamp strm, int flush)
) 
```




<hr>



### function OF 

```C++
ZEXTERN int ZEXPORT deflateEnd OF (
    (z_streamp strm)
) 
```




<hr>



### function OF 

```C++
ZEXTERN int ZEXPORT deflateSetDictionary OF (
    (z_streamp strm, const Bytef *dictionary, uInt dictLength)
) 
```




<hr>



### function OF 

```C++
ZEXTERN int ZEXPORT deflateCopy OF (
    (z_streamp dest, z_streamp source)
) 
```




<hr>



### function OF 

```C++
ZEXTERN int ZEXPORT deflateParams OF (
    (z_streamp strm, int level, int strategy)
) 
```




<hr>



### function OF 

```C++
ZEXTERN int ZEXPORT compress OF (
    (Bytef *dest, uLongf *destLen, const Bytef *source, uLong sourceLen)
) 
```




<hr>



### function OF 

```C++
ZEXTERN int ZEXPORT compress2 OF (
    (Bytef *dest, uLongf *destLen, const Bytef *source, uLong sourceLen, int level)
) 
```




<hr>



### function OF 

```C++
ZEXTERN gzFile ZEXPORT gzopen OF (
    (const char *path, const char *mode)
) 
```




<hr>



### function OF 

```C++
ZEXTERN gzFile ZEXPORT gzdopen OF (
    (int fd, const char *mode)
) 
```




<hr>



### function OF 

```C++
ZEXTERN int ZEXPORT gzsetparams OF (
    (gzFile file, int level, int strategy)
) 
```




<hr>



### function OF 

```C++
ZEXTERN int ZEXPORT gzread OF (
    (gzFile file, voidp buf, unsigned len)
) 
```




<hr>



### function OF 

```C++
ZEXTERN int ZEXPORTVA gzprintf OF (
    (gzFile file, const char *format,...)
) 
```




<hr>



### function OF 

```C++
ZEXTERN int ZEXPORT gzputs OF (
    (gzFile file, const char *s)
) 
```




<hr>



### function OF 

```C++
ZEXTERN char *ZEXPORT gzgets OF (
    (gzFile file, char *buf, int len)
) 
```




<hr>



### function OF 

```C++
ZEXTERN int ZEXPORT gzputc OF (
    (gzFile file, int c)
) 
```




<hr>



### function OF 

```C++
ZEXTERN int ZEXPORT gzgetc OF (
    (gzFile file)
) 
```




<hr>



### function OF 

```C++
ZEXTERN int ZEXPORT gzflush OF (
    (gzFile file, int flush)
) 
```




<hr>



### function OF 

```C++
ZEXTERN z_off_t ZEXPORT gzseek OF (
    (gzFile file, z_off_t offset, int whence)
) 
```




<hr>



### function OF 

```C++
ZEXTERN const char *ZEXPORT gzerror OF (
    (gzFile file, int *errnum)
) 
```




<hr>



### function OF 

```C++
ZEXTERN uLong ZEXPORT adler32 OF (
    (uLong adler, const Bytef *buf, uInt len)
) 
```




<hr>



### function OF 

```C++
ZEXTERN uLong ZEXPORT crc32 OF (
    (uLong crc, const Bytef *buf, uInt len)
) 
```




<hr>



### function OF 

```C++
ZEXTERN int ZEXPORT deflateInit_ OF (
    (z_streamp strm, int level, const char *version, int stream_size)
) 
```




<hr>



### function OF 

```C++
ZEXTERN int ZEXPORT inflateInit_ OF (
    (z_streamp strm, const char *version, int stream_size)
) 
```




<hr>



### function OF 

```C++
ZEXTERN int ZEXPORT deflateInit2_ OF (
    (z_streamp strm, int level, int method, int windowBits, int memLevel, int strategy, const char *version, int stream_size)
) 
```




<hr>



### function OF 

```C++
ZEXTERN int ZEXPORT inflateInit2_ OF (
    (z_streamp strm, int windowBits, const char *version, int stream_size)
) 
```




<hr>



### function OF 

```C++
ZEXTERN const char *ZEXPORT zError OF (
    (int err)
) 
```




<hr>



### function OF 

```C++
ZEXTERN int ZEXPORT inflateSyncPoint OF (
    (z_streamp z)
) 
```




<hr>
## Macro Definition Documentation





### define ZLIB\_VERSION 

```C++
#define ZLIB_VERSION `"1.1.4"`
```




<hr>



### define Z\_ASCII 

```C++
#define Z_ASCII `1`
```




<hr>



### define Z\_BEST\_COMPRESSION 

```C++
#define Z_BEST_COMPRESSION `9`
```




<hr>



### define Z\_BEST\_SPEED 

```C++
#define Z_BEST_SPEED `1`
```




<hr>



### define Z\_BINARY 

```C++
#define Z_BINARY `0`
```




<hr>



### define Z\_BUF\_ERROR 

```C++
#define Z_BUF_ERROR `(-5)`
```




<hr>



### define Z\_DATA\_ERROR 

```C++
#define Z_DATA_ERROR `(-3)`
```




<hr>



### define Z\_DEFAULT\_COMPRESSION 

```C++
#define Z_DEFAULT_COMPRESSION `(-1)`
```




<hr>



### define Z\_DEFAULT\_STRATEGY 

```C++
#define Z_DEFAULT_STRATEGY `0`
```




<hr>



### define Z\_DEFLATED 

```C++
#define Z_DEFLATED `8`
```




<hr>



### define Z\_ERRNO 

```C++
#define Z_ERRNO `(-1)`
```




<hr>



### define Z\_FILTERED 

```C++
#define Z_FILTERED `1`
```




<hr>



### define Z\_FINISH 

```C++
#define Z_FINISH `4`
```




<hr>



### define Z\_FULL\_FLUSH 

```C++
#define Z_FULL_FLUSH `3`
```




<hr>



### define Z\_HUFFMAN\_ONLY 

```C++
#define Z_HUFFMAN_ONLY `2`
```




<hr>



### define Z\_MEM\_ERROR 

```C++
#define Z_MEM_ERROR `(-4)`
```




<hr>



### define Z\_NEED\_DICT 

```C++
#define Z_NEED_DICT `2`
```




<hr>



### define Z\_NO\_COMPRESSION 

```C++
#define Z_NO_COMPRESSION `0`
```




<hr>



### define Z\_NO\_FLUSH 

```C++
#define Z_NO_FLUSH `0`
```




<hr>



### define Z\_NULL 

```C++
#define Z_NULL `0  /* for initializing zalloc, zfree, opaque */`
```




<hr>



### define Z\_OK 

```C++
#define Z_OK `0`
```




<hr>



### define Z\_PARTIAL\_FLUSH 

```C++
#define Z_PARTIAL_FLUSH `1 /* will be removed, use Z_SYNC_FLUSH instead */`
```




<hr>



### define Z\_STREAM\_END 

```C++
#define Z_STREAM_END `1`
```




<hr>



### define Z\_STREAM\_ERROR 

```C++
#define Z_STREAM_ERROR `(-2)`
```




<hr>



### define Z\_SYNC\_FLUSH 

```C++
#define Z_SYNC_FLUSH `2`
```




<hr>



### define Z\_UNKNOWN 

```C++
#define Z_UNKNOWN `2`
```




<hr>



### define Z\_VERSION\_ERROR 

```C++
#define Z_VERSION_ERROR `(-6)`
```




<hr>



### define deflateInit 

```C++
#define deflateInit (
    strm,
    level
) `deflateInit_((strm), (level),       ZLIB_VERSION, sizeof( z_stream ))`
```




<hr>



### define deflateInit2 

```C++
#define deflateInit2 (
    strm,
    level,
    method,
    windowBits,
    memLevel,
    strategy
) `/* multi line expression */`
```




<hr>



### define inflateInit 

```C++
#define inflateInit (
    strm
) `inflateInit_((strm),                ZLIB_VERSION, sizeof( z_stream ))`
```




<hr>



### define inflateInit2 

```C++
#define inflateInit2 (
    strm,
    windowBits
) `inflateInit2_((strm), (windowBits), ZLIB_VERSION, sizeof( z_stream ))`
```




<hr>



### define zlib\_version 

```C++
#define zlib_version `zlibVersion()`
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/GGPOUE4/Private/zlib.h`

