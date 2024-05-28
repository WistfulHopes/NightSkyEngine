// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AdvancedFriendsGameInstance.h"
#include "FighterRunners.h"
#include "NightSkyEngine/Battle/RandomManager.h"
#include "Engine/GameInstance.h"
#include "NightSkyGameInstance.generated.h"

class UNightSkySettingsInfo;
class USoundData;
constexpr int32 MaxReplays = 999;

class APlayerObject;
class UReplaySaveInfo;
enum class ERoundFormat : uint8;

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
	FString StageURL;
	UPROPERTY(BlueprintReadWrite)
	FString MusicName;
};

/**
 * 
 */
UCLASS()
class NIGHTSKYENGINE_API UNightSkyGameInstance : public UAdvancedFriendsGameInstance
{
	GENERATED_BODY()

	UPROPERTY()
	UReplaySaveInfo* CurrentReplay;
	
	virtual void Init() override;

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Replays")  
	void BP_OnFindReplaysComplete(const TArray<UReplaySaveInfo*> &AllReplays);
	
public:
	bool FinishedLoadingForNetworkBattle = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString GameVersion;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString BattleVersion;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UNightSkySettingsInfo> SettingsInfo;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundData> MusicData;

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

	UFUNCTION(BlueprintCallable)
	void TravelToVSInfo() const;
	void TravelToBattleMap() const;

	void LoadReplay();
	void PlayReplayToGameState(int32 FrameNumber, int32& OutP1Input, int32& OutP2Input) const;
	
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
