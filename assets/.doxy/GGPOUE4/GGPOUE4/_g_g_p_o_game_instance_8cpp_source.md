

# File GGPOGameInstance.cpp

[**File List**](files.md) **>** [**GGPOUE4**](dir_61f8f2a9aed5edd4e8edeed0f59c7e8a.md) **>** [**Private**](dir_37a60bd602479ee08f2dd49815e2e03d.md) **>** [**GGPOGameInstance.cpp**](_g_g_p_o_game_instance_8cpp.md)

[Go to the documentation of this file](_g_g_p_o_game_instance_8cpp.md)


```C++
// Copyright 2020 BwdYeti.


#include "GGPOGameInstance.h"
#include "include/ggponet.h"

void UGGPOGameInstance::CreateNetwork(int32 NumPlayers, int32 PlayerIndex, int32 LocalPort, TArray<FString> RemoteAddresses)
{
    UGGPONetwork* addresses = UGGPONetwork::CreateNetwork(
        this,
        FName(FString(TEXT("GGPONetwork"))),
        NumPlayers,
        PlayerIndex,
        LocalPort,
        RemoteAddresses);
    NetworkAddresses = addresses;
}

```


