

# Class ANightSkyGameState



[**ClassList**](annotated.md) **>** [**ANightSkyGameState**](class_a_night_sky_game_state.md)








Inherits the following classes: AGameStateBase


Inherited by the following classes: [ANightSkyWTGameState](class_a_night_sky_w_t_game_state.md)
















## Public Attributes

| Type | Name |
| ---: | :--- |
|  [**AAudioManager**](class_a_audio_manager.md) \* | [**AudioManager**](#variable-audiomanager)   = `nullptr`<br> |
|  [**UBattleExtensionData**](class_u_battle_extension_data.md) \* | [**BattleExtensionData**](#variable-battleextensiondata)   = `{}`<br> |
|  TArray&lt; FGameplayTag &gt; | [**BattleExtensionNames**](#variable-battleextensionnames)   = `{}`<br> |
|  TArray&lt; [**UBattleExtension**](class_u_battle_extension.md) \* &gt; | [**BattleExtensions**](#variable-battleextensions)   = `{}`<br> |
|  [**ANightSkyBattleHudActor**](class_a_night_sky_battle_hud_actor.md) \* | [**BattleHudActor**](#variable-battlehudactor)   = `nullptr`<br> |
|  TSubclassOf&lt; [**ABattleObject**](class_a_battle_object.md) &gt; | [**BattleObjectClass**](#variable-battleobjectclass)   = `ABattleObject::StaticClass()`<br> |
|  FTransform | [**BattleSceneTransform**](#variable-battlescenetransform)  <br> |
|  [**FBattleState**](struct_f_battle_state.md) | [**BattleState**](#variable-battlestate)   = `{}`<br> |
|  ACameraActor \* | [**CameraActor**](#variable-cameraactor)   = `nullptr`<br> |
|  class [**AFighterLocalRunner**](class_a_fighter_local_runner.md) \* | [**FighterRunner**](#variable-fighterrunner)   = `nullptr`<br> |
|  class [**UNightSkyGameInstance**](class_u_night_sky_game_instance.md) \* | [**GameInstance**](#variable-gameinstance)   = `nullptr`<br> |
|  int32 | [**LocalFrame**](#variable-localframe)   = `0`<br> |
|  int | [**MaxBattleObjects**](#variable-maxbattleobjects)   = `400`<br> |
|  TArray&lt; [**ABattleObject**](class_a_battle_object.md) \* &gt; | [**Objects**](#variable-objects)   = `{}`<br> |
|  class [**AParticleManager**](class_a_particle_manager.md) \* | [**ParticleManager**](#variable-particlemanager)   = `nullptr`<br> |
|  TArray&lt; [**APlayerObject**](class_a_player_object.md) \* &gt; | [**Players**](#variable-players)   = `{}`<br> |
|  int32 | [**RemoteFrame**](#variable-remoteframe)   = `0`<br> |
|  class ALevelSequenceActor \* | [**SequenceActor**](#variable-sequenceactor)   = `nullptr`<br> |
|  ACameraActor \* | [**SequenceCameraActor**](#variable-sequencecameraactor)   = `nullptr`<br> |
|  TSubclassOf&lt; ACameraActor &gt; | [**SequenceCameraActorClass**](#variable-sequencecameraactorclass)  <br> |
|  [**APlayerObject**](class_a_player_object.md) \* | [**SequenceEnemy**](#variable-sequenceenemy)   = `nullptr`<br> |
|  [**APlayerObject**](class_a_player_object.md) \* | [**SequenceTarget**](#variable-sequencetarget)   = `nullptr`<br> |
|  TArray&lt; [**ABattleObject**](class_a_battle_object.md) \* &gt; | [**SortedObjects**](#variable-sortedobjects)   = `{}`<br> |
|  bool | [**bIsPlayingSequence**](#variable-bisplayingsequence)   = `false`<br> |
|  bool | [**bPauseGame**](#variable-bpausegame)   = `false`<br> |
|  bool | [**bViewCollision**](#variable-bviewcollision)   = `false`<br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**ANightSkyGameState**](#function-anightskygamestate) () <br> |
|  [**ABattleObject**](class_a_battle_object.md) \* | [**AddBattleObject**](#function-addbattleobject) (const [**UState**](class_u_state.md) \* InState, int PosX, int PosY, EObjDir Dir, int32 ObjectStateIndex, bool bIsCommonState, [**APlayerObject**](class_a_player_object.md) \* Parent) const<br> |
|  void | [**AssignEnemy**](#function-assignenemy) () <br> |
|  void | [**BattleHudVisibility**](#function-battlehudvisibility) (bool Visible) <br> |
|  [**APlayerObject**](class_a_player_object.md) \* | [**CallAssist**](#function-callassist) (const bool IsP1, int AssistIndex, const FGameplayTag AssistName) <br> |
|  void | [**CallBattleExtension**](#function-callbattleextension) (FGameplayTag Name) <br> |
|  void | [**CameraShake**](#function-camerashake) (const TSubclassOf&lt; UCameraShakeBase &gt; & Pattern, float Scale) const<br> |
|  bool | [**CanTag**](#function-cantag) (const [**APlayerObject**](class_a_player_object.md) \* InPlayer, int TeamIndex) const<br> |
|  void | [**EndMatch**](#function-endmatch) () <br> |
|  void | [**EndMatch\_BP**](#function-endmatch_bp) () <br> |
|  int32 | [**GetGauge**](#function-getgauge) (bool IsP1, int32 GaugeIndex) const<br> |
|  int | [**GetLocalInputs**](#function-getlocalinputs) (int Index) const<br> |
|  [**APlayerObject**](class_a_player_object.md) \* | [**GetMainPlayer**](#function-getmainplayer) (bool IsP1) const<br> |
|  bool | [**GetPaused**](#function-getpaused) () const<br> |
|  EScreenFlag | [**GetScreenFlags**](#function-getscreenflags) () const<br> |
|  TArray&lt; [**APlayerObject**](class_a_player_object.md) \* &gt; | [**GetTeam**](#function-getteam) (bool IsP1) const<br> |
|  int32 | [**GetTeamCount**](#function-getteamcount) (bool bIsP1) const<br> |
|  void | [**HUDInit**](#function-hudinit) () const<br> |
|  bool | [**IsTagBattle**](#function-istagbattle) () const<br> |
|  void | [**LoadForRollback**](#function-loadforrollback) (const TArray&lt; uint8 &gt; & InBytes) <br> |
|  void | [**LoadGameState**](#function-loadgamestate) ([**FRollbackData**](struct_f_rollback_data.md) & RollbackData) <br> |
|  void | [**ManageAudio**](#function-manageaudio) () <br> |
|  void | [**MatchInit**](#function-matchinit) () <br> |
|  void | [**PlayAnnouncerVoice**](#function-playannouncervoice-12) (USoundBase \* InSoundWave, float MaxDuration) <br> |
|  void | [**PlayAnnouncerVoice**](#function-playannouncervoice-22) (const FGameplayTag Name) <br> |
|  void | [**PlayCharaAudio**](#function-playcharaaudio) (USoundBase \* InSoundWave, float MaxDuration) <br> |
|  void | [**PlayCommonAudio**](#function-playcommonaudio) (USoundBase \* InSoundWave, float MaxDuration) <br> |
|  void | [**PlayLevelSequence**](#function-playlevelsequence) ([**APlayerObject**](class_a_player_object.md) \* Target, [**APlayerObject**](class_a_player_object.md) \* Enemy, ULevelSequence \* Sequence) <br> |
|  void | [**PlayMusic**](#function-playmusic-12) (USoundBase \* InSoundWave, float MaxDuration) <br> |
|  void | [**PlayMusic**](#function-playmusic-22) (const FGameplayTag Name) <br> |
|  void | [**PlayVoiceLine**](#function-playvoiceline) (USoundBase \* InSoundWave, float MaxDuration, int Player) <br> |
|  void | [**RollbackStartAudio**](#function-rollbackstartaudio) (int32 InFrame) <br> |
|  void | [**RoundInit**](#function-roundinit) () <br> |
|  TArray&lt; uint8 &gt; | [**SaveForRollback**](#function-saveforrollback) () <br> |
|  void | [**SaveGameState**](#function-savegamestate) ([**FRollbackData**](struct_f_rollback_data.md) & RollbackData, int32 \* InChecksum) <br> |
|  void | [**ScreenPosToWorldPos**](#function-screenpostoworldpos) (int32 X, int32 Y, int32 & OutX, int32 & OutY) const<br> |
|  void | [**SetDrawPriorityBack**](#function-setdrawpriorityback) ([**ABattleObject**](class_a_battle_object.md) \* InObject) const<br> |
|  void | [**SetDrawPriorityFront**](#function-setdrawpriorityfront) ([**ABattleObject**](class_a_battle_object.md) \* InObject) const<br> |
|  void | [**SetGauge**](#function-setgauge) (bool IsP1, int32 GaugeIndex, int32 Value) <br> |
|  void | [**SetOtherChecksum**](#function-setotherchecksum) (uint32 RemoteChecksum, int32 InFrame) <br> |
|  void | [**SetPaused**](#function-setpaused) (bool bPause) <br> |
|  void | [**SetScreenBounds**](#function-setscreenbounds) () const<br> |
|  void | [**SetScreenCorners**](#function-setscreencorners) () <br> |
|  void | [**SetScreenFlags**](#function-setscreenflags) (UPARAM(meta=(Bitmask, BitmaskEnum="/Script/NightSkyEngine.EScreenFlag")) int32 InFlags) <br> |
|  void | [**SetTeamCooldown**](#function-setteamcooldown) (const bool IsP1, const int TeamIndex, const int Cooldown) <br> |
|  void | [**StartSuperFreeze**](#function-startsuperfreeze) (int32 Duration, int32 SelfDuration, [**ABattleObject**](class_a_battle_object.md) \* CallingObject) <br> |
|  void | [**StopLevelSequence**](#function-stoplevelsequence) () <br> |
|  [**APlayerObject**](class_a_player_object.md) \* | [**SwitchMainPlayer**](#function-switchmainplayer) ([**APlayerObject**](class_a_player_object.md) \* InPlayer, int TeamIndex, bool bForce=false, bool bEvenOnScreen=false) <br> |
| virtual void | [**Tick**](#function-tick) (float DeltaTime) override<br> |
|  void | [**UpdateCamera**](#function-updatecamera) () <br> |
|  void | [**UpdateGameState**](#function-updategamestate-12) () <br> |
|  void | [**UpdateGameState**](#function-updategamestate-22) (int32 Input1, int32 Input2, bool bShouldResimulate) <br> |
|  void | [**UpdateHUD**](#function-updatehud) () <br> |
|  void | [**UpdateHUDAnimations\_BP**](#function-updatehudanimations_bp) () <br> |
|  void | [**UpdateHUD\_BP**](#function-updatehud_bp) () <br> |
|  void | [**UpdateScreen**](#function-updatescreen) () <br> |
|  void | [**UseGauge**](#function-usegauge) (bool IsP1, int32 GaugeIndex, int32 Value) <br> |
























## Protected Functions

| Type | Name |
| ---: | :--- |
| virtual void | [**BeginPlay**](#function-beginplay) () override<br> |
|  void | [**CollisionView**](#function-collisionview) () const<br> |
|  int32 | [**CreateChecksum**](#function-createchecksum) () <br> |
| virtual void | [**EndPlay**](#function-endplay) (const EEndPlayReason::Type EndPlayReason) override<br> |
|  FGGPONetworkStats | [**GetNetworkStats**](#function-getnetworkstats) () const<br> |
|  void | [**HandleHitCollision**](#function-handlehitcollision) () const<br> |
|  bool | [**HandleMatchWin**](#function-handlematchwin) () <br> |
|  void | [**HandlePushCollision**](#function-handlepushcollision) () const<br> |
|  void | [**HandleRoundWin**](#function-handleroundwin) () <br> |
|  void | [**Init**](#function-init) () <br> |
|  void | [**NextRoundTransition**](#function-nextroundtransition) (bool bIsP1) <br> |
|  void | [**PlayIntros**](#function-playintros) () <br> |
|  void | [**ResetTraining**](#function-resettraining) () <br> |
|  void | [**SortObjects**](#function-sortobjects) () <br> |
|  void | [**UpdateLocalInput**](#function-updatelocalinput) () <br> |
|  void | [**UpdateVisuals**](#function-updatevisuals) (bool bShouldResimulate) const<br> |




## Public Attributes Documentation




### variable AudioManager 

```C++
AAudioManager* ANightSkyGameState::AudioManager;
```




<hr>



### variable BattleExtensionData 

```C++
UBattleExtensionData* ANightSkyGameState::BattleExtensionData;
```




<hr>



### variable BattleExtensionNames 

```C++
TArray<FGameplayTag> ANightSkyGameState::BattleExtensionNames;
```




<hr>



### variable BattleExtensions 

```C++
TArray<UBattleExtension*> ANightSkyGameState::BattleExtensions;
```




<hr>



### variable BattleHudActor 

```C++
ANightSkyBattleHudActor* ANightSkyGameState::BattleHudActor;
```




<hr>



### variable BattleObjectClass 

```C++
TSubclassOf<ABattleObject> ANightSkyGameState::BattleObjectClass;
```




<hr>



### variable BattleSceneTransform 

```C++
FTransform ANightSkyGameState::BattleSceneTransform;
```




<hr>



### variable BattleState 

```C++
FBattleState ANightSkyGameState::BattleState;
```




<hr>



### variable CameraActor 

```C++
ACameraActor* ANightSkyGameState::CameraActor;
```




<hr>



### variable FighterRunner 

```C++
class AFighterLocalRunner* ANightSkyGameState::FighterRunner;
```




<hr>



### variable GameInstance 

```C++
class UNightSkyGameInstance* ANightSkyGameState::GameInstance;
```




<hr>



### variable LocalFrame 

```C++
int32 ANightSkyGameState::LocalFrame;
```




<hr>



### variable MaxBattleObjects 

```C++
int ANightSkyGameState::MaxBattleObjects;
```




<hr>



### variable Objects 

```C++
TArray<ABattleObject*> ANightSkyGameState::Objects;
```




<hr>



### variable ParticleManager 

```C++
class AParticleManager* ANightSkyGameState::ParticleManager;
```




<hr>



### variable Players 

```C++
TArray<APlayerObject*> ANightSkyGameState::Players;
```




<hr>



### variable RemoteFrame 

```C++
int32 ANightSkyGameState::RemoteFrame;
```




<hr>



### variable SequenceActor 

```C++
class ALevelSequenceActor* ANightSkyGameState::SequenceActor;
```




<hr>



### variable SequenceCameraActor 

```C++
ACameraActor* ANightSkyGameState::SequenceCameraActor;
```




<hr>



### variable SequenceCameraActorClass 

```C++
TSubclassOf<ACameraActor> ANightSkyGameState::SequenceCameraActorClass;
```




<hr>



### variable SequenceEnemy 

```C++
APlayerObject* ANightSkyGameState::SequenceEnemy;
```




<hr>



### variable SequenceTarget 

```C++
APlayerObject* ANightSkyGameState::SequenceTarget;
```




<hr>



### variable SortedObjects 

```C++
TArray<ABattleObject*> ANightSkyGameState::SortedObjects;
```




<hr>



### variable bIsPlayingSequence 

```C++
bool ANightSkyGameState::bIsPlayingSequence;
```




<hr>



### variable bPauseGame 

```C++
bool ANightSkyGameState::bPauseGame;
```




<hr>



### variable bViewCollision 

```C++
bool ANightSkyGameState::bViewCollision;
```




<hr>
## Public Functions Documentation




### function ANightSkyGameState 

```C++
ANightSkyGameState::ANightSkyGameState () 
```




<hr>



### function AddBattleObject 

```C++
ABattleObject * ANightSkyGameState::AddBattleObject (
    const UState * InState,
    int PosX,
    int PosY,
    EObjDir Dir,
    int32 ObjectStateIndex,
    bool bIsCommonState,
    APlayerObject * Parent
) const
```




<hr>



### function AssignEnemy 

```C++
void ANightSkyGameState::AssignEnemy () 
```




<hr>



### function BattleHudVisibility 

```C++
void ANightSkyGameState::BattleHudVisibility (
    bool Visible
) 
```




<hr>



### function CallAssist 

```C++
APlayerObject * ANightSkyGameState::CallAssist (
    const bool IsP1,
    int AssistIndex,
    const FGameplayTag AssistName
) 
```




<hr>



### function CallBattleExtension 

```C++
void ANightSkyGameState::CallBattleExtension (
    FGameplayTag Name
) 
```




<hr>



### function CameraShake 

```C++
void ANightSkyGameState::CameraShake (
    const TSubclassOf< UCameraShakeBase > & Pattern,
    float Scale
) const
```




<hr>



### function CanTag 

```C++
bool ANightSkyGameState::CanTag (
    const APlayerObject * InPlayer,
    int TeamIndex
) const
```




<hr>



### function EndMatch 

```C++
void ANightSkyGameState::EndMatch () 
```




<hr>



### function EndMatch\_BP 

```C++
void ANightSkyGameState::EndMatch_BP () 
```




<hr>



### function GetGauge 

```C++
int32 ANightSkyGameState::GetGauge (
    bool IsP1,
    int32 GaugeIndex
) const
```




<hr>



### function GetLocalInputs 

```C++
int ANightSkyGameState::GetLocalInputs (
    int Index
) const
```




<hr>



### function GetMainPlayer 

```C++
APlayerObject * ANightSkyGameState::GetMainPlayer (
    bool IsP1
) const
```




<hr>



### function GetPaused 

```C++
bool ANightSkyGameState::GetPaused () const
```




<hr>



### function GetScreenFlags 

```C++
EScreenFlag ANightSkyGameState::GetScreenFlags () const
```




<hr>



### function GetTeam 

```C++
TArray< APlayerObject * > ANightSkyGameState::GetTeam (
    bool IsP1
) const
```




<hr>



### function GetTeamCount 

```C++
int32 ANightSkyGameState::GetTeamCount (
    bool bIsP1
) const
```




<hr>



### function HUDInit 

```C++
void ANightSkyGameState::HUDInit () const
```




<hr>



### function IsTagBattle 

```C++
bool ANightSkyGameState::IsTagBattle () const
```




<hr>



### function LoadForRollback 

```C++
void ANightSkyGameState::LoadForRollback (
    const TArray< uint8 > & InBytes
) 
```




<hr>



### function LoadGameState 

```C++
void ANightSkyGameState::LoadGameState (
    FRollbackData & RollbackData
) 
```




<hr>



### function ManageAudio 

```C++
void ANightSkyGameState::ManageAudio () 
```




<hr>



### function MatchInit 

```C++
void ANightSkyGameState::MatchInit () 
```




<hr>



### function PlayAnnouncerVoice [1/2]

```C++
void ANightSkyGameState::PlayAnnouncerVoice (
    USoundBase * InSoundWave,
    float MaxDuration
) 
```




<hr>



### function PlayAnnouncerVoice [2/2]

```C++
void ANightSkyGameState::PlayAnnouncerVoice (
    const FGameplayTag Name
) 
```




<hr>



### function PlayCharaAudio 

```C++
void ANightSkyGameState::PlayCharaAudio (
    USoundBase * InSoundWave,
    float MaxDuration
) 
```




<hr>



### function PlayCommonAudio 

```C++
void ANightSkyGameState::PlayCommonAudio (
    USoundBase * InSoundWave,
    float MaxDuration
) 
```




<hr>



### function PlayLevelSequence 

```C++
void ANightSkyGameState::PlayLevelSequence (
    APlayerObject * Target,
    APlayerObject * Enemy,
    ULevelSequence * Sequence
) 
```




<hr>



### function PlayMusic [1/2]

```C++
void ANightSkyGameState::PlayMusic (
    USoundBase * InSoundWave,
    float MaxDuration
) 
```




<hr>



### function PlayMusic [2/2]

```C++
void ANightSkyGameState::PlayMusic (
    const FGameplayTag Name
) 
```




<hr>



### function PlayVoiceLine 

```C++
void ANightSkyGameState::PlayVoiceLine (
    USoundBase * InSoundWave,
    float MaxDuration,
    int Player
) 
```




<hr>



### function RollbackStartAudio 

```C++
void ANightSkyGameState::RollbackStartAudio (
    int32 InFrame
) 
```




<hr>



### function RoundInit 

```C++
void ANightSkyGameState::RoundInit () 
```




<hr>



### function SaveForRollback 

```C++
TArray< uint8 > ANightSkyGameState::SaveForRollback () 
```




<hr>



### function SaveGameState 

```C++
void ANightSkyGameState::SaveGameState (
    FRollbackData & RollbackData,
    int32 * InChecksum
) 
```




<hr>



### function ScreenPosToWorldPos 

```C++
void ANightSkyGameState::ScreenPosToWorldPos (
    int32 X,
    int32 Y,
    int32 & OutX,
    int32 & OutY
) const
```




<hr>



### function SetDrawPriorityBack 

```C++
void ANightSkyGameState::SetDrawPriorityBack (
    ABattleObject * InObject
) const
```




<hr>



### function SetDrawPriorityFront 

```C++
void ANightSkyGameState::SetDrawPriorityFront (
    ABattleObject * InObject
) const
```




<hr>



### function SetGauge 

```C++
void ANightSkyGameState::SetGauge (
    bool IsP1,
    int32 GaugeIndex,
    int32 Value
) 
```




<hr>



### function SetOtherChecksum 

```C++
void ANightSkyGameState::SetOtherChecksum (
    uint32 RemoteChecksum,
    int32 InFrame
) 
```




<hr>



### function SetPaused 

```C++
void ANightSkyGameState::SetPaused (
    bool bPause
) 
```




<hr>



### function SetScreenBounds 

```C++
void ANightSkyGameState::SetScreenBounds () const
```




<hr>



### function SetScreenCorners 

```C++
void ANightSkyGameState::SetScreenCorners () 
```




<hr>



### function SetScreenFlags 

```C++
void ANightSkyGameState::SetScreenFlags (
    UPARAM(meta=(Bitmask, BitmaskEnum="/Script/NightSkyEngine.EScreenFlag")) int32 InFlags
) 
```




<hr>



### function SetTeamCooldown 

```C++
void ANightSkyGameState::SetTeamCooldown (
    const bool IsP1,
    const int TeamIndex,
    const int Cooldown
) 
```




<hr>



### function StartSuperFreeze 

```C++
void ANightSkyGameState::StartSuperFreeze (
    int32 Duration,
    int32 SelfDuration,
    ABattleObject * CallingObject
) 
```




<hr>



### function StopLevelSequence 

```C++
void ANightSkyGameState::StopLevelSequence () 
```




<hr>



### function SwitchMainPlayer 

```C++
APlayerObject * ANightSkyGameState::SwitchMainPlayer (
    APlayerObject * InPlayer,
    int TeamIndex,
    bool bForce=false,
    bool bEvenOnScreen=false
) 
```




<hr>



### function Tick 

```C++
virtual void ANightSkyGameState::Tick (
    float DeltaTime
) override
```




<hr>



### function UpdateCamera 

```C++
void ANightSkyGameState::UpdateCamera () 
```




<hr>



### function UpdateGameState [1/2]

```C++
void ANightSkyGameState::UpdateGameState () 
```




<hr>



### function UpdateGameState [2/2]

```C++
void ANightSkyGameState::UpdateGameState (
    int32 Input1,
    int32 Input2,
    bool bShouldResimulate
) 
```




<hr>



### function UpdateHUD 

```C++
void ANightSkyGameState::UpdateHUD () 
```




<hr>



### function UpdateHUDAnimations\_BP 

```C++
void ANightSkyGameState::UpdateHUDAnimations_BP () 
```




<hr>



### function UpdateHUD\_BP 

```C++
void ANightSkyGameState::UpdateHUD_BP () 
```




<hr>



### function UpdateScreen 

```C++
void ANightSkyGameState::UpdateScreen () 
```




<hr>



### function UseGauge 

```C++
void ANightSkyGameState::UseGauge (
    bool IsP1,
    int32 GaugeIndex,
    int32 Value
) 
```




<hr>
## Protected Functions Documentation




### function BeginPlay 

```C++
virtual void ANightSkyGameState::BeginPlay () override
```




<hr>



### function CollisionView 

```C++
void ANightSkyGameState::CollisionView () const
```




<hr>



### function CreateChecksum 

```C++
int32 ANightSkyGameState::CreateChecksum () 
```




<hr>



### function EndPlay 

```C++
virtual void ANightSkyGameState::EndPlay (
    const EEndPlayReason::Type EndPlayReason
) override
```




<hr>



### function GetNetworkStats 

```C++
FGGPONetworkStats ANightSkyGameState::GetNetworkStats () const
```




<hr>



### function HandleHitCollision 

```C++
void ANightSkyGameState::HandleHitCollision () const
```




<hr>



### function HandleMatchWin 

```C++
bool ANightSkyGameState::HandleMatchWin () 
```




<hr>



### function HandlePushCollision 

```C++
void ANightSkyGameState::HandlePushCollision () const
```




<hr>



### function HandleRoundWin 

```C++
void ANightSkyGameState::HandleRoundWin () 
```




<hr>



### function Init 

```C++
void ANightSkyGameState::Init () 
```




<hr>



### function NextRoundTransition 

```C++
void ANightSkyGameState::NextRoundTransition (
    bool bIsP1
) 
```




<hr>



### function PlayIntros 

```C++
void ANightSkyGameState::PlayIntros () 
```




<hr>



### function ResetTraining 

```C++
void ANightSkyGameState::ResetTraining () 
```




<hr>



### function SortObjects 

```C++
void ANightSkyGameState::SortObjects () 
```




<hr>



### function UpdateLocalInput 

```C++
void ANightSkyGameState::UpdateLocalInput () 
```




<hr>



### function UpdateVisuals 

```C++
void ANightSkyGameState::UpdateVisuals (
    bool bShouldResimulate
) const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/NightSkyEngine/Battle/NightSkyGameState.h`

