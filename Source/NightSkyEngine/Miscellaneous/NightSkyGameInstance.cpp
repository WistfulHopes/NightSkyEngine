// Fill out your copyright notice in the Description page of Project Settings.


#include "NightSkyGameInstance.h"

#include "NightSkySettingsInfo.h"
#include "ReplayInfo.h"
#include "Kismet/GameplayStatics.h"

void UNightSkyGameInstance::Init()
{
	Super::Init();

	BattleData.Random = FRandomManager(FGenericPlatformMath::Rand());

	SettingsInfo = Cast<UNightSkySettingsInfo>(UGameplayStatics::LoadGameFromSlot("SYSTEM", 0));
	if (!SettingsInfo)
	{
		SettingsInfo = Cast<UNightSkySettingsInfo>(UGameplayStatics::CreateSaveGameObject(UNightSkySettingsInfo::StaticClass()));
		UGameplayStatics::SaveGameToSlot(SettingsInfo, "SYSTEM", 0);
	}

	const FString AntiAliasingCommand = "r.AntiAliasingMethod " + FString::FromInt(SettingsInfo->AntiAliasingMethod);
	const FString GlobalIlluminationCommand = "r.DynamicGlobalIlluminationMethod " + FString::FromInt(SettingsInfo->GlobalIlluminationMethod);

	GetWorld()->Exec(GetWorld(), *AntiAliasingCommand);
	GetWorld()->Exec(GetWorld(), *GlobalIlluminationCommand);
}

void UNightSkyGameInstance::TravelToVSInfo() const
{
	this->GetWorld()->ServerTravel("VSInfo_PL", true);
}

void UNightSkyGameInstance::TravelToBattleMap() const
{
	this->GetWorld()->ServerTravel(BattleData.StageURL, true);
}

void UNightSkyGameInstance::LoadReplay()
{
	BattleData = CurrentReplay->BattleData;
}

void UNightSkyGameInstance::PlayReplayToGameState(int32 FrameNumber, int32& OutP1Input, int32& OutP2Input) const
{
	if (FrameNumber >= CurrentReplay->LengthInFrames)
	{
		UGameplayStatics::OpenLevel(this, FName(TEXT("MainMenu_PL")));
		return;
	}
	OutP1Input = CurrentReplay->InputsP1[FrameNumber];
	OutP2Input = CurrentReplay->InputsP2[FrameNumber];
}

void UNightSkyGameInstance::RecordReplay()
{
	CurrentReplay = Cast<UReplaySaveInfo>(UGameplayStatics::CreateSaveGameObject(UReplaySaveInfo::StaticClass()));
	CurrentReplay->BattleData = BattleData;
	CurrentReplay->Version = BattleVersion;
}

void UNightSkyGameInstance::UpdateReplay(int32 InputsP1, int32 InputsP2) const
{
	CurrentReplay->LengthInFrames++;
	CurrentReplay->InputsP1.Add(InputsP1);
	CurrentReplay->InputsP2.Add(InputsP2);
}

void UNightSkyGameInstance::RollbackReplay(int32 FramesToRollback) const
{
	for (int i = 0; i < FramesToRollback; i++)
	{
		CurrentReplay->LengthInFrames--;
		CurrentReplay->InputsP1.Pop();
		CurrentReplay->InputsP2.Pop();
	}
}

void UNightSkyGameInstance::EndRecordReplay() const
{
	if (IsReplay || IsTraining) return;
	FString ReplayName = "REPLAY";
	for (int i = 0; i < MaxReplays; i++)
	{
		ReplayName = "REPLAY";
		ReplayName.AppendInt(i);
		if (!UGameplayStatics::DoesSaveGameExist(ReplayName, 0))
		{
			break;
		}
	}
	UGameplayStatics::SaveGameToSlot(CurrentReplay, ReplayName, 0);
}

void UNightSkyGameInstance::PlayReplayFromBP(FString ReplayName)
{
	FighterRunner = Multiplayer;
	IsTraining = false;
	IsReplay = true;
	CurrentReplay = Cast<UReplaySaveInfo>(UGameplayStatics::LoadGameFromSlot(ReplayName, 0));
	LoadReplay();
}

void UNightSkyGameInstance::FindReplays()
{
	ReplayList.Empty();
	for (int i = 0; i < MaxReplays; i++)
	{
		FString ReplayName = "REPLAY";
		ReplayName.AppendInt(i);
		if (!UGameplayStatics::DoesSaveGameExist(ReplayName, 0))
		{
			continue;
		}
		ReplayList.Add(Cast<UReplaySaveInfo>(UGameplayStatics::LoadGameFromSlot(ReplayName, 0)));
		ReplayList.Last()->ReplayIndex = i;
		if (ReplayList.Last()->Version != BattleVersion)
		{
			ReplayList.Pop();
			UGameplayStatics::DeleteGameInSlot(ReplayName, 0);
		}
	}
	BP_OnFindReplaysComplete(ReplayList);
}

void UNightSkyGameInstance::DeleteReplay(const FString& ReplayName)
{
	if (UGameplayStatics::DoesSaveGameExist(ReplayName, 0))
	{
		UGameplayStatics::DeleteGameInSlot(ReplayName, 0);
	}
	FindReplays();
}