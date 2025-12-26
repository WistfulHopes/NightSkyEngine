

# Class ABattleObject



[**ClassList**](annotated.md) **>** [**ABattleObject**](class_a_battle_object.md)








Inherits the following classes: APawn


Inherited by the following classes: [APlayerObject](class_a_player_object.md)
















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
|  int32 | [**AnglePitch\_x1000**](#variable-anglepitch_x1000)   = `0`<br> |
|  int32 | [**AngleRoll\_x1000**](#variable-angleroll_x1000)   = `0`<br> |
|  int32 | [**AngleYaw\_x1000**](#variable-angleyaw_x1000)   = `0`<br> |
|  float | [**AnimBlendIn**](#variable-animblendin)   = `{}`<br> |
|  float | [**AnimBlendOut**](#variable-animblendout)   = `{}`<br> |
|  int32 | [**AnimFrame**](#variable-animframe)   = `0`<br> |
|  TArray&lt; [**FAnimStruct**](struct_f_anim_struct.md) &gt; | [**AnimStructs**](#variable-animstructs)  <br> |
|  uint32 | [**AttackFlags**](#variable-attackflags)   = `0`<br> |
|  [**ABattleObject**](class_a_battle_object.md) \* | [**AttackOwner**](#variable-attackowner)  <br> |
|  [**ABattleObject**](class_a_battle_object.md) \* | [**AttackTarget**](#variable-attacktarget)   = `nullptr`<br> |
|  int32 | [**B**](#variable-b)   = `0`<br> |
|  int32 | [**BlendAnimFrame**](#variable-blendanimframe)   = `0`<br> |
|  FGameplayTag | [**BlendCelName**](#variable-blendcelname)   = `{}`<br> |
|  bool | [**BlendOffset**](#variable-blendoffset)   = `false`<br> |
|  TArray&lt; [**FCollisionBox**](struct_f_collision_box.md) &gt; | [**Boxes**](#variable-boxes)  <br> |
|  int32 | [**CelIndex**](#variable-celindex)   = `0`<br> |
|  FGameplayTag | [**CelName**](#variable-celname)   = `{}`<br> |
|  TObjectPtr&lt; [**ANightSkyCharaSelectGameState**](class_a_night_sky_chara_select_game_state.md) &gt; | [**CharaSelectGameState**](#variable-charaselectgamestate)   = `nullptr`<br> |
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
|  TObjectPtr&lt; [**ANightSkyGameState**](class_a_night_sky_game_state.md) &gt; | [**GameState**](#variable-gamestate)   = `nullptr`<br> |
|  bool | [**GotoLabelActive**](#variable-gotolabelactive)   = `false`<br> |
|  int32 | [**Gravity**](#variable-gravity)   = `1900`<br> |
|  int32 | [**GroundHeight**](#variable-groundheight)   = `0`<br> |
|  [**FHitDataCommon**](struct_f_hit_data_common.md) | [**HitCommon**](#variable-hitcommon)   = `{}`<br> |
|  int32 | [**Hitstop**](#variable-hitstop)   = `0`<br> |
|  [**FHomingParams**](struct_f_homing_params.md) | [**HomingParams**](#variable-homingparams)   = `[**FHomingParams**](struct_f_homing_params.md)()`<br> |
|  int32 | [**Inertia**](#variable-inertia)   = `0`<br> |
|  bool | [**IsActive**](#variable-isactive)   = `false`<br> |
|  bool | [**IsPlayer**](#variable-isplayer)   = `false`<br> |
|  int32 | [**L**](#variable-l)   = `0`<br> |
|  FGameplayTag | [**LabelName**](#variable-labelname)   = `{}`<br> |
|  TObjectPtr&lt; [**ALinkActor**](class_a_link_actor.md) &gt; | [**LinkedActor**](#variable-linkedactor)  <br> |
|  TObjectPtr&lt; UNiagaraComponent &gt; | [**LinkedParticle**](#variable-linkedparticle)   = `nullptr`<br> |
|  [**ABattleObject**](class_a_battle_object.md) \* | [**MaterialLinkObj**](#variable-materiallinkobj)   = `nullptr`<br> |
|  int32 | [**MaxCelTime**](#variable-maxceltime)   = `0`<br> |
|  int32 | [**MiscFlags**](#variable-miscflags)   = `0`<br> |
|  FLinearColor | [**MulColor**](#variable-mulcolor)   = `FLinearColor(1, 1, 1, 1)`<br> |
|  FLinearColor | [**MulFadeColor**](#variable-mulfadecolor)   = `{}`<br> |
|  float | [**MulFadeSpeed**](#variable-mulfadespeed)   = `0`<br> |
|  int32 | [**NextOffsetX**](#variable-nextoffsetx)   = `0`<br> |
|  int32 | [**NextOffsetY**](#variable-nextoffsety)   = `0`<br> |
|  [**FHitData**](struct_f_hit_data.md) | [**NormalHit**](#variable-normalhit)   = `{}`<br> |
|  uint32 | [**ObjNumber**](#variable-objnumber)   = `0`<br> |
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
|  TObjectPtr&lt; [**UState**](class_u_state.md) &gt; | [**ObjectState**](#variable-objectstate)   = `nullptr`<br> |
|  int32 | [**ObjectStateIndex**](#variable-objectstateindex)   = `0`<br> |
|  FGameplayTag | [**ObjectStateName**](#variable-objectstatename)   = `{}`<br> |
|  TArray&lt; [**ABattleObject**](class_a_battle_object.md) \* &gt; | [**ObjectsToIgnoreHitsFrom**](#variable-objectstoignorehitsfrom)  <br> |
|  float | [**OrthoBlendActive**](#variable-orthoblendactive)   = `0`<br> |
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
|  float | [**ScreenSpaceDepthOffset**](#variable-screenspacedepthoffset)   = `0`<br> |
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
|  int32 | [**StunTime**](#variable-stuntime)   = `0`<br> |
|  int32 | [**StunTimeMax**](#variable-stuntimemax)   = `0`<br> |
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
|   | [**ABattleObject**](#function-abattleobject) () <br> |
|  [**ABattleObject**](class_a_battle_object.md) \* | [**AddBattleObject**](#function-addbattleobject) (FGameplayTag InStateName, int32 PosXOffset=0, int32 PosYOffset=0, EPosType PosType=POS\_Player) <br> |
|  [**ABattleObject**](class_a_battle_object.md) \* | [**AddCommonBattleObject**](#function-addcommonbattleobject) (FGameplayTag InStateName, int32 PosXOffset=0, int32 PosYOffset=0, EPosType PosType=POS\_Player) <br> |
|  void | [**AddPosXWithDir**](#function-addposxwithdir) (int InPosX) <br> |
|  void | [**AddSpeedXRaw**](#function-addspeedxraw) (int InSpeedX) <br> |
|  void | [**AttachToSocketOfObject**](#function-attachtosocketofobject) (FName InSocketName, FVector Offset, EObjType ObjType) <br> |
|  int32 | [**CalculateAngleBetweenPoints**](#function-calculateanglebetweenpoints) (EObjType Obj1, EPosType Pos1, EObjType Obj2, EPosType Pos2) <br> |
|  int32 | [**CalculateDistanceBetweenPoints**](#function-calculatedistancebetweenpoints) (EDistanceType Type, EObjType Obj1, EPosType Pos1, EObjType Obj2, EPosType Pos2) <br> |
|  void | [**CalculatePushbox**](#function-calculatepushbox) () <br> |
|  int32 | [**CalculateSpeedAngle**](#function-calculatespeedangle) () const<br> |
|  void | [**CallSubroutine**](#function-callsubroutine) (FGameplayTag Name) <br> |
|  void | [**CallSubroutineWithArgs**](#function-callsubroutinewithargs) (FGameplayTag Name, int32 Arg1, int32 Arg2, int32 Arg3, int32 Arg4) <br> |
|  void | [**CameraShake**](#function-camerashake) (FGameplayTag PatternName, int32 Scale) <br> |
|  bool | [**CheckBoxOverlap**](#function-checkboxoverlap) ([**ABattleObject**](class_a_battle_object.md) \* OtherObj, const EBoxType SelfType, const FGameplayTag SelfCustomType, const EBoxType OtherType, const FGameplayTag OtherCustomType) <br> |
|  bool | [**CheckIsGrounded**](#function-checkisgrounded) () const<br> |
|  void | [**CollisionView**](#function-collisionview) () <br> |
|  void | [**CreateCharaParticle**](#function-createcharaparticle) (FGameplayTag Name, EPosType PosType, FVector Offset=FVector::ZeroVector, FRotator Rotation=FRotator::ZeroRotator) <br> |
|  void | [**CreateCommonParticle**](#function-createcommonparticle) (FGameplayTag Name, EPosType PosType, FVector Offset=FVector::ZeroVector, FRotator Rotation=FRotator::ZeroRotator) <br> |
|  void | [**DeactivateObject**](#function-deactivateobject) () <br> |
|  void | [**DetachFromSocket**](#function-detachfromsocket) () <br> |
|  void | [**DisableInertia**](#function-disableinertia) () <br> |
|  void | [**EnableDeactivateIfBeyondBounds**](#function-enabledeactivateifbeyondbounds) (bool Enable) <br> |
|  void | [**EnableDeactivateOnReceiveHit**](#function-enabledeactivateonreceivehit) (bool Enable) <br> |
|  void | [**EnableDeactivateOnStateChange**](#function-enabledeactivateonstatechange) (bool Enable) <br> |
|  void | [**EnableFlip**](#function-enableflip) (bool Enabled) <br> |
|  void | [**EnableHit**](#function-enablehit) (bool Enabled) <br> |
|  void | [**EnableInertia**](#function-enableinertia) () <br> |
|  void | [**FaceOpponent**](#function-faceopponent) () <br> |
|  void | [**FlipObject**](#function-flipobject) () <br> |
|  int32 | [**GenerateRandomNumber**](#function-generaterandomnumber) (int32 Min, int32 Max) const<br> |
|  UAnimSequenceBase \* | [**GetAnimSequenceForPart**](#function-getanimsequenceforpart) (const FName Part) const<br> |
|  [**ABattleObject**](class_a_battle_object.md) \* | [**GetBattleObject**](#function-getbattleobject) (EObjType Type) <br> |
|  void | [**GetBoxPosition**](#function-getboxposition) (const EBoxType BoxType, const FGameplayTag CustomType, int & OutPosX, int & OutPosY) const<br> |
|  void | [**GetBoxes**](#function-getboxes) () <br> |
|  FGameplayTag | [**GetCelName**](#function-getcelname) () const<br> |
|  UPaperFlipbook \* | [**GetFlipbookForPart**](#function-getflipbookforpart) (const FName Part) const<br> |
|  int32 | [**GetGauge**](#function-getgauge) (int32 GaugeIndex) const<br> |
|  FGameplayTag | [**GetLabelName**](#function-getlabelname) () const<br> |
|  int32 | [**GetPosYCenter**](#function-getposycenter) () const<br> |
|  void | [**GotoLabel**](#function-gotolabel) (FGameplayTag InName) <br> |
|  void | [**HaltMomentum**](#function-haltmomentum) () <br> |
|  void | [**HandleClashCollision**](#function-handleclashcollision) ([**ABattleObject**](class_a_battle_object.md) \* OtherObj) <br> |
|  void | [**HandleCustomCollision\_PostHit**](#function-handlecustomcollision_posthit) ([**ABattleObject**](class_a_battle_object.md) \* OtherObj) <br> |
|  void | [**HandleCustomCollision\_PreHit**](#function-handlecustomcollision_prehit) ([**ABattleObject**](class_a_battle_object.md) \* OtherObj) <br> |
|  void | [**HandleFlip**](#function-handleflip) () <br> |
|  void | [**HandleHitCollision**](#function-handlehitcollision) ([**ABattleObject**](class_a_battle_object.md) \* AttackedObj) <br> |
|  void | [**HandlePushCollision**](#function-handlepushcollision) ([**ABattleObject**](class_a_battle_object.md) \* OtherObj) <br> |
|  void | [**IgnoreSuperFreeze**](#function-ignoresuperfreeze) (bool Ignore) <br> |
|  void | [**InitEventHandler**](#function-initeventhandler) (EEventType EventType, FName FuncName, int32 Value, FGameplayTag SubroutineName) <br> |
|  [**FHitData**](struct_f_hit_data.md) | [**InitHitDataByAttackLevel**](#function-inithitdatabyattacklevel) (bool IsCounter) <br> |
|  void | [**InitObject**](#function-initobject) () <br> |
|  bool | [**IsStopped**](#function-isstopped) () const<br> |
|  bool | [**IsTimerPaused**](#function-istimerpaused) () const<br> |
|  [**ALinkActor**](class_a_link_actor.md) \* | [**LinkActor**](#function-linkactor) (FGameplayTag Name) <br> |
|  void | [**LinkCharaParticle**](#function-linkcharaparticle) (FGameplayTag Name) <br> |
|  void | [**LinkCommonParticle**](#function-linkcommonparticle) (FGameplayTag Name) <br> |
|  void | [**LoadForRollback**](#function-loadforrollback) (const unsigned char \* Buffer) <br> |
|  void | [**PlayCharaSound**](#function-playcharasound) (FGameplayTag Name) <br> |
|  void | [**PlayCommonSound**](#function-playcommonsound) (FGameplayTag Name) <br> |
|  void | [**PosTypeToPosition**](#function-postypetoposition) (EPosType Type, int32 & OutPosX, int32 & OutPosY) const<br> |
|  void | [**PositionLinkUpdate**](#function-positionlinkupdate) () <br> |
|  void | [**RemoveEventHandler**](#function-removeeventhandler) (EEventType EventType) <br> |
|  void | [**RemoveLinkActor**](#function-removelinkactor) () <br> |
|  void | [**ResetObject**](#function-resetobject) () <br> |
|  void | [**SaveForRollback**](#function-saveforrollback) (unsigned char \* Buffer) const<br> |
|  void | [**ScreenPosToWorldPos**](#function-screenpostoworldpos) (const int32 X, const int32 Y, int32 & OutX, int32 & OutY) const<br> |
|  void | [**SetAttacking**](#function-setattacking) (bool Attacking) <br> |
|  void | [**SetBlendCelName**](#function-setblendcelname) (FGameplayTag InName) <br> |
|  void | [**SetCelDuration**](#function-setcelduration) (int32 InTime) <br> |
|  void | [**SetCelName**](#function-setcelname) (FGameplayTag InName) <br> |
|  void | [**SetFacing**](#function-setfacing) (EObjDir NewDir) <br> |
|  void | [**SetFloorCollisionActive**](#function-setfloorcollisionactive) (bool Active) <br> |
|  void | [**SetGauge**](#function-setgauge) (int32 GaugeIndex, int32 Value) <br> |
|  void | [**SetHitOTG**](#function-sethitotg) (bool Enable) <br> |
|  void | [**SetIgnoreHitstunScaling**](#function-setignorehitstunscaling) (bool Ignore) <br> |
|  void | [**SetIgnoreOTG**](#function-setignoreotg) (bool Ignore) <br> |
|  void | [**SetIgnorePushbackScaling**](#function-setignorepushbackscaling) (bool Ignore) <br> |
|  void | [**SetObjectID**](#function-setobjectid) (int InObjectID) <br> |
|  void | [**SetPitch**](#function-setpitch) (int32 Pitch\_x1000) <br> |
|  void | [**SetPlayerHit**](#function-setplayerhit) (bool Enable) <br> |
|  void | [**SetProjectileAttribute**](#function-setprojectileattribute) (bool Attribute) <br> |
|  void | [**SetProrateOnce**](#function-setprorateonce) (bool Once) <br> |
|  void | [**SetPushCollisionActive**](#function-setpushcollisionactive) (bool Active) <br> |
|  void | [**SetPushWidthExtend**](#function-setpushwidthextend) (int32 Extend) <br> |
|  void | [**SetRoll**](#function-setroll) (int32 Roll\_x1000) <br> |
|  void | [**SetSpeedXRaw**](#function-setspeedxraw) (int InSpeedX) <br> |
|  void | [**SetTimeUntilNextCel**](#function-settimeuntilnextcel) (int32 InTime) <br> |
|  void | [**SetWallCollisionActive**](#function-setwallcollisionactive) (bool Active) <br> |
|  void | [**SetYaw**](#function-setyaw) (int32 Yaw\_x1000) <br> |
|  void | [**StartSuperFreeze**](#function-startsuperfreeze) (int Duration, int SelfDuration=0) <br> |
| virtual void | [**Tick**](#function-tick) (float DeltaTime) override<br> |
|  void | [**TriggerEvent**](#function-triggerevent) (EEventType EventType, FGameplayTag StateMachineName) <br> |
| virtual void | [**Update**](#function-update) () <br> |
| virtual void | [**UpdateVisuals**](#function-updatevisuals) () <br> |
| virtual void | [**UpdateVisualsNoRollback**](#function-updatevisualsnorollback) () <br> |
|  void | [**UpdateVisuals\_BP**](#function-updatevisuals_bp) () <br> |
|  void | [**UseGauge**](#function-usegauge) (int32 GaugeIndex, int32 Value) <br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  int32 | [**NormalizeAngle**](#function-normalizeangle) (int32 Angle\_x1000) <br> |






## Protected Attributes

| Type | Name |
| ---: | :--- |
|  int32 | [**PushHeight**](#variable-pushheight)   = `0`<br> |
|  int32 | [**PushHeightLow**](#variable-pushheightlow)   = `0`<br> |
|  int32 | [**PushWidth**](#variable-pushwidth)   = `0`<br> |
|  int32 | [**PushWidthExtend**](#variable-pushwidthextend)   = `0`<br> |
















## Protected Functions

| Type | Name |
| ---: | :--- |
| virtual void | [**BeginPlay**](#function-beginplay) () override<br> |
|  void | [**CalculateHoming**](#function-calculatehoming) () <br> |
|  void | [**FuncCall**](#function-funccall) (const FName & FuncName) const<br> |
|  [**UNightSkyAnimSequenceUserData**](class_u_night_sky_anim_sequence_user_data.md) \* | [**GetAnimSequenceUserData**](#function-getanimsequenceuserdata) (const FName PartName) const<br> |
|  TArray&lt; [**UNightSkyAnimSequenceUserData**](class_u_night_sky_anim_sequence_user_data.md) \* &gt; | [**GetAnimSequenceUserDatas**](#function-getanimsequenceuserdatas) () const<br> |
|  void | [**Move**](#function-move) () <br> |
|  bool | [**SuperArmorSuccess**](#function-superarmorsuccess) (const [**ABattleObject**](class_a_battle_object.md) \* Attacker) const<br> |




## Public Attributes Documentation




### variable ActionReg1 

```C++
int32 ABattleObject::ActionReg1;
```




<hr>



### variable ActionReg2 

```C++
int32 ABattleObject::ActionReg2;
```




<hr>



### variable ActionReg3 

```C++
int32 ABattleObject::ActionReg3;
```




<hr>



### variable ActionReg4 

```C++
int32 ABattleObject::ActionReg4;
```




<hr>



### variable ActionReg5 

```C++
int32 ABattleObject::ActionReg5;
```




<hr>



### variable ActionReg6 

```C++
int32 ABattleObject::ActionReg6;
```




<hr>



### variable ActionReg7 

```C++
int32 ABattleObject::ActionReg7;
```




<hr>



### variable ActionReg8 

```C++
int32 ABattleObject::ActionReg8;
```




<hr>



### variable ActionTime 

```C++
int32 ABattleObject::ActionTime;
```




<hr>



### variable AddColor 

```C++
FLinearColor ABattleObject::AddColor;
```




<hr>



### variable AddFadeColor 

```C++
FLinearColor ABattleObject::AddFadeColor;
```




<hr>



### variable AddFadeSpeed 

```C++
float ABattleObject::AddFadeSpeed;
```




<hr>



### variable AnglePitch\_x1000 

```C++
int32 ABattleObject::AnglePitch_x1000;
```




<hr>



### variable AngleRoll\_x1000 

```C++
int32 ABattleObject::AngleRoll_x1000;
```




<hr>



### variable AngleYaw\_x1000 

```C++
int32 ABattleObject::AngleYaw_x1000;
```




<hr>



### variable AnimBlendIn 

```C++
float ABattleObject::AnimBlendIn;
```




<hr>



### variable AnimBlendOut 

```C++
float ABattleObject::AnimBlendOut;
```




<hr>



### variable AnimFrame 

```C++
int32 ABattleObject::AnimFrame;
```




<hr>



### variable AnimStructs 

```C++
TArray<FAnimStruct> ABattleObject::AnimStructs;
```




<hr>



### variable AttackFlags 

```C++
uint32 ABattleObject::AttackFlags;
```




<hr>



### variable AttackOwner 

```C++
ABattleObject* ABattleObject::AttackOwner;
```




<hr>



### variable AttackTarget 

```C++
ABattleObject* ABattleObject::AttackTarget;
```




<hr>



### variable B 

```C++
int32 ABattleObject::B;
```




<hr>



### variable BlendAnimFrame 

```C++
int32 ABattleObject::BlendAnimFrame;
```




<hr>



### variable BlendCelName 

```C++
FGameplayTag ABattleObject::BlendCelName;
```




<hr>



### variable BlendOffset 

```C++
bool ABattleObject::BlendOffset;
```




<hr>



### variable Boxes 

```C++
TArray<FCollisionBox> ABattleObject::Boxes;
```




<hr>



### variable CelIndex 

```C++
int32 ABattleObject::CelIndex;
```




<hr>



### variable CelName 

```C++
FGameplayTag ABattleObject::CelName;
```




<hr>



### variable CharaSelectGameState 

```C++
TObjectPtr<ANightSkyCharaSelectGameState> ABattleObject::CharaSelectGameState;
```




<hr>



### variable ColPosX 

```C++
int32 ABattleObject::ColPosX;
```




<hr>



### variable ColPosY 

```C++
int32 ABattleObject::ColPosY;
```




<hr>



### variable CounterHit 

```C++
FHitData ABattleObject::CounterHit;
```




<hr>



### variable DamageColor 

```C++
FLinearColor ABattleObject::DamageColor;
```




<hr>



### variable DamageColor2 

```C++
FLinearColor ABattleObject::DamageColor2;
```




<hr>



### variable Direction 

```C++
TEnumAsByte<EObjDir> ABattleObject::Direction;
```




<hr>



### variable DrawPriority 

```C++
int32 ABattleObject::DrawPriority;
```




<hr>



### variable DrawPriorityLinkObj 

```C++
ABattleObject* ABattleObject::DrawPriorityLinkObj;
```




<hr>



### variable EventHandlers 

```C++
FEventHandler ABattleObject::EventHandlers[EVT_NUM];
```




<hr>



### variable FadeTransparency 

```C++
float ABattleObject::FadeTransparency;
```




<hr>



### variable FrameBlendPosition 

```C++
float ABattleObject::FrameBlendPosition;
```




<hr>



### variable GameState 

```C++
TObjectPtr<ANightSkyGameState> ABattleObject::GameState;
```




<hr>



### variable GotoLabelActive 

```C++
bool ABattleObject::GotoLabelActive;
```




<hr>



### variable Gravity 

```C++
int32 ABattleObject::Gravity;
```




<hr>



### variable GroundHeight 

```C++
int32 ABattleObject::GroundHeight;
```




<hr>



### variable HitCommon 

```C++
FHitDataCommon ABattleObject::HitCommon;
```




<hr>



### variable Hitstop 

```C++
int32 ABattleObject::Hitstop;
```




<hr>



### variable HomingParams 

```C++
FHomingParams ABattleObject::HomingParams;
```




<hr>



### variable Inertia 

```C++
int32 ABattleObject::Inertia;
```




<hr>



### variable IsActive 

```C++
bool ABattleObject::IsActive;
```




<hr>



### variable IsPlayer 

```C++
bool ABattleObject::IsPlayer;
```




<hr>



### variable L 

```C++
int32 ABattleObject::L;
```




<hr>



### variable LabelName 

```C++
FGameplayTag ABattleObject::LabelName;
```




<hr>



### variable LinkedActor 

```C++
TObjectPtr<ALinkActor> ABattleObject::LinkedActor;
```




<hr>



### variable LinkedParticle 

```C++
TObjectPtr<UNiagaraComponent> ABattleObject::LinkedParticle;
```




<hr>



### variable MaterialLinkObj 

```C++
ABattleObject* ABattleObject::MaterialLinkObj;
```




<hr>



### variable MaxCelTime 

```C++
int32 ABattleObject::MaxCelTime;
```




<hr>



### variable MiscFlags 

```C++
int32 ABattleObject::MiscFlags;
```




<hr>



### variable MulColor 

```C++
FLinearColor ABattleObject::MulColor;
```




<hr>



### variable MulFadeColor 

```C++
FLinearColor ABattleObject::MulFadeColor;
```




<hr>



### variable MulFadeSpeed 

```C++
float ABattleObject::MulFadeSpeed;
```




<hr>



### variable NextOffsetX 

```C++
int32 ABattleObject::NextOffsetX;
```




<hr>



### variable NextOffsetY 

```C++
int32 ABattleObject::NextOffsetY;
```




<hr>



### variable NormalHit 

```C++
FHitData ABattleObject::NormalHit;
```




<hr>



### variable ObjNumber 

```C++
uint32 ABattleObject::ObjNumber;
```




<hr>



### variable ObjSync 

```C++
unsigned char ABattleObject::ObjSync;
```




<hr>



### variable ObjSyncEnd 

```C++
unsigned char ABattleObject::ObjSyncEnd;
```




<hr>



### variable ObjectID 

```C++
uint32 ABattleObject::ObjectID;
```




<hr>



### variable ObjectOffset 

```C++
FVector ABattleObject::ObjectOffset;
```




<hr>



### variable ObjectReg1 

```C++
int32 ABattleObject::ObjectReg1;
```




<hr>



### variable ObjectReg2 

```C++
int32 ABattleObject::ObjectReg2;
```




<hr>



### variable ObjectReg3 

```C++
int32 ABattleObject::ObjectReg3;
```




<hr>



### variable ObjectReg4 

```C++
int32 ABattleObject::ObjectReg4;
```




<hr>



### variable ObjectReg5 

```C++
int32 ABattleObject::ObjectReg5;
```




<hr>



### variable ObjectReg6 

```C++
int32 ABattleObject::ObjectReg6;
```




<hr>



### variable ObjectReg7 

```C++
int32 ABattleObject::ObjectReg7;
```




<hr>



### variable ObjectReg8 

```C++
int32 ABattleObject::ObjectReg8;
```




<hr>



### variable ObjectRotation 

```C++
FRotator ABattleObject::ObjectRotation;
```




<hr>



### variable ObjectScale 

```C++
FVector ABattleObject::ObjectScale;
```




<hr>



### variable ObjectState 

```C++
TObjectPtr<UState> ABattleObject::ObjectState;
```




<hr>



### variable ObjectStateIndex 

```C++
int32 ABattleObject::ObjectStateIndex;
```




<hr>



### variable ObjectStateName 

```C++
FGameplayTag ABattleObject::ObjectStateName;
```




<hr>



### variable ObjectsToIgnoreHitsFrom 

```C++
TArray<ABattleObject*> ABattleObject::ObjectsToIgnoreHitsFrom;
```




<hr>



### variable OrthoBlendActive 

```C++
float ABattleObject::OrthoBlendActive;
```




<hr>



### variable Player 

```C++
APlayerObject* ABattleObject::Player;
```




<hr>



### variable PosX 

```C++
int32 ABattleObject::PosX;
```




<hr>



### variable PosY 

```C++
int32 ABattleObject::PosY;
```




<hr>



### variable PosZ 

```C++
int32 ABattleObject::PosZ;
```




<hr>



### variable PositionLinkObj 

```C++
ABattleObject* ABattleObject::PositionLinkObj;
```




<hr>



### variable PrevOffsetX 

```C++
int32 ABattleObject::PrevOffsetX;
```




<hr>



### variable PrevOffsetY 

```C++
int32 ABattleObject::PrevOffsetY;
```




<hr>



### variable PrevPosX 

```C++
int32 ABattleObject::PrevPosX;
```




<hr>



### variable PrevPosY 

```C++
int32 ABattleObject::PrevPosY;
```




<hr>



### variable PrevPosZ 

```C++
int32 ABattleObject::PrevPosZ;
```




<hr>



### variable PrevRootMotionX 

```C++
int32 ABattleObject::PrevRootMotionX;
```




<hr>



### variable PrevRootMotionY 

```C++
int32 ABattleObject::PrevRootMotionY;
```




<hr>



### variable PrevRootMotionZ 

```C++
int32 ABattleObject::PrevRootMotionZ;
```




<hr>



### variable Pushback 

```C++
int32 ABattleObject::Pushback;
```




<hr>



### variable R 

```C++
int32 ABattleObject::R;
```




<hr>



### variable ReceivedHit 

```C++
FHitData ABattleObject::ReceivedHit;
```




<hr>



### variable ReceivedHitCommon 

```C++
FHitDataCommon ABattleObject::ReceivedHitCommon;
```




<hr>



### variable ScreenSpaceDepthOffset 

```C++
float ABattleObject::ScreenSpaceDepthOffset;
```




<hr>



### variable SocketName 

```C++
FName ABattleObject::SocketName;
```




<hr>



### variable SocketObj 

```C++
EObjType ABattleObject::SocketObj;
```




<hr>



### variable SocketOffset 

```C++
FVector ABattleObject::SocketOffset;
```




<hr>



### variable SpeedX 

```C++
int32 ABattleObject::SpeedX;
```




<hr>



### variable SpeedXRate 

```C++
int32 ABattleObject::SpeedXRate;
```




<hr>



### variable SpeedXRatePerFrame 

```C++
int32 ABattleObject::SpeedXRatePerFrame;
```




<hr>



### variable SpeedY 

```C++
int32 ABattleObject::SpeedY;
```




<hr>



### variable SpeedYRate 

```C++
int32 ABattleObject::SpeedYRate;
```




<hr>



### variable SpeedYRatePerFrame 

```C++
int32 ABattleObject::SpeedYRatePerFrame;
```




<hr>



### variable SpeedZ 

```C++
int32 ABattleObject::SpeedZ;
```




<hr>



### variable SpeedZRate 

```C++
int32 ABattleObject::SpeedZRate;
```




<hr>



### variable SpeedZRatePerFrame 

```C++
int32 ABattleObject::SpeedZRatePerFrame;
```




<hr>



### variable StopLinkObj 

```C++
ABattleObject* ABattleObject::StopLinkObj;
```




<hr>



### variable StunTime 

```C++
int32 ABattleObject::StunTime;
```




<hr>



### variable StunTimeMax 

```C++
int32 ABattleObject::StunTimeMax;
```




<hr>



### variable SubroutineReg1 

```C++
int32 ABattleObject::SubroutineReg1;
```




<hr>



### variable SubroutineReg2 

```C++
int32 ABattleObject::SubroutineReg2;
```




<hr>



### variable SubroutineReg3 

```C++
int32 ABattleObject::SubroutineReg3;
```




<hr>



### variable SubroutineReg4 

```C++
int32 ABattleObject::SubroutineReg4;
```




<hr>



### variable SubroutineReturnVal1 

```C++
int32 ABattleObject::SubroutineReturnVal1;
```




<hr>



### variable SubroutineReturnVal2 

```C++
int32 ABattleObject::SubroutineReturnVal2;
```




<hr>



### variable SubroutineReturnVal3 

```C++
int32 ABattleObject::SubroutineReturnVal3;
```




<hr>



### variable SubroutineReturnVal4 

```C++
int32 ABattleObject::SubroutineReturnVal4;
```




<hr>



### variable SuperArmorData 

```C++
FSuperArmorData ABattleObject::SuperArmorData;
```




<hr>



### variable T 

```C++
int32 ABattleObject::T;
```




<hr>



### variable TimeUntilNextCel 

```C++
int32 ABattleObject::TimeUntilNextCel;
```




<hr>



### variable Timer0 

```C++
int32 ABattleObject::Timer0;
```




<hr>



### variable Timer1 

```C++
int32 ABattleObject::Timer1;
```




<hr>



### variable Transparency 

```C++
float ABattleObject::Transparency;
```




<hr>



### variable TransparencySpeed 

```C++
float ABattleObject::TransparencySpeed;
```




<hr>



### variable UpdateTime 

```C++
int32 ABattleObject::UpdateTime;
```




<hr>



### variable bIsCommonState 

```C++
bool ABattleObject::bIsCommonState;
```




<hr>



### variable bRender 

```C++
bool ABattleObject::bRender;
```




<hr>
## Public Functions Documentation




### function ABattleObject 

```C++
ABattleObject::ABattleObject () 
```




<hr>



### function AddBattleObject 

```C++
ABattleObject * ABattleObject::AddBattleObject (
    FGameplayTag InStateName,
    int32 PosXOffset=0,
    int32 PosYOffset=0,
    EPosType PosType=POS_Player
) 
```




<hr>



### function AddCommonBattleObject 

```C++
ABattleObject * ABattleObject::AddCommonBattleObject (
    FGameplayTag InStateName,
    int32 PosXOffset=0,
    int32 PosYOffset=0,
    EPosType PosType=POS_Player
) 
```




<hr>



### function AddPosXWithDir 

```C++
void ABattleObject::AddPosXWithDir (
    int InPosX
) 
```




<hr>



### function AddSpeedXRaw 

```C++
void ABattleObject::AddSpeedXRaw (
    int InSpeedX
) 
```




<hr>



### function AttachToSocketOfObject 

```C++
void ABattleObject::AttachToSocketOfObject (
    FName InSocketName,
    FVector Offset,
    EObjType ObjType
) 
```




<hr>



### function CalculateAngleBetweenPoints 

```C++
int32 ABattleObject::CalculateAngleBetweenPoints (
    EObjType Obj1,
    EPosType Pos1,
    EObjType Obj2,
    EPosType Pos2
) 
```




<hr>



### function CalculateDistanceBetweenPoints 

```C++
int32 ABattleObject::CalculateDistanceBetweenPoints (
    EDistanceType Type,
    EObjType Obj1,
    EPosType Pos1,
    EObjType Obj2,
    EPosType Pos2
) 
```




<hr>



### function CalculatePushbox 

```C++
void ABattleObject::CalculatePushbox () 
```




<hr>



### function CalculateSpeedAngle 

```C++
int32 ABattleObject::CalculateSpeedAngle () const
```




<hr>



### function CallSubroutine 

```C++
void ABattleObject::CallSubroutine (
    FGameplayTag Name
) 
```




<hr>



### function CallSubroutineWithArgs 

```C++
void ABattleObject::CallSubroutineWithArgs (
    FGameplayTag Name,
    int32 Arg1,
    int32 Arg2,
    int32 Arg3,
    int32 Arg4
) 
```




<hr>



### function CameraShake 

```C++
void ABattleObject::CameraShake (
    FGameplayTag PatternName,
    int32 Scale
) 
```




<hr>



### function CheckBoxOverlap 

```C++
bool ABattleObject::CheckBoxOverlap (
    ABattleObject * OtherObj,
    const EBoxType SelfType,
    const FGameplayTag SelfCustomType,
    const EBoxType OtherType,
    const FGameplayTag OtherCustomType
) 
```




<hr>



### function CheckIsGrounded 

```C++
bool ABattleObject::CheckIsGrounded () const
```




<hr>



### function CollisionView 

```C++
void ABattleObject::CollisionView () 
```




<hr>



### function CreateCharaParticle 

```C++
void ABattleObject::CreateCharaParticle (
    FGameplayTag Name,
    EPosType PosType,
    FVector Offset=FVector::ZeroVector,
    FRotator Rotation=FRotator::ZeroRotator
) 
```




<hr>



### function CreateCommonParticle 

```C++
void ABattleObject::CreateCommonParticle (
    FGameplayTag Name,
    EPosType PosType,
    FVector Offset=FVector::ZeroVector,
    FRotator Rotation=FRotator::ZeroRotator
) 
```




<hr>



### function DeactivateObject 

```C++
void ABattleObject::DeactivateObject () 
```




<hr>



### function DetachFromSocket 

```C++
void ABattleObject::DetachFromSocket () 
```




<hr>



### function DisableInertia 

```C++
void ABattleObject::DisableInertia () 
```




<hr>



### function EnableDeactivateIfBeyondBounds 

```C++
void ABattleObject::EnableDeactivateIfBeyondBounds (
    bool Enable
) 
```




<hr>



### function EnableDeactivateOnReceiveHit 

```C++
void ABattleObject::EnableDeactivateOnReceiveHit (
    bool Enable
) 
```




<hr>



### function EnableDeactivateOnStateChange 

```C++
void ABattleObject::EnableDeactivateOnStateChange (
    bool Enable
) 
```




<hr>



### function EnableFlip 

```C++
void ABattleObject::EnableFlip (
    bool Enabled
) 
```




<hr>



### function EnableHit 

```C++
void ABattleObject::EnableHit (
    bool Enabled
) 
```




<hr>



### function EnableInertia 

```C++
void ABattleObject::EnableInertia () 
```




<hr>



### function FaceOpponent 

```C++
void ABattleObject::FaceOpponent () 
```




<hr>



### function FlipObject 

```C++
void ABattleObject::FlipObject () 
```




<hr>



### function GenerateRandomNumber 

```C++
int32 ABattleObject::GenerateRandomNumber (
    int32 Min,
    int32 Max
) const
```




<hr>



### function GetAnimSequenceForPart 

```C++
UAnimSequenceBase * ABattleObject::GetAnimSequenceForPart (
    const FName Part
) const
```




<hr>



### function GetBattleObject 

```C++
ABattleObject * ABattleObject::GetBattleObject (
    EObjType Type
) 
```




<hr>



### function GetBoxPosition 

```C++
void ABattleObject::GetBoxPosition (
    const EBoxType BoxType,
    const FGameplayTag CustomType,
    int & OutPosX,
    int & OutPosY
) const
```




<hr>



### function GetBoxes 

```C++
void ABattleObject::GetBoxes () 
```




<hr>



### function GetCelName 

```C++
FGameplayTag ABattleObject::GetCelName () const
```




<hr>



### function GetFlipbookForPart 

```C++
UPaperFlipbook * ABattleObject::GetFlipbookForPart (
    const FName Part
) const
```




<hr>



### function GetGauge 

```C++
int32 ABattleObject::GetGauge (
    int32 GaugeIndex
) const
```




<hr>



### function GetLabelName 

```C++
FGameplayTag ABattleObject::GetLabelName () const
```




<hr>



### function GetPosYCenter 

```C++
int32 ABattleObject::GetPosYCenter () const
```




<hr>



### function GotoLabel 

```C++
void ABattleObject::GotoLabel (
    FGameplayTag InName
) 
```




<hr>



### function HaltMomentum 

```C++
void ABattleObject::HaltMomentum () 
```




<hr>



### function HandleClashCollision 

```C++
void ABattleObject::HandleClashCollision (
    ABattleObject * OtherObj
) 
```




<hr>



### function HandleCustomCollision\_PostHit 

```C++
void ABattleObject::HandleCustomCollision_PostHit (
    ABattleObject * OtherObj
) 
```




<hr>



### function HandleCustomCollision\_PreHit 

```C++
void ABattleObject::HandleCustomCollision_PreHit (
    ABattleObject * OtherObj
) 
```




<hr>



### function HandleFlip 

```C++
void ABattleObject::HandleFlip () 
```




<hr>



### function HandleHitCollision 

```C++
void ABattleObject::HandleHitCollision (
    ABattleObject * AttackedObj
) 
```




<hr>



### function HandlePushCollision 

```C++
void ABattleObject::HandlePushCollision (
    ABattleObject * OtherObj
) 
```




<hr>



### function IgnoreSuperFreeze 

```C++
void ABattleObject::IgnoreSuperFreeze (
    bool Ignore
) 
```




<hr>



### function InitEventHandler 

```C++
void ABattleObject::InitEventHandler (
    EEventType EventType,
    FName FuncName,
    int32 Value,
    FGameplayTag SubroutineName
) 
```




<hr>



### function InitHitDataByAttackLevel 

```C++
FHitData ABattleObject::InitHitDataByAttackLevel (
    bool IsCounter
) 
```




<hr>



### function InitObject 

```C++
void ABattleObject::InitObject () 
```




<hr>



### function IsStopped 

```C++
bool ABattleObject::IsStopped () const
```




<hr>



### function IsTimerPaused 

```C++
bool ABattleObject::IsTimerPaused () const
```




<hr>



### function LinkActor 

```C++
ALinkActor * ABattleObject::LinkActor (
    FGameplayTag Name
) 
```




<hr>



### function LinkCharaParticle 

```C++
void ABattleObject::LinkCharaParticle (
    FGameplayTag Name
) 
```




<hr>



### function LinkCommonParticle 

```C++
void ABattleObject::LinkCommonParticle (
    FGameplayTag Name
) 
```




<hr>



### function LoadForRollback 

```C++
void ABattleObject::LoadForRollback (
    const unsigned char * Buffer
) 
```




<hr>



### function PlayCharaSound 

```C++
void ABattleObject::PlayCharaSound (
    FGameplayTag Name
) 
```




<hr>



### function PlayCommonSound 

```C++
void ABattleObject::PlayCommonSound (
    FGameplayTag Name
) 
```




<hr>



### function PosTypeToPosition 

```C++
void ABattleObject::PosTypeToPosition (
    EPosType Type,
    int32 & OutPosX,
    int32 & OutPosY
) const
```




<hr>



### function PositionLinkUpdate 

```C++
void ABattleObject::PositionLinkUpdate () 
```




<hr>



### function RemoveEventHandler 

```C++
void ABattleObject::RemoveEventHandler (
    EEventType EventType
) 
```




<hr>



### function RemoveLinkActor 

```C++
void ABattleObject::RemoveLinkActor () 
```




<hr>



### function ResetObject 

```C++
void ABattleObject::ResetObject () 
```




<hr>



### function SaveForRollback 

```C++
void ABattleObject::SaveForRollback (
    unsigned char * Buffer
) const
```




<hr>



### function ScreenPosToWorldPos 

```C++
void ABattleObject::ScreenPosToWorldPos (
    const int32 X,
    const int32 Y,
    int32 & OutX,
    int32 & OutY
) const
```




<hr>



### function SetAttacking 

```C++
void ABattleObject::SetAttacking (
    bool Attacking
) 
```




<hr>



### function SetBlendCelName 

```C++
void ABattleObject::SetBlendCelName (
    FGameplayTag InName
) 
```




<hr>



### function SetCelDuration 

```C++
void ABattleObject::SetCelDuration (
    int32 InTime
) 
```




<hr>



### function SetCelName 

```C++
void ABattleObject::SetCelName (
    FGameplayTag InName
) 
```




<hr>



### function SetFacing 

```C++
void ABattleObject::SetFacing (
    EObjDir NewDir
) 
```




<hr>



### function SetFloorCollisionActive 

```C++
void ABattleObject::SetFloorCollisionActive (
    bool Active
) 
```




<hr>



### function SetGauge 

```C++
void ABattleObject::SetGauge (
    int32 GaugeIndex,
    int32 Value
) 
```




<hr>



### function SetHitOTG 

```C++
void ABattleObject::SetHitOTG (
    bool Enable
) 
```




<hr>



### function SetIgnoreHitstunScaling 

```C++
void ABattleObject::SetIgnoreHitstunScaling (
    bool Ignore
) 
```




<hr>



### function SetIgnoreOTG 

```C++
void ABattleObject::SetIgnoreOTG (
    bool Ignore
) 
```




<hr>



### function SetIgnorePushbackScaling 

```C++
void ABattleObject::SetIgnorePushbackScaling (
    bool Ignore
) 
```




<hr>



### function SetObjectID 

```C++
void ABattleObject::SetObjectID (
    int InObjectID
) 
```




<hr>



### function SetPitch 

```C++
void ABattleObject::SetPitch (
    int32 Pitch_x1000
) 
```




<hr>



### function SetPlayerHit 

```C++
void ABattleObject::SetPlayerHit (
    bool Enable
) 
```




<hr>



### function SetProjectileAttribute 

```C++
void ABattleObject::SetProjectileAttribute (
    bool Attribute
) 
```




<hr>



### function SetProrateOnce 

```C++
void ABattleObject::SetProrateOnce (
    bool Once
) 
```




<hr>



### function SetPushCollisionActive 

```C++
void ABattleObject::SetPushCollisionActive (
    bool Active
) 
```




<hr>



### function SetPushWidthExtend 

```C++
void ABattleObject::SetPushWidthExtend (
    int32 Extend
) 
```




<hr>



### function SetRoll 

```C++
void ABattleObject::SetRoll (
    int32 Roll_x1000
) 
```




<hr>



### function SetSpeedXRaw 

```C++
void ABattleObject::SetSpeedXRaw (
    int InSpeedX
) 
```




<hr>



### function SetTimeUntilNextCel 

```C++
void ABattleObject::SetTimeUntilNextCel (
    int32 InTime
) 
```




<hr>



### function SetWallCollisionActive 

```C++
void ABattleObject::SetWallCollisionActive (
    bool Active
) 
```




<hr>



### function SetYaw 

```C++
void ABattleObject::SetYaw (
    int32 Yaw_x1000
) 
```




<hr>



### function StartSuperFreeze 

```C++
void ABattleObject::StartSuperFreeze (
    int Duration,
    int SelfDuration=0
) 
```




<hr>



### function Tick 

```C++
virtual void ABattleObject::Tick (
    float DeltaTime
) override
```




<hr>



### function TriggerEvent 

```C++
void ABattleObject::TriggerEvent (
    EEventType EventType,
    FGameplayTag StateMachineName
) 
```




<hr>



### function Update 

```C++
virtual void ABattleObject::Update () 
```




<hr>



### function UpdateVisuals 

```C++
virtual void ABattleObject::UpdateVisuals () 
```




<hr>



### function UpdateVisualsNoRollback 

```C++
virtual void ABattleObject::UpdateVisualsNoRollback () 
```




<hr>



### function UpdateVisuals\_BP 

```C++
void ABattleObject::UpdateVisuals_BP () 
```




<hr>



### function UseGauge 

```C++
void ABattleObject::UseGauge (
    int32 GaugeIndex,
    int32 Value
) 
```




<hr>
## Public Static Functions Documentation




### function NormalizeAngle 

```C++
static int32 ABattleObject::NormalizeAngle (
    int32 Angle_x1000
) 
```




<hr>
## Protected Attributes Documentation




### variable PushHeight 

```C++
int32 ABattleObject::PushHeight;
```




<hr>



### variable PushHeightLow 

```C++
int32 ABattleObject::PushHeightLow;
```




<hr>



### variable PushWidth 

```C++
int32 ABattleObject::PushWidth;
```




<hr>



### variable PushWidthExtend 

```C++
int32 ABattleObject::PushWidthExtend;
```




<hr>
## Protected Functions Documentation




### function BeginPlay 

```C++
virtual void ABattleObject::BeginPlay () override
```




<hr>



### function CalculateHoming 

```C++
void ABattleObject::CalculateHoming () 
```




<hr>



### function FuncCall 

```C++
void ABattleObject::FuncCall (
    const FName & FuncName
) const
```




<hr>



### function GetAnimSequenceUserData 

```C++
UNightSkyAnimSequenceUserData * ABattleObject::GetAnimSequenceUserData (
    const FName PartName
) const
```




<hr>



### function GetAnimSequenceUserDatas 

```C++
TArray< UNightSkyAnimSequenceUserData * > ABattleObject::GetAnimSequenceUserDatas () const
```




<hr>



### function Move 

```C++
void ABattleObject::Move () 
```




<hr>



### function SuperArmorSuccess 

```C++
bool ABattleObject::SuperArmorSuccess (
    const ABattleObject * Attacker
) const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/NightSkyEngine/Battle/Objects/BattleObject.h`

