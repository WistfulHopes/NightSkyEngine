// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "NightSkyVSInfoGameState.generated.h"

class UNightSkyGameInstance;
/**
 * 
 */
UCLASS()
class NIGHTSKYENGINE_API ANightSkyVSInfoGameState : public AGameStateBase
{
	GENERATED_BODY()

	double VSInfoTime;
	bool MapLoaded;
	int32 LoadedCharaPackageCount;
	int32 TotalCharaPackageCount;

	UPROPERTY()
	TArray<TObjectPtr<UPackage>> Packages;
	UPROPERTY()
	TObjectPtr<UNightSkyGameInstance> GameInstance;

public:
	ANightSkyVSInfoGameState();
	
	UPROPERTY(EditAnywhere)
	double MaxVSInfoTime = 6;
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
	void OnMapPackageLoaded(const FName& PackageName, UPackage* LoadedPackage, EAsyncLoadingResult::Type Result);
	void OnCharaPackageLoaded(const FName& PackageName, UPackage* LoadedPackage, EAsyncLoadingResult::Type Result);
};
