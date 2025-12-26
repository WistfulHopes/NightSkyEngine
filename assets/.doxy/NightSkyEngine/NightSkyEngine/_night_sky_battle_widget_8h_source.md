

# File NightSkyBattleWidget.h

[**File List**](files.md) **>** [**NightSkyEngine**](dir_01309b4faf1ec48651014f612e2b32bb.md) **>** [**Source**](dir_d32ee28216ed342fa25c01ae9dcd9cc4.md) **>** [**NightSkyEngine**](dir_a12a4fa09c295aab9e164f44221961f1.md) **>** [**UI**](dir_a40c408bd590fbad9d640bb5832ac49f.md) **>** [**NightSkyBattleWidget.h**](_night_sky_battle_widget_8h.md)

[Go to the documentation of this file](_night_sky_battle_widget_8h.md)


```C++
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
    void PlayFadeAnim();
    
    UFUNCTION(BlueprintImplementableEvent)
    void PlayFadeOutAnim();

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
    void PlayRoundInitAnim();

    UFUNCTION(BlueprintImplementableEvent)
    void PlayRoundWinAnim(bool bIsP1);

    UFUNCTION(BlueprintImplementableEvent)
    void PlayMatchWinAnim(bool bIsP1);

    UFUNCTION(BlueprintImplementableEvent)
    void PlayComboCounterAnim();

    void PlayStandardAnimations();
    void SetAnimationRollbackData();
    void RollbackAnimations();

    TArray<uint8> SaveForRollback();
    void LoadForRollback(const TArray<uint8>& InBytes);
};
```


