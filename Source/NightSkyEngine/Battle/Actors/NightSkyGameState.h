// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerObject.h"
#include "GameFramework/GameStateBase.h"
#include "NightSkyGameState.generated.h"

constexpr int32 MaxRollbackFrames = 10;
constexpr float OneFrame = 1 / 60;

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

USTRUCT(BlueprintType)
struct FBattleState
{
	GENERATED_BODY()

	char BattleStateSync;
	int FrameNumber;
	int TimeUntilRoundStart = 180;
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
	
	int ActiveObjectCount;
	uint8 ObjBuffer[406][SizeOfBattleObject] = { { 0 } };
	bool ObjActive[400] = { false };
	uint8 CharBuffer[6][SizeOfPlayerObject] = { { 0 } };
	uint8 BattleStateBuffer[SizeOfBattleState] = { 0 };
	uint32 Checksum = 0;
};

UCLASS()
class NIGHTSKYENGINE_API ANightSkyGameState : public AGameStateBase
{
	GENERATED_BODY()
	
	UPROPERTY()
	APlayerObject* Players[6];
	UPROPERTY()
	ABattleObject* Objects[400];

public:
	// Sets default values for this actor's properties
	ANightSkyGameState();
	
	UPROPERTY()
	ABattleObject* SortedObjects[406];
	
	UPROPERTY(BlueprintReadWrite)
	class ALevelSequenceActor* SequenceActor;
	UPROPERTY(BlueprintReadWrite)
	ACameraActor* CameraActor;
	UPROPERTY(BlueprintReadWrite)
	ACameraActor* SequenceCameraActor;
	UPROPERTY(BlueprintReadOnly)
	APlayerObject* SequenceTarget;
	
	UPROPERTY()
	class AFighterLocalRunner* FighterRunner;

	TArray<FRollbackData> StoredRollbackData;
	FBattleState BattleState;
	int LocalFrame;
	int RemoteFrame;

private:
	int LocalInputs[MaxRollbackFrames][2];
	int RemoteInputs[MaxRollbackFrames][2];
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
	void SetScreenBounds(); //sets screen bounds
	void SetWallCollision(); //forces wall collision

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void UpdateGameState();
	void UpdateGameState(int32 Input1, int32 Input2);
	void UpdateCamera() const;
	int GetLocalInputs(int Index) const; //get local inputs from player controller
	void UpdateRemoteInput(int RemoteInput[], int32 InFrame); //when remote inputs are received, update inputs
	void SetOtherChecksum(uint32 RemoteChecksum, int32 InFrame);
	void ScreenPosToWorldPos(int32 X, int32 Y, int32* OutX, int32* OutY) const;
	void SaveGameState(); //saves game state
	void LoadGameState(); //loads game state
};
