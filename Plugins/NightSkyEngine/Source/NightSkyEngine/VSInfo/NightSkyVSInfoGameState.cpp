// Fill out your copyright notice in the Description page of Project Settings.


#include "NightSkyVSInfoGameState.h"

#include "NightSkyEngine/Network/NetworkPawn.h"
#include "NightSkyEngine/Miscellaneous/NightSkyGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "NightSkyEngine/Battle/Actors/PlayerObject.h"
#include "NightSkyEngine/Data/PrimaryCharaData.h"
#include "NightSkyEngine/Data/PrimaryStageData.h"

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
