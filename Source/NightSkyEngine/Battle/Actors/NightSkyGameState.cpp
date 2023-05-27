// Fill out your copyright notice in the Description page of Project Settings.


#include "NightSkyGameState.h"
#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"
#include "NightSkyPlayerController.h"
#include "ParticleManager.h"
#include "Camera/CameraActor.h"
#include "Components/SlateWrapperTypes.h"
#include "FighterRunners/FighterSynctestRunner.h"
#include "Kismet/GameplayStatics.h"
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
	GameInstance = Cast<UNightSkyGameInstance>(GetGameInstance());
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
			if (GameInstance->PlayerList.Num() > i)
			{
				if (GameInstance->PlayerList[i] != nullptr)
				{
					Players[i] = GetWorld()->SpawnActor<APlayerObject>(GameInstance->PlayerList[i]);
					Players[i]->PlayerIndex = i * 2 >= MaxPlayerObjects;
					Players[i]->TeamIndex = i % MaxPlayerObjects / 2;
					for (int j = 0; j < i; j++)
					{
						if (IsValid(GameInstance->PlayerList[j]))
						{
							if (Players[i]->IsA(GameInstance->PlayerList[j]))
							{
								Players[i]->ColorIndex = 2;
								break;
							}
						}
					}
				}
				else
				{
					Players[i] = GetWorld()->SpawnActor<APlayerObject>(APlayerObject::StaticClass());
				}
				if (i % 3 == 0)
				{
					Players[i]->PlayerFlags |= PLF_IsOnScreen;
				}
			}
			else
			{
				Players[i] = GetWorld()->SpawnActor<APlayerObject>(APlayerObject::StaticClass());
				if (i % 3 == 0)
				{
					Players[i]->PlayerFlags |= PLF_IsOnScreen;
				}
			}
			SortedObjects[i] = Players[i];
		}
		else
		{
			Players[i] = GetWorld()->SpawnActor<APlayerObject>(APlayerObject::StaticClass());
			if (i % 3 == 0)
			{
				Players[i]->PlayerFlags |= PLF_IsOnScreen;
			}
			SortedObjects[i] = Players[i];
		}
		Players[i]->InitPlayer();
		Players[i]->GameState = this;
		Players[i]->ObjNumber = i + MaxBattleObjects;
	}
	for (int i = 0; i < MaxBattleObjects; i++)
	{
		Objects[i] = GetWorld()->SpawnActor<ABattleObject>(ABattleObject::StaticClass());
		Objects[i]->ResetObject();
		Objects[i]->GameState = this;
		Objects[i]->ObjNumber = i;
		SortedObjects[i + MaxPlayerObjects] = Objects[i];
	}

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = GetOwner();

	switch (GameInstance->FighterRunner)
	{
	case LocalPlay:
		FighterRunner = GetWorld()->SpawnActor<AFighterLocalRunner>(AFighterLocalRunner::StaticClass(),SpawnParameters);
		break;
	case Multiplayer:
		FighterRunner = GetWorld()->SpawnActor<AFighterLocalRunner>(AFighterMultiplayerRunner::StaticClass(),SpawnParameters);
		break;
	case SyncTest:
		FighterRunner = GetWorld()->SpawnActor<AFighterLocalRunner>(AFighterSynctestRunner::StaticClass(),SpawnParameters);
		break;
	default:
		FighterRunner = GetWorld()->SpawnActor<AFighterLocalRunner>(AFighterLocalRunner::StaticClass(),SpawnParameters);
		break;
	}
	
	BattleState.RoundFormat = GameInstance->RoundFormat;
	BattleState.RoundTimer = GameInstance->StartRoundTimer * 60;
	
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
	
	BattleState.RoundTimer = GameInstance->StartRoundTimer * 60;
	BattleState.CurrentScreenPos = 0;
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
	UpdateCamera();
	UpdateUI();
}

void ANightSkyGameState::UpdateGameState(int32 Input1, int32 Input2)
{
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

	for (int i = 0; i < MaxBattleObjects + MaxPlayerObjects; i++)
	{
		if (i == BattleState.ActiveObjectCount)
			break;
		if (!SortedObjects[i]->IsPlayer || SortedObjects[i]->Player->PlayerFlags & PLF_IsOnScreen)
			SortedObjects[i]->Update();
	}
	HandlePushCollision();
	HandleHitCollision();
	SetScreenBounds();
	SetWallCollision();
	HandleRoundWin();
	ParticleManager->PauseParticles();
}

