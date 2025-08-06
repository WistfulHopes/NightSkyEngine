// Fill out your copyright notice in the Description page of Project Settings.


#include "AudioManager.h"

#include "Components/AudioComponent.h"


// Sets default values
AAudioManager::AAudioManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(FName("RootComponent"));
	for (int i = 0; i < CommonAudioChannelCount; i++)
	{
		FString Name = "CommonAudioPlayer";
		Name.AppendInt(i);
		CommonAudioPlayers[i] = CreateDefaultSubobject<UAudioComponent>(FName(Name));
		CommonAudioPlayers[i]->AutoAttachParent = RootComponent;
	}
	for (int i = 0; i < CharaAudioChannelCount; i++)
	{
		FString Name = "CharaAudioPlayer";
		Name.AppendInt(i);
		CharaAudioPlayers[i] = CreateDefaultSubobject<UAudioComponent>(FName(Name));
		CharaAudioPlayers[i]->AutoAttachParent = RootComponent;
	}
	for (int i = 0; i < CharaVoiceChannelCount; i++)
	{
		FString Name = "CharaVoicePlayer";
		Name.AppendInt(i);
		CharaVoicePlayers[i] = CreateDefaultSubobject<UAudioComponent>(FName(Name));
		CharaVoicePlayers[i]->AutoAttachParent = RootComponent;
	}
	AnnouncerVoicePlayer = CreateDefaultSubobject<UAudioComponent>(TEXT("AnnouncerVoicePlayer"));
	AnnouncerVoicePlayer->bAutoActivate = false;
	AnnouncerVoicePlayer->AutoAttachParent = RootComponent;
	MusicPlayer = CreateDefaultSubobject<UAudioComponent>(TEXT("MusicPlayer"));
	MusicPlayer->bAutoActivate = true;
	MusicPlayer->AutoAttachParent = RootComponent;
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
}