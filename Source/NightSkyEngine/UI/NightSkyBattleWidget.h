// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NightSkyBattleWidget.generated.h"

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
};
