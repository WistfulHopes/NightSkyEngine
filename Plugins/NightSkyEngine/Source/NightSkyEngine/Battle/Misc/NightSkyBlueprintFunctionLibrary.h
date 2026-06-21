// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "NightSkyBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class NIGHTSKYENGINE_API UNightSkyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

private:
	static void SerializeProperty(void* Ptr, FProperty* Property, TArray<uint8>& Data, bool bForce = false);
	static int64 DeserializeProperty(void* Ptr, FProperty* Property, const TArrayView<const uint8>& Data, int64& DataIdx, bool bForce = false);
	
public:
	static void SerializeBinStruct(void* Ptr, UScriptStruct* Struct, TArray<uint8>& Data, bool bForce = false);
	static int64 DeserializeBinStruct(void* Ptr, UScriptStruct* Struct, const TArrayView<const uint8>& Data, int64& DataIdx, bool bForce = false);

	static void SerializeBin(UObject* Obj, TArray<uint8>& Data);
	static int64 DeserializeBin(UObject* Obj, const TArrayView<const uint8>& Data);
	
	UFUNCTION(BlueprintPure)
	static int32 Vec2Angle_x1000(int32 x, int32 y);
	UFUNCTION(BlueprintPure)
	static int32 Cos_x1000(int32 Deg_x10);
	UFUNCTION(BlueprintPure)
	static int32 Sin_x1000(int32 Deg_x10);
};
