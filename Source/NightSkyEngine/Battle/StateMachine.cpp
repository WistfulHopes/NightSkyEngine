#include "StateMachine.h"

#include "StateAlias.h"
#include "SubroutineState.h"
#include "Actors/PlayerObject.h"

void FStateMachine::AddState(const FName& Name, UState* Config)
{
	Config->Parent = Parent;
	States.Add(Config);
	StateNames.Add(Name);
	if (CurrentState == nullptr)
	{
		CurrentState = Config;
		Parent->TriggerEvent(EVT_Enter);
		Update();
	}
}

FName FStateMachine::GetStateName(int Index)
{
	if (Index > 0 && Index < States.Num())
	{
		return FName(States[Index]->Name);
	}
	return "";
}

int FStateMachine::GetStateIndex(FName Name) const
{
	return StateNames.Find(Name);
}

bool FStateMachine::SetState(const FName Name, bool bIsAlias)
{
	if (StateNames.Find(Name) == INDEX_NONE)
	{
		return false;
	}

	if (IsCurrentState(Name))
	{
		CurrentState = States[StateNames.Find(Name)];
		return true;
	}

	const auto StateToEnter = States[StateNames.Find(Name)];
	if (const auto SubroutineState = Cast<USubroutineState>(StateToEnter))
	{
		Parent->CallSubroutine(SubroutineState->SubroutineName);
		return false;
	}
	if (!bIsAlias)
	{
		Parent->StateEntryName = FName(StateToEnter->Name);
	}
	if (const auto Alias = Cast<UStateAlias>(StateToEnter))
	{
		return SetState(FName(Alias->StateToEnter), true);
	}
	
	Parent->TriggerEvent(EVT_Exit);
	Parent->OnStateChange();	

	CurrentState = StateToEnter;
	Parent->PostStateChange();
	Parent->TriggerEvent(EVT_Enter);
	Update();

	return true;
}

bool FStateMachine::ForceSetState(const FName Name, bool bIsAlias)
{
	if (StateNames.Find(Name) == INDEX_NONE)
	{
		return false;
	}
	
	const auto StateToEnter = States[StateNames.Find(Name)];
	if (const auto SubroutineState = Cast<USubroutineState>(StateToEnter))
	{
		Parent->CallSubroutine(SubroutineState->SubroutineName);
		return false;
	}
	if (!bIsAlias)
	{
		Parent->StateEntryName = FName(StateToEnter->Name);
	}
	if (const auto Alias = Cast<UStateAlias>(StateToEnter))
	{
		return ForceSetState(FName(Alias->StateToEnter), true);
	}

	Parent->TriggerEvent(EVT_Exit);
	Parent->OnStateChange();	

	CurrentState = StateToEnter;
	Parent->PostStateChange();
	Parent->TriggerEvent(EVT_Enter);
	Update();

	return true;
}

bool FStateMachine::ForceRollbackState(const FName Name)
{
	if (StateNames.Find(Name) == INDEX_NONE)
	{
		return false;
	}
		
	CurrentState = States[StateNames.Find(Name)];

	return true;
}

bool FStateMachine::CheckStateStanceCondition(const EEntryStance StateStance, const int PlayerStance)
{
	if ((StateStance == EEntryStance::Standing && PlayerStance == ACT_Standing)
	|| (StateStance == EEntryStance::Standing && PlayerStance == ACT_Crouching)
	|| (StateStance == EEntryStance::Crouching && PlayerStance == ACT_Standing)
	|| (StateStance == EEntryStance::Crouching && PlayerStance == ACT_Crouching)
	|| (StateStance == EEntryStance::Jumping && PlayerStance == ACT_Jumping)
	|| StateStance == EEntryStance::None)
	{
		return true;
	}
	return false;
}

void FStateMachine::Update() const
{
	if (CurrentState != nullptr)
	{
		CurrentState->CallExec();
	}
}
