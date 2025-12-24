// Fill out your copyright notice in the Description page of Project Settings.


#include "NightSkyEditorBlueprintLibrary.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(NightSkyEditorBlueprintLibrary)

FGameplayTag UNightSkyEditorBlueprintLibrary::GetGameplayTagFromName(FName Name)
{
	return FGameplayTag::RequestGameplayTag(Name);
}
