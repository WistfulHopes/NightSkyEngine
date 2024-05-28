// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AudioManager.h"
#include "PlayerObject.h"
#include "GameFramework/GameStateBase.h"
#include "include/ggponet.h"
#include "NightSkyEngine/Battle/RandomManager.h"
#include "NightSkyGameState.generated.h"

class UBattleExtensionData;
class UBattleExtension;
constexpr int32 MaxRollbackFrames = 1;
constexpr float OneFrame = 0.0166666666;
constexpr int32 MaxBattleObjects = 400;
constexpr int32 MaxPlayerObjects = 6;
constexpr int32 GaugeCount = 5;

class ANightSkyBattleHudActor;

// Battle data

UENUM()
enum class ERoundFormat : uint8
{
	FirstToOne,
	FirstToTwo,
	FirstToThree,
	FirstToFour,
	FirstToFive,
	TwoVsTwo,
	ThreeVsThree,
	TwoVsTwoKOF,
	ThreeVsThreeKOF,
};

enum EIntroSide
{
	INT_P1,
	INT_P2,
	INT_None,
};

USTRUCT()
struct FAudioChannel
{
	GENERATED_BODY()

	UPROPERTY()
	USoundBase* SoundWave;
	int StartingFrame;
	float MaxDuration = 1.0f;
	bool Finished = true;
};

USTRUCT()
struct FTeamData
{
	GENERATED_BODY()

	int32 CooldownTimer[MaxPlayerObjects / 2];
};

USTRUCT(BlueprintType)
struct FBattleState
{
	GENERATED_BODY()

	char BattleStateSync;

	FTeamData TeamData[2];
	
	int32 FrameNumber = 0;
	int32 TimeUntilRoundStart = 0;

	UPROPERTY(EditAnywhere)
	int32 TagCooldown = 300;
	UPROPERTY(EditAnywhere)
	int32 AssistCooldown = 180;
	
	UPROPERTY(EditAnywhere)
	int32 RoundStartPos = 297500;
	int32 CurrentScreenPos = 0;
	
	UPROPERTY(EditAnywhere)
	int32 ScreenBounds = 840000;
	UPROPERTY(EditAnywhere)
	int32 StageBounds = 1680000;
	
	FVector CameraPosition = FVector();
	FVector PrevCameraPosition = FVector();
	bool bHUDVisible = true;
	
	UPROPERTY(BlueprintReadOnly)
	int32 RoundTimer = 0;
	
	bool PauseTimer = false;
	bool PauseParticles = false;
	bool IsPlayingSequence = false;
	
	FRandomManager RandomManager;
	
	int32 Meter[2] {0, 0};
	int32 MaxMeter[2] {10000, 10000};

	int32 Gauge[2][GaugeCount];
	UPROPERTY(EditAnywhere)
	int32 MaxGauge[GaugeCount];

	int32 SuperFreezeDuration = 0;
	int32 SuperFreezeSelfDuration = 0;
	
	UPROPERTY()
	ABattleObject* SuperFreezeCaller = nullptr;
	UPROPERTY()
	APlayerObject* MainPlayer[2];
	
	int32 P1RoundsWon = 0;
	int32 P2RoundsWon = 0;
	int32 RoundCount = 0;

	EIntroSide CurrentIntroSide = INT_None;
	
	int32 ActiveObjectCount = MaxPlayerObjects;
	int32 CurrentSequenceTime = -1;
	
	FAudioChannel CommonAudioChannels[CommonAudioChannelCount];
	FAudioChannel CharaAudioChannels[CharaAudioChannelCount];
	FAudioChannel CharaVoiceChannels[CharaVoiceChannelCount];
	FAudioChannel AnnouncerVoiceChannel;
	FAudioChannel MusicChannel;

	char BattleStateSyncEnd;

	UPROPERTY(BlueprintReadOnly)
	ERoundFormat RoundFormat = ERoundFormat::FirstToTwo;
};

constexpr size_t SizeOfBattleState = offsetof(FBattleState, BattleStateSyncEnd) - offsetof(
	FBattleState, BattleStateSync);

struct FRollbackData
{
	uint8 ObjBuffer[MaxBattleObjects + MaxPlayerObjects][SizeOfBattleObject] = { { 0 } };
	bool ObjActive[MaxBattleObjects] = { false };
	uint8 CharBuffer[MaxPlayerObjects][SizeOfPlayerObject] = { { 0 } };
	uint8 BattleStateBuffer[SizeOfBattleState] = { 0 };
	uint64 SizeOfBPRollbackData;
};

struct FBPRollbackData
{
	TArray<TArray<uint8>> PlayerData;
	TArray<TArray<uint8>> StateData;
	TArray<TArray<uint8>> ExtensionData;

	void Serialize(FArchive& Ar);
};

// Network

USTRUCT(BlueprintType)
struct FNetworkStats
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	int32 Ping;
	UPROPERTY(BlueprintReadOnly)
	int32 RollbackFrames;
};

// Main class

UCLASS()
class NIGHTSKYENGINE_API ANightSkyGameState : public AGameStateBase
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	ABattleObject* Objects[MaxBattleObjects] {};
	UPROPERTY()
	APlayerObject* Players[MaxPlayerObjects] {};

