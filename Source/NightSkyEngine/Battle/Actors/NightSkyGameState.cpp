// Fill out your copyright notice in the Description page of Project Settings.


#include "NightSkyGameState.h"
#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"
#include "NightSkyPlayerController.h"
#include "ParticleManager.h"
#include "Camera/CameraActor.h"
#include "CineCameraActor.h"
#include "Camera/CameraComponent.h"
#include "Components/AudioComponent.h"
#include "Components/SlateWrapperTypes.h"
#include "FighterRunners/FighterReplayRunner.h"
#include "FighterRunners/FighterSynctestRunner.h"
#include "Kismet/GameplayStatics.h"
#include "NightSkyEngine/Battle/Globals.h"
#include "NightSkyEngine/Data/BattleExtensionData.h"
#include "NightSkyEngine/Miscellaneous/FighterRunners.h"
#include "NightSkyEngine/Miscellaneous/NightSkyGameInstance.h"
#include "NightSkyEngine/UI/NightSkyBattleHudActor.h"
#include "NightSkyEngine/UI/NightSkyBattleWidget.h"

void FBPRollbackData::Serialize(FArchive& Ar)
{
	Ar << PlayerData;
	Ar << StateData;
	Ar << ExtensionData;
}

// Sets default values
ANightSkyGameState::ANightSkyGameState()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ANightSkyGameState::BeginPlay()
{
	Super::BeginPlay();

	FActorSpawnParameters SpawnParameters;
	ParticleManager = GetWorld()->SpawnActor<AParticleManager>();
	AudioManager = GetWorld()->SpawnActor<AAudioManager>();
	GameInstance = Cast<UNightSkyGameInstance>(GetGameInstance());
	CameraActor = GetWorld()->SpawnActor<ACameraActor>(ACameraActor::StaticClass());
	CameraActor->GetCameraComponent()->SetFieldOfView(54);
	SequenceCameraActor = GetWorld()->SpawnActor<ACineCameraActor>(ACineCameraActor::StaticClass());
	SequenceActor = GetWorld()->SpawnActor<ALevelSequenceActor>(ALevelSequenceActor::StaticClass());
	
	const FVector NewCameraLocation = BattleSceneTransform.GetRotation().RotateVector(FVector(0, 1080, 175)) + BattleSceneTransform.GetLocation();
	FRotator CameraRotation = BattleSceneTransform.GetRotation().Rotator();
	CameraRotation.Yaw -= 90;

	BattleState.PrevCameraPosition = NewCameraLocation;
	CameraActor->SetActorLocation(NewCameraLocation);
	CameraActor->SetActorRotation(CameraRotation);
	SequenceCameraActor->SetActorLocation(NewCameraLocation);
	SequenceCameraActor->SetActorRotation(CameraRotation);
	
	Init();
}

void ANightSkyGameState::Init()
{
	BattleState.RandomManager = GameInstance->BattleData.Random;
	
	for (int i = 0; i < MaxRollbackFrames; i++)
	{
		MainRollbackData.Add(FRollbackData());
		BPRollbackData.Add(FBPRollbackData());
	}

	if (IsValid(BattleExtensionData))
	{
		for (auto Extension : BattleExtensionData->ExtensionArray)
		{
			BattleExtensions.Add(NewObject<UBattleExtension>(this, Extension));
			BattleExtensions.Last()->Parent = this;
			BattleExtensionNames.Add(*BattleExtensions.Last()->Name);
		}
	}
	
	for (int i = 0; i < MaxPlayerObjects; i++)
	{
		if (GameInstance != nullptr)
		{
			if (GameInstance->BattleData.PlayerList.Num() > i)
			{
				if (GameInstance->BattleData.PlayerList[i] != nullptr)
				{
					Players[i] = GetWorld()->SpawnActor<APlayerObject>(GameInstance->BattleData.PlayerList[i], BattleSceneTransform);
					Players[i]->ColorIndex = 1;
					if (GameInstance->BattleData.ColorIndices.Num() > i)
						Players[i]->ColorIndex = GameInstance->BattleData.ColorIndices[i];
					for (int j = 0; j < i; j++)
					{
						if (IsValid(GameInstance->BattleData.PlayerList[j]))
						{
							if (Players[i]->IsA(GameInstance->BattleData.PlayerList[j]))
							{
								if (Players[i]->ColorIndex == Players[j]->ColorIndex)
								{
									if (Players[j]->ColorIndex > 1)
										Players[i]->ColorIndex = 1;
									else
										Players[i]->ColorIndex = 2;
								}
								break;
							}
						}
					}
				}
				else
				{
					Players[i] = GetWorld()->SpawnActor<APlayerObject>(APlayerObject::StaticClass(), BattleSceneTransform);
				}
			}
			else
			{
				Players[i] = GetWorld()->SpawnActor<APlayerObject>(APlayerObject::StaticClass(), BattleSceneTransform);
			}
			SortedObjects[i] = Players[i];
		}
		else
		{
			Players[i] = GetWorld()->SpawnActor<APlayerObject>(APlayerObject::StaticClass(), BattleSceneTransform);
			SortedObjects[i] = Players[i];
		}
		Players[i]->InitPlayer();
		Players[i]->GameState = this;
		SortedObjects[i] = Players[i];

		if (i >= MaxPlayerObjects / 2 && GameInstance->IsCPUBattle)
		{
			Players[i]->SpawnDefaultController();
		}
	}
	
	for (int i = 0; i < MaxBattleObjects; i++)
	{
		Objects[i] = GetWorld()->SpawnActor<ABattleObject>(ABattleObject::StaticClass(), BattleSceneTransform);
		Objects[i]->GameState = this;
		SortedObjects[i + MaxPlayerObjects] = Objects[i];
	}

	MatchInit();
}

void ANightSkyGameState::PlayIntros()
{
	if (GameInstance->IsTraining) {
		GetMainPlayer(true)->JumpToState(GetMainPlayer(true)->CharaStateData->DefaultStand);
		GetMainPlayer(false)->JumpToState(GetMainPlayer(false)->CharaStateData->DefaultStand);
		return;
	}
	BattleState.CurrentIntroSide = INT_P1;
	GetMainPlayer(true)->JumpToState(GetMainPlayer(true)->IntroName);
	BattleHudVisibility(false);
}

void ANightSkyGameState::RoundInit()
{
	BattleState.RandomManager.Reseed(BattleState.RandomManager.Rand() + BattleState.RoundCount);
	BattleState.RoundCount++;

	BattleState.SuperFreezeSelfDuration = 0;
	BattleState.SuperFreezeDuration = 0;
	BattleState.SuperFreezeCaller = nullptr;
	
	if (BattleState.RoundFormat < ERoundFormat::TwoVsTwo || BattleState.RoundCount == 1)
	{
		if (BattleState.RoundCount != 1)
		{
			GetMainPlayer(true)->JumpToState(GetMainPlayer(true)->CharaStateData->DefaultStand);
			GetMainPlayer(false)->JumpToState(GetMainPlayer(false)->CharaStateData->DefaultStand);
		}
		
		if (!GameInstance->IsTraining)
			BattleState.TimeUntilRoundStart = 180;
		for (int i = 0; i < MaxBattleObjects; i++)
			Objects[i]->ResetObject();
	
		for (int i = 0; i < MaxPlayerObjects; i++)
			Players[i]->RoundInit(true);

		Players[0]->PlayerFlags = PLF_IsOnScreen;
		Players[MaxPlayerObjects / 2]->PlayerFlags = PLF_IsOnScreen;

		BattleState.MaxMeter[0] = Players[0]->MaxMeter;
		BattleState.MaxMeter[1] = Players[MaxPlayerObjects / 2]->MaxMeter;
	
		BattleState.RoundTimer = GameInstance->BattleData.StartRoundTimer * 60;
		BattleState.CurrentScreenPos = 0;
		BattleState.bHUDVisible = true;
	
		const FVector NewCameraLocation = BattleSceneTransform.GetRotation().RotateVector(FVector(0, 1080, 175)) + BattleSceneTransform.GetLocation();
		FRotator CameraRotation = BattleSceneTransform.GetRotation().Rotator();
		CameraRotation.Yaw -= 90;

		BattleState.PrevCameraPosition = NewCameraLocation;
		CameraActor->SetActorLocation(NewCameraLocation);
		CameraActor->SetActorRotation(CameraRotation);

		CallBattleExtension("RoundInit");
	}
	else if (BattleState.RoundFormat < ERoundFormat::TwoVsTwoKOF)
	{
		const bool IsP1 = GetMainPlayer(true)->CurrentHealth == 0;
		GetMainPlayer(IsP1)->SetOnScreen(false);
		const auto NewPosX = GetMainPlayer(IsP1)->PosX;
		if (!SwitchMainPlayer(GetMainPlayer(IsP1), 1))
		{
			SwitchMainPlayer(GetMainPlayer(IsP1), 2);
		}
		GetMainPlayer(IsP1)->PosX = NewPosX;
		GetMainPlayer(IsP1)->PosY = 0;
		GetMainPlayer(IsP1)->JumpToState(GetMainPlayer(IsP1)->CharaStateData->DefaultTagIn);
		
		GetMainPlayer(true)->PlayerFlags &= ~PLF_RoundWinInputLock;
		GetMainPlayer(false)->PlayerFlags &= ~PLF_RoundWinInputLock;
		
		for (const auto& Player : Players) Player->RoundWinTimer = 180;
	}
	else
	{
		const bool IsP1 = GetMainPlayer(true)->CurrentHealth == 0;
		GetMainPlayer(IsP1)->SetOnScreen(false);
		SwitchMainPlayer(GetMainPlayer(IsP1), 1);

		if (BattleState.RoundCount != 1)
		{
			GetMainPlayer(true)->JumpToState(GetMainPlayer(true)->CharaStateData->DefaultStand);
			GetMainPlayer(false)->JumpToState(GetMainPlayer(false)->CharaStateData->DefaultStand);
		}
		
		if (!GameInstance->IsTraining)
			BattleState.TimeUntilRoundStart = 180;
		for (int i = 0; i < MaxBattleObjects; i++)
			Objects[i]->ResetObject();
	
		for (int i = 0; i < MaxPlayerObjects; i++)
			Players[i]->RoundInit(false);

		Players[0]->PlayerFlags = PLF_IsOnScreen;
		Players[MaxPlayerObjects / 2]->PlayerFlags = PLF_IsOnScreen;

		BattleState.MaxMeter[0] = Players[0]->MaxMeter;
		BattleState.MaxMeter[1] = Players[MaxPlayerObjects / 2]->MaxMeter;
	
		BattleState.RoundTimer = GameInstance->BattleData.StartRoundTimer * 60;
		BattleState.CurrentScreenPos = 0;
		BattleState.bHUDVisible = true;
	
		const FVector NewCameraLocation = BattleSceneTransform.GetRotation().RotateVector(FVector(0, 1080, 175)) + BattleSceneTransform.GetLocation();
		FRotator CameraRotation = BattleSceneTransform.GetRotation().Rotator();
		CameraRotation.Yaw -= 90;

		BattleState.PrevCameraPosition = NewCameraLocation;
		CameraActor->SetActorLocation(NewCameraLocation);
		CameraActor->SetActorRotation(CameraRotation);

		CallBattleExtension("RoundInit");
	}
}

