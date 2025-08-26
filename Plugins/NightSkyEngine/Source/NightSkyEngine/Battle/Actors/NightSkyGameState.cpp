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
#include "NightSkyEngine/Battle/CPU/NightSkyAIController.h"
#include "NightSkyEngine/Data/BattleExtensionData.h"
#include "NightSkyEngine/Data/PrimaryCharaData.h"
#include "NightSkyEngine/Data/SubroutineData.h"
#include "NightSkyEngine/Network/FighterRunners.h"
#include "NightSkyEngine/Miscellaneous/NightSkyGameInstance.h"
#include "NightSkyEngine/UI/NightSkyBattleHudActor.h"
#include "NightSkyEngine/UI/NightSkyBattleWidget.h"
#include "Serialization/ObjectReader.h"
#include "Serialization/ObjectWriter.h"

void FRollbackData::Serialize(FArchive& Ar)
{
	Ar << ObjActive;
	Ar << ObjBuffer;
	Ar << CharBuffer;
	Ar << BattleStateBuffer;
	Ar << PlayerData;
	Ar << StateData;
	Ar << ExtensionData;
	Ar << WidgetAnimationData;
	Ar << SizeOfBPRollbackData;
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

	UpdateCamera();

	Init();
}

void ANightSkyGameState::Init()
{
	for (int i = 0; i < MaxRollbackFrames; i++)
	{
		RollbackData.Add(FRollbackData());
	}

	if (IsValid(BattleExtensionData))
	{
		for (auto Extension : BattleExtensionData->ExtensionArray)
		{
			BattleExtensions.Add(NewObject<UBattleExtension>(this, Extension));
			BattleExtensions.Last()->Parent = this;
			BattleExtensionNames.Add(BattleExtensions.Last()->Name);
		}
	}

	for (int i = 0; i < GameInstance->BattleData.PlayerListP1.Num(); i++)
	{
		APlayerObject* SpawnedPlayer;
		if (const auto Player = GameInstance->BattleData.PlayerListP1[i]; Player != nullptr)
		{
			Players.Add(GetWorld()->SpawnActor<APlayerObject>(Player->PlayerClass,
															   BattleSceneTransform));
			SpawnedPlayer = Players.Last();
			SpawnedPlayer->ColorIndex = 1;
			if (GameInstance->BattleData.ColorIndicesP1.Num() > i)
				SpawnedPlayer->ColorIndex = GameInstance->BattleData.ColorIndicesP1[i];
		}
		else
		{
			Players.Add(GetWorld()->SpawnActor<APlayerObject>(APlayerObject::StaticClass(), BattleSceneTransform));
			SpawnedPlayer = Players.Last();
		}
		SortedObjects.Add(SpawnedPlayer);
		SpawnedPlayer->InitPlayer();
		SpawnedPlayer->GameState = this;
	}

	for (int i = 0; i < GameInstance->BattleData.PlayerListP2.Num(); i++)
	{
		APlayerObject* SpawnedPlayer;
		if (const auto Player = GameInstance->BattleData.PlayerListP2[i]; Player != nullptr)
		{
			Players.Add(GetWorld()->SpawnActor<APlayerObject>(Player->PlayerClass,
															   BattleSceneTransform));
			SpawnedPlayer = Players.Last();
			SpawnedPlayer->ColorIndex = 1;
			if (GameInstance->BattleData.ColorIndicesP2.Num() > i)
				SpawnedPlayer->ColorIndex = GameInstance->BattleData.ColorIndicesP2[i];
			for (int j = 0; j < GameInstance->BattleData.PlayerListP1.Num(); j++)
			{
				if (IsValid(GameInstance->BattleData.PlayerListP1[j]))
				{
					if (SpawnedPlayer->IsA(GameInstance->BattleData.PlayerListP1[j]->PlayerClass))
					{
						if (SpawnedPlayer->ColorIndex == Players[j]->ColorIndex)
						{
							if (SpawnedPlayer->ColorIndex > 1)
								SpawnedPlayer->ColorIndex = 1;
							else
								SpawnedPlayer->ColorIndex = 2;
						}
						break;
					}
				}
			}
		}
		else
		{
			Players.Add(GetWorld()->SpawnActor<APlayerObject>(APlayerObject::StaticClass(), BattleSceneTransform));
			SpawnedPlayer = Players.Last();
		}
		SortedObjects.Add(SpawnedPlayer);
		SpawnedPlayer->InitPlayer();
		SpawnedPlayer->GameState = this;

		if (GameInstance->IsCPUBattle && !GameInstance->IsTraining)
		{
			SpawnedPlayer->SpawnDefaultController();
			SpawnedPlayer->bIsCpu = true;
		}
	}

	for (int i = 0; i < MaxBattleObjects; i++)
	{
		Objects.Add(GetWorld()->SpawnActor<ABattleObject>(BattleObjectClass, BattleSceneTransform));
		Objects[i]->GameState = this;
		SortedObjects.Add(Objects.Last());
	}

	MatchInit();
	HUDInit();
}

void ANightSkyGameState::PlayIntros()
{
	if (GameInstance->IsTraining)
	{
		BattleState.BattlePhase = EBattlePhase::Battle;
		GetMainPlayer(true)->JumpToStatePrimary(State_Universal_Stand);
		GetMainPlayer(false)->JumpToStatePrimary(State_Universal_Stand);
		return;
	}
	BattleState.BattlePhase = EBattlePhase::Intro;
	BattleState.CurrentIntroSide = INT_P1;
	GetMainPlayer(true)->JumpToStatePrimary(GetMainPlayer(true)->IntroName);
	BattleHudVisibility(false);
}

void ANightSkyGameState::RoundInit()
{
	BattleState.PauseTimer = false;
	BattleState.RandomManager.Reseed(BattleState.RandomManager.Rand() + BattleState.RoundCount);
	BattleState.RoundCount++;

	BattleState.ScreenData = Cast<ANightSkyGameState>(GetClass()->GetDefaultObject())->BattleState.ScreenData;

	BattleState.SuperFreezeSelfDuration = 0;
	BattleState.SuperFreezeDuration = 0;
	BattleState.SuperFreezeCaller = nullptr;
	BattleState.BattlePhase = EBattlePhase::Battle;
	BattleState.FadeTimer = BattleState.MaxFadeTimer;

	if (BattleState.BattleFormat == EBattleFormat::Rounds || BattleState.RoundCount == 1)
	{
		if (!GameInstance->IsTraining)
			BattleState.TimeUntilRoundStart = BattleState.MaxTimeUntilRoundStart;
		for (int i = 0; i < MaxBattleObjects; i++)
			Objects[i]->ResetObject();

		for (const auto Player : Players)
			Player->RoundInit(true);

		if (BattleState.RoundCount != 1)
		{
			GetMainPlayer(true)->JumpToStatePrimary(State_Universal_Stand);
			GetMainPlayer(false)->JumpToStatePrimary(State_Universal_Stand);
		}

		Players[0]->PlayerFlags = PLF_IsOnScreen;
		Players[BattleState.TeamData[0].TeamCount]->PlayerFlags = PLF_IsOnScreen;

		BattleState.MaxMeter[0] = Players[0]->MaxMeter;
		BattleState.MaxMeter[1] = Players[BattleState.TeamData[0].TeamCount]->MaxMeter;

		BattleState.RoundTimer = GameInstance->BattleData.StartRoundTimer * 60;
		BattleState.bHUDVisible = true;

		const FVector NewCameraLocation = BattleSceneTransform.GetRotation().RotateVector(FVector(0, 1080, 175)) +
			BattleSceneTransform.GetLocation();
		FRotator CameraRotation = BattleSceneTransform.GetRotation().Rotator();
		CameraRotation.Yaw -= 90;

		CameraActor->SetActorLocation(NewCameraLocation);
		CameraActor->SetActorRotation(CameraRotation);

		CallBattleExtension(BattleExtension_RoundInit);
	}
	else if (BattleState.BattleFormat == EBattleFormat::Tag)
	{
		const bool IsP1 = GetMainPlayer(true)->CurrentHealth == 0;
		GetMainPlayer(IsP1)->SetOnScreen(false);
		const auto NewPosX = GetMainPlayer(IsP1)->PosX;
		SwitchMainPlayer(GetMainPlayer(IsP1), 1);
		GetMainPlayer(IsP1)->PosX = NewPosX;
		GetMainPlayer(IsP1)->PosY = 0;
		GetMainPlayer(IsP1)->JumpToStatePrimary(State_Universal_TagIn);

		GetMainPlayer(true)->PlayerFlags &= ~PLF_RoundWinInputLock;
		GetMainPlayer(false)->PlayerFlags &= ~PLF_RoundWinInputLock;

		for (const auto& Player : Players) Player->RoundWinTimer = 300;
	}
	else
	{
		const bool IsP1 = GetMainPlayer(true)->CurrentHealth == 0;
		GetMainPlayer(IsP1)->SetOnScreen(false);
		SwitchMainPlayer(GetMainPlayer(IsP1), 1);

		if (!GameInstance->IsTraining)
			BattleState.TimeUntilRoundStart = BattleState.MaxTimeUntilRoundStart;
		for (int i = 0; i < MaxBattleObjects; i++)
			Objects[i]->ResetObject();

		for (const auto Player : Players)
			Player->RoundInit(false);

		GetMainPlayer(true)->JumpToStatePrimary(State_Universal_Stand);
		GetMainPlayer(false)->JumpToStatePrimary(State_Universal_Stand);

		GetMainPlayer(true)->PlayerFlags = PLF_IsOnScreen;
		GetMainPlayer(false)->PlayerFlags = PLF_IsOnScreen;

		BattleState.MaxMeter[0] = GetMainPlayer(true)->MaxMeter;
		BattleState.MaxMeter[1] = GetMainPlayer(false)->MaxMeter;

		BattleState.RoundTimer = GameInstance->BattleData.StartRoundTimer * 60;
		BattleState.bHUDVisible = true;

		const FVector NewCameraLocation = BattleSceneTransform.GetRotation().RotateVector(FVector(0, 1080, 175)) +
			BattleSceneTransform.GetLocation();
		FRotator CameraRotation = BattleSceneTransform.GetRotation().Rotator();
		CameraRotation.Yaw -= 90;

		CameraActor->SetActorLocation(NewCameraLocation);
		CameraActor->SetActorRotation(CameraRotation);

		CallBattleExtension(BattleExtension_RoundInit);
	}

	BattleState.ScreenData.TargetObjects.Add(GetMainPlayer(true));
	BattleState.ScreenData.TargetObjects.Add(GetMainPlayer(false));
}

