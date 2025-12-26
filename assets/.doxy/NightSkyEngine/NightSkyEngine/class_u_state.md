

# Class UState



[**ClassList**](annotated.md) **>** [**UState**](class_u_state.md)



_A character state that determines behavior._ [More...](#detailed-description)

* `#include <State.h>`



Inherits the following classes: [USerializableObj](class_u_serializable_obj.md)


Inherited by the following classes: [UStateAlias](class_u_state_alias.md),  [USubroutineState](class_u_subroutine_state.md)




















## Public Attributes

| Type | Name |
| ---: | :--- |
|  [**FStateCPUData**](struct_f_state_c_p_u_data.md) | [**CPUData**](#variable-cpudata)  <br> |
|  int32 | [**CelIndex**](#variable-celindex)  <br> |
|  FGameplayTag | [**CustomStateType**](#variable-customstatetype)  <br> |
|  EEntryStance | [**EntryStance**](#variable-entrystance)  <br> |
|  TArray&lt; [**FInputConditionList**](struct_f_input_condition_list.md) &gt; | [**InputConditionLists**](#variable-inputconditionlists)  <br> |
|  bool | [**IsFollowupState**](#variable-isfollowupstate)  <br> |
|  int32 | [**MaxChain**](#variable-maxchain)   = `-1`<br> |
|  int32 | [**MaxInstances**](#variable-maxinstances)   = `1`<br> |
|  FGameplayTag | [**Name**](#variable-name)  <br> |
|  int32 | [**ObjectID**](#variable-objectid)  <br> |
|  [**ABattleObject**](class_a_battle_object.md) \* | [**Parent**](#variable-parent)  <br> |
|  FGameplayTag | [**ShareChainName**](#variable-sharechainname)  <br> |
|  TArray&lt; EStateCondition &gt; | [**StateConditions**](#variable-stateconditions)  <br> |
|  EStateType | [**StateType**](#variable-statetype)  <br> |
|  bool | [**bCPUUsable**](#variable-bcpuusable)   = `true`<br> |
|  bool | [**bEnableReverseBeat**](#variable-benablereversebeat)   = `true`<br> |
|  bool | [**bHumanUsable**](#variable-bhumanusable)   = `true`<br> |
































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual void | [**CallExec**](#function-callexec) () <br> |
|  bool | [**CanEnterState**](#function-canenterstate) () <br> |
|  void | [**Exec**](#function-exec) () <br> |
|  void | [**Init**](#function-init) () <br> |


## Public Functions inherited from USerializableObj

See [USerializableObj](class_u_serializable_obj.md)

| Type | Name |
| ---: | :--- |
|  void | [**LoadForRollback**](class_u_serializable_obj.md#function-loadforrollback) (const TArray&lt; uint8 &gt; & InBytes) <br> |
|  void | [**ResetToCDO**](class_u_serializable_obj.md#function-resettocdo) () <br> |
|  TArray&lt; uint8 &gt; | [**SaveForRollback**](class_u_serializable_obj.md#function-saveforrollback) () <br> |






















































## Detailed Description


Provides functionality for the current character behavior, such as frame data, animations, and more. 


    
## Public Attributes Documentation




### variable CPUData 

```C++
FStateCPUData UState::CPUData;
```



Data for the CPU to determine when to enter the state. 


        

<hr>



### variable CelIndex 

```C++
int32 UState::CelIndex;
```



The current cel index. Used in Blueprint macros to determine which code to execute. 


        

<hr>



### variable CustomStateType 

```C++
FGameplayTag UState::CustomStateType;
```



The custom state type. Only used if the base state type is set to Custom. 


        

<hr>



### variable EntryStance 

```C++
EEntryStance UState::EntryStance;
```



The required stance to enter this state. Only used on player states. 


        

<hr>



### variable InputConditionLists 

```C++
TArray<FInputConditionList> UState::InputConditionLists;
```



An array of input condition lists. Only the success of one input condition list is required to enter the state. 


        

<hr>



### variable IsFollowupState 

```C++
bool UState::IsFollowupState;
```



A value that determines if this state can be entered directly, or must be canceled into. 


        

<hr>



### variable MaxChain 

```C++
int32 UState::MaxChain;
```



The maximum number of times this state can be used in a chain. For use with moves used in a combo that you wish to prevent cancelling into multiple times in sequence. 


        

<hr>



### variable MaxInstances 

```C++
int32 UState::MaxInstances;
```



Determines how many of this state will be spawned. Only used on object states. Player states will ignore this value and always spawn one instance. 


        

<hr>



### variable Name 

```C++
FGameplayTag UState::Name;
```



The name of this state. For player states, this is used to jump to states directly. For object states, this is used to create an object by name. 


        

<hr>



### variable ObjectID 

```C++
int32 UState::ObjectID;
```



A value that's set to match with spawned objects. If an owned object with this ID is active, this state can't be entered. For use with states that you do not wish to enter while the projectile is active. Only used on player states. 


        

<hr>



### variable Parent 

```C++
ABattleObject* UState::Parent;
```



The object that owns this state instance. For player states, this will always be the owning player. For object states, this value will change when a new object is activated and takes over this state. 


        

<hr>



### variable ShareChainName 

```C++
FGameplayTag UState::ShareChainName;
```



The state name to share a max chain with. 


        

<hr>



### variable StateConditions 

```C++
TArray<EStateCondition> UState::StateConditions;
```



An array of state conditions. All state conditions must be successful to enter this state. 


        

<hr>



### variable StateType 

```C++
EStateType UState::StateType;
```



The type of this state. 


        

<hr>



### variable bCPUUsable 

```C++
bool UState::bCPUUsable;
```



If a CPU player should be able to enter the state. Not used with object states. 


        

<hr>



### variable bEnableReverseBeat 

```C++
bool UState::bEnableReverseBeat;
```



The maximum number of times this state can be used in a reverse beat chain. For use with normal attacks that you don't want to use in reverse beat. 


        

<hr>



### variable bHumanUsable 

```C++
bool UState::bHumanUsable;
```



If a human player should be able to enter the state. Not used with object states. 


        

<hr>
## Public Functions Documentation




### function CallExec 

```C++
virtual void UState::CallExec () 
```



Wrapper for Exec function that sets CelIndex to zero. 


        

<hr>



### function CanEnterState 

```C++
bool UState::CanEnterState () 
```



Called to check if the state may be entered. 


        

<hr>



### function Exec 

```C++
void UState::Exec () 
```



Called every frame to update the state. 


        

<hr>



### function Init 

```C++
void UState::Init () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/NightSkyEngine/Battle/Script/State.h`

