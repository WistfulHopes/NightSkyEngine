// Fill out your copyright notice in the Description page of Project Settings.


#include "NightSkyWTGameState.h"

#include "Camera/CameraActor.h"
#include "NightSkyEngine/Battle/Actors/ParticleManager.h"
#include "NightSkyEngine/Battle/Actors/FighterRunners/FighterLocalRunner.h"
#include "NightSkyEngine/Miscellaneous/NightSkyGameInstance.h"
#include "CineCameraActor.h"
#include "Camera/CameraComponent.h"
#include "LevelSequenceActor.h"
#include "NightSkyEngine/Data/BattleExtensionData.h"

// Sets default values
ANightSkyWTGameState::ANightSkyWTGameState()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BattleSceneTransform = FTransform();
	bIsBattling = false;
	bIsMatchEnd = false;
}

// Called when the game starts or when spawned
void ANightSkyWTGameState::BeginPlay()
{
	AActor::BeginPlay();

	FActorSpawnParameters SpawnParameters;
	ParticleManager = GetWorld()->SpawnActor<AParticleManager>();
	AudioManager = GetWorld()->SpawnActor<AAudioManager>();
	GameInstance = Cast<UNightSkyGameInstance>(GetGameInstance());
	CameraActor = GetWorld()->SpawnActor<ACameraActor>(ACameraActor::StaticClass());
	CameraActor->GetCameraComponent()->SetFieldOfView(54);
	SequenceCameraActor = GetWorld()->SpawnActor<ACineCameraActor>(ACineCameraActor::StaticClass());
	SequenceActor = GetWorld()->SpawnActor<ALevelSequenceActor>(ALevelSequenceActor::StaticClass());
}

void ANightSkyWTGameState::Init(APlayerObject* P1, APlayerObject* P2)
{
	bIsBattling = true;

	if (IsValid(BattleExtensionData))
	{
		for (auto Extension : BattleExtensionData->ExtensionArray)
		{
			BattleExtensions.Add(NewObject<UBattleExtension>(this, Extension));
			BattleExtensions.Last()->Parent = this;
			BattleExtensionNames.Add(BattleExtensions.Last()->Name);
		}
	}

	{
		Players.Add(P1);
		P1->SetActorTransform(BattleSceneTransform);
		P1->PlayerFlags |= PLF_IsOnScreen;
		SortedObjects.Add(P1);
		P1->InitPlayer();
		P1->GameState = this;
	}
	{
		Players.Add(P2);
		P2->SetActorTransform(BattleSceneTransform);
		P2->PlayerFlags |= PLF_IsOnScreen;
		SortedObjects.Add(P2);
		P2->InitPlayer();
		P2->GameState = this;
	}

	for (int i = 0; i < MaxBattleObjects; i++)
	{
		Objects.Add(GetWorld()->SpawnActor<ABattleObject>(ABattleObject::StaticClass(), BattleSceneTransform));
		Objects[i]->GameState = this;
		SortedObjects.Add(Objects.Last());
	}
	
	const FVector NewCameraLocation = BattleSceneTransform.GetRotation().RotateVector(FVector(0, 1080, 175)) + BattleSceneTransform.GetLocation();
	FRotator CameraRotation = BattleSceneTransform.GetRotation().Rotator();
	CameraRotation.Yaw -= 90;
	
	CameraActor->SetActorLocation(NewCameraLocation);
	CameraActor->SetActorRotation(CameraRotation);
	SequenceCameraActor->SetActorLocation(NewCameraLocation);

	MatchInit();
	HUDInit();
}

// Called every frame
void ANightSkyWTGameState::Tick(float DeltaTime)
{
	AActor::Tick(DeltaTime);
	
	if (bIsBattling && IsValid(FighterRunner))
		FighterRunner->Update(DeltaTime);

	if (bIsMatchEnd && BattleState.SuperFreezeCaller == nullptr)
	{
		bIsBattling = false;
		bIsMatchEnd = false;
		Objects.Empty();
		Players.Empty();
		SortedObjects.Empty();
		OnBattleEndDelegate.Broadcast();
	}
}