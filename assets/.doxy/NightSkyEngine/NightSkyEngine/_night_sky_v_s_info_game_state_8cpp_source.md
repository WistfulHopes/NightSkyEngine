

# File NightSkyVSInfoGameState.cpp

[**File List**](files.md) **>** [**NightSkyEngine**](dir_01309b4faf1ec48651014f612e2b32bb.md) **>** [**Source**](dir_d32ee28216ed342fa25c01ae9dcd9cc4.md) **>** [**NightSkyEngine**](dir_a12a4fa09c295aab9e164f44221961f1.md) **>** [**VSInfo**](dir_0a96afba4f006b77d5cb7d94a414ba7d.md) **>** [**NightSkyVSInfoGameState.cpp**](_night_sky_v_s_info_game_state_8cpp.md)

[Go to the documentation of this file](_night_sky_v_s_info_game_state_8cpp.md)


```C++
// Fill out your copyright notice in the Description page of Project Settings.


#include "NightSkyVSInfoGameState.h"

#include "NightSkyEngine/Network/NetworkPawn.h"
#include "NightSkyEngine/Miscellaneous/NightSkyGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "NightSkyEngine/Battle/Objects/PlayerObject.h"
#include "NightSkyEngine/Data/PrimaryCharaData.h"
#include "NightSkyEngine/Data/PrimaryStageData.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(NightSkyVSInfoGameState)

ANightSkyVSInfoGameState::ANightSkyVSInfoGameState()
{
    PrimaryActorTick.bCanEverTick = true;

    VSInfoTime = 0;
    MapLoaded = false;
    LoadedCharaPackageCount = 0;
    TotalCharaPackageCount = 0;
}

void ANightSkyVSInfoGameState::BeginPlay()
{
    Super::BeginPlay();

    GameInstance = Cast<UNightSkyGameInstance>(GetGameInstance());
    LoadPackageAsync(GameInstance->BattleData.Stage->StageURL,
        FLoadPackageAsyncDelegate::CreateUObject(this,
            &ANightSkyVSInfoGameState::OnMapPackageLoaded),
        0, PKG_ContainsMap);
    for (const auto PrimaryCharaData : GameInstance->BattleData.PlayerListP1)
    {
        if (PrimaryCharaData == nullptr) continue;
        ++TotalCharaPackageCount;
        LoadPackageAsync(PrimaryCharaData->PlayerClass->GetPathName(),
            FLoadPackageAsyncDelegate::CreateUObject(this,
                &ANightSkyVSInfoGameState::OnCharaPackageLoaded));
    }
    for (const auto PrimaryCharaData : GameInstance->BattleData.PlayerListP2)
    {
        if (PrimaryCharaData == nullptr) continue;
        ++TotalCharaPackageCount;
        LoadPackageAsync(PrimaryCharaData->PlayerClass->GetPathName(),
            FLoadPackageAsyncDelegate::CreateUObject(this,
                &ANightSkyVSInfoGameState::OnCharaPackageLoaded));
    }
}

void ANightSkyVSInfoGameState::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    VSInfoTime += DeltaSeconds;
    if (VSInfoTime >= MaxVSInfoTime && MapLoaded && LoadedCharaPackageCount == TotalCharaPackageCount)
    {
        if (GameInstance->FighterRunner != Multiplayer || GameInstance->IsReplay)
            GameInstance->TravelToBattleMap();
        else
        {
            GameInstance->FinishedLoadingForNetworkBattle = true;
            if (GetWorld()->GetNetMode() == NM_Client)
            {
                const auto NetworkPawn = Cast<ANetworkPawn>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
                if (IsValid(NetworkPawn))
                {
                    NetworkPawn->ServerGetFinishedLoading(true);
                }
            }
        }
    }
}

void ANightSkyVSInfoGameState::OnMapPackageLoaded(const FName& PackageName, UPackage* LoadedPackage,
    EAsyncLoadingResult::Type Result)
{
    MapLoaded = true;
    Packages.Add(LoadedPackage);
}

void ANightSkyVSInfoGameState::OnCharaPackageLoaded(const FName& PackageName, UPackage* LoadedPackage,
    EAsyncLoadingResult::Type Result)
{
    ++LoadedCharaPackageCount;
    Packages.Add(LoadedPackage);
}
```


