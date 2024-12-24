// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeTaskBlueprintBase.h"
#include "NightSkyEngine/Battle/State.h"
#include "NightSkySTT_ExecInput.generated.h"

/**
 * 
 */
UCLASS()
class NIGHTSKYENGINE_API UNightSkySTT_ExecInput : public UStateTreeTaskBlueprintBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FInputConditionList Conditions;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EInputFlags> HoldInput;
	
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) override;
	virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) override;	
};
