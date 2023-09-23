// Fill out your copyright notice in the Description page of Project Settings.


#include "NightSkyGameState.h"
#include "EngineUtils.h"
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
#include "NightSkyEngine/Miscellaneous/FighterRunners.h"
#include "NightSkyEngine/Miscellaneous/NightSkyGameInstance.h"
#include "NightSkyEngine/UI/NightSkyBattleHudActor.h"
#include "NightSkyEngine/UI/NightSkyBattleWidget.h"

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
	Init();
}

void ANightSkyGameState::Init()
{
	for (int i = 0; i < MaxRollbackFrames; i++)
	{
		StoredRollbackData.Add(FRollbackData());
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
					Players[i]->PlayerIndex = i * 2 >= MaxPlayerObjects;
					Players[i]->TeamIndex = i % MaxPlayerObjects / 2;
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
				if (i % 3 == 0)
				{
					Players[i]->PlayerFlags |= PLF_IsOnScreen;
				}
			}
			else
			{
				Players[i] = GetWorld()->SpawnActor<APlayerObject>(APlayerObject::StaticClass(), BattleSceneTransform);
				if (i % 3 == 0)
				{
					Players[i]->PlayerFlags |= PLF_IsOnScreen;
				}
			}
			SortedObjects[i] = Players[i];
		}
		else
		{
			Players[i] = GetWorld()->SpawnActor<APlayerObject>(APlayerObject::StaticClass(), BattleSceneTransform);
			if (i % 3 == 0)
			{
				Players[i]->PlayerFlags |= PLF_IsOnScreen;
			}
			SortedObjects[i] = Players[i];
		}
		Players[i]->InitPlayer();
		Players[i]->GameState = this;
		Players[i]->ObjNumber = i + MaxBattleObjects;
		SortedObjects[i] = Players[i];
	}
	for (int i = 0; i < MaxBattleObjects; i++)
	{
		Objects[i] = GetWorld()->SpawnActor<ABattleObject>(ABattleObject::StaticClass(), BattleSceneTransform);
		Objects[i]->GameState = this;
		Objects[i]->ObjNumber = i;
		SortedObjects[i + MaxPlayerObjects] = Objects[i];
	}

	for (int i = MaxBattleObjects + MaxPlayerObjects; i >= 0; i--)
	{
		SetDrawPriorityFront(SortedObjects[i]);
	}
	
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = GetOwner();

	switch (GameInstance->FighterRunner)
	{
	case LocalPlay:
		FighterRunner = GetWorld()->SpawnActor<AFighterLocalRunner>(AFighterLocalRunner::StaticClass(),SpawnParameters);
		break;
	case Multiplayer:
		if (GameInstance->IsReplay)
			FighterRunner = GetWorld()->SpawnActor<AFighterReplayRunner>(AFighterReplayRunner::StaticClass(),SpawnParameters);
		else
			FighterRunner = GetWorld()->SpawnActor<AFighterLocalRunner>(AFighterMultiplayerRunner::StaticClass(),SpawnParameters);
		break;
	case SyncTest:
		FighterRunner = GetWorld()->SpawnActor<AFighterLocalRunner>(AFighterSynctestRunner::StaticClass(),SpawnParameters);
		break;
	default:
		FighterRunner = GetWorld()->SpawnActor<AFighterLocalRunner>(AFighterLocalRunner::StaticClass(),SpawnParameters);
		break;
	}

	const FVector NewCameraLocation = BattleSceneTransform.GetRotation().RotateVector(FVector(0, 1080, 175)) + BattleSceneTransform.GetLocation();
	FRotator CameraRotation = BattleSceneTransform.GetRotation().Rotator();
	CameraRotation.Yaw -= 90;
	
	CameraActor->SetActorLocation(NewCameraLocation);
	CameraActor->SetActorRotation(CameraRotation);
	SequenceCameraActor->SetActorLocation(NewCameraLocation);
	SequenceCameraActor->SetActorRotation(CameraRotation);
	
	BattleState.RoundFormat = GameInstance->BattleData.RoundFormat;
	BattleState.RoundTimer = GameInstance->BattleData.StartRoundTimer * 60;
	
	RoundInit();
}

