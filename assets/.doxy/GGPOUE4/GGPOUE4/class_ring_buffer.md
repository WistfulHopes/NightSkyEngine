

# Class RingBuffer

**template &lt;class T, int N&gt;**



[**ClassList**](annotated.md) **>** [**RingBuffer**](class_ring_buffer.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**RingBuffer**](#function-ringbuffer) () <br> |
|  bool | [**empty**](#function-empty) () <br> |
|  T & | [**front**](#function-front) () <br> |
|  T & | [**item**](#function-item) (int i) <br> |
|  void | [**pop**](#function-pop) () <br> |
|  void | [**push**](#function-push) (const T & t) <br> |
|  int | [**size**](#function-size) () <br> |








## Protected Attributes

| Type | Name |
| ---: | :--- |
|  T | [**\_elements**](#variable-_elements)  <br> |
|  int | [**\_head**](#variable-_head)  <br> |
|  int | [**\_size**](#variable-_size)  <br> |
|  int | [**\_tail**](#variable-_tail)  <br> |




















## Public Functions Documentation




### function RingBuffer 

```C++
inline RingBuffer::RingBuffer () 
```




<hr>



### function empty 

```C++
inline bool RingBuffer::empty () 
```




<hr>



### function front 

```C++
inline T & RingBuffer::front () 
```




<hr>



### function item 

```C++
inline T & RingBuffer::item (
    int i
) 
```




<hr>



### function pop 

```C++
inline void RingBuffer::pop () 
```




<hr>



### function push 

```C++
inline void RingBuffer::push (
    const T & t
) 
```




<hr>



### function size 

```C++
inline int RingBuffer::size () 
```




<hr>
## Protected Attributes Documentation




### variable \_elements 

```C++
T RingBuffer< T, N >::_elements[N];
```




<hr>



### variable \_head 

```C++
int RingBuffer< T, N >::_head;
```




<hr>



### variable \_size 

```C++
int RingBuffer< T, N >::_size;
```




<hr>



### variable \_tail 

```C++
int RingBuffer< T, N >::_tail;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/GGPOUE4/Private/ring_buffer.h`

