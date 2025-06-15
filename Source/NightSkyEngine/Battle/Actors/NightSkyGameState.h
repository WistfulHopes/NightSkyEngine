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

class ANightSkyBattleHudActor;

// Battle data

UENUM(BlueprintType)
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

enum EWinSide 
{
	WIN_None,
	WIN_P1,
	WIN_P2,
	WIN_Draw,
};

UENUM()
enum class EBattlePhase
{
	Intro,
	Battle,
	RoundEnd,
	MatchEnd,
	EndScreen,
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

	UPROPERTY(SaveGame)
	int TeamCount = 0;

	UPROPERTY(SaveGame)
	TArray<int32> CooldownTimer;
};

UENUM()
enum EScreenFlag 
{
	SCR_None,
	SCR_Lock = 1 << 0,
	SCR_LockXPos = 1 << 1,
	SCR_LockYPos = 1 << 2,
	SCR_LockWidth = 1 << 3,
	SCR_DisableScreenSides = 1 << 4,
};

USTRUCT(BlueprintType)
struct FScreenData 
{
	GENERATED_BODY()

	EScreenFlag Flags;
	
	UPROPERTY(EditAnywhere)
	int DefaultMaxWidth = 1689;
	UPROPERTY(EditAnywhere)
	int DefaultWidth = 1280;
	UPROPERTY(EditAnywhere)
	int DefaultScreenYTargetOffset = -100;

	int MaxZoomOutWidth = 1689;
	int ZoomOutBeginX = 1280;
	
	UPROPERTY()
	ABattleObject* TargetObjects[6]{};
	int TargetObjectCount;
	
	int ObjTop = 0;
	int ObjBottom = 0;
	int HigherObjBottom = 0;
	int ObjLeft = 0;
	int ObjRight = 0;
	int ObjLength = 0;
	int ObjHeight = 0;

	int ScreenWorldCenterX = 0;
	int ScreenWorldCenterY = 0;
	int ScreenWorldWidth = 1280;

	int TargetCenterX = 0;
	int TargetCenterY = 0;
	int TargetWidth = 1280;

	int CenterXVelocity = 0;
	int CenterYVelocity = 0;
	int WidthVelocity = 0;

	int FinalScreenX = 0;
	int FinalScreenY = 0;
	int FinalScreenWidth = 1280;

	float ScreenYZoom = 0;
	
	int TargetOffsetY = 350;
	int TargetOffsetLandYMax = 250;
	int TargetOffsetLandYAdd = 6;
	int TargetOffsetAirYMax = 180;
	int TargetOffsetAirYAdd = 3;
	int TargetOffsetAirYPos = 400;
	int TargetOffsetAirYDist = 570;

	int ScreenBoundsLeft = -640;
	int ScreenBoundsRight = 640;
	int ScreenBoundsTop = 0;

	UPROPERTY(EditAnywhere)
	int StageBoundsLeft = -3200;
	UPROPERTY(EditAnywhere)
	int StageBoundsRight = 3200;
	UPROPERTY(EditAnywhere)
	int StageBoundsTop = 5400;

	bool bStopScreenUpdate;
	bool bStopZoomCamera;
	bool bTouchingWorldSide;

	void AddTargetObj(ABattleObject* InTarget);
	void RemoveTargetObj(const ABattleObject* InTarget);
};

USTRUCT(BlueprintType)
struct FBattleState
{
	GENERATED_BODY()

	char BattleStateSync;
	
	int32 FrameNumber = 0;
	int32 TimeUntilRoundStart = 0;

	UPROPERTY(EditAnywhere)
	int32 TagCooldown = 300;
	UPROPERTY(EditAnywhere)
	int32 AssistCooldown = 180;
	
	UPROPERTY(EditAnywhere)
	int32 RoundStartPos = 297500;

	UPROPERTY(EditAnywhere)
	FScreenData ScreenData;
	
	FVector CameraPosition = FVector();
	bool bHUDVisible = true;
	
	UPROPERTY(BlueprintReadOnly)
	int32 RoundTimer = 0;
	
	bool PauseTimer = false;
	bool PauseParticles = false;
	bool IsPlayingSequence = false;
	
	FRandomManager RandomManager;
	
	int32 Meter[2] {0, 0};
	int32 MaxMeter[2] {10000, 10000};

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
	EWinSide CurrentWinSide = WIN_None;
	EBattlePhase BattlePhase = EBattlePhase::Intro;
	
	int32 ActiveObjectCount = 0;
	int32 CurrentSequenceTime = -1;
	
	FAudioChannel CommonAudioChannels[CommonAudioChannelCount];
	FAudioChannel CharaAudioChannels[CharaAudioChannelCount];
	FAudioChannel CharaVoiceChannels[CharaVoiceChannelCount];
	FAudioChannel AnnouncerVoiceChannel;
	FAudioChannel MusicChannel;