void ANightSkyGameState::UpdateGameState()
{
	RemoteFrame++;
	LocalFrame++;
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
			else if (Players[3]->CurrentHealth > Players[0]->CurrentHealth)
			{
				if ((Players[3]->PlayerFlags & PLF_RoundWinInputLock) == 0)
					BattleState.P2RoundsWon++;
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
			else if (Players[0]->CurrentHealth == Players[3]->CurrentHealth)
			{
				if ((Players[0]->PlayerFlags & PLF_RoundWinInputLock) == 0)
				{
					BattleState.P1RoundsWon++;
					BattleState.P2RoundsWon++;
				}
				Players[0]->PlayerFlags |= PLF_RoundWinInputLock;
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

void ANightSkyGameState::HandleMatchWin() const
{
	switch (BattleState.RoundFormat)
	{
	case ERoundFormat::FirstToOne:
		if (BattleState.P1RoundsWon > 0 && BattleState.P2RoundsWon < BattleState.P1RoundsWon)
		{
			UGameplayStatics::OpenLevel(GetGameInstance(), FName(TEXT("MainMenu_PL")));
		}
		else if (BattleState.P2RoundsWon > 0 && BattleState.P1RoundsWon < BattleState.P2RoundsWon)
		{
			UGameplayStatics::OpenLevel(GetGameInstance(), FName(TEXT("MainMenu_PL")));
		}
		else if (BattleState.P1RoundsWon == 2 && BattleState.P2RoundsWon == 2)
		{
			UGameplayStatics::OpenLevel(GetGameInstance(), FName(TEXT("MainMenu_PL")));
		}
		return;
	case ERoundFormat::FirstToTwo:
		if (BattleState.P1RoundsWon > 1 && BattleState.P2RoundsWon < BattleState.P1RoundsWon)
		{
			UGameplayStatics::OpenLevel(GetGameInstance(), FName(TEXT("MainMenu_PL")));
		}
		else if (BattleState.P2RoundsWon > 1 && BattleState.P1RoundsWon < BattleState.P2RoundsWon)
		{
			UGameplayStatics::OpenLevel(GetGameInstance(), FName(TEXT("MainMenu_PL")));
		}
		else if (BattleState.P1RoundsWon == 3 && BattleState.P2RoundsWon == 3)
		{
			UGameplayStatics::OpenLevel(GetGameInstance(), FName(TEXT("MainMenu_PL")));
		}
		return;
	case ERoundFormat::FirstToThree:
		if (BattleState.P1RoundsWon > 2 && BattleState.P2RoundsWon < BattleState.P1RoundsWon)
		{
			UGameplayStatics::OpenLevel(GetGameInstance(), FName(TEXT("MainMenu_PL")));
		}
		else if (BattleState.P2RoundsWon > 2 && BattleState.P1RoundsWon < BattleState.P2RoundsWon)
		{
			UGameplayStatics::OpenLevel(GetGameInstance(), FName(TEXT("MainMenu_PL")));
		}
		else if (BattleState.P1RoundsWon == 4 && BattleState.P2RoundsWon == 4)
		{
			UGameplayStatics::OpenLevel(GetGameInstance(), FName(TEXT("MainMenu_PL")));
		}
		return;
	case ERoundFormat::FirstToFour:
		if (BattleState.P1RoundsWon > 3 && BattleState.P2RoundsWon < BattleState.P1RoundsWon)
		{
			UGameplayStatics::OpenLevel(GetGameInstance(), FName(TEXT("MainMenu_PL")));
		}
		else if (BattleState.P2RoundsWon > 3 && BattleState.P1RoundsWon < BattleState.P2RoundsWon)
		{
			UGameplayStatics::OpenLevel(GetGameInstance(), FName(TEXT("MainMenu_PL")));
		}
		else if (BattleState.P1RoundsWon == 5 && BattleState.P2RoundsWon == 5)
		{
			UGameplayStatics::OpenLevel(GetGameInstance(), FName(TEXT("MainMenu_PL")));
		}
		return;
	case ERoundFormat::FirstToFive:
		if (BattleState.P1RoundsWon > 4 && BattleState.P2RoundsWon < BattleState.P1RoundsWon)
		{
			UGameplayStatics::OpenLevel(GetGameInstance(), FName(TEXT("MainMenu_PL")));
		}
		else if (BattleState.P2RoundsWon > 4 && BattleState.P1RoundsWon < BattleState.P2RoundsWon)
		{
			UGameplayStatics::OpenLevel(GetGameInstance(), FName(TEXT("MainMenu_PL")));
		}
		else if (BattleState.P1RoundsWon == 6 && BattleState.P2RoundsWon == 6)
		{
			UGameplayStatics::OpenLevel(GetGameInstance(), FName(TEXT("MainMenu_PL")));
		}
		return;
	default: ;
	}
}

void ANightSkyGameState::SetScreenBounds()
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
						const int NewScreenPos = (Players[i]->PosX + Players[j]->PosX) / 2;
						BattleState.CurrentScreenPos = BattleState.CurrentScreenPos + (NewScreenPos - BattleState.CurrentScreenPos) * 5 / 100;
						if (BattleState.CurrentScreenPos > 1080000)
						{
							BattleState.CurrentScreenPos = 1080000;
						}
						else if (BattleState.CurrentScreenPos < -1080000)
						{
							BattleState.CurrentScreenPos = -1080000;
						}
					}
				}
			}
		}
	}
}

