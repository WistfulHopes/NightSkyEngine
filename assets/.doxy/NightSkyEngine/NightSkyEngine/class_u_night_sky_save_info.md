

# Class UNightSkySaveInfo



[**ClassList**](annotated.md) **>** [**UNightSkySaveInfo**](class_u_night_sky_save_info.md)








Inherits the following classes: USaveGame


Inherited by the following classes: [UNightSkySettingsInfo](class_u_night_sky_settings_info.md),  [UReplaySaveInfo](class_u_replay_save_info.md)
















## Public Attributes

| Type | Name |
| ---: | :--- |
|  TArray&lt; uint8 &gt; | [**Data**](#variable-data)  <br> |
|  TArray&lt; [**FObjectRecord**](struct_f_object_record.md) &gt; | [**ObjectRecords**](#variable-objectrecords)  <br> |
|  TArray&lt; UObject \* &gt; | [**PersistentOuters**](#variable-persistentouters)  <br> |
|  TArray&lt; UObject \* &gt; | [**TempObjects**](#variable-tempobjects)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**ActorArraySaver**](#function-actorarraysaver) (UPARAM(ref) TArray&lt; AActor \* &gt; & SaveActors) <br> |
|  void | [**ActorPreloader**](#function-actorpreloader) (AActor \* WorldActor, [**FObjectRecord**](struct_f_object_record.md) & ActorRecord) <br> |
|  void | [**ActorSaver**](#function-actorsaver) (AActor \* SaveActor) <br> |
|  void | [**LoadData**](#function-loaddata) (UObject \* Object, UPARAM(ref) TArray&lt; uint8 &gt; & InData) <br> |
|  void | [**SaveData**](#function-savedata) (UObject \* Object, TArray&lt; uint8 &gt; & InData) <br> |
|  void | [**UObjectArraySaver**](#function-uobjectarraysaver) (UPARAM(ref) TArray&lt; UObject \* &gt; & SaveObjects) <br> |
|  void | [**UObjectDataLoader**](#function-uobjectdataloader) () <br> |
|  void | [**UObjectSaver**](#function-uobjectsaver) (UObject \* SaveObject) <br> |
|  void | [**UObjectsPreloader**](#function-uobjectspreloader) (AActor \* WorldActor) <br> |




























## Public Attributes Documentation




### variable Data 

```C++
TArray<uint8> UNightSkySaveInfo::Data;
```




<hr>



### variable ObjectRecords 

```C++
TArray<FObjectRecord> UNightSkySaveInfo::ObjectRecords;
```




<hr>



### variable PersistentOuters 

```C++
TArray<UObject*> UNightSkySaveInfo::PersistentOuters;
```




<hr>



### variable TempObjects 

```C++
TArray<UObject*> UNightSkySaveInfo::TempObjects;
```




<hr>
## Public Functions Documentation




### function ActorArraySaver 

```C++
void UNightSkySaveInfo::ActorArraySaver (
    UPARAM(ref) TArray< AActor * > & SaveActors
) 
```




<hr>



### function ActorPreloader 

```C++
void UNightSkySaveInfo::ActorPreloader (
    AActor * WorldActor,
    FObjectRecord & ActorRecord
) 
```




<hr>



### function ActorSaver 

```C++
void UNightSkySaveInfo::ActorSaver (
    AActor * SaveActor
) 
```




<hr>



### function LoadData 

```C++
void UNightSkySaveInfo::LoadData (
    UObject * Object,
    UPARAM(ref) TArray< uint8 > & InData
) 
```




<hr>



### function SaveData 

```C++
void UNightSkySaveInfo::SaveData (
    UObject * Object,
    TArray< uint8 > & InData
) 
```




<hr>



### function UObjectArraySaver 

```C++
void UNightSkySaveInfo::UObjectArraySaver (
    UPARAM(ref) TArray< UObject * > & SaveObjects
) 
```




<hr>



### function UObjectDataLoader 

```C++
void UNightSkySaveInfo::UObjectDataLoader () 
```




<hr>



### function UObjectSaver 

```C++
void UNightSkySaveInfo::UObjectSaver (
    UObject * SaveObject
) 
```




<hr>



### function UObjectsPreloader 

```C++
void UNightSkySaveInfo::UObjectsPreloader (
    AActor * WorldActor
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/NightSkyEngine/Miscellaneous/NightSkySaveInfo.h`