void ANightSkyGameState::RoundInit()
{
	BattleState.RoundCount++;
	if (!GameInstance->IsTraining)
		BattleState.TimeUntilRoundStart = 180;
	for (int i = 0; i < MaxBattleObjects; i++)
		Objects[i]->ResetObject();
	
	for (int i = 0; i < MaxPlayerObjects; i++)
		Players[i]->ResetForRound();

	Players[0]->PlayerFlags = PLF_IsOnScreen;
	Players[MaxPlayerObjects / 2]->PlayerFlags = PLF_IsOnScreen;
	
	BattleState.RoundTimer = GameInstance->BattleData.StartRoundTimer * 60;
	BattleState.CurrentScreenPos = 0;
	BattleState.bHUDVisible = true;
	
	const FVector NewCameraLocation = BattleSceneTransform.GetRotation().RotateVector(FVector(0, 1080, 175)) + BattleSceneTransform.GetLocation();
	FRotator CameraRotation = BattleSceneTransform.GetRotation().Rotator();
	CameraRotation.Yaw -= 90;
	
	CameraActor->SetActorLocation(NewCameraLocation);
	CameraActor->SetActorRotation(CameraRotation);
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
	int SendInputs[MaxRollbackFrames] = { 16 };
	if (PlayerIndex == 0)
	{
		RemoteInputs[LocalFrame % MaxRollbackFrames][0] = LocalInputs[LocalFrame % MaxRollbackFrames][0] = GetLocalInputs(0);
		for (int i = 0; i < MaxRollbackFrames; i++)
		{
			SendInputs[i] = LocalInputs[i][0];
		}
		Cast<ANightSkyPlayerController>(GetWorld()->GetFirstPlayerController())->UpdateInput(SendInputs, LocalFrame);
		RemoteInputs[LocalFrame % MaxRollbackFrames][1] = LocalInputs[LocalFrame % MaxRollbackFrames][1] = LocalInputs[RemoteFrame % MaxRollbackFrames][1];
	}
	else
	{
		RemoteInputs[LocalFrame % MaxRollbackFrames][0] = LocalInputs[LocalFrame % MaxRollbackFrames][0] = LocalInputs[RemoteFrame % MaxRollbackFrames][0];
		RemoteInputs[LocalFrame % MaxRollbackFrames][1] = LocalInputs[LocalFrame % MaxRollbackFrames][1] = GetLocalInputs(0);
		for (int i = 0; i < MaxRollbackFrames; i++)
		{
			SendInputs[i] = LocalInputs[i][1];
		}
		Cast<ANightSkyPlayerController>(GetWorld()->GetFirstPlayerController())->UpdateInput(SendInputs, LocalFrame);
	}
}

// Called every frame
void ANightSkyGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FighterRunner->Update(DeltaTime);
}

void ANightSkyGameState::UpdateGameState(int32 Input1, int32 Input2)
{
	LocalFrame++;
	ParticleManager->UpdateParticles();
	if (!GameInstance->IsTraining && !BattleState.PauseTimer)
	{
		if (BattleState.TimeUntilRoundStart > 0)
			BattleState.TimeUntilRoundStart--;
		else
			BattleState.RoundTimer--;
	}

	if (BattleState.RoundTimer < 0)
		BattleState.RoundTimer = 0;
	BattleState.FrameNumber++;

	if (BattleState.CurrentSequenceTime != -1)
		BattleState.CurrentSequenceTime++;
	
	for (int i = 0; i < 2; i++)
	{
		if (BattleState.Meter[i] > BattleState.MaxMeter[i])
			BattleState.Meter[i] = BattleState.MaxMeter[i];
		if (BattleState.Meter[i] < 0)
			BattleState.Meter[i] = 0;
	}
	
	SortObjects();

	Players[0]->Inputs = Input1;
	Players[3]->Inputs = Input2;
	for (int i = 0; i < MaxPlayerObjects; i++)
	{
		if (Players[i]->PlayerFlags & PLF_IsOnScreen)
		{
			for (int j = 0; j < MaxPlayerObjects; j++)
			{
				if (i < MaxPlayerObjects / 2)
				{
					if (j >= MaxPlayerObjects / 2 && Players[j]->PlayerFlags & PLF_IsOnScreen)
					{
						Players[i]->Enemy = Players[j];
					}
				}
				else
				{
					if (j < MaxPlayerObjects / 2 && Players[j]->PlayerFlags & PLF_IsOnScreen)
					{
						Players[i]->Enemy = Players[j];
					}
				}
			}
		}
	}

	HandleHitCollision();
	for (int i = 0; i < MaxBattleObjects + MaxPlayerObjects; i++)
	{
		if (i == BattleState.ActiveObjectCount)
			break;
		if (!SortedObjects[i]->IsPlayer || SortedObjects[i]->Player->PlayerFlags & PLF_IsOnScreen)
			SortedObjects[i]->Update();
	}
	HandlePushCollision();
	SetScreenBounds();
	SetStageBounds();
	HandleRoundWin();
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
	
	// these aren't strictly game state related, but tying them to game state update makes things better
	UpdateCamera();
	UpdateHUD();
	ManageAudio();
}

