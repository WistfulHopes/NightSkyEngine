// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NightSkyEngine/Battle/Actors/NightSkyPlayerController.h"
#include "NightSkyWTPlayerController.generated.h"

UCLASS()
class NIGHTSKYENGINE_API ANightSkyWTPlayerController : public ANightSkyPlayerController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ANightSkyWTPlayerController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
