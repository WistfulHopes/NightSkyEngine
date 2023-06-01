// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ParticleData.generated.h"

USTRUCT(BlueprintType)
struct FParticleStruct
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FString Name;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	class UNiagaraSystem* ParticleSystem;
};

/**
 * 
 */
UCLASS()
class NIGHTSKYENGINE_API UParticleData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<FParticleStruct> ParticleStructs;
};
