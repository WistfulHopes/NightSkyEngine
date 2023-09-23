#include "StateMachine.h"
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

bool FStateMachine::SetState(const FName Name)
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

	Parent->TriggerEvent(EVT_Exit);
	Parent->OnStateChange();	

	CurrentState = States[StateNames.Find(Name)];
	Parent->PostStateChange();
	Parent->TriggerEvent(EVT_Enter);
	Update();

	return true;
}

bool FStateMachine::ForceSetState(const FName Name)
{
	if (StateNames.Find(Name) == INDEX_NONE)
	{
		return false;
	}
	
	Parent->TriggerEvent(EVT_Exit);
	Parent->OnStateChange();	

	CurrentState = States[StateNames.Find(Name)];
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
