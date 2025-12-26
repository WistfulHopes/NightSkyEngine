

# Class UNightSkyAnimSequenceUserData



[**ClassList**](annotated.md) **>** [**UNightSkyAnimSequenceUserData**](class_u_night_sky_anim_sequence_user_data.md)








Inherits the following classes: UAssetUserData


































## Public Functions

| Type | Name |
| ---: | :--- |
|  [**FAnimVector**](struct_f_anim_vector.md) | [**GetCachedBoneLocationAtTime**](#function-getcachedbonelocationattime) (FName BoneName, int32 Time, bool bRelativeToRoot) const<br> |
|  [**FAnimTransform**](struct_f_anim_transform.md) | [**GetCachedBoneTransformAtTime**](#function-getcachedbonetransformattime) (FName BoneName, int32 Time, bool bRelativeToRoot) const<br> |
|  int32 | [**GetFrameCount**](#function-getframecount) () const<br> |
|  int32 | [**GetFrameRate**](#function-getframerate) () const<br> |
|  [**FAnimVector**](struct_f_anim_vector.md) | [**GetRootTranslationAtTime**](#function-getroottranslationattime) (int32 Time) const<br> |
| virtual void | [**PostEditChangeOwner**](#function-posteditchangeowner) (const FPropertyChangedEvent & PropertyChangedEvent) override<br> |




























## Public Functions Documentation




### function GetCachedBoneLocationAtTime 

```C++
FAnimVector UNightSkyAnimSequenceUserData::GetCachedBoneLocationAtTime (
    FName BoneName,
    int32 Time,
    bool bRelativeToRoot
) const
```




<hr>



### function GetCachedBoneTransformAtTime 

```C++
FAnimTransform UNightSkyAnimSequenceUserData::GetCachedBoneTransformAtTime (
    FName BoneName,
    int32 Time,
    bool bRelativeToRoot
) const
```




<hr>



### function GetFrameCount 

```C++
inline int32 UNightSkyAnimSequenceUserData::GetFrameCount () const
```




<hr>



### function GetFrameRate 

```C++
inline int32 UNightSkyAnimSequenceUserData::GetFrameRate () const
```




<hr>



### function GetRootTranslationAtTime 

```C++
FAnimVector UNightSkyAnimSequenceUserData::GetRootTranslationAtTime (
    int32 Time
) const
```




<hr>



### function PostEditChangeOwner 

```C++
virtual void UNightSkyAnimSequenceUserData::PostEditChangeOwner (
    const FPropertyChangedEvent & PropertyChangedEvent
) override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/NightSkyEngine/Battle/Animation/NightSkyAnimSequenceUserData.h`

