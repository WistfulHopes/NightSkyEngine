

# File bitvector.h

[**File List**](files.md) **>** [**GGPOUE4**](dir_61f8f2a9aed5edd4e8edeed0f59c7e8a.md) **>** [**Private**](dir_37a60bd602479ee08f2dd49815e2e03d.md) **>** [**bitvector.h**](bitvector_8h.md)

[Go to the documentation of this file](bitvector_8h.md)


```C++
/* -----------------------------------------------------------------------
 * GGPO.net (http://ggpo.net)  -  Copyright 2009 GroundStorm Studios, LLC.
 *
 * Use of this software is governed by the MIT license that can be found
 * in the LICENSE file.
 */

#ifndef _BITVECTOR_H
#define _BITVECTOR_H

#define BITVECTOR_NIBBLE_SIZE 8

void BitVector_SetBit(uint8 *vector, int *offset);
void BitVector_ClearBit(uint8 *vector, int *offset);
void BitVector_WriteNibblet(uint8 *vector, int nibble, int *offset);
int BitVector_ReadBit(uint8 *vector, int *offset);
int BitVector_ReadNibblet(uint8 *vector, int *offset);

#endif // _BITVECTOR_H
```