void ANightSkyGameState::UpdateGameState()
{
	RemoteFrame++;
	UpdateLocalInput();
	UpdateGameState(LocalInputs[LocalFrame % MaxRollbackFrames][0], LocalInputs[LocalFrame % MaxRollbackFrames][1]);
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
		for (int j = 0; j < MaxPlayerObjects; j++)
		{
			if (i != j && SortedObjects[j]->Player->PlayerFlags & PLF_IsOnScreen)
			{
				SortedObjects[i]->HandleHitCollision(Cast<APlayerObject>(SortedObjects[j]));
			}
		}
		for (int j = 0; j < MaxBattleObjects + MaxPlayerObjects; j++)
		{
			if (i != j)
			{
				SortedObjects[i]->HandleClashCollision(SortedObjects[j]);
			}
		}
	}
}

void ANightSkyGameState::HandleRoundWin()
{
	if (BattleState.RoundFormat < ERoundFormat::TwoVsTwo)
	{
		if (Players[0]->CurrentHealth > 0 && Players[3]->CurrentHealth <= 0)
		{
			if ((Players[0]->PlayerFlags & PLF_RoundWinInputLock) == 0)
				BattleState.P1RoundsWon++;
			if (!(Players[0]->AttackFlags & ATK_IsAttacking))
				Players[0]->RoundWinTimer--;
			Players[0]->PlayerFlags |= PLF_RoundWinInputLock;
			BattleState.PauseTimer = true;
			if (Players[0]->RoundWinTimer == 0)
			{
				BattleState.PauseTimer = false;
				HandleMatchWin();
				RoundInit();
			}
		}
		else if (Players[3]->CurrentHealth > 0 && Players[0]->CurrentHealth <= 0)
		{
			if ((Players[3]->PlayerFlags & PLF_RoundWinInputLock) == 0)
				BattleState.P2RoundsWon++;
			if (!(Players[3]->AttackFlags & ATK_IsAttacking))
				Players[3]->RoundWinTimer--;
			Players[3]->PlayerFlags |= PLF_RoundWinInputLock;
			BattleState.PauseTimer = true;
			if (Players[3]->RoundWinTimer == 0)
			{
				BattleState.PauseTimer = false;
				HandleMatchWin();
				RoundInit();
			}
		}
		else if (Players[0]->CurrentHealth <= 0 && Players[3]->CurrentHealth <= 0)
		{
			if ((Players[0]->PlayerFlags & PLF_RoundWinInputLock) == 0)
			{
				BattleState.P1RoundsWon++;
				BattleState.P2RoundsWon++;
			}
			Players[0]->PlayerFlags |= PLF_RoundWinInputLock;
			Players[3]->PlayerFlags |= PLF_RoundWinInputLock;
			if (!(Players[0]->AttackFlags & ATK_IsAttacking))
				Players[0]->RoundWinTimer--;
			BattleState.PauseTimer = true;
			if (Players[0]->RoundWinTimer == 0)
			{
				BattleState.PauseTimer = false;
				HandleMatchWin();
				RoundInit();
			}
		}
		else if (BattleState.RoundTimer <= 0)
		{
			if (Players[0]->CurrentHealth > Players[3]->CurrentHealth)
			{
				if ((Players[0]->PlayerFlags & PLF_RoundWinInputLock) == 0)
					BattleState.P1RoundsWon++;
				if (!(Players[0]->AttackFlags & ATK_IsAttacking))
					Players[0]->RoundWinTimer--;
				Players[0]->PlayerFlags |= PLF_RoundWinInputLock;
				Players[3]->PlayerFlags |= PLF_RoundWinInputLock;
				BattleState.PauseTimer = true;
				if (Players[0]->RoundWinTimer == 0)
				{
					BattleState.PauseTimer = false;
					HandleMatchWin();
					RoundInit();
				}
			}
			else if (Players[3]->CurrentHealth > Players[0]->CurrentHealth)
			{
				if ((Players[3]->PlayerFlags & PLF_RoundWinInputLock) == 0)
					BattleState.P2RoundsWon++;
				if (!(Players[3]->AttackFlags & ATK_IsAttacking))
					Players[3]->RoundWinTimer--;
				Players[0]->PlayerFlags |= PLF_RoundWinInputLock;
				Players[3]->PlayerFlags |= PLF_RoundWinInputLock;
				BattleState.PauseTimer = true;
				if (Players[3]->RoundWinTimer == 0)
				{
					BattleState.PauseTimer = false;
					HandleMatchWin();
					RoundInit();
				}
			}
			else if (Players[0]->CurrentHealth == Players[3]->CurrentHealth)
			{
				if ((Players[0]->PlayerFlags & PLF_RoundWinInputLock) == 0)
				{
					BattleState.P1RoundsWon++;
					BattleState.P2RoundsWon++;
				}
				Players[0]->PlayerFlags |= PLF_RoundWinInputLock;
				Players[3]->PlayerFlags |= PLF_RoundWinInputLock;
				if (!(Players[0]->AttackFlags & ATK_IsAttacking))
					Players[0]->RoundWinTimer--;
				BattleState.PauseTimer = true;
				if (Players[0]->RoundWinTimer == 0)
				{
					BattleState.PauseTimer = false;
					HandleMatchWin();
					RoundInit();
				}
			}
		}
	}
}

