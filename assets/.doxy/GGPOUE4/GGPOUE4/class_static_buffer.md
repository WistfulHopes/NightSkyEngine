

# Class StaticBuffer

**template &lt;class T, int N&gt;**



[**ClassList**](annotated.md) **>** [**StaticBuffer**](class_static_buffer.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**StaticBuffer**](#function-staticbuffer) () <br> |
|  T & | [**operator[]**](#function-operator) (int i) <br> |
|  void | [**push\_back**](#function-push_back) (const T & t) <br> |
|  int | [**size**](#function-size) () <br> |








## Protected Attributes

| Type | Name |
| ---: | :--- |
|  T | [**\_elements**](#variable-_elements)  <br> |
|  int | [**\_size**](#variable-_size)  <br> |




















## Public Functions Documentation




### function StaticBuffer 

```C++
inline StaticBuffer::StaticBuffer () 
```




<hr>



### function operator[] 

```C++
inline T & StaticBuffer::operator[] (
    int i
) 
```




<hr>



### function push\_back 

```C++
inline void StaticBuffer::push_back (
    const T & t
) 
```




<hr>



### function size 

```C++
inline int StaticBuffer::size () 
```




<hr>
## Protected Attributes Documentation




### variable \_elements 

```C++
T StaticBuffer< T, N >::_elements[N];
```




<hr>



### variable \_size 

```C++
int StaticBuffer< T, N >::_size;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/GGPOUE4/Private/static_buffer.h`

