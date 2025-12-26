

# Class AAudioManager



[**ClassList**](annotated.md) **>** [**AAudioManager**](class_a_audio_manager.md)








Inherits the following classes: AActor


















## Public Attributes

| Type | Name |
| ---: | :--- |
|  UAudioComponent \* | [**AnnouncerVoicePlayer**](#variable-announcervoiceplayer)  <br> |
|  UAudioComponent \* | [**CharaAudioPlayers**](#variable-charaaudioplayers)  <br> |
|  UAudioComponent \* | [**CharaVoicePlayers**](#variable-charavoiceplayers)  <br> |
|  UAudioComponent \* | [**CommonAudioPlayers**](#variable-commonaudioplayers)  <br> |
|  UAudioComponent \* | [**MusicPlayer**](#variable-musicplayer)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**AAudioManager**](#function-aaudiomanager) () <br> |
|  void | [**PauseAllAudio**](#function-pauseallaudio) () <br> |
| virtual void | [**Tick**](#function-tick) (float DeltaTime) override<br> |
























## Protected Functions

| Type | Name |
| ---: | :--- |
| virtual void | [**BeginPlay**](#function-beginplay) () override<br> |




## Public Attributes Documentation




### variable AnnouncerVoicePlayer 

```C++
UAudioComponent* AAudioManager::AnnouncerVoicePlayer;
```




<hr>



### variable CharaAudioPlayers 

```C++
UAudioComponent* AAudioManager::CharaAudioPlayers[CharaAudioChannelCount];
```




<hr>



### variable CharaVoicePlayers 

```C++
UAudioComponent* AAudioManager::CharaVoicePlayers[CharaVoiceChannelCount];
```




<hr>



### variable CommonAudioPlayers 

```C++
UAudioComponent* AAudioManager::CommonAudioPlayers[CommonAudioChannelCount];
```




<hr>



### variable MusicPlayer 

```C++
UAudioComponent* AAudioManager::MusicPlayer;
```




<hr>
## Public Functions Documentation




### function AAudioManager 

```C++
AAudioManager::AAudioManager () 
```




<hr>



### function PauseAllAudio 

```C++
void AAudioManager::PauseAllAudio () 
```




<hr>



### function Tick 

```C++
virtual void AAudioManager::Tick (
    float DeltaTime
) override
```




<hr>
## Protected Functions Documentation




### function BeginPlay 

```C++
virtual void AAudioManager::BeginPlay () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/NightSkyEngine/Battle/Actors/AudioManager.h`

