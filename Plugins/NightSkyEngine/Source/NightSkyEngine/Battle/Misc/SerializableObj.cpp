// Fill out your copyright notice in the Description page of Project Settings.


#include "SerializableObj.h"

#include "NightSkyBlueprintFunctionLibrary.h"
#include "Serialization/ObjectReader.h"
#include "Serialization/ObjectWriter.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(SerializableObj)

TArray<uint8> USerializableObj::SaveForRollback()
{
	TArray<uint8> SaveData;
	UNightSkyBlueprintFunctionLibrary::SerializeBin(this, SaveData);
	return SaveData;
}

void USerializableObj::LoadForRollback(const TArray<uint8>& InBytes)
{
	UNightSkyBlueprintFunctionLibrary::DeserializeBin(this, InBytes);
}

void USerializableObj::ResetToCDO()
{
	const auto CDO = Cast<USerializableObj>(GetClass()->GetDefaultObject());
	LoadForRollback(CDO->SaveForRollback());
}
