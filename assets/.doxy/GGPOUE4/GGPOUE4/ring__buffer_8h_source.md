

# File ring\_buffer.h

[**File List**](files.md) **>** [**GGPOUE4**](dir_61f8f2a9aed5edd4e8edeed0f59c7e8a.md) **>** [**Private**](dir_37a60bd602479ee08f2dd49815e2e03d.md) **>** [**ring\_buffer.h**](ring__buffer_8h.md)

[Go to the documentation of this file](ring__buffer_8h.md)


```C++
/* -----------------------------------------------------------------------
 * GGPO.net (http://ggpo.net)  -  Copyright 2009 GroundStorm Studios, LLC.
 *
 * Use of this software is governed by the MIT license that can be found
 * in the LICENSE file.
 */

#ifndef _RING_BUFFER_H
#define _RING_BUFFER_H

#include <types.h>

template<class T, int N> class RingBuffer
{
public:
   RingBuffer<T, N>() : 
      _head(0),
      _tail(0),
      _size(0) {
  } 

   T &front() {
      ASSERT(_size != N);
      return _elements[_tail];
   }
   
   T &item(int i) {
      ASSERT(i < _size);
      return _elements[(_tail + i) % N];
   }

   void pop() {
      ASSERT(_size != N);
      _tail = (_tail + 1) % N;
      _size--;
   }

   void push(const T &t) {
      ASSERT(_size != (N-1));
      _elements[_head] = t;
      _head = (_head + 1) % N;
      _size++;
   }

   int size() {
      return _size;
   }

   bool empty() {
      return _size == 0;
   }

protected:
   T        _elements[N];
   int      _head;
   int      _tail;
   int      _size;
};

#endif
```


