// Fill out your copyright notice in the Description page of Project Settings.


#include "NightSkyBlueprintFunctionLibrary.h"

#include "Globals.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(NightSkyBlueprintFunctionLibrary)

void UNightSkyBlueprintFunctionLibrary::SerializeProperty(void* Ptr, FProperty* Property, TArray<uint8>& Data, bool bForce)
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
				SerializeProperty(ArrayHelper.GetRawPtr(ArrIdx), ((FArrayProperty*)Property)->Inner,
				  Data, true);
			}
		}
		else
		{
			Data.Append(Property->ContainerPtrToValuePtr<uint8>(Ptr, Idx), Property->GetElementSize());
		}
	}
}

void UNightSkyBlueprintFunctionLibrary::DeserializeProperty(void* Ptr, FProperty* Property, const TArray<uint8>& Data,
                                                            int& DataIdx, bool bForce)
{
	if ((Property->PropertyFlags & CPF_SaveGame) == 0 && !bForce) return;
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

			ArrayHelper.EmptyAndAddValues(Length);
			for (int ArrIdx = 0; ArrIdx < Length; ArrIdx++)
			{
				DeserializeProperty(ArrayHelper.GetRawPtr(ArrIdx), ((FArrayProperty*)Property)->Inner,
				  Data, DataIdx, true);
			}
		}
		else
		{
			FMemory::Memcpy(Property->ContainerPtrToValuePtr<uint8>(Ptr, Idx), &Data[DataIdx],
							Property->GetElementSize());
			DataIdx += Property->GetElementSize();
		}
	}
}

void UNightSkyBlueprintFunctionLibrary::SerializeBinStruct(void* Ptr, UScriptStruct* Struct, TArray<uint8>& Data)
{
	for (FProperty* Property = Struct->PropertyLink; Property != nullptr; Property = Property->PropertyLinkNext)
	{
		SerializeProperty(Ptr, Property, Data);
	}
}

void UNightSkyBlueprintFunctionLibrary::DeserializeBinStruct(void* Ptr, UScriptStruct* Struct,
                                                             const TArray<uint8>& Data, int& DataIdx)
{
	for (FProperty* Property = Struct->PropertyLink; Property != nullptr; Property = Property->PropertyLinkNext)
	{
		DeserializeProperty(Ptr, Property, Data, DataIdx);
	}
}

void UNightSkyBlueprintFunctionLibrary::SerializeBin(UObject* Obj, TArray<uint8>& Data)
{
	const UClass* Class = Obj->GetClass();
	for (FProperty* Property = Class->PropertyLink; Property != nullptr; Property = Property->PropertyLinkNext)
	{
		SerializeProperty(Obj, Property, Data);
	}
}

void UNightSkyBlueprintFunctionLibrary::DeserializeBin(UObject* Obj, const TArray<uint8>& Data)
{
	const UClass* Class = Obj->GetClass();
	int DataIdx = 0;
	for (FProperty* Property = Class->PropertyLink; Property != nullptr; Property = Property->PropertyLinkNext)
	{
		DeserializeProperty(Obj, Property, Data, DataIdx);
	}
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