void ANightSkyGameState::SetWallCollision()
{
	for (int i = 0; i < MaxPlayerObjects; i++)
	{
		if (Players[i] != nullptr)
		{
			if (Players[i]->PlayerFlags & PLF_IsOnScreen && Players[i]->MiscFlags & MISC_WallCollisionActive)
			{
				Players[i]->PlayerFlags |= PLF_TouchingWall;
				Players[i]->WallTouchTimer++;
				if (Players[i]->PosX >= 840000 + BattleState.CurrentScreenPos)
				{
					Players[i]->PosX = 840000 + BattleState.CurrentScreenPos;
				}
				else if (Players[i]->PosX <= -840000 + BattleState.CurrentScreenPos)
				{
					Players[i]->PosX = -840000 + BattleState.CurrentScreenPos;
				}
				else
				{
					Players[i]->PlayerFlags &= ~PLF_TouchingWall;
				Players[i]->WallTouchTimer = 0;
				}
			}
		}
	}
}


void ANightSkyGameState::UpdateCamera() const
{
	if (CameraActor != nullptr)
	{
		FVector Average = (Players[0]->GetActorLocation() + Players[3]->GetActorLocation()) / 2;
		float NewX = FMath::Clamp(-Average.X,-540, 540);
		float Distance = sqrt(abs((Players[0]->GetActorLocation() - Players[3]->GetActorLocation()).X));
		Distance = FMath::Clamp(Distance,20, 25);
		float NewY = FMath::GetMappedRangeValueClamped(TRange<float>(0, 25), TRange<float>(0, 840), Distance);
		float NewZ = Average.Z + 150;
		FVector NewCameraLocation = FMath::Lerp(CameraActor->GetActorLocation(), FVector(-NewX, NewY, NewZ), 0.15);
		CameraActor->SetActorLocation(NewCameraLocation);
		if (!SequenceActor->SequencePlayer->IsPlaying())
		{
			SequenceCameraActor->SetActorLocation(FVector(0, 840, 175));
		}
	}
}

void ANightSkyGameState::UpdateUI()
{
	if (BattleHudActor != nullptr)
	{
		if (BattleHudActor->Widget != nullptr)
		{
			if (BattleHudActor->Widget->P1Health.Num() >= 3)
			{
				BattleHudActor->Widget->P1Health[0] = static_cast<float>(Players[0]->CurrentHealth) / static_cast<float>(Players[0]->MaxHealth);
				BattleHudActor->Widget->P1Health[1] = static_cast<float>(Players[1]->CurrentHealth) / static_cast<float>(Players[1]->MaxHealth);
				BattleHudActor->Widget->P1Health[2] = static_cast<float>(Players[2]->CurrentHealth) / static_cast<float>(Players[2]->MaxHealth);
			}
			if (BattleHudActor->Widget->P2Health.Num() >= 3)
			{
				BattleHudActor->Widget->P2Health[0] = static_cast<float>(Players[3]->CurrentHealth) / static_cast<float>(Players[3]->MaxHealth);
				BattleHudActor->Widget->P2Health[1] = static_cast<float>(Players[4]->CurrentHealth) / static_cast<float>(Players[4]->MaxHealth);
				BattleHudActor->Widget->P2Health[2] = static_cast<float>(Players[5]->CurrentHealth) / static_cast<float>(Players[5]->MaxHealth);
			}
			BattleHudActor->Widget->P1RoundsWon = BattleState.P1RoundsWon;
			BattleHudActor->Widget->P2RoundsWon = BattleState.P2RoundsWon;
			BattleHudActor->Widget->Timer = ceil(static_cast<float>(BattleState.RoundTimer) / 60);
			BattleHudActor->Widget->P1Meter = static_cast<float>(BattleState.Meter[0]) / 10000;
			BattleHudActor->Widget->P2Meter = static_cast<float>(BattleState.Meter[1]) / 10000;
			BattleHudActor->Widget->P1ComboCounter = Players[0]->ComboCounter;
			BattleHudActor->Widget->P2ComboCounter = Players[3]->ComboCounter;
		}
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

void ANightSkyGameState::ScreenPosToWorldPos(int32 X, int32 Y, int32* OutX, int32* OutY) const
{
	*OutX = BattleState.CurrentScreenPos - 840000 + 1800000 * X / 100;
}

void ANightSkyGameState::BattleHudVisibility(bool Visible) const
{
	if (Visible)
		BattleHudActor->Widget->SetVisibility(ESlateVisibility::Visible);
	else
		BattleHudActor->Widget->SetVisibility(ESlateVisibility::Hidden);
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
}
