// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AudioManager.h"
#include "PlayerObject.h"
#include "GameFramework/GameStateBase.h"
#include "NightSkyGameState.generated.h"

constexpr int32 MaxRollbackFrames = 1;
constexpr float OneFrame = 0.0166666666;
constexpr int32 MaxBattleObjects = 101;
constexpr int32 MaxPlayerObjects = 6;

class ANightSkyBattleHudActor;

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

#pragma pack (push, 1)

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

USTRUCT(BlueprintType)
struct FBattleState
{
	GENERATED_BODY()

	char BattleStateSync;
	int32 FrameNumber;
	int32 TimeUntilRoundStart;
	int32 CurrentScreenPos = 0;
	UPROPERTY(BlueprintReadOnly)
	int32 RoundTimer = 0;
	bool PauseTimer;
	bool PauseParticles;
	int32 Meter[2] { 0 , 0 };
	int32 MaxMeter[2] { 10000 , 10000 };
	int32 P1RoundsWon;
	int32 P2RoundsWon;
	int32 RoundCount = 0;
	int32 ActiveObjectCount;
	int32 CurrentSequenceTime = -1;
	FAudioChannel CommonAudioChannels[CommonAudioChannelCount];
	FAudioChannel CharaAudioChannels[CharaAudioChannelCount];
	FAudioChannel CharaVoiceChannels[CharaVoiceChannelCount];
	FAudioChannel AnnouncerVoiceChannel;

	char BattleStateSyncEnd;

	UPROPERTY(BlueprintReadOnly)
	ERoundFormat RoundFormat = ERoundFormat::FirstToTwo;
};

constexpr size_t SizeOfBattleState = offsetof(FBattleState, BattleStateSyncEnd) - offsetof(FBattleState, BattleStateSync);

USTRUCT()
struct FRollbackData
{
	GENERATED_BODY()
	
	uint8 ObjBuffer[MaxBattleObjects + MaxPlayerObjects][SizeOfBattleObject] = { { 0 } };
	bool ObjActive[MaxBattleObjects] = { false };
	uint8 CharBuffer[MaxPlayerObjects][SizeOfPlayerObject] = { { 0 } };
	uint8 BattleStateBuffer[SizeOfBattleState] = { 0 };
};
#pragma pack(pop)

UCLASS()
class NIGHTSKYENGINE_API ANightSkyGameState : public AGameStateBase
{
	GENERATED_BODY()
	
	UPROPERTY()
	ABattleObject* Objects[MaxBattleObjects];
	UPROPERTY()
	APlayerObject* Players[MaxPlayerObjects];

public:
	// Sets default values for this actor's properties
	ANightSkyGameState();
	
	UPROPERTY()
	ABattleObject* SortedObjects[MaxBattleObjects + MaxPlayerObjects];
	
	UPROPERTY()
	class UNightSkyGameInstance* GameInstance;

	UPROPERTY()
	class AParticleManager* ParticleManager;
	UPROPERTY()
	AAudioManager* AudioManager;
	
	UPROPERTY(BlueprintReadWrite)
	class ALevelSequenceActor* SequenceActor;
	UPROPERTY(BlueprintReadWrite)
	ACameraActor* CameraActor;
	UPROPERTY(BlueprintReadWrite)
	ACameraActor* SequenceCameraActor;
	UPROPERTY(BlueprintReadOnly)
	APlayerObject* SequenceTarget;
	UPROPERTY(BlueprintReadWrite)
	bool bPauseGame;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bViewCollision;

	UPROPERTY(BlueprintReadOnly)
	bool bIsPlayingSequence;
	
	UPROPERTY()
	class AFighterLocalRunner* FighterRunner;
	UPROPERTY(BlueprintReadWrite)
	ANightSkyBattleHudActor* BattleHudActor;

	TArray<FRollbackData> StoredRollbackData;
	FBattleState BattleState;
	int32 LocalFrame;
	int32 RemoteFrame;
	
private:
	int32 LocalInputs[MaxRollbackFrames][2];
	int32 RemoteInputs[MaxRollbackFrames][2];
	uint32 Checksum;
	uint32 OtherChecksum;
	int32 OtherChecksumFrame;
	int32 PrevOtherChecksumFrame;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void Init();
	void RoundInit();
	void UpdateLocalInput(); //updates local input
	void SortObjects();
	void HandlePushCollision() const; //for each active object, handle push collision
	void HandleHitCollision() const;
	void HandleRoundWin();
	void HandleMatchWin() const;
	void CollisionView() const;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void UpdateGameState();
	void UpdateGameState(int32 Input1, int32 Input2);
	void SetScreenBounds(); //sets screen bounds
	void SetWallCollision(); //forces wall collision
	void StartSuperFreeze(int Duration);
	void ScreenPosToWorldPos(int32 X, int32 Y, int32* OutX, int32* OutY) const;
	ABattleObject* AddBattleObject(UState* InState, int PosX, int PosY, EObjDir Dir, APlayerObject* Parent) const;
	void SetDrawPriorityFront(ABattleObject* InObject) const;
	void SaveGameState(); //saves game state
	void LoadGameState(); //loads game state
	
	void UpdateCamera();
	void PlayLevelSequence(APlayerObject* Target, ULevelSequence* Sequence);
	void UpdateUI();
	void BattleHudVisibility(bool Visible) const;
	
	void PlayCommonAudio(USoundBase* InSoundWave, float MaxDuration);
	void PlayCharaAudio(USoundBase* InSoundWave, float MaxDuration);
	void PlayVoiceLine(USoundBase* InSoundWave, float MaxDuration, int Player);
	void ManageAudio();
	void RollbackStartAudio() const;
	
	int GetLocalInputs(int Index) const; //get local inputs from player controller
	void UpdateRemoteInput(int RemoteInput[], int32 InFrame); //when remote inputs are received, update inputs
	void SetOtherChecksum(uint32 RemoteChecksum, int32 InFrame);
};
