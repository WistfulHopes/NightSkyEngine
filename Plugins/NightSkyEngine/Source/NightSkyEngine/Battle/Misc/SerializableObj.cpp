// Fill out your copyright notice in the Description page of Project Settings.


#include "SerializableObj.h"

#include "NightSkyBlueprintFunctionLibrary.h"
#include "Serialization/ObjectReader.h"
#include "Serialization/ObjectWriter.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(SerializableObj)

void USerializableObj::SaveForRollback(TArray<uint8>& Data)
{
	UNightSkyBlueprintFunctionLibrary::SerializeBin(this, Data);
}

int64 USerializableObj::LoadForRollback(const TArrayView<const uint8>& InBytes)
{
	return UNightSkyBlueprintFunctionLibrary::DeserializeBin(this, MakeArrayView(InBytes));
}

void USerializableObj::ResetToCDO()
{
	const auto CDO = Cast<USerializableObj>(GetClass()->GetDefaultObject());
	TArray<uint8> Data;
	CDO->SaveForRollback(Data);
	LoadForRollback(Data);
}