void ANightSkyGameState::HandleMatchWin()
{
	switch (BattleState.RoundFormat)
	{
	case ERoundFormat::FirstToOne:
		if (BattleState.P1RoundsWon > 0 && BattleState.P2RoundsWon < BattleState.P1RoundsWon)
		{
			GameInstance->EndRecordReplay();
			UGameplayStatics::OpenLevel(GetGameInstance(), FName(TEXT("MainMenu_PL")));
		}
		else if (BattleState.P2RoundsWon > 0 && BattleState.P1RoundsWon < BattleState.P2RoundsWon)
		{
			GameInstance->EndRecordReplay();
			UGameplayStatics::OpenLevel(GetGameInstance(), FName(TEXT("MainMenu_PL")));
		}
		else if (BattleState.P1RoundsWon == 2 && BattleState.P2RoundsWon == 2)
		{
			GameInstance->EndRecordReplay();
			UGameplayStatics::OpenLevel(GetGameInstance(), FName(TEXT("MainMenu_PL")));
		}
		return;
	case ERoundFormat::FirstToTwo:
		if (BattleState.P1RoundsWon > 1 && BattleState.P2RoundsWon < BattleState.P1RoundsWon)
		{
			GameInstance->EndRecordReplay();
			UGameplayStatics::OpenLevel(GetGameInstance(), FName(TEXT("MainMenu_PL")));
		}
		else if (BattleState.P2RoundsWon > 1 && BattleState.P1RoundsWon < BattleState.P2RoundsWon)
		{
			GameInstance->EndRecordReplay();
			UGameplayStatics::OpenLevel(GetGameInstance(), FName(TEXT("MainMenu_PL")));
		}
		else if (BattleState.P1RoundsWon == 3 && BattleState.P2RoundsWon == 3)
		{
			GameInstance->EndRecordReplay();
			UGameplayStatics::OpenLevel(GetGameInstance(), FName(TEXT("MainMenu_PL")));
		}
		return;
	case ERoundFormat::FirstToThree:
		if (BattleState.P1RoundsWon > 2 && BattleState.P2RoundsWon < BattleState.P1RoundsWon)
		{
			GameInstance->EndRecordReplay();
			UGameplayStatics::OpenLevel(GetGameInstance(), FName(TEXT("MainMenu_PL")));
		}
		else if (BattleState.P2RoundsWon > 2 && BattleState.P1RoundsWon < BattleState.P2RoundsWon)
		{
			GameInstance->EndRecordReplay();
			UGameplayStatics::OpenLevel(GetGameInstance(), FName(TEXT("MainMenu_PL")));
		}
		else if (BattleState.P1RoundsWon == 4 && BattleState.P2RoundsWon == 4)
		{
			GameInstance->EndRecordReplay();
			UGameplayStatics::OpenLevel(GetGameInstance(), FName(TEXT("MainMenu_PL")));
		}
		return;
	case ERoundFormat::FirstToFour:
		if (BattleState.P1RoundsWon > 3 && BattleState.P2RoundsWon < BattleState.P1RoundsWon)
		{
			GameInstance->EndRecordReplay();
			UGameplayStatics::OpenLevel(GetGameInstance(), FName(TEXT("MainMenu_PL")));
		}
		else if (BattleState.P2RoundsWon > 3 && BattleState.P1RoundsWon < BattleState.P2RoundsWon)
		{
			GameInstance->EndRecordReplay();
			UGameplayStatics::OpenLevel(GetGameInstance(), FName(TEXT("MainMenu_PL")));
		}
		else if (BattleState.P1RoundsWon == 5 && BattleState.P2RoundsWon == 5)
		{
			GameInstance->EndRecordReplay();
			UGameplayStatics::OpenLevel(GetGameInstance(), FName(TEXT("MainMenu_PL")));
		}
		return;
	case ERoundFormat::FirstToFive:
		if (BattleState.P1RoundsWon > 4 && BattleState.P2RoundsWon < BattleState.P1RoundsWon)
		{
			GameInstance->EndRecordReplay();
			UGameplayStatics::OpenLevel(GetGameInstance(), FName(TEXT("MainMenu_PL")));
		}
		else if (BattleState.P2RoundsWon > 4 && BattleState.P1RoundsWon < BattleState.P2RoundsWon)
		{
			GameInstance->EndRecordReplay();
			UGameplayStatics::OpenLevel(GetGameInstance(), FName(TEXT("MainMenu_PL")));
		}
		else if (BattleState.P1RoundsWon == 6 && BattleState.P2RoundsWon == 6)
		{
			GameInstance->EndRecordReplay();
			UGameplayStatics::OpenLevel(GetGameInstance(), FName(TEXT("MainMenu_PL")));
		}
		return;
	default: ;
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

FGGPONetworkStats ANightSkyGameState::GetNetworkStats() const
{
	AFighterMultiplayerRunner* Runner = Cast<AFighterMultiplayerRunner>(FighterRunner);
	if (IsValid(Runner))
	{
		FGGPONetworkStats Stats = { };
		if (Runner->Players[0]->type == GGPO_PLAYERTYPE_REMOTE)
			GGPONet::ggpo_get_network_stats(Runner->ggpo, Runner->PlayerHandles[0], &Stats);
		else
			GGPONet::ggpo_get_network_stats(Runner->ggpo, Runner->PlayerHandles[1], &Stats);
		return Stats;
	}
	constexpr FGGPONetworkStats Stats = { };
	return Stats;
}

void ANightSkyGameState::SetStageBounds()
{
	for (int i = 0; i < MaxPlayerObjects; i++)
	{
		if (Players[i]->PlayerIndex == 0)
		{
			for (int j = 0; j < MaxPlayerObjects; j++)
			{
				if (Players[j]->PlayerIndex == 1)
				{
					if (Players[i]->PlayerFlags & PLF_IsOnScreen && Players[j]->PlayerFlags & PLF_IsOnScreen)
					{
						const int32 NewScreenPos = (Players[i]->PosX + Players[j]->PosX) / 2;
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
				}
			}
		}
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

void ANightSkyGameState::StartSuperFreeze(int Duration, APlayerObject* CallingPlayer)
{
	for (int i = 0; i < BattleState.ActiveObjectCount; i++)
	{
		if (SortedObjects[i] == Cast<ABattleObject>(CallingPlayer)) continue;
		SortedObjects[i]->SuperFreezeTimer = Duration;
	}
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
		const FVector P1Location = FVector(static_cast<float>(Players[0]->PosX) / COORD_SCALE, static_cast<float>(Players[0]->PosZ) / COORD_SCALE, static_cast<float>(Players[0]->PosY) / COORD_SCALE);
		const FVector P2Location = FVector(static_cast<float>(Players[3]->PosX) / COORD_SCALE, static_cast<float>(Players[3]->PosZ) / COORD_SCALE, static_cast<float>(Players[3]->PosY) / COORD_SCALE);
		const FVector Average = (P1Location + P2Location) / 2;
		const float NewX = FMath::Clamp(-Average.X,-BattleState.ScreenBounds / 1000, BattleState.ScreenBounds / 1000);
		float Distance = sqrt(abs((P1Location - P2Location).X));
		Distance = FMath::Clamp(Distance,16, BattleState.ScreenBounds / 37800);
		const float NewY = FMath::GetMappedRangeValueClamped(TRange<float>(4, BattleState.ScreenBounds / 37800), TRange<float>(0, BattleState.ScreenBounds / 1000), Distance);
		float NewZ;
		if (P1Location.Z > P2Location.Z)
			NewZ = FMath::Lerp(P1Location.Z, P2Location.Z, 0.25) + 125;
		else
			NewZ = FMath::Lerp(P1Location.Z, P2Location.Z, 0.75) + 125;
		BattleState.CameraPosition = BattleSceneTransform.GetRotation().RotateVector(FVector(-NewX, NewY, NewZ)) + BattleSceneTransform.GetLocation();
		BattleState.CameraPosition = FMath::Lerp(CameraActor->GetActorLocation(), BattleState.CameraPosition, 0.1);
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
			if (BattleState.CurrentSequenceTime >= SequenceActor->SequencePlayer->GetEndTime().Time)
			{
				SequenceActor->SequencePlayer->Stop();
				BattleState.CurrentSequenceTime = -1;
				BattleState.IsPlayingSequence = false;
				return;
			}
			const FMovieSceneSequencePlaybackParams Params = FMovieSceneSequencePlaybackParams(
				FFrameTime(BattleState.CurrentSequenceTime),
				EUpdatePositionMethod::Scrub);
			SequenceActor->SequencePlayer->SetPlaybackPosition(Params);
			if (SequenceTarget->Direction == DIR_Left)
			{
				auto NewCamLocation = SequenceCameraActor->GetActorLocation();
				NewCamLocation.X = -(NewCamLocation.X - SequenceTarget->GetActorLocation().X) + SequenceTarget->GetActorLocation().X;
				SequenceCameraActor->SetActorLocation(NewCamLocation);
				auto NewCamRotation = SequenceCameraActor->GetActorRotation();
				NewCamRotation.Yaw = -NewCamRotation.Yaw - 180;
				SequenceCameraActor->SetActorRotation(NewCamRotation);

				auto NewEnemyLocation = SequenceEnemy->GetActorLocation();
				NewEnemyLocation.X = -(NewEnemyLocation.X - static_cast<float>(SequenceEnemy->PosX) / COORD_SCALE) + static_cast<float>(SequenceEnemy->PosX) / COORD_SCALE;
				SequenceEnemy->SetActorLocation(NewEnemyLocation);
			}
		}
	}
	bIsPlayingSequence = BattleState.IsPlayingSequence;
}

void ANightSkyGameState::PlayLevelSequence(APlayerObject* Target, APlayerObject* Enemy, ULevelSequence* Sequence)
{
	if (SequenceActor != nullptr)
	{
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
		FVector SequenceLocation =
			FVector(Target->GetActorLocation().X, SequenceCameraActor->GetActorLocation().Y, Target->GetActorLocation().Z)
			+ BattleSceneTransform.GetRotation().RotateVector(FVector(0, 0, 175));
		SequenceCameraActor->SetActorLocation(SequenceLocation);
		SequenceActor->SetActorRotation(Target->GetActorRotation());
		BattleState.CurrentSequenceTime = 0;
		BattleState.IsPlayingSequence = true;
	}
}

void ANightSkyGameState::CameraShake(TSubclassOf<UCameraShakeBase> Pattern, float Scale) const
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
				BattleHudActor->TopWidget->P1Health[0] = static_cast<float>(Players[0]->CurrentHealth) / static_cast<float>(Players[0]->MaxHealth);
				BattleHudActor->TopWidget->P1Health[1] = static_cast<float>(Players[1]->CurrentHealth) / static_cast<float>(Players[1]->MaxHealth);
				BattleHudActor->TopWidget->P1Health[2] = static_cast<float>(Players[2]->CurrentHealth) / static_cast<float>(Players[2]->MaxHealth);
			}
			if (BattleHudActor->TopWidget->P2Health.Num() >= 3)
			{
				BattleHudActor->TopWidget->P2Health[0] = static_cast<float>(Players[3]->CurrentHealth) / static_cast<float>(Players[3]->MaxHealth);
				BattleHudActor->TopWidget->P2Health[1] = static_cast<float>(Players[4]->CurrentHealth) / static_cast<float>(Players[4]->MaxHealth);
				BattleHudActor->TopWidget->P2Health[2] = static_cast<float>(Players[5]->CurrentHealth) / static_cast<float>(Players[5]->MaxHealth);
			}
			BattleHudActor->TopWidget->P1RoundsWon = BattleState.P1RoundsWon;
			BattleHudActor->TopWidget->P2RoundsWon = BattleState.P2RoundsWon;
			BattleHudActor->TopWidget->Timer = ceil(static_cast<float>(BattleState.RoundTimer) / 60);
			BattleHudActor->TopWidget->P1ComboCounter = Players[0]->ComboCounter;
			BattleHudActor->TopWidget->P2ComboCounter = Players[3]->ComboCounter;
			BattleHudActor->TopWidget->Ping = NetworkStats.Ping;
			BattleHudActor->TopWidget->RollbackFrames = NetworkStats.RollbackFrames;
		}
		if (BattleHudActor->BottomWidget != nullptr)
		{
			BattleHudActor->BottomWidget->P1Meter = static_cast<float>(BattleState.Meter[0]) / 10000;
			BattleHudActor->BottomWidget->P2Meter = static_cast<float>(BattleState.Meter[1]) / 10000;
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
		}
		return PlayerObjects;
	}
	TArray<APlayerObject*> PlayerObjects;
	for (int i = MaxPlayerObjects / 2; i < MaxPlayerObjects; i++)
	{
		PlayerObjects.Add(Players[i]);
	}
	return PlayerObjects;
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
			AudioManager->CommonAudioPlayers[i]->SetSound(InSoundWave);
			AudioManager->CommonAudioPlayers[i]->Play();
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
			AudioManager->CharaAudioPlayers[i]->SetSound(InSoundWave);
			AudioManager->CharaAudioPlayers[i]->Play();
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
	AudioManager->CharaVoicePlayers[Player]->SetSound(InSoundWave);
	AudioManager->CharaVoicePlayers[Player]->Play();
}

