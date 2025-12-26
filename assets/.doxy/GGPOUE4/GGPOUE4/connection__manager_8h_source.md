

# File connection\_manager.h

[**File List**](files.md) **>** [**GGPOUE4**](dir_61f8f2a9aed5edd4e8edeed0f59c7e8a.md) **>** [**Public**](dir_85b7962d70ed8e910f117d16fb4825fd.md) **>** [**include**](dir_a7503a859c0cbfef62dfa39920604457.md) **>** [**connection\_manager.h**](connection__manager_8h.md)

[Go to the documentation of this file](connection__manager_8h.md)


```C++

#ifndef _CONNECTION_MANAGER_H
#define _CONNECTION_MANAGER_H

#include <map>
#include <memory>
#include <string>
#include "../../Private/types.h"

class ConnectionInfo {
public:
    ConnectionInfo() {}
    virtual ~ConnectionInfo() {
    }
    virtual std::string ToString() = 0;
};

class GGPOUE4_API ConnectionManager {
public:
    ConnectionManager() : _id_to_issue(0) {}

    virtual ~ConnectionManager();

    virtual int SendTo(const char* buffer, int len, int flags, int connection_id) = 0;

    virtual int RecvFrom(char* buffer, int len, int flags, int* connection_id) = 0;

    virtual int ResetManager() {
        _connection_map.clear();
        return 0;
    }

    virtual std::string ToString(int connection_id);

    void Log(const char* fmt, ...);

protected:
    int AddConnection(std::shared_ptr<ConnectionInfo> info) {
        _connection_map.insert({_id_to_issue, info});
        return _id_to_issue++;
    }

    int _id_to_issue;
    std::map <int, std::shared_ptr<ConnectionInfo>> _connection_map;
};

#if defined(_WINDOWS)
class UPDInfo : public ConnectionInfo   {
public:
    UPDInfo(const char* ip_address, uint16 port);

    sockaddr_in addr;

    ~UPDInfo() {
    }

    virtual std::string ToString();
};

class GGPOUE4_API UDPConnectionManager : public ConnectionManager {

public:
    UDPConnectionManager();
    virtual ~UDPConnectionManager();

    virtual int SendTo(const char* buffer, int len, int flags, int connection_id);

    virtual int RecvFrom(char* buffer, int len, int flags, int* connection_id);

    int AddConnection(const char* ip_address, uint16 port);

    void Init(uint16 port);

    int FindIDFromIP(sockaddr_in* sockaddr);

protected:
    std::shared_ptr<ConnectionInfo> BuildConnectionInfo(const char* ip_address, uint16 port);

    sockaddr_in _peer_addr;

    SOCKET _socket;

};
#endif


#endif
```