void ANightSkyGameState::UpdateLocalInput()
{
	if (GameInstance->FighterRunner == LocalPlay)
	{
		LocalInputs[LocalFrame % MaxRollbackFrames][0] = GetLocalInputs(0);
		LocalInputs[LocalFrame % MaxRollbackFrames][1] = GetLocalInputs(1);
		return;
	}
	const int PlayerIndex = GameInstance->PlayerIndex;
	if (PlayerIndex == 0)
	{
		RemoteInputs[LocalFrame % MaxRollbackFrames][0] = LocalInputs[LocalFrame % MaxRollbackFrames][0] = GetLocalInputs(0);
		RemoteInputs[LocalFrame % MaxRollbackFrames][1] = LocalInputs[LocalFrame % MaxRollbackFrames][1] = LocalInputs[RemoteFrame % MaxRollbackFrames][1];
	}
	else
	{
		RemoteInputs[LocalFrame % MaxRollbackFrames][0] = LocalInputs[LocalFrame % MaxRollbackFrames][0] = LocalInputs[RemoteFrame % MaxRollbackFrames][0];
		RemoteInputs[LocalFrame % MaxRollbackFrames][1] = LocalInputs[LocalFrame % MaxRollbackFrames][1] = GetLocalInputs(0);
	}
}

// Called every frame
void ANightSkyGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FighterRunner->Update(DeltaTime);
}

void ANightSkyGameState::MatchInit()
{
	if (FighterRunner) 
	{
		FighterRunner->Destroy();
		FighterRunner = nullptr;
	}
	
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = GetOwner();

	switch (GameInstance->FighterRunner)
	{
	case LocalPlay:
		FighterRunner = GetWorld()->SpawnActor<AFighterLocalRunner>(SpawnParameters);
		break;
	case Multiplayer:
		if (GameInstance->IsReplay)
			FighterRunner = GetWorld()->SpawnActor<AFighterReplayRunner>(SpawnParameters);
		else
			FighterRunner = GetWorld()->SpawnActor<AFighterMultiplayerRunner>(SpawnParameters);
		break;
	case SyncTest:
		FighterRunner = GetWorld()->SpawnActor<AFighterSynctestRunner>(SpawnParameters);
		break;
	default:
		FighterRunner = GetWorld()->SpawnActor<AFighterLocalRunner>(SpawnParameters);
		break;
	}
	
	BattleState = FBattleState();
	BattleState = Cast<ANightSkyGameState>(GetClass()->ClassDefaultObject)->BattleState;
	for (int i = 0; i < MaxPlayerObjects; i++)
	{
		Players[i]->PlayerIndex = i * 2 >= MaxPlayerObjects;
		Players[i]->TeamIndex = i % (MaxPlayerObjects / 2);
		if (i % 3 == 0)
		{
			Players[i]->PlayerFlags |= PLF_IsOnScreen;
		}
		else
		{
			Players[i]->PlayerFlags &= ~PLF_IsOnScreen;
		}
		Players[i]->ObjNumber = i + MaxBattleObjects;
		Players[i]->CallSubroutine("CmnMatchInit");
		Players[i]->CallSubroutine("MatchInit");
	}
	for (int i = 0; i < MaxBattleObjects; i++)
	{
		Objects[i]->ObjNumber = i;
	}
	for (int i = MaxBattleObjects + MaxPlayerObjects; i >= 0; i--)
	{
		SetDrawPriorityFront(SortedObjects[i]);
	}
	
	BattleState.MainPlayer[0] = Players[0];
	BattleState.MainPlayer[1] = Players[MaxPlayerObjects / 2];
	BattleState.RoundFormat = GameInstance->BattleData.RoundFormat;
	BattleState.RoundTimer = GameInstance->BattleData.StartRoundTimer * 60;
	
	PlayMusic(GameInstance->BattleData.MusicName);
	RoundInit();
	PlayIntros();
}

void ANightSkyGameState::UpdateGameState(int32 Input1, int32 Input2, bool bShouldResimulate)
{
	if (bShouldResimulate == false && bIsResimulating == true) RollbackStartAudio(BattleState.FrameNumber);
	bIsResimulating = bShouldResimulate;
	LocalFrame++;
	ParticleManager->UpdateParticles();

	if (BattleState.CurrentIntroSide != INT_None)
	{
		if (BattleState.CurrentIntroSide == INT_P1 && GetMainPlayer(true)->GetCurrentStateName() != GetMainPlayer(true)->IntroName)
		{
			GetMainPlayer(false)->JumpToState(GetMainPlayer(false)->IntroName);
			BattleState.CurrentIntroSide = INT_P2;
		}
		else if (BattleState.CurrentIntroSide == INT_P2 && GetMainPlayer(false)->GetCurrentStateName() != GetMainPlayer(false)->IntroName)
		{
			GetMainPlayer(true)->JumpToState(GetMainPlayer(true)->CharaStateData->DefaultStand);
			GetMainPlayer(false)->JumpToState(GetMainPlayer(false)->CharaStateData->DefaultStand);
			BattleState.CurrentIntroSide = INT_None;
			BattleHudVisibility(true);
		}
	}
	
	else if (!GameInstance->IsTraining && !BattleState.PauseTimer)
	{
		if (BattleState.TimeUntilRoundStart > 0)
			BattleState.TimeUntilRoundStart--;
		else
			BattleState.RoundTimer--;
	}

	if (BattleState.RoundTimer < 0)
		BattleState.RoundTimer = 0;
	BattleState.FrameNumber++;

	if (!BattleState.SuperFreezeDuration)
	{
		CallBattleExtension("Update");
		for (int i = 0; i < 2; i++)
		{
			if (GetMainPlayer(i == 0)->ComboCounter) continue;
			for (auto& Cooldown : BattleState.TeamData[i].CooldownTimer)
			{
				if (Cooldown == 0) continue;
				if (GameInstance->IsTraining) Cooldown = 0;
				else Cooldown--;
			}
		}
	}
	
	if (BattleState.CurrentSequenceTime != -1)
		BattleState.CurrentSequenceTime++;
	
	SortObjects();

	BattleState.MainPlayer[0]->Inputs = Input1;
	BattleState.MainPlayer[1]->Inputs = Input2;
	for (int i = 0; i < MaxPlayerObjects; i++)
	{
		for (int j = 0; j < MaxPlayerObjects; j++)
		{
			if (i < MaxPlayerObjects / 2)
			{
				Players[i]->Enemy = GetMainPlayer(false);
			}
			else
			{
				Players[i]->Enemy = GetMainPlayer(true);
			}
		}
	}

	HandleHitCollision();
	
	for (int i = 0; i < MaxBattleObjects + MaxPlayerObjects; i++)
	{
		if (i == BattleState.ActiveObjectCount)
			break;
		if (((BattleState.SuperFreezeSelfDuration && SortedObjects[i] == BattleState.SuperFreezeCaller)
			|| (BattleState.SuperFreezeDuration && SortedObjects[i] != BattleState.SuperFreezeCaller))
			&& (SortedObjects[i]->MiscFlags & MISC_IgnoreSuperFreeze) == 0)
		{
			if (SortedObjects[i]->IsPlayer)
			{
				if (SortedObjects[i]->Player->PlayerFlags & PLF_IsStunned)
					SortedObjects[i]->Player->HandleBufferedState();
				SortedObjects[i]->GetBoxes();
				SortedObjects[i]->Player->StoredInputBuffer.Update(SortedObjects[i]->Player->Inputs);
				SortedObjects[i]->Player->HandleStateMachine(true); //handle state transitions
			}
			continue;
		}
		SortedObjects[i]->Update();
	}

	if (BattleState.SuperFreezeSelfDuration == 1)
	{
		BattleState.SuperFreezeCaller->TriggerEvent(EVT_SuperFreezeEnd);
	}
	if (BattleState.SuperFreezeDuration == 1)
	{
		for (int i = 0; i < MaxBattleObjects + MaxPlayerObjects; i++)
		{
			SortedObjects[i]->TriggerEvent(EVT_SuperFreezeEnd);
		}

		BattleState.PauseTimer = false;
		BattleHudVisibility(true);
	}
	
	if (BattleState.SuperFreezeSelfDuration) BattleState.SuperFreezeSelfDuration--;
	if (BattleState.SuperFreezeDuration) BattleState.SuperFreezeDuration--;
	
	HandlePushCollision();
	SetScreenBounds();
	SetStageBounds();
	ParticleManager->PauseParticles();
	if (GameInstance->FighterRunner == Multiplayer && !GameInstance->IsReplay)
	{
		GameInstance->UpdateReplay(Input1, Input2);
	}
	CollisionView();
	
	const FGGPONetworkStats Network = GetNetworkStats();
	NetworkStats.Ping = Network.network.ping;
	const int32 LocalFramesBehind = Network.timesync.local_frames_behind;
	const int32 RemoteFramesBehind = Network.timesync.remote_frames_behind;

	if (LocalFramesBehind < 0 && RemoteFramesBehind < 0)
		NetworkStats.RollbackFrames = abs(abs(LocalFramesBehind) - abs(RemoteFramesBehind));
	else if (LocalFramesBehind > 0 && RemoteFramesBehind > 0)
		NetworkStats.RollbackFrames = 0;
	else
		NetworkStats.RollbackFrames = abs(LocalFramesBehind) + abs(RemoteFramesBehind);
	
	for (int i = 0; i < 2; i++)
	{
		if (BattleState.Meter[i] > BattleState.MaxMeter[i])
			BattleState.Meter[i] = BattleState.MaxMeter[i];
		if (BattleState.Meter[i] < 0)
			BattleState.Meter[i] = 0;

		for (int j = 0; j < GaugeCount; j++)
		{
			if (BattleState.Gauge[i][j] > BattleState.MaxGauge[j])
				BattleState.Gauge[i][j] = BattleState.MaxGauge[j];
			if (BattleState.Gauge[i][j] < 0)
				BattleState.Gauge[i][j] = 0;
		}
	}
	
	HandleRoundWin();
	
	// these aren't strictly game state related, but tying them to game state update makes things better
	UpdateVisuals();
	UpdateCamera();
	UpdateHUD();
	ManageAudio();
}

