

# Class UNightSkyGameInstance



[**ClassList**](annotated.md) **>** [**UNightSkyGameInstance**](class_u_night_sky_game_instance.md)








Inherits the following classes: UGameInstance


















## Public Attributes

| Type | Name |
| ---: | :--- |
|  TObjectPtr&lt; [**USoundData**](class_u_sound_data.md) &gt; | [**AnnouncerData**](#variable-announcerdata)  <br> |
|  [**FBattleData**](struct_f_battle_data.md) | [**BattleData**](#variable-battledata)  <br> |
|  FString | [**BattleVersion**](#variable-battleversion)  <br> |
|  TEnumAsByte&lt; EFighterRunners &gt; | [**FighterRunner**](#variable-fighterrunner)  <br> |
|  bool | [**FinishedLoadingForNetworkBattle**](#variable-finishedloadingfornetworkbattle)   = `false`<br> |
|  FString | [**GameVersion**](#variable-gameversion)  <br> |
|  bool | [**IsCPUBattle**](#variable-iscpubattle)   = `false`<br> |
|  bool | [**IsReplay**](#variable-isreplay)   = `false`<br> |
|  bool | [**IsTraining**](#variable-istraining)   = `false`<br> |
|  TObjectPtr&lt; [**USoundData**](class_u_sound_data.md) &gt; | [**MusicData**](#variable-musicdata)  <br> |
|  int | [**PlayerIndex**](#variable-playerindex)  <br> |
|  TArray&lt; [**UReplaySaveInfo**](class_u_replay_save_info.md) \* &gt; | [**ReplayList**](#variable-replaylist)  <br> |
|  TObjectPtr&lt; [**UNightSkySettingsInfo**](class_u_night_sky_settings_info.md) &gt; | [**SettingsInfo**](#variable-settingsinfo)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**DeleteReplay**](#function-deletereplay) (const FString & ReplayName) <br> |
|  void | [**EndRecordReplay**](#function-endrecordreplay) () const<br> |
|  void | [**FindReplays**](#function-findreplays) () <br> |
|  void | [**LoadReplay**](#function-loadreplay) () <br> |
|  void | [**PlayReplayFromBP**](#function-playreplayfrombp) (FString ReplayName) <br> |
|  void | [**PlayReplayToGameState**](#function-playreplaytogamestate) (int32 FrameNumber, int32 & OutP1Input, int32 & OutP2Input) const<br> |
|  void | [**RecordReplay**](#function-recordreplay) () <br> |
|  void | [**RollbackReplay**](#function-rollbackreplay) (int32 FramesToRollback) const<br> |
|  void | [**TravelToBattleMap**](#function-traveltobattlemap) () const<br> |
|  void | [**TravelToVSInfo**](#function-traveltovsinfo) () const<br> |
|  void | [**UpdateReplay**](#function-updatereplay) (int32 InputsP1, int32 InputsP2) const<br> |
























## Protected Functions

| Type | Name |
| ---: | :--- |
|  void | [**BP\_OnFindReplaysComplete**](#function-bp_onfindreplayscomplete) (const TArray&lt; [**UReplaySaveInfo**](class_u_replay_save_info.md) \* &gt; & AllReplays) <br> |




## Public Attributes Documentation




### variable AnnouncerData 

```C++
TObjectPtr<USoundData> UNightSkyGameInstance::AnnouncerData;
```




<hr>



### variable BattleData 

```C++
FBattleData UNightSkyGameInstance::BattleData;
```




<hr>



### variable BattleVersion 

```C++
FString UNightSkyGameInstance::BattleVersion;
```




<hr>



### variable FighterRunner 

```C++
TEnumAsByte<EFighterRunners> UNightSkyGameInstance::FighterRunner;
```




<hr>



### variable FinishedLoadingForNetworkBattle 

```C++
bool UNightSkyGameInstance::FinishedLoadingForNetworkBattle;
```




<hr>



### variable GameVersion 

```C++
FString UNightSkyGameInstance::GameVersion;
```




<hr>



### variable IsCPUBattle 

```C++
bool UNightSkyGameInstance::IsCPUBattle;
```




<hr>



### variable IsReplay 

```C++
bool UNightSkyGameInstance::IsReplay;
```




<hr>



### variable IsTraining 

```C++
bool UNightSkyGameInstance::IsTraining;
```




<hr>



### variable MusicData 

```C++
TObjectPtr<USoundData> UNightSkyGameInstance::MusicData;
```




<hr>



### variable PlayerIndex 

```C++
int UNightSkyGameInstance::PlayerIndex;
```




<hr>



### variable ReplayList 

```C++
TArray<UReplaySaveInfo*> UNightSkyGameInstance::ReplayList;
```




<hr>



### variable SettingsInfo 

```C++
TObjectPtr<UNightSkySettingsInfo> UNightSkyGameInstance::SettingsInfo;
```




<hr>
## Public Functions Documentation




### function DeleteReplay 

```C++
void UNightSkyGameInstance::DeleteReplay (
    const FString & ReplayName
) 
```



Delete a previously recorded replay 


        

<hr>



### function EndRecordReplay 

```C++
void UNightSkyGameInstance::EndRecordReplay () const
```




<hr>



### function FindReplays 

```C++
void UNightSkyGameInstance::FindReplays () 
```



Start looking for/finding replays on the hard drive 


        

<hr>



### function LoadReplay 

```C++
void UNightSkyGameInstance::LoadReplay () 
```




<hr>



### function PlayReplayFromBP 

```C++
void UNightSkyGameInstance::PlayReplayFromBP (
    FString ReplayName
) 
```



Start playback for a previously recorded Replay, from blueprint 


        

<hr>



### function PlayReplayToGameState 

```C++
void UNightSkyGameInstance::PlayReplayToGameState (
    int32 FrameNumber,
    int32 & OutP1Input,
    int32 & OutP2Input
) const
```




<hr>



### function RecordReplay 

```C++
void UNightSkyGameInstance::RecordReplay () 
```




<hr>



### function RollbackReplay 

```C++
void UNightSkyGameInstance::RollbackReplay (
    int32 FramesToRollback
) const
```




<hr>



### function TravelToBattleMap 

```C++
void UNightSkyGameInstance::TravelToBattleMap () const
```




<hr>



### function TravelToVSInfo 

```C++
void UNightSkyGameInstance::TravelToVSInfo () const
```




<hr>



### function UpdateReplay 

```C++
void UNightSkyGameInstance::UpdateReplay (
    int32 InputsP1,
    int32 InputsP2
) const
```




<hr>
## Protected Functions Documentation




### function BP\_OnFindReplaysComplete 

```C++
void UNightSkyGameInstance::BP_OnFindReplaysComplete (
    const TArray< UReplaySaveInfo * > & AllReplays
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/NightSkyEngine/Miscellaneous/NightSkyGameInstance.h`

