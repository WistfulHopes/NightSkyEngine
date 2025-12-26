

# Class UNightSkySettingsInfo



[**ClassList**](annotated.md) **>** [**UNightSkySettingsInfo**](class_u_night_sky_settings_info.md)








Inherits the following classes: [UNightSkySaveInfo](class_u_night_sky_save_info.md)






















## Public Attributes

| Type | Name |
| ---: | :--- |
|  int32 | [**AntiAliasingMethod**](#variable-antialiasingmethod)  <br> |
|  int32 | [**GlobalIlluminationMethod**](#variable-globalilluminationmethod)  <br> |


## Public Attributes inherited from UNightSkySaveInfo

See [UNightSkySaveInfo](class_u_night_sky_save_info.md)

| Type | Name |
| ---: | :--- |
|  TArray&lt; uint8 &gt; | [**Data**](class_u_night_sky_save_info.md#variable-data)  <br> |
|  TArray&lt; [**FObjectRecord**](struct_f_object_record.md) &gt; | [**ObjectRecords**](class_u_night_sky_save_info.md#variable-objectrecords)  <br> |
|  TArray&lt; UObject \* &gt; | [**PersistentOuters**](class_u_night_sky_save_info.md#variable-persistentouters)  <br> |
|  TArray&lt; UObject \* &gt; | [**TempObjects**](class_u_night_sky_save_info.md#variable-tempobjects)  <br> |
































## Public Functions inherited from UNightSkySaveInfo

See [UNightSkySaveInfo](class_u_night_sky_save_info.md)

| Type | Name |
| ---: | :--- |
|  void | [**ActorArraySaver**](class_u_night_sky_save_info.md#function-actorarraysaver) (UPARAM(ref) TArray&lt; AActor \* &gt; & SaveActors) <br> |
|  void | [**ActorPreloader**](class_u_night_sky_save_info.md#function-actorpreloader) (AActor \* WorldActor, [**FObjectRecord**](struct_f_object_record.md) & ActorRecord) <br> |
|  void | [**ActorSaver**](class_u_night_sky_save_info.md#function-actorsaver) (AActor \* SaveActor) <br> |
|  void | [**LoadData**](class_u_night_sky_save_info.md#function-loaddata) (UObject \* Object, UPARAM(ref) TArray&lt; uint8 &gt; & InData) <br> |
|  void | [**SaveData**](class_u_night_sky_save_info.md#function-savedata) (UObject \* Object, TArray&lt; uint8 &gt; & InData) <br> |
|  void | [**UObjectArraySaver**](class_u_night_sky_save_info.md#function-uobjectarraysaver) (UPARAM(ref) TArray&lt; UObject \* &gt; & SaveObjects) <br> |
|  void | [**UObjectDataLoader**](class_u_night_sky_save_info.md#function-uobjectdataloader) () <br> |
|  void | [**UObjectSaver**](class_u_night_sky_save_info.md#function-uobjectsaver) (UObject \* SaveObject) <br> |
|  void | [**UObjectsPreloader**](class_u_night_sky_save_info.md#function-uobjectspreloader) (AActor \* WorldActor) <br> |






















































## Public Attributes Documentation




### variable AntiAliasingMethod 

```C++
int32 UNightSkySettingsInfo::AntiAliasingMethod;
```




<hr>



### variable GlobalIlluminationMethod 

```C++
int32 UNightSkySettingsInfo::GlobalIlluminationMethod;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/NightSkyEngine/Miscellaneous/NightSkySettingsInfo.h`

