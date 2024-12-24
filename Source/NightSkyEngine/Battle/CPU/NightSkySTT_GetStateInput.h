// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeTaskBlueprintBase.h"
#include "NightSkyEngine/Battle/State.h"
#include "NightSkySTT_GetStateInput.generated.h"

/**
 * 
 */
UCLASS()
class NIGHTSKYENGINE_API UNightSkySTT_GetStateInput : public UStateTreeTaskBlueprintBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag StateName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FInputConditionList Conditions;
	
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) override;
};
