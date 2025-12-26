

# Class ANightSkyWTGameState



[**ClassList**](annotated.md) **>** [**ANightSkyWTGameState**](class_a_night_sky_w_t_game_state.md)








Inherits the following classes: [ANightSkyGameState](class_a_night_sky_game_state.md)






















## Public Attributes

| Type | Name |
| ---: | :--- |
|  FOnBattleEndDelegate | [**OnBattleEndDelegate**](#variable-onbattleenddelegate)  <br> |
|  bool | [**bIsBattling**](#variable-bisbattling)  <br> |
|  bool | [**bIsMatchEnd**](#variable-bismatchend)  <br> |


## Public Attributes inherited from ANightSkyGameState

See [ANightSkyGameState](class_a_night_sky_game_state.md)

| Type | Name |
| ---: | :--- |
|  [**AAudioManager**](class_a_audio_manager.md) \* | [**AudioManager**](class_a_night_sky_game_state.md#variable-audiomanager)   = `nullptr`<br> |
|  [**UBattleExtensionData**](class_u_battle_extension_data.md) \* | [**BattleExtensionData**](class_a_night_sky_game_state.md#variable-battleextensiondata)   = `{}`<br> |
|  TArray&lt; FGameplayTag &gt; | [**BattleExtensionNames**](class_a_night_sky_game_state.md#variable-battleextensionnames)   = `{}`<br> |
|  TArray&lt; [**UBattleExtension**](class_u_battle_extension.md) \* &gt; | [**BattleExtensions**](class_a_night_sky_game_state.md#variable-battleextensions)   = `{}`<br> |
|  [**ANightSkyBattleHudActor**](class_a_night_sky_battle_hud_actor.md) \* | [**BattleHudActor**](class_a_night_sky_game_state.md#variable-battlehudactor)   = `nullptr`<br> |
|  TSubclassOf&lt; [**ABattleObject**](class_a_battle_object.md) &gt; | [**BattleObjectClass**](class_a_night_sky_game_state.md#variable-battleobjectclass)   = `ABattleObject::StaticClass()`<br> |
|  FTransform | [**BattleSceneTransform**](class_a_night_sky_game_state.md#variable-battlescenetransform)  <br> |
|  [**FBattleState**](struct_f_battle_state.md) | [**BattleState**](class_a_night_sky_game_state.md#variable-battlestate)   = `{}`<br> |
|  ACameraActor \* | [**CameraActor**](class_a_night_sky_game_state.md#variable-cameraactor)   = `nullptr`<br> |
|  class [**AFighterLocalRunner**](class_a_fighter_local_runner.md) \* | [**FighterRunner**](class_a_night_sky_game_state.md#variable-fighterrunner)   = `nullptr`<br> |
|  class [**UNightSkyGameInstance**](class_u_night_sky_game_instance.md) \* | [**GameInstance**](class_a_night_sky_game_state.md#variable-gameinstance)   = `nullptr`<br> |
|  int32 | [**LocalFrame**](class_a_night_sky_game_state.md#variable-localframe)   = `0`<br> |
|  int | [**MaxBattleObjects**](class_a_night_sky_game_state.md#variable-maxbattleobjects)   = `400`<br> |
|  TArray&lt; [**ABattleObject**](class_a_battle_object.md) \* &gt; | [**Objects**](class_a_night_sky_game_state.md#variable-objects)   = `{}`<br> |
|  class [**AParticleManager**](class_a_particle_manager.md) \* | [**ParticleManager**](class_a_night_sky_game_state.md#variable-particlemanager)   = `nullptr`<br> |
|  TArray&lt; [**APlayerObject**](class_a_player_object.md) \* &gt; | [**Players**](class_a_night_sky_game_state.md#variable-players)   = `{}`<br> |
|  int32 | [**RemoteFrame**](class_a_night_sky_game_state.md#variable-remoteframe)   = `0`<br> |
|  class ALevelSequenceActor \* | [**SequenceActor**](class_a_night_sky_game_state.md#variable-sequenceactor)   = `nullptr`<br> |
|  ACameraActor \* | [**SequenceCameraActor**](class_a_night_sky_game_state.md#variable-sequencecameraactor)   = `nullptr`<br> |
|  TSubclassOf&lt; ACameraActor &gt; | [**SequenceCameraActorClass**](class_a_night_sky_game_state.md#variable-sequencecameraactorclass)  <br> |
|  [**APlayerObject**](class_a_player_object.md) \* | [**SequenceEnemy**](class_a_night_sky_game_state.md#variable-sequenceenemy)   = `nullptr`<br> |
|  [**APlayerObject**](class_a_player_object.md) \* | [**SequenceTarget**](class_a_night_sky_game_state.md#variable-sequencetarget)   = `nullptr`<br> |
|  TArray&lt; [**ABattleObject**](class_a_battle_object.md) \* &gt; | [**SortedObjects**](class_a_night_sky_game_state.md#variable-sortedobjects)   = `{}`<br> |
|  bool | [**bIsPlayingSequence**](class_a_night_sky_game_state.md#variable-bisplayingsequence)   = `false`<br> |
|  bool | [**bPauseGame**](class_a_night_sky_game_state.md#variable-bpausegame)   = `false`<br> |
|  bool | [**bViewCollision**](class_a_night_sky_game_state.md#variable-bviewcollision)   = `false`<br> |






























## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**ANightSkyWTGameState**](#function-anightskywtgamestate) () <br> |
|  void | [**Init**](#function-init) ([**APlayerObject**](class_a_player_object.md) \* P1, [**APlayerObject**](class_a_player_object.md) \* P2) <br> |
| virtual void | [**Tick**](#function-tick) (float DeltaTime) override<br> |


## Public Functions inherited from ANightSkyGameState

See [ANightSkyGameState](class_a_night_sky_game_state.md)

| Type | Name |
| ---: | :--- |
|   | [**ANightSkyGameState**](class_a_night_sky_game_state.md#function-anightskygamestate) () <br> |
|  [**ABattleObject**](class_a_battle_object.md) \* | [**AddBattleObject**](class_a_night_sky_game_state.md#function-addbattleobject) (const [**UState**](class_u_state.md) \* InState, int PosX, int PosY, EObjDir Dir, int32 ObjectStateIndex, bool bIsCommonState, [**APlayerObject**](class_a_player_object.md) \* Parent) const<br> |
|  void | [**AssignEnemy**](class_a_night_sky_game_state.md#function-assignenemy) () <br> |
|  void | [**BattleHudVisibility**](class_a_night_sky_game_state.md#function-battlehudvisibility) (bool Visible) <br> |
|  [**APlayerObject**](class_a_player_object.md) \* | [**CallAssist**](class_a_night_sky_game_state.md#function-callassist) (const bool IsP1, int AssistIndex, const FGameplayTag AssistName) <br> |
|  void | [**CallBattleExtension**](class_a_night_sky_game_state.md#function-callbattleextension) (FGameplayTag Name) <br> |
|  void | [**CameraShake**](class_a_night_sky_game_state.md#function-camerashake) (const TSubclassOf&lt; UCameraShakeBase &gt; & Pattern, float Scale) const<br> |
|  bool | [**CanTag**](class_a_night_sky_game_state.md#function-cantag) (const [**APlayerObject**](class_a_player_object.md) \* InPlayer, int TeamIndex) const<br> |
|  void | [**EndMatch**](class_a_night_sky_game_state.md#function-endmatch) () <br> |
|  void | [**EndMatch\_BP**](class_a_night_sky_game_state.md#function-endmatch_bp) () <br> |
|  int32 | [**GetGauge**](class_a_night_sky_game_state.md#function-getgauge) (bool IsP1, int32 GaugeIndex) const<br> |
|  int | [**GetLocalInputs**](class_a_night_sky_game_state.md#function-getlocalinputs) (int Index) const<br> |
|  [**APlayerObject**](class_a_player_object.md) \* | [**GetMainPlayer**](class_a_night_sky_game_state.md#function-getmainplayer) (bool IsP1) const<br> |
|  bool | [**GetPaused**](class_a_night_sky_game_state.md#function-getpaused) () const<br> |
|  EScreenFlag | [**GetScreenFlags**](class_a_night_sky_game_state.md#function-getscreenflags) () const<br> |
|  TArray&lt; [**APlayerObject**](class_a_player_object.md) \* &gt; | [**GetTeam**](class_a_night_sky_game_state.md#function-getteam) (bool IsP1) const<br> |
|  int32 | [**GetTeamCount**](class_a_night_sky_game_state.md#function-getteamcount) (bool bIsP1) const<br> |
|  void | [**HUDInit**](class_a_night_sky_game_state.md#function-hudinit) () const<br> |
|  bool | [**IsTagBattle**](class_a_night_sky_game_state.md#function-istagbattle) () const<br> |
|  void | [**LoadForRollback**](class_a_night_sky_game_state.md#function-loadforrollback) (const TArray&lt; uint8 &gt; & InBytes) <br> |
|  void | [**LoadGameState**](class_a_night_sky_game_state.md#function-loadgamestate) ([**FRollbackData**](struct_f_rollback_data.md) & RollbackData) <br> |
|  void | [**ManageAudio**](class_a_night_sky_game_state.md#function-manageaudio) () <br> |
|  void | [**MatchInit**](class_a_night_sky_game_state.md#function-matchinit) () <br> |
|  void | [**PlayAnnouncerVoice**](class_a_night_sky_game_state.md#function-playannouncervoice-12) (USoundBase \* InSoundWave, float MaxDuration) <br> |
|  void | [**PlayAnnouncerVoice**](class_a_night_sky_game_state.md#function-playannouncervoice-22) (const FGameplayTag Name) <br> |
|  void | [**PlayCharaAudio**](class_a_night_sky_game_state.md#function-playcharaaudio) (USoundBase \* InSoundWave, float MaxDuration) <br> |
|  void | [**PlayCommonAudio**](class_a_night_sky_game_state.md#function-playcommonaudio) (USoundBase \* InSoundWave, float MaxDuration) <br> |
|  void | [**PlayLevelSequence**](class_a_night_sky_game_state.md#function-playlevelsequence) ([**APlayerObject**](class_a_player_object.md) \* Target, [**APlayerObject**](class_a_player_object.md) \* Enemy, ULevelSequence \* Sequence) <br> |
|  void | [**PlayMusic**](class_a_night_sky_game_state.md#function-playmusic-12) (USoundBase \* InSoundWave, float MaxDuration) <br> |
|  void | [**PlayMusic**](class_a_night_sky_game_state.md#function-playmusic-22) (const FGameplayTag Name) <br> |
|  void | [**PlayVoiceLine**](class_a_night_sky_game_state.md#function-playvoiceline) (USoundBase \* InSoundWave, float MaxDuration, int Player) <br> |
|  void | [**RollbackStartAudio**](class_a_night_sky_game_state.md#function-rollbackstartaudio) (int32 InFrame) <br> |
|  void | [**RoundInit**](class_a_night_sky_game_state.md#function-roundinit) () <br> |
|  TArray&lt; uint8 &gt; | [**SaveForRollback**](class_a_night_sky_game_state.md#function-saveforrollback) () <br> |
|  void | [**SaveGameState**](class_a_night_sky_game_state.md#function-savegamestate) ([**FRollbackData**](struct_f_rollback_data.md) & RollbackData, int32 \* InChecksum) <br> |
|  void | [**ScreenPosToWorldPos**](class_a_night_sky_game_state.md#function-screenpostoworldpos) (int32 X, int32 Y, int32 & OutX, int32 & OutY) const<br> |
|  void | [**SetDrawPriorityBack**](class_a_night_sky_game_state.md#function-setdrawpriorityback) ([**ABattleObject**](class_a_battle_object.md) \* InObject) const<br> |
|  void | [**SetDrawPriorityFront**](class_a_night_sky_game_state.md#function-setdrawpriorityfront) ([**ABattleObject**](class_a_battle_object.md) \* InObject) const<br> |
|  void | [**SetGauge**](class_a_night_sky_game_state.md#function-setgauge) (bool IsP1, int32 GaugeIndex, int32 Value) <br> |
|  void | [**SetOtherChecksum**](class_a_night_sky_game_state.md#function-setotherchecksum) (uint32 RemoteChecksum, int32 InFrame) <br> |
|  void | [**SetPaused**](class_a_night_sky_game_state.md#function-setpaused) (bool bPause) <br> |
|  void | [**SetScreenBounds**](class_a_night_sky_game_state.md#function-setscreenbounds) () const<br> |
|  void | [**SetScreenCorners**](class_a_night_sky_game_state.md#function-setscreencorners) () <br> |
|  void | [**SetScreenFlags**](class_a_night_sky_game_state.md#function-setscreenflags) (UPARAM(meta=(Bitmask, BitmaskEnum="/Script/NightSkyEngine.EScreenFlag")) int32 InFlags) <br> |
|  void | [**SetTeamCooldown**](class_a_night_sky_game_state.md#function-setteamcooldown) (const bool IsP1, const int TeamIndex, const int Cooldown) <br> |
|  void | [**StartSuperFreeze**](class_a_night_sky_game_state.md#function-startsuperfreeze) (int32 Duration, int32 SelfDuration, [**ABattleObject**](class_a_battle_object.md) \* CallingObject) <br> |
|  void | [**StopLevelSequence**](class_a_night_sky_game_state.md#function-stoplevelsequence) () <br> |
|  [**APlayerObject**](class_a_player_object.md) \* | [**SwitchMainPlayer**](class_a_night_sky_game_state.md#function-switchmainplayer) ([**APlayerObject**](class_a_player_object.md) \* InPlayer, int TeamIndex, bool bForce=false, bool bEvenOnScreen=false) <br> |
| virtual void | [**Tick**](class_a_night_sky_game_state.md#function-tick) (float DeltaTime) override<br> |
|  void | [**UpdateCamera**](class_a_night_sky_game_state.md#function-updatecamera) () <br> |
|  void | [**UpdateGameState**](class_a_night_sky_game_state.md#function-updategamestate-12) () <br> |
|  void | [**UpdateGameState**](class_a_night_sky_game_state.md#function-updategamestate-22) (int32 Input1, int32 Input2, bool bShouldResimulate) <br> |
|  void | [**UpdateHUD**](class_a_night_sky_game_state.md#function-updatehud) () <br> |
|  void | [**UpdateHUDAnimations\_BP**](class_a_night_sky_game_state.md#function-updatehudanimations_bp) () <br> |
|  void | [**UpdateHUD\_BP**](class_a_night_sky_game_state.md#function-updatehud_bp) () <br> |
|  void | [**UpdateScreen**](class_a_night_sky_game_state.md#function-updatescreen) () <br> |
|  void | [**UseGauge**](class_a_night_sky_game_state.md#function-usegauge) (bool IsP1, int32 GaugeIndex, int32 Value) <br> |














































## Protected Functions

| Type | Name |
| ---: | :--- |
| virtual void | [**BeginPlay**](#function-beginplay) () override<br> |


## Protected Functions inherited from ANightSkyGameState

See [ANightSkyGameState](class_a_night_sky_game_state.md)

| Type | Name |
| ---: | :--- |
| virtual void | [**BeginPlay**](class_a_night_sky_game_state.md#function-beginplay) () override<br> |
|  void | [**CollisionView**](class_a_night_sky_game_state.md#function-collisionview) () const<br> |
|  int32 | [**CreateChecksum**](class_a_night_sky_game_state.md#function-createchecksum) () <br> |
| virtual void | [**EndPlay**](class_a_night_sky_game_state.md#function-endplay) (const EEndPlayReason::Type EndPlayReason) override<br> |
|  FGGPONetworkStats | [**GetNetworkStats**](class_a_night_sky_game_state.md#function-getnetworkstats) () const<br> |
|  void | [**HandleHitCollision**](class_a_night_sky_game_state.md#function-handlehitcollision) () const<br> |
|  bool | [**HandleMatchWin**](class_a_night_sky_game_state.md#function-handlematchwin) () <br> |
|  void | [**HandlePushCollision**](class_a_night_sky_game_state.md#function-handlepushcollision) () const<br> |
|  void | [**HandleRoundWin**](class_a_night_sky_game_state.md#function-handleroundwin) () <br> |
|  void | [**Init**](class_a_night_sky_game_state.md#function-init) () <br> |
|  void | [**NextRoundTransition**](class_a_night_sky_game_state.md#function-nextroundtransition) (bool bIsP1) <br> |
|  void | [**PlayIntros**](class_a_night_sky_game_state.md#function-playintros) () <br> |
|  void | [**ResetTraining**](class_a_night_sky_game_state.md#function-resettraining) () <br> |
|  void | [**SortObjects**](class_a_night_sky_game_state.md#function-sortobjects) () <br> |
|  void | [**UpdateLocalInput**](class_a_night_sky_game_state.md#function-updatelocalinput) () <br> |
|  void | [**UpdateVisuals**](class_a_night_sky_game_state.md#function-updatevisuals) (bool bShouldResimulate) const<br> |






## Public Attributes Documentation




### variable OnBattleEndDelegate 

```C++
FOnBattleEndDelegate ANightSkyWTGameState::OnBattleEndDelegate;
```




<hr>



### variable bIsBattling 

```C++
bool ANightSkyWTGameState::bIsBattling;
```




<hr>



### variable bIsMatchEnd 

```C++
bool ANightSkyWTGameState::bIsMatchEnd;
```




<hr>
## Public Functions Documentation




### function ANightSkyWTGameState 

```C++
ANightSkyWTGameState::ANightSkyWTGameState () 
```




<hr>



### function Init 

```C++
void ANightSkyWTGameState::Init (
    APlayerObject * P1,
    APlayerObject * P2
) 
```




<hr>



### function Tick 

```C++
virtual void ANightSkyWTGameState::Tick (
    float DeltaTime
) override
```



Implements [*ANightSkyGameState::Tick*](class_a_night_sky_game_state.md#function-tick)


<hr>
## Protected Functions Documentation




### function BeginPlay 

```C++
virtual void ANightSkyWTGameState::BeginPlay () override
```



Implements [*ANightSkyGameState::BeginPlay*](class_a_night_sky_game_state.md#function-beginplay)


<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/NightSkyEngine/WT/NightSkyWTGameState.h`