void ANightSkyGameState::ManageAudio()
{
	for (int i = 0; i < CommonAudioChannelCount; i++)
	{
		const int CurrentAudioTime = BattleState.FrameNumber - BattleState.CommonAudioChannels[i].StartingFrame;
		if (!BattleState.CommonAudioChannels[i].Finished && static_cast<int>(BattleState.CommonAudioChannels[i].MaxDuration * 60) < CurrentAudioTime + 0.2)
		{
			BattleState.CommonAudioChannels[i].Finished = true;
			AudioManager->CommonAudioPlayers[i]->Stop();
			AudioManager->CommonAudioPlayers[i]->SetSound(nullptr);
		}
	}
	for (int i = 0; i < CharaAudioChannelCount; i++)
	{
		const int CurrentAudioTime = BattleState.FrameNumber - BattleState.CharaAudioChannels[i].StartingFrame;
		if (!BattleState.CharaAudioChannels[i].Finished && static_cast<int>(BattleState.CharaAudioChannels[i].MaxDuration * 60) < CurrentAudioTime + 0.2)
		{
			BattleState.CharaAudioChannels[i].Finished = true;
			AudioManager->CharaAudioPlayers[i]->Stop();
			AudioManager->CharaAudioPlayers[i]->SetSound(nullptr);
		}
	}
	for (int i = 0; i < CharaVoiceChannelCount; i++)
	{
		const int CurrentAudioTime = BattleState.FrameNumber - BattleState.CharaVoiceChannels[i].StartingFrame;
		if (!BattleState.CharaVoiceChannels[i].Finished && static_cast<int>(BattleState.CharaVoiceChannels[i].MaxDuration * 60) < CurrentAudioTime + 0.2)
		{
			BattleState.CharaVoiceChannels[i].Finished = true;
			AudioManager->CharaVoicePlayers[i]->Stop();
			AudioManager->CharaVoicePlayers[i]->SetSound(nullptr);
		}
	}
	const int CurrentAudioTime = BattleState.FrameNumber - BattleState.AnnouncerVoiceChannel.StartingFrame;
	if (!BattleState.AnnouncerVoiceChannel.Finished && static_cast<int>(BattleState.AnnouncerVoiceChannel.MaxDuration * 60) < CurrentAudioTime + 0.2)
	{
		BattleState.AnnouncerVoiceChannel.Finished = true;
		AudioManager->AnnouncerVoicePlayer->Stop();
		AudioManager->AnnouncerVoicePlayer->SetSound(nullptr);
	}
}

