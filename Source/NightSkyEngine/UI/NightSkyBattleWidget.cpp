// Fill out your copyright notice in the Description page of Project Settings.


#include "NightSkyBattleWidget.h"

void UNightSkyBattleWidget::PlayStandardAnimations()
{
	PlayHealthAnim();
	PlayRecoverableHealthAnim();
	PlayTimerAnim();
	PlayMeterAnim();
	PlayGaugeAnim();
	PlayComboCounterAnim();
}

void UNightSkyBattleWidget::RollbackAnimations()
{
	for (const auto RollbackAnim : WidgetAnimationRollback)
	{
		if (RollbackAnim.bPlaying)
			PlayAnimation(RollbackAnim.Anim, RollbackAnim.Time);
		else
			SetAnimationCurrentTime(RollbackAnim.Anim, RollbackAnim.Time);
	}
}
