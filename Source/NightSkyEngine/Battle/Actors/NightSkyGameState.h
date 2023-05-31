// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

USTRUCT(BlueprintType)
struct FBattleState
{
	GENERATED_BODY()

	char BattleStateSync;
	int FrameNumber;
	int TimeUntilRoundStart;
	int CurrentScreenPos = 0;
	UPROPERTY(BlueprintReadOnly)
	int RoundTimer = 0;
	bool PauseTimer;
	bool PauseParticles;
	int Meter[2] { 0 , 0 };
	int MaxMeter[2] { 10000 , 10000 };
	int P1RoundsWon;
	int P2RoundsWon;
	int RoundCount = 0;
	int ActiveObjectCount;

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
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void UpdateGameState();
	void UpdateGameState(int32 Input1, int32 Input2);
	void SetScreenBounds(); //sets screen bounds
	void SetWallCollision(); //forces wall collision
	void UpdateCamera() const;
	void UpdateUI();
	void SetDrawPriorityFront(ABattleObject* InObject) const;
	int GetLocalInputs(int Index) const; //get local inputs from player controller
	void UpdateRemoteInput(int RemoteInput[], int32 InFrame); //when remote inputs are received, update inputs
	void SetOtherChecksum(uint32 RemoteChecksum, int32 InFrame);
	void ScreenPosToWorldPos(int32 X, int32 Y, int32* OutX, int32* OutY) const;
	void BattleHudVisibility(bool Visible) const;
	void SaveGameState(); //saves game state
	void LoadGameState(); //loads game state
};
