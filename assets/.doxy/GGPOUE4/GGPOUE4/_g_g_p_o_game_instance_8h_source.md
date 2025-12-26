

# File GGPOGameInstance.h

[**File List**](files.md) **>** [**GGPOUE4**](dir_61f8f2a9aed5edd4e8edeed0f59c7e8a.md) **>** [**Public**](dir_85b7962d70ed8e910f117d16fb4825fd.md) **>** [**GGPOGameInstance.h**](_g_g_p_o_game_instance_8h.md)

[Go to the documentation of this file](_g_g_p_o_game_instance_8h.md)


```C++
// Copyright 2020 BwdYeti.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GGPOGameInstance.generated.h"

// Forward declarations
class UGGPONetwork;

UCLASS()
class GGPOUE4_API UGGPOGameInstance : public UGameInstance
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        UGGPONetwork* NetworkAddresses;

    UFUNCTION(BlueprintCallable, Category = "GGPO")
        void CreateNetwork(int32 NumPlayers, int32 PlayerIndex, int32 LocalPort, TArray<FString> RemoteAddresses);
    
};
```


