#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"
#include "State.h"
#include "StateMachine.generated.h"

class APlayerObject;

UE_DECLARE_GAMEPLAY_TAG_EXTERN(StateMachine_Primary);

/**
 * @brief The player object's state machine.
 *
 * Contains all player states and state names, as well as the currently active state.
 */
USTRUCT(BlueprintType)
struct NIGHTSKYENGINE_API FStateMachine
{
	GENERATED_BODY()

	
	UPROPERTY(SaveGame)
	bool bPrimary;
	/**
	 * The currently active state.
	 */
	UPROPERTY(EditDefaultsOnly, SaveGame)
	FGameplayTag StateMachineName;
	/**
	 * Flags of currently enabled states.
	 */
	UPROPERTY(SaveGame, meta=(Bitmask, BitmaskEnum = "/Script/NightSkyEngine.EEnableFlags"))
	int32 EnableFlags = 0;
	/**
	 * Currently enabled custom state types.
	 */
	UPROPERTY(SaveGame)
	TArray<FGameplayTag> EnabledCustomStateTypes;
	/**
	 * The currently active state.
	 */
	UPROPERTY(SaveGame)
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
	TArray<FGameplayTag> StateNames;
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
	void AddState(const FGameplayTag& Name, UState* Config);

	/**
	 * Checks a name against the current state name.
	 */	
	FORCEINLINE bool IsCurrentState(const FGameplayTag& Name) const
	{
		return CurrentState->Name == Name;
	}
	
	/**
	 * Gets the current state name.
	 */	
	FGameplayTag GetStateName(int Index);
	/**
	 * Gets the current state index.
	 */	
	int GetStateIndex(FGameplayTag Name) const;

	/**
	 * Sets the current state.
	 * If attempting to set the state to the same as the current state, nothing will happen.
	 * 
	 * @param Name The state to set as current.
	 * @param bIsAlias If the state is being set via an alias.
	 * @return If the state was successfully set, return true. Otherwise return false.
	 */
	bool SetState(const FGameplayTag Name, bool bIsAlias = false);
	/**
	 * Sets the current state.
	 * If the state to set is the same as the current state, the state will be reset.
	 * 
	 * @param Name The state to set as current.
	 * @param bIsAlias If the state is being set via an alias.
	 * @return If the state was successfully set, return true. Otherwise return false.
	 */
	bool ForceSetState(const FGameplayTag Name, bool bIsAlias = false);
	/**
	 * Sets the current state.
	 * If the state to set is the same as the current state, the state will be reset.
	 * 
	 * @param Class The state to set as current.
	 * @param bIsAlias If the state is being set via an alias.
	 * @return If the state was successfully set, return true. Otherwise return false.
	 */
	bool ForceSetState(TSubclassOf<UState> Class, bool bIsAlias = false);
	/**
	 * Sets the current state for rollback.
	 * Code called when entering a state normally will not be called.
	 * 
	 * @param Name The state to set as current.
	 * @return If the state was successfully set, return true. Otherwise return false.
	 */
	bool ForceRollbackState(const FGameplayTag Name);

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
