

# Struct FInputCondition



[**ClassList**](annotated.md) **>** [**FInputCondition**](struct_f_input_condition.md)



[More...](#detailed-description)

* `#include <State.h>`





















## Public Attributes

| Type | Name |
| ---: | :--- |
|  TArray&lt; TEnumAsByte&lt; EInputFlags &gt; &gt; | [**DisallowedInputs**](#variable-disallowedinputs)  <br> |
|  int | [**ImpreciseInputCount**](#variable-impreciseinputcount)   = `0`<br> |
|  EInputMethod | [**Method**](#variable-method)   = `EInputMethod::Normal`<br> |
|  TArray&lt; [**FInputBitmask**](struct_f_input_bitmask.md) &gt; | [**Sequence**](#variable-sequence)  <br> |












































## Detailed Description


Contains an input condition. 


    
## Public Attributes Documentation




### variable DisallowedInputs 

```C++
TArray<TEnumAsByte<EInputFlags> > FInputCondition::DisallowedInputs;
```



Disallowed inputs. If any inputs in this array are detected, the entire condition is invalidated. 


        

<hr>



### variable ImpreciseInputCount 

```C++
int FInputCondition::ImpreciseInputCount;
```



This value determines how many imprecise inputs are allowed in this condition. An imprecise input is a diagonal input that matches the cardinal direction. For use with the Strict or Once Strict input methods. 


        

<hr>



### variable Method 

```C++
EInputMethod FInputCondition::Method;
```



The input method used for this condition. 


        

<hr>



### variable Sequence 

```C++
TArray<FInputBitmask> FInputCondition::Sequence;
```



A sequence of input bitmasks. Depending on lenience, the amount of time between inputs is increased or decreased. 


        

<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/NightSkyEngine/Battle/Script/State.h`

