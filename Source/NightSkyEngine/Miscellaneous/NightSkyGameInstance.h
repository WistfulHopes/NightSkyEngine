// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FighterRunners.h"
#include "OnlineLobbyInterface.h"
#include "OnlineSessionSettings.h"
#include "RandomManager.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "NightSkyGameInstance.generated.h"

inline FString GameVersion = "0.0.1A";
constexpr int32 MaxReplays = 999;

class APlayerObject;
class UReplaySaveInfo;
enum class ERoundFormat : uint8;

USTRUCT(BlueprintType)
struct FFriendInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FString DisplayName;
	FUniqueNetIdPtr NetId;
};

USTRUCT(BlueprintType)
struct FSessionInfo
{
	GENERATED_BODY()

	FOnlineSessionSearchResult Result;
	UPROPERTY(BlueprintReadOnly)
	FString ConnectInfo;
};

USTRUCT(BlueprintType)
struct FBattleData
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<TSubclassOf<APlayerObject>> PlayerList;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<int32> ColorIndices;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ERoundFormat RoundFormat;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 StartRoundTimer;
	UPROPERTY()
	FRandomManager Random;
	UPROPERTY(BlueprintReadWrite)
	FString StageURL = "TestMap_PL";
};

/**
 * 
 */
UCLASS()
class NIGHTSKYENGINE_API UNightSkyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
	FDelegateHandle LoginDelegateHandle;
	FDelegateHandle FindSessionsDelegateHandle;
	FDelegateHandle JoinSessionDelegateHandle;
	FDelegateHandle DestroySessionDelegateHandle;
	FDelegateHandle CreateSessionDelegateHandle;
	int SessionIndex;
	TSharedPtr<const FOnlineLobbyId> LobbyID;
	UPROPERTY()
	UReplaySaveInfo* CurrentReplay;
	
	void OnSessionInviteAccepted(bool bArg, int I, TSharedPtr<const FUniqueNetId, ESPMode::ThreadSafe> UniqueNetId, const FOnlineSessionSearchResult& OnlineSessionSearchResult);
	void HandleLoginComplete(int I, bool bArg, const FUniqueNetId& UniqueNetId, const FString& String);
	void OnReadComplete(int I, bool bArg, const FString& String, const FString& String1);
	void HandleFindSessionsComplete(bool bArg, TSharedRef<FOnlineSessionSearch, ESPMode::ThreadSafe> Shared);
	void HandleJoinSessionComplete(FName Name, EOnJoinSessionCompleteResult::Type Arg);
	void HandleJoinInviteSessionComplete(FName Name, EOnJoinSessionCompleteResult::Type Arg);
	void HandleDestroySessionComplete(FName Name, bool bArg);
	void HandleCreateSessionComplete(FName Name, bool bArg);

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Replays")  
	void BP_OnFindReplaysComplete(const TArray<UReplaySaveInfo*> &AllReplays);
	
public:
	UPROPERTY()
	TArray<UReplaySaveInfo*> ReplayList;
	UPROPERTY(BlueprintReadWrite)
	int PlayerIndex;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FBattleData BattleData;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool IsTraining = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool IsCPUBattle = false;
	UPROPERTY(BlueprintReadWrite)
	bool IsReplay = false;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TEnumAsByte<EFighterRunners> FighterRunner;	
	UPROPERTY(BlueprintReadOnly)
	TArray<FFriendInfo> FriendInfos;
	UPROPERTY(BlueprintReadOnly)
	TArray<FSessionInfo> SessionInfos;
	UPROPERTY(BlueprintReadOnly)
	TArray<FString> LobbyIDs;
	TArray<TSharedRef<const FOnlineLobbyId>> LobbyInfos;

	FOnlineSessionSearchResult InviteResult;

	UFUNCTION(BlueprintCallable)
	bool Login();
	UFUNCTION(BlueprintCallable)
	bool GetFriendsList();
	UFUNCTION(BlueprintCallable)
	bool CreateSession();
	UFUNCTION(BlueprintCallable)
	bool CreateLobby();
	UFUNCTION(BlueprintCallable)
	bool SearchForServer();
	UFUNCTION(BlueprintCallable)
	bool SearchForLobby();
	UFUNCTION(BlueprintCallable)
	bool JoinServer(FString ConnectInfo);
	UFUNCTION(BlueprintCallable)
	bool JoinLobby(FString InLobbyID);
	UFUNCTION(BlueprintCallable)
	bool DestroySession();
	UFUNCTION(BlueprintCallable)
	bool DestroyLobby();
	UFUNCTION(BlueprintCallable)
	void SeamlessTravel();

	void LoadReplay();
	void PlayReplayToGameState(int32 FrameNumber, int32& OutP1Input, int32& OutP2Input);
	
	void RecordReplay();
	void UpdateReplay(int32 InputsP1, int32 InputsP2) const;
	void RollbackReplay(int32 FramesToRollback) const;
	void EndRecordReplay() const;
	
	/** Start playback for a previously recorded Replay, from blueprint */   
	UFUNCTION(BlueprintCallable, Category = "Replays")   
	void PlayReplayFromBP(FString ReplayName);   
  
	/** Start looking for/finding replays on the hard drive */  
	UFUNCTION(BlueprintCallable, Category = "Replays")  
	void FindReplays(); 
  
	/** Delete a previously recorded replay */
	UFUNCTION(BlueprintCallable, Category = "Replays")
	void DeleteReplay(const FString &ReplayName);
};
