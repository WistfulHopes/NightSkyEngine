// Fill out your copyright notice in the Description page of Project Settings.


#include "FighterMultiplayerRunner.h"

#include <fstream>

#include "Kismet/GameplayStatics.h"
#include "NightSkyEngine/Battle/Actors/NightSkyGameState.h"
#include "NightSkyEngine/Miscellaneous/NightSkyGameInstance.h"
#include "NightSkyEngine/Miscellaneous/RpcConnectionManager.h"
#include <iostream>

#include "Serialization/BufferArchive.h"

// Sets default values
AFighterMultiplayerRunner::AFighterMultiplayerRunner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = false;
	connectionManager = nullptr;
}

// Called when the game starts or when spawned
void AFighterMultiplayerRunner::BeginPlay()
{
	Super::BeginPlay();
	GGPOSessionCallbacks cb = CreateCallbacks();
	connectionManager = new RpcConnectionManager();
	GGPONet::ggpo_start_session(&ggpo, &cb, connectionManager,"", 2, sizeof(int));
	GGPONet::ggpo_set_disconnect_timeout(ggpo, 45000);
	GGPONet::ggpo_set_disconnect_notify_start(ggpo, 15000);
	for (int i = 0; i < 2; i++)
	{
		GGPOPlayerHandle handle;
		GGPOPlayer* player = new GGPOPlayer();
		player->type = GGPO_PLAYERTYPE_REMOTE;
		if(i == GameState->GameInstance->PlayerIndex)
		{
			player->type = GGPO_PLAYERTYPE_LOCAL;
			connectionManager->playerIndex = i == 0 ? 1 : 0;	
		}
		player->player_num = i + 1;
		player->connection_id = i;
		GGPONet::ggpo_add_player(ggpo, player, &handle);
		if(player->type == GGPO_PLAYERTYPE_LOCAL)
			GGPONet::ggpo_set_frame_delay(ggpo,handle,2);// TODO: Logic for framedelay (based on ping? or make user choose?)
		Players.Add(player);
		PlayerInputIndex.Add(-1);
		PlayerHandles.Add(handle);
	}
	GGPONet::ggpo_try_synchronize_local(ggpo);
}

void AFighterMultiplayerRunner::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	
	delete connectionManager;
}


