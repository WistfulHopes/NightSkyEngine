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

private:
	UPROPERTY(VisibleAnywhere)
	int FramesElapsed;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag StateName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int FramesToWait = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FInputConditionList Conditions;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EInputFlags> HoldInput;
	
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) override;
	virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) override;	
};
