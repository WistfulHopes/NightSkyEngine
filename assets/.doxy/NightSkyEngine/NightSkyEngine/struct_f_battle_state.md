

# Struct FBattleState



[**ClassList**](annotated.md) **>** [**FBattleState**](struct_f_battle_state.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  int32 | [**ActiveObjectCount**](#variable-activeobjectcount)   = `0`<br> |
|  [**FAudioChannel**](struct_f_audio_channel.md) | [**AnnouncerVoiceChannel**](#variable-announcervoicechannel)  <br> |
|  int32 | [**AssistCooldown**](#variable-assistcooldown)   = `180`<br> |
|  EBattleFormat | [**BattleFormat**](#variable-battleformat)   = `EBattleFormat::Rounds`<br> |
|  EBattlePhase | [**BattlePhase**](#variable-battlephase)   = `EBattlePhase::Intro`<br> |
|  char | [**BattleStateSync**](#variable-battlestatesync)  <br> |
|  char | [**BattleStateSyncEnd**](#variable-battlestatesyncend)  <br> |
|  FVector | [**CameraPosition**](#variable-cameraposition)   = `FVector()`<br> |
|  [**FAudioChannel**](struct_f_audio_channel.md) | [**CharaAudioChannels**](#variable-charaaudiochannels)  <br> |
|  [**FAudioChannel**](struct_f_audio_channel.md) | [**CharaVoiceChannels**](#variable-charavoicechannels)  <br> |
|  [**FAudioChannel**](struct_f_audio_channel.md) | [**CommonAudioChannels**](#variable-commonaudiochannels)  <br> |
|  EIntroSide | [**CurrentIntroSide**](#variable-currentintroside)   = `INT\_None`<br> |
|  int32 | [**CurrentSequenceTime**](#variable-currentsequencetime)   = `-1`<br> |
|  TEnumAsByte&lt; EWinSide &gt; | [**CurrentWinSide**](#variable-currentwinside)   = `WIN\_None`<br> |
|  int32 | [**FadeTimer**](#variable-fadetimer)  <br> |
|  int32 | [**FrameNumber**](#variable-framenumber)   = `0`<br> |
|  TArray&lt; int32 &gt; | [**GaugeP1**](#variable-gaugep1)  <br> |
|  TArray&lt; int32 &gt; | [**GaugeP2**](#variable-gaugep2)  <br> |
|  bool | [**IsPlayingSequence**](#variable-isplayingsequence)   = `false`<br> |
|  [**APlayerObject**](class_a_player_object.md) \* | [**MainPlayer**](#variable-mainplayer)  <br> |
|  int32 | [**MaxFadeTimer**](#variable-maxfadetimer)   = `12`<br> |
|  TArray&lt; int32 &gt; | [**MaxGauge**](#variable-maxgauge)  <br> |
|  int32 | [**MaxMeter**](#variable-maxmeter)   = `{10000, 10000}`<br> |
|  int32 | [**MaxRoundCount**](#variable-maxroundcount)  <br> |
|  int32 | [**MaxTimeUntilRoundStart**](#variable-maxtimeuntilroundstart)  <br> |
|  int32 | [**Meter**](#variable-meter)   = `{0, 0}`<br> |
|  [**FAudioChannel**](struct_f_audio_channel.md) | [**MusicChannel**](#variable-musicchannel)  <br> |
|  float | [**OrthoBlendActive**](#variable-orthoblendactive)  <br> |
|  int32 | [**P1RoundsWon**](#variable-p1roundswon)   = `0`<br> |
|  int32 | [**P2RoundsWon**](#variable-p2roundswon)   = `0`<br> |
|  bool | [**PauseParticles**](#variable-pauseparticles)   = `false`<br> |
|  bool | [**PauseTimer**](#variable-pausetimer)   = `false`<br> |
|  [**FRandomManager**](struct_f_random_manager.md) | [**RandomManager**](#variable-randommanager)  <br> |
|  int32 | [**RoundCount**](#variable-roundcount)   = `0`<br> |
|  int32 | [**RoundStartPos**](#variable-roundstartpos)   = `297500`<br> |
|  int32 | [**RoundTimer**](#variable-roundtimer)   = `0`<br> |
|  [**FScreenData**](struct_f_screen_data.md) | [**ScreenData**](#variable-screendata)  <br> |
|  [**ABattleObject**](class_a_battle_object.md) \* | [**SuperFreezeCaller**](#variable-superfreezecaller)   = `nullptr`<br> |
|  int32 | [**SuperFreezeDuration**](#variable-superfreezeduration)   = `0`<br> |
|  int32 | [**SuperFreezeSelfDuration**](#variable-superfreezeselfduration)   = `0`<br> |
|  int32 | [**TagCooldown**](#variable-tagcooldown)   = `300`<br> |
|  [**FTeamData**](struct_f_team_data.md) | [**TeamData**](#variable-teamdata)  <br> |
|  int32 | [**TimeUntilRoundStart**](#variable-timeuntilroundstart)   = `0`<br> |
|  bool | [**bHUDVisible**](#variable-bhudvisible)   = `true`<br> |












































## Public Attributes Documentation




### variable ActiveObjectCount 

```C++
int32 FBattleState::ActiveObjectCount;
```




<hr>



### variable AnnouncerVoiceChannel 

```C++
FAudioChannel FBattleState::AnnouncerVoiceChannel;
```




<hr>



### variable AssistCooldown 

```C++
int32 FBattleState::AssistCooldown;
```




<hr>



### variable BattleFormat 

```C++
EBattleFormat FBattleState::BattleFormat;
```




<hr>



### variable BattlePhase 

```C++
EBattlePhase FBattleState::BattlePhase;
```




<hr>



### variable BattleStateSync 

```C++
char FBattleState::BattleStateSync;
```




<hr>



### variable BattleStateSyncEnd 

```C++
char FBattleState::BattleStateSyncEnd;
```




<hr>



### variable CameraPosition 

```C++
FVector FBattleState::CameraPosition;
```




<hr>



### variable CharaAudioChannels 

```C++
FAudioChannel FBattleState::CharaAudioChannels[CharaAudioChannelCount];
```




<hr>



### variable CharaVoiceChannels 

```C++
FAudioChannel FBattleState::CharaVoiceChannels[CharaVoiceChannelCount];
```




<hr>



### variable CommonAudioChannels 

```C++
FAudioChannel FBattleState::CommonAudioChannels[CommonAudioChannelCount];
```




<hr>



### variable CurrentIntroSide 

```C++
EIntroSide FBattleState::CurrentIntroSide;
```




<hr>



### variable CurrentSequenceTime 

```C++
int32 FBattleState::CurrentSequenceTime;
```




<hr>



### variable CurrentWinSide 

```C++
TEnumAsByte<EWinSide> FBattleState::CurrentWinSide;
```




<hr>



### variable FadeTimer 

```C++
int32 FBattleState::FadeTimer;
```




<hr>



### variable FrameNumber 

```C++
int32 FBattleState::FrameNumber;
```




<hr>



### variable GaugeP1 

```C++
TArray<int32> FBattleState::GaugeP1;
```




<hr>



### variable GaugeP2 

```C++
TArray<int32> FBattleState::GaugeP2;
```




<hr>



### variable IsPlayingSequence 

```C++
bool FBattleState::IsPlayingSequence;
```




<hr>



### variable MainPlayer 

```C++
APlayerObject* FBattleState::MainPlayer[2];
```




<hr>



### variable MaxFadeTimer 

```C++
int32 FBattleState::MaxFadeTimer;
```




<hr>



### variable MaxGauge 

```C++
TArray<int32> FBattleState::MaxGauge;
```




<hr>



### variable MaxMeter 

```C++
int32 FBattleState::MaxMeter[2];
```




<hr>



### variable MaxRoundCount 

```C++
int32 FBattleState::MaxRoundCount;
```




<hr>



### variable MaxTimeUntilRoundStart 

```C++
int32 FBattleState::MaxTimeUntilRoundStart;
```




<hr>



### variable Meter 

```C++
int32 FBattleState::Meter[2];
```




<hr>



### variable MusicChannel 

```C++
FAudioChannel FBattleState::MusicChannel;
```




<hr>



### variable OrthoBlendActive 

```C++
float FBattleState::OrthoBlendActive;
```




<hr>



### variable P1RoundsWon 

```C++
int32 FBattleState::P1RoundsWon;
```




<hr>



### variable P2RoundsWon 

```C++
int32 FBattleState::P2RoundsWon;
```




<hr>



### variable PauseParticles 

```C++
bool FBattleState::PauseParticles;
```




<hr>



### variable PauseTimer 

```C++
bool FBattleState::PauseTimer;
```




<hr>



### variable RandomManager 

```C++
FRandomManager FBattleState::RandomManager;
```




<hr>



### variable RoundCount 

```C++
int32 FBattleState::RoundCount;
```




<hr>



### variable RoundStartPos 

```C++
int32 FBattleState::RoundStartPos;
```




<hr>



### variable RoundTimer 

```C++
int32 FBattleState::RoundTimer;
```




<hr>



### variable ScreenData 

```C++
FScreenData FBattleState::ScreenData;
```




<hr>



### variable SuperFreezeCaller 

```C++
ABattleObject* FBattleState::SuperFreezeCaller;
```




<hr>



### variable SuperFreezeDuration 

```C++
int32 FBattleState::SuperFreezeDuration;
```




<hr>



### variable SuperFreezeSelfDuration 

```C++
int32 FBattleState::SuperFreezeSelfDuration;
```




<hr>



### variable TagCooldown 

```C++
int32 FBattleState::TagCooldown;
```




<hr>



### variable TeamData 

```C++
FTeamData FBattleState::TeamData[2];
```




<hr>



### variable TimeUntilRoundStart 

```C++
int32 FBattleState::TimeUntilRoundStart;
```




<hr>



### variable bHUDVisible 

```C++
bool FBattleState::bHUDVisible;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/NightSkyEngine/Battle/NightSkyGameState.h`

