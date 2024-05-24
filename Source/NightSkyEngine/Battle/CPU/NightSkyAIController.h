// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "NightSkyAIController.generated.h"

class ANightSkyGameState;
class UState;
class APlayerObject;

UCLASS()
class NIGHTSKYENGINE_API ANightSkyAIController : public AAIController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ANightSkyAIController();

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<APlayerObject> Player;
	UPROPERTY()
	TObjectPtr<ANightSkyGameState> GameState = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	int32 GetEnemyDistanceX() const;
	int32 GetEnemyDistanceY() const;

	int32 CheckFWalkWeight() const;
	int32 CheckBWalkWeight() const;
	int32 CheckFDashWeight() const;
	int32 CheckBDashWeight() const;
	int32 CheckAttackWeight(const UState* State) const;
	int32 CheckBurstWeight() const;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
