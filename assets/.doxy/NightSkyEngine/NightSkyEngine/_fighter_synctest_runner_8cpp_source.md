

# File FighterSynctestRunner.cpp

[**File List**](files.md) **>** [**Battle**](dir_59b3558fc0091a3111c9e7dd8d94b2ea.md) **>** [**FighterRunners**](dir_55fd23ec9dd9ced1aa4a37204be9832d.md) **>** [**FighterSynctestRunner.cpp**](_fighter_synctest_runner_8cpp.md)

[Go to the documentation of this file](_fighter_synctest_runner_8cpp.md)


```C++
// Fill out your copyright notice in the Description page of Project Settings.


#include "FighterSynctestRunner.h"
#include "NightSkyEngine/Battle/NightSkyGameState.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(FighterSynctestRunner)

// Sets default values
AFighterSynctestRunner::AFighterSynctestRunner()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;
    bReplicates = false;
}

// Called when the game starts or when spawned
void AFighterSynctestRunner::BeginPlay()
{
    AFighterLocalRunner::BeginPlay();
    GGPOSessionCallbacks cb = CreateCallbacks();
    GGPONet::ggpo_start_synctest(&ggpo, &cb, "", 2, sizeof(int), 6);
    GGPONet::ggpo_set_disconnect_timeout(ggpo, 45000);
    GGPONet::ggpo_set_disconnect_notify_start(ggpo, 15000);
    for (int i = 0; i < 2; i++)
    {
        GGPOPlayerHandle handle;
        GGPOPlayer* player = new GGPOPlayer();
        player->type = GGPO_PLAYERTYPE_LOCAL;
        player->player_num = i + 1;
        GGPONet::ggpo_add_player(ggpo, player, &handle);
        Players.Add(player);
        PlayerInputIndex.Add(i);
        PlayerHandles.Add(handle);
    }
    GGPONet::ggpo_try_synchronize_local(ggpo);
}

void AFighterSynctestRunner::Update(float DeltaTime)
{
    ElapsedTime += DeltaTime;
    while (ElapsedTime >= OneFrame)
    {
        GgpoUpdate();
        ElapsedTime -= OneFrame;
    }
    GGPONet::ggpo_idle(ggpo, 1);
}
```