void ANightSkyGameState::UpdateLocalInput()
{
	LocalInputs[0] = GetLocalInputs(0);
	LocalInputs[1] = GetLocalInputs(1);
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

	BattleState = Cast<ANightSkyGameState>(GetClass()->GetDefaultObject())->BattleState;

	BattleState.RandomManager = GameInstance->BattleData.Random;
	BattleState.TeamData[0].TeamCount = GameInstance->BattleData.PlayerListP1.Num();
	BattleState.TeamData[1].TeamCount = GameInstance->BattleData.PlayerListP2.Num();
	BattleState.GaugeP1.Empty();
	BattleState.GaugeP2.Empty();
	BattleState.GaugeP1.AddDefaulted(BattleState.MaxGauge.Num());
	BattleState.GaugeP2.AddDefaulted(BattleState.MaxGauge.Num());
	
	CallBattleExtension(BattleExtension_MatchInit);

	for (int i = 0; i < Players.Num(); i++)
	{
		Players[i]->PlayerIndex = i >= BattleState.TeamData[0].TeamCount;
		Players[i]->TeamIndex = i >= BattleState.TeamData[0].TeamCount ? i - BattleState.TeamData[0].TeamCount : i;
		Players[i]->PlayerFlags &= ~PLF_IsOnScreen;
		Players[i]->ObjNumber = i + MaxBattleObjects;
		Players[i]->CallSubroutine(Subroutine_Cmn_MatchInit);
		Players[i]->CallSubroutine(Subroutine_MatchInit);
	}
	for (int i = 0; i < MaxBattleObjects; i++)
	{
		Objects[i]->ObjNumber = i;
	}
	for (int i = SortedObjects.Num() - 1; i >= 0; i--)
	{
		SetDrawPriorityFront(SortedObjects[i]);
	}
	
	BattleState.MainPlayer[0] = Players[0];
	BattleState.MainPlayer[0]->PlayerFlags |= PLF_IsOnScreen;
	BattleState.MainPlayer[1] = Players[BattleState.TeamData[0].TeamCount];
	BattleState.MainPlayer[1]->PlayerFlags |= PLF_IsOnScreen;
	BattleState.BattleFormat = GameInstance->BattleData.BattleFormat;
	BattleState.MaxTimeUntilRoundStart = GameInstance->BattleData.TimeUntilRoundStart;
	BattleState.MaxRoundCount = GameInstance->BattleData.RoundCount;
	BattleState.RoundTimer = GameInstance->BattleData.StartRoundTimer * 60;

	PlayMusic(GameInstance->BattleData.MusicName);
	BattleHudActor->BottomWidget->PlayFadeOutAnim();
	RoundInit();
	PlayIntros();
}

void ANightSkyGameState::UpdateGameState(int32 Input1, int32 Input2, bool bShouldResimulate)
{
	if (bShouldResimulate == false && bIsResimulating == true) RollbackStartAudio(BattleState.FrameNumber);
	bIsResimulating = bShouldResimulate;
	LocalFrame++;

	ParticleManager->UpdateParticles();
	UpdateScreen();

	if (BattleState.BattlePhase == EBattlePhase::Intro)
	{
		if (BattleState.CurrentIntroSide == INT_P1)
		{
			if (GetMainPlayer(true)->IntroEndFlag)
			{
				GetMainPlayer(true)->JumpToStatePrimary(State_Universal_Stand);
			}
			if (GetMainPlayer(true)->GetCurrentStateName(StateMachine_Primary) != GetMainPlayer(true)->IntroName)
			{
				GetMainPlayer(false)->JumpToStatePrimary(GetMainPlayer(false)->IntroName);
				BattleState.CurrentIntroSide = INT_P2;
			}
		}
		else if (BattleState.CurrentIntroSide == INT_P2)
		{
			if (GetMainPlayer(false)->IntroEndFlag)
			{
				GetMainPlayer(false)->JumpToStatePrimary(State_Universal_Stand);
			}
			if (GetMainPlayer(false)->GetCurrentStateName(StateMachine_Primary) != GetMainPlayer(false)->IntroName)
			{
				GetMainPlayer(true)->JumpToStatePrimary(State_Universal_Stand);
				GetMainPlayer(false)->JumpToStatePrimary(State_Universal_Stand);
				BattleState.CurrentIntroSide = INT_None;
				BattleState.BattlePhase = EBattlePhase::Battle;
				BattleHudVisibility(true);
				BattleHudActor->BottomWidget->PlayRoundInitAnim();
			}
		}
	}

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

	if (!BattleState.SuperFreezeDuration)
	{
		CallBattleExtension(BattleExtension_Update);
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

	if (!BattleState.MainPlayer[0]->bIsCpu) BattleState.MainPlayer[0]->Inputs = Input1;
	else if (const auto CPU = Cast<ANightSkyAIController>(BattleState.MainPlayer[0]->Controller); CPU)
		CPU->Update();
	if (!BattleState.MainPlayer[1]->bIsCpu) BattleState.MainPlayer[1]->Inputs = Input2;
	else if (const auto CPU = Cast<ANightSkyAIController>(BattleState.MainPlayer[1]->Controller); CPU)
		CPU->Update();
	for (int i = 0; i < Players.Num(); i++)
	{
		for (int j = 0; j < Players.Num(); j++)
		{
			if (i < BattleState.TeamData[0].TeamCount)
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

	for (int i = 0; i < SortedObjects.Num(); i++)
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

				// Handle state transitions
				SortedObjects[i]->Player->HandleStateMachine(true, SortedObjects[i]->Player->GetStateMachine(StateMachine_Primary));
				for (auto& StateMachine : SortedObjects[i]->Player->SubStateMachines)
				{
					SortedObjects[i]->Player->HandleStateMachine(true, StateMachine);
				}
			}
			continue;
		}
		SortedObjects[i]->Update();
	}

	if (BattleState.SuperFreezeSelfDuration == 1)
	{
		BattleState.SuperFreezeCaller->TriggerEvent(EVT_SuperFreezeEnd, StateMachine_Primary);
	}
	if (BattleState.SuperFreezeDuration == 1)
	{
		for (int i = 0; i < SortedObjects.Num(); i++)
		{
			SortedObjects[i]->TriggerEvent(EVT_SuperFreezeEnd, StateMachine_Primary);
		}

		BattleState.PauseTimer = false;
		BattleState.SuperFreezeCaller = nullptr;
		BattleHudVisibility(true);
	}

	if (BattleState.SuperFreezeSelfDuration) BattleState.SuperFreezeSelfDuration--;
	if (BattleState.SuperFreezeDuration) BattleState.SuperFreezeDuration--;

	HandlePushCollision();
	SetScreenBounds();
	HandleRoundWin();

	// these aren't strictly game state related, but tying them to game state update makes things better	

	if (GameInstance->FighterRunner == Multiplayer && !GameInstance->IsReplay)
	{
		GameInstance->UpdateReplay(Input1, Input2);
	}

	CollisionView();

	const auto [network, timesync] = GetNetworkStats();
	NetworkStats.Ping = network.ping;
	const int32 LocalFramesBehind = timesync.local_frames_behind;
	const int32 RemoteFramesBehind = timesync.remote_frames_behind;

	if (LocalFramesBehind < 0 && RemoteFramesBehind < 0)
	{
		NetworkStats.RollbackFrames = abs(abs(LocalFramesBehind) - abs(RemoteFramesBehind));
	}
	else if (LocalFramesBehind > 0 && RemoteFramesBehind > 0)
	{
		NetworkStats.RollbackFrames = 0;
	}
	else
	{
		NetworkStats.RollbackFrames = abs(LocalFramesBehind) + abs(RemoteFramesBehind);
	}

	for (int i = 0; i < 2; i++)
	{
		if (BattleState.Meter[i] > BattleState.MaxMeter[i])
			BattleState.Meter[i] = BattleState.MaxMeter[i];
		if (BattleState.Meter[i] < 0)
			BattleState.Meter[i] = 0;
	}
	
	for (int i = 0; i < BattleState.MaxGauge.Num(); i++)
	{
		if (BattleState.GaugeP1[i] > BattleState.MaxGauge[i])
			BattleState.GaugeP1[i] = BattleState.MaxGauge[i];
		if (BattleState.GaugeP1[i] < 0)
			BattleState.GaugeP1[i] = 0;
	}
	for (int i = 0; i < BattleState.MaxGauge.Num(); i++)
	{
		if (BattleState.GaugeP2[i] > BattleState.MaxGauge[i])
			BattleState.GaugeP2[i] = BattleState.MaxGauge[i];
		if (BattleState.GaugeP2[i] < 0)
			BattleState.GaugeP2[i] = 0;
	}

	ParticleManager->PauseParticles();
	UpdateVisuals();
	UpdateCamera();
	UpdateHUD();
	ManageAudio();
}

