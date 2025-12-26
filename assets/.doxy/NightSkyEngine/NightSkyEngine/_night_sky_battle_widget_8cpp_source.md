

# File NightSkyBattleWidget.cpp

[**File List**](files.md) **>** [**NightSkyEngine**](dir_01309b4faf1ec48651014f612e2b32bb.md) **>** [**Source**](dir_d32ee28216ed342fa25c01ae9dcd9cc4.md) **>** [**NightSkyEngine**](dir_a12a4fa09c295aab9e164f44221961f1.md) **>** [**UI**](dir_a40c408bd590fbad9d640bb5832ac49f.md) **>** [**NightSkyBattleWidget.cpp**](_night_sky_battle_widget_8cpp.md)

[Go to the documentation of this file](_night_sky_battle_widget_8cpp.md)


```C++
// Fill out your copyright notice in the Description page of Project Settings.


#include "NightSkyBattleWidget.h"

#include "Serialization/ObjectReader.h"
#include "Serialization/ObjectWriter.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(NightSkyBattleWidget)

void UNightSkyBattleWidget::PlayStandardAnimations()
{
    PlayHealthAnim();
    PlayRecoverableHealthAnim();
    PlayTimerAnim();
    PlayMeterAnim();
    PlayGaugeAnim();
    PlayComboCounterAnim();
}

void UNightSkyBattleWidget::SetAnimationRollbackData()
{
    for (auto& [Anim, Time, bPlaying] : WidgetAnimationRollback)
    {
        if (IsAnimationPlaying(Anim))
        {
            bPlaying = true;
            Time = GetAnimationCurrentTime(Anim);
        }
    }
}

void UNightSkyBattleWidget::RollbackAnimations()
{
    for (const auto& [Anim, Time, bPlaying] : WidgetAnimationRollback)
    {
        if (bPlaying)
            PlayAnimation(Anim, Time);
        else
            SetAnimationCurrentTime(Anim, Time);
    }
}

TArray<uint8> UNightSkyBattleWidget::SaveForRollback()
{
    TArray<uint8> SaveData;
    FObjectWriter Writer(SaveData);
    Writer.ArIsSaveGame = true;
    GetClass()->SerializeBin(Writer, this);
    return SaveData;
}

void UNightSkyBattleWidget::LoadForRollback(const TArray<uint8>& InBytes)
{
    if (InBytes.Num() <= 1) return;
    FObjectReader Reader(InBytes);
    Reader.ArIsSaveGame = true;
    GetClass()->SerializeBin(Reader, this);
}
```


