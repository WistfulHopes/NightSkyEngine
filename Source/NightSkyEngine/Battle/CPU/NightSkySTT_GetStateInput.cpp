// Fill out your copyright notice in the Description page of Project Settings.


#include "NightSkySTT_GetStateInput.h"

#include "NightSkyAIController.h"
#include "StateTreeExecutionContext.h"
#include "NightSkyEngine/Battle/Actors/PlayerObject.h"

EStateTreeRunStatus UNightSkySTT_GetStateInput::EnterState(FStateTreeExecutionContext& Context,
	const FStateTreeTransitionResult& Transition)
{
	const auto Status =  Super::EnterState(Context, Transition);
	
	const auto Owner = Cast<APlayerObject>(Cast<ANightSkyAIController>(Context.GetOwner())->GetPawn());
	if (!Owner) return EStateTreeRunStatus::Failed;

	const auto State = Owner->StoredStateMachine.States.FindByPredicate([&](const UState* InState)
	{
		if (!InState) return false;
		return InState->Name == StateName;
	});

	if (State != nullptr)
	{
		if ((*State)->InputConditionLists.Num() == 0) Conditions = FInputConditionList();
		else Conditions = (*State)->InputConditionLists[0];
	}
	
	return EStateTreeRunStatus::Running;
}
