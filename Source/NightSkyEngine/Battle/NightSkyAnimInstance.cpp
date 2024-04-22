// Fill out your copyright notice in the Description page of Project Settings.


#include "NightSkyAnimInstance.h"

void UNightSkyAnimInstance::Montage_Advance(float DeltaSeconds)
{
	if (!RootMontage)
	{
		Super::Montage_Advance(DeltaSeconds);
		return;
	}
	
	Montage_SetPosition(RootMontage, CurrentAnimTime);
}

void UNightSkyAnimInstance::CreateRootMontage(UAnimSequenceBase* Asset, const FAlphaBlendArgs& BlendIn, const FAlphaBlendArgs& BlendOut)
{
	RootMontage = PlaySlotAnimationAsDynamicMontage_WithBlendArgs(Asset, "Root", BlendIn, BlendOut, 1, 1, -1,
	                                                              CurrentAnimTime);
	Montage_SetNextSection("Default", "Default", RootMontage);
}
