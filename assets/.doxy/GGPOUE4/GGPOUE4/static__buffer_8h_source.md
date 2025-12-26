

# File static\_buffer.h

[**File List**](files.md) **>** [**GGPOUE4**](dir_61f8f2a9aed5edd4e8edeed0f59c7e8a.md) **>** [**Private**](dir_37a60bd602479ee08f2dd49815e2e03d.md) **>** [**static\_buffer.h**](static__buffer_8h.md)

[Go to the documentation of this file](static__buffer_8h.md)


```C++
/* -----------------------------------------------------------------------
 * GGPO.net (http://ggpo.net)  -  Copyright 2009 GroundStorm Studios, LLC.
 *
 * Use of this software is governed by the MIT license that can be found
 * in the LICENSE file.
 */

#ifndef _STATIC_BUFFER_H
#define _STATIC_BUFFER_H

#include <types.h>

template<class T, int N> class StaticBuffer
{
public:
   StaticBuffer<T, N>() :
      _size(0) {
   } 

   T& operator[](int i) {
      ASSERT(i >= 0 && i < _size);
      return _elements[i];
   }

   void push_back(const T &t) {
      ASSERT(_size != (N-1));
      _elements[_size++] = t;
   }

   int size() {
      return _size;
   }


protected:
   T        _elements[N];
   int      _size;
};

#endif
```


