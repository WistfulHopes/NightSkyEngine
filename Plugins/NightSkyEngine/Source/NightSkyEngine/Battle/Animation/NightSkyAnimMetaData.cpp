// Fill out your copyright notice in the Description page of Project Settings.


#include "NightSkyAnimMetaData.h"

#include "NightSkyAnimSequenceUserData.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(NightSkyAnimMetaData)

UNightSkyAnimMetaData::UNightSkyAnimMetaData()
{
	const auto AnimSequence = Cast<UAnimSequence>(GetOuter());

	if (!AnimSequence) return;
	if (IsValid(AnimSequence->GetAssetUserData<UNightSkyAnimSequenceUserData>())) return;

	AnimSequence->AddAssetUserDataOfClass(UNightSkyAnimSequenceUserData::StaticClass());
	UserData = static_cast<UNightSkyAnimSequenceUserData*>(AnimSequence->GetAssetUserDataOfClass(
		UNightSkyAnimSequenceUserData::StaticClass()));
}
