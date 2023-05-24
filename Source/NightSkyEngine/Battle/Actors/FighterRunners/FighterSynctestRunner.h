// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FighterMultiplayerRunner.h"
#include "FighterSynctestRunner.generated.h"

UCLASS()
class NIGHTSKYENGINE_API AFighterSynctestRunner : public AFighterMultiplayerRunner
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFighterSynctestRunner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	virtual void Update(float DeltaTime) override;

};
