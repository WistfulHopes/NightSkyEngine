

# Class USubroutine



[**ClassList**](annotated.md) **>** [**USubroutine**](class_u_subroutine.md)



_A subroutine callable from any player or object state._ [More...](#detailed-description)

* `#include <Subroutine.h>`



Inherits the following classes: [USerializableObj](class_u_serializable_obj.md)






















## Public Attributes

| Type | Name |
| ---: | :--- |
|  FGameplayTag | [**Name**](#variable-name)  <br> |
|  [**ABattleObject**](class_a_battle_object.md) \* | [**Parent**](#variable-parent)  <br> |
































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


Allows encapsulating commonly used code that can be reused in states. 


    
## Public Attributes Documentation




### variable Name 

```C++
FGameplayTag USubroutine::Name;
```



The name of the subroutine. Used to call the subroutine. 


        

<hr>



### variable Parent 

```C++
ABattleObject* USubroutine::Parent;
```



The object that currently owns this subroutine instance. The last object to use this subroutine will be the owner. 


        

<hr>
## Public Functions Documentation




### function Exec 

```C++
void USubroutine::Exec () 
```



The primary function of the subroutine. 


        

<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/NightSkyEngine/Battle/Script/Subroutine.h`