public:
	// Sets default values for this actor's properties
	ANightSkyGameState();
	
	UPROPERTY(BlueprintReadWrite)
	FTransform BattleSceneTransform;
	
	UPROPERTY()
	ABattleObject* SortedObjects[MaxBattleObjects + MaxPlayerObjects] {};

	UPROPERTY()
	class UNightSkyGameInstance* GameInstance = nullptr;

	UPROPERTY()
	class AParticleManager* ParticleManager = nullptr;
	UPROPERTY()
	AAudioManager* AudioManager = nullptr;

	UPROPERTY(BlueprintReadWrite)
	class ALevelSequenceActor* SequenceActor = nullptr;
	UPROPERTY(BlueprintReadWrite)
	ACameraActor* CameraActor = nullptr;
	UPROPERTY(BlueprintReadWrite)
	ACameraActor* SequenceCameraActor = nullptr;
	UPROPERTY(BlueprintReadOnly)
	APlayerObject* SequenceTarget = nullptr;
	UPROPERTY(BlueprintReadOnly)
	APlayerObject* SequenceEnemy = nullptr;
	UPROPERTY(BlueprintReadWrite)
	bool bPauseGame = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bViewCollision = false;

	UPROPERTY(BlueprintReadOnly)
	bool bIsPlayingSequence = false;

	UPROPERTY()
	class AFighterLocalRunner* FighterRunner = nullptr;;
	UPROPERTY(BlueprintReadWrite)
	ANightSkyBattleHudActor* BattleHudActor = nullptr;;

	TArray<FRollbackData> MainRollbackData = {};
	TArray<FBPRollbackData> BPRollbackData = {};

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FBattleState BattleState = FBattleState();
	
	UPROPERTY()
	TArray<UBattleExtension*> BattleExtensions = {};
	TArray<FName> BattleExtensionNames = {};

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UBattleExtensionData* BattleExtensionData = {};
	
	int32 LocalFrame = 0;
	int32 RemoteFrame = 0;

private:
	int32 LocalInputs[MaxRollbackFrames][2] = {};
	int32 RemoteInputs[MaxRollbackFrames][2] = {};
	int32 Checksum = 0;
	int32 OtherChecksum = 0;
	int32 OtherChecksumFrame = 0;
	int32 PrevOtherChecksumFrame = 0;
	FNetworkStats NetworkStats = FNetworkStats();
	bool bIsResimulating = false;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void Init();
	void PlayIntros();
	void UpdateLocalInput(); //updates local input
	void SortObjects();
	void HandlePushCollision() const; //for each active object, handle push collision
	void HandleHitCollision() const;
	void UpdateVisuals() const;
	void HandleRoundWin();
	virtual bool HandleMatchWin();
	void CollisionView() const;
	int32 CreateChecksum();
	FGGPONetworkStats GetNetworkStats() const;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void MatchInit();
	void RoundInit();
	
	void UpdateGameState();
	void UpdateGameState(int32 Input1, int32 Input2, bool bShouldResimulate);

	void SetStageBounds(); //sets screen bounds
	void SetScreenBounds() const; //forces wall collision
	void StartSuperFreeze(int32 Duration, int32 SelfDuration, ABattleObject* CallingObject);
	void ScreenPosToWorldPos(int32 X, int32 Y, int32* OutX, int32* OutY) const;
	ABattleObject* AddBattleObject(const UState* InState, int PosX, int PosY, EObjDir Dir, int32 ObjectStateIndex, bool bIsCommonState, APlayerObject* Parent) const;
	void SetDrawPriorityFront(ABattleObject* InObject) const;
	APlayerObject* SwitchMainPlayer(APlayerObject* InPlayer, int TeamIndex);
	APlayerObject* CallAssist(const bool IsP1, int AssistIndex, const FString& AssistName);
	bool CanTag(const APlayerObject* InPlayer, int TeamIndex) const;
	
	void SaveGameState(int32* InChecksum); //saves game state
	void LoadGameState(); //loads game state

	void UpdateCamera();
	void PlayLevelSequence(APlayerObject* Target, APlayerObject* Enemy, ULevelSequence* Sequence);
	void CameraShake(const TSubclassOf<UCameraShakeBase>& Pattern, float Scale) const;

	void UpdateHUD() const;
	void BattleHudVisibility(bool Visible);
	
	void PlayCommonAudio(USoundBase* InSoundWave, float MaxDuration);
	void PlayCharaAudio(USoundBase* InSoundWave, float MaxDuration);
	void PlayVoiceLine(USoundBase* InSoundWave, float MaxDuration, int Player);
	void PlayAnnouncerVoice(USoundBase* InSoundWave, float MaxDuration);
	void PlayMusic(const FString& Name);
	void PlayMusic(USoundBase* InSoundWave, float MaxDuration);
	void ManageAudio();
	void RollbackStartAudio(int32 InFrame) const;

	int GetLocalInputs(int Index) const; //get local inputs from player controller
	void UpdateRemoteInput(int RemoteInput[], int32 InFrame); //when remote inputs are received, update inputs
	void SetOtherChecksum(uint32 RemoteChecksum, int32 InFrame);

	UFUNCTION(BlueprintCallable)
	TArray<APlayerObject*> GetTeam(bool IsP1) const;
	UFUNCTION(BlueprintCallable)
	APlayerObject* GetMainPlayer(bool IsP1) const;
	UFUNCTION(BlueprintCallable)
	void CallBattleExtension(FString Name);
	UFUNCTION(BlueprintPure)
	int32 GetGauge(bool IsP1, int32 GaugeIndex) const;
	UFUNCTION(BlueprintCallable)
	void SetGauge(bool IsP1, int32 GaugeIndex, int32 Value);
	UFUNCTION(BlueprintCallable)
	void UseGauge(bool IsP1, int32 GaugeIndex, int32 Value);
	UFUNCTION(BlueprintPure)
	bool IsTagBattle() const;

	UFUNCTION(BlueprintImplementableEvent)
	void EndMatch();
};