void ANightSkyGameState::SetScreenCorners()
{
	const auto ScreenData = &BattleState.ScreenData;

	if (ScreenData->TargetObjects.Num() == 0)
	{
		ScreenData->ObjTop = 0;
		ScreenData->ObjBottom = 0;
		ScreenData->HigherObjBottom = 0;
		ScreenData->ObjLeft = 0;
		ScreenData->ObjRight = 0;
		ScreenData->ObjLength = 0;
		ScreenData->ObjHeight = 0;

		return;
	}

	bool bIsFirst = true;

	for (const auto Target : ScreenData->TargetObjects)
	{
		if (Target == nullptr) break;

		Target->CalculatePushbox();

		auto TargetL = Target->PosX - 85000;
		auto TargetR = Target->PosX + 85000;

		if (bIsFirst)
		{
			ScreenData->ObjTop = Target->T / 1000;
			ScreenData->ObjBottom = Target->B / 1000;
			ScreenData->HigherObjBottom = Target->B / 1000;
			ScreenData->ObjLeft = TargetL / 1000;
			ScreenData->ObjRight = TargetR / 1000;

			bIsFirst = false;
		}
		else
		{
			if (Target->T > ScreenData->ObjTop * 1000) ScreenData->ObjTop = Target->T / 1000;
			if (Target->B < ScreenData->ObjBottom * 1000) ScreenData->ObjBottom = Target->B / 1000;
			if (Target->B > ScreenData->HigherObjBottom * 1000) ScreenData->HigherObjBottom = Target->B / 1000;
			if (TargetL < ScreenData->ObjLeft * 1000) ScreenData->ObjLeft = TargetL / 1000;
			if (TargetR > ScreenData->ObjRight * 1000) ScreenData->ObjRight = TargetR / 1000;
		}
	}

	ScreenData->ObjLength = ScreenData->ObjRight - ScreenData->ObjLeft;
	ScreenData->ObjHeight = ScreenData->ObjTop - ScreenData->ObjBottom;
}

void ANightSkyGameState::UpdateScreen()
{
	const auto ScreenData = &BattleState.ScreenData;

	ScreenData->MaxZoomOutWidth = ScreenData->DefaultMaxWidth;
	ScreenData->ZoomOutBeginX = ScreenData->DefaultWidth;

	SetScreenCorners();

	if ((ScreenData->Flags & SCR_Lock) == 0)
	{
		if ((ScreenData->Flags & SCR_LockXPos) == 0)
			ScreenData->TargetCenterX = ScreenData->ObjLeft + ScreenData->
				ObjLength / 2;

		if ((ScreenData->Flags & SCR_LockWidth) == 0)
		{
			ScreenData->TargetWidth = ScreenData->ObjLength + ScreenData->ZoomOutBeginX / 4;
			if (ScreenData->TargetWidth < ScreenData->ZoomOutBeginX)
				ScreenData->TargetWidth = ScreenData->
					ZoomOutBeginX;
			if (ScreenData->TargetWidth > ScreenData->MaxZoomOutWidth)
				ScreenData->TargetWidth = ScreenData->
					MaxZoomOutWidth;
		}

		if ((ScreenData->Flags & SCR_LockYPos) == 0)
		{
			int TargetOffsetY;

			auto Ratio = 1280000 / ScreenData->TargetWidth;
			if (Ratio * ScreenData->ObjBottom / 1000 <= ScreenData->TargetOffsetAirYPos ||
				Ratio * (ScreenData->HigherObjBottom - ScreenData->ObjBottom) / 1000 >= ScreenData->
				TargetOffsetAirYDist)
			{
				TargetOffsetY = FMath::Min(ScreenData->TargetOffsetY + ScreenData->TargetOffsetLandYAdd, ScreenData->TargetOffsetLandYMax);
			}
			else
			{
				TargetOffsetY = FMath::Max(ScreenData->TargetOffsetY + ScreenData->TargetOffsetAirYAdd, ScreenData->TargetOffsetAirYMax);
			}

			ScreenData->TargetOffsetY = TargetOffsetY;
			
			Ratio = Ratio * ScreenData->HigherObjBottom / 1000 - Ratio * TargetOffsetY / 1000;
			ScreenData->TargetCenterY = FMath::Clamp(Ratio, 0, ScreenData->StageBoundsTop);
		}
	}

	const auto Width = ScreenData->TargetWidth - ScreenData->ScreenWorldWidth;
	ScreenData->WidthVelocity = Width / 14 - 1;
	ScreenData->ScreenWorldWidth += ScreenData->WidthVelocity;

	auto ScreenXSpeedFrame = 10;
	auto ScreenXSpeed = 50;

	ScreenData->CenterXVelocity = (ScreenData->TargetCenterX - ScreenData->ScreenWorldCenterX) / ScreenXSpeedFrame;

	if (ScreenData->CenterXVelocity > ScreenXSpeed) ScreenData->CenterXVelocity = ScreenXSpeed;
	else if (ScreenData->CenterXVelocity < -ScreenXSpeed) ScreenData->CenterXVelocity = -ScreenXSpeed;
	
	if (ScreenData->TargetCenterX - ScreenData->ScreenWorldCenterX > 0)
	{
		ScreenData->CenterXVelocity++;
	}
	else if (ScreenData->TargetCenterX - ScreenData->ScreenWorldCenterX < 0)
	{
		ScreenData->CenterXVelocity--;
	}

	ScreenData->ScreenWorldCenterX += ScreenData->CenterXVelocity;

	auto CenterYVelocity = ScreenData->TargetCenterY - ScreenData->ScreenWorldCenterY > 0 ? 3000 : 1000;
	auto ScreenYSpeed = 250;

	if (ScreenData->TargetCenterY - ScreenData->ScreenWorldCenterY <= 0) ScreenData->CenterYVelocity = 3000;

	ScreenData->CenterYVelocity = (ScreenData->TargetCenterY - ScreenData->ScreenWorldCenterY) * 1000 / CenterYVelocity;

	if (ScreenData->CenterYVelocity > ScreenYSpeed) ScreenData->CenterYVelocity = ScreenYSpeed;
	else if (ScreenData->CenterYVelocity < -ScreenYSpeed) ScreenData->CenterYVelocity = -ScreenYSpeed;

	if (ScreenData->TargetCenterY - ScreenData->ScreenWorldCenterY > 0)
	{
		ScreenData->CenterYVelocity++;
	}
	else if (ScreenData->TargetCenterY - ScreenData->ScreenWorldCenterY < 0)
	{
		ScreenData->CenterYVelocity--;
	}

	ScreenData->ScreenWorldCenterY += ScreenData->CenterYVelocity;

	ScreenData->bTouchingWorldSide = false;

	if (ScreenData->ScreenWorldCenterX + ScreenData->ScreenWorldWidth / 2 >= ScreenData->StageBoundsRight)
	{
		ScreenData->ScreenWorldCenterX = ScreenData->StageBoundsRight - ScreenData->ScreenWorldWidth / 2;
		ScreenData->bTouchingWorldSide = true;
	}

	if (ScreenData->ScreenWorldCenterX - ScreenData->ScreenWorldWidth / 2 <= ScreenData->StageBoundsLeft)
	{
		ScreenData->ScreenWorldCenterX = ScreenData->StageBoundsLeft + ScreenData->ScreenWorldWidth / 2;
		ScreenData->bTouchingWorldSide = true;
	}

	ScreenData->ScreenBoundsLeft = ScreenData->ScreenWorldCenterX - ScreenData->ScreenWorldWidth / 2;
	ScreenData->ScreenBoundsRight = ScreenData->ScreenWorldCenterX + ScreenData->ScreenWorldWidth / 2;

	if (ScreenData->Flags & SCR_DisableScreenSides)
	{
		ScreenData->ScreenBoundsLeft = ScreenData->StageBoundsLeft;
		ScreenData->ScreenBoundsRight = ScreenData->StageBoundsRight;
	}

	ScreenData->ScreenBoundsTop = 106432 / (ScreenData->ZoomOutBeginX * 1000 / ScreenData->ScreenWorldWidth) +
		368000 / (ScreenData->ZoomOutBeginX * 1000 / ScreenData->ScreenWorldWidth) + ScreenData->ScreenWorldCenterY;

	ScreenData->FinalScreenX = ScreenData->ScreenWorldCenterX;
	ScreenData->FinalScreenY = ScreenData->ScreenWorldCenterY;
	ScreenData->FinalScreenWidth = ScreenData->ScreenWorldWidth;

	ScreenData->FinalScreenWidth <= 0 ? 1 : ScreenData->FinalScreenWidth;

	if (ScreenData->FinalScreenY >= ScreenData->StageBoundsTop - 106)
		ScreenData->FinalScreenY = ScreenData->
			StageBoundsTop - 106;

	ScreenData->ScreenYZoom = 130 * (1
		- static_cast<float>(ScreenData->FinalScreenWidth) / static_cast<float>(ScreenData->DefaultWidth));
}

