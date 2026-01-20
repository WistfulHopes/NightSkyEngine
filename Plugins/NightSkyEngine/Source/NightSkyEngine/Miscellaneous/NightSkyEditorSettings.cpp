// Fill out your copyright notice in the Description page of Project Settings.


#include "NightSkyEditorSettings.h"

UNightSkyEditorSettings::UNightSkyEditorSettings(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	CategoryName = "Plugins";
	SectionName = "Night Sky Engine";
}

UNightSkyEditorSettings* UNightSkyEditorSettings::Get()
{
	return GetMutableDefault<UNightSkyEditorSettings>();
}

const UNightSkyEditorSettings* UNightSkyEditorSettings::GetConst()
{
	return GetDefault<UNightSkyEditorSettings>();
}
