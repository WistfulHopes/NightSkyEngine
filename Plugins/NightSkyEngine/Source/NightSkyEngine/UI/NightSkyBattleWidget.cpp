// Fill out your copyright notice in the Description page of Project Settings.


#include "NightSkyBattleWidget.h"

#include "NightSkyEngine/Battle/Misc/NightSkyBlueprintFunctionLibrary.h"

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

void UNightSkyBattleWidget::SaveForRollback(TArray<uint8>& Data)
{
	UNightSkyBlueprintFunctionLibrary::SerializeBin(this, Data);
}

uint64 UNightSkyBattleWidget::LoadForRollback(const TArrayView<const uint8>& InBytes)
{
	return UNightSkyBlueprintFunctionLibrary::DeserializeBin(this, InBytes);
}
