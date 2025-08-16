#include "StateMachine.h"

#include "StateAlias.h"
#include "SubroutineState.h"
#include "Actors/PlayerObject.h"

UE_DEFINE_GAMEPLAY_TAG_COMMENT(StateMachine_Primary, "StateMachine.Primary", "Primary State Machine");

void FStateMachine::AddState(const FGameplayTag& Name, UState* Config)
{
	Config->Parent = Parent;
	States.Add(Config);
	StateNames.Add(Name);
	if (CurrentState == nullptr)
	{
		CurrentState = Config;
		CurrentState->Init();
		Update();
	}
}

FGameplayTag FStateMachine::GetStateName(int Index)
{
	if (Index > 0 && Index < States.Num())
	{
		return States[Index]->Name;
	}
	return FGameplayTag::EmptyTag;
}

int FStateMachine::GetStateIndex(FGameplayTag Name) const
{
	return StateNames.Find(Name);
}

bool FStateMachine::SetState(const FGameplayTag Name, bool bIsAlias)
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
		Parent->StateEntryName = StateToEnter->Name;
	}
	if (const auto Alias = Cast<UStateAlias>(StateToEnter))
	{
		return SetState(Alias->StateToEnter, true);
	}
	
	Parent->TriggerEvent(EVT_Exit, StateMachineName);
	if (bPrimary) Parent->OnStateChange();

	CurrentState = StateToEnter;
	if (bPrimary) Parent->PostStateChange();
	CurrentState->Init();
	Update();

	return true;
}

bool FStateMachine::ForceSetState(const FGameplayTag Name, bool bIsAlias)
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
		Parent->StateEntryName = StateToEnter->Name;
	}
	if (const auto Alias = Cast<UStateAlias>(StateToEnter))
	{
		return ForceSetState(Alias->StateToEnter, true);
	}

	Parent->TriggerEvent(EVT_Exit, StateMachineName);
	if (bPrimary) Parent->OnStateChange();

	CurrentState = StateToEnter;
	if (bPrimary) Parent->PostStateChange();
	CurrentState->Init();
	Update();

	return true;
}

bool FStateMachine::ForceSetState(TSubclassOf<UState> Class, bool bIsAlias)
{
	for (auto State : States)
	{
		if (State->GetClass() == Class)
		{
			if (const auto SubroutineState = Cast<USubroutineState>(State))
			{
				Parent->CallSubroutine(SubroutineState->SubroutineName);
				return false;
			}
			if (!bIsAlias)
			{
				Parent->StateEntryName = State->Name;
			}
			if (const auto Alias = Cast<UStateAlias>(State))
			{
				return ForceSetState(Alias->StateToEnter, true);
			}

			Parent->TriggerEvent(EVT_Exit, StateMachineName);
			if (bPrimary) Parent->OnStateChange();

			CurrentState = State;
			if (bPrimary) Parent->PostStateChange();
			CurrentState->Init();
			Update();

			return true;
		}
	}
	return false;
}

bool FStateMachine::ForceRollbackState(const FGameplayTag Name)
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
