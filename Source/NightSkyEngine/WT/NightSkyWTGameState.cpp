// Fill out your copyright notice in the Description page of Project Settings.


#include "NightSkyWTGameState.h"

#include "Camera/CameraActor.h"
#include "NightSkyEngine/Battle/Actors/ParticleManager.h"
#include "NightSkyEngine/Battle/Actors/FighterRunners/FighterLocalRunner.h"
#include "NightSkyEngine/Miscellaneous/NightSkyGameInstance.h"


// Sets default values
ANightSkyWTGameState::ANightSkyWTGameState()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BattleSceneTransform = FTransform();
	bIsBattling = false;
}

// Called when the game starts or when spawned
void ANightSkyWTGameState::BeginPlay()
{
	AActor::BeginPlay();

	FActorSpawnParameters SpawnParameters;
	ParticleManager = GetWorld()->SpawnActor<AParticleManager>();
	AudioManager = GetWorld()->SpawnActor<AAudioManager>();
	GameInstance = Cast<UNightSkyGameInstance>(GetGameInstance());
}

void ANightSkyWTGameState::HandleMatchWin()
{
	bIsBattling = false;
	
	OnBattleEndDelegate.Broadcast();
}

void ANightSkyWTGameState::Init(APlayerObject* P1, APlayerObject* P2)
{
	bIsBattling = true;

	BattleState = FBattleState();
	
	for (int i = 0; i < MaxRollbackFrames; i++)
	{
		MainRollbackData.Add(FRollbackData());
	}

	for (int i = 0 ; i < MaxPlayerObjects; i++)
	{
		if (i == 0 || i == 3)
		{
			if (i == 0)
				Players[i] = P1;
			else
				Players[i] = P2;
			Players[i]->SetActorTransform(BattleSceneTransform);
			Players[i]->PlayerFlags |= PLF_IsOnScreen;
		}
		else
			Players[i] = GetWorld()->SpawnActor<APlayerObject>(APlayerObject::StaticClass(), BattleSceneTransform);
		Players[i]->PlayerIndex = i * 2 >= MaxPlayerObjects;
		Players[i]->TeamIndex = i % MaxPlayerObjects / 2;
		Players[i]->InitPlayer();
		Players[i]->GameState = this;
		Players[i]->ObjNumber = MaxBattleObjects + i;
		SortedObjects[i] = Players[i];
	}
	BattleState.MainPlayer[0] = Players[0];
	BattleState.MainPlayer[1] = Players[MaxPlayerObjects / 2];

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

	FighterRunner = GetWorld()->SpawnActor<AFighterLocalRunner>(AFighterLocalRunner::StaticClass(),SpawnParameters);
	
	const FVector NewCameraLocation = BattleSceneTransform.GetRotation().RotateVector(FVector(0, 1080, 175)) + BattleSceneTransform.GetLocation();
	FRotator CameraRotation = BattleSceneTransform.GetRotation().Rotator();
	CameraRotation.Yaw -= 90;
	
	CameraActor->SetActorLocation(NewCameraLocation);
	CameraActor->SetActorRotation(CameraRotation);
	SequenceCameraActor->SetActorLocation(NewCameraLocation);
	
	SequenceCameraActor->SetActorRotation(CameraRotation);
	BattleState.RoundFormat = ERoundFormat::FirstToOne;
	BattleState.RoundTimer = 99 * 60;

	RoundInit();
}

// Called every frame
void ANightSkyWTGameState::Tick(float DeltaTime)
{
	AActor::Tick(DeltaTime);
	
	if (bIsBattling && IsValid(FighterRunner))
		FighterRunner->Update(DeltaTime);
}