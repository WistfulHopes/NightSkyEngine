

# Class FCollisionDataDetails



[**ClassList**](annotated.md) **>** [**FCollisionDataDetails**](class_f_collision_data_details.md)



[More...](#detailed-description)

* `#include <CollisionDataDetails.h>`



Inherits the following classes: IDetailCustomization


































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual void | [**CustomizeDetails**](#function-customizedetails) (IDetailLayoutBuilder & DetailBuilder) override<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  TSharedRef&lt; IDetailCustomization &gt; | [**MakeInstance**](#function-makeinstance) () <br> |


























## Detailed Description


Detail customization for UCollisionData that displays CollisionFrames in a hierarchical tree organized by GameplayTag. 


    
## Public Functions Documentation




### function CustomizeDetails 

```C++
virtual void FCollisionDataDetails::CustomizeDetails (
    IDetailLayoutBuilder & DetailBuilder
) override
```




<hr>
## Public Static Functions Documentation




### function MakeInstance 

```C++
static TSharedRef< IDetailCustomization > FCollisionDataDetails::MakeInstance () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/CollisionEditor/Public/CollisionDataDetails.h`