void ANightSkyGameState::UpdateGameState()
{
	RemoteFrame++;
	UpdateLocalInput();
	UpdateGameState(LocalInputs[LocalFrame % MaxRollbackFrames][0], LocalInputs[LocalFrame % MaxRollbackFrames][1], false);
}

void ANightSkyGameState::SortObjects()
{
	BattleState.ActiveObjectCount = MaxPlayerObjects;
	for (int i = MaxPlayerObjects; i < MaxBattleObjects + MaxPlayerObjects; i++)
	{
		for (int j = i + 1; j < MaxBattleObjects + MaxPlayerObjects; j++)
		{
			if (SortedObjects[j]->IsActive && !SortedObjects[i]->IsActive)
			{
				ABattleObject* Temp = SortedObjects[i];
				SortedObjects[i] = SortedObjects[j];
				SortedObjects[j] = Temp;
			}
		}
		if (SortedObjects[i]->IsActive)
		{
			BattleState.ActiveObjectCount++;
		}
	}
}

void ANightSkyGameState::HandlePushCollision() const
{
	for (int i = 0; i < MaxPlayerObjects; i++)
	{
		for (int j = 0; j < MaxPlayerObjects; j++)
		{
			if (Players[i]->PlayerIndex != Players[j]->PlayerIndex && Players[i]->PlayerFlags & PLF_IsOnScreen && Players[j]->PlayerFlags & PLF_IsOnScreen)
			{
				Players[i]->HandlePushCollision(Players[j]);
			}
		}
	}
}

void ANightSkyGameState::HandleHitCollision() const
{
	for (int i = 0; i < MaxBattleObjects + MaxPlayerObjects; i++)
	{
		if (i == BattleState.ActiveObjectCount)
			break;
		for (int j = 0; j < MaxBattleObjects + MaxPlayerObjects; j++)
		{
			if (j == BattleState.ActiveObjectCount)
				break;
			if (SortedObjects[i]->Player->PlayerIndex != SortedObjects[j]->Player->PlayerIndex && SortedObjects[j]->Player->PlayerFlags & PLF_IsOnScreen)
			{
				SortedObjects[i]->HandleHitCollision(SortedObjects[j]);
			}
			if (i != j)
			{
				SortedObjects[i]->HandleClashCollision(SortedObjects[j]);
			}
		}
	}
}

void ANightSkyGameState::UpdateVisuals() const
{
	for (int i = 0; i < MaxBattleObjects + MaxPlayerObjects; i++)
	{
		if (i == BattleState.ActiveObjectCount)
			break;
		SortedObjects[i]->UpdateVisuals();
	}
}

void ANightSkyGameState::HandleRoundWin()
{
	if (GetMainPlayer(true)->CurrentHealth > 0 && GetMainPlayer(false)->CurrentHealth <= 0)
	{
		if ((GetMainPlayer(true)->PlayerFlags & PLF_RoundWinInputLock) == 0)
			BattleState.P1RoundsWon++;
		GetMainPlayer(true)->RoundWinTimer--;
		GetMainPlayer(true)->PlayerFlags |= PLF_RoundWinInputLock;
		BattleState.PauseTimer = true;
		if (GetMainPlayer(true)->RoundWinTimer == 0)
		{
			if (IsTagBattle())
			{
				if (!HandleMatchWin())
				{
					BattleState.PauseTimer = false;
					RoundInit();
				}
			}
			else if (!HandleMatchWin())
			{
				if (!GetMainPlayer(true)->JumpToState(GetMainPlayer(true)->CharaStateData->DefaultRoundWin))
				{
					BattleState.PauseTimer = false;
					RoundInit();
				}
			}
		}
	}
	else if (GetMainPlayer(false)->CurrentHealth > 0 && GetMainPlayer(true)->CurrentHealth <= 0)
	{
		if ((GetMainPlayer(false)->PlayerFlags & PLF_RoundWinInputLock) == 0)
			BattleState.P2RoundsWon++;
		GetMainPlayer(false)->RoundWinTimer--;
		GetMainPlayer(false)->PlayerFlags |= PLF_RoundWinInputLock;
		BattleState.PauseTimer = true;
		if (IsTagBattle())
		{
			if (!HandleMatchWin())
			{
				BattleState.PauseTimer = false;
				RoundInit();
			}
		}
		else if (!HandleMatchWin())
		{
			if (!GetMainPlayer(false)->JumpToState(GetMainPlayer(false)->CharaStateData->DefaultRoundWin))
			{
				BattleState.PauseTimer = false;
				RoundInit();
			}
		}
	}
	else if (GetMainPlayer(true)->CurrentHealth <= 0 && GetMainPlayer(false)->CurrentHealth <= 0)
	{
		if ((GetMainPlayer(true)->PlayerFlags & PLF_RoundWinInputLock) == 0)
		{
			BattleState.P1RoundsWon++;
			BattleState.P2RoundsWon++;
		}
		GetMainPlayer(true)->PlayerFlags |= PLF_RoundWinInputLock;
		GetMainPlayer(false)->PlayerFlags |= PLF_RoundWinInputLock;
		GetMainPlayer(true)->RoundWinTimer--;
		BattleState.PauseTimer = true;
		if (GetMainPlayer(true)->RoundWinTimer == 0)
		{
			if (!HandleMatchWin())
			{
				BattleState.PauseTimer = false;
				RoundInit();
			}
		}
	}
	else if (BattleState.RoundTimer <= 0)
	{
		if (GetMainPlayer(true)->CurrentHealth > GetMainPlayer(false)->CurrentHealth)
		{
			if ((GetMainPlayer(true)->PlayerFlags & PLF_RoundWinInputLock) == 0)
				BattleState.P1RoundsWon++;
			GetMainPlayer(true)->RoundWinTimer--;
			GetMainPlayer(true)->PlayerFlags |= PLF_RoundWinInputLock;
			GetMainPlayer(false)->PlayerFlags |= PLF_RoundWinInputLock;
			BattleState.PauseTimer = true;
			if (GetMainPlayer(true)->RoundWinTimer == 0)
			{
				if (IsTagBattle())
				{
					if (!HandleMatchWin())
					{
						BattleState.PauseTimer = false;
						RoundInit();
					}
				}
				else if (!HandleMatchWin())
				{
					if (!GetMainPlayer(true)->JumpToState(GetMainPlayer(true)->CharaStateData->DefaultRoundWin))
					{
						BattleState.PauseTimer = false;
						RoundInit();
					}
				}
			}
		}
		else if (GetMainPlayer(false)->CurrentHealth > GetMainPlayer(true)->CurrentHealth)
		{
			if ((GetMainPlayer(false)->PlayerFlags & PLF_RoundWinInputLock) == 0)
				BattleState.P2RoundsWon++;
			GetMainPlayer(false)->RoundWinTimer--;
			GetMainPlayer(true)->PlayerFlags |= PLF_RoundWinInputLock;
			GetMainPlayer(false)->PlayerFlags |= PLF_RoundWinInputLock;
			BattleState.PauseTimer = true;
			if (GetMainPlayer(false)->RoundWinTimer == 0)
			{
				if (IsTagBattle())
				{
					if (!HandleMatchWin())
					{
						BattleState.PauseTimer = false;
						RoundInit();
					}
				}
				else if (!HandleMatchWin())
				{
					if (!GetMainPlayer(false)->JumpToState(GetMainPlayer(false)->CharaStateData->DefaultRoundWin))
					{
						BattleState.PauseTimer = false;
						RoundInit();
					}
				}
			}
		}
		else if (GetMainPlayer(true)->CurrentHealth == GetMainPlayer(false)->CurrentHealth)
		{
			if ((GetMainPlayer(true)->PlayerFlags & PLF_RoundWinInputLock) == 0)
			{
				BattleState.P1RoundsWon++;
				BattleState.P2RoundsWon++;
			}
			GetMainPlayer(true)->PlayerFlags |= PLF_RoundWinInputLock;
			GetMainPlayer(false)->PlayerFlags |= PLF_RoundWinInputLock;
			GetMainPlayer(true)->RoundWinTimer--;
			BattleState.PauseTimer = true;
			if (GetMainPlayer(true)->RoundWinTimer == 0)
			{
				if (!HandleMatchWin())
				{
					BattleState.PauseTimer = false;
					RoundInit();
				}
			}
		}
	}
}

