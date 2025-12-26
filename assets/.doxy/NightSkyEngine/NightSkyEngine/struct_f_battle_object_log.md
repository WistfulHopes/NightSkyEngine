

# Struct FBattleObjectLog



[**ClassList**](annotated.md) **>** [**FBattleObjectLog**](struct_f_battle_object_log.md)



[More...](#detailed-description)

* `#include <BattleObject.h>`





Inherited by the following classes: [FPlayerObjectLog](struct_f_player_object_log.md)
















## Public Attributes

| Type | Name |
| ---: | :--- |
|  int32 | [**ActionReg1**](#variable-actionreg1)   = `0`<br> |
|  int32 | [**ActionReg2**](#variable-actionreg2)   = `0`<br> |
|  int32 | [**ActionReg3**](#variable-actionreg3)   = `0`<br> |
|  int32 | [**ActionReg4**](#variable-actionreg4)   = `0`<br> |
|  int32 | [**ActionReg5**](#variable-actionreg5)   = `0`<br> |
|  int32 | [**ActionReg6**](#variable-actionreg6)   = `0`<br> |
|  int32 | [**ActionReg7**](#variable-actionreg7)   = `0`<br> |
|  int32 | [**ActionReg8**](#variable-actionreg8)   = `0`<br> |
|  int32 | [**ActionTime**](#variable-actiontime)   = `0`<br> |
|  FLinearColor | [**AddColor**](#variable-addcolor)   = `FLinearColor(0, 0, 0, 1)`<br> |
|  FLinearColor | [**AddFadeColor**](#variable-addfadecolor)   = `{}`<br> |
|  float | [**AddFadeSpeed**](#variable-addfadespeed)   = `0`<br> |
|  int32 | [**AnglePitch\_x10**](#variable-anglepitch_x10)   = `0`<br> |
|  int32 | [**AngleRoll\_x10**](#variable-angleroll_x10)   = `0`<br> |
|  int32 | [**AngleYaw\_x10**](#variable-angleyaw_x10)   = `0`<br> |
|  float | [**AnimBlendIn**](#variable-animblendin)   = `{}`<br> |
|  float | [**AnimBlendOut**](#variable-animblendout)   = `{}`<br> |
|  int32 | [**AnimFrame**](#variable-animframe)   = `0`<br> |
|  uint32 | [**AttackFlags**](#variable-attackflags)   = `0`<br> |
|  [**ABattleObject**](class_a_battle_object.md) \* | [**AttackOwner**](#variable-attackowner)  <br> |
|  [**ABattleObject**](class_a_battle_object.md) \* | [**AttackTarget**](#variable-attacktarget)   = `nullptr`<br> |
|  int32 | [**B**](#variable-b)   = `0`<br> |
|  int32 | [**BlendAnimFrame**](#variable-blendanimframe)   = `0`<br> |
|  FGameplayTag | [**BlendCelName**](#variable-blendcelname)   = `{}`<br> |
|  bool | [**BlendOffset**](#variable-blendoffset)   = `false`<br> |
|  int32 | [**CelIndex**](#variable-celindex)   = `0`<br> |
|  FGameplayTag | [**CelName**](#variable-celname)   = `{}`<br> |
|  int32 | [**ColPosX**](#variable-colposx)   = `0`<br> |
|  int32 | [**ColPosY**](#variable-colposy)   = `0`<br> |
|  [**FHitData**](struct_f_hit_data.md) | [**CounterHit**](#variable-counterhit)   = `{}`<br> |
|  FLinearColor | [**DamageColor**](#variable-damagecolor)   = `FLinearColor(1, 1, 1, 1)`<br> |
|  FLinearColor | [**DamageColor2**](#variable-damagecolor2)   = `FLinearColor(1, 1, 1, 1)`<br> |
|  TEnumAsByte&lt; EObjDir &gt; | [**Direction**](#variable-direction)   = `DIR\_Right`<br> |
|  int32 | [**DrawPriority**](#variable-drawpriority)   = `0`<br> |
|  [**ABattleObject**](class_a_battle_object.md) \* | [**DrawPriorityLinkObj**](#variable-drawprioritylinkobj)   = `nullptr`<br> |
|  [**FEventHandler**](struct_f_event_handler.md) | [**EventHandlers**](#variable-eventhandlers)   = `{}`<br> |
|  float | [**FadeTransparency**](#variable-fadetransparency)   = `1`<br> |
|  float | [**FrameBlendPosition**](#variable-frameblendposition)   = `0`<br> |
|  bool | [**GotoLabelActive**](#variable-gotolabelactive)   = `false`<br> |
|  int32 | [**Gravity**](#variable-gravity)   = `1900`<br> |
|  int32 | [**GroundHeight**](#variable-groundheight)   = `0`<br> |
|  [**FHitDataCommon**](struct_f_hit_data_common.md) | [**HitCommon**](#variable-hitcommon)   = `{}`<br> |
|  uint32 | [**Hitstop**](#variable-hitstop)   = `0`<br> |
|  [**FHomingParams**](struct_f_homing_params.md) | [**HomingParams**](#variable-homingparams)   = `[**FHomingParams**](struct_f_homing_params.md)()`<br> |
|  int32 | [**Inertia**](#variable-inertia)   = `0`<br> |
|  bool | [**IsActive**](#variable-isactive)   = `false`<br> |
|  bool | [**IsPlayer**](#variable-isplayer)   = `false`<br> |
|  int32 | [**L**](#variable-l)   = `0`<br> |
|  FGameplayTag | [**LabelName**](#variable-labelname)   = `{}`<br> |
|  [**ABattleObject**](class_a_battle_object.md) \* | [**MaterialLinkObj**](#variable-materiallinkobj)   = `nullptr`<br> |
|  int32 | [**MaxCelTime**](#variable-maxceltime)   = `0`<br> |
|  int32 | [**MiscFlags**](#variable-miscflags)   = `0`<br> |
|  FLinearColor | [**MulColor**](#variable-mulcolor)   = `FLinearColor(1, 1, 1, 1)`<br> |
|  FLinearColor | [**MulFadeColor**](#variable-mulfadecolor)   = `{}`<br> |
|  float | [**MulFadeSpeed**](#variable-mulfadespeed)   = `0`<br> |
|  int32 | [**NextOffsetX**](#variable-nextoffsetx)   = `0`<br> |
|  int32 | [**NextOffsetY**](#variable-nextoffsety)   = `0`<br> |
|  [**FHitData**](struct_f_hit_data.md) | [**NormalHit**](#variable-normalhit)   = `{}`<br> |
|  unsigned char | [**ObjSync**](#variable-objsync)   = `0`<br> |
|  unsigned char | [**ObjSyncEnd**](#variable-objsyncend)   = `0`<br> |
|  uint32 | [**ObjectID**](#variable-objectid)   = `0`<br> |
|  FVector | [**ObjectOffset**](#variable-objectoffset)   = `FVector::ZeroVector`<br> |
|  int32 | [**ObjectReg1**](#variable-objectreg1)   = `0`<br> |
|  int32 | [**ObjectReg2**](#variable-objectreg2)   = `0`<br> |
|  int32 | [**ObjectReg3**](#variable-objectreg3)   = `0`<br> |
|  int32 | [**ObjectReg4**](#variable-objectreg4)   = `0`<br> |
|  int32 | [**ObjectReg5**](#variable-objectreg5)   = `0`<br> |
|  int32 | [**ObjectReg6**](#variable-objectreg6)   = `0`<br> |
|  int32 | [**ObjectReg7**](#variable-objectreg7)   = `0`<br> |
|  int32 | [**ObjectReg8**](#variable-objectreg8)   = `0`<br> |
|  FRotator | [**ObjectRotation**](#variable-objectrotation)   = `FRotator::ZeroRotator`<br> |
|  FVector | [**ObjectScale**](#variable-objectscale)   = `FVector::One()`<br> |
|  int32 | [**ObjectStateIndex**](#variable-objectstateindex)   = `0`<br> |
|  FGameplayTag | [**ObjectStateName**](#variable-objectstatename)   = `{}`<br> |
|  [**APlayerObject**](class_a_player_object.md) \* | [**Player**](#variable-player)   = `nullptr`<br> |
|  int32 | [**PosX**](#variable-posx)   = `0`<br> |
|  int32 | [**PosY**](#variable-posy)   = `0`<br> |
|  int32 | [**PosZ**](#variable-posz)   = `0`<br> |
|  [**ABattleObject**](class_a_battle_object.md) \* | [**PositionLinkObj**](#variable-positionlinkobj)   = `nullptr`<br> |
|  int32 | [**PrevOffsetX**](#variable-prevoffsetx)   = `0`<br> |
|  int32 | [**PrevOffsetY**](#variable-prevoffsety)   = `0`<br> |
|  int32 | [**PrevPosX**](#variable-prevposx)   = `0`<br> |
|  int32 | [**PrevPosY**](#variable-prevposy)   = `0`<br> |
|  int32 | [**PrevPosZ**](#variable-prevposz)   = `0`<br> |
|  int32 | [**PrevRootMotionX**](#variable-prevrootmotionx)   = `0`<br> |
|  int32 | [**PrevRootMotionY**](#variable-prevrootmotiony)   = `0`<br> |
|  int32 | [**PrevRootMotionZ**](#variable-prevrootmotionz)   = `0`<br> |
|  int32 | [**Pushback**](#variable-pushback)   = `0`<br> |
|  int32 | [**R**](#variable-r)   = `0`<br> |
|  [**FHitData**](struct_f_hit_data.md) | [**ReceivedHit**](#variable-receivedhit)   = `{}`<br> |
|  [**FHitDataCommon**](struct_f_hit_data_common.md) | [**ReceivedHitCommon**](#variable-receivedhitcommon)   = `{}`<br> |
|  bool | [**ReturnReg**](#variable-returnreg)   = `false`<br> |
|  FName | [**SocketName**](#variable-socketname)   = `{}`<br> |
|  EObjType | [**SocketObj**](#variable-socketobj)   = `OBJ\_Self`<br> |
|  FVector | [**SocketOffset**](#variable-socketoffset)   = `FVector::ZeroVector`<br> |
|  int32 | [**SpeedX**](#variable-speedx)   = `0`<br> |
|  int32 | [**SpeedXRate**](#variable-speedxrate)   = `100`<br> |
|  int32 | [**SpeedXRatePerFrame**](#variable-speedxrateperframe)   = `100`<br> |
|  int32 | [**SpeedY**](#variable-speedy)   = `0`<br> |
|  int32 | [**SpeedYRate**](#variable-speedyrate)   = `100`<br> |
|  int32 | [**SpeedYRatePerFrame**](#variable-speedyrateperframe)   = `100`<br> |
|  int32 | [**SpeedZ**](#variable-speedz)   = `0`<br> |
|  int32 | [**SpeedZRate**](#variable-speedzrate)   = `100`<br> |
|  int32 | [**SpeedZRatePerFrame**](#variable-speedzrateperframe)   = `100`<br> |
|  [**ABattleObject**](class_a_battle_object.md) \* | [**StopLinkObj**](#variable-stoplinkobj)   = `nullptr`<br> |
|  uint32 | [**StunTime**](#variable-stuntime)   = `0`<br> |
|  uint32 | [**StunTimeMax**](#variable-stuntimemax)   = `0`<br> |
|  int32 | [**SubroutineReg1**](#variable-subroutinereg1)   = `0`<br> |
|  int32 | [**SubroutineReg2**](#variable-subroutinereg2)   = `0`<br> |
|  int32 | [**SubroutineReg3**](#variable-subroutinereg3)   = `0`<br> |
|  int32 | [**SubroutineReg4**](#variable-subroutinereg4)   = `0`<br> |
|  int32 | [**SubroutineReturnVal1**](#variable-subroutinereturnval1)   = `0`<br> |
|  int32 | [**SubroutineReturnVal2**](#variable-subroutinereturnval2)   = `0`<br> |
|  int32 | [**SubroutineReturnVal3**](#variable-subroutinereturnval3)   = `0`<br> |
|  int32 | [**SubroutineReturnVal4**](#variable-subroutinereturnval4)   = `0`<br> |
|  [**FSuperArmorData**](struct_f_super_armor_data.md) | [**SuperArmorData**](#variable-superarmordata)   = `[**FSuperArmorData**](struct_f_super_armor_data.md)()`<br> |
|  int32 | [**T**](#variable-t)   = `0`<br> |
|  int32 | [**TimeUntilNextCel**](#variable-timeuntilnextcel)   = `0`<br> |
|  int32 | [**Timer0**](#variable-timer0)   = `0`<br> |
|  int32 | [**Timer1**](#variable-timer1)   = `0`<br> |
|  float | [**Transparency**](#variable-transparency)   = `1`<br> |
|  float | [**TransparencySpeed**](#variable-transparencyspeed)   = `0`<br> |
|  int32 | [**UpdateTime**](#variable-updatetime)   = `0`<br> |
|  bool | [**bIsCommonState**](#variable-biscommonstate)   = `false`<br> |
|  bool | [**bRender**](#variable-brender)   = `true`<br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
| virtual void | [**LogForSyncTestFile**](#function-logforsynctestfile) (std::ofstream & file) <br> |
| virtual  | [**~FBattleObjectLog**](#function-fbattleobjectlog) () = default<br> |








## Protected Attributes

| Type | Name |
| ---: | :--- |
|  int32 | [**PushHeight**](#variable-pushheight)   = `0`<br> |
|  int32 | [**PushHeightLow**](#variable-pushheightlow)   = `0`<br> |
|  int32 | [**PushWidth**](#variable-pushwidth)   = `0`<br> |
|  int32 | [**PushWidthExtend**](#variable-pushwidthextend)   = `0`<br> |




















## Detailed Description


This struct is only for sync logs. 


    
## Public Attributes Documentation




### variable ActionReg1 

```C++
int32 FBattleObjectLog::ActionReg1;
```




<hr>



### variable ActionReg2 

```C++
int32 FBattleObjectLog::ActionReg2;
```




<hr>



### variable ActionReg3 

```C++
int32 FBattleObjectLog::ActionReg3;
```




<hr>



### variable ActionReg4 

```C++
int32 FBattleObjectLog::ActionReg4;
```




<hr>



### variable ActionReg5 

```C++
int32 FBattleObjectLog::ActionReg5;
```




<hr>



### variable ActionReg6 

```C++
int32 FBattleObjectLog::ActionReg6;
```




<hr>



### variable ActionReg7 

```C++
int32 FBattleObjectLog::ActionReg7;
```




<hr>



### variable ActionReg8 

```C++
int32 FBattleObjectLog::ActionReg8;
```




<hr>



### variable ActionTime 

```C++
int32 FBattleObjectLog::ActionTime;
```




<hr>



### variable AddColor 

```C++
FLinearColor FBattleObjectLog::AddColor;
```




<hr>



### variable AddFadeColor 

```C++
FLinearColor FBattleObjectLog::AddFadeColor;
```




<hr>



### variable AddFadeSpeed 

```C++
float FBattleObjectLog::AddFadeSpeed;
```




<hr>



### variable AnglePitch\_x10 

```C++
int32 FBattleObjectLog::AnglePitch_x10;
```




<hr>



### variable AngleRoll\_x10 

```C++
int32 FBattleObjectLog::AngleRoll_x10;
```




<hr>



### variable AngleYaw\_x10 

```C++
int32 FBattleObjectLog::AngleYaw_x10;
```




<hr>



### variable AnimBlendIn 

```C++
float FBattleObjectLog::AnimBlendIn;
```




<hr>



### variable AnimBlendOut 

```C++
float FBattleObjectLog::AnimBlendOut;
```




<hr>



### variable AnimFrame 

```C++
int32 FBattleObjectLog::AnimFrame;
```




<hr>



### variable AttackFlags 

```C++
uint32 FBattleObjectLog::AttackFlags;
```




<hr>



### variable AttackOwner 

```C++
ABattleObject* FBattleObjectLog::AttackOwner;
```




<hr>



### variable AttackTarget 

```C++
ABattleObject* FBattleObjectLog::AttackTarget;
```




<hr>



### variable B 

```C++
int32 FBattleObjectLog::B;
```




<hr>



### variable BlendAnimFrame 

```C++
int32 FBattleObjectLog::BlendAnimFrame;
```




<hr>



### variable BlendCelName 

```C++
FGameplayTag FBattleObjectLog::BlendCelName;
```




<hr>



### variable BlendOffset 

```C++
bool FBattleObjectLog::BlendOffset;
```




<hr>



### variable CelIndex 

```C++
int32 FBattleObjectLog::CelIndex;
```




<hr>



### variable CelName 

```C++
FGameplayTag FBattleObjectLog::CelName;
```




<hr>



### variable ColPosX 

```C++
int32 FBattleObjectLog::ColPosX;
```




<hr>



### variable ColPosY 

```C++
int32 FBattleObjectLog::ColPosY;
```




<hr>



### variable CounterHit 

```C++
FHitData FBattleObjectLog::CounterHit;
```




<hr>



### variable DamageColor 

```C++
FLinearColor FBattleObjectLog::DamageColor;
```




<hr>



### variable DamageColor2 

```C++
FLinearColor FBattleObjectLog::DamageColor2;
```




<hr>



### variable Direction 

```C++
TEnumAsByte<EObjDir> FBattleObjectLog::Direction;
```




<hr>



### variable DrawPriority 

```C++
int32 FBattleObjectLog::DrawPriority;
```




<hr>



### variable DrawPriorityLinkObj 

```C++
ABattleObject* FBattleObjectLog::DrawPriorityLinkObj;
```




<hr>



### variable EventHandlers 

```C++
FEventHandler FBattleObjectLog::EventHandlers[EVT_NUM];
```




<hr>



### variable FadeTransparency 

```C++
float FBattleObjectLog::FadeTransparency;
```




<hr>



### variable FrameBlendPosition 

```C++
float FBattleObjectLog::FrameBlendPosition;
```




<hr>



### variable GotoLabelActive 

```C++
bool FBattleObjectLog::GotoLabelActive;
```




<hr>



### variable Gravity 

```C++
int32 FBattleObjectLog::Gravity;
```




<hr>



### variable GroundHeight 

```C++
int32 FBattleObjectLog::GroundHeight;
```




<hr>



### variable HitCommon 

```C++
FHitDataCommon FBattleObjectLog::HitCommon;
```




<hr>



### variable Hitstop 

```C++
uint32 FBattleObjectLog::Hitstop;
```




<hr>



### variable HomingParams 

```C++
FHomingParams FBattleObjectLog::HomingParams;
```




<hr>



### variable Inertia 

```C++
int32 FBattleObjectLog::Inertia;
```




<hr>



### variable IsActive 

```C++
bool FBattleObjectLog::IsActive;
```




<hr>



### variable IsPlayer 

```C++
bool FBattleObjectLog::IsPlayer;
```




<hr>



### variable L 

```C++
int32 FBattleObjectLog::L;
```




<hr>



### variable LabelName 

```C++
FGameplayTag FBattleObjectLog::LabelName;
```




<hr>



### variable MaterialLinkObj 

```C++
ABattleObject* FBattleObjectLog::MaterialLinkObj;
```




<hr>



### variable MaxCelTime 

```C++
int32 FBattleObjectLog::MaxCelTime;
```




<hr>



### variable MiscFlags 

```C++
int32 FBattleObjectLog::MiscFlags;
```




<hr>



### variable MulColor 

```C++
FLinearColor FBattleObjectLog::MulColor;
```




<hr>



### variable MulFadeColor 

```C++
FLinearColor FBattleObjectLog::MulFadeColor;
```




<hr>



### variable MulFadeSpeed 

```C++
float FBattleObjectLog::MulFadeSpeed;
```




<hr>



### variable NextOffsetX 

```C++
int32 FBattleObjectLog::NextOffsetX;
```




<hr>



### variable NextOffsetY 

```C++
int32 FBattleObjectLog::NextOffsetY;
```




<hr>



### variable NormalHit 

```C++
FHitData FBattleObjectLog::NormalHit;
```




<hr>



### variable ObjSync 

```C++
unsigned char FBattleObjectLog::ObjSync;
```




<hr>



### variable ObjSyncEnd 

```C++
unsigned char FBattleObjectLog::ObjSyncEnd;
```




<hr>



### variable ObjectID 

```C++
uint32 FBattleObjectLog::ObjectID;
```




<hr>



### variable ObjectOffset 

```C++
FVector FBattleObjectLog::ObjectOffset;
```




<hr>



### variable ObjectReg1 

```C++
int32 FBattleObjectLog::ObjectReg1;
```




<hr>



### variable ObjectReg2 

```C++
int32 FBattleObjectLog::ObjectReg2;
```




<hr>



### variable ObjectReg3 

```C++
int32 FBattleObjectLog::ObjectReg3;
```




<hr>



### variable ObjectReg4 

```C++
int32 FBattleObjectLog::ObjectReg4;
```




<hr>



### variable ObjectReg5 

```C++
int32 FBattleObjectLog::ObjectReg5;
```




<hr>



### variable ObjectReg6 

```C++
int32 FBattleObjectLog::ObjectReg6;
```




<hr>



### variable ObjectReg7 

```C++
int32 FBattleObjectLog::ObjectReg7;
```




<hr>



### variable ObjectReg8 

```C++
int32 FBattleObjectLog::ObjectReg8;
```




<hr>



### variable ObjectRotation 

```C++
FRotator FBattleObjectLog::ObjectRotation;
```




<hr>



### variable ObjectScale 

```C++
FVector FBattleObjectLog::ObjectScale;
```




<hr>



### variable ObjectStateIndex 

```C++
int32 FBattleObjectLog::ObjectStateIndex;
```




<hr>



### variable ObjectStateName 

```C++
FGameplayTag FBattleObjectLog::ObjectStateName;
```




<hr>



### variable Player 

```C++
APlayerObject* FBattleObjectLog::Player;
```




<hr>



### variable PosX 

```C++
int32 FBattleObjectLog::PosX;
```




<hr>



### variable PosY 

```C++
int32 FBattleObjectLog::PosY;
```




<hr>



### variable PosZ 

```C++
int32 FBattleObjectLog::PosZ;
```




<hr>



### variable PositionLinkObj 

```C++
ABattleObject* FBattleObjectLog::PositionLinkObj;
```




<hr>



### variable PrevOffsetX 

```C++
int32 FBattleObjectLog::PrevOffsetX;
```




<hr>



### variable PrevOffsetY 

```C++
int32 FBattleObjectLog::PrevOffsetY;
```




<hr>



### variable PrevPosX 

```C++
int32 FBattleObjectLog::PrevPosX;
```




<hr>



### variable PrevPosY 

```C++
int32 FBattleObjectLog::PrevPosY;
```




<hr>



### variable PrevPosZ 

```C++
int32 FBattleObjectLog::PrevPosZ;
```




<hr>



### variable PrevRootMotionX 

```C++
int32 FBattleObjectLog::PrevRootMotionX;
```




<hr>



### variable PrevRootMotionY 

```C++
int32 FBattleObjectLog::PrevRootMotionY;
```




<hr>



### variable PrevRootMotionZ 

```C++
int32 FBattleObjectLog::PrevRootMotionZ;
```




<hr>



### variable Pushback 

```C++
int32 FBattleObjectLog::Pushback;
```




<hr>



### variable R 

```C++
int32 FBattleObjectLog::R;
```




<hr>



### variable ReceivedHit 

```C++
FHitData FBattleObjectLog::ReceivedHit;
```




<hr>



### variable ReceivedHitCommon 

```C++
FHitDataCommon FBattleObjectLog::ReceivedHitCommon;
```




<hr>



### variable ReturnReg 

```C++
bool FBattleObjectLog::ReturnReg;
```




<hr>



### variable SocketName 

```C++
FName FBattleObjectLog::SocketName;
```




<hr>



### variable SocketObj 

```C++
EObjType FBattleObjectLog::SocketObj;
```




<hr>



### variable SocketOffset 

```C++
FVector FBattleObjectLog::SocketOffset;
```




<hr>



### variable SpeedX 

```C++
int32 FBattleObjectLog::SpeedX;
```




<hr>



### variable SpeedXRate 

```C++
int32 FBattleObjectLog::SpeedXRate;
```




<hr>



### variable SpeedXRatePerFrame 

```C++
int32 FBattleObjectLog::SpeedXRatePerFrame;
```




<hr>



### variable SpeedY 

```C++
int32 FBattleObjectLog::SpeedY;
```




<hr>



### variable SpeedYRate 

```C++
int32 FBattleObjectLog::SpeedYRate;
```




<hr>



### variable SpeedYRatePerFrame 

```C++
int32 FBattleObjectLog::SpeedYRatePerFrame;
```




<hr>



### variable SpeedZ 

```C++
int32 FBattleObjectLog::SpeedZ;
```




<hr>



### variable SpeedZRate 

```C++
int32 FBattleObjectLog::SpeedZRate;
```




<hr>



### variable SpeedZRatePerFrame 

```C++
int32 FBattleObjectLog::SpeedZRatePerFrame;
```




<hr>



### variable StopLinkObj 

```C++
ABattleObject* FBattleObjectLog::StopLinkObj;
```




<hr>



### variable StunTime 

```C++
uint32 FBattleObjectLog::StunTime;
```




<hr>



### variable StunTimeMax 

```C++
uint32 FBattleObjectLog::StunTimeMax;
```




<hr>



### variable SubroutineReg1 

```C++
int32 FBattleObjectLog::SubroutineReg1;
```




<hr>



### variable SubroutineReg2 

```C++
int32 FBattleObjectLog::SubroutineReg2;
```




<hr>



### variable SubroutineReg3 

```C++
int32 FBattleObjectLog::SubroutineReg3;
```




<hr>



### variable SubroutineReg4 

```C++
int32 FBattleObjectLog::SubroutineReg4;
```




<hr>



### variable SubroutineReturnVal1 

```C++
int32 FBattleObjectLog::SubroutineReturnVal1;
```




<hr>



### variable SubroutineReturnVal2 

```C++
int32 FBattleObjectLog::SubroutineReturnVal2;
```




<hr>



### variable SubroutineReturnVal3 

```C++
int32 FBattleObjectLog::SubroutineReturnVal3;
```




<hr>



### variable SubroutineReturnVal4 

```C++
int32 FBattleObjectLog::SubroutineReturnVal4;
```




<hr>



### variable SuperArmorData 

```C++
FSuperArmorData FBattleObjectLog::SuperArmorData;
```




<hr>



### variable T 

```C++
int32 FBattleObjectLog::T;
```




<hr>



### variable TimeUntilNextCel 

```C++
int32 FBattleObjectLog::TimeUntilNextCel;
```




<hr>



### variable Timer0 

```C++
int32 FBattleObjectLog::Timer0;
```




<hr>



### variable Timer1 

```C++
int32 FBattleObjectLog::Timer1;
```




<hr>



### variable Transparency 

```C++
float FBattleObjectLog::Transparency;
```




<hr>



### variable TransparencySpeed 

```C++
float FBattleObjectLog::TransparencySpeed;
```




<hr>



### variable UpdateTime 

```C++
int32 FBattleObjectLog::UpdateTime;
```




<hr>



### variable bIsCommonState 

```C++
bool FBattleObjectLog::bIsCommonState;
```




<hr>



### variable bRender 

```C++
bool FBattleObjectLog::bRender;
```




<hr>
## Public Functions Documentation




### function LogForSyncTestFile 

```C++
virtual void FBattleObjectLog::LogForSyncTestFile (
    std::ofstream & file
) 
```




<hr>



### function ~FBattleObjectLog 

```C++
virtual FBattleObjectLog::~FBattleObjectLog () = default
```




<hr>
## Protected Attributes Documentation




### variable PushHeight 

```C++
int32 FBattleObjectLog::PushHeight;
```




<hr>



### variable PushHeightLow 

```C++
int32 FBattleObjectLog::PushHeightLow;
```




<hr>



### variable PushWidth 

```C++
int32 FBattleObjectLog::PushWidth;
```




<hr>



### variable PushWidthExtend 

```C++
int32 FBattleObjectLog::PushWidthExtend;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/NightSkyEngine/Battle/Objects/BattleObject.h`

