// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AudioManager.generated.h"

constexpr int CommonAudioChannelCount = 32;
constexpr int CharaAudioChannelCount = 32;
constexpr int CharaVoiceChannelCount = 6;

UCLASS()
class NIGHTSKYENGINE_API AAudioManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAudioManager();
	// Component for common audio
	UPROPERTY()
	UAudioComponent* CommonAudioPlayers[CommonAudioChannelCount];
	// Component for character audio
	UPROPERTY()
	UAudioComponent* CharaAudioPlayers[CharaAudioChannelCount];
	// Component for character voice
	UPROPERTY()
	UAudioComponent* CharaVoicePlayers[CharaVoiceChannelCount];
	// Component for announcer voice
	UPROPERTY()
	UAudioComponent* AnnouncerVoicePlayer;
	// Component for Battle Music
	UPROPERTY()
	UAudioComponent* BattleMusicPlayer;
	// Component for Battle Music Track
	UPROPERTY()
	USoundBase* BattleMusicTrack;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void PauseAllAudio();
	void PlayBattleMusic();
	void StopBattleMusic();
};