bool ANightSkyGameState::HandleMatchWin()
{
	switch (BattleState.RoundFormat)
	{
	case ERoundFormat::FirstToOne:
		{
			if (BattleState.P1RoundsWon > 0 && BattleState.P2RoundsWon < BattleState.P1RoundsWon)
			{
				if (!GetMainPlayer(true)->JumpToState(GetMainPlayer(true)->CharaStateData->DefaultMatchWin)) EndMatch();
				GameInstance->EndRecordReplay();
				return true;
			}
			if (BattleState.P2RoundsWon > 0 && BattleState.P1RoundsWon < BattleState.P2RoundsWon)
			{
				if (!GetMainPlayer(false)->JumpToState(GetMainPlayer(false)->CharaStateData->DefaultMatchWin)) EndMatch();
				GameInstance->EndRecordReplay();
				return true;
			}
			if (BattleState.P1RoundsWon == 2 && BattleState.P2RoundsWon == 2)
			{
				GameInstance->EndRecordReplay();
				return true;
			}
		}
		return false;
	case ERoundFormat::FirstToTwo:
		{
			if (BattleState.P1RoundsWon > 1 && BattleState.P2RoundsWon < BattleState.P1RoundsWon)
			{
				if (!GetMainPlayer(true)->JumpToState(GetMainPlayer(true)->CharaStateData->DefaultMatchWin)) EndMatch();
				GameInstance->EndRecordReplay();
				return true;
			}
			if (BattleState.P2RoundsWon > 1 && BattleState.P1RoundsWon < BattleState.P2RoundsWon)
			{
				if (!GetMainPlayer(false)->JumpToState(GetMainPlayer(false)->CharaStateData->DefaultMatchWin)) EndMatch();
				GameInstance->EndRecordReplay();
				return true;
			}
			if (BattleState.P1RoundsWon == 3 && BattleState.P2RoundsWon == 3)
			{
				GameInstance->EndRecordReplay();
				return true;
			}
		}
		return false;
	case ERoundFormat::FirstToThree:
		{
			if (BattleState.P1RoundsWon > 2 && BattleState.P2RoundsWon < BattleState.P1RoundsWon)
			{
				if (!GetMainPlayer(true)->JumpToState(GetMainPlayer(true)->CharaStateData->DefaultMatchWin)) EndMatch();
				GameInstance->EndRecordReplay();
				return true;
			}
			if (BattleState.P2RoundsWon > 2 && BattleState.P1RoundsWon < BattleState.P2RoundsWon)
			{
				if (!GetMainPlayer(false)->JumpToState(GetMainPlayer(false)->CharaStateData->DefaultMatchWin)) EndMatch();
				GameInstance->EndRecordReplay();
				return true;
			}
			if (BattleState.P1RoundsWon == 4 && BattleState.P2RoundsWon == 4)
			{
				GameInstance->EndRecordReplay();
				return true;
			}
		}
		return false;
	case ERoundFormat::FirstToFour:
		{
			if (BattleState.P1RoundsWon > 3 && BattleState.P2RoundsWon < BattleState.P1RoundsWon)
			{
				if (!GetMainPlayer(true)->JumpToState(GetMainPlayer(true)->CharaStateData->DefaultMatchWin)) EndMatch();
				GameInstance->EndRecordReplay();
				return true;
			}
			if (BattleState.P2RoundsWon > 3 && BattleState.P1RoundsWon < BattleState.P2RoundsWon)
			{
				if (!GetMainPlayer(false)->JumpToState(GetMainPlayer(false)->CharaStateData->DefaultMatchWin)) EndMatch();
				GameInstance->EndRecordReplay();
				return true;
			}
			if (BattleState.P1RoundsWon == 5 && BattleState.P2RoundsWon == 5)
			{
				GameInstance->EndRecordReplay();
				return true;
			}
		}
		return false;
	case ERoundFormat::FirstToFive:
		{
			if (BattleState.P1RoundsWon > 4 && BattleState.P2RoundsWon < BattleState.P1RoundsWon)
			{
				if (!GetMainPlayer(true)->JumpToState(GetMainPlayer(true)->CharaStateData->DefaultMatchWin)) EndMatch();
				GameInstance->EndRecordReplay();
				return true;
			}
			if (BattleState.P2RoundsWon > 4 && BattleState.P1RoundsWon < BattleState.P2RoundsWon)
			{
				if (!GetMainPlayer(false)->JumpToState(GetMainPlayer(false)->CharaStateData->DefaultMatchWin)) EndMatch();
				GameInstance->EndRecordReplay();
				return true;
			}
			if (BattleState.P1RoundsWon == 6 && BattleState.P2RoundsWon == 6)
			{
				GameInstance->EndRecordReplay();
				return true;
			}
		}
		return false;
	case ERoundFormat::TwoVsTwo:
	case ERoundFormat::TwoVsTwoKOF:
		{
			if (BattleState.P1RoundsWon > 1 && BattleState.P2RoundsWon < BattleState.P1RoundsWon)
			{
				if (!GetMainPlayer(true)->JumpToState(GetMainPlayer(true)->CharaStateData->DefaultMatchWin)) EndMatch();
				GameInstance->EndRecordReplay();
				return true;
			}
			if (BattleState.P2RoundsWon > 1 && BattleState.P1RoundsWon < BattleState.P2RoundsWon)
			{
				if (!GetMainPlayer(false)->JumpToState(GetMainPlayer(false)->CharaStateData->DefaultMatchWin)) EndMatch();
				GameInstance->EndRecordReplay();
				return true;
			}
			if (BattleState.P1RoundsWon == 2 && BattleState.P2RoundsWon == 2)
			{
				GameInstance->EndRecordReplay();
				return true;
			}
		}
		return false;
	case ERoundFormat::ThreeVsThree:
	case ERoundFormat::ThreeVsThreeKOF:
		{
			if (BattleState.P1RoundsWon > 2 && BattleState.P2RoundsWon < BattleState.P1RoundsWon)
			{
				if (!GetMainPlayer(true)->JumpToState(GetMainPlayer(true)->CharaStateData->DefaultMatchWin)) EndMatch();
				GameInstance->EndRecordReplay();
				return true;
			}
			if (BattleState.P2RoundsWon > 2 && BattleState.P1RoundsWon < BattleState.P2RoundsWon)
			{
				if (!GetMainPlayer(false)->JumpToState(GetMainPlayer(false)->CharaStateData->DefaultMatchWin)) EndMatch();
				GameInstance->EndRecordReplay();
				return true;
			}
			if (BattleState.P1RoundsWon == 3 && BattleState.P2RoundsWon == 3)
			{
				GameInstance->EndRecordReplay();
				return true;
			}
		}
		return false;
	default:
		return false;
	}
}

void ANightSkyGameState::CollisionView() const
{
	if (bViewCollision)
	{
		for (int i = 0; i < BattleState.ActiveObjectCount; i++)
		{
			SortedObjects[i]->CollisionView();
		}
	}
}

int32 ANightSkyGameState::CreateChecksum()
{
	Checksum = 0;

	for (const auto Player : Players)
	{
		Checksum += Player->ActionTime ^ Player->ActionTime << 16;
		Checksum += Player->PosX ^ Player->PosX << 16;
		Checksum += Player->PosY ^ Player->PosY << 16;
		Checksum += Player->CurrentHealth ^ Player->CurrentHealth << 16;
	}
	
	Checksum += BattleState.Meter[0] ^ BattleState.Meter[0];
	Checksum += BattleState.Meter[1] ^ BattleState.Meter[1];

	for (const auto Gauge : BattleState.Gauge[0])
	{
		Checksum += Gauge ^ Gauge << 16;
	}
	for (const auto Gauge : BattleState.Gauge[1])
	{
		Checksum += Gauge ^ Gauge << 16;
	}
	
	return Checksum;
}

FGGPONetworkStats ANightSkyGameState::GetNetworkStats() const
{
	if (AFighterMultiplayerRunner* Runner = Cast<AFighterMultiplayerRunner>(FighterRunner))
	{
		FGGPONetworkStats Stats = { 0 };
		if (Runner->Players[0]->type == GGPO_PLAYERTYPE_REMOTE)
			GGPONet::ggpo_get_network_stats(Runner->ggpo, Runner->PlayerHandles[0], &Stats);
		else
			GGPONet::ggpo_get_network_stats(Runner->ggpo, Runner->PlayerHandles[1], &Stats);
		return Stats;
	}
	constexpr FGGPONetworkStats Stats = { 0 };
	return Stats;
}

void ANightSkyGameState::SetStageBounds()
{
	if ((GetMainPlayer(true)->MiscFlags & MISC_WallCollisionActive) == 0) return;
	if ((GetMainPlayer(false)->MiscFlags & MISC_WallCollisionActive) == 0) return;
	const int32 NewScreenPos = (GetMainPlayer(true)->PosX + GetMainPlayer(false)->PosX) / 2;
	BattleState.CurrentScreenPos = BattleState.CurrentScreenPos + (NewScreenPos - BattleState.CurrentScreenPos) * 5 / 100;
	if (BattleState.CurrentScreenPos > BattleState.StageBounds)
	{
		BattleState.CurrentScreenPos = BattleState.StageBounds;
	}
	else if (BattleState.CurrentScreenPos < -BattleState.StageBounds)
	{
		BattleState.CurrentScreenPos = -BattleState.StageBounds;
	}
}