GGPOSessionCallbacks AFighterMultiplayerRunner::CreateCallbacks()
{
	GGPOSessionCallbacks cb = {0};

	cb.begin_game = std::bind(&AFighterMultiplayerRunner::BeginGameCallback, this, std::placeholders::_1);
	cb.save_game_state = std::bind(&AFighterMultiplayerRunner::SaveGameStateCallback, this,
	                               std::placeholders::_1, std::placeholders::_2, std::placeholders::_3,
	                               std::placeholders::_4);
	cb.load_game_state = std::bind(&AFighterMultiplayerRunner::LoadGameStateCallback, this,
	                               std::placeholders::_1, std::placeholders::_2);
	cb.log_game_state = std::bind(&AFighterMultiplayerRunner::LogGameState, this,
	                              std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	cb.free_buffer = std::bind(&AFighterMultiplayerRunner::FreeBuffer, this, std::placeholders::_1);
	cb.advance_frame = std::bind(&AFighterMultiplayerRunner::AdvanceFrameCallback, this, std::placeholders::_1);
	cb.on_event = std::bind(&AFighterMultiplayerRunner::OnEventCallback, this, std::placeholders::_1);

	return cb;
}

bool AFighterMultiplayerRunner::BeginGameCallback(const char*)
{
	return true;
}

bool AFighterMultiplayerRunner::SaveGameStateCallback(unsigned char** buffer, int32* len, int32* checksum, int32)
{
	GameState->SaveGameState(checksum);
	int BackupFrame = GameState->LocalFrame % MaxRollbackFrames;
	FRollbackData rollbackdata = GameState->MainRollbackData[BackupFrame];
	FBPRollbackData bprollbackdata = GameState->BPRollbackData[BackupFrame];
	FBufferArchive Ar(false);
	Ar.SetWantBinaryPropertySerialization(true);
	bprollbackdata.Serialize(Ar);
	rollbackdata.SizeOfBPRollbackData = Ar.Num();

	*len = sizeof(FRollbackData) + Ar.Num();
	*buffer = new unsigned char[*len];
	
	FMemory::Memcpy(*buffer, &rollbackdata, sizeof(FRollbackData));
	FMemory::Memcpy(*buffer + sizeof(FRollbackData), Ar.GetData(), Ar.Num());
	return true;
}

bool AFighterMultiplayerRunner::LoadGameStateCallback(unsigned char* buffer, int32 len)
{
	int BackupFrame = GameState->LocalFrame % MaxRollbackFrames;
	FRollbackData* rollbackdata = &GameState->MainRollbackData[BackupFrame];
	FBPRollbackData* bprollbackdata = &GameState->BPRollbackData[BackupFrame];
	
	FMemory::Memcpy(rollbackdata, buffer, sizeof(FRollbackData));

	uint8* BPBuffer = new uint8[len - sizeof(FRollbackData)];
	FMemory::Memcpy(BPBuffer, buffer + sizeof(FRollbackData), len - sizeof(FRollbackData));

	const TArray BPArray(BPBuffer, rollbackdata->SizeOfBPRollbackData);
	FMemoryReader Ar(BPArray);
	Ar.SetWantBinaryPropertySerialization(true);
	bprollbackdata->Serialize(Ar);
	
	GameState->LoadGameState();
	return true;
}

bool AFighterMultiplayerRunner::LogGameState(const char* filename, unsigned char* buffer, int len)
{
	FString savedDir = FPaths::ConvertRelativePathToFull(FPaths::ProjectSavedDir());

	savedDir.Append(filename);
	std::ofstream file;
	file.open(TCHAR_TO_ANSI(*savedDir));
	if (file.is_open())
	{
		FRollbackData* rollbackdata = (FRollbackData*)malloc(sizeof(FRollbackData));
		memcpy(rollbackdata, buffer, sizeof(FRollbackData));
		file << "GameState:\n";
		FBattleState BattleState;
		FMemory::Memcpy(&BattleState, rollbackdata->BattleStateBuffer, SizeOfBattleState);
		file << "\tFrameNumber: " << BattleState.FrameNumber << std::endl;
		file << "\tActiveObjectCount: " << BattleState.ActiveObjectCount << std::endl;
		for (int i = 0; i < MaxBattleObjects; i++)
		{
			if (rollbackdata->ObjActive[i])
			{
				ABattleObject* BattleActor = NewObject<ABattleObject>();
				FMemory::Memcpy(reinterpret_cast<char*>(BattleActor) + offsetof(ABattleObject, ObjSync), rollbackdata->ObjBuffer[i], SizeOfBattleObject);
				BattleActor->LogForSyncTestFile(file);
			}
		}
		for (int i = MaxBattleObjects; i < MaxBattleObjects + MaxPlayerObjects; i++)
		{
			APlayerObject* PlayerCharacter = NewObject<APlayerObject>();
			FMemory::Memcpy(reinterpret_cast<char*>(PlayerCharacter) + offsetof(ABattleObject, ObjSync), rollbackdata->ObjBuffer[i], SizeOfBattleObject);
			FMemory::Memcpy(reinterpret_cast<char*>(PlayerCharacter) + offsetof(APlayerObject, PlayerSync), rollbackdata->CharBuffer[i - MaxBattleObjects], SizeOfPlayerObject);
			PlayerCharacter->LogForSyncTestFile(file);
		}
		
		file << "RawRollbackData:\n";
		file << "\tStateBuffer:\n";
		file << "\n\t0: ";
		for (int x = 0; x < SizeOfBattleState; x++)
		{
			file << std::hex << std::uppercase << static_cast<int>(rollbackdata->BattleStateBuffer[x]) << " ";
			if(x % 16 == 0)
			{
				file << "\n\t" << std::hex << std::uppercase << x << ": ";
			}
		}
		file << "\n";
		file << "\tObjBuffer:\n";
		for (int i = 0; i < MaxBattleObjects + MaxPlayerObjects; i++)
		{
			file << "Object " << i << ":\n";
			file << "\n\t0: ";
			for (int x = 0; x < SizeOfBattleObject; x++)
			{
				file << std::hex << std::uppercase << static_cast<int>(rollbackdata->ObjBuffer[i][x]) << " ";
				if(x % 16 == 0)
				{
					file << "\n\t" << std::hex << std::uppercase << x << ": ";
				}
			}
			file << "\n";
		}
		file << "\n";
		file << "\tObjActive:\n";
		for (int i = 0; i < MaxBattleObjects; i++)
		{
			file << rollbackdata->ObjActive[i] << " ";
		}
		file << "\n";
		file << "\tPlayerBuffer:\n";
		for (int i = 0; i < MaxPlayerObjects; i++)
		{
			file << "Player " << i << ":\n";
			file << "\n\t0: ";
			for (int x = 0; x < SizeOfPlayerObject; x++)
			{
				file << std::hex << std::uppercase << static_cast<int>(rollbackdata->CharBuffer[i][x]) << " ";
				if(x % 16 == 0)
				{
					file << "\n\t" << std::hex << std::uppercase << x << ": ";
				}
			}
			file << "\n";
		}
		file << "\n";

		int checksum = fletcher32_checksum((short*)buffer, sizeof(FRollbackData) / 2);
		file << "RawBuffer:\n";
		file << "\tFletcher32Checksum: " << checksum << "\n";
		file << "\tBuffer:\n\t0: ";
		for (int i = 0; i < sizeof(FRollbackData); i++)
		{
			file << std::hex << std::uppercase << static_cast<int>(buffer[i]) << " ";
			if(i % 16 == 0)
			{
				file << "\n\t" << std::hex << std::uppercase << i << ": ";
			}
		}
		
		delete[] buffer;
		file.close();
	}
	return true;
}

void AFighterMultiplayerRunner::FreeBuffer(void* buffer)
{
	delete[] static_cast<char*>(buffer);
}

bool AFighterMultiplayerRunner::AdvanceFrameCallback(int flag)
{
	int inputs[2] = {0};
	int disconnect_flags;
	GGPONet::ggpo_synchronize_input(ggpo, (void*)inputs, sizeof(int) * 2, &disconnect_flags);
	GameState->UpdateGameState(inputs[0], inputs[1], true);
	GGPONet::ggpo_advance_frame(ggpo);
	return true;
}

bool AFighterMultiplayerRunner::OnEventCallback(GGPOEvent* info)
{
	int progress;
	switch (info->code)
	{
	case GGPO_EVENTCODE_CONNECTED_TO_PEER:
		UE_LOG(LogTemp, Warning, TEXT("GGPO_EVENTCODE_CONNECTED_TO_PEER"));
		break;
	case GGPO_EVENTCODE_SYNCHRONIZING_WITH_PEER:
		UE_LOG(LogTemp, Warning, TEXT("GGPO_EVENTCODE_SYNCHRONIZING_WITH_PEER"));
	//synchronized = false;
		progress = 100 * info->u.synchronizing.count / info->u.synchronizing.total;
		break;
	case GGPO_EVENTCODE_SYNCHRONIZED_WITH_PEER:
		UE_LOG(LogTemp, Warning, TEXT("GGPO_EVENTCODE_SYNCHRONIZED_WITH_PEER"));
		if (GameState->GameInstance->FighterRunner == Multiplayer && !GameState->GameInstance->IsReplay)
		{
			GameState->GameInstance->EndRecordReplay();
			GameState->GameInstance->RecordReplay();
		}
	//synchronized = true;
		break;
	case GGPO_EVENTCODE_RUNNING:
		UE_LOG(LogTemp, Warning, TEXT("GGPO_EVENTCODE_RUNNING"));

		break;
	case GGPO_EVENTCODE_CONNECTION_INTERRUPTED:
		UE_LOG(LogTemp, Warning, TEXT("GGPO_EVENTCODE_CONNECTION_INTERRUPTED"));
	// connectionLost = true;
	// FightGameInstance->ErrorMessage = FString("Connection interrupted");
	// EndOnline(true);
		UGameplayStatics::OpenLevel(GetGameInstance(), FName(TEXT("MainMenu_PL")));
		break;
	case GGPO_EVENTCODE_CONNECTION_RESUMED:
		//connectionLost = false;
		UE_LOG(LogTemp, Warning, TEXT("GGPO_EVENTCODE_CONNECTION_RESUMED"));

		break;
	case GGPO_EVENTCODE_DISCONNECTED_FROM_PEER:
		UE_LOG(LogTemp, Warning, TEXT("GGPO_EVENTCODE_DISCONNECTED_FROM_PEER"));
		UGameplayStatics::OpenLevel(GetGameInstance(), FName(TEXT("MainMenu_PL")));
	//FightGameInstance->ErrorMessage = FString("Enemy disconnected");
	//EndOnline(true);
		break;
	case GGPO_EVENTCODE_TIMESYNC:
		UE_LOG(LogTemp, Warning, TEXT("GGPO_EVENTCODE_TIMESYNC"));
		//if(MultipliedFramesAhead>3)
		{
			MultipliedFramesAhead=info->u.timesync.frames_ahead*TimesyncMultiplier;
		}
		break;
	case GGPO_EVENTCODE_TIMESYNC_BEHIND:
		UE_LOG(LogTemp, Warning, TEXT("GGPO_EVENTCODE_TIMESYNC_BEHIND"));
		//MultipliedFramesBehind=info->u.timesync.frames_ahead*TimesyncMultiplier;
		break;
	}
	return true;
}


void AFighterMultiplayerRunner::GgpoUpdate()
{
	GGPOErrorCode result = GGPOErrorCode::GGPO_OK;
	int disconnect_flags;
	int inputs[2] = {0};
	for (int i = 0; i < 2; ++i)
	{
		if (Players[i]->type == GGPO_PLAYERTYPE_LOCAL)
		{
			int input = 0;
			if (PlayerInputIndex[i] == -1)
			{
				for (int index = 0; index < 4; index++)
				{
					input |= GameState->GetLocalInputs(index);
				}
			}
			else
			{
				input = GameState->GetLocalInputs(PlayerInputIndex[i]);
			}

			result = GGPONet::ggpo_add_local_input(ggpo, PlayerHandles[i], &input, sizeof(input));
		}
	}
	if (GGPO_SUCCEEDED(result))
	{
		result = GGPONet::ggpo_synchronize_input(ggpo, (void*)inputs, sizeof(int) * 2, &disconnect_flags);
		if (GGPO_SUCCEEDED(result))
		{
			GameState->UpdateGameState(inputs[0], inputs[1], false);
			GGPONet::ggpo_advance_frame(ggpo);
		}
	}
}

void AFighterMultiplayerRunner::Update(float DeltaTime)
{
	ElapsedTime += DeltaTime;
	
	while (ElapsedTime >= OneFrame)
	{
		if(MultipliedFramesAhead>0)
		{
			int ahead = MultipliedFramesAhead;
			MultipliedFramesAhead--;
			if(ahead%TimesyncMultiplier==0)
			{
				ElapsedTime=0;
				break;
			}
		}
		GgpoUpdate();
		ElapsedTime -= OneFrame;
		// if(MultipliedFramesBehind>0)
		// {
		// 	MultipliedFramesBehind--;
		// 	if(MultipliedFramesBehind%TimesyncMultiplier)
		// 	{
		// 		accumulatorBreaker=0;
		// 		ElapsedTime += OneFrame;
		// 	}	
		// }
		//
	}
	GGPONet::ggpo_idle(ggpo,1);
}


//TODO refactor to a static libaray
int
AFighterMultiplayerRunner::fletcher32_checksum(short* data, size_t len)
{
	int sum1 = 0xffff, sum2 = 0xffff;

	while (len)
	{
		size_t tlen = len > 360 ? 360 : len;
		len -= tlen;
		do
		{
			sum1 += *data++;
			sum2 += sum1;
		}
		while (--tlen);
		sum1 = (sum1 & 0xffff) + (sum1 >> 16);
		sum2 = (sum2 & 0xffff) + (sum2 >> 16);
	}

	/* Second reduction step to reduce sums to 16 bits */
	sum1 = (sum1 & 0xffff) + (sum1 >> 16);
	sum2 = (sum2 & 0xffff) + (sum2 >> 16);
	return sum2 << 16 | sum1;
}
