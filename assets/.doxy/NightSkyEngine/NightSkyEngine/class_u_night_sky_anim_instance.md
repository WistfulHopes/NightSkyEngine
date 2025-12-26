

# Class UNightSkyAnimInstance



[**ClassList**](annotated.md) **>** [**UNightSkyAnimInstance**](class_u_night_sky_anim_instance.md)








Inherits the following classes: UAnimInstance


















## Public Attributes

| Type | Name |
| ---: | :--- |
|  float | [**CurrentAnimTime**](#variable-currentanimtime)  <br> |
|  UAnimMontage \* | [**RootMontage**](#variable-rootmontage)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**CreateRootMontage**](#function-createrootmontage) (UAnimSequenceBase \* Asset, const FAlphaBlendArgs & BlendIn, const FAlphaBlendArgs & BlendOut) <br> |
























## Protected Functions

| Type | Name |
| ---: | :--- |
| virtual void | [**Montage\_Advance**](#function-montage_advance) (float DeltaSeconds) override<br> |




## Public Attributes Documentation




### variable CurrentAnimTime 

```C++
float UNightSkyAnimInstance::CurrentAnimTime;
```




<hr>



### variable RootMontage 

```C++
UAnimMontage* UNightSkyAnimInstance::RootMontage;
```




<hr>
## Public Functions Documentation




### function CreateRootMontage 

```C++
void UNightSkyAnimInstance::CreateRootMontage (
    UAnimSequenceBase * Asset,
    const FAlphaBlendArgs & BlendIn,
    const FAlphaBlendArgs & BlendOut
) 
```




<hr>
## Protected Functions Documentation




### function Montage\_Advance 

```C++
virtual void UNightSkyAnimInstance::Montage_Advance (
    float DeltaSeconds
) override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/NightSkyEngine/Battle/Animation/NightSkyAnimInstance.h`

