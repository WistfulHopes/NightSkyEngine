// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "NightSkyGameInstance.h"
#include "NetworkPawn.generated.h"

class APlayerObject;

UCLASS()
class NIGHTSKYENGINE_API ANetworkPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ANetworkPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	UPROPERTY(BlueprintReadOnly, Replicated)
	bool CharaDataReceived = false;
	UPROPERTY(BlueprintReadOnly, Replicated)
	bool bRematchAccepted = false;
	
	UFUNCTION( Server, Reliable )
	void ServerChecksumCheck(uint32 Checksum, int32 InFrame);
	UFUNCTION( Client, Reliable )
	void ClientChecksumCheck(uint32 Checksum, int32 InFrame);
	UFUNCTION( Server, Reliable )
	void ServerGetBattleData(FBattleData InBattleData);
	UFUNCTION( Client, Reliable )
	void ClientGetBattleData(FBattleData InBattleData);
	UFUNCTION( Server, Reliable )
	void ServerGetFinishedLoading(bool Finished);

	UPROPERTY()
	class AFighterMultiplayerRunner* FighterMultiplayerRunner = nullptr;
	
	UFUNCTION( Server, Reliable )
	void SendGgpoToServer(const TArray<int8> &GgpoMessage);
	UFUNCTION( Client, Reliable )
	void SendGgpoToClient(const TArray<int8> &GgpoMessage);
	
	UFUNCTION( Server, Reliable )
	void SendRematchToServer();
	UFUNCTION( Client, Reliable )
	void SendRematchToClient();
};
