

# File RpcConnectionManager.h

[**File List**](files.md) **>** [**Network**](dir_261b7ff0e57c151ad26fd5c163777bbe.md) **>** [**RpcConnectionManager.h**](_rpc_connection_manager_8h.md)

[Go to the documentation of this file](_rpc_connection_manager_8h.md)


```C++
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "include/connection_manager.h"

class NIGHTSKYENGINE_API RpcConnectionManager: public ConnectionManager
{
public:
    RpcConnectionManager();
    virtual ~RpcConnectionManager() override;
    
    virtual int SendTo(const char* buffer, int len, int flags, int connection_id);
    virtual int RecvFrom(char* buffer, int len, int flags, int* connection_id);
    
    int playerIndex;
    TDoubleLinkedList<TArray<int8>> sendSchedule;
    TDoubleLinkedList<TArray<int8>> receiveSchedule;
};

```


