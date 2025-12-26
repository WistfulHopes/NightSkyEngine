

# Class UBattleExtension



[**ClassList**](annotated.md) **>** [**UBattleExtension**](class_u_battle_extension.md)



_A customizable extension to the battle ruleset._ [More...](#detailed-description)

* `#include <BattleExtension.h>`



Inherits the following classes: [USerializableObj](class_u_serializable_obj.md)






















## Public Attributes

| Type | Name |
| ---: | :--- |
|  FGameplayTag | [**Name**](#variable-name)  <br> |
|  [**ANightSkyGameState**](class_a_night_sky_game_state.md) \* | [**Parent**](#variable-parent)  <br> |
































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**Exec**](#function-exec) () <br> |


## Public Functions inherited from USerializableObj

See [USerializableObj](class_u_serializable_obj.md)

| Type | Name |
| ---: | :--- |
|  void | [**LoadForRollback**](class_u_serializable_obj.md#function-loadforrollback) (const TArray&lt; uint8 &gt; & InBytes) <br> |
|  void | [**ResetToCDO**](class_u_serializable_obj.md#function-resettocdo) () <br> |
|  TArray&lt; uint8 &gt; | [**SaveForRollback**](class_u_serializable_obj.md#function-saveforrollback) () <br> |






















































## Detailed Description


Allows modifying some general battle behavior. 


    
## Public Attributes Documentation




### variable Name 

```C++
FGameplayTag UBattleExtension::Name;
```



The name of the subroutine. Used to call the subroutine. 


        

<hr>



### variable Parent 

```C++
ANightSkyGameState* UBattleExtension::Parent;
```



The owning game state. 


        

<hr>
## Public Functions Documentation




### function Exec 

```C++
void UBattleExtension::Exec () 
```



The primary function of the subroutine. 


        

<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/NightSkyEngine/Battle/Script/BattleExtension.h`

