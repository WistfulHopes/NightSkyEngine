// Fill out your copyright notice in the Description page of Project Settings.


#include "NightSkySTT_ExecInput.h"

#include "NightSkyAIController.h"
#include "StateTreeExecutionContext.h"
#include "NightSkyEngine/Battle/Actors/PlayerObject.h"

EStateTreeRunStatus UNightSkySTT_ExecInput::EnterState(FStateTreeExecutionContext& Context,
                                                       const FStateTreeTransitionResult& Transition)
{
	const auto Status = Super::EnterState(Context, Transition);

	const auto Owner = Cast<APlayerObject>(Cast<ANightSkyAIController>(Context.GetOwner())->GetPawn());
	if (!Owner) return EStateTreeRunStatus::Failed;
	if (!Cast<ANightSkyAIController>(Context.GetOwner())->bCanUpdateInput) return Status;

	for (auto Condition : Conditions.InputConditions)
	{
		Owner->StoredInputBuffer.WriteInputCondition(Condition);
	}

	return Status;
}

EStateTreeRunStatus UNightSkySTT_ExecInput::Tick(FStateTreeExecutionContext& Context, const float DeltaTime)
{
	const auto Status = Super::Tick(Context, DeltaTime);

	FramesElapsed++;
	
	const auto Owner = Cast<APlayerObject>(Cast<ANightSkyAIController>(Context.GetOwner())->GetPawn());
	if (!Owner) return EStateTreeRunStatus::Failed;
	if (!Cast<ANightSkyAIController>(Context.GetOwner())->bCanUpdateInput) return Status;

	Owner->StoredInputBuffer.Update(HoldInput);

	if (FramesToWait < FramesElapsed) return EStateTreeRunStatus::Failed;
	if (Owner->StoredStateMachine.CurrentState->Name == StateName) return EStateTreeRunStatus::Succeeded;

	return Status;
}
