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
	static void DeserializeProperty(void* Ptr, FProperty* Property, const TArray<uint8>& Data, int& DataIdx, bool bForce = false);
	
public:
	static void SerializeBinStruct(void* Ptr, UScriptStruct* Struct, TArray<uint8>& Data);
	static void DeserializeBinStruct(void* Ptr, UScriptStruct* Struct, const TArray<uint8>& Data, int& DataIdx);

	UFUNCTION(BlueprintPure)
	static void SerializeBin(UObject* Obj, TArray<uint8>& Data);
	UFUNCTION(BlueprintCallable)
	static void DeserializeBin(UObject* Obj, const TArray<uint8>& Data);
	UFUNCTION(BlueprintPure)
	static int32 Vec2Angle_x1000(int32 x, int32 y);
	UFUNCTION(BlueprintPure)
	static int32 Cos_x1000(int32 Deg_x10);
	UFUNCTION(BlueprintPure)
	static int32 Sin_x1000(int32 Deg_x10);
};
