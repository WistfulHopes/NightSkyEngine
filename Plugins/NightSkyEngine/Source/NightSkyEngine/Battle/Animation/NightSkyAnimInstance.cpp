// Fill out your copyright notice in the Description page of Project Settings.


#include "NightSkyAnimInstance.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(NightSkyAnimInstance)

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
	if (!Asset) return;
	RootMontage = PlaySlotAnimationAsDynamicMontage_WithBlendArgs(Asset, "Root", BlendIn, BlendOut, 1, 1, -1,
	                                                              CurrentAnimTime);
	Montage_SetNextSection("Default", "Default", RootMontage);
}
