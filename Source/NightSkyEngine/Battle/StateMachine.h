#pragma once

#include "CoreMinimal.h"
#include "State.h"
#include "StateMachine.generated.h"

class APlayerObject;

/**
 * @brief The player object's state machine.
 *
 * Contains all player states and state names, as well as the currently active state.
 */
USTRUCT()
struct NIGHTSKYENGINE_API FStateMachine
{
	GENERATED_BODY()

	/**
	 * The currently active state.
	 */
	UPROPERTY()
	UState* CurrentState;
	/**
	 * An array of all player states.
	 */
	UPROPERTY()
	TArray<UState*> States;
	/**
	 * An array of all player state names.
	 * Used to lookup states.
	 */
	UPROPERTY()
	TArray<FName> StateNames;
	/**
	 * The parent of this state machine.
	 */
	UPROPERTY()
	APlayerObject* Parent;

	/**
	 * Adds a state to the state machine.
	 * If no current state is set, the input state will be used as the current state.
	 * Only call at the beginning of a match!
	 */	
	void AddState(const FName& Name, UState* Config);

	/**
	 * Checks a name against the current state name.
	 */	
	FORCEINLINE bool IsCurrentState(const FName& Name) const
	{
		return CurrentState->Name == Name;
	}
	
	/**
	 * Gets the current state name.
	 */	
	FName GetStateName(int Index);
	/**
	 * Gets the current state index.
	 */	
	int GetStateIndex(FName Name) const;

	/**
	 * Sets the current state.
	 * If attempting to set the state to the same as the current state, nothing will happen.
	 * 
	 * @param Name The state to set as current.
	 * @param bIsAlias If the state is being set via an alias.
	 * @return If the state was successfully set, return true. Otherwise return false.
	 */
	bool SetState(const FName Name, bool bIsAlias = false);
	/**
	 * Sets the current state.
	 * If the state to set is the same as the current state, the state will be reset.
	 * 
	 * @param Name The state to set as current.
	 * @param bIsAlias If the state is being set via an alias.
	 * @return If the state was successfully set, return true. Otherwise return false.
	 */
	bool ForceSetState(const FName Name, bool bIsAlias = false);
	/**
	 * Sets the current state for rollback.
	 * Code called when entering a state normally will not be called.
	 * 
	 * @param Name The state to set as current.
	 * @return If the state was successfully set, return true. Otherwise return false.
	 */
	bool ForceRollbackState(const FName Name);

	/**
	 * Checks if the state allows the player's current stance.
	 * 
	 * @param StateStance The state's required stance.
	 * @param PlayerStance The current player's stance.
	 * @return If the state stance allows the player's stance, return true. Otherwise return false.
	 */
	static bool CheckStateStanceCondition(const EEntryStance StateStance, const int PlayerStance);

	/**
	 * Calls the current state's exec function.
	 */
	void Update() const;
};