void ANightSkyGameState::SetScreenBounds() const
{
	for (int i = 0; i < BattleState.ActiveObjectCount; i++)
	{
		if (SortedObjects[i] != nullptr)
		{
			if (SortedObjects[i]->MiscFlags & MISC_WallCollisionActive)
			{
				if (const auto Player = Cast<APlayerObject>(SortedObjects[i]))
				{
					if (!(Player->PlayerFlags & PLF_IsOnScreen)) continue;
					Player->PlayerFlags |= PLF_TouchingWall;
					Player->WallTouchTimer++;
				}
				if (SortedObjects[i]->PosX >= BattleState.ScreenBounds + BattleState.CurrentScreenPos)
				{
					SortedObjects[i]->PosX = BattleState.ScreenBounds + BattleState.CurrentScreenPos;
				}
				else if (SortedObjects[i]->PosX <= -BattleState.ScreenBounds + BattleState.CurrentScreenPos)
				{
					SortedObjects[i]->PosX = -BattleState.ScreenBounds + BattleState.CurrentScreenPos;
				}
				else
				{
					if (const auto Player = Cast<APlayerObject>(SortedObjects[i]))
					{
						Player->PlayerFlags &= ~PLF_TouchingWall;
						Player->WallTouchTimer = 0;
					}
				}
			}
		}
	}
}

void ANightSkyGameState::StartSuperFreeze(int32 Duration, int32 SelfDuration, ABattleObject* CallingObject)
{
	BattleState.SuperFreezeDuration = Duration;
	BattleState.SuperFreezeSelfDuration = SelfDuration;
	BattleState.SuperFreezeCaller = CallingObject;
	BattleState.PauseTimer = true;
}

ABattleObject* ANightSkyGameState::AddBattleObject(
	const UState* InState,
	int PosX,
	int PosY,
	EObjDir Dir,
	int32 ObjectStateIndex,
	bool bIsCommonState,
	APlayerObject* Parent) const
{
	for (int i = 0; i < MaxBattleObjects; i++)
	{
		if (!Objects[i]->IsActive)
		{
			Objects[i]->ObjectState = DuplicateObject(InState, Objects[i]);
			Objects[i]->ObjectState->Parent = Objects[i];
			Objects[i]->IsActive = true;
			Objects[i]->Direction = Dir;
			Objects[i]->Player = Parent;
			Objects[i]->PosX = PosX;
			Objects[i]->PosY = PosY;
			Objects[i]->ObjectStateIndex = ObjectStateIndex;
			Objects[i]->bIsCommonState = bIsCommonState;
			Objects[i]->InitObject();
			return Objects[i];
		}
	}
	return nullptr;
}

void ANightSkyGameState::UpdateCamera()
{
	if (CameraActor != nullptr)
	{
		const FVector P1Location = FVector(static_cast<float>(BattleState.MainPlayer[0]->PosX) / COORD_SCALE,
		                                   static_cast<float>(BattleState.MainPlayer[0]->PosZ) / COORD_SCALE,
		                                   static_cast<float>(BattleState.MainPlayer[0]->PosY) / COORD_SCALE);
		const FVector P2Location = FVector(static_cast<float>(BattleState.MainPlayer[1]->PosX) / COORD_SCALE,
		                                   static_cast<float>(BattleState.MainPlayer[1]->PosZ) / COORD_SCALE,
		                                   static_cast<float>(BattleState.MainPlayer[1]->PosY) / COORD_SCALE);
		const FVector Average = (P1Location + P2Location) / 2;
		float DistanceForX = sqrt(abs((P1Location - P2Location).X));
		DistanceForX = FMath::Clamp(DistanceForX,16, BattleState.ScreenBounds / 37800);
		DistanceForX = FMath::GetMappedRangeValueClamped(TRange<float>(16, BattleState.ScreenBounds / 18900), TRange<float>(0, BattleState.ScreenBounds / 1250), DistanceForX);
		const float NewX = FMath::Clamp(
			-Average.X, -(BattleState.StageBounds + BattleState.ScreenBounds * 0.5) / COORD_SCALE + DistanceForX,
			(BattleState.StageBounds + BattleState.ScreenBounds * 0.5) / COORD_SCALE - DistanceForX);
		float DistanceForYZ = sqrt(FVector::Distance(P1Location, P2Location));
		DistanceForYZ = FMath::Clamp(DistanceForYZ,16, BattleState.ScreenBounds / 37800);
		const float NewY = FMath::GetMappedRangeValueClamped(TRange<float>(16, BattleState.ScreenBounds / 37800), TRange<float>(540, BattleState.ScreenBounds / 1000), DistanceForYZ);
		float NewZ;
		if (P1Location.Z > P2Location.Z)
			NewZ = FMath::Lerp(P1Location.Z, P2Location.Z, 0.25);
		else
			NewZ = FMath::Lerp(P1Location.Z, P2Location.Z, 0.75);
		const float BaseZ = FMath::GetMappedRangeValueClamped(TRange<float>(4, BattleState.ScreenBounds / 37800), TRange<float>(25, 175), DistanceForYZ);
		NewZ += BaseZ;
		BattleState.PrevCameraPosition = BattleState.CameraPosition;
		BattleState.CameraPosition = BattleSceneTransform.GetRotation().RotateVector(FVector(-NewX, NewY, NewZ)) + BattleSceneTransform.GetLocation();
		BattleState.CameraPosition = FMath::Lerp(BattleState.PrevCameraPosition, BattleState.CameraPosition, 0.25);
		CameraActor->SetActorLocation(BattleState.CameraPosition);
		if (BattleState.CurrentSequenceTime == -1)
		{
			const FVector SequenceCameraLocation = BattleSceneTransform.GetRotation().RotateVector(FVector(0, 1080, 175)) + BattleSceneTransform.GetLocation();
			SequenceCameraActor->SetActorLocation(SequenceCameraLocation);
			if (const auto PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0); IsValid(PlayerController))
			{
				PlayerController->SetViewTargetWithBlend(CameraActor);	
			}
		}
		else
		{
			if (BattleState.CurrentSequenceTime >= SequenceActor->GetSequencePlayer()->GetEndTime().Time)
			{
				SequenceActor->GetSequencePlayer()->Stop();
				BattleState.CurrentSequenceTime = -1;
				BattleState.IsPlayingSequence = false;
				return;
			}
			const FMovieSceneSequencePlaybackParams Params = FMovieSceneSequencePlaybackParams(
				FFrameTime(BattleState.CurrentSequenceTime),
				EUpdatePositionMethod::Scrub);
			SequenceActor->GetSequencePlayer()->SetPlaybackPosition(Params);
			const FVector SequenceTargetVector = FVector(SequenceTarget->PosX / COORD_SCALE,
			                                             SequenceTarget->PosZ / COORD_SCALE,
			                                             SequenceTarget->PosY / COORD_SCALE);

			FVector NewCamLocation = SequenceCameraActor->GetActorLocation();
			NewCamLocation.Y = NewCamLocation.Y + SequenceTargetVector.Y;
			NewCamLocation.Z = NewCamLocation.Z + SequenceTargetVector.Z;

			if (SequenceTarget->Direction == DIR_Left)
			{
				NewCamLocation.X = -NewCamLocation.X + SequenceTargetVector.X;
				auto NewCamRotation = SequenceCameraActor->GetActorRotation();
				NewCamRotation.Yaw = -NewCamRotation.Yaw - 180;
				SequenceCameraActor->SetActorRotation(NewCamRotation);
			}
			else
			{
				NewCamLocation.X = NewCamLocation.X + SequenceTargetVector.X;
			}

			SequenceCameraActor->SetActorLocation(BattleSceneTransform.GetRotation().RotateVector(NewCamLocation) + BattleSceneTransform.GetLocation());

			const FRotator CameraRotation = BattleSceneTransform.GetRotation().Rotator() + SequenceCameraActor->GetActorRotation();

			SequenceCameraActor->SetActorRotation(CameraRotation);
		}
	}
	bIsPlayingSequence = BattleState.IsPlayingSequence;
}

void ANightSkyGameState::PlayLevelSequence(APlayerObject* Target, APlayerObject* Enemy, ULevelSequence* Sequence)
{
	if (SequenceActor != nullptr)
	{
		SequenceActor->GetSequencePlayer()->Stop();
		SequenceActor->SetSequence(Sequence);
		TArray<FMovieSceneBinding> Bindings = Sequence->GetMovieScene()->GetBindings();
		int NumBindings = Bindings.Num();
		for (int i = 0; i < NumBindings; i++)
		{
			FMovieSceneBinding MovieSceneBinding = Bindings[i];
			if (!MovieSceneBinding.GetName().Equals("Target"))
			{
				continue;
			}

			FMovieSceneObjectBindingID BindingId = FMovieSceneObjectBindingID(MovieSceneBinding.GetObjectGuid());
			SequenceActor->SetBinding(BindingId, TArray<AActor*>{ Target });

			break;
		}
		for (int i = 0; i < NumBindings; i++)
		{
			FMovieSceneBinding MovieSceneBinding = Bindings[i];
			if (!MovieSceneBinding.GetName().Equals("Enemy"))
			{
				continue;
			}

			FMovieSceneObjectBindingID BindingId = FMovieSceneObjectBindingID(MovieSceneBinding.GetObjectGuid());
			SequenceActor->SetBinding(BindingId, TArray<AActor*>{ Enemy });

			break;
		}
		for (int i = 0; i < NumBindings; i++)
		{
			FMovieSceneBinding MovieSceneBinding = Bindings[i];
			if (!MovieSceneBinding.GetName().Equals("CameraActor"))
			{
				continue;
			}

			FMovieSceneObjectBindingID BindingId = FMovieSceneObjectBindingID(MovieSceneBinding.GetObjectGuid());
			SequenceActor->SetBinding(BindingId, TArray<AActor*>{ CameraActor });

			break;
		}
		for (int i = 0; i < NumBindings; i++)
		{
			FMovieSceneBinding MovieSceneBinding = Bindings[i];
			if (!MovieSceneBinding.GetName().Equals("SequenceCameraActor"))
			{
				continue;
			}

			FMovieSceneObjectBindingID BindingId = FMovieSceneObjectBindingID(MovieSceneBinding.GetObjectGuid());
			SequenceActor->SetBinding(BindingId, TArray<AActor*>{ SequenceCameraActor });

			break;
		}
		SequenceTarget = Target;
		SequenceEnemy = Enemy;
		BattleState.CurrentSequenceTime = 0;
		BattleState.IsPlayingSequence = true;
	}
}

