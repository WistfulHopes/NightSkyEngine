

# Struct FCollisionBox



[**ClassList**](annotated.md) **>** [**FCollisionBox**](struct_f_collision_box.md)



_A collision box._ [More...](#detailed-description)

* `#include <CollisionBox.h>`





















## Public Attributes

| Type | Name |
| ---: | :--- |
|  FGameplayTag | [**CustomType**](#variable-customtype)  <br> |
|  int32 | [**PosX**](#variable-posx)   = `0`<br> |
|  int32 | [**PosY**](#variable-posy)   = `0`<br> |
|  int32 | [**SizeX**](#variable-sizex)   = `0`<br> |
|  int32 | [**SizeY**](#variable-sizey)   = `0`<br> |
|  TEnumAsByte&lt; EBoxType &gt; | [**Type**](#variable-type)   = `BOX\_Hurt`<br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  bool | [**operator!=**](#function-operator) (const [**FCollisionBox**](struct_f_collision_box.md) & OtherBox) const<br> |




























## Detailed Description


Primarily used for push and hit collision, but some box types are used for specific operations. 


    
## Public Attributes Documentation




### variable CustomType 

```C++
FGameplayTag FCollisionBox::CustomType;
```



The custom box type. Used with BOX\_Custom to define custom box behaviors. 


        

<hr>



### variable PosX 

```C++
int32 FCollisionBox::PosX;
```



X position. 


        

<hr>



### variable PosY 

```C++
int32 FCollisionBox::PosY;
```



Y position. 


        

<hr>



### variable SizeX 

```C++
int32 FCollisionBox::SizeX;
```



X size. 


        

<hr>



### variable SizeY 

```C++
int32 FCollisionBox::SizeY;
```



Y size. 


        

<hr>



### variable Type 

```C++
TEnumAsByte<EBoxType> FCollisionBox::Type;
```



The type of box. 


        

<hr>
## Public Functions Documentation




### function operator!= 

```C++
inline bool FCollisionBox::operator!= (
    const FCollisionBox & OtherBox
) const
```



Compares against another collision box for inequality.




**Parameters:**


* `OtherBox` The box to compare against. 



**Returns:**

If any of the fields of the other box are different, return true. Otherwise return false. 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/NightSkyEngine/Battle/Misc/CollisionBox.h`

