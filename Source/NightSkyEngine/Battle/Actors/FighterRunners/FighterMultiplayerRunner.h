// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FighterLocalRunner.h"
#include "include/ggponet.h"
#include "FighterMultiplayerRunner.generated.h"

constexpr int TimesyncMultiplier =4;

UCLASS()
class NIGHTSKYENGINE_API AFighterMultiplayerRunner : public AFighterLocalRunner
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFighterMultiplayerRunner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	GGPOSessionCallbacks CreateCallbacks();
	bool __cdecl BeginGameCallback(const char*);
	bool __cdecl SaveGameStateCallback(unsigned char** buffer, int32* len, int32* checksum, int32);
	bool __cdecl LoadGameStateCallback(unsigned char* buffer, int32 len);
	bool __cdecl LogGameState(const char* filename, unsigned char* buffer, int len);
	void __cdecl FreeBuffer(void* buffer);
	bool __cdecl AdvanceFrameCallback(int32);
	bool __cdecl OnEventCallback(GGPOEvent* info);

public:
	GGPOSession* ggpo = nullptr;
	TArray<GGPOPlayerHandle> PlayerHandles;
	TArray<GGPOPlayer*> Players;

protected:
	TArray<int> PlayerInputIndex;
	void GgpoUpdate();

	int MultipliedFramesAhead=0;
	int MultipliedFramesBehind=0;
	
public:	
	virtual void Update(float DeltaTime) override;
	class RpcConnectionManager* connectionManager;

	static int	fletcher32_checksum(short* data, size_t len);
};