void ANightSkyGameState::CameraShake(const TSubclassOf<UCameraShakeBase>& Pattern, float Scale) const
{
	if (Pattern)
	{
		const auto PlayerCameraManager = UGameplayStatics::GetPlayerCameraManager(this, 0);
		PlayerCameraManager->StopAllCameraShakes();
		PlayerCameraManager->StartCameraShake(Pattern, Scale);
	}
}

void ANightSkyGameState::UpdateHUD() const
{
	if (BattleState.bHUDVisible)
	{
		BattleHudActor->TopWidget->SetVisibility(ESlateVisibility::Visible);
		BattleHudActor->BottomWidget->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		BattleHudActor->TopWidget->SetVisibility(ESlateVisibility::Hidden);
		BattleHudActor->BottomWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	
	if (BattleHudActor != nullptr)
	{
		if (BattleHudActor->TopWidget != nullptr)
		{
			if (BattleHudActor->TopWidget->P1Health.Num() >= 3)
			{
				BattleHudActor->TopWidget->P1Health[0] = static_cast<float>(GetTeam(true)[0]->CurrentHealth) / static_cast<float>(GetTeam(true)[0]->MaxHealth);
				BattleHudActor->TopWidget->P1Health[1] = static_cast<float>(GetTeam(true)[1]->CurrentHealth) / static_cast<float>(GetTeam(true)[1]->MaxHealth);
				BattleHudActor->TopWidget->P1Health[2] = static_cast<float>(GetTeam(true)[2]->CurrentHealth) / static_cast<float>(GetTeam(true)[2]->MaxHealth);
			}
			if (BattleHudActor->TopWidget->P2Health.Num() >= 3)
			{
				BattleHudActor->TopWidget->P2Health[0] = static_cast<float>(GetTeam(false)[0]->CurrentHealth) / static_cast<float>(GetTeam(false)[0]->MaxHealth);
				BattleHudActor->TopWidget->P2Health[1] = static_cast<float>(GetTeam(false)[1]->CurrentHealth) / static_cast<float>(GetTeam(false)[1]->MaxHealth);
				BattleHudActor->TopWidget->P2Health[2] = static_cast<float>(GetTeam(false)[2]->CurrentHealth) / static_cast<float>(GetTeam(false)[2]->MaxHealth);
			}
			if (BattleHudActor->TopWidget->P1RecoverableHealth.Num() >= 3)
			{
				BattleHudActor->TopWidget->P1RecoverableHealth[0] = static_cast<float>(GetTeam(true)[0]->CurrentHealth + GetTeam(true)[0]->RecoverableHealth) / static_cast<float>(GetTeam(true)[0]->MaxHealth);
				BattleHudActor->TopWidget->P1RecoverableHealth[1] = static_cast<float>(GetTeam(true)[1]->CurrentHealth + GetTeam(true)[1]->RecoverableHealth) / static_cast<float>(GetTeam(true)[1]->MaxHealth);
				BattleHudActor->TopWidget->P1RecoverableHealth[2] = static_cast<float>(GetTeam(true)[2]->CurrentHealth + GetTeam(true)[2]->RecoverableHealth) / static_cast<float>(GetTeam(true)[2]->MaxHealth);
			}
			if (BattleHudActor->TopWidget->P2RecoverableHealth.Num() >= 3)
			{
				BattleHudActor->TopWidget->P2RecoverableHealth[0] = static_cast<float>(GetTeam(false)[0]->CurrentHealth + GetTeam(false)[0]->RecoverableHealth) / static_cast<float>(GetTeam(false)[0]->MaxHealth);
				BattleHudActor->TopWidget->P2RecoverableHealth[1] = static_cast<float>(GetTeam(false)[1]->CurrentHealth + GetTeam(false)[1]->RecoverableHealth) / static_cast<float>(GetTeam(false)[1]->MaxHealth);
				BattleHudActor->TopWidget->P2RecoverableHealth[2] = static_cast<float>(GetTeam(false)[2]->CurrentHealth + GetTeam(false)[2]->RecoverableHealth) / static_cast<float>(GetTeam(false)[2]->MaxHealth);
			}
			BattleHudActor->TopWidget->P1RoundsWon = BattleState.P1RoundsWon;
			BattleHudActor->TopWidget->P2RoundsWon = BattleState.P2RoundsWon;
			BattleHudActor->TopWidget->Timer = static_cast<float>(BattleState.RoundTimer / 60);
			BattleHudActor->TopWidget->P1ComboCounter = BattleState.MainPlayer[0]->ComboCounter;
			BattleHudActor->TopWidget->P2ComboCounter = BattleState.MainPlayer[1]->ComboCounter;
			BattleHudActor->TopWidget->Ping = NetworkStats.Ping;
			BattleHudActor->TopWidget->RollbackFrames = NetworkStats.RollbackFrames;
		}
		if (BattleHudActor->BottomWidget != nullptr)
		{
			BattleHudActor->BottomWidget->P1Meter = static_cast<float>(BattleState.Meter[0]) / 10000;
			BattleHudActor->BottomWidget->P2Meter = static_cast<float>(BattleState.Meter[1]) / 10000;

			if (BattleHudActor->BottomWidget->P1Gauge.IsEmpty()) BattleHudActor->BottomWidget->P1Gauge.SetNum(GaugeCount);
			if (BattleHudActor->BottomWidget->P2Gauge.IsEmpty()) BattleHudActor->BottomWidget->P2Gauge.SetNum(GaugeCount);
			
			for (int j = 0; j < GaugeCount; j++)
			{
				BattleHudActor->BottomWidget->P1Gauge[j] = static_cast<float>(BattleState.Gauge[0][j]) / BattleState.MaxGauge[j];
				BattleHudActor->BottomWidget->P2Gauge[j] = static_cast<float>(BattleState.Gauge[1][j]) / BattleState.MaxGauge[j];
			}
		}
	}
}

void ANightSkyGameState::SetDrawPriorityFront(ABattleObject* InObject) const
{
	if (InObject->IsPlayer)
	{
		for (int i = 0; i < MaxPlayerObjects; i++)
		{
			if (SortedObjects[i]->DrawPriority <= InObject->DrawPriority)
				SortedObjects[i]->DrawPriority++;
		}
		InObject->DrawPriority = 0;
		return;
	}
	for (int i = MaxPlayerObjects; i < BattleState.ActiveObjectCount; i++)
	{
		if (SortedObjects[i]->DrawPriority <= InObject->DrawPriority)
			SortedObjects[i]->DrawPriority++;
		InObject->DrawPriority = MaxPlayerObjects;
	}
}

APlayerObject* ANightSkyGameState::SwitchMainPlayer(APlayerObject* InPlayer, int TeamIndex)
{
	if (TeamIndex == 0) return nullptr;
	if (BattleState.RoundFormat < ERoundFormat::TwoVsTwo) return nullptr;
	if (BattleState.RoundFormat > ERoundFormat::ThreeVsThree) return nullptr;
	if (BattleState.RoundFormat == ERoundFormat::TwoVsTwo && TeamIndex > 1) return nullptr;
	if (BattleState.RoundFormat == ERoundFormat::ThreeVsThree && TeamIndex > 2) return nullptr;
	const bool IsP1 = InPlayer->PlayerIndex == 0;
	if (BattleState.TeamData[IsP1 == 0].CooldownTimer[TeamIndex] > 0) return nullptr;

	const auto NewPlayer = GetTeam(IsP1)[TeamIndex];
	if (NewPlayer->CurrentHealth == 0) return nullptr;
	if (NewPlayer->PlayerFlags & PLF_IsOnScreen) return nullptr;
	NewPlayer->TeamIndex = 0;
	InPlayer->TeamIndex = TeamIndex;
	NewPlayer->JumpToState(NewPlayer->CharaStateData->DefaultTagIn);
	NewPlayer->SetOnScreen(true);
	for (const auto EnemyPlayer : GetTeam(!IsP1))
	{
		EnemyPlayer->Enemy = NewPlayer;
	}
	BattleState.MainPlayer[!IsP1] = NewPlayer;
	BattleState.TeamData[IsP1 == 0].CooldownTimer[TeamIndex] = BattleState.TagCooldown;
	return NewPlayer;
}

APlayerObject* ANightSkyGameState::CallAssist(const bool IsP1, const int AssistIndex, const FString& AssistName)
{
	if (AssistIndex == 0) return nullptr;
	if (BattleState.RoundFormat < ERoundFormat::TwoVsTwo) return nullptr;
	if (BattleState.RoundFormat > ERoundFormat::ThreeVsThree) return nullptr;
	if (BattleState.RoundFormat == ERoundFormat::TwoVsTwo && AssistIndex > 1) return nullptr;
	if (BattleState.RoundFormat == ERoundFormat::ThreeVsThree && AssistIndex > 2) return nullptr;
	if (BattleState.TeamData[IsP1 == 0].CooldownTimer[AssistIndex] > 0) return nullptr;

	const auto NewPlayer = GetTeam(IsP1)[AssistIndex];
	if (NewPlayer->CurrentHealth == 0) return nullptr;
	if (NewPlayer->PlayerFlags & PLF_IsOnScreen) return nullptr;
	NewPlayer->JumpToState(AssistName);
	NewPlayer->SetOnScreen(true);
	NewPlayer->Direction = GetMainPlayer(IsP1)->Direction;
	BattleState.TeamData[IsP1 == 0].CooldownTimer[AssistIndex] = BattleState.AssistCooldown;
	return NewPlayer;
}

bool ANightSkyGameState::CanTag(const APlayerObject* InPlayer, int TeamIndex) const
{
	if (TeamIndex == 0) return false;
	if (BattleState.RoundFormat < ERoundFormat::TwoVsTwo) return false;
	if (BattleState.RoundFormat > ERoundFormat::ThreeVsThree) return false;
	if (BattleState.RoundFormat == ERoundFormat::TwoVsTwo && TeamIndex > 1) return false;
	if (BattleState.RoundFormat == ERoundFormat::ThreeVsThree && TeamIndex > 2) return false;
	const bool IsP1 = InPlayer->PlayerIndex == 0;

	if (BattleState.TeamData[IsP1 == 0].CooldownTimer[TeamIndex] > 0) return false;
	
	const auto NewPlayer = GetTeam(IsP1)[TeamIndex];
	if (NewPlayer->CurrentHealth == 0) return false;
	if (NewPlayer->PlayerFlags & PLF_IsOnScreen) return false;

	return true;
}

int ANightSkyGameState::GetLocalInputs(int Index) const
{
	if (const ANightSkyPlayerController* Controller = Cast<ANightSkyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), Index)); Controller != nullptr)
	{
		return Controller->Inputs;
	}
	return 0;
}

