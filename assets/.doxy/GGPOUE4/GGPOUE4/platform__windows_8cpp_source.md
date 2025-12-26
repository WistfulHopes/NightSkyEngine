

# File platform\_windows.cpp

[**File List**](files.md) **>** [**GGPOUE4**](dir_61f8f2a9aed5edd4e8edeed0f59c7e8a.md) **>** [**Private**](dir_37a60bd602479ee08f2dd49815e2e03d.md) **>** [**platform\_windows.cpp**](platform__windows_8cpp.md)

[Go to the documentation of this file](platform__windows_8cpp.md)


```C++
/* -----------------------------------------------------------------------
* GGPO.net (http://ggpo.net)  -  Copyright 2009 GroundStorm Studios, LLC.
 *
 * Use of this software is governed by the MIT license that can be found
 * in the LICENSE file.
 */
#ifdef _WINDOWS
#include "platform_windows.h"

BOOL WINAPI
DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
   srand(Platform::GetCurrentTimeMS() + Platform::GetProcessID());
   return true;
}

#endif
```


