// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SerializableObj.generated.h"

/**
 * 
 */
UCLASS()
class NIGHTSKYENGINE_API USerializableObj : public UObject
{
	GENERATED_BODY()
	
public:
	TArray<uint8> SaveForRollback();
	void LoadForRollback(const TArray<uint8>& InBytes);
	void ResetToCDO();
};