void ANightSkyGameState::UpdateRemoteInput(int RemoteInput[], int32 InFrame)
{
	const int PlayerIndex = GameInstance->PlayerIndex;
	if (PlayerIndex == 0)
	{
		for (int i = InFrame; i > InFrame - MaxRollbackFrames; i--)
		{
			RemoteInputs[i % MaxRollbackFrames][1] = RemoteInput[i % MaxRollbackFrames];
		}
	}
	else
	{
		for (int i = InFrame; i > InFrame - MaxRollbackFrames; i--)
		{
			RemoteInputs[i % MaxRollbackFrames][0] = RemoteInput[i % MaxRollbackFrames];
		}
	}
}

void ANightSkyGameState::SetOtherChecksum(uint32 RemoteChecksum, int32 InFrame)
{
	OtherChecksum = RemoteChecksum;
	OtherChecksumFrame = InFrame;
}

TArray<APlayerObject*> ANightSkyGameState::GetTeam(bool IsP1) const
{
	if (IsP1)
	{
		TArray<APlayerObject*> PlayerObjects;
		for (int i = 0; i < MaxPlayerObjects / 2; i++)
		{
			PlayerObjects.Add(Players[i]);
			for (int j = 0; j < PlayerObjects.Num() - 1; j++)
			{
				if (PlayerObjects[i]->TeamIndex < PlayerObjects[j]->TeamIndex)
				{
					PlayerObjects.Swap(i, j);
				}
			}
		}
		return PlayerObjects;
	}
	TArray<APlayerObject*> PlayerObjects;
	for (int i = MaxPlayerObjects / 2; i < MaxPlayerObjects; i++)
	{
		PlayerObjects.Add(Players[i]);
		for (int j = 0; j < PlayerObjects.Num() - 1; j++)
		{
			if (PlayerObjects[i - MaxPlayerObjects / 2]->TeamIndex < PlayerObjects[j]->TeamIndex)
			{
				PlayerObjects.Swap(i - MaxPlayerObjects / 2, j);
			}
		}
	}
	return PlayerObjects;
}

APlayerObject* ANightSkyGameState::GetMainPlayer(bool IsP1) const
{
	if (IsP1) return BattleState.MainPlayer[0];
	return BattleState.MainPlayer[1];
}

void ANightSkyGameState::CallBattleExtension(FString Name)
{
	if (BattleExtensionNames.Find(FName(Name)) != INDEX_NONE)
	{
		BattleExtensions[BattleExtensionNames.Find(FName(Name))]->Exec();
	}
}

int32 ANightSkyGameState::GetGauge(bool IsP1, int32 GaugeIndex) const
{
	if (GaugeIndex < GaugeCount)
	{
		if (IsP1) return BattleState.Gauge[0][GaugeIndex];
		return BattleState.Gauge[1][GaugeIndex];
	}
	
	return -1;
}

void ANightSkyGameState::SetGauge(bool IsP1, int32 GaugeIndex, int32 Value)
{
	if (GaugeIndex < GaugeCount)
	{
		if (IsP1) BattleState.Gauge[0][GaugeIndex] = Value;
		else BattleState.Gauge[1][GaugeIndex] = Value;
	}
}

void ANightSkyGameState::UseGauge(bool IsP1, int32 GaugeIndex, int32 Value)
{
	if (GaugeIndex < GaugeCount)
	{
		if (IsP1) BattleState.Gauge[0][GaugeIndex] -= Value;
		else BattleState.Gauge[1][GaugeIndex] -= Value;
	}
}

bool ANightSkyGameState::IsTagBattle() const
{
	return BattleState.RoundFormat >= ERoundFormat::TwoVsTwo && BattleState.RoundFormat <= ERoundFormat::ThreeVsThree;
}

void ANightSkyGameState::ScreenPosToWorldPos(int32 X, int32 Y, int32* OutX, int32* OutY) const
{
	*OutX = BattleState.CurrentScreenPos - BattleState.ScreenBounds + BattleState.StageBounds * 2 * X / 100;
}

void ANightSkyGameState::BattleHudVisibility(bool Visible)
{
	BattleState.bHUDVisible = Visible;
}

void ANightSkyGameState::PlayCommonAudio(USoundBase* InSoundWave, float MaxDuration)
{
	for (int i = 0; i < CommonAudioChannelCount; i++)
	{
		if (BattleState.CommonAudioChannels[i].Finished)
		{
			BattleState.CommonAudioChannels[i].SoundWave = InSoundWave;
			BattleState.CommonAudioChannels[i].StartingFrame = BattleState.FrameNumber;
			BattleState.CommonAudioChannels[i].MaxDuration = MaxDuration;
			BattleState.CommonAudioChannels[i].Finished = false;
			if (!bIsResimulating)
			{
				AudioManager->CommonAudioPlayers[i]->SetSound(InSoundWave);
				AudioManager->CommonAudioPlayers[i]->Play();
			}
			return;
		}
	}
}

void ANightSkyGameState::PlayCharaAudio(USoundBase* InSoundWave, float MaxDuration)
{
	for (int i = 0; i < CharaAudioChannelCount; i++)
	{
		if (BattleState.CharaAudioChannels[i].Finished)
		{
			BattleState.CharaAudioChannels[i].SoundWave = InSoundWave;
			BattleState.CharaAudioChannels[i].StartingFrame = BattleState.FrameNumber;
			BattleState.CharaAudioChannels[i].MaxDuration = MaxDuration;
			BattleState.CharaAudioChannels[i].Finished = false;
			if (!bIsResimulating)
			{
				AudioManager->CharaAudioPlayers[i]->SetSound(InSoundWave);
				AudioManager->CharaAudioPlayers[i]->Play();
			}
			return;
		}
	}
}

void ANightSkyGameState::PlayVoiceLine(USoundBase* InSoundWave, float MaxDuration, int Player)
{
	BattleState.CharaVoiceChannels[Player].SoundWave = InSoundWave;
	BattleState.CharaVoiceChannels[Player].StartingFrame = BattleState.FrameNumber;
	BattleState.CharaVoiceChannels[Player].MaxDuration = MaxDuration;
	BattleState.CharaVoiceChannels[Player].Finished = false;
	if (!bIsResimulating)
	{
		AudioManager->CharaVoicePlayers[Player]->SetSound(InSoundWave);
		AudioManager->CharaVoicePlayers[Player]->Play();
	}
}

void ANightSkyGameState::PlayAnnouncerVoice(USoundBase* InSoundWave, float MaxDuration)
{
	BattleState.AnnouncerVoiceChannel.SoundWave = InSoundWave;
	BattleState.AnnouncerVoiceChannel.StartingFrame = BattleState.FrameNumber;
	BattleState.AnnouncerVoiceChannel.MaxDuration = MaxDuration;
	BattleState.AnnouncerVoiceChannel.Finished = false;
	if (!bIsResimulating)
	{
		AudioManager->AnnouncerVoicePlayer->SetSound(InSoundWave);
		AudioManager->AnnouncerVoicePlayer->Play();
	}
}

void ANightSkyGameState::PlayMusic(const FString& Name)
{
	if (!IsValid(GameInstance))
		return;
	if (GameInstance->MusicData != nullptr)
	{
		for (FSoundStruct SoundStruct : GameInstance->MusicData->SoundDatas)
		{
			if (SoundStruct.Name == Name)
			{
				PlayMusic(SoundStruct.SoundWave, SoundStruct.MaxDuration);
				break;
			}
		}
	}
}

void ANightSkyGameState::PlayMusic(USoundBase* InSoundWave, float MaxDuration)
{
	BattleState.MusicChannel.SoundWave = InSoundWave;
	BattleState.MusicChannel.StartingFrame = BattleState.FrameNumber;
	BattleState.MusicChannel.MaxDuration = MaxDuration;
	if (!bIsResimulating)
	{
		AudioManager->MusicPlayer->SetSound(InSoundWave);
		AudioManager->MusicPlayer->Play();
	}
}

