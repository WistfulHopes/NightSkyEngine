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

public:
	UFUNCTION(BlueprintPure)
	static int32 Vec2Angle_x1000(int32 x, int32 y);
	UFUNCTION(BlueprintPure)
	static int32 Cos_x1000(int32 Deg_x10);
	UFUNCTION(BlueprintPure)
	static int32 Sin_x1000(int32 Deg_x10);
};
