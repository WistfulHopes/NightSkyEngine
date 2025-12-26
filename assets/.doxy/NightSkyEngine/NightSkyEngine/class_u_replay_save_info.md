

# Class UReplaySaveInfo



[**ClassList**](annotated.md) **>** [**UReplaySaveInfo**](class_u_replay_save_info.md)








Inherits the following classes: [UNightSkySaveInfo](class_u_night_sky_save_info.md)






















## Public Attributes

| Type | Name |
| ---: | :--- |
|  [**FBattleData**](struct_f_battle_data.md) | [**BattleData**](#variable-battledata)  <br> |
|  TArray&lt; int32 &gt; | [**InputsP1**](#variable-inputsp1)  <br> |
|  TArray&lt; int32 &gt; | [**InputsP2**](#variable-inputsp2)  <br> |
|  int32 | [**LengthInFrames**](#variable-lengthinframes)  <br> |
|  int32 | [**ReplayIndex**](#variable-replayindex)  <br> |
|  FDateTime | [**Timestamp**](#variable-timestamp)  <br> |
|  FString | [**Version**](#variable-version)  <br> |
|  bool | [**bIsTraining**](#variable-bistraining)  <br> |


## Public Attributes inherited from UNightSkySaveInfo

See [UNightSkySaveInfo](class_u_night_sky_save_info.md)

| Type | Name |
| ---: | :--- |
|  TArray&lt; uint8 &gt; | [**Data**](class_u_night_sky_save_info.md#variable-data)  <br> |
|  TArray&lt; [**FObjectRecord**](struct_f_object_record.md) &gt; | [**ObjectRecords**](class_u_night_sky_save_info.md#variable-objectrecords)  <br> |
|  TArray&lt; UObject \* &gt; | [**PersistentOuters**](class_u_night_sky_save_info.md#variable-persistentouters)  <br> |
|  TArray&lt; UObject \* &gt; | [**TempObjects**](class_u_night_sky_save_info.md#variable-tempobjects)  <br> |






























## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**UReplaySaveInfo**](#function-ureplaysaveinfo) () <br> |


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




### variable BattleData 

```C++
FBattleData UReplaySaveInfo::BattleData;
```




<hr>



### variable InputsP1 

```C++
TArray<int32> UReplaySaveInfo::InputsP1;
```




<hr>



### variable InputsP2 

```C++
TArray<int32> UReplaySaveInfo::InputsP2;
```




<hr>



### variable LengthInFrames 

```C++
int32 UReplaySaveInfo::LengthInFrames;
```




<hr>



### variable ReplayIndex 

```C++
int32 UReplaySaveInfo::ReplayIndex;
```




<hr>



### variable Timestamp 

```C++
FDateTime UReplaySaveInfo::Timestamp;
```




<hr>



### variable Version 

```C++
FString UReplaySaveInfo::Version;
```




<hr>



### variable bIsTraining 

```C++
bool UReplaySaveInfo::bIsTraining;
```




<hr>
## Public Functions Documentation




### function UReplaySaveInfo 

```C++
inline UReplaySaveInfo::UReplaySaveInfo () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/NightSkyEngine/Miscellaneous/ReplayInfo.h`

