

# Struct FInputBuffer



[**ClassList**](annotated.md) **>** [**FInputBuffer**](struct_f_input_buffer.md)



_The input buffer for a player object._ [More...](#detailed-description)

* `#include <InputBuffer.h>`





















## Public Attributes

| Type | Name |
| ---: | :--- |
|  int32 | [**InputBufferInternal**](#variable-inputbufferinternal)   = `{ 16 }`<br> |
|  int32 | [**InputTime**](#variable-inputtime)   = `{}`<br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  bool | [**CheckInputCondition**](#function-checkinputcondition) (const [**FInputCondition**](struct_f_input_condition.md) & InputCondition) <br>_Checks an input condition against the buffer._  |
|  bool | [**CheckInputSequence**](#function-checkinputsequence) () const<br> |
|  bool | [**CheckInputSequenceNegative**](#function-checkinputsequencenegative) () const<br> |
|  bool | [**CheckInputSequenceNegativeStrict**](#function-checkinputsequencenegativestrict) () const<br> |
|  bool | [**CheckInputSequenceOnce**](#function-checkinputsequenceonce) () const<br> |
|  bool | [**CheckInputSequenceOnceStrict**](#function-checkinputsequenceoncestrict) () const<br> |
|  bool | [**CheckInputSequencePressAndRelease**](#function-checkinputsequencepressandrelease) () const<br> |
|  bool | [**CheckInputSequencePressAndReleaseStrict**](#function-checkinputsequencepressandreleasestrict) () const<br> |
|  bool | [**CheckInputSequenceStrict**](#function-checkinputsequencestrict) () const<br> |
|  void | [**Emplace**](#function-emplace) (int32 Input, uint32 Index) <br>_Stores the input at an arbitrary buffer position. Intended for CPU usage._  |
|  void | [**FlipInputsInBuffer**](#function-flipinputsinbuffer) () <br> |
|  void | [**Update**](#function-update) (int32 Input, bool bStopped=false) <br>_Stores the input for this frame._  |
|  void | [**WriteInputCondition**](#function-writeinputcondition) (const [**FInputCondition**](struct_f_input_condition.md) & InputCondition) <br> |




























## Detailed Description


Stores inputs every frame, and handles input checking. 


    
## Public Attributes Documentation




### variable InputBufferInternal 

```C++
int32 FInputBuffer::InputBufferInternal[InputBufferSize];
```



All stored inputs. Inputs are stored with the newest at the end and the oldest at the beginning. 


        

<hr>



### variable InputTime 

```C++
int32 FInputBuffer::InputTime[InputBufferSize];
```



All input times. Input times are looped over and incremented every actionable frame. 


        

<hr>
## Public Functions Documentation




### function CheckInputCondition 

_Checks an input condition against the buffer._ 
```C++
bool FInputBuffer::CheckInputCondition (
    const FInputCondition & InputCondition
) 
```





**Parameters:**


* `InputCondition` The input condition to check. 



**Returns:**

If the input condition matches the buffer, return true. Otherwise return false. 





        

<hr>



### function CheckInputSequence 

```C++
bool FInputBuffer::CheckInputSequence () const
```



Checks the input sequence against the buffer with the Normal method. 

**See also:** EInputMethod


**Returns:**

If the input sequence matches the buffer, return true. Otherwise return false. 





        

<hr>



### function CheckInputSequenceNegative 

```C++
bool FInputBuffer::CheckInputSequenceNegative () const
```



Checks the input sequence against the buffer with the Negative method. 

**See also:** EInputMethod


**Returns:**

If the input sequence matches the buffer, return true. Otherwise return false. 





        

<hr>



### function CheckInputSequenceNegativeStrict 

```C++
bool FInputBuffer::CheckInputSequenceNegativeStrict () const
```



Checks the input sequence against the buffer with the Negative Strict method. 

**See also:** EInputMethod


**Returns:**

If the input sequence matches the buffer, return true. Otherwise return false. 





        

<hr>



### function CheckInputSequenceOnce 

```C++
bool FInputBuffer::CheckInputSequenceOnce () const
```



Checks the input sequence against the buffer with the Once method. 

**See also:** EInputMethod


**Returns:**

If the input sequence matches the buffer, return true. Otherwise return false. 





        

<hr>



### function CheckInputSequenceOnceStrict 

```C++
bool FInputBuffer::CheckInputSequenceOnceStrict () const
```



Checks the input sequence against the buffer with the Once Strict method. 

**See also:** EInputMethod


**Returns:**

If the input sequence matches the buffer, return true. Otherwise return false. 





        

<hr>



### function CheckInputSequencePressAndRelease 

```C++
bool FInputBuffer::CheckInputSequencePressAndRelease () const
```



Checks the input sequence against the buffer with the Once method. 

**See also:** EInputMethod


**Returns:**

If the input sequence matches the buffer, return true. Otherwise return false. 





        

<hr>



### function CheckInputSequencePressAndReleaseStrict 

```C++
bool FInputBuffer::CheckInputSequencePressAndReleaseStrict () const
```



Checks the input sequence against the buffer with the Once Strict method. 

**See also:** EInputMethod


**Returns:**

If the input sequence matches the buffer, return true. Otherwise return false. 





        

<hr>



### function CheckInputSequenceStrict 

```C++
bool FInputBuffer::CheckInputSequenceStrict () const
```



Checks the input sequence against the buffer with the Strict method. 

**See also:** EInputMethod


**Returns:**

If the input sequence matches the buffer, return true. Otherwise return false. 





        

<hr>



### function Emplace 

_Stores the input at an arbitrary buffer position. Intended for CPU usage._ 
```C++
void FInputBuffer::Emplace (
    int32 Input,
    uint32 Index
) 
```





**Parameters:**


* `Input` The input bitmask to store. 
* `Index` The index of the buffer to store at. 




        

<hr>



### function FlipInputsInBuffer 

```C++
void FInputBuffer::FlipInputsInBuffer () 
```



Flips the directional inputs in the buffer. For use after a character switches sides. 


        

<hr>



### function Update 

_Stores the input for this frame._ 
```C++
void FInputBuffer::Update (
    int32 Input,
    bool bStopped=false
) 
```





**Parameters:**


* `Input` The input bitmask to store. 
* `bStopped` If the owning object is in hitstop/super freeze. 




        

<hr>



### function WriteInputCondition 

```C++
void FInputBuffer::WriteInputCondition (
    const FInputCondition & InputCondition
) 
```



Writes an input condition to the buffer. For use with CPU. 

**Parameters:**


* `InputCondition` The input condition to write. 




        

<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/NightSkyEngine/Battle/Misc/InputBuffer.h`

