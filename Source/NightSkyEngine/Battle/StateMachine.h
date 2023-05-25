#pragma once

#include "CoreMinimal.h"
#include "State.h"
#include "StateMachine.generated.h"

class APlayerObject;
#pragma pack (push, 1)

/**
 * 
 */
USTRUCT()
struct FStateMachine
{
	GENERATED_BODY()

	UPROPERTY()
	UState* CurrentState;
	UPROPERTY()
	TArray<UState*> States;
	UPROPERTY()
	TArray<FString> StateNames;
	UPROPERTY()
	APlayerObject* Parent;
	
	void Initialize();	
	void AddState(const FString Name, UState* Config);
	
	bool IsCurrentState(const FString Name) const
	{
		return CurrentState->Name == Name;
	}

	FString GetStateName(int Index);
	int GetStateIndex(FString Name);
	
	bool SetState(const FString Name);
	bool ForceSetState(const FString Name);
	bool ForceRollbackState(const FString Name);
		
	static bool CheckStateEntryCondition(const EEntryState EntryState, const int ActionFlags);
	
	void Update() const;
};
#pragma pack(pop)
