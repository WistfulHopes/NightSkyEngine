// Fill out your copyright notice in the Description page of Project Settings.


#include "SerializableObj.h"

#include "Serialization/ObjectReader.h"
#include "Serialization/ObjectWriter.h"

TArray<uint8> USerializableObj::SaveForRollback()
{
	TArray<uint8> SaveData;
	FObjectWriter Writer(SaveData);
	Writer.ArIsSaveGame = true;
	GetClass()->SerializeBin(Writer, this);
	return SaveData;
}

void USerializableObj::LoadForRollback(const TArray<uint8>& InBytes)
{
	FObjectReader Reader(InBytes);
	Reader.ArIsSaveGame = true;
	GetClass()->SerializeBin(Reader, this);
}

void USerializableObj::ResetToCDO()
{
	const auto CDO = Cast<USerializableObj>(GetClass()->GetDefaultObject());
	LoadForRollback(CDO->SaveForRollback());
}
