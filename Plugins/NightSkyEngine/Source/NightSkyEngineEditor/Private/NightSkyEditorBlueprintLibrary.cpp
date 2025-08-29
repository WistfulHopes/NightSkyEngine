// Fill out your copyright notice in the Description page of Project Settings.


#include "NightSkyEditorBlueprintLibrary.h"

FGameplayTag UNightSkyEditorBlueprintLibrary::GetGameplayTagFromName(FName Name)
{
	return FGameplayTag::RequestGameplayTag(Name);
}