void ANightSkyGameState::RollbackStartAudio() const
{
	for (int i = 0; i < CommonAudioChannelCount; i++)
	{
		if (BattleState.CommonAudioChannels[i].SoundWave != AudioManager->CommonAudioPlayers[i]->GetSound())
		{
			AudioManager->CommonAudioPlayers[i]->Stop();
			AudioManager->CommonAudioPlayers[i]->SetSound(BattleState.CommonAudioChannels[i].SoundWave);
			const float CurrentAudioTime = static_cast<float>(BattleState.FrameNumber - BattleState.CommonAudioChannels[i].StartingFrame) / 60.f;
			if (!BattleState.CommonAudioChannels[i].Finished && !AudioManager->CommonAudioPlayers[i]->IsPlaying())
			{
				//AudioManager->CommonAudioPlayers[i]->SetFloatParameter(FName(TEXT("Start Time")), CurrentAudioTime);
				AudioManager->CommonAudioPlayers[i]->Play(CurrentAudioTime);
			}
		}
	}
	for (int i = 0; i < CharaAudioChannelCount; i++)
	{
		if (BattleState.CharaAudioChannels[i].SoundWave != AudioManager->CharaAudioPlayers[i]->GetSound())
		{
			AudioManager->CharaAudioPlayers[i]->Stop();
			AudioManager->CharaAudioPlayers[i]->SetSound(BattleState.CharaAudioChannels[i].SoundWave);
			const float CurrentAudioTime = static_cast<float>(BattleState.FrameNumber - BattleState.CharaAudioChannels[i].StartingFrame) / 60.f;
			if (!BattleState.CharaAudioChannels[i].Finished && !AudioManager->CharaAudioPlayers[i]->IsPlaying())
			{
				//AudioManager->CharaAudioPlayers[i]->SetFloatParameter(FName(TEXT("Start Time")), CurrentAudioTime);
				AudioManager->CharaAudioPlayers[i]->Play(CurrentAudioTime);
			}
		}
	}
	for (int i = 0; i < CharaVoiceChannelCount; i++)
	{
		if (BattleState.CharaVoiceChannels[i].SoundWave != AudioManager->CharaVoicePlayers[i]->GetSound())
		{
			AudioManager->CharaVoicePlayers[i]->Stop();
			AudioManager->CharaVoicePlayers[i]->SetSound(BattleState.CharaVoiceChannels[i].SoundWave);
			const float CurrentAudioTime = static_cast<float>(BattleState.FrameNumber - BattleState.CharaVoiceChannels[i].StartingFrame) / 60.f;
			if (!BattleState.CharaVoiceChannels[i].Finished && !AudioManager->CharaVoicePlayers[i]->IsPlaying())
			{
				//AudioManager->CharaVoicePlayers[i]->SetFloatParameter(FName(TEXT("Start Time")), CurrentAudioTime);
				AudioManager->CharaVoicePlayers[i]->Play(CurrentAudioTime);
			}
		}
	}
	if (BattleState.AnnouncerVoiceChannel.SoundWave != AudioManager->AnnouncerVoicePlayer->GetSound())
	{
		AudioManager->AnnouncerVoicePlayer->Stop();
		AudioManager->AnnouncerVoicePlayer->SetSound(BattleState.AnnouncerVoiceChannel.SoundWave);
		const float CurrentAudioTime = static_cast<float>(BattleState.FrameNumber - BattleState.AnnouncerVoiceChannel.StartingFrame) / 60.f;
		if (!BattleState.AnnouncerVoiceChannel.Finished && !AudioManager->AnnouncerVoicePlayer->IsPlaying())
		{
			//AudioManager->AnnouncerVoicePlayer->SetFloatParameter(FName(TEXT("Start Time")), CurrentAudioTime);
			AudioManager->AnnouncerVoicePlayer->Play(CurrentAudioTime);
		}
	}
}