void ANightSkyGameState::UpdateGameState()
{
	RemoteFrame++;
	UpdateLocalInput();
	UpdateGameState(LocalInputs[0], LocalInputs[1],
	                false);
}

void ANightSkyGameState::SortObjects()
{
	BattleState.ActiveObjectCount = Players.Num();
	for (int i = Players.Num(); i < SortedObjects.Num(); i++)
	{
		for (int j = i + 1; j < SortedObjects.Num(); j++)
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
	for (int i = 0; i < Players.Num(); i++)
	{
		for (int j = 0; j < Players.Num(); j++)
		{
			if (Players[i]->PlayerIndex != Players[j]->PlayerIndex && Players[i]->PlayerFlags & PLF_IsOnScreen &&
				Players[j]->PlayerFlags & PLF_IsOnScreen)
			{
				Players[i]->HandlePushCollision(Players[j]);
			}
		}
	}
}

void ANightSkyGameState::HandleHitCollision() const
{
	for (int i = 0; i < SortedObjects.Num(); i++)
	{
		if (i == BattleState.ActiveObjectCount)
			break;
		for (int j = 0; j < SortedObjects.Num(); j++)
		{
			if (j == BattleState.ActiveObjectCount)
				break;
			if (SortedObjects[i]->Player->PlayerIndex != SortedObjects[j]->Player->PlayerIndex 
				&& SortedObjects[i]->Player->PlayerFlags & PLF_IsOnScreen
				&& SortedObjects[j]->Player->PlayerFlags & PLF_IsOnScreen)
			{
				SortedObjects[i]->HandleCustomCollision_PreHit(SortedObjects[j]);
				SortedObjects[i]->HandleClashCollision(SortedObjects[j]);
				SortedObjects[i]->HandleHitCollision(SortedObjects[j]);
				SortedObjects[i]->HandleCustomCollision_PostHit(SortedObjects[j]);
			}
		}
	}
}

void ANightSkyGameState::UpdateVisuals() const
{
	for (int i = 0; i < SortedObjects.Num(); i++)
	{
		if (i == BattleState.ActiveObjectCount)
			break;
		SortedObjects[i]->UpdateVisuals();
	}
}

void ANightSkyGameState::HandleRoundWin()
{
	if (BattleState.BattlePhase == EBattlePhase::EndScreen) return;
	
	if (GetMainPlayer(true)->CurrentHealth > 0 && GetMainPlayer(false)->CurrentHealth <= 0)
	{
		if ((GetMainPlayer(true)->PlayerFlags & PLF_RoundWinInputLock) == 0)
			BattleState.P1RoundsWon++;
		GetMainPlayer(true)->RoundWinTimer--;
		GetMainPlayer(true)->PlayerFlags |= PLF_RoundWinInputLock;
		if (BattleState.BattlePhase < EBattlePhase::RoundEnd)
			BattleState.BattlePhase = EBattlePhase::RoundEnd;
		BattleState.PauseTimer = true;
		if (GetMainPlayer(true)->RoundWinTimer == 0)
		{
			GetMainPlayer(true)->JumpToStatePrimary(State_Universal_RoundWin);
		}
		NextRoundTransition(true);
	}
	else if (GetMainPlayer(false)->CurrentHealth > 0 && GetMainPlayer(true)->CurrentHealth <= 0)
	{
		if ((GetMainPlayer(false)->PlayerFlags & PLF_RoundWinInputLock) == 0)
			BattleState.P2RoundsWon++;
		GetMainPlayer(false)->RoundWinTimer--;
		GetMainPlayer(false)->PlayerFlags |= PLF_RoundWinInputLock;
		if (BattleState.BattlePhase < EBattlePhase::RoundEnd)
			BattleState.BattlePhase = EBattlePhase::RoundEnd;
		BattleState.PauseTimer = true;
		if (GetMainPlayer(false)->RoundWinTimer == 0)
		{
			GetMainPlayer(false)->JumpToStatePrimary(State_Universal_RoundWin);
		}
		NextRoundTransition(false);
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
		if (BattleState.BattlePhase < EBattlePhase::RoundEnd)
			BattleState.BattlePhase = EBattlePhase::RoundEnd;
		BattleState.PauseTimer = true;
		NextRoundTransition(true);
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
			if (BattleState.BattlePhase < EBattlePhase::RoundEnd)
				BattleState.BattlePhase = EBattlePhase::RoundEnd;
			BattleState.PauseTimer = true;
			if (GetMainPlayer(true)->RoundWinTimer == 0)
			{
				GetMainPlayer(true)->JumpToStatePrimary(State_Universal_RoundWin);
				GetMainPlayer(false)->JumpToStatePrimary(State_Universal_RoundLose);
			}
			NextRoundTransition(true);
		}
		else if (GetMainPlayer(false)->CurrentHealth > GetMainPlayer(true)->CurrentHealth)
		{
			if ((GetMainPlayer(false)->PlayerFlags & PLF_RoundWinInputLock) == 0)
				BattleState.P2RoundsWon++;
			GetMainPlayer(false)->RoundWinTimer--;
			GetMainPlayer(true)->PlayerFlags |= PLF_RoundWinInputLock;
			GetMainPlayer(false)->PlayerFlags |= PLF_RoundWinInputLock;
			if (BattleState.BattlePhase < EBattlePhase::RoundEnd)
				BattleState.BattlePhase = EBattlePhase::RoundEnd;
			BattleState.PauseTimer = true;
			if (GetMainPlayer(false)->RoundWinTimer == 0)
			{
				GetMainPlayer(false)->JumpToStatePrimary(State_Universal_RoundWin);
				GetMainPlayer(true)->JumpToStatePrimary(State_Universal_RoundLose);
			}
			NextRoundTransition(false);
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
			if (BattleState.BattlePhase < EBattlePhase::RoundEnd)
				BattleState.BattlePhase = EBattlePhase::RoundEnd;
			GetMainPlayer(true)->RoundWinTimer--;
			BattleState.PauseTimer = true;
			if (GetMainPlayer(true)->RoundWinTimer == 0)
			{
				GetMainPlayer(true)->JumpToStatePrimary(State_Universal_RoundLose);
				GetMainPlayer(false)->JumpToStatePrimary(State_Universal_RoundLose);
			}
			NextRoundTransition(true);
		}
	}
}

