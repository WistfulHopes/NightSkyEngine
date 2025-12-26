

# Struct FInputBitmask



[**ClassList**](annotated.md) **>** [**FInputBitmask**](struct_f_input_bitmask.md)



[More...](#detailed-description)

* `#include <State.h>`





















## Public Attributes

| Type | Name |
| ---: | :--- |
|  TArray&lt; TEnumAsByte&lt; EInputFlags &gt; &gt; | [**DisallowedInputs**](#variable-disallowedinputs)  <br> |
|  int32 | [**Hold**](#variable-hold)   = `0`<br> |
|  int | [**InputFlag**](#variable-inputflag)  <br> |
|  int32 | [**Lenience**](#variable-lenience)   = `3`<br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**FInputBitmask**](#function-finputbitmask-12) () <br> |
|   | [**FInputBitmask**](#function-finputbitmask-22) (EInputFlags Input) <br> |




























## Detailed Description


A container struct for input bitmasks. 


    
## Public Attributes Documentation




### variable DisallowedInputs 

```C++
TArray<TEnumAsByte<EInputFlags> > FInputBitmask::DisallowedInputs;
```



Disallowed inputs. If any inputs in this array are detected, this input is invalidated. 


        

<hr>



### variable Hold 

```C++
int32 FInputBitmask::Hold;
```



How long the input must be held for. Unless you're creating a charge/hold input, leave as zero. Does not work with the Negative or Negative Strict input methods. 


        

<hr>



### variable InputFlag 

```C++
int FInputBitmask::InputFlag;
```



The input flag.




**See also:** EInputFlags 



        

<hr>



### variable Lenience 

```C++
int32 FInputBitmask::Lenience;
```



How much buffer time there is for the input. 


        

<hr>
## Public Functions Documentation




### function FInputBitmask [1/2]

```C++
inline FInputBitmask::FInputBitmask () 
```




<hr>



### function FInputBitmask [2/2]

```C++
inline FInputBitmask::FInputBitmask (
    EInputFlags Input
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/NightSkyEngine/Battle/Script/State.h`

