// Fill out your copyright notice in the Description page of Project Settings.


#include "NightSkyBattleWidget.h"

#include "Serialization/ObjectReader.h"
#include "Serialization/ObjectWriter.h"

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
	FObjectReader Reader(InBytes);
	Reader.ArIsSaveGame = true;
	GetClass()->SerializeBin(Reader, this);
}
