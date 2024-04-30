// Fill out your copyright notice in the Description page of Project Settings.


#include "AudioManager.h"

#include "Components/AudioComponent.h"


// Sets default values
AAudioManager::AAudioManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set audio components for common audio
	for (int i = 0; i < CommonAudioChannelCount; i++)
	{
		FString Name = "CommonAudioPlayer";
		Name.AppendInt(i);
		CommonAudioPlayers[i] = CreateDefaultSubobject<UAudioComponent>(FName(Name));
		CommonAudioPlayers[i]->AutoAttachParent = RootComponent;
	}
	// Set audio components for character sounds
	for (int i = 0; i < CharaAudioChannelCount; i++)
	{
		FString Name = "CharaAudioPlayer";
		Name.AppendInt(i);
		CharaAudioPlayers[i] = CreateDefaultSubobject<UAudioComponent>(FName(Name));
		CharaAudioPlayers[i]->AutoAttachParent = RootComponent;
	}
	// Set audio components for character voices
	for (int i = 0; i < CharaVoiceChannelCount; i++)
	{
		FString Name = "CharaVoicePlayer";
		Name.AppendInt(i);
		CharaVoicePlayers[i] = CreateDefaultSubobject<UAudioComponent>(FName(Name));
		CharaVoicePlayers[i]->AutoAttachParent = RootComponent;
	}
	// Set audio component for announcer voice
	AnnouncerVoicePlayer = CreateDefaultSubobject<UAudioComponent>(TEXT("AnnouncerVoicePlayer"));
	AnnouncerVoicePlayer->bAutoActivate = false;
	AnnouncerVoicePlayer->AutoAttachParent = RootComponent;
	// Set audio component for battle music
	BattleMusicPlayer = CreateDefaultSubobject<UAudioComponent>(TEXT("BattleMusicPlayer"));
	BattleMusicPlayer->bAutoActivate = false;
	BattleMusicPlayer->AutoAttachParent = RootComponent;
}

// Called when the game starts or when spawned
void AAudioManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAudioManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAudioManager::PauseAllAudio()
{
	for (const auto Player : CommonAudioPlayers)
	{
		Player->Stop();
	}
	for (const auto Player : CharaAudioPlayers)
	{
		Player->Stop();
	}
	for (const auto Player : CharaVoicePlayers)
	{
		Player->Stop();
	}
	AnnouncerVoicePlayer->Stop();
	// Stop Battle Music when pausing all audio
	StopBattleMusic();
}

// Function to play battle music
void AAudioManager::PlayBattleMusic()
{
	if (BattleMusicTrack)
	{
		BattleMusicPlayer->SetSound(BattleMusicTrack);
		BattleMusicPlayer->Play();
	}
}

// Stops battle music
void AAudioManager::StopBattleMusic()
{
	BattleMusicPlayer->Stop();
}