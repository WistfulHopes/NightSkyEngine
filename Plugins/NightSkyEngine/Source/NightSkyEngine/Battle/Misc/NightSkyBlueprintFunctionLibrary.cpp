// Fill out your copyright notice in the Description page of Project Settings.


#include "NightSkyBlueprintFunctionLibrary.h"

#include "Globals.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(NightSkyBlueprintFunctionLibrary)

void UNightSkyBlueprintFunctionLibrary::SerializeProperty(void* Ptr, FProperty* Property, TArray<uint8>& Data,
                                                          bool bForce)
{
	if ((Property->PropertyFlags & CPF_SaveGame) == 0 && !bForce) return;
	Data.Append((uint8*)&Property->ArrayDim, 4);
	for (int Idx = 0; Idx < Property->ArrayDim; Idx++)
	{
		if (Property->IsA(FStructProperty::StaticClass()))
		{
			SerializeBinStruct(Property->ContainerPtrToValuePtr<void>(Ptr, 0), ((FStructProperty*)Property)->Struct,
			                   Data);
		}
		else if (Property->IsA(FArrayProperty::StaticClass()))
		{
			void* ScriptArray = Property->ContainerPtrToValuePtr<void>(Ptr, Idx);
			FScriptArrayHelper ArrayHelper((FArrayProperty*)Property, ScriptArray);
			int32 Length = ArrayHelper.Num();

			Data.Append((uint8*)&Length, 4);

			for (int ArrIdx = 0; ArrIdx < Length; ArrIdx++)
			{
				if (((FArrayProperty*)Property)->Inner->IsA(FStructProperty::StaticClass()))
				{
					SerializeBinStruct(ArrayHelper.GetRawPtr(ArrIdx), ((FStructProperty*)((FArrayProperty*)Property)->Inner)->Struct,
					                  Data, true);
				}
				else
				{
					Data.Append(ArrayHelper.GetRawPtr(ArrIdx), ((FArrayProperty*)Property)->Inner->GetElementSize());
				}
			}
		}
		else
		{
			Data.Append(Property->ContainerPtrToValuePtr<uint8>(Ptr, Idx), Property->GetElementSize());
		}
	}
}

int64 UNightSkyBlueprintFunctionLibrary::DeserializeProperty(void* Ptr, FProperty* Property,
                                                             const TArrayView<const uint8>& Data,
                                                             int64& DataIdx, bool bForce)
{
	if ((Property->PropertyFlags & CPF_SaveGame) == 0 && !bForce) return DataIdx;
	Property->ArrayDim = *(int32*)&Data[DataIdx];
	DataIdx += 4;
	for (int Idx = 0; Idx < Property->ArrayDim; Idx++)
	{
		if (Property->IsA(FStructProperty::StaticClass()))
		{
			DeserializeBinStruct(Property->ContainerPtrToValuePtr<void>(Ptr, 0),
			                     ((FStructProperty*)Property)->Struct, Data, DataIdx);
		}
		else if (Property->IsA(FArrayProperty::StaticClass()))
		{
			int32 Length = *(int32*)&Data[DataIdx];
			DataIdx += 4;
			void* ScriptArray = Property->ContainerPtrToValuePtr<void>(Ptr, Idx);
			FScriptArrayHelper ArrayHelper((FArrayProperty*)Property, ScriptArray);

			ArrayHelper.Resize(Length);
			for (int ArrIdx = 0; ArrIdx < Length; ArrIdx++)
			{
				if (((FArrayProperty*)Property)->Inner->IsA(FStructProperty::StaticClass()))
				{
					DeserializeBinStruct(ArrayHelper.GetRawPtr(ArrIdx),
					                     ((FStructProperty*)((FArrayProperty*)Property)->Inner)->Struct,
					                     Data, DataIdx, true);
				}
				else
				{
					FMemory::Memcpy(ArrayHelper.GetRawPtr(ArrIdx), &Data[DataIdx],
					                ((FArrayProperty*)Property)->Inner->GetElementSize());
					DataIdx += ((FArrayProperty*)Property)->Inner->GetElementSize();
				}
			}
		}
		else
		{
			FMemory::Memcpy(Property->ContainerPtrToValuePtr<uint8>(Ptr, Idx), &Data[DataIdx],
			                Property->GetElementSize());
			DataIdx += Property->GetElementSize();
		}
	}
	return DataIdx;
}

void UNightSkyBlueprintFunctionLibrary::SerializeBinStruct(void* Ptr, UScriptStruct* Struct, TArray<uint8>& Data, bool bForce)
{
	for (FProperty* Property = Struct->PropertyLink; Property != nullptr; Property = Property->PropertyLinkNext)
	{
		SerializeProperty(Ptr, Property, Data, bForce);
	}
}

int64 UNightSkyBlueprintFunctionLibrary::DeserializeBinStruct(void* Ptr, UScriptStruct* Struct,
                                                              const TArrayView<const uint8>& Data, int64& DataIdx, bool bForce)
{
	for (FProperty* Property = Struct->PropertyLink; Property != nullptr; Property = Property->PropertyLinkNext)
	{
		DeserializeProperty(Ptr, Property, Data, DataIdx, bForce);
	}
	return DataIdx;
}

void UNightSkyBlueprintFunctionLibrary::SerializeBin(UObject* Obj, TArray<uint8>& Data)
{
	const UClass* Class = Obj->GetClass();
	for (FProperty* Property = Class->PropertyLink; Property != nullptr; Property = Property->PropertyLinkNext)
	{
		SerializeProperty(Obj, Property, Data);
	}
}

int64 UNightSkyBlueprintFunctionLibrary::DeserializeBin(UObject* Obj, const TArrayView<const uint8>& Data)
{
	const UClass* Class = Obj->GetClass();
	int64 DataIdx = 0;
	for (FProperty* Property = Class->PropertyLink; Property != nullptr; Property = Property->PropertyLinkNext)
	{
		DeserializeProperty(Obj, Property, Data, DataIdx);
	}
	return DataIdx;
}

int32 UNightSkyBlueprintFunctionLibrary::Vec2Angle_x1000(int32 x, int32 y)
{
	int32 Angle = static_cast<int>(atan2(y, x) * 57295.77791868204) % 360000;
	if (Angle < 0)
		Angle += 360000;
	return Angle;
}

int32 UNightSkyBlueprintFunctionLibrary::Cos_x1000(int32 Deg_x10)
{
	int32 Tmp1 = (Deg_x10 + 900) % 3600;
	int32 Tmp2 = Deg_x10 + 3600;
	if (Tmp1 >= 0)
		Tmp2 = Tmp1;
	if (Tmp2 < 900)
		return gSinTable[Tmp2];
	if (Tmp2 < 1800)
		return gSinTable[1799 - Tmp2];
	if (Tmp2 >= 2700)
		return -gSinTable[3599 - Tmp2];
	return -gSinTable[Tmp2 - 1800];
}

int32 UNightSkyBlueprintFunctionLibrary::Sin_x1000(int32 Deg_x10)
{
	int32 Tmp1 = Deg_x10 % 3600;
	int32 Tmp2 = Deg_x10 + 3600;
	if (Tmp1 >= 0)
		Tmp2 = Tmp1;
	if (Tmp2 < 900)
		return gSinTable[Tmp2];
	if (Tmp2 < 1800)
		return gSinTable[1799 - Tmp2];
	if (Tmp2 >= 2700)
		return -gSinTable[3599 - Tmp2];
	return -gSinTable[Tmp2 - 1800];
}
