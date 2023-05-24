// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "NightSkyGameInstance.generated.h"

class APlayerObject;
enum class ERoundFormat : uint8;

/**
 * 
 */
UCLASS()
class NIGHTSKYENGINE_API UNightSkyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<TSubclassOf<APlayerObject>> PlayerList;
	UPROPERTY(BlueprintReadWrite)
	int PlayerIndex;
	UPROPERTY(BlueprintReadWrite)
	FString StageURL;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ERoundFormat RoundFormat;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int StartRoundTimer;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	bool IsTraining = false;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	bool IsCPUBattle = false;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TEnumAsByte<EFighterRunners> FighterRunner;
};
