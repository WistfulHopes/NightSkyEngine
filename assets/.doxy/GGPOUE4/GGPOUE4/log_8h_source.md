

# File log.h

[**File List**](files.md) **>** [**GGPOUE4**](dir_61f8f2a9aed5edd4e8edeed0f59c7e8a.md) **>** [**Private**](dir_37a60bd602479ee08f2dd49815e2e03d.md) **>** [**log.h**](log_8h.md)

[Go to the documentation of this file](log_8h.md)


```C++
/* -----------------------------------------------------------------------
 * GGPO.net (http://ggpo.net)  -  Copyright 2009 GroundStorm Studios, LLC.
 *
 * Use of this software is governed by the MIT license that can be found
 * in the LICENSE file.
 */

#ifndef _LOG_H
#define _LOG_H

extern void Log(const char *fmt, ...);
extern void Logv(const char *fmt, va_list list);
extern void Logv(FILE *fp, const char *fmt, va_list args);
extern void LogFlush();
extern void LogFlushOnLog(bool flush);

#endif
```


