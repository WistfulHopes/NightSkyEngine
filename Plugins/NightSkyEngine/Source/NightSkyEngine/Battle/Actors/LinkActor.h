// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LinkActor.generated.h"

UCLASS()
class NIGHTSKYENGINE_API ALinkActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALinkActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintImplementableEvent)
	void Init();
	
	UFUNCTION(BlueprintImplementableEvent)
	void Update();
	
	UFUNCTION(BlueprintImplementableEvent)
	void Exit();
};
