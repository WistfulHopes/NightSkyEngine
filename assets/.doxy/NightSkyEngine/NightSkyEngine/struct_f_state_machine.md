

# Struct FStateMachine



[**ClassList**](annotated.md) **>** [**FStateMachine**](struct_f_state_machine.md)



_The player object's state machine._ [More...](#detailed-description)

* `#include <StateMachine.h>`





















## Public Attributes

| Type | Name |
| ---: | :--- |
|  [**UState**](class_u_state.md) \* | [**CurrentState**](#variable-currentstate)  <br> |
|  int32 | [**EnableFlags**](#variable-enableflags)   = `0`<br> |
|  TArray&lt; FGameplayTag &gt; | [**EnabledCustomStateTypes**](#variable-enabledcustomstatetypes)  <br> |
|  [**APlayerObject**](class_a_player_object.md) \* | [**Parent**](#variable-parent)  <br> |
|  FGameplayTag | [**StateMachineName**](#variable-statemachinename)  <br> |
|  TArray&lt; FGameplayTag &gt; | [**StateNames**](#variable-statenames)  <br> |
|  TArray&lt; [**UState**](class_u_state.md) \* &gt; | [**States**](#variable-states)  <br> |
|  bool | [**bPrimary**](#variable-bprimary)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**AddState**](#function-addstate) (const FGameplayTag & Name, [**UState**](class_u_state.md) \* Config) <br> |
|  bool | [**ForceRollbackState**](#function-forcerollbackstate) (const FGameplayTag Name) <br> |
|  bool | [**ForceSetState**](#function-forcesetstate-12) (const FGameplayTag Name, bool bIsAlias=false) <br> |
|  bool | [**ForceSetState**](#function-forcesetstate-22) (TSubclassOf&lt; [**UState**](class_u_state.md) &gt; Class, bool bIsAlias=false) <br> |
|  int | [**GetStateIndex**](#function-getstateindex) (FGameplayTag Name) const<br> |
|  FGameplayTag | [**GetStateName**](#function-getstatename) (int Index) <br> |
|  FORCEINLINE bool | [**IsCurrentState**](#function-iscurrentstate) (const FGameplayTag & Name) const<br> |
|  bool | [**SetState**](#function-setstate) (const FGameplayTag Name, bool bIsAlias=false) <br> |
|  void | [**Update**](#function-update) () const<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  bool | [**CheckStateStanceCondition**](#function-checkstatestancecondition) (const EEntryStance StateStance, const int PlayerStance) <br> |


























## Detailed Description


Contains all player states and state names, as well as the currently active state. 


    
## Public Attributes Documentation




### variable CurrentState 

```C++
UState* FStateMachine::CurrentState;
```



The currently active state. 


        

<hr>



### variable EnableFlags 

```C++
int32 FStateMachine::EnableFlags;
```



Flags of currently enabled states. 


        

<hr>



### variable EnabledCustomStateTypes 

```C++
TArray<FGameplayTag> FStateMachine::EnabledCustomStateTypes;
```



Currently enabled custom state types. 


        

<hr>



### variable Parent 

```C++
APlayerObject* FStateMachine::Parent;
```



The parent of this state machine. 


        

<hr>



### variable StateMachineName 

```C++
FGameplayTag FStateMachine::StateMachineName;
```



The currently active state. 


        

<hr>



### variable StateNames 

```C++
TArray<FGameplayTag> FStateMachine::StateNames;
```



An array of all player state names. Used to lookup states. 


        

<hr>



### variable States 

```C++
TArray<UState*> FStateMachine::States;
```



An array of all player states. 


        

<hr>



### variable bPrimary 

```C++
bool FStateMachine::bPrimary;
```




<hr>
## Public Functions Documentation




### function AddState 

```C++
void FStateMachine::AddState (
    const FGameplayTag & Name,
    UState * Config
) 
```



Adds a state to the state machine. If no current state is set, the input state will be used as the current state. Only call at the beginning of a match! 


        

<hr>



### function ForceRollbackState 

```C++
bool FStateMachine::ForceRollbackState (
    const FGameplayTag Name
) 
```



Sets the current state for rollback. Code called when entering a state normally will not be called.




**Parameters:**


* `Name` The state to set as current. 



**Returns:**

If the state was successfully set, return true. Otherwise return false. 





        

<hr>



### function ForceSetState [1/2]

```C++
bool FStateMachine::ForceSetState (
    const FGameplayTag Name,
    bool bIsAlias=false
) 
```



Sets the current state. If the state to set is the same as the current state, the state will be reset.




**Parameters:**


* `Name` The state to set as current. 
* `bIsAlias` If the state is being set via an alias. 



**Returns:**

If the state was successfully set, return true. Otherwise return false. 





        

<hr>



### function ForceSetState [2/2]

```C++
bool FStateMachine::ForceSetState (
    TSubclassOf< UState > Class,
    bool bIsAlias=false
) 
```



Sets the current state. If the state to set is the same as the current state, the state will be reset.




**Parameters:**


* `Class` The state to set as current. 
* `bIsAlias` If the state is being set via an alias. 



**Returns:**

If the state was successfully set, return true. Otherwise return false. 





        

<hr>



### function GetStateIndex 

```C++
int FStateMachine::GetStateIndex (
    FGameplayTag Name
) const
```



Gets the current state index. 


        

<hr>



### function GetStateName 

```C++
FGameplayTag FStateMachine::GetStateName (
    int Index
) 
```



Gets the current state name. 


        

<hr>



### function IsCurrentState 

```C++
inline FORCEINLINE bool FStateMachine::IsCurrentState (
    const FGameplayTag & Name
) const
```



Checks a name against the current state name. 


        

<hr>



### function SetState 

```C++
bool FStateMachine::SetState (
    const FGameplayTag Name,
    bool bIsAlias=false
) 
```



Sets the current state. If attempting to set the state to the same as the current state, nothing will happen.




**Parameters:**


* `Name` The state to set as current. 
* `bIsAlias` If the state is being set via an alias. 



**Returns:**

If the state was successfully set, return true. Otherwise return false. 





        

<hr>



### function Update 

```C++
void FStateMachine::Update () const
```



Calls the current state's exec function. 


        

<hr>
## Public Static Functions Documentation




### function CheckStateStanceCondition 

```C++
static bool FStateMachine::CheckStateStanceCondition (
    const EEntryStance StateStance,
    const int PlayerStance
) 
```



Checks if the state allows the player's current stance.




**Parameters:**


* `StateStance` The state's required stance. 
* `PlayerStance` The current player's stance. 



**Returns:**

If the state stance allows the player's stance, return true. Otherwise return false. 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/NightSkyEngine/Battle/Script/StateMachine.h`

