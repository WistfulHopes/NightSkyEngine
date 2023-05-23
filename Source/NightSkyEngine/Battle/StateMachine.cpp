#include "StateMachine.h"
#include "Actors/PlayerObject.h"

void FStateMachine::Initialize()
{
	for (auto State : States)
	{
		State->Parent = Parent;
		StateNames.Add(State->Name);
		if (CurrentState == nullptr)
		{
			CurrentState = State;
		}
	}
}

void FStateMachine::AddState(const FString Name, UState* Config)
{
	Config->Parent = Parent;
	States.Add(Config);
	StateNames.Add(Name);
	if (CurrentState == nullptr)
	{
		CurrentState = Config;
	}
}

FString FStateMachine::GetStateName(int Index)
{
	if (Index > 0 && Index < States.Num())
	{
		return States[Index]->Name;
	}
	return "";
}

int FStateMachine::GetStateIndex(FString Name)
{
	return StateNames.Find(Name);
}

bool FStateMachine::SetState(const FString Name)
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
		
	Parent->OnStateChange();	

	CurrentState = States[StateNames.Find(Name)];

	return true;
}

bool FStateMachine::ForceSetState(const FString Name)
{
	if (StateNames.Find(Name) == INDEX_NONE)
	{
		return false;
	}
	
	Parent->OnStateChange();

	CurrentState = States[StateNames.Find(Name)];

	return true;
}

bool FStateMachine::ForceRollbackState(const FString Name)
{
	if (StateNames.Find(Name) == INDEX_NONE)
	{
		return false;
	}
		
	CurrentState = States[StateNames.Find(Name)];

	return true;
}

bool FStateMachine::CheckStateEntryCondition(const EEntryState EntryState, const int ActionFlags)
{
	if ((EntryState == EEntryState::Standing && ActionFlags == ACT_Standing)
	|| (EntryState == EEntryState::Standing && ActionFlags == ACT_Crouching)
	|| (EntryState == EEntryState::Crouching && ActionFlags == ACT_Standing)
	|| (EntryState == EEntryState::Crouching && ActionFlags == ACT_Crouching)
	|| (EntryState == EEntryState::Jumping && ActionFlags == ACT_Jumping)
	|| EntryState == EEntryState::None)
	{
		return true;
	}
	return false;
}

void FStateMachine::Update() const
{
	if (CurrentState != nullptr)
	{
		CurrentState->Exec();
	}
}
