

# File udp.h

[**File List**](files.md) **>** [**GGPOUE4**](dir_61f8f2a9aed5edd4e8edeed0f59c7e8a.md) **>** [**Private**](dir_37a60bd602479ee08f2dd49815e2e03d.md) **>** [**network**](dir_ecf22e3aebc35a5fe7ab40162c798880.md) **>** [**udp.h**](udp_8h.md)

[Go to the documentation of this file](udp_8h.md)


```C++
/* -----------------------------------------------------------------------
 * GGPO.net (http://ggpo.net)  -  Copyright 2009 GroundStorm Studios, LLC.
 *
 * Use of this software is governed by the MIT license that can be found
 * in the LICENSE file.
 */

#ifndef _UDP_H
#define _UDP_H

#include "poll.h"
#include "udp_msg.h"
#include "include/ggponet.h"
#include "include/connection_manager.h"

#define MAX_UDP_ENDPOINTS     16

static const int MAX_UDP_PACKET_SIZE = 4096;

class Udp : public IPollSink
{
public:
   struct Stats {
      int      bytes_sent;
      int      packets_sent;
      float    kbps_sent;
   };

   struct Callbacks {
      virtual ~Callbacks() { }
      virtual void OnMsg(int connection_id, UdpMsg *msg, int len) = 0;
   };


protected:
   void Log(const char *fmt, ...);

public:
   Udp();

   void Init(Poll *p, Callbacks *callbacks, ConnectionManager* connection_manager);
   
   void SendTo(char *buffer, int len, int flags, int connection_id);

   virtual bool OnLoopPoll(void *cookie);

public:
   ~Udp(void);

protected:
   ConnectionManager* _connection_manager;

   // state management
   Callbacks      *_callbacks;
   Poll           *_poll;
};

#endif
```


