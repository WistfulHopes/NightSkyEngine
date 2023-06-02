// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FighterLocalRunner.h"
#include "FighterReplayRunner.generated.h"

class UNightSkyGameInstance;

UCLASS()
class NIGHTSKYENGINE_API AFighterReplayRunner : public AFighterLocalRunner
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFighterReplayRunner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UNightSkyGameInstance* GameInstance;
	
public:
	// Called every frame
	virtual void Update(float DeltaTime) override;
};
