// Fill out your copyright notice in the Description page of Project Settings.


#include "NightSkySTT_SelectAttack.h"

#include "NightSkyAIController.h"
#include "StateTreeExecutionContext.h"
#include "NightSkyEngine/Battle/Actors/PlayerObject.h"

EStateTreeRunStatus UNightSkySTT_SelectAttack::EnterState(FStateTreeExecutionContext& Context,
                                                          const FStateTreeTransitionResult& Transition)
{
	const auto Status = Super::EnterState(Context, Transition);

	const auto Controller = Cast<ANightSkyAIController>(Context.GetOwner());
	const auto Owner = Cast<APlayerObject>(Controller->GetPawn());
	if (!Owner) return EStateTreeRunStatus::Failed;
	if (!Cast<ANightSkyAIController>(Context.GetOwner())->bCanUpdateInput) return Status;

	int Weight = 0;
	
	for (const auto State : Owner->StoredStateMachine.States.FilterByPredicate([](const UState* State)
	{
		return State->StateType >= EStateType::NormalAttack && State->StateType <= EStateType::SuperAttack;
	}))
	{
		if (!Owner->CanEnterState(State)) continue;

		if (const auto TmpWeight = Controller->CheckAttackWeight(State); TmpWeight > Weight)
		{
			StateName = State->Name;
			Weight = TmpWeight;
		}
	}
	
	if (!StateName.IsValid()) return EStateTreeRunStatus::Failed;
	
	return EStateTreeRunStatus::Running;
}
