

# File bitvector.cpp

[**File List**](files.md) **>** [**GGPOUE4**](dir_61f8f2a9aed5edd4e8edeed0f59c7e8a.md) **>** [**Private**](dir_37a60bd602479ee08f2dd49815e2e03d.md) **>** [**bitvector.cpp**](bitvector_8cpp.md)

[Go to the documentation of this file](bitvector_8cpp.md)


```C++
/* -----------------------------------------------------------------------
 * GGPO.net (http://ggpo.net)  -  Copyright 2009 GroundStorm Studios, LLC.
 *
 * Use of this software is governed by the MIT license that can be found
 * in the LICENSE file.
 */

#include "bitvector.h"
#include "types.h"

void
BitVector_SetBit(uint8 *vector, int *offset)
{
   vector[(*offset) / 8] |= (1 << ((*offset) % 8));
   *offset += 1;
}

void
BitVector_ClearBit(uint8 *vector, int *offset)
{
   vector[(*offset) / 8] &= ~(1 << ((*offset) % 8));
   *offset += 1;
}

void
BitVector_WriteNibblet(uint8 *vector, int nibble, int *offset)
{
   ASSERT(nibble < (1 << BITVECTOR_NIBBLE_SIZE));
   for (int i = 0; i < BITVECTOR_NIBBLE_SIZE; i++) {
      if (nibble & (1 << i)) {
         BitVector_SetBit(vector, offset);
      } else {
         BitVector_ClearBit(vector, offset);
      }
   }
}

int
BitVector_ReadBit(uint8 *vector, int *offset)
{
   int retval = !!(vector[(*offset) / 8] & (1 << ((*offset) % 8)));
   *offset += 1;
   return retval;
}

int
BitVector_ReadNibblet(uint8 *vector, int *offset)
{
   int nibblet = 0;
   for (int i = 0; i < BITVECTOR_NIBBLE_SIZE; i++) {
      nibblet |= (BitVector_ReadBit(vector, offset) << i);
   }
   return nibblet;
}

```


