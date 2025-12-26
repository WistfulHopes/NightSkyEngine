

# File platform\_unix.cpp

[**File List**](files.md) **>** [**GGPOUE4**](dir_61f8f2a9aed5edd4e8edeed0f59c7e8a.md) **>** [**Private**](dir_37a60bd602479ee08f2dd49815e2e03d.md) **>** [**platform\_unix.cpp**](platform__unix_8cpp.md)

[Go to the documentation of this file](platform__unix_8cpp.md)


```C++
/* -----------------------------------------------------------------------
 * GGPO.net (http://ggpo.net)  -  Copyright 2009 GroundStorm Studios, LLC.
 *
 * Use of this software is governed by the MIT license that can be found
 * in the LICENSE file.
 */
#ifdef __linux__

#include "platform_unix.h"

uint32_t Platform::GetCurrentTimeMS() {
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return (ts.tv_sec * 1000) + (ts.tv_nsec / (1000*1000));
}

void Platform::SleepMS(int milliseconds) {
  usleep(milliseconds * 1000);
}

void Platform::CreateDirectory(const char* pathname, const void* junk) {
  mkdir(pathname, -1);
}

static void __attribute__((constructor)) DllMain() {
   srand(Platform::GetCurrentTimeMS() + Platform::GetProcessID());
}
#endif
```