void ANightSkyGameState::SaveGameState()
{
	const int BackupFrame = LocalFrame % MaxRollbackFrames;
	memcpy(StoredRollbackData[BackupFrame].BattleStateBuffer, &BattleState.BattleStateSync, SizeOfBattleState);
	for (int i = 0; i < MaxBattleObjects; i++)
	{
		if (Objects[i]->IsActive)
		{
			Objects[i]->SaveForRollback(StoredRollbackData[BackupFrame].ObjBuffer[i]);
			StoredRollbackData[BackupFrame].ObjActive[i] = true;
		}
		else
			StoredRollbackData[BackupFrame].ObjActive[i] = false;
	}
	for (int i = 0; i < MaxPlayerObjects; i++)
	{
		Players[i]->SaveForRollback(StoredRollbackData[BackupFrame].ObjBuffer[i + MaxBattleObjects]);
		Players[i]->SaveForRollbackPlayer(StoredRollbackData[BackupFrame].CharBuffer[i]);
	}
}

void ANightSkyGameState::LoadGameState()
{
	const int CurrentRollbackFrame = LocalFrame % MaxRollbackFrames;
	const int CurrentFrame = BattleState.FrameNumber;
	memcpy(&BattleState.BattleStateSync, StoredRollbackData[CurrentRollbackFrame].BattleStateBuffer, SizeOfBattleState);
	for (int i = 0; i < MaxBattleObjects; i++)
	{
		if (StoredRollbackData[CurrentRollbackFrame].ObjActive[i])
		{
			Objects[i]->LoadForRollback(StoredRollbackData[CurrentRollbackFrame].ObjBuffer[i]);
		}
		else
		{
			if (Objects[i]->IsActive)
				Objects[i]->ResetObject();
		}
	}
	for (int i = 0; i < MaxPlayerObjects; i++)
	{
		Players[i]->LoadForRollback(StoredRollbackData[CurrentRollbackFrame].ObjBuffer[i + MaxBattleObjects]);
		Players[i]->LoadForRollbackPlayer(StoredRollbackData[CurrentRollbackFrame].CharBuffer[i]);
	}
	SortObjects();
	ParticleManager->RollbackParticles(CurrentFrame - BattleState.FrameNumber);
	if (!FighterRunner->IsA(AFighterSynctestRunner::StaticClass()))
		GameInstance->RollbackReplay(CurrentFrame - BattleState.FrameNumber);
	RollbackStartAudio();
}
