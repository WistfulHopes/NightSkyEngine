// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NightSkyBattleWidget.generated.h"

USTRUCT(BlueprintType)
struct FRollbackAnimation
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	UWidgetAnimation* Anim;
	
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float Time;

	UPROPERTY(BlueprintReadWrite, SaveGame)
	bool bPlaying;
};

/**
 * 
 */
UCLASS()
class NIGHTSKYENGINE_API UNightSkyBattleWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly)
	TArray<float> P1Health;
	UPROPERTY(BlueprintReadOnly)
	TArray<float> P2Health;
	UPROPERTY(BlueprintReadOnly)
	TArray<float> P1RecoverableHealth;
	UPROPERTY(BlueprintReadOnly)
	TArray<float> P2RecoverableHealth;
	UPROPERTY(BlueprintReadOnly)
	float Timer;
	UPROPERTY(BlueprintReadOnly)
	float P1Meter;
	UPROPERTY(BlueprintReadOnly)
	float P2Meter;
	UPROPERTY(BlueprintReadOnly)
	TArray<float> P1Gauge;
	UPROPERTY(BlueprintReadOnly)
	TArray<float> P2Gauge;
	UPROPERTY(BlueprintReadOnly)
	int P1RoundsWon;
	UPROPERTY(BlueprintReadOnly)
	int P2RoundsWon;
	UPROPERTY(BlueprintReadOnly)
	int P1ComboCounter;
	UPROPERTY(BlueprintReadOnly)
	int P2ComboCounter;
	UPROPERTY(BlueprintReadOnly)
	int Ping;
	UPROPERTY(BlueprintReadOnly)
	int RollbackFrames;

	UPROPERTY(BlueprintReadWrite, SaveGame)
	TArray<FRollbackAnimation> WidgetAnimationRollback;

	UFUNCTION(BlueprintImplementableEvent)
	void RegisterAnimationsForRollback();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayHealthAnim();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayRecoverableHealthAnim();
	
	UFUNCTION(BlueprintImplementableEvent)
	void PlayTimerAnim();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayMeterAnim();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayGaugeAnim();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayRoundWinAnim(bool bIsP1);

	UFUNCTION(BlueprintImplementableEvent)
	void PlayMatchWinAnim(bool bIsP1);

	UFUNCTION(BlueprintImplementableEvent)
	void PlayComboCounterAnim();

	void PlayStandardAnimations();
	void RollbackAnimations();

	TArray<uint8> SaveForRollback();
	void LoadForRollback(const TArray<uint8>& InBytes);
};