	char BattleStateSyncEnd;

	UPROPERTY(SaveGame)
	FTeamData TeamData[2];
	
	UPROPERTY(SaveGame)
	TArray<int32> GaugeP1;
	UPROPERTY(SaveGame)
	TArray<int32> GaugeP2;
	UPROPERTY(EditAnywhere, SaveGame)
	TArray<int32> MaxGauge;
	
	UPROPERTY(BlueprintReadOnly)
	ERoundFormat RoundFormat = ERoundFormat::FirstToTwo;
};

constexpr size_t SizeOfBattleState = offsetof(FBattleState, BattleStateSyncEnd) - offsetof(
	FBattleState, BattleStateSync);

USTRUCT()
struct FRollbackData
{
	GENERATED_BODY()
	
	UPROPERTY()
	TArray<bool> ObjActive;
	TArray<TArray<uint8>> ObjBuffer;
	TArray<TArray<uint8>> CharBuffer;
	TArray<uint8> BattleStateBuffer;
	TArray<TArray<uint8>> PlayerData;
	TArray<uint8> BattleStateData;
	TArray<TArray<uint8>> StateData;
	TArray<TArray<uint8>> ExtensionData;
	TArray<TArray<uint8>> WidgetAnimationData;
	UPROPERTY()
	uint64 SizeOfBPRollbackData;
	
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

public:
	// Sets default values for this actor's properties
	ANightSkyGameState();
	
	UPROPERTY(EditAnywhere)
	int MaxBattleObjects = 400;
	UPROPERTY()
	TArray<ABattleObject*> Objects {};
	UPROPERTY()
	TArray<APlayerObject*> Players {};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, SaveGame)
	FBattleState BattleState = FBattleState();
	
	UPROPERTY()
	TArray<ABattleObject*> SortedObjects {};
	
	UPROPERTY(BlueprintReadWrite)
	FTransform BattleSceneTransform;
	
	UPROPERTY()
	TArray<UBattleExtension*> BattleExtensions = {};
	TArray<FGameplayTag> BattleExtensionNames = {};

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UBattleExtensionData* BattleExtensionData = {};

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

	TArray<FRollbackData> RollbackData = {};
	
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
	bool HandleMatchWin();
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

	void SetScreenCorners();
	void UpdateScreen();
	void SetScreenBounds() const; //forces wall collision
	void StartSuperFreeze(int32 Duration, int32 SelfDuration, ABattleObject* CallingObject);
	void ScreenPosToWorldPos(int32 X, int32 Y, int32* OutX, int32* OutY) const;
	ABattleObject* AddBattleObject(const UState* InState, int PosX, int PosY, EObjDir Dir, int32 ObjectStateIndex, bool bIsCommonState, APlayerObject* Parent) const;
	void SetDrawPriorityFront(ABattleObject* InObject) const;
	APlayerObject* SwitchMainPlayer(APlayerObject* InPlayer, int TeamIndex);
	APlayerObject* CallAssist(const bool IsP1, int AssistIndex, const FGameplayTag AssistName);
	bool CanTag(const APlayerObject* InPlayer, int TeamIndex) const;
	
	void SaveGameState(int32* InChecksum); //saves game state
	void LoadGameState(); //loads game state
	
	TArray<uint8> SaveForRollback();
	void LoadForRollback(const TArray<uint8>& InBytes);

	void UpdateCamera();
	void PlayLevelSequence(APlayerObject* Target, APlayerObject* Enemy, ULevelSequence* Sequence);
	void CameraShake(const TSubclassOf<UCameraShakeBase>& Pattern, float Scale) const;

	void HUDInit() const;
	void UpdateHUD() const;
	void BattleHudVisibility(bool Visible);
	
	void PlayCommonAudio(USoundBase* InSoundWave, float MaxDuration);
	void PlayCharaAudio(USoundBase* InSoundWave, float MaxDuration);
	void PlayVoiceLine(USoundBase* InSoundWave, float MaxDuration, int Player);
	void PlayAnnouncerVoice(USoundBase* InSoundWave, float MaxDuration);
	void PlayMusic(const FGameplayTag Name);
	void PlayMusic(USoundBase* InSoundWave, float MaxDuration);
	void ManageAudio();
	void RollbackStartAudio(int32 InFrame);

	int GetLocalInputs(int Index) const; //get local inputs from player controller
	void UpdateRemoteInput(int RemoteInput[], int32 InFrame); //when remote inputs are received, update inputs
	void SetOtherChecksum(uint32 RemoteChecksum, int32 InFrame);

	UFUNCTION(BlueprintCallable)
	TArray<APlayerObject*> GetTeam(bool IsP1) const;
	UFUNCTION(BlueprintCallable)
	APlayerObject* GetMainPlayer(bool IsP1) const;
	UFUNCTION(BlueprintCallable)
	void CallBattleExtension(FGameplayTag Name);
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