void ANightSkyGameState::NextRoundTransition(bool bIsP1)
{
	if (GetMainPlayer(bIsP1)->RoundWinTimer <= 0)
	{
		if (IsTagBattle())
		{
			if (!HandleMatchWin())
			{
				RoundInit();
			}
		}
		else if (!HandleMatchWin() && GetMainPlayer(bIsP1)->RoundEndFlag == true)
		{
			if (BattleState.BattlePhase != EBattlePhase::Fade)
			{
				BattleHudActor->BottomWidget->PlayFadeAnim();
				BattleState.BattlePhase = EBattlePhase::Fade;
			}
			BattleState.FadeTimer--;
			if (BattleState.FadeTimer <= 0)
			{
				RoundInit();
				BattleHudActor->BottomWidget->PlayRoundInitAnim();
			}
		}
	}
}

bool ANightSkyGameState::HandleMatchWin()
{
	if (BattleState.CurrentWinSide != WIN_None) {
		if (BattleState.BattlePhase == EBattlePhase::EndScreen) return true;
		if (BattleState.CurrentWinSide == WIN_P2)
		{
			if (GetMainPlayer(false)->RoundEndFlag == true)
			{
				EndMatch();
			}
		}
		else
		{
			if (GetMainPlayer(true)->RoundEndFlag == true)
			{
				EndMatch();
			}
		}
		return true;
	}
	switch (BattleState.BattleFormat)
	{
	case EBattleFormat::Rounds:
		{
			if (BattleState.P1RoundsWon >= BattleState.MaxRoundCount && BattleState.P2RoundsWon < BattleState.P1RoundsWon)
			{
				GetMainPlayer(true)->JumpToStatePrimary(State_Universal_MatchWin);
				GameInstance->EndRecordReplay();
				BattleState.CurrentWinSide = WIN_P1;
				return true;
			}
			if (BattleState.P2RoundsWon >= BattleState.MaxRoundCount && BattleState.P1RoundsWon < BattleState.P2RoundsWon)
			{
				GetMainPlayer(false)->JumpToStatePrimary(State_Universal_MatchWin);
				GameInstance->EndRecordReplay();
				BattleState.CurrentWinSide = WIN_P2;
				return true;
			}
			if (BattleState.P1RoundsWon > BattleState.MaxRoundCount && BattleState.P2RoundsWon > BattleState.MaxRoundCount)
			{
				GameInstance->EndRecordReplay();
				BattleState.CurrentWinSide = WIN_Draw;
				return true;
			}
		}
		return false;
	case EBattleFormat::Tag:
	case EBattleFormat::KOF:
		{
			if (BattleState.P1RoundsWon >= BattleState.TeamData[1].TeamCount && BattleState.P2RoundsWon < BattleState.P1RoundsWon)
			{
				GetMainPlayer(true)->JumpToStatePrimary(State_Universal_MatchWin);
				GameInstance->EndRecordReplay();
				BattleState.CurrentWinSide = WIN_P1;
				return true;
			}
			if (BattleState.P2RoundsWon >= BattleState.TeamData[0].TeamCount && BattleState.P1RoundsWon < BattleState.P2RoundsWon)
			{
				GetMainPlayer(false)->JumpToStatePrimary(State_Universal_MatchWin);
				GameInstance->EndRecordReplay();
				BattleState.CurrentWinSide = WIN_P2;
				return true;
			}
			if (BattleState.P1RoundsWon >= BattleState.TeamData[1].TeamCount && BattleState.P2RoundsWon >= BattleState.TeamData[0].TeamCount)
			{
				GameInstance->EndRecordReplay();
				BattleState.CurrentWinSide = WIN_Draw;
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

	Checksum += BattleState.Meter[0] ^ BattleState.Meter[0] << 16;
	Checksum += BattleState.Meter[1] ^ BattleState.Meter[1] << 16;

	for (const auto Gauge : BattleState.GaugeP1)
	{
		Checksum += Gauge ^ Gauge << 16;
	}
	for (const auto Gauge : BattleState.GaugeP2)
	{
		Checksum += Gauge ^ Gauge << 16;
	}

	return Checksum;
}

FGGPONetworkStats ANightSkyGameState::GetNetworkStats() const
{
	FGGPONetworkStats Stats{};
	if (AFighterMultiplayerRunner* Runner = Cast<AFighterMultiplayerRunner>(FighterRunner))
	{
		if (Runner->Players[0]->type == GGPO_PLAYERTYPE_REMOTE)
			GGPONet::ggpo_get_network_stats(Runner->ggpo, Runner->PlayerHandles[0], &Stats);
		else
			GGPONet::ggpo_get_network_stats(Runner->ggpo, Runner->PlayerHandles[1], &Stats);
		return Stats;
	}
	return Stats;
}

void ANightSkyGameState::SetScreenBounds() const
{
	for (int i = 0; i < BattleState.ActiveObjectCount; i++)
	{
		if (SortedObjects[i] != nullptr)
		{
			if (SortedObjects[i]->MiscFlags & MISC_WallCollisionActive)
			{
				const auto ScreenData = &BattleState.ScreenData;

				if (const auto Player = Cast<APlayerObject>(SortedObjects[i]))
				{
					if (!(Player->PlayerFlags & PLF_IsOnScreen)) continue;
					Player->PlayerFlags |= PLF_TouchingWall;
					Player->WallTouchTimer++;
				}

				SortedObjects[i]->CalculatePushbox();

				if (SortedObjects[i]->PosX + 85000 >= ScreenData->ScreenBoundsRight * 1000)
				{
					SortedObjects[i]->PosX = ScreenData->ScreenBoundsRight * 1000 - 85000;
				}
				else if (SortedObjects[i]->PosX - 85000 <= ScreenData->ScreenBoundsLeft * 1000)
				{
					SortedObjects[i]->PosX = ScreenData->ScreenBoundsLeft * 1000 + 85000;
				}
				else
				{
					if (const auto Player = Cast<APlayerObject>(SortedObjects[i]))
					{
						Player->PlayerFlags &= ~PLF_TouchingWall;
						Player->WallTouchTimer = 0;
					}
				}

				if (SortedObjects[i]->PosY >= ScreenData->ScreenBoundsTop * 1000)
				{
					SortedObjects[i]->PosY = ScreenData->ScreenBoundsTop * 1000;
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
		const auto ScreenData = &BattleState.ScreenData;

		BattleState.CameraPosition = BattleSceneTransform.GetRotation().RotateVector(
			FVector(ScreenData->FinalScreenX * 0.43, ScreenData->FinalScreenWidth * 0.43,
			        ScreenData->FinalScreenY * 0.43 - ScreenData->ScreenYZoom + 130)) + BattleSceneTransform.GetLocation();
		CameraActor->SetActorLocation(BattleState.CameraPosition);
		if (BattleState.CurrentSequenceTime == -1)
		{
			const FVector SequenceCameraLocation = BattleSceneTransform.GetRotation().RotateVector(
					FVector(0, 1080, 175)) + BattleSceneTransform.GetLocation();
			SequenceCameraActor->SetActorLocation(SequenceCameraLocation);
			if (const auto PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0); IsValid(
				PlayerController))
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

			SequenceCameraActor->SetActorLocation(
				BattleSceneTransform.GetRotation().RotateVector(NewCamLocation) + BattleSceneTransform.GetLocation());

			const FRotator CameraRotation = BattleSceneTransform.GetRotation().Rotator() + SequenceCameraActor->
				GetActorRotation();

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
			SequenceActor->SetBinding(BindingId, TArray<AActor*>{Target});

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
			SequenceActor->SetBinding(BindingId, TArray<AActor*>{Enemy});

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
			SequenceActor->SetBinding(BindingId, TArray<AActor*>{CameraActor});

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
			SequenceActor->SetBinding(BindingId, TArray<AActor*>{SequenceCameraActor});

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

void ANightSkyGameState::HUDInit() const
{
	if (BattleHudActor != nullptr)
	{
		if (BattleHudActor->TopWidget != nullptr)
		{
			BattleHudActor->TopWidget->P1Health.Init(0, BattleState.TeamData[0].TeamCount);
			BattleHudActor->TopWidget->P2Health.Init(0, BattleState.TeamData[1].TeamCount);
			BattleHudActor->TopWidget->P1RecoverableHealth.Init(0, BattleState.TeamData[0].TeamCount);
			BattleHudActor->TopWidget->P2RecoverableHealth.Init(0, BattleState.TeamData[1].TeamCount);
		}
	}
}

void ANightSkyGameState::UpdateHUD()
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
			for (int i = 0; i < BattleState.TeamData[0].TeamCount; i++)
			{
				BattleHudActor->TopWidget->P1Health[i] = static_cast<float>(GetTeam(true)[i]->CurrentHealth) /
					static_cast<float>(GetTeam(true)[i]->MaxHealth);
				BattleHudActor->TopWidget->P1RecoverableHealth[i] = static_cast<float>(GetTeam(true)[i]->CurrentHealth +
					GetTeam(true)[i]->RecoverableHealth) / static_cast<float>(GetTeam(true)[i]->MaxHealth);
			}
			for (int i = 0; i < BattleState.TeamData[1].TeamCount; i++)
			{
				BattleHudActor->TopWidget->P2Health[i] = static_cast<float>(GetTeam(false)[i]->CurrentHealth) /
					static_cast<float>(GetTeam(false)[i]->MaxHealth);
				BattleHudActor->TopWidget->P2RecoverableHealth[i] = static_cast<float>(GetTeam(false)[i]->CurrentHealth
					+ GetTeam(false)[i]->RecoverableHealth) / static_cast<float>(GetTeam(false)[i]->MaxHealth);
			}
			BattleHudActor->TopWidget->P1RoundsWon = BattleState.P1RoundsWon;
			BattleHudActor->TopWidget->P2RoundsWon = BattleState.P2RoundsWon;
			BattleHudActor->TopWidget->Timer = static_cast<float>(BattleState.RoundTimer / 60);
			BattleHudActor->TopWidget->P1ComboCounter = BattleState.MainPlayer[0]->ComboCounter;
			BattleHudActor->TopWidget->P2ComboCounter = BattleState.MainPlayer[1]->ComboCounter;
			BattleHudActor->TopWidget->Ping = NetworkStats.Ping;
			BattleHudActor->TopWidget->RollbackFrames = NetworkStats.RollbackFrames;
			
			if (BattleHudActor->TopWidget->P1Gauge.IsEmpty())
				BattleHudActor->TopWidget->P1Gauge.SetNum(
					BattleState.MaxGauge.Num());
			if (BattleHudActor->TopWidget->P2Gauge.IsEmpty())
				BattleHudActor->TopWidget->P2Gauge.SetNum(
					BattleState.MaxGauge.Num());
			
			for (int j = 0; j < BattleState.MaxGauge.Num(); j++)
			{
				BattleHudActor->TopWidget->P1Gauge[j] = static_cast<float>(BattleState.GaugeP1[j]) / BattleState.
					MaxGauge[j];
				BattleHudActor->TopWidget->P2Gauge[j] = static_cast<float>(BattleState.GaugeP2[j]) / BattleState.
					MaxGauge[j];
			}
		}
		if (BattleHudActor->BottomWidget != nullptr)
		{
			BattleHudActor->BottomWidget->P1Meter = static_cast<float>(BattleState.Meter[0]) / 10000;
			BattleHudActor->BottomWidget->P2Meter = static_cast<float>(BattleState.Meter[1]) / 10000;

			if (BattleHudActor->BottomWidget->P1Gauge.IsEmpty())
				BattleHudActor->BottomWidget->P1Gauge.SetNum(
					BattleState.MaxGauge.Num());
			if (BattleHudActor->BottomWidget->P2Gauge.IsEmpty())
				BattleHudActor->BottomWidget->P2Gauge.SetNum(
					BattleState.MaxGauge.Num());

			for (int j = 0; j < BattleState.MaxGauge.Num(); j++)
			{
				BattleHudActor->BottomWidget->P1Gauge[j] = static_cast<float>(BattleState.GaugeP1[j]) / BattleState.
					MaxGauge[j];
				BattleHudActor->BottomWidget->P2Gauge[j] = static_cast<float>(BattleState.GaugeP2[j]) / BattleState.
					MaxGauge[j];
			}
		}
		UpdateHUD_BP();
	}

	UpdateHUDAnimations_BP();
	
	BattleHudActor->TopWidget->PlayStandardAnimations();
	BattleHudActor->TopWidget->SetAnimationRollbackData();
	BattleHudActor->BottomWidget->PlayStandardAnimations();
	BattleHudActor->BottomWidget->SetAnimationRollbackData();
	
	for (auto& [Anim, Time, bPlaying] : BattleHudActor->TopWidget->WidgetAnimationRollback)
	{
		bPlaying = BattleHudActor->TopWidget->IsAnimationPlaying(Anim);
		Time = BattleHudActor->TopWidget->GetAnimationCurrentTime(Anim);
	}

	for (auto& [Anim, Time, bPlaying] : BattleHudActor->BottomWidget->WidgetAnimationRollback)
	{
		bPlaying = BattleHudActor->BottomWidget->IsAnimationPlaying(Anim);
		Time = BattleHudActor->BottomWidget->GetAnimationCurrentTime(Anim);
	}
}

void ANightSkyGameState::SetDrawPriorityFront(ABattleObject* InObject) const
{
	if (InObject->IsPlayer)
	{
		for (int i = 0; i < Players.Num(); i++)
		{
			if (SortedObjects[i]->DrawPriority <= InObject->DrawPriority)
				SortedObjects[i]->DrawPriority++;
		}
		InObject->DrawPriority = 0;
		return;
	}
	for (int i = Players.Num(); i < BattleState.ActiveObjectCount; i++)
	{
		if (SortedObjects[i]->DrawPriority <= InObject->DrawPriority)
			SortedObjects[i]->DrawPriority++;
		InObject->DrawPriority = Players.Num();
	}
}

APlayerObject* ANightSkyGameState::SwitchMainPlayer(APlayerObject* InPlayer, int TeamIndex)
{
	if (TeamIndex == 0) return nullptr;
	const bool IsP1 = InPlayer->PlayerIndex == 0;
	if (BattleState.BattleFormat != EBattleFormat::Tag && TeamIndex >= BattleState.TeamData[IsP1 == false].TeamCount) return nullptr;
	if (BattleState.TeamData[IsP1 == false].CooldownTimer[TeamIndex] > 0) return nullptr;

	const auto NewPlayer = GetTeam(IsP1)[TeamIndex];
	if (NewPlayer->CurrentHealth == 0) return nullptr;
	if (NewPlayer->PlayerFlags & PLF_IsOnScreen) return nullptr;
	NewPlayer->TeamIndex = 0;
	InPlayer->TeamIndex = TeamIndex;
	BattleState.ScreenData.TargetObjects.Remove(InPlayer);
	BattleState.ScreenData.TargetObjects.Add(NewPlayer);
	NewPlayer->JumpToStatePrimary(State_Universal_TagIn);
	NewPlayer->SetOnScreen(true);
	for (const auto EnemyPlayer : GetTeam(!IsP1))
	{
		EnemyPlayer->Enemy = NewPlayer;
	}
	BattleState.MainPlayer[!IsP1] = NewPlayer;
	BattleState.TeamData[IsP1 == 0].CooldownTimer[TeamIndex] = BattleState.TagCooldown;
	return NewPlayer;
}

APlayerObject* ANightSkyGameState::CallAssist(const bool IsP1, const int AssistIndex, const FGameplayTag AssistName)
{
	if (AssistIndex == 0) return nullptr;
	if (BattleState.BattleFormat != EBattleFormat::Tag && AssistIndex >= BattleState.TeamData[IsP1 == false].TeamCount) return nullptr;
	if (BattleState.TeamData[IsP1 == 0].CooldownTimer[AssistIndex] > 0) return nullptr;

	const auto NewPlayer = GetTeam(IsP1)[AssistIndex];
	if (NewPlayer->CurrentHealth == 0) return nullptr;
	if (NewPlayer->PlayerFlags & PLF_IsOnScreen) return nullptr;
	NewPlayer->JumpToStatePrimary(AssistName);
	NewPlayer->SetOnScreen(true);
	NewPlayer->Direction = GetMainPlayer(IsP1)->Direction;
	BattleState.TeamData[IsP1 == 0].CooldownTimer[AssistIndex] = BattleState.AssistCooldown;
	return NewPlayer;
}

bool ANightSkyGameState::CanTag(const APlayerObject* InPlayer, int TeamIndex) const
{
	if (TeamIndex == 0) return false;
	const bool IsP1 = InPlayer->PlayerIndex == 0;
	if (BattleState.BattleFormat != EBattleFormat::Tag && TeamIndex >= BattleState.TeamData[IsP1 == false].TeamCount) return false;

	if (BattleState.TeamData[IsP1 == 0].CooldownTimer[TeamIndex] > 0) return false;

	const auto NewPlayer = GetTeam(IsP1)[TeamIndex];
	if (NewPlayer->CurrentHealth == 0) return false;
	if (NewPlayer->PlayerFlags & PLF_IsOnScreen) return false;

	return true;
}

int ANightSkyGameState::GetLocalInputs(int Index) const
{
	if (const ANightSkyPlayerController* Controller = Cast<ANightSkyPlayerController>(
		UGameplayStatics::GetPlayerController(GetWorld(), Index)); Controller != nullptr)
	{
		return Controller->Inputs;
	}
	return 0;
}

void ANightSkyGameState::SetOtherChecksum(uint32 RemoteChecksum, int32 InFrame)
{
	OtherChecksum = RemoteChecksum;
	OtherChecksumFrame = InFrame;
}

void ANightSkyGameState::PlayAnnouncerVoice(const FGameplayTag Name)
{
	if (!IsValid(GameInstance))
		return;
	if (GameInstance->AnnouncerData != nullptr)
	{
		for (FSoundStruct SoundStruct : GameInstance->AnnouncerData->SoundDatas)
		{
			if (SoundStruct.Name == Name)
			{
				PlayAnnouncerVoice(SoundStruct.SoundWave, SoundStruct.MaxDuration);
				break;
			}
		}
	}
}

TArray<APlayerObject*> ANightSkyGameState::GetTeam(bool IsP1) const
{
	if (IsP1)
	{
		TArray<APlayerObject*> PlayerObjects;
		for (int i = 0; i < BattleState.TeamData[0].TeamCount; i++)
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
	for (int i = BattleState.TeamData[1].TeamCount; i < Players.Num(); i++)
	{
		PlayerObjects.Add(Players[i]);
		for (int j = 0; j < PlayerObjects.Num() - 1; j++)
		{
			if (PlayerObjects[i - BattleState.TeamData[0].TeamCount]->TeamIndex < PlayerObjects[j]->TeamIndex)
			{
				PlayerObjects.Swap(i - BattleState.TeamData[0].TeamCount, j);
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

void ANightSkyGameState::CallBattleExtension(FGameplayTag Name)
{
	if (BattleExtensionNames.Find(FGameplayTag(Name)) != INDEX_NONE)
	{
		BattleExtensions[BattleExtensionNames.Find(FGameplayTag(Name))]->Exec();
	}
}

int32 ANightSkyGameState::GetGauge(bool IsP1, int32 GaugeIndex) const
{
	if (GaugeIndex < BattleState.MaxGauge.Num())
	{
		if (IsP1) return BattleState.GaugeP1[GaugeIndex];
		return BattleState.GaugeP2[GaugeIndex];
	}

	return -1;
}

void ANightSkyGameState::SetGauge(bool IsP1, int32 GaugeIndex, int32 Value)
{
	if (GaugeIndex < BattleState.MaxGauge.Num())
	{
		if (IsP1) BattleState.GaugeP1[GaugeIndex] = Value;
		else BattleState.GaugeP2[GaugeIndex] = Value;
	}
}

void ANightSkyGameState::UseGauge(bool IsP1, int32 GaugeIndex, int32 Value)
{
	if (GaugeIndex < BattleState.MaxGauge.Num())
	{
		if (IsP1) BattleState.GaugeP1[GaugeIndex] -= Value;
		else BattleState.GaugeP2[GaugeIndex] -= Value;
	}
}

bool ANightSkyGameState::IsTagBattle() const
{
	return BattleState.BattleFormat == EBattleFormat::Tag;
}

int32 ANightSkyGameState::GetTeamCount(const bool bIsP1) const
{
	return BattleState.TeamData[bIsP1 == false].TeamCount;
}

void ANightSkyGameState::ScreenPosToWorldPos(const int32 X, const int32 Y, int32* OutX, int32* OutY) const
{
	*OutX = BattleState.ScreenData.FinalScreenX * X / 100;
	*OutY = BattleState.ScreenData.FinalScreenY * Y / 100;
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

void ANightSkyGameState::PlayMusic(const FGameplayTag Name)
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
	for (int i = 0; i < CommonAudioChannelCount; i++)
	{
		const int CurrentAudioTime = BattleState.FrameNumber - BattleState.CommonAudioChannels[i].StartingFrame;
		if (!BattleState.CommonAudioChannels[i].Finished && static_cast<int>(BattleState.CommonAudioChannels[i].
			MaxDuration * 60) < CurrentAudioTime)
		{
			BattleState.CommonAudioChannels[i].Finished = true;
			BattleState.CommonAudioChannels[i].SoundWave = nullptr;
			if (bIsResimulating) continue;
			AudioManager->CommonAudioPlayers[i]->Stop();
			AudioManager->CommonAudioPlayers[i]->SetSound(nullptr);
		}
	}
	for (int i = 0; i < CharaAudioChannelCount; i++)
	{
		const int CurrentAudioTime = BattleState.FrameNumber - BattleState.CharaAudioChannels[i].StartingFrame;
		if (!BattleState.CharaAudioChannels[i].Finished && static_cast<int>(BattleState.CharaAudioChannels[i].
			MaxDuration * 60) < CurrentAudioTime)
		{
			BattleState.CharaAudioChannels[i].Finished = true;
			BattleState.CharaAudioChannels[i].SoundWave = nullptr;
			if (bIsResimulating) continue;
			AudioManager->CharaAudioPlayers[i]->Stop();
			AudioManager->CharaAudioPlayers[i]->SetSound(nullptr);
		}
	}
	for (int i = 0; i < CharaVoiceChannelCount; i++)
	{
		const int CurrentAudioTime = BattleState.FrameNumber - BattleState.CharaVoiceChannels[i].StartingFrame;
		if (!BattleState.CharaVoiceChannels[i].Finished && static_cast<int>(BattleState.CharaVoiceChannels[i].
			MaxDuration * 60) < CurrentAudioTime)
		{
			BattleState.CharaVoiceChannels[i].Finished = true;
			BattleState.CharaVoiceChannels[i].SoundWave = nullptr;
			if (bIsResimulating) continue;
			AudioManager->CharaVoicePlayers[i]->Stop();
			AudioManager->CharaVoicePlayers[i]->SetSound(nullptr);
		}
	}
	{
		const int CurrentAudioTime = BattleState.FrameNumber - BattleState.AnnouncerVoiceChannel.StartingFrame;
		if (!BattleState.AnnouncerVoiceChannel.Finished && static_cast<int>(BattleState.AnnouncerVoiceChannel.
			MaxDuration * 60) < CurrentAudioTime)
		{
			BattleState.AnnouncerVoiceChannel.Finished = true;
			BattleState.AnnouncerVoiceChannel.SoundWave = nullptr;
			if (!bIsResimulating)
			{
				AudioManager->AnnouncerVoicePlayer->Stop();
				AudioManager->AnnouncerVoicePlayer->SetSound(nullptr);
			}
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

void ANightSkyGameState::RollbackStartAudio(int32 InFrame)
{
	ManageAudio();

	for (int i = 0; i < CommonAudioChannelCount; i++)
	{
		if (BattleState.CommonAudioChannels[i].Finished) continue;
		if (BattleState.CommonAudioChannels[i].SoundWave == AudioManager->CommonAudioPlayers[i]->GetSound()) continue;

		AudioManager->CommonAudioPlayers[i]->Stop();
		AudioManager->CommonAudioPlayers[i]->SetSound(BattleState.CommonAudioChannels[i].SoundWave);
		const float CurrentAudioTime = static_cast<float>(InFrame - BattleState.CommonAudioChannels[i].StartingFrame) /
			60.f;
		if (BattleState.CommonAudioChannels[i].MaxDuration > CurrentAudioTime)
			AudioManager->CommonAudioPlayers[i]->Play(CurrentAudioTime);
	}
	for (int i = 0; i < CharaAudioChannelCount; i++)
	{
		if (BattleState.CharaAudioChannels[i].Finished) continue;
		if (BattleState.CharaAudioChannels[i].SoundWave == AudioManager->CharaAudioPlayers[i]->GetSound()) continue;

		AudioManager->CharaAudioPlayers[i]->Stop();
		AudioManager->CharaAudioPlayers[i]->SetSound(BattleState.CharaAudioChannels[i].SoundWave);
		const float CurrentAudioTime = static_cast<float>(InFrame - BattleState.CharaAudioChannels[i].StartingFrame) /
			60.f;
		if (BattleState.CharaAudioChannels[i].MaxDuration > CurrentAudioTime)
			AudioManager->CharaAudioPlayers[i]->Play(CurrentAudioTime);
	}
	for (int i = 0; i < CharaVoiceChannelCount; i++)
	{
		if (BattleState.CharaVoiceChannels[i].Finished) continue;
		if (BattleState.CharaVoiceChannels[i].SoundWave == AudioManager->CharaVoicePlayers[i]->GetSound()) continue;

		AudioManager->CharaVoicePlayers[i]->Stop();
		AudioManager->CharaVoicePlayers[i]->SetSound(BattleState.CharaVoiceChannels[i].SoundWave);
		const float CurrentAudioTime = static_cast<float>(InFrame - BattleState.CharaVoiceChannels[i].StartingFrame) /
			60.f;
		if (BattleState.CharaVoiceChannels[i].MaxDuration > CurrentAudioTime)
			AudioManager->CharaVoicePlayers[i]->Play(CurrentAudioTime);
	}
	if (!BattleState.AnnouncerVoiceChannel.Finished && BattleState.AnnouncerVoiceChannel.SoundWave != AudioManager->
		AnnouncerVoicePlayer->GetSound())
	{
		AudioManager->AnnouncerVoicePlayer->Stop();
		AudioManager->AnnouncerVoicePlayer->SetSound(BattleState.AnnouncerVoiceChannel.SoundWave);
		const float CurrentAudioTime = static_cast<float>(InFrame - BattleState.AnnouncerVoiceChannel.StartingFrame) /
			60.f;
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
	RollbackData[BackupFrame] = FRollbackData();
	RollbackData[BackupFrame].BattleStateBuffer.AddUninitialized(SizeOfBattleState);
	FMemory::Memcpy(RollbackData[BackupFrame].BattleStateBuffer.GetData(), &BattleState.BattleStateSync, SizeOfBattleState);
	RollbackData[BackupFrame].BattleStateData = SaveForRollback();
	for (int i = 0; i < BattleExtensions.Num(); i++)
	{
		RollbackData[BackupFrame].ExtensionData.Add(BattleExtensions[i]->SaveForRollback());
	}
	if (BattleExtensions.Num() == 0)
	{
		RollbackData[BackupFrame].ExtensionData.Add(TArray<uint8>{1});
	}
	for (int i = 0; i < MaxBattleObjects; i++)
	{
		if (Objects[i]->IsActive)
		{
			RollbackData[BackupFrame].ObjBuffer.AddDefaulted();
			RollbackData[BackupFrame].ObjBuffer.Last().AddUninitialized(SizeOfBattleObject);
			Objects[i]->SaveForRollback(RollbackData[BackupFrame].ObjBuffer[i].GetData());
			RollbackData[BackupFrame].StateData.Add(Objects[i]->ObjectState->SaveForRollback());
			RollbackData[BackupFrame].ObjActive.AddDefaulted();
			RollbackData[BackupFrame].ObjActive[i] = true;
		}
		else
		{
			RollbackData[BackupFrame].ObjBuffer.AddDefaulted();
			RollbackData[BackupFrame].ObjActive.AddDefaulted();
			RollbackData[BackupFrame].ObjActive[i] = false;
			RollbackData[BackupFrame].StateData.Add(TArray<uint8>{1});
		}
	}
	for (int i = 0; i < Players.Num(); i++)
	{
		RollbackData[BackupFrame].ObjBuffer.AddDefaulted();
		RollbackData[BackupFrame].ObjBuffer.Last().AddUninitialized(SizeOfBattleObject);
		Players[i]->SaveForRollback(RollbackData[BackupFrame].ObjBuffer[i + MaxBattleObjects].GetData());
		if (Players[i]->PlayerFlags & PLF_IsOnScreen)
		{
			RollbackData[BackupFrame].StateData.Add(Players[i]->PrimaryStateMachine.CurrentState->SaveForRollback());
		}
		else
		{
			RollbackData[BackupFrame].StateData.Add(TArray<uint8>{1});
		}
		RollbackData[BackupFrame].CharBuffer.AddDefaulted();
		RollbackData[BackupFrame].CharBuffer.Last().AddUninitialized(SizeOfPlayerObject);
		Players[i]->SaveForRollbackPlayer(RollbackData[BackupFrame].CharBuffer[i].GetData());
		RollbackData[BackupFrame].PlayerData.Add(Players[i]->SaveForRollbackBP());
	}

	RollbackData[BackupFrame].WidgetAnimationData.Add(BattleHudActor->TopWidget->SaveForRollback());
	RollbackData[BackupFrame].WidgetAnimationData.Add(BattleHudActor->BottomWidget->SaveForRollback());
	
	*InChecksum = CreateChecksum();
}

void ANightSkyGameState::LoadGameState()
{
	const int CurrentRollbackFrame = LocalFrame % MaxRollbackFrames;
	const int CurrentFrame = BattleState.FrameNumber;
	FMemory::Memcpy(&BattleState.BattleStateSync, RollbackData[CurrentRollbackFrame].BattleStateBuffer.GetData(), SizeOfBattleState);
	LoadForRollback(RollbackData[CurrentRollbackFrame].BattleStateData);
	for (int i = 0; i < BattleExtensions.Num(); i++)
	{
		BattleExtensions[i]->LoadForRollback(RollbackData[CurrentRollbackFrame].ExtensionData[i]);
	}
	for (int i = 0; i < MaxBattleObjects; i++)
	{
		if (RollbackData[CurrentRollbackFrame].ObjActive[i])
		{
			Objects[i]->LoadForRollback(RollbackData[CurrentRollbackFrame].ObjBuffer[i].GetData());
			Objects[i]->ObjectState->LoadForRollback(RollbackData[CurrentRollbackFrame].StateData[i]);
		}
		else
		{
			if (Objects[i]->IsActive)
				Objects[i]->ResetObject();
		}
	}
	for (int i = 0; i < Players.Num(); i++)
	{
		Players[i]->LoadForRollback(RollbackData[CurrentRollbackFrame].ObjBuffer[i + MaxBattleObjects].GetData());
		if (Players[i]->PlayerFlags & PLF_IsOnScreen)
		{
			Players[i]->PrimaryStateMachine.CurrentState->LoadForRollback(
				RollbackData[CurrentRollbackFrame].StateData[i + MaxBattleObjects]);
		}
		Players[i]->LoadForRollbackPlayer(RollbackData[CurrentRollbackFrame].CharBuffer[i].GetData());
		Players[i]->LoadForRollbackBP(RollbackData[CurrentRollbackFrame].PlayerData[i]);
	}
	SortObjects();
	ParticleManager->RollbackParticles(CurrentFrame - BattleState.FrameNumber);

	BattleHudActor->TopWidget->LoadForRollback(RollbackData[CurrentRollbackFrame].WidgetAnimationData[0]);
	BattleHudActor->BottomWidget->LoadForRollback(RollbackData[CurrentRollbackFrame].WidgetAnimationData[1]);

	BattleHudActor->TopWidget->RollbackAnimations();
	BattleHudActor->BottomWidget->RollbackAnimations();
	
	if (!FighterRunner->IsA(AFighterSynctestRunner::StaticClass()))
		GameInstance->RollbackReplay(CurrentFrame - BattleState.FrameNumber);
}

TArray<uint8> ANightSkyGameState::SaveForRollback()
{
	TArray<uint8> SaveData;
	FObjectWriter Writer(SaveData);
	Writer.ArIsSaveGame = true;
	GetClass()->SerializeBin(Writer, this);
	return SaveData;
}

void ANightSkyGameState::LoadForRollback(const TArray<uint8>& InBytes)
{
	FObjectReader Reader(InBytes);
	Reader.ArIsSaveGame = true;
	GetClass()->SerializeBin(Reader, this);
}

void ANightSkyGameState::EndMatch()
{
	EndMatch_BP();
	BattleState.BattlePhase = EBattlePhase::EndScreen;
}
