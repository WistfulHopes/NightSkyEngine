// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkPawn.h"

#include "NightSkyGameInstance.h"
#include "RpcConnectionManager.h"
#include "NightSkyEngine/Battle/Actors/NightSkyGameState.h"
#include "Net/UnrealNetwork.h"
#include "NightSkyEngine/Battle/Actors/FighterRunners/FighterMultiplayerRunner.h"

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

void ANetworkPawn::ClientGetBattleData_Implementation(FBattleData InBattleData)
{
	UNightSkyGameInstance* GameInstance = Cast<UNightSkyGameInstance>(GetGameInstance());
	GameInstance->BattleData.PlayerList[0] = InBattleData.PlayerList[0];
	GameInstance->BattleData.PlayerList[1] = InBattleData.PlayerList[1];
	GameInstance->BattleData.PlayerList[2] = InBattleData.PlayerList[2];
	GameInstance->BattleData.RoundFormat = InBattleData.RoundFormat;
	GameInstance->BattleData.StartRoundTimer = InBattleData.StartRoundTimer;
	GameInstance->BattleData.Random = InBattleData.Random;
	CharaDataReceived = true;
}

void ANetworkPawn::ServerGetBattleData_Implementation(FBattleData InBattleData)
{
	UNightSkyGameInstance* GameInstance = Cast<UNightSkyGameInstance>(GetGameInstance());
	GameInstance->BattleData.PlayerList[3] = InBattleData.PlayerList[3];
	GameInstance->BattleData.PlayerList[4] = InBattleData.PlayerList[4];
	GameInstance->BattleData.PlayerList[5] = InBattleData.PlayerList[5];
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

void ANetworkPawn::SendToClient_Implementation(const TArray<int32> &InInputs, int32 InFrame)
{
	if (ANightSkyGameState* GameState = Cast<ANightSkyGameState>(GetWorld()->GetGameState()))
	{
		if (GameState != nullptr)
		{
			int SendInputs[MaxRollbackFrames];
			for (int i = 0; i < MaxRollbackFrames; i++)
			{
				SendInputs[i] = InInputs[i];
			}
			GameState->UpdateRemoteInput(SendInputs, InFrame);
		}
	}
}

void ANetworkPawn::SendToServer_Implementation(const TArray<int32> &InInputs, int32 InFrame)
{
	if (ANightSkyGameState* GameState = Cast<ANightSkyGameState>(GetWorld()->GetGameState()))
	{
		if (GameState != nullptr)
		{
			int SendInputs[MaxRollbackFrames];
			for (int i = 0; i < MaxRollbackFrames; i++)
			{
				SendInputs[i] = InInputs[i];
			}
			GameState->UpdateRemoteInput(SendInputs, InFrame);
		}
	}
}

