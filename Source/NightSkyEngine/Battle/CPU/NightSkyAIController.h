// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NightSkyEngine/Battle/State.h"
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
	bool bCanUpdateInput = false;
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<APlayerObject> Player = nullptr;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ANightSkyGameState> GameState = nullptr;
	UPROPERTY(BlueprintReadWrite)
	FInputCondition Condition{};

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	int32 GetEnemyDistanceX() const;
	UFUNCTION(BlueprintCallable)
	int32 GetEnemyDistanceY() const;

	UFUNCTION(BlueprintCallable)
	int32 CheckAttackWeight(const UState* State) const;
	UFUNCTION(BlueprintCallable)
	int32 CheckBurstWeight() const;
};
