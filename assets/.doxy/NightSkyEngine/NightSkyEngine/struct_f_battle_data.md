

# Struct FBattleData



[**ClassList**](annotated.md) **>** [**FBattleData**](struct_f_battle_data.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  EBattleFormat | [**BattleFormat**](#variable-battleformat)  <br> |
|  TArray&lt; int32 &gt; | [**ColorIndicesP1**](#variable-colorindicesp1)  <br> |
|  TArray&lt; int32 &gt; | [**ColorIndicesP2**](#variable-colorindicesp2)  <br> |
|  FGameplayTag | [**MusicName**](#variable-musicname)  <br> |
|  TArray&lt; [**UPrimaryCharaData**](class_u_primary_chara_data.md) \* &gt; | [**PlayerListP1**](#variable-playerlistp1)  <br> |
|  TArray&lt; [**UPrimaryCharaData**](class_u_primary_chara_data.md) \* &gt; | [**PlayerListP2**](#variable-playerlistp2)  <br> |
|  [**FRandomManager**](struct_f_random_manager.md) | [**Random**](#variable-random)  <br> |
|  int32 | [**RoundCount**](#variable-roundcount)   = `2`<br> |
|  [**UPrimaryStageData**](class_u_primary_stage_data.md) \* | [**Stage**](#variable-stage)  <br> |
|  int32 | [**StartRoundTimer**](#variable-startroundtimer)   = `99`<br> |
|  int32 | [**TimeUntilRoundStart**](#variable-timeuntilroundstart)   = `180`<br> |
|  bool | [**bIsValid**](#variable-bisvalid)   = `false`<br> |












































## Public Attributes Documentation




### variable BattleFormat 

```C++
EBattleFormat FBattleData::BattleFormat;
```




<hr>



### variable ColorIndicesP1 

```C++
TArray<int32> FBattleData::ColorIndicesP1;
```




<hr>



### variable ColorIndicesP2 

```C++
TArray<int32> FBattleData::ColorIndicesP2;
```




<hr>



### variable MusicName 

```C++
FGameplayTag FBattleData::MusicName;
```




<hr>



### variable PlayerListP1 

```C++
TArray<UPrimaryCharaData*> FBattleData::PlayerListP1;
```




<hr>



### variable PlayerListP2 

```C++
TArray<UPrimaryCharaData*> FBattleData::PlayerListP2;
```




<hr>



### variable Random 

```C++
FRandomManager FBattleData::Random;
```




<hr>



### variable RoundCount 

```C++
int32 FBattleData::RoundCount;
```




<hr>



### variable Stage 

```C++
UPrimaryStageData* FBattleData::Stage;
```




<hr>



### variable StartRoundTimer 

```C++
int32 FBattleData::StartRoundTimer;
```




<hr>



### variable TimeUntilRoundStart 

```C++
int32 FBattleData::TimeUntilRoundStart;
```




<hr>



### variable bIsValid 

```C++
bool FBattleData::bIsValid;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/NightSkyEngine/Miscellaneous/NightSkyGameInstance.h`

