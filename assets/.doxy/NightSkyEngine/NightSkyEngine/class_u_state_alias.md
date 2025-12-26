

# Class UStateAlias



[**ClassList**](annotated.md) **>** [**UStateAlias**](class_u_state_alias.md)



[More...](#detailed-description)

* `#include <StateAlias.h>`



Inherits the following classes: [UState](class_u_state.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  FGameplayTag | [**StateToEnter**](#variable-statetoenter)  <br> |


## Public Attributes inherited from UState

See [UState](class_u_state.md)

| Type | Name |
| ---: | :--- |
|  [**FStateCPUData**](struct_f_state_c_p_u_data.md) | [**CPUData**](class_u_state.md#variable-cpudata)  <br> |
|  int32 | [**CelIndex**](class_u_state.md#variable-celindex)  <br> |
|  FGameplayTag | [**CustomStateType**](class_u_state.md#variable-customstatetype)  <br> |
|  EEntryStance | [**EntryStance**](class_u_state.md#variable-entrystance)  <br> |
|  TArray&lt; [**FInputConditionList**](struct_f_input_condition_list.md) &gt; | [**InputConditionLists**](class_u_state.md#variable-inputconditionlists)  <br> |
|  bool | [**IsFollowupState**](class_u_state.md#variable-isfollowupstate)  <br> |
|  int32 | [**MaxChain**](class_u_state.md#variable-maxchain)   = `-1`<br> |
|  int32 | [**MaxInstances**](class_u_state.md#variable-maxinstances)   = `1`<br> |
|  FGameplayTag | [**Name**](class_u_state.md#variable-name)  <br> |
|  int32 | [**ObjectID**](class_u_state.md#variable-objectid)  <br> |
|  [**ABattleObject**](class_a_battle_object.md) \* | [**Parent**](class_u_state.md#variable-parent)  <br> |
|  FGameplayTag | [**ShareChainName**](class_u_state.md#variable-sharechainname)  <br> |
|  TArray&lt; EStateCondition &gt; | [**StateConditions**](class_u_state.md#variable-stateconditions)  <br> |
|  EStateType | [**StateType**](class_u_state.md#variable-statetype)  <br> |
|  bool | [**bCPUUsable**](class_u_state.md#variable-bcpuusable)   = `true`<br> |
|  bool | [**bEnableReverseBeat**](class_u_state.md#variable-benablereversebeat)   = `true`<br> |
|  bool | [**bHumanUsable**](class_u_state.md#variable-bhumanusable)   = `true`<br> |














































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual void | [**CallExec**](#function-callexec) () override<br> |


## Public Functions inherited from UState

See [UState](class_u_state.md)

| Type | Name |
| ---: | :--- |
| virtual void | [**CallExec**](class_u_state.md#function-callexec) () <br> |
|  bool | [**CanEnterState**](class_u_state.md#function-canenterstate) () <br> |
|  void | [**Exec**](class_u_state.md#function-exec) () <br> |
|  void | [**Init**](class_u_state.md#function-init) () <br> |


## Public Functions inherited from USerializableObj

See [USerializableObj](class_u_serializable_obj.md)

| Type | Name |
| ---: | :--- |
|  void | [**LoadForRollback**](class_u_serializable_obj.md#function-loadforrollback) (const TArray&lt; uint8 &gt; & InBytes) <br> |
|  void | [**ResetToCDO**](class_u_serializable_obj.md#function-resettocdo) () <br> |
|  TArray&lt; uint8 &gt; | [**SaveForRollback**](class_u_serializable_obj.md#function-saveforrollback) () <br> |
















































































## Detailed Description


An "alias" for an existing state. Allows giving different conditions for entering an existing state. 


    
## Public Attributes Documentation




### variable StateToEnter 

```C++
FGameplayTag UStateAlias::StateToEnter;
```




<hr>
## Public Functions Documentation




### function CallExec 

```C++
inline virtual void UStateAlias::CallExec () override
```



Wrapper for Exec function that sets CelIndex to zero. 


        
Implements [*UState::CallExec*](class_u_state.md#function-callexec)


<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/NightSkyEngine/Battle/Script/StateAlias.h`

