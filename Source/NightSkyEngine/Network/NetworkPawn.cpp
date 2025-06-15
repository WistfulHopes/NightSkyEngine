// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkPawn.h"

#include "NightSkyEngine/Miscellaneous/NightSkyGameInstance.h"
#include "RpcConnectionManager.h"
#include "Engine/AssetManager.h"
#include "NightSkyEngine/Battle/Actors/NightSkyGameState.h"
#include "Net/UnrealNetwork.h"
#include "NightSkyEngine/Battle/Actors/FighterRunners/FighterMultiplayerRunner.h"
#include "NightSkyEngine/Data/PrimaryCharaData.h"

// Sets default values
ANetworkPawn::ANetworkPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
}

// Called when the game starts or when spawned
void ANetworkPawn::BeginPlay()
{
	Super::BeginPlay();
}

void ANetworkPawn::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ANetworkPawn, CharaDataReceived)
	DOREPLIFETIME(ANetworkPawn, bRematchAccepted)
}

void ANetworkPawn::ServerGetCharaData(TArray<FPrimaryAssetId> Assets)
{
	UNightSkyGameInstance* GameInstance = Cast<UNightSkyGameInstance>(GetGameInstance());
	
	GameInstance->BattleData.PlayerListP2[0] = Cast<UPrimaryCharaData>(UAssetManager::Get().GetPrimaryAssetObject(Assets[0]));
	GameInstance->BattleData.PlayerListP2[1] = Cast<UPrimaryCharaData>(UAssetManager::Get().GetPrimaryAssetObject(Assets[1]));
	GameInstance->BattleData.PlayerListP2[2] = Cast<UPrimaryCharaData>(UAssetManager::Get().GetPrimaryAssetObject(Assets[2]));

	CharaDataReceived = true;
}

void ANetworkPawn::ClientGetCharaData(TArray<FPrimaryAssetId> Assets)
{
	UNightSkyGameInstance* GameInstance = Cast<UNightSkyGameInstance>(GetGameInstance());
	
	GameInstance->BattleData.PlayerListP1[0] = Cast<UPrimaryCharaData>(UAssetManager::Get().GetPrimaryAssetObject(Assets[0]));
	GameInstance->BattleData.PlayerListP1[1] = Cast<UPrimaryCharaData>(UAssetManager::Get().GetPrimaryAssetObject(Assets[1]));
	GameInstance->BattleData.PlayerListP1[2] = Cast<UPrimaryCharaData>(UAssetManager::Get().GetPrimaryAssetObject(Assets[2]));

	CharaDataReceived = true;
}

void ANetworkPawn::SendRematchToClient_Implementation()
{
	bRematchAccepted = true;
}

void ANetworkPawn::SendRematchToServer_Implementation()
{
	bRematchAccepted = true;
}

void ANetworkPawn::ServerGetFinishedLoading_Implementation(bool Finished)
{
	const UNightSkyGameInstance* GameInstance = Cast<UNightSkyGameInstance>(GetGameInstance());
	if (Finished == true && Finished == GameInstance->FinishedLoadingForNetworkBattle)
		GameInstance->TravelToBattleMap();
}

void ANetworkPawn::SendGgpoToClient_Implementation(const TArray<int8> &GgpoMessage)
{
	 if(FighterMultiplayerRunner)
	 	FighterMultiplayerRunner->connectionManager->receiveSchedule.AddTail(GgpoMessage);
}

void ANetworkPawn::SendGgpoToServer_Implementation(const TArray<int8> &GgpoMessage)
{
	 if(FighterMultiplayerRunner)
	 	FighterMultiplayerRunner->connectionManager->receiveSchedule.AddTail(GgpoMessage);
}

void ANetworkPawn::ClientGetBattleData_Implementation(FBattleData InBattleData, FNetworkMirror Mirror)
{
	UNightSkyGameInstance* GameInstance = Cast<UNightSkyGameInstance>(GetGameInstance());
	UAssetManager::Get().LoadPrimaryAssets(Mirror.PlayerList, TArray<FName>(), FStreamableDelegate::CreateUObject(this, &ANetworkPawn::ClientGetCharaData, Mirror.PlayerList));
	GameInstance->BattleData.ColorIndices[0] = InBattleData.ColorIndices[0];
	GameInstance->BattleData.ColorIndices[1] = InBattleData.ColorIndices[1];
	GameInstance->BattleData.ColorIndices[2] = InBattleData.ColorIndices[2];
	GameInstance->BattleData.RoundFormat = InBattleData.RoundFormat;
	GameInstance->BattleData.StartRoundTimer = InBattleData.StartRoundTimer;
	GameInstance->BattleData.Random = InBattleData.Random;
	GameInstance->BattleData.Stage = InBattleData.Stage;
	GameInstance->BattleData.MusicName = InBattleData.MusicName;
}

void ANetworkPawn::ServerGetBattleData_Implementation(FBattleData InBattleData, FNetworkMirror Mirror)
{
	UNightSkyGameInstance* GameInstance = Cast<UNightSkyGameInstance>(GetGameInstance());
	UAssetManager::Get().LoadPrimaryAssets(Mirror.PlayerList, TArray<FName>(), FStreamableDelegate::CreateUObject(this, &ANetworkPawn::ServerGetCharaData, Mirror.PlayerList));
	GameInstance->BattleData.ColorIndices[3] = InBattleData.ColorIndices[3];
	GameInstance->BattleData.ColorIndices[4] = InBattleData.ColorIndices[4];
	GameInstance->BattleData.ColorIndices[5] = InBattleData.ColorIndices[5];
	CharaDataReceived = true;
}

void ANetworkPawn::ServerChecksumCheck_Implementation(uint32 Checksum, int32 InFrame)
{
	if (ANightSkyGameState* GameState = Cast<ANightSkyGameState>(GetWorld()->GetGameState()))
	{
		if (GameState != nullptr)
		{
			GameState->SetOtherChecksum(Checksum, InFrame);
		}
	}
}

void ANetworkPawn::ClientChecksumCheck_Implementation(uint32 Checksum, int32 InFrame)
{
	if (ANightSkyGameState* GameState = Cast<ANightSkyGameState>(GetWorld()->GetGameState()))
	{
		if (GameState != nullptr)
		{
			GameState->SetOtherChecksum(Checksum, InFrame);
		}
	}
}