void ANightSkyGameState::ManageAudio()
{
	if (bIsResimulating) return;
	for (int i = 0; i < CommonAudioChannelCount; i++)
	{
		const int CurrentAudioTime = BattleState.FrameNumber - BattleState.CommonAudioChannels[i].StartingFrame;
		if (!BattleState.CommonAudioChannels[i].Finished && static_cast<int>(BattleState.CommonAudioChannels[i].MaxDuration * 60) < CurrentAudioTime)
		{
			BattleState.CommonAudioChannels[i].Finished = true;
			AudioManager->CommonAudioPlayers[i]->Stop();
			AudioManager->CommonAudioPlayers[i]->SetSound(nullptr);
		}
	}
	for (int i = 0; i < CharaAudioChannelCount; i++)
	{
		const int CurrentAudioTime = BattleState.FrameNumber - BattleState.CharaAudioChannels[i].StartingFrame;
		if (!BattleState.CharaAudioChannels[i].Finished && static_cast<int>(BattleState.CharaAudioChannels[i].MaxDuration * 60) < CurrentAudioTime)
		{
			BattleState.CharaAudioChannels[i].Finished = true;
			AudioManager->CharaAudioPlayers[i]->Stop();
			AudioManager->CharaAudioPlayers[i]->SetSound(nullptr);
		}
	}
	for (int i = 0; i < CharaVoiceChannelCount; i++)
	{
		const int CurrentAudioTime = BattleState.FrameNumber - BattleState.CharaVoiceChannels[i].StartingFrame;
		if (!BattleState.CharaVoiceChannels[i].Finished && static_cast<int>(BattleState.CharaVoiceChannels[i].MaxDuration * 60) < CurrentAudioTime)
		{
			BattleState.CharaVoiceChannels[i].Finished = true;
			AudioManager->CharaVoicePlayers[i]->Stop();
			AudioManager->CharaVoicePlayers[i]->SetSound(nullptr);
		}
	}
	{
		const int CurrentAudioTime = BattleState.FrameNumber - BattleState.AnnouncerVoiceChannel.StartingFrame;
		if (!BattleState.AnnouncerVoiceChannel.Finished && static_cast<int>(BattleState.AnnouncerVoiceChannel.MaxDuration * 60) < CurrentAudioTime)
		{
			BattleState.AnnouncerVoiceChannel.Finished = true;
			AudioManager->AnnouncerVoicePlayer->Stop();
			AudioManager->AnnouncerVoicePlayer->SetSound(nullptr);
		}
	}
	{
		const int CurrentAudioTime = BattleState.FrameNumber - BattleState.MusicChannel.StartingFrame;
		if (static_cast<int>(BattleState.MusicChannel.MaxDuration * 60) < CurrentAudioTime)
		{
			PlayMusic(BattleState.MusicChannel.SoundWave, BattleState.MusicChannel.MaxDuration);
		}
	}
}

void ANightSkyGameState::RollbackStartAudio(int32 InFrame) const
{
	for (int i = 0; i < CommonAudioChannelCount; i++)
	{
		if (BattleState.CommonAudioChannels[i].Finished) continue;
		if (BattleState.CommonAudioChannels[i].SoundWave == AudioManager->CommonAudioPlayers[i]->GetSound()) continue;
		
		AudioManager->CommonAudioPlayers[i]->Stop();
		AudioManager->CommonAudioPlayers[i]->SetSound(BattleState.CommonAudioChannels[i].SoundWave);
		const float CurrentAudioTime = static_cast<float>(InFrame - BattleState.CommonAudioChannels[i].StartingFrame) / 60.f;
		if (BattleState.CommonAudioChannels[i].MaxDuration > CurrentAudioTime)
			AudioManager->CommonAudioPlayers[i]->Play(CurrentAudioTime);
	}
	for (int i = 0; i < CharaAudioChannelCount; i++)
	{
		if (BattleState.CharaAudioChannels[i].Finished) continue;
		if (BattleState.CharaAudioChannels[i].SoundWave == AudioManager->CharaAudioPlayers[i]->GetSound()) continue;
		
		AudioManager->CharaAudioPlayers[i]->Stop();
		AudioManager->CharaAudioPlayers[i]->SetSound(BattleState.CharaAudioChannels[i].SoundWave);
		const float CurrentAudioTime = static_cast<float>(InFrame - BattleState.CharaAudioChannels[i].StartingFrame) / 60.f;
		if (BattleState.CharaAudioChannels[i].MaxDuration > CurrentAudioTime)
			AudioManager->CharaAudioPlayers[i]->Play(CurrentAudioTime);
	}
	for (int i = 0; i < CharaVoiceChannelCount; i++)
	{
		if (BattleState.CharaVoiceChannels[i].Finished) continue;
		if (BattleState.CharaVoiceChannels[i].SoundWave == AudioManager->CharaVoicePlayers[i]->GetSound()) continue;
		
		AudioManager->CharaVoicePlayers[i]->Stop();
		AudioManager->CharaVoicePlayers[i]->SetSound(BattleState.CharaVoiceChannels[i].SoundWave);
		const float CurrentAudioTime = static_cast<float>(InFrame - BattleState.CharaVoiceChannels[i].StartingFrame) / 60.f;
		if (BattleState.CharaVoiceChannels[i].MaxDuration > CurrentAudioTime)
			AudioManager->CharaVoicePlayers[i]->Play(CurrentAudioTime);
	}
	if (!BattleState.AnnouncerVoiceChannel.Finished && BattleState.AnnouncerVoiceChannel.SoundWave != AudioManager->AnnouncerVoicePlayer->GetSound())
	{
		AudioManager->AnnouncerVoicePlayer->Stop();
		AudioManager->AnnouncerVoicePlayer->SetSound(BattleState.AnnouncerVoiceChannel.SoundWave);
		const float CurrentAudioTime = static_cast<float>(InFrame - BattleState.AnnouncerVoiceChannel.StartingFrame) / 60.f;
		if (BattleState.AnnouncerVoiceChannel.MaxDuration > CurrentAudioTime)
			AudioManager->AnnouncerVoicePlayer->Play(CurrentAudioTime);
	}
	if (BattleState.MusicChannel.SoundWave != AudioManager->MusicPlayer->GetSound())
	{
		AudioManager->MusicPlayer->Stop();
		AudioManager->MusicPlayer->SetSound(BattleState.MusicChannel.SoundWave);
		const float CurrentAudioTime = static_cast<float>(InFrame - BattleState.MusicChannel.StartingFrame) / 60.f;
		if (BattleState.MusicChannel.MaxDuration > CurrentAudioTime)
			AudioManager->MusicPlayer->Play(CurrentAudioTime);
	}
}

void ANightSkyGameState::SaveGameState(int32* InChecksum)
{
	const int BackupFrame = LocalFrame % MaxRollbackFrames;
	BPRollbackData[BackupFrame] = FBPRollbackData();
	memcpy(MainRollbackData[BackupFrame].BattleStateBuffer, &BattleState.BattleStateSync, SizeOfBattleState);
	for (int i = 0; i < BattleExtensions.Num(); i++)
	{
		BPRollbackData[BackupFrame].ExtensionData.Add(BattleExtensions[i]->SaveForRollback());
	}
	if (BattleExtensions.Num() == 0)
	{
		BPRollbackData[BackupFrame].ExtensionData.Add(TArray<uint8> { 1 });
	}
	for (int i = 0; i < MaxBattleObjects; i++)
	{
		if (Objects[i]->IsActive)
		{
			Objects[i]->SaveForRollback(MainRollbackData[BackupFrame].ObjBuffer[i]);
			BPRollbackData[BackupFrame].StateData.Add(Objects[i]->ObjectState->SaveForRollback());
			MainRollbackData[BackupFrame].ObjActive[i] = true;
		}
		else
		{
			MainRollbackData[BackupFrame].ObjActive[i] = false;
			BPRollbackData[BackupFrame].StateData.Add(TArray<uint8> { 1 });
		}
	}
	for (int i = 0; i < MaxPlayerObjects; i++)
	{
		Players[i]->SaveForRollback(MainRollbackData[BackupFrame].ObjBuffer[i + MaxBattleObjects]);
		if (Players[i]->PlayerFlags & PLF_IsOnScreen)
		{
			BPRollbackData[BackupFrame].StateData.Add(Players[i]->StoredStateMachine.CurrentState->SaveForRollback());
		}
		else
		{
			BPRollbackData[BackupFrame].StateData.Add(TArray<uint8> { 1 });
		}
		Players[i]->SaveForRollbackPlayer(MainRollbackData[BackupFrame].CharBuffer[i]);
		BPRollbackData[BackupFrame].PlayerData.Add(Players[i]->SaveForRollbackBP());
	}

	*InChecksum = CreateChecksum();
}

void ANightSkyGameState::LoadGameState()
{
	const int CurrentRollbackFrame = LocalFrame % MaxRollbackFrames;
	const int CurrentFrame = BattleState.FrameNumber;
	memcpy(&BattleState.BattleStateSync, MainRollbackData[CurrentRollbackFrame].BattleStateBuffer, SizeOfBattleState);
	for (int i = 0; i < BattleExtensions.Num(); i++)
	{
		BattleExtensions[i]->LoadForRollback(BPRollbackData[CurrentRollbackFrame].ExtensionData[i]);
	}
	for (int i = 0; i < MaxBattleObjects; i++)
	{
		if (MainRollbackData[CurrentRollbackFrame].ObjActive[i])
		{
			Objects[i]->LoadForRollback(MainRollbackData[CurrentRollbackFrame].ObjBuffer[i]);
			Objects[i]->ObjectState->LoadForRollback(BPRollbackData[CurrentRollbackFrame].StateData[i]);
		}
		else
		{
			if (Objects[i]->IsActive)
				Objects[i]->ResetObject();
		}
	}
	for (int i = 0; i < MaxPlayerObjects; i++)
	{
		Players[i]->LoadForRollback(MainRollbackData[CurrentRollbackFrame].ObjBuffer[i + MaxBattleObjects]);
		if (Players[i]->PlayerFlags & PLF_IsOnScreen)
		{
			Players[i]->StoredStateMachine.CurrentState->LoadForRollback(BPRollbackData[CurrentRollbackFrame].StateData[i + MaxBattleObjects]);
		}
		Players[i]->LoadForRollbackPlayer(MainRollbackData[CurrentRollbackFrame].CharBuffer[i]);
		Players[i]->LoadForRollbackBP(BPRollbackData[CurrentRollbackFrame].PlayerData[i]);
	}
	SortObjects();
	ParticleManager->RollbackParticles(CurrentFrame - BattleState.FrameNumber);
	if (!FighterRunner->IsA(AFighterSynctestRunner::StaticClass()))
		GameInstance->RollbackReplay(CurrentFrame - BattleState.FrameNumber);
}