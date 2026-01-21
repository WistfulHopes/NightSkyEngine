

# Class APlayerObject



[**ClassList**](annotated.md) **>** [**APlayerObject**](class_a_player_object.md)








Inherits the following classes: [ABattleObject](class_a_battle_object.md)






















## Public Attributes

| Type | Name |
| ---: | :--- |
|  int32 | [**AirDashCount**](#variable-airdashcount)  <br> |
|  int32 | [**AirDashMinimumHeight**](#variable-airdashminimumheight)  <br> |
|  uint32 | [**AirDashTimer**](#variable-airdashtimer)   = `0`<br> |
|  int32 | [**AirJumpCount**](#variable-airjumpcount)  <br> |
|  int32 | [**AirPushHeight**](#variable-airpushheight)  <br> |
|  int32 | [**AirPushHeightLow**](#variable-airpushheightlow)  <br> |
|  int32 | [**AirPushWidth**](#variable-airpushwidth)  <br> |
|  int32 | [**BAirDashNoAttackTime**](#variable-bairdashnoattacktime)  <br> |
|  int32 | [**BAirDashSpeed**](#variable-bairdashspeed)  <br> |
|  int32 | [**BAirDashTime**](#variable-bairdashtime)  <br> |
|  int32 | [**BDashGravity**](#variable-bdashgravity)  <br> |
|  int32 | [**BDashHeight**](#variable-bdashheight)  <br> |
|  int32 | [**BDashSpeed**](#variable-bdashspeed)  <br> |
|  int32 | [**BJumpSpeed**](#variable-bjumpspeed)  <br> |
|  int32 | [**BSuperJumpSpeed**](#variable-bsuperjumpspeed)  <br> |
|  int32 | [**BWalkSpeed**](#variable-bwalkspeed)  <br> |
|  [**UCameraShakeData**](class_u_camera_shake_data.md) \* | [**CameraShakeData**](#variable-camerashakedata)  <br> |
|  bool | [**CanProximityThrow**](#variable-canproximitythrow)  <br> |
|  bool | [**CanReverseBeat**](#variable-canreversebeat)  <br> |
|  TArray&lt; int32 &gt; | [**ChainCancelOptions**](#variable-chaincanceloptions)  <br> |
|  [**UParticleData**](class_u_particle_data.md) \* | [**CharaParticleData**](#variable-charaparticledata)  <br> |
|  [**UStateData**](class_u_state_data.md) \* | [**CharaStateData**](#variable-charastatedata)  <br> |
|  [**USubroutineData**](class_u_subroutine_data.md) \* | [**CharaSubroutineData**](#variable-charasubroutinedata)  <br> |
|  int32 | [**CloseNormalRange**](#variable-closenormalrange)  <br> |
|  int32 | [**CmnPlayerReg1**](#variable-cmnplayerreg1)   = `0`<br> |
|  int32 | [**CmnPlayerReg2**](#variable-cmnplayerreg2)   = `0`<br> |
|  int32 | [**CmnPlayerReg3**](#variable-cmnplayerreg3)   = `0`<br> |
|  int32 | [**CmnPlayerReg4**](#variable-cmnplayerreg4)   = `0`<br> |
|  int32 | [**CmnPlayerReg5**](#variable-cmnplayerreg5)   = `0`<br> |
|  int32 | [**CmnPlayerReg6**](#variable-cmnplayerreg6)   = `0`<br> |
|  int32 | [**CmnPlayerReg7**](#variable-cmnplayerreg7)   = `0`<br> |
|  int32 | [**CmnPlayerReg8**](#variable-cmnplayerreg8)   = `0`<br> |
|  [**UCollisionData**](class_u_collision_data.md) \* | [**CollisionData**](#variable-collisiondata)  <br> |
|  int32 | [**ColorIndex**](#variable-colorindex)   = `1`<br> |
|  int32 | [**ComboCounter**](#variable-combocounter)  <br> |
|  int32 | [**ComboRate**](#variable-comborate)   = `60`<br> |
|  int32 | [**ComboTimer**](#variable-combotimer)  <br> |
|  [**UCollisionData**](class_u_collision_data.md) \* | [**CommonCollisionData**](#variable-commoncollisiondata)  <br> |
|  [**ULinkActorData**](class_u_link_actor_data.md) \* | [**CommonLinkActorData**](#variable-commonlinkactordata)  <br> |
|  [**UStateData**](class_u_state_data.md) \* | [**CommonObjectStateData**](#variable-commonobjectstatedata)  <br> |
|  TArray&lt; FGameplayTag &gt; | [**CommonObjectStateNames**](#variable-commonobjectstatenames)  <br> |
|  TArray&lt; [**UState**](class_u_state.md) \* &gt; | [**CommonObjectStates**](#variable-commonobjectstates)  <br> |
|  [**UParticleData**](class_u_particle_data.md) \* | [**CommonParticleData**](#variable-commonparticledata)  <br> |
|  [**USequenceData**](class_u_sequence_data.md) \* | [**CommonSequenceData**](#variable-commonsequencedata)  <br> |
|  [**USoundData**](class_u_sound_data.md) \* | [**CommonSoundData**](#variable-commonsounddata)  <br> |
|  [**USubroutineData**](class_u_subroutine_data.md) \* | [**CommonSubroutineData**](#variable-commonsubroutinedata)  <br> |
|  TArray&lt; FGameplayTag &gt; | [**CommonSubroutineNames**](#variable-commonsubroutinenames)  <br> |
|  TArray&lt; [**USubroutine**](class_u_subroutine.md) \* &gt; | [**CommonSubroutines**](#variable-commonsubroutines)  <br> |
|  bool | [**ComponentVisible**](#variable-componentvisible)  <br> |
|  int32 | [**CrouchPushHeight**](#variable-crouchpushheight)  <br> |
|  int32 | [**CrouchPushWidth**](#variable-crouchpushwidth)  <br> |
|  int32 | [**CurrentHealth**](#variable-currenthealth)  <br> |
|  TMap&lt; FGameplayTag, FGameplayTag &gt; | [**DamageReactionCels**](#variable-damagereactioncels)  <br> |
|  [**APlayerObject**](class_a_player_object.md) \* | [**Enemy**](#variable-enemy)  <br> |
|  TArray&lt; [**FExtraGauge**](struct_f_extra_gauge.md) &gt; | [**ExtraGauges**](#variable-extragauges)  <br> |
|  int32 | [**FAirDashNoAttackTime**](#variable-fairdashnoattacktime)  <br> |
|  int32 | [**FAirDashSpeed**](#variable-fairdashspeed)  <br> |
|  int32 | [**FAirDashTime**](#variable-fairdashtime)  <br> |
|  int32 | [**FDashAccel**](#variable-fdashaccel)  <br> |
|  int32 | [**FDashFriction**](#variable-fdashfriction)  <br> |
|  int32 | [**FDashInitSpeed**](#variable-fdashinitspeed)  <br> |
|  int32 | [**FDashMaxSpeed**](#variable-fdashmaxspeed)  <br> |
|  int32 | [**FJumpSpeed**](#variable-fjumpspeed)  <br> |
|  int32 | [**FSuperJumpSpeed**](#variable-fsuperjumpspeed)  <br> |
|  int32 | [**FWalkSpeed**](#variable-fwalkspeed)  <br> |
|  bool | [**FlipInputs**](#variable-flipinputs)  <br> |
|  int32 | [**ForwardAirDashMeterGain**](#variable-forwardairdashmetergain)  <br> |
|  int32 | [**ForwardDashMeterGain**](#variable-forwarddashmetergain)  <br> |
|  int32 | [**ForwardJumpMeterGain**](#variable-forwardjumpmetergain)  <br> |
|  int32 | [**ForwardWalkMeterGain**](#variable-forwardwalkmetergain)  <br> |
|  uint32 | [**Inputs**](#variable-inputs)  <br> |
|  bool | [**IntroEndFlag**](#variable-introendflag)   = `false`<br> |
|  FGameplayTag | [**IntroName**](#variable-introname)  <br> |
|  uint32 | [**InvulnFlags**](#variable-invulnflags)   = `0`<br> |
|  int32 | [**JumpGravity**](#variable-jumpgravity)  <br> |
|  int32 | [**JumpHeight**](#variable-jumpheight)  <br> |
|  [**ULinkActorData**](class_u_link_actor_data.md) \* | [**LinkActorData**](#variable-linkactordata)  <br> |
|  [**UMaterialData**](class_u_material_data.md) \* | [**MaterialData**](#variable-materialdata)  <br> |
|  int32 | [**MaxColorIndex**](#variable-maxcolorindex)   = `2`<br> |
|  int32 | [**MaxHealth**](#variable-maxhealth)  <br> |
|  int32 | [**MaxMeter**](#variable-maxmeter)   = `10000`<br> |
|  int32 | [**MaxOTGCount**](#variable-maxotgcount)  <br> |
|  int32 | [**MeterPercentOnHit**](#variable-meterpercentonhit)   = `72`<br> |
|  int32 | [**MeterPercentOnHitGuard**](#variable-meterpercentonhitguard)   = `18`<br> |
|  int32 | [**MeterPercentOnReceiveHit**](#variable-meterpercentonreceivehit)   = `40`<br> |
|  int32 | [**MeterPercentOnReceiveHitGuard**](#variable-meterpercentonreceivehitguard)   = `10`<br> |
|  TArray&lt; int32 &gt; | [**MovesUsedInChain**](#variable-movesusedinchain)   = `{}`<br> |
|  TArray&lt; int32 &gt; | [**MovesUsedInCombo**](#variable-movesusedincombo)   = `{}`<br> |
|  int32 | [**OTGCount**](#variable-otgcount)  <br> |
|  [**UStateData**](class_u_state_data.md) \* | [**ObjectStateData**](#variable-objectstatedata)  <br> |
|  TArray&lt; FGameplayTag &gt; | [**ObjectStateNames**](#variable-objectstatenames)  <br> |
|  TArray&lt; [**UState**](class_u_state.md) \* &gt; | [**ObjectStates**](#variable-objectstates)  <br> |
|  int32 | [**OtgProration**](#variable-otgproration)   = `80`<br> |
|  uint32 | [**PlayerFlags**](#variable-playerflags)   = `0`<br> |
|  int32 | [**PlayerIndex**](#variable-playerindex)  <br> |
|  int32 | [**PlayerReg1**](#variable-playerreg1)   = `0`<br> |
|  int32 | [**PlayerReg2**](#variable-playerreg2)   = `0`<br> |
|  int32 | [**PlayerReg3**](#variable-playerreg3)   = `0`<br> |
|  int32 | [**PlayerReg4**](#variable-playerreg4)   = `0`<br> |
|  int32 | [**PlayerReg5**](#variable-playerreg5)   = `0`<br> |
|  int32 | [**PlayerReg6**](#variable-playerreg6)   = `0`<br> |
|  int32 | [**PlayerReg7**](#variable-playerreg7)   = `0`<br> |
|  int32 | [**PlayerReg8**](#variable-playerreg8)   = `0`<br> |
|  unsigned char | [**PlayerSync**](#variable-playersync)  <br> |
|  unsigned char | [**PlayerSyncEnd**](#variable-playersyncend)  <br> |
|  [**FStateMachine**](struct_f_state_machine.md) | [**PrimaryStateMachine**](#variable-primarystatemachine)  <br> |
|  [**FInputCondition**](struct_f_input_condition.md) | [**ProximityThrowInput**](#variable-proximitythrowinput)  <br> |
|  int32 | [**RecoverableHealth**](#variable-recoverablehealth)  <br> |
|  bool | [**RoundEndFlag**](#variable-roundendflag)   = `false`<br> |
|  int32 | [**RoundWinTimer**](#variable-roundwintimer)   = `120`<br> |
|  [**USequenceData**](class_u_sequence_data.md) \* | [**SequenceData**](#variable-sequencedata)  <br> |
|  [**USoundData**](class_u_sound_data.md) \* | [**SoundData**](#variable-sounddata)  <br> |
|  TEnumAsByte&lt; EActionStance &gt; | [**Stance**](#variable-stance)  <br> |
|  int32 | [**StandPushHeight**](#variable-standpushheight)  <br> |
|  int32 | [**StandPushWidth**](#variable-standpushwidth)  <br> |
|  FGameplayTag | [**StateEntryName**](#variable-stateentryname)  <br> |
|  [**ABattleObject**](class_a_battle_object.md) \* | [**StoredBattleObjects**](#variable-storedbattleobjects)  <br> |
|  [**FInputBuffer**](struct_f_input_buffer.md) | [**StoredInputBuffer**](#variable-storedinputbuffer)  <br> |
|  TArray&lt; [**FLinkedActorContainer**](struct_f_linked_actor_container.md) &gt; | [**StoredLinkActors**](#variable-storedlinkactors)  <br> |
|  uint32 | [**StrikeInvulnerableTimer**](#variable-strikeinvulnerabletimer)   = `0`<br> |
|  TMap&lt; FGameplayTag, [**UStateData**](class_u_state_data.md) \* &gt; | [**SubStateData**](#variable-substatedata)  <br> |
|  TArray&lt; [**FStateMachine**](struct_f_state_machine.md) &gt; | [**SubStateMachines**](#variable-substatemachines)  <br> |
|  TArray&lt; FGameplayTag &gt; | [**SubroutineNames**](#variable-subroutinenames)  <br> |
|  TArray&lt; [**USubroutine**](class_u_subroutine.md) \* &gt; | [**Subroutines**](#variable-subroutines)  <br> |
|  int32 | [**SuperJumpGravity**](#variable-superjumpgravity)  <br> |
|  int32 | [**SuperJumpHeight**](#variable-superjumpheight)  <br> |
|  int32 | [**TeamIndex**](#variable-teamindex)  <br> |
|  uint32 | [**ThrowInvulnerableTimer**](#variable-throwinvulnerabletimer)   = `0`<br> |
|  int32 | [**ThrowResistAfterWakeUp**](#variable-throwresistafterwakeup)   = `5`<br> |
|  uint32 | [**ThrowResistTimer**](#variable-throwresisttimer)   = `0`<br> |
|  int32 | [**ThrowTechWindow**](#variable-throwtechwindow)   = `6`<br> |
|  int32 | [**TotalProration**](#variable-totalproration)   = `10000`<br> |
|  [**USoundData**](class_u_sound_data.md) \* | [**VoiceData**](#variable-voicedata)  <br> |
|  int32 | [**WallTouchTimer**](#variable-walltouchtimer)  <br> |
|  TArray&lt; int32 &gt; | [**WhiffCancelOptions**](#variable-whiffcanceloptions)  <br> |
|  bool | [**bCrumpled**](#variable-bcrumpled)  <br> |
|  bool | [**bIsCpu**](#variable-biscpu)   = `false`<br> |
|  bool | [**bLimitCrumple**](#variable-blimitcrumple)   = `true`<br> |
|  bool | [**bMirrorWhenFlip**](#variable-bmirrorwhenflip)  <br> |


## Public Attributes inherited from ABattleObject

See [ABattleObject](class_a_battle_object.md)

| Type | Name |
| ---: | :--- |
|  int32 | [**ActionReg1**](class_a_battle_object.md#variable-actionreg1)   = `0`<br> |
|  int32 | [**ActionReg2**](class_a_battle_object.md#variable-actionreg2)   = `0`<br> |
|  int32 | [**ActionReg3**](class_a_battle_object.md#variable-actionreg3)   = `0`<br> |
|  int32 | [**ActionReg4**](class_a_battle_object.md#variable-actionreg4)   = `0`<br> |
|  int32 | [**ActionReg5**](class_a_battle_object.md#variable-actionreg5)   = `0`<br> |
|  int32 | [**ActionReg6**](class_a_battle_object.md#variable-actionreg6)   = `0`<br> |
|  int32 | [**ActionReg7**](class_a_battle_object.md#variable-actionreg7)   = `0`<br> |
|  int32 | [**ActionReg8**](class_a_battle_object.md#variable-actionreg8)   = `0`<br> |
|  int32 | [**ActionTime**](class_a_battle_object.md#variable-actiontime)   = `0`<br> |
|  FLinearColor | [**AddColor**](class_a_battle_object.md#variable-addcolor)   = `FLinearColor(0, 0, 0, 1)`<br> |
|  FLinearColor | [**AddFadeColor**](class_a_battle_object.md#variable-addfadecolor)   = `{}`<br> |
|  float | [**AddFadeSpeed**](class_a_battle_object.md#variable-addfadespeed)   = `0`<br> |
|  int32 | [**AnglePitch\_x1000**](class_a_battle_object.md#variable-anglepitch_x1000)   = `0`<br> |
|  int32 | [**AngleRoll\_x1000**](class_a_battle_object.md#variable-angleroll_x1000)   = `0`<br> |
|  int32 | [**AngleYaw\_x1000**](class_a_battle_object.md#variable-angleyaw_x1000)   = `0`<br> |
|  float | [**AnimBlendIn**](class_a_battle_object.md#variable-animblendin)   = `{}`<br> |
|  float | [**AnimBlendOut**](class_a_battle_object.md#variable-animblendout)   = `{}`<br> |
|  int32 | [**AnimFrame**](class_a_battle_object.md#variable-animframe)   = `0`<br> |
|  TArray&lt; [**FAnimStruct**](struct_f_anim_struct.md) &gt; | [**AnimStructs**](class_a_battle_object.md#variable-animstructs)  <br> |
|  uint32 | [**AttackFlags**](class_a_battle_object.md#variable-attackflags)   = `0`<br> |
|  [**ABattleObject**](class_a_battle_object.md) \* | [**AttackOwner**](class_a_battle_object.md#variable-attackowner)  <br> |
|  [**ABattleObject**](class_a_battle_object.md) \* | [**AttackTarget**](class_a_battle_object.md#variable-attacktarget)   = `nullptr`<br> |
|  int32 | [**B**](class_a_battle_object.md#variable-b)   = `0`<br> |
|  int32 | [**BlendAnimFrame**](class_a_battle_object.md#variable-blendanimframe)   = `0`<br> |
|  FGameplayTag | [**BlendCelName**](class_a_battle_object.md#variable-blendcelname)   = `{}`<br> |
|  bool | [**BlendOffset**](class_a_battle_object.md#variable-blendoffset)   = `false`<br> |
|  TArray&lt; [**FCollisionBox**](struct_f_collision_box.md) &gt; | [**Boxes**](class_a_battle_object.md#variable-boxes)  <br> |
|  int32 | [**CelIndex**](class_a_battle_object.md#variable-celindex)   = `0`<br> |
|  FGameplayTag | [**CelName**](class_a_battle_object.md#variable-celname)   = `{}`<br> |
|  TObjectPtr&lt; [**ANightSkyCharaSelectGameState**](class_a_night_sky_chara_select_game_state.md) &gt; | [**CharaSelectGameState**](class_a_battle_object.md#variable-charaselectgamestate)   = `nullptr`<br> |
|  int32 | [**ColPosX**](class_a_battle_object.md#variable-colposx)   = `0`<br> |
|  int32 | [**ColPosY**](class_a_battle_object.md#variable-colposy)   = `0`<br> |
|  [**FHitData**](struct_f_hit_data.md) | [**CounterHit**](class_a_battle_object.md#variable-counterhit)   = `{}`<br> |
|  FLinearColor | [**DamageColor**](class_a_battle_object.md#variable-damagecolor)   = `FLinearColor(1, 1, 1, 1)`<br> |
|  FLinearColor | [**DamageColor2**](class_a_battle_object.md#variable-damagecolor2)   = `FLinearColor(1, 1, 1, 1)`<br> |
|  TEnumAsByte&lt; EObjDir &gt; | [**Direction**](class_a_battle_object.md#variable-direction)   = `DIR\_Right`<br> |
|  int32 | [**DrawPriority**](class_a_battle_object.md#variable-drawpriority)   = `0`<br> |
|  [**ABattleObject**](class_a_battle_object.md) \* | [**DrawPriorityLinkObj**](class_a_battle_object.md#variable-drawprioritylinkobj)   = `nullptr`<br> |
|  [**FEventHandler**](struct_f_event_handler.md) | [**EventHandlers**](class_a_battle_object.md#variable-eventhandlers)   = `{}`<br> |
|  float | [**FadeTransparency**](class_a_battle_object.md#variable-fadetransparency)   = `1`<br> |
|  float | [**FrameBlendPosition**](class_a_battle_object.md#variable-frameblendposition)   = `0`<br> |
|  TObjectPtr&lt; [**ANightSkyGameState**](class_a_night_sky_game_state.md) &gt; | [**GameState**](class_a_battle_object.md#variable-gamestate)   = `nullptr`<br> |
|  bool | [**GotoLabelActive**](class_a_battle_object.md#variable-gotolabelactive)   = `false`<br> |
|  int32 | [**Gravity**](class_a_battle_object.md#variable-gravity)   = `1900`<br> |
|  int32 | [**GroundHeight**](class_a_battle_object.md#variable-groundheight)   = `0`<br> |
|  [**FHitDataCommon**](struct_f_hit_data_common.md) | [**HitCommon**](class_a_battle_object.md#variable-hitcommon)   = `{}`<br> |
|  int32 | [**Hitstop**](class_a_battle_object.md#variable-hitstop)   = `0`<br> |
|  [**FHomingParams**](struct_f_homing_params.md) | [**HomingParams**](class_a_battle_object.md#variable-homingparams)   = `[**FHomingParams**](struct_f_homing_params.md)()`<br> |
|  int32 | [**Inertia**](class_a_battle_object.md#variable-inertia)   = `0`<br> |
|  bool | [**IsActive**](class_a_battle_object.md#variable-isactive)   = `false`<br> |
|  bool | [**IsPlayer**](class_a_battle_object.md#variable-isplayer)   = `false`<br> |
|  int32 | [**L**](class_a_battle_object.md#variable-l)   = `0`<br> |
|  FGameplayTag | [**LabelName**](class_a_battle_object.md#variable-labelname)   = `{}`<br> |
|  TObjectPtr&lt; [**ALinkActor**](class_a_link_actor.md) &gt; | [**LinkedActor**](class_a_battle_object.md#variable-linkedactor)  <br> |
|  TObjectPtr&lt; UNiagaraComponent &gt; | [**LinkedParticle**](class_a_battle_object.md#variable-linkedparticle)   = `nullptr`<br> |
|  [**ABattleObject**](class_a_battle_object.md) \* | [**MaterialLinkObj**](class_a_battle_object.md#variable-materiallinkobj)   = `nullptr`<br> |
|  int32 | [**MaxCelTime**](class_a_battle_object.md#variable-maxceltime)   = `0`<br> |
|  int32 | [**MiscFlags**](class_a_battle_object.md#variable-miscflags)   = `0`<br> |
|  FLinearColor | [**MulColor**](class_a_battle_object.md#variable-mulcolor)   = `FLinearColor(1, 1, 1, 1)`<br> |
|  FLinearColor | [**MulFadeColor**](class_a_battle_object.md#variable-mulfadecolor)   = `{}`<br> |
|  float | [**MulFadeSpeed**](class_a_battle_object.md#variable-mulfadespeed)   = `0`<br> |
|  int32 | [**NextOffsetX**](class_a_battle_object.md#variable-nextoffsetx)   = `0`<br> |
|  int32 | [**NextOffsetY**](class_a_battle_object.md#variable-nextoffsety)   = `0`<br> |
|  [**FHitData**](struct_f_hit_data.md) | [**NormalHit**](class_a_battle_object.md#variable-normalhit)   = `{}`<br> |
|  uint32 | [**ObjNumber**](class_a_battle_object.md#variable-objnumber)   = `0`<br> |
|  unsigned char | [**ObjSync**](class_a_battle_object.md#variable-objsync)   = `0`<br> |
|  unsigned char | [**ObjSyncEnd**](class_a_battle_object.md#variable-objsyncend)   = `0`<br> |
|  uint32 | [**ObjectID**](class_a_battle_object.md#variable-objectid)   = `0`<br> |
|  FVector | [**ObjectOffset**](class_a_battle_object.md#variable-objectoffset)   = `FVector::ZeroVector`<br> |
|  int32 | [**ObjectReg1**](class_a_battle_object.md#variable-objectreg1)   = `0`<br> |
|  int32 | [**ObjectReg2**](class_a_battle_object.md#variable-objectreg2)   = `0`<br> |
|  int32 | [**ObjectReg3**](class_a_battle_object.md#variable-objectreg3)   = `0`<br> |
|  int32 | [**ObjectReg4**](class_a_battle_object.md#variable-objectreg4)   = `0`<br> |
|  int32 | [**ObjectReg5**](class_a_battle_object.md#variable-objectreg5)   = `0`<br> |
|  int32 | [**ObjectReg6**](class_a_battle_object.md#variable-objectreg6)   = `0`<br> |
|  int32 | [**ObjectReg7**](class_a_battle_object.md#variable-objectreg7)   = `0`<br> |
|  int32 | [**ObjectReg8**](class_a_battle_object.md#variable-objectreg8)   = `0`<br> |
|  FRotator | [**ObjectRotation**](class_a_battle_object.md#variable-objectrotation)   = `FRotator::ZeroRotator`<br> |
|  FVector | [**ObjectScale**](class_a_battle_object.md#variable-objectscale)   = `FVector::One()`<br> |
|  TObjectPtr&lt; [**UState**](class_u_state.md) &gt; | [**ObjectState**](class_a_battle_object.md#variable-objectstate)   = `nullptr`<br> |
|  int32 | [**ObjectStateIndex**](class_a_battle_object.md#variable-objectstateindex)   = `0`<br> |
|  FGameplayTag | [**ObjectStateName**](class_a_battle_object.md#variable-objectstatename)   = `{}`<br> |
|  TArray&lt; [**ABattleObject**](class_a_battle_object.md) \* &gt; | [**ObjectsToIgnoreHitsFrom**](class_a_battle_object.md#variable-objectstoignorehitsfrom)  <br> |
|  float | [**OrthoBlendActive**](class_a_battle_object.md#variable-orthoblendactive)   = `0`<br> |
|  [**APlayerObject**](class_a_player_object.md) \* | [**Player**](class_a_battle_object.md#variable-player)   = `nullptr`<br> |
|  int32 | [**PosX**](class_a_battle_object.md#variable-posx)   = `0`<br> |
|  int32 | [**PosY**](class_a_battle_object.md#variable-posy)   = `0`<br> |
|  int32 | [**PosZ**](class_a_battle_object.md#variable-posz)   = `0`<br> |
|  [**ABattleObject**](class_a_battle_object.md) \* | [**PositionLinkObj**](class_a_battle_object.md#variable-positionlinkobj)   = `nullptr`<br> |
|  int32 | [**PrevOffsetX**](class_a_battle_object.md#variable-prevoffsetx)   = `0`<br> |
|  int32 | [**PrevOffsetY**](class_a_battle_object.md#variable-prevoffsety)   = `0`<br> |
|  int32 | [**PrevPosX**](class_a_battle_object.md#variable-prevposx)   = `0`<br> |
|  int32 | [**PrevPosY**](class_a_battle_object.md#variable-prevposy)   = `0`<br> |
|  int32 | [**PrevPosZ**](class_a_battle_object.md#variable-prevposz)   = `0`<br> |
|  int32 | [**PrevRootMotionX**](class_a_battle_object.md#variable-prevrootmotionx)   = `0`<br> |
|  int32 | [**PrevRootMotionY**](class_a_battle_object.md#variable-prevrootmotiony)   = `0`<br> |
|  int32 | [**PrevRootMotionZ**](class_a_battle_object.md#variable-prevrootmotionz)   = `0`<br> |
|  int32 | [**Pushback**](class_a_battle_object.md#variable-pushback)   = `0`<br> |
|  int32 | [**R**](class_a_battle_object.md#variable-r)   = `0`<br> |
|  [**FHitData**](struct_f_hit_data.md) | [**ReceivedHit**](class_a_battle_object.md#variable-receivedhit)   = `{}`<br> |
|  [**FHitDataCommon**](struct_f_hit_data_common.md) | [**ReceivedHitCommon**](class_a_battle_object.md#variable-receivedhitcommon)   = `{}`<br> |
|  float | [**ScreenSpaceDepthOffset**](class_a_battle_object.md#variable-screenspacedepthoffset)   = `0`<br> |
|  FName | [**SocketName**](class_a_battle_object.md#variable-socketname)   = `{}`<br> |
|  EObjType | [**SocketObj**](class_a_battle_object.md#variable-socketobj)   = `OBJ\_Self`<br> |
|  FVector | [**SocketOffset**](class_a_battle_object.md#variable-socketoffset)   = `FVector::ZeroVector`<br> |
|  int32 | [**SpeedX**](class_a_battle_object.md#variable-speedx)   = `0`<br> |
|  int32 | [**SpeedXRate**](class_a_battle_object.md#variable-speedxrate)   = `100`<br> |
|  int32 | [**SpeedXRatePerFrame**](class_a_battle_object.md#variable-speedxrateperframe)   = `100`<br> |
|  int32 | [**SpeedY**](class_a_battle_object.md#variable-speedy)   = `0`<br> |
|  int32 | [**SpeedYRate**](class_a_battle_object.md#variable-speedyrate)   = `100`<br> |
|  int32 | [**SpeedYRatePerFrame**](class_a_battle_object.md#variable-speedyrateperframe)   = `100`<br> |
|  int32 | [**SpeedZ**](class_a_battle_object.md#variable-speedz)   = `0`<br> |
|  int32 | [**SpeedZRate**](class_a_battle_object.md#variable-speedzrate)   = `100`<br> |
|  int32 | [**SpeedZRatePerFrame**](class_a_battle_object.md#variable-speedzrateperframe)   = `100`<br> |
|  [**ABattleObject**](class_a_battle_object.md) \* | [**StopLinkObj**](class_a_battle_object.md#variable-stoplinkobj)   = `nullptr`<br> |
|  int32 | [**StunTime**](class_a_battle_object.md#variable-stuntime)   = `0`<br> |
|  int32 | [**StunTimeMax**](class_a_battle_object.md#variable-stuntimemax)   = `0`<br> |
|  int32 | [**SubroutineReg1**](class_a_battle_object.md#variable-subroutinereg1)   = `0`<br> |
|  int32 | [**SubroutineReg2**](class_a_battle_object.md#variable-subroutinereg2)   = `0`<br> |
|  int32 | [**SubroutineReg3**](class_a_battle_object.md#variable-subroutinereg3)   = `0`<br> |
|  int32 | [**SubroutineReg4**](class_a_battle_object.md#variable-subroutinereg4)   = `0`<br> |
|  int32 | [**SubroutineReturnVal1**](class_a_battle_object.md#variable-subroutinereturnval1)   = `0`<br> |
|  int32 | [**SubroutineReturnVal2**](class_a_battle_object.md#variable-subroutinereturnval2)   = `0`<br> |
|  int32 | [**SubroutineReturnVal3**](class_a_battle_object.md#variable-subroutinereturnval3)   = `0`<br> |
|  int32 | [**SubroutineReturnVal4**](class_a_battle_object.md#variable-subroutinereturnval4)   = `0`<br> |
|  [**FSuperArmorData**](struct_f_super_armor_data.md) | [**SuperArmorData**](class_a_battle_object.md#variable-superarmordata)   = `[**FSuperArmorData**](struct_f_super_armor_data.md)()`<br> |
|  int32 | [**T**](class_a_battle_object.md#variable-t)   = `0`<br> |
|  int32 | [**TimeUntilNextCel**](class_a_battle_object.md#variable-timeuntilnextcel)   = `0`<br> |
|  int32 | [**Timer0**](class_a_battle_object.md#variable-timer0)   = `0`<br> |
|  int32 | [**Timer1**](class_a_battle_object.md#variable-timer1)   = `0`<br> |
|  float | [**Transparency**](class_a_battle_object.md#variable-transparency)   = `1`<br> |
|  float | [**TransparencySpeed**](class_a_battle_object.md#variable-transparencyspeed)   = `0`<br> |
|  int32 | [**UpdateTime**](class_a_battle_object.md#variable-updatetime)   = `0`<br> |
|  bool | [**bIsCommonState**](class_a_battle_object.md#variable-biscommonstate)   = `false`<br> |
|  bool | [**bRender**](class_a_battle_object.md#variable-brender)   = `true`<br> |






























## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**APlayerObject**](#function-aplayerobject) () <br> |
|  void | [**AddAirDash**](#function-addairdash) (int32 NewAirDash) <br> |
|  void | [**AddAirJump**](#function-addairjump) (int32 NewAirJump) <br> |
|  void | [**AddAutoComboCancel**](#function-addautocombocancel) (FGameplayTag Option, EInputFlags Button) <br> |
|  void | [**AddBattleObjectToStorage**](#function-addbattleobjecttostorage) ([**ABattleObject**](class_a_battle_object.md) \* InActor, int Index) <br> |
|  void | [**AddChainCancelOption**](#function-addchaincanceloption) (FGameplayTag Option) <br> |
|  void | [**AddHealth**](#function-addhealth) (int Value) <br> |
|  void | [**AddMeter**](#function-addmeter) (int Meter) <br> |
|  void | [**AddObjectState**](#function-addobjectstate) (FGameplayTag Name, [**UState**](class_u_state.md) \* State, bool IsCommon) <br> |
|  void | [**AddRecoverableHealth**](#function-addrecoverablehealth) (int Value) <br> |
|  void | [**AddState**](#function-addstate) (FGameplayTag Name, [**UState**](class_u_state.md) \* State, FGameplayTag StateMachineName) <br> |
|  void | [**AddSubroutine**](#function-addsubroutine) (FGameplayTag Name, [**USubroutine**](class_u_subroutine.md) \* Subroutine, bool IsCommon) <br> |
|  void | [**AddWhiffCancelOption**](#function-addwhiffcanceloption) (FGameplayTag Option) <br> |
|  void | [**BattleHudVisibility**](#function-battlehudvisibility) (bool Visible) <br> |
|  [**APlayerObject**](class_a_player_object.md) \* | [**CallAssist**](#function-callassist) (int AssistIndex, FGameplayTag AssistName) <br> |
|  bool | [**CanEnterState**](#function-canenterstate) ([**UState**](class_u_state.md) \* State, FGameplayTag StateMachineName) <br> |
|  bool | [**CheckEnemyInRange**](#function-checkenemyinrange) (int32 XBegin, int32 XEnd, int32 YBegin, int32 YEnd) const<br> |
|  bool | [**CheckHasHit**](#function-checkhashit) () const<br> |
|  bool | [**CheckInput**](#function-checkinput) (const [**FInputCondition**](struct_f_input_condition.md) & Input) <br> |
|  bool | [**CheckIsAttacking**](#function-checkisattacking) () const<br> |
|  bool | [**CheckIsStunned**](#function-checkisstunned) () const<br> |
|  bool | [**CheckStateEnabled**](#function-checkstateenabled) (EStateType StateType, FGameplayTag CustomStateType, FGameplayTag StateMachineName) <br> |
|  void | [**DisableAll**](#function-disableall) (FGameplayTag StateMachineName) <br> |
|  void | [**DisableCustomState**](#function-disablecustomstate) (FGameplayTag CustomStateType, FGameplayTag StateMachineName) <br> |
|  void | [**DisableState**](#function-disablestate) (UPARAM(meta=(Bitmask, BitmaskEnum="/Script/NightSkyEngine.EEnableFlags")) int32 Bitmask, FGameplayTag StateMachineName) <br> |
|  void | [**EditorUpdate**](#function-editorupdate) () <br> |
|  void | [**EmptyStateMachine**](#function-emptystatemachine) () <br> |
|  void | [**EnableAll**](#function-enableall) (FGameplayTag StateMachineName) <br> |
|  void | [**EnableAttacks**](#function-enableattacks) () <br> |
|  void | [**EnableCancelIntoSelf**](#function-enablecancelintoself) (bool Enable) <br> |
|  void | [**EnableChainCancel**](#function-enablechaincancel) (bool Enable) <br> |
|  void | [**EnableCustomState**](#function-enablecustomstate) (FGameplayTag CustomStateType, FGameplayTag StateMachineName) <br> |
|  void | [**EnableForwardAirdashCancel**](#function-enableforwardairdashcancel) (bool Enable) <br> |
|  void | [**EnableJumpCancel**](#function-enablejumpcancel) (bool Enable) <br> |
|  void | [**EnableReverseBeat**](#function-enablereversebeat) (bool Enable) <br> |
|  void | [**EnableSpecialCancel**](#function-enablespecialcancel) (bool Enable) <br> |
|  void | [**EnableState**](#function-enablestate) (UPARAM(meta=(Bitmask, BitmaskEnum="/Script/NightSkyEngine.EEnableFlags")) int32 Bitmask, FGameplayTag StateMachineName) <br> |
|  void | [**EnableSuperCancel**](#function-enablesupercancel) (bool Enable) <br> |
|  void | [**EnableWhiffCancel**](#function-enablewhiffcancel) (bool Enable) <br> |
|  void | [**EndMatch**](#function-endmatch) () const<br> |
|  void | [**EndRound**](#function-endround) () const<br> |
|  void | [**ForceEnableFarNormal**](#function-forceenablefarnormal) (bool Enable) <br> |
|  EBlockType | [**GetAttackBlockType**](#function-getattackblocktype) () const<br> |
|  FGameplayTag | [**GetCurrentStateName**](#function-getcurrentstatename) (FGameplayTag StateMachineName) <br> |
|  int32 | [**GetEnableFlags**](#function-getenableflags) (FGameplayTag StateMachineName) <br> |
|  FGameplayTag | [**GetLastStateName**](#function-getlaststatename) () const<br> |
|  FGameplayTag | [**GetStateEntryName**](#function-getstateentryname) () const<br> |
|  [**FStateMachine**](struct_f_state_machine.md) & | [**GetStateMachine**](#function-getstatemachine) (FGameplayTag StateMachineName) <br> |
|  bool | [**HandleAutoCombo**](#function-handleautocombo) (int32 StateIndex, [**FStateMachine**](struct_f_state_machine.md) & StateMachine) <br> |
|  void | [**HandleBlockAction**](#function-handleblockaction) () <br> |
|  void | [**HandleBufferedState**](#function-handlebufferedstate-12) () <br> |
|  void | [**HandleBufferedState**](#function-handlebufferedstate-22) ([**FStateMachine**](struct_f_state_machine.md) & StateMachine) <br> |
|  void | [**HandleEndCombo**](#function-handleendcombo) () <br> |
|  void | [**HandleFlipInput**](#function-handleflipinput) () <br> |
|  void | [**HandleHitAction**](#function-handlehitaction) (EHitAction HACT) <br> |
|  void | [**HandleProximityBlock**](#function-handleproximityblock) () <br> |
|  bool | [**HandleStateInputs**](#function-handlestateinputs) (int32 StateIndex, bool Buffer, [**FStateMachine**](struct_f_state_machine.md) & StateMachine) <br> |
|  void | [**HandleStateMachine**](#function-handlestatemachine) (bool Buffer, [**FStateMachine**](struct_f_state_machine.md) & StateMachine) <br> |
|  bool | [**HandleStateTransition**](#function-handlestatetransition) (int32 StateIndex, bool Buffer, [**FStateMachine**](struct_f_state_machine.md) & StateMachine) <br> |
|  void | [**InitBP**](#function-initbp) () <br> |
|  void | [**InitPlayer**](#function-initplayer) () <br> |
|  bool | [**IsCorrectBlock**](#function-iscorrectblock) (EBlockType BlockType) <br> |
|  bool | [**IsEnemyAttackState**](#function-isenemyattackstate) () const<br> |
|  bool | [**IsEnemyBlocking**](#function-isenemyblocking) () const<br> |
|  bool | [**IsEnemyThrow**](#function-isenemythrow) () const<br> |
|  bool | [**IsInvulnerable**](#function-isinvulnerable) (const [**ABattleObject**](class_a_battle_object.md) \* Attacker) const<br> |
|  bool | [**IsInvulnerable\_BP**](#function-isinvulnerable_bp) () const<br> |
|  bool | [**IsMainPlayer**](#function-ismainplayer) () const<br> |
|  bool | [**IsOnScreen**](#function-isonscreen) () const<br> |
|  bool | [**IsTouchingWall**](#function-istouchingwall) () const<br> |
|  bool | [**JumpToState**](#function-jumptostate) (FGameplayTag NewName, FGameplayTag StateMachineName, bool IsLabel=false) <br> |
|  bool | [**JumpToStateByClass**](#function-jumptostatebyclass) (TSubclassOf&lt; [**UState**](class_u_state.md) &gt; Class, FGameplayTag StateMachineName, bool IsLabel=false) <br> |
|  bool | [**JumpToStateByClassPrimary**](#function-jumptostatebyclassprimary) (TSubclassOf&lt; [**UState**](class_u_state.md) &gt; Class, bool IsLabel=false) <br> |
|  bool | [**JumpToStatePrimary**](#function-jumptostateprimary) (FGameplayTag NewName, bool IsLabel=false) <br> |
|  void | [**LoadForRollbackBP**](#function-loadforrollbackbp) (TArray&lt; uint8 &gt; InBytes) <br> |
|  void | [**LoadForRollbackPlayer**](#function-loadforrollbackplayer) (const unsigned char \* Buffer) <br> |
|  void | [**OnStateChange**](#function-onstatechange) () <br> |
|  void | [**PauseRoundTimer**](#function-pauseroundtimer) (bool Pause) <br> |
|  void | [**PlayCommonLevelSequence**](#function-playcommonlevelsequence) (FGameplayTag Name) <br> |
|  void | [**PlayLevelSequence**](#function-playlevelsequence) (FGameplayTag Name) <br> |
|  void | [**PlayVoiceLine**](#function-playvoiceline) (FGameplayTag Name) <br> |
|  void | [**PostStateChange**](#function-poststatechange) () <br> |
|  void | [**RecoverHealth**](#function-recoverhealth) (int Value) <br> |
|  void | [**RemoveAutoComboCancel**](#function-removeautocombocancel) (EInputFlags Button) <br> |
|  void | [**RemoveChainCancelOption**](#function-removechaincanceloption) (FGameplayTag Option) <br> |
|  void | [**RemoveWhiffCancelOption**](#function-removewhiffcanceloption) (FGameplayTag Option) <br> |
|  void | [**ResetAirDash**](#function-resetairdash) () <br> |
|  void | [**ResetAirJump**](#function-resetairjump) () <br> |
|  void | [**RoundInit**](#function-roundinit) (bool ResetHealth) <br> |
|  void | [**RoundInit\_BP**](#function-roundinit_bp) () <br> |
|  TArray&lt; uint8 &gt; | [**SaveForRollbackBP**](#function-saveforrollbackbp) () <br> |
|  void | [**SaveForRollbackPlayer**](#function-saveforrollbackplayer) (unsigned char \* Buffer) const<br> |
|  void | [**SetAirDashNoAttackTimer**](#function-setairdashnoattacktimer) (bool IsForward) <br> |
|  void | [**SetAirDashTimer**](#function-setairdashtimer) (bool IsForward) <br> |
|  void | [**SetDamageReactionCel**](#function-setdamagereactioncel) (FGameplayTag Type) <br> |
|  void | [**SetDefaultComponentVisibility**](#function-setdefaultcomponentvisibility) () <br> |
|  void | [**SetDefaultLandingAction**](#function-setdefaultlandingaction) (bool Enable) <br> |
|  void | [**SetGuardValues**](#function-setguardvalues) () <br> |
|  void | [**SetHeadAttribute**](#function-setheadattribute) (bool Attribute) <br> |
|  void | [**SetHeadInvulnerable**](#function-setheadinvulnerable) (bool Invulnerable) <br> |
|  void | [**SetHealth**](#function-sethealth) (int Value) <br> |
|  void | [**SetHitValues**](#function-sethitvalues) (bool bCustomAir=false) <br> |
|  void | [**SetHitValuesOverTime**](#function-sethitvaluesovertime) () <br> |
|  void | [**SetHitgrabActive**](#function-sethitgrabactive) (bool Active) <br> |
|  void | [**SetKnockdownState**](#function-setknockdownstate) () <br> |
|  void | [**SetMeterCooldownTimer**](#function-setmetercooldowntimer) (int Timer) <br> |
|  void | [**SetOnScreen**](#function-setonscreen) (bool OnScreen) <br> |
|  void | [**SetProjectileInvulnerable**](#function-setprojectileinvulnerable) (bool Invulnerable) <br> |
|  void | [**SetRecoverableHealth**](#function-setrecoverablehealth) (int Value) <br> |
|  void | [**SetStance**](#function-setstance) (EActionStance InStance) <br> |
|  void | [**SetStateForCPU**](#function-setstateforcpu) (FGameplayTag StateName, FGameplayTag StateMachineName) <br> |
|  void | [**SetStrikeInvulnerable**](#function-setstrikeinvulnerable) (bool Invulnerable) <br> |
|  void | [**SetStrikeInvulnerableForTime**](#function-setstrikeinvulnerablefortime) (int32 Timer) <br> |
|  void | [**SetStunTime**](#function-setstuntime) (int32 NewTime) <br> |
|  void | [**SetTeamCooldown**](#function-setteamcooldown) (int NewTeamIndex, int Cooldown) <br> |
|  void | [**SetThrowActive**](#function-setthrowactive) (bool Active) <br> |
|  void | [**SetThrowExeState**](#function-setthrowexestate) (FGameplayTag ExeState) <br> |
|  void | [**SetThrowInvulnerable**](#function-setthrowinvulnerable) (bool Invulnerable) <br> |
|  void | [**SetThrowInvulnerableForTime**](#function-setthrowinvulnerablefortime) (int32 Timer) <br> |
|  void | [**SetThrowPosition**](#function-setthrowposition) (int32 ThrowPosX, int32 ThrowPosY) <br> |
|  void | [**SetThrowRange**](#function-setthrowrange) (int32 InThrowRange) <br> |
|  void | [**SetThrowResistForTime**](#function-setthrowresistfortime) (int32 Timer) <br> |
|  void | [**StopLevelSequence**](#function-stoplevelsequence) () <br> |
|  [**APlayerObject**](class_a_player_object.md) \* | [**SwitchMainPlayer**](#function-switchmainplayer) (int NewTeamIndex, bool bForce=false, bool bEvenOnScreen=false) <br> |
|  void | [**ThrowEnd**](#function-throwend) () <br> |
|  void | [**ThrowExe**](#function-throwexe) () <br> |
|  void | [**ToggleComponentVisibility**](#function-togglecomponentvisibility) (FName ComponentName, bool Visible) <br> |
| virtual void | [**Update**](#function-update) () override<br> |
|  void | [**UpdateNotBattle**](#function-updatenotbattle) () <br> |
|  void | [**UseMeter**](#function-usemeter) (int Use) <br> |


## Public Functions inherited from ABattleObject

See [ABattleObject](class_a_battle_object.md)

| Type | Name |
| ---: | :--- |
|   | [**ABattleObject**](class_a_battle_object.md#function-abattleobject) () <br> |
|  [**ABattleObject**](class_a_battle_object.md) \* | [**AddBattleObject**](class_a_battle_object.md#function-addbattleobject) (FGameplayTag InStateName, int32 PosXOffset=0, int32 PosYOffset=0, EPosType PosType=POS\_Player) <br> |
|  [**ABattleObject**](class_a_battle_object.md) \* | [**AddCommonBattleObject**](class_a_battle_object.md#function-addcommonbattleobject) (FGameplayTag InStateName, int32 PosXOffset=0, int32 PosYOffset=0, EPosType PosType=POS\_Player) <br> |
|  void | [**AddPosXWithDir**](class_a_battle_object.md#function-addposxwithdir) (int InPosX) <br> |
|  void | [**AddSpeedXRaw**](class_a_battle_object.md#function-addspeedxraw) (int InSpeedX) <br> |
|  void | [**ApplyRootMotion**](class_a_battle_object.md#function-applyrootmotion) () <br> |
|  void | [**AttachToSocketOfObject**](class_a_battle_object.md#function-attachtosocketofobject) (FName InSocketName, FVector Offset, EObjType ObjType) <br> |
|  int32 | [**CalculateAngleBetweenPoints**](class_a_battle_object.md#function-calculateanglebetweenpoints) (EObjType Obj1, EPosType Pos1, EObjType Obj2, EPosType Pos2) <br> |
|  int32 | [**CalculateDistanceBetweenPoints**](class_a_battle_object.md#function-calculatedistancebetweenpoints) (EDistanceType Type, EObjType Obj1, EPosType Pos1, EObjType Obj2, EPosType Pos2) <br> |
|  void | [**CalculatePushbox**](class_a_battle_object.md#function-calculatepushbox) () <br> |
|  int32 | [**CalculateSpeedAngle**](class_a_battle_object.md#function-calculatespeedangle) () const<br> |
|  void | [**CallSubroutine**](class_a_battle_object.md#function-callsubroutine) (FGameplayTag Name) <br> |
|  void | [**CallSubroutineWithArgs**](class_a_battle_object.md#function-callsubroutinewithargs) (FGameplayTag Name, int32 Arg1, int32 Arg2, int32 Arg3, int32 Arg4) <br> |
|  void | [**CameraShake**](class_a_battle_object.md#function-camerashake) (FGameplayTag PatternName, int32 Scale) <br> |
|  bool | [**CheckBoxOverlap**](class_a_battle_object.md#function-checkboxoverlap) ([**ABattleObject**](class_a_battle_object.md) \* OtherObj, const EBoxType SelfType, const FGameplayTag SelfCustomType, const EBoxType OtherType, const FGameplayTag OtherCustomType) <br> |
|  bool | [**CheckIsGrounded**](class_a_battle_object.md#function-checkisgrounded) () const<br> |
|  void | [**CollisionView**](class_a_battle_object.md#function-collisionview) () <br> |
|  void | [**CreateCharaParticle**](class_a_battle_object.md#function-createcharaparticle) (FGameplayTag Name, EPosType PosType, FVector Offset=FVector::ZeroVector, FRotator Rotation=FRotator::ZeroRotator) <br> |
|  void | [**CreateCommonParticle**](class_a_battle_object.md#function-createcommonparticle) (FGameplayTag Name, EPosType PosType, FVector Offset=FVector::ZeroVector, FRotator Rotation=FRotator::ZeroRotator) <br> |
|  void | [**DeactivateObject**](class_a_battle_object.md#function-deactivateobject) () <br> |
|  void | [**DetachFromSocket**](class_a_battle_object.md#function-detachfromsocket) () <br> |
|  void | [**DisableInertia**](class_a_battle_object.md#function-disableinertia) () <br> |
|  void | [**EnableDeactivateIfBeyondBounds**](class_a_battle_object.md#function-enabledeactivateifbeyondbounds) (bool Enable) <br> |
|  void | [**EnableDeactivateOnReceiveHit**](class_a_battle_object.md#function-enabledeactivateonreceivehit) (bool Enable) <br> |
|  void | [**EnableDeactivateOnStateChange**](class_a_battle_object.md#function-enabledeactivateonstatechange) (bool Enable) <br> |
|  void | [**EnableFlip**](class_a_battle_object.md#function-enableflip) (bool Enabled) <br> |
|  void | [**EnableHit**](class_a_battle_object.md#function-enablehit) (bool Enabled) <br> |
|  void | [**EnableInertia**](class_a_battle_object.md#function-enableinertia) () <br> |
|  void | [**FaceOpponent**](class_a_battle_object.md#function-faceopponent) () <br> |
|  void | [**FlipObject**](class_a_battle_object.md#function-flipobject) () <br> |
|  int32 | [**GenerateRandomNumber**](class_a_battle_object.md#function-generaterandomnumber) (int32 Min, int32 Max) const<br> |
|  UAnimSequenceBase \* | [**GetAnimSequenceForPart**](class_a_battle_object.md#function-getanimsequenceforpart) (const FName Part) const<br> |
|  [**ABattleObject**](class_a_battle_object.md) \* | [**GetBattleObject**](class_a_battle_object.md#function-getbattleobject) (EObjType Type) <br> |
|  void | [**GetBoxPosition**](class_a_battle_object.md#function-getboxposition) (const EBoxType BoxType, const FGameplayTag CustomType, int & OutPosX, int & OutPosY) const<br> |
|  void | [**GetBoxes**](class_a_battle_object.md#function-getboxes) () <br> |
|  FGameplayTag | [**GetCelName**](class_a_battle_object.md#function-getcelname) () const<br> |
|  UPaperFlipbook \* | [**GetFlipbookForPart**](class_a_battle_object.md#function-getflipbookforpart) (const FName Part) const<br> |
|  int32 | [**GetGauge**](class_a_battle_object.md#function-getgauge) (int32 GaugeIndex) const<br> |
|  FGameplayTag | [**GetLabelName**](class_a_battle_object.md#function-getlabelname) () const<br> |
|  int32 | [**GetPosYCenter**](class_a_battle_object.md#function-getposycenter) () const<br> |
|  void | [**GotoLabel**](class_a_battle_object.md#function-gotolabel) (FGameplayTag InName) <br> |
|  void | [**HaltMomentum**](class_a_battle_object.md#function-haltmomentum) () <br> |
|  void | [**HandleClashCollision**](class_a_battle_object.md#function-handleclashcollision) ([**ABattleObject**](class_a_battle_object.md) \* OtherObj) <br> |
|  void | [**HandleCustomCollision\_PostHit**](class_a_battle_object.md#function-handlecustomcollision_posthit) ([**ABattleObject**](class_a_battle_object.md) \* OtherObj) <br> |
|  void | [**HandleCustomCollision\_PreHit**](class_a_battle_object.md#function-handlecustomcollision_prehit) ([**ABattleObject**](class_a_battle_object.md) \* OtherObj) <br> |
|  void | [**HandleFlip**](class_a_battle_object.md#function-handleflip) () <br> |
|  void | [**HandleHitCollision**](class_a_battle_object.md#function-handlehitcollision) ([**ABattleObject**](class_a_battle_object.md) \* AttackedObj) <br> |
|  void | [**HandlePushCollision**](class_a_battle_object.md#function-handlepushcollision) ([**ABattleObject**](class_a_battle_object.md) \* OtherObj) <br> |
|  void | [**IgnoreSuperFreeze**](class_a_battle_object.md#function-ignoresuperfreeze) (bool Ignore) <br> |
|  void | [**InitEventHandler**](class_a_battle_object.md#function-initeventhandler) (EEventType EventType, FName FuncName, int32 Value, FGameplayTag SubroutineName) <br> |
|  [**FHitData**](struct_f_hit_data.md) | [**InitHitDataByAttackLevel**](class_a_battle_object.md#function-inithitdatabyattacklevel) (bool IsCounter) <br> |
|  void | [**InitObject**](class_a_battle_object.md#function-initobject) () <br> |
|  bool | [**IsStopped**](class_a_battle_object.md#function-isstopped) () const<br> |
|  bool | [**IsTimerPaused**](class_a_battle_object.md#function-istimerpaused) () const<br> |
|  [**ALinkActor**](class_a_link_actor.md) \* | [**LinkActor**](class_a_battle_object.md#function-linkactor) (FGameplayTag Name) <br> |
|  void | [**LinkCharaParticle**](class_a_battle_object.md#function-linkcharaparticle) (FGameplayTag Name) <br> |
|  void | [**LinkCommonParticle**](class_a_battle_object.md#function-linkcommonparticle) (FGameplayTag Name) <br> |
|  void | [**LoadForRollback**](class_a_battle_object.md#function-loadforrollback) (const unsigned char \* Buffer) <br> |
|  void | [**PlayCharaSound**](class_a_battle_object.md#function-playcharasound) (FGameplayTag Name) <br> |
|  void | [**PlayCommonSound**](class_a_battle_object.md#function-playcommonsound) (FGameplayTag Name) <br> |
|  void | [**PosTypeToPosition**](class_a_battle_object.md#function-postypetoposition) (EPosType Type, int32 & OutPosX, int32 & OutPosY) const<br> |
|  void | [**PositionLinkUpdate**](class_a_battle_object.md#function-positionlinkupdate) () <br> |
|  void | [**RemoveEventHandler**](class_a_battle_object.md#function-removeeventhandler) (EEventType EventType) <br> |
|  void | [**RemoveLinkActor**](class_a_battle_object.md#function-removelinkactor) () <br> |
|  void | [**ResetObject**](class_a_battle_object.md#function-resetobject) () <br> |
|  void | [**SaveForRollback**](class_a_battle_object.md#function-saveforrollback) (unsigned char \* Buffer) const<br> |
|  void | [**ScreenPosToWorldPos**](class_a_battle_object.md#function-screenpostoworldpos) (const int32 X, const int32 Y, int32 & OutX, int32 & OutY) const<br> |
|  void | [**SetAttacking**](class_a_battle_object.md#function-setattacking) (bool Attacking) <br> |
|  void | [**SetBlendCelName**](class_a_battle_object.md#function-setblendcelname) (FGameplayTag InName) <br> |
|  void | [**SetCelDuration**](class_a_battle_object.md#function-setcelduration) (int32 InTime) <br> |
|  void | [**SetCelName**](class_a_battle_object.md#function-setcelname) (FGameplayTag InName) <br> |
|  void | [**SetFacing**](class_a_battle_object.md#function-setfacing) (EObjDir NewDir) <br> |
|  void | [**SetFloorCollisionActive**](class_a_battle_object.md#function-setfloorcollisionactive) (bool Active) <br> |
|  void | [**SetGauge**](class_a_battle_object.md#function-setgauge) (int32 GaugeIndex, int32 Value) <br> |
|  void | [**SetHitOTG**](class_a_battle_object.md#function-sethitotg) (bool Enable) <br> |
|  void | [**SetIgnoreHitstunScaling**](class_a_battle_object.md#function-setignorehitstunscaling) (bool Ignore) <br> |
|  void | [**SetIgnoreOTG**](class_a_battle_object.md#function-setignoreotg) (bool Ignore) <br> |
|  void | [**SetIgnorePushbackScaling**](class_a_battle_object.md#function-setignorepushbackscaling) (bool Ignore) <br> |
|  void | [**SetObjectID**](class_a_battle_object.md#function-setobjectid) (int InObjectID) <br> |
|  void | [**SetPitch**](class_a_battle_object.md#function-setpitch) (int32 Pitch\_x1000) <br> |
|  void | [**SetPlayerHit**](class_a_battle_object.md#function-setplayerhit) (bool Enable) <br> |
|  void | [**SetProjectileAttribute**](class_a_battle_object.md#function-setprojectileattribute) (bool Attribute) <br> |
|  void | [**SetProrateOnce**](class_a_battle_object.md#function-setprorateonce) (bool Once) <br> |
|  void | [**SetPushCollisionActive**](class_a_battle_object.md#function-setpushcollisionactive) (bool Active) <br> |
|  void | [**SetPushWidthExtend**](class_a_battle_object.md#function-setpushwidthextend) (int32 Extend) <br> |
|  void | [**SetRoll**](class_a_battle_object.md#function-setroll) (int32 Roll\_x1000) <br> |
|  void | [**SetSpeedXRaw**](class_a_battle_object.md#function-setspeedxraw) (int InSpeedX) <br> |
|  void | [**SetTimeUntilNextCel**](class_a_battle_object.md#function-settimeuntilnextcel) (int32 InTime) <br> |
|  void | [**SetWallCollisionActive**](class_a_battle_object.md#function-setwallcollisionactive) (bool Active) <br> |
|  void | [**SetYaw**](class_a_battle_object.md#function-setyaw) (int32 Yaw\_x1000) <br> |
|  void | [**StartSuperFreeze**](class_a_battle_object.md#function-startsuperfreeze) (int Duration, int SelfDuration=0) <br> |
| virtual void | [**Tick**](class_a_battle_object.md#function-tick) (float DeltaTime) override<br> |
|  void | [**TriggerEvent**](class_a_battle_object.md#function-triggerevent) (EEventType EventType, FGameplayTag StateMachineName) <br> |
| virtual void | [**Update**](class_a_battle_object.md#function-update) () <br> |
| virtual void | [**UpdateVisuals**](class_a_battle_object.md#function-updatevisuals) () <br> |
| virtual void | [**UpdateVisualsNoRollback**](class_a_battle_object.md#function-updatevisualsnorollback) () <br> |
|  void | [**UpdateVisuals\_BP**](class_a_battle_object.md#function-updatevisuals_bp) () <br> |
|  void | [**UseGauge**](class_a_battle_object.md#function-usegauge) (int32 GaugeIndex, int32 Value) <br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  uint32 | [**FlipInput**](#function-flipinput) (uint32 Input) <br> |


## Public Static Functions inherited from ABattleObject

See [ABattleObject](class_a_battle_object.md)

| Type | Name |
| ---: | :--- |
|  int32 | [**NormalizeAngle**](class_a_battle_object.md#function-normalizeangle) (int32 Angle\_x1000) <br> |










## Protected Attributes

| Type | Name |
| ---: | :--- |
|  uint32 | [**AirDashNoAttackTime**](#variable-airdashnoattacktime)   = `0`<br> |
|  uint32 | [**AirDashTimerMax**](#variable-airdashtimermax)   = `0`<br> |
|  int32 | [**AutoComboCancels**](#variable-autocombocancels)   = `{}`<br> |
|  FGameplayTag | [**BufferedStateName**](#variable-bufferedstatename)  <br> |
|  uint32 | [**CancelFlags**](#variable-cancelflags)   = `0`<br> |
|  uint32 | [**CurrentAirDashCount**](#variable-currentairdashcount)   = `0`<br> |
|  uint32 | [**CurrentAirJumpCount**](#variable-currentairjumpcount)   = `0`<br> |
|  FGameplayTag | [**ExeStateName**](#variable-exestatename)  <br> |
|  uint32 | [**InstantBlockLockoutTimer**](#variable-instantblocklockouttimer)   = `0`<br> |
|  FGameplayTag | [**LastStateName**](#variable-laststatename)  <br> |
|  uint32 | [**MeterCooldownTimer**](#variable-metercooldowntimer)   = `0`<br> |
|  int32 | [**ThrowRange**](#variable-throwrange)   = `0`<br> |
|  int32 | [**ThrowTechTimer**](#variable-throwtechtimer)   = `0`<br> |
|  bool | [**bIsAutoCombo**](#variable-bisautocombo)   = `false`<br> |


## Protected Attributes inherited from ABattleObject

See [ABattleObject](class_a_battle_object.md)

| Type | Name |
| ---: | :--- |
|  int32 | [**PushHeight**](class_a_battle_object.md#variable-pushheight)   = `0`<br> |
|  int32 | [**PushHeightLow**](class_a_battle_object.md#variable-pushheightlow)   = `0`<br> |
|  int32 | [**PushWidth**](class_a_battle_object.md#variable-pushwidth)   = `0`<br> |
|  int32 | [**PushWidthExtend**](class_a_battle_object.md#variable-pushwidthextend)   = `0`<br> |
































## Protected Functions inherited from ABattleObject

See [ABattleObject](class_a_battle_object.md)

| Type | Name |
| ---: | :--- |
| virtual void | [**BeginPlay**](class_a_battle_object.md#function-beginplay) () override<br> |
|  void | [**CalculateHoming**](class_a_battle_object.md#function-calculatehoming) () <br> |
|  void | [**FuncCall**](class_a_battle_object.md#function-funccall) (const FName & FuncName) const<br> |
|  [**UNightSkyAnimSequenceUserData**](class_u_night_sky_anim_sequence_user_data.md) \* | [**GetAnimSequenceUserData**](class_a_battle_object.md#function-getanimsequenceuserdata) (const FName PartName) const<br> |
|  TArray&lt; [**UNightSkyAnimSequenceUserData**](class_u_night_sky_anim_sequence_user_data.md) \* &gt; | [**GetAnimSequenceUserDatas**](class_a_battle_object.md#function-getanimsequenceuserdatas) () const<br> |
|  void | [**Move**](class_a_battle_object.md#function-move) () <br> |
|  bool | [**SuperArmorSuccess**](class_a_battle_object.md#function-superarmorsuccess) (const [**ABattleObject**](class_a_battle_object.md) \* Attacker) const<br> |






## Public Attributes Documentation




### variable AirDashCount 

```C++
int32 APlayerObject::AirDashCount;
```




<hr>



### variable AirDashMinimumHeight 

```C++
int32 APlayerObject::AirDashMinimumHeight;
```




<hr>



### variable AirDashTimer 

```C++
uint32 APlayerObject::AirDashTimer;
```




<hr>



### variable AirJumpCount 

```C++
int32 APlayerObject::AirJumpCount;
```




<hr>



### variable AirPushHeight 

```C++
int32 APlayerObject::AirPushHeight;
```




<hr>



### variable AirPushHeightLow 

```C++
int32 APlayerObject::AirPushHeightLow;
```




<hr>



### variable AirPushWidth 

```C++
int32 APlayerObject::AirPushWidth;
```




<hr>



### variable BAirDashNoAttackTime 

```C++
int32 APlayerObject::BAirDashNoAttackTime;
```




<hr>



### variable BAirDashSpeed 

```C++
int32 APlayerObject::BAirDashSpeed;
```




<hr>



### variable BAirDashTime 

```C++
int32 APlayerObject::BAirDashTime;
```




<hr>



### variable BDashGravity 

```C++
int32 APlayerObject::BDashGravity;
```




<hr>



### variable BDashHeight 

```C++
int32 APlayerObject::BDashHeight;
```




<hr>



### variable BDashSpeed 

```C++
int32 APlayerObject::BDashSpeed;
```




<hr>



### variable BJumpSpeed 

```C++
int32 APlayerObject::BJumpSpeed;
```




<hr>



### variable BSuperJumpSpeed 

```C++
int32 APlayerObject::BSuperJumpSpeed;
```




<hr>



### variable BWalkSpeed 

```C++
int32 APlayerObject::BWalkSpeed;
```




<hr>



### variable CameraShakeData 

```C++
UCameraShakeData* APlayerObject::CameraShakeData;
```




<hr>



### variable CanProximityThrow 

```C++
bool APlayerObject::CanProximityThrow;
```




<hr>



### variable CanReverseBeat 

```C++
bool APlayerObject::CanReverseBeat;
```




<hr>



### variable ChainCancelOptions 

```C++
TArray<int32> APlayerObject::ChainCancelOptions;
```




<hr>



### variable CharaParticleData 

```C++
UParticleData* APlayerObject::CharaParticleData;
```




<hr>



### variable CharaStateData 

```C++
UStateData* APlayerObject::CharaStateData;
```




<hr>



### variable CharaSubroutineData 

```C++
USubroutineData* APlayerObject::CharaSubroutineData;
```




<hr>



### variable CloseNormalRange 

```C++
int32 APlayerObject::CloseNormalRange;
```




<hr>



### variable CmnPlayerReg1 

```C++
int32 APlayerObject::CmnPlayerReg1;
```




<hr>



### variable CmnPlayerReg2 

```C++
int32 APlayerObject::CmnPlayerReg2;
```




<hr>



### variable CmnPlayerReg3 

```C++
int32 APlayerObject::CmnPlayerReg3;
```




<hr>



### variable CmnPlayerReg4 

```C++
int32 APlayerObject::CmnPlayerReg4;
```




<hr>



### variable CmnPlayerReg5 

```C++
int32 APlayerObject::CmnPlayerReg5;
```




<hr>



### variable CmnPlayerReg6 

```C++
int32 APlayerObject::CmnPlayerReg6;
```




<hr>



### variable CmnPlayerReg7 

```C++
int32 APlayerObject::CmnPlayerReg7;
```




<hr>



### variable CmnPlayerReg8 

```C++
int32 APlayerObject::CmnPlayerReg8;
```




<hr>



### variable CollisionData 

```C++
UCollisionData* APlayerObject::CollisionData;
```




<hr>



### variable ColorIndex 

```C++
int32 APlayerObject::ColorIndex;
```




<hr>



### variable ComboCounter 

```C++
int32 APlayerObject::ComboCounter;
```




<hr>



### variable ComboRate 

```C++
int32 APlayerObject::ComboRate;
```




<hr>



### variable ComboTimer 

```C++
int32 APlayerObject::ComboTimer;
```




<hr>



### variable CommonCollisionData 

```C++
UCollisionData* APlayerObject::CommonCollisionData;
```




<hr>



### variable CommonLinkActorData 

```C++
ULinkActorData* APlayerObject::CommonLinkActorData;
```




<hr>



### variable CommonObjectStateData 

```C++
UStateData* APlayerObject::CommonObjectStateData;
```




<hr>



### variable CommonObjectStateNames 

```C++
TArray<FGameplayTag> APlayerObject::CommonObjectStateNames;
```




<hr>



### variable CommonObjectStates 

```C++
TArray<UState*> APlayerObject::CommonObjectStates;
```




<hr>



### variable CommonParticleData 

```C++
UParticleData* APlayerObject::CommonParticleData;
```




<hr>



### variable CommonSequenceData 

```C++
USequenceData* APlayerObject::CommonSequenceData;
```




<hr>



### variable CommonSoundData 

```C++
USoundData* APlayerObject::CommonSoundData;
```




<hr>



### variable CommonSubroutineData 

```C++
USubroutineData* APlayerObject::CommonSubroutineData;
```




<hr>



### variable CommonSubroutineNames 

```C++
TArray<FGameplayTag> APlayerObject::CommonSubroutineNames;
```




<hr>



### variable CommonSubroutines 

```C++
TArray<USubroutine*> APlayerObject::CommonSubroutines;
```




<hr>



### variable ComponentVisible 

```C++
bool APlayerObject::ComponentVisible[MaxComponentCount];
```




<hr>



### variable CrouchPushHeight 

```C++
int32 APlayerObject::CrouchPushHeight;
```




<hr>



### variable CrouchPushWidth 

```C++
int32 APlayerObject::CrouchPushWidth;
```




<hr>



### variable CurrentHealth 

```C++
int32 APlayerObject::CurrentHealth;
```




<hr>



### variable DamageReactionCels 

```C++
TMap<FGameplayTag, FGameplayTag> APlayerObject::DamageReactionCels;
```




<hr>



### variable Enemy 

```C++
APlayerObject* APlayerObject::Enemy;
```




<hr>



### variable ExtraGauges 

```C++
TArray<FExtraGauge> APlayerObject::ExtraGauges;
```




<hr>



### variable FAirDashNoAttackTime 

```C++
int32 APlayerObject::FAirDashNoAttackTime;
```




<hr>



### variable FAirDashSpeed 

```C++
int32 APlayerObject::FAirDashSpeed;
```




<hr>



### variable FAirDashTime 

```C++
int32 APlayerObject::FAirDashTime;
```




<hr>



### variable FDashAccel 

```C++
int32 APlayerObject::FDashAccel;
```




<hr>



### variable FDashFriction 

```C++
int32 APlayerObject::FDashFriction;
```




<hr>



### variable FDashInitSpeed 

```C++
int32 APlayerObject::FDashInitSpeed;
```




<hr>



### variable FDashMaxSpeed 

```C++
int32 APlayerObject::FDashMaxSpeed;
```




<hr>



### variable FJumpSpeed 

```C++
int32 APlayerObject::FJumpSpeed;
```




<hr>



### variable FSuperJumpSpeed 

```C++
int32 APlayerObject::FSuperJumpSpeed;
```




<hr>



### variable FWalkSpeed 

```C++
int32 APlayerObject::FWalkSpeed;
```




<hr>



### variable FlipInputs 

```C++
bool APlayerObject::FlipInputs;
```




<hr>



### variable ForwardAirDashMeterGain 

```C++
int32 APlayerObject::ForwardAirDashMeterGain;
```




<hr>



### variable ForwardDashMeterGain 

```C++
int32 APlayerObject::ForwardDashMeterGain;
```




<hr>



### variable ForwardJumpMeterGain 

```C++
int32 APlayerObject::ForwardJumpMeterGain;
```




<hr>



### variable ForwardWalkMeterGain 

```C++
int32 APlayerObject::ForwardWalkMeterGain;
```




<hr>



### variable Inputs 

```C++
uint32 APlayerObject::Inputs;
```




<hr>



### variable IntroEndFlag 

```C++
bool APlayerObject::IntroEndFlag;
```




<hr>



### variable IntroName 

```C++
FGameplayTag APlayerObject::IntroName;
```




<hr>



### variable InvulnFlags 

```C++
uint32 APlayerObject::InvulnFlags;
```




<hr>



### variable JumpGravity 

```C++
int32 APlayerObject::JumpGravity;
```




<hr>



### variable JumpHeight 

```C++
int32 APlayerObject::JumpHeight;
```




<hr>



### variable LinkActorData 

```C++
ULinkActorData* APlayerObject::LinkActorData;
```




<hr>



### variable MaterialData 

```C++
UMaterialData* APlayerObject::MaterialData;
```




<hr>



### variable MaxColorIndex 

```C++
int32 APlayerObject::MaxColorIndex;
```




<hr>



### variable MaxHealth 

```C++
int32 APlayerObject::MaxHealth;
```




<hr>



### variable MaxMeter 

```C++
int32 APlayerObject::MaxMeter;
```




<hr>



### variable MaxOTGCount 

```C++
int32 APlayerObject::MaxOTGCount;
```




<hr>



### variable MeterPercentOnHit 

```C++
int32 APlayerObject::MeterPercentOnHit;
```




<hr>



### variable MeterPercentOnHitGuard 

```C++
int32 APlayerObject::MeterPercentOnHitGuard;
```




<hr>



### variable MeterPercentOnReceiveHit 

```C++
int32 APlayerObject::MeterPercentOnReceiveHit;
```




<hr>



### variable MeterPercentOnReceiveHitGuard 

```C++
int32 APlayerObject::MeterPercentOnReceiveHitGuard;
```




<hr>



### variable MovesUsedInChain 

```C++
TArray<int32> APlayerObject::MovesUsedInChain;
```




<hr>



### variable MovesUsedInCombo 

```C++
TArray<int32> APlayerObject::MovesUsedInCombo;
```




<hr>



### variable OTGCount 

```C++
int32 APlayerObject::OTGCount;
```




<hr>



### variable ObjectStateData 

```C++
UStateData* APlayerObject::ObjectStateData;
```




<hr>



### variable ObjectStateNames 

```C++
TArray<FGameplayTag> APlayerObject::ObjectStateNames;
```




<hr>



### variable ObjectStates 

```C++
TArray<UState*> APlayerObject::ObjectStates;
```




<hr>



### variable OtgProration 

```C++
int32 APlayerObject::OtgProration;
```




<hr>



### variable PlayerFlags 

```C++
uint32 APlayerObject::PlayerFlags;
```




<hr>



### variable PlayerIndex 

```C++
int32 APlayerObject::PlayerIndex;
```




<hr>



### variable PlayerReg1 

```C++
int32 APlayerObject::PlayerReg1;
```




<hr>



### variable PlayerReg2 

```C++
int32 APlayerObject::PlayerReg2;
```




<hr>



### variable PlayerReg3 

```C++
int32 APlayerObject::PlayerReg3;
```




<hr>



### variable PlayerReg4 

```C++
int32 APlayerObject::PlayerReg4;
```




<hr>



### variable PlayerReg5 

```C++
int32 APlayerObject::PlayerReg5;
```




<hr>



### variable PlayerReg6 

```C++
int32 APlayerObject::PlayerReg6;
```




<hr>



### variable PlayerReg7 

```C++
int32 APlayerObject::PlayerReg7;
```




<hr>



### variable PlayerReg8 

```C++
int32 APlayerObject::PlayerReg8;
```




<hr>



### variable PlayerSync 

```C++
unsigned char APlayerObject::PlayerSync;
```




<hr>



### variable PlayerSyncEnd 

```C++
unsigned char APlayerObject::PlayerSyncEnd;
```




<hr>



### variable PrimaryStateMachine 

```C++
FStateMachine APlayerObject::PrimaryStateMachine;
```




<hr>



### variable ProximityThrowInput 

```C++
FInputCondition APlayerObject::ProximityThrowInput;
```




<hr>



### variable RecoverableHealth 

```C++
int32 APlayerObject::RecoverableHealth;
```




<hr>



### variable RoundEndFlag 

```C++
bool APlayerObject::RoundEndFlag;
```




<hr>



### variable RoundWinTimer 

```C++
int32 APlayerObject::RoundWinTimer;
```




<hr>



### variable SequenceData 

```C++
USequenceData* APlayerObject::SequenceData;
```




<hr>



### variable SoundData 

```C++
USoundData* APlayerObject::SoundData;
```




<hr>



### variable Stance 

```C++
TEnumAsByte<EActionStance> APlayerObject::Stance;
```




<hr>



### variable StandPushHeight 

```C++
int32 APlayerObject::StandPushHeight;
```




<hr>



### variable StandPushWidth 

```C++
int32 APlayerObject::StandPushWidth;
```




<hr>



### variable StateEntryName 

```C++
FGameplayTag APlayerObject::StateEntryName;
```




<hr>



### variable StoredBattleObjects 

```C++
ABattleObject* APlayerObject::StoredBattleObjects[16];
```




<hr>



### variable StoredInputBuffer 

```C++
FInputBuffer APlayerObject::StoredInputBuffer;
```




<hr>



### variable StoredLinkActors 

```C++
TArray<FLinkedActorContainer> APlayerObject::StoredLinkActors;
```




<hr>



### variable StrikeInvulnerableTimer 

```C++
uint32 APlayerObject::StrikeInvulnerableTimer;
```




<hr>



### variable SubStateData 

```C++
TMap<FGameplayTag, UStateData*> APlayerObject::SubStateData;
```




<hr>



### variable SubStateMachines 

```C++
TArray<FStateMachine> APlayerObject::SubStateMachines;
```




<hr>



### variable SubroutineNames 

```C++
TArray<FGameplayTag> APlayerObject::SubroutineNames;
```




<hr>



### variable Subroutines 

```C++
TArray<USubroutine*> APlayerObject::Subroutines;
```




<hr>



### variable SuperJumpGravity 

```C++
int32 APlayerObject::SuperJumpGravity;
```




<hr>



### variable SuperJumpHeight 

```C++
int32 APlayerObject::SuperJumpHeight;
```




<hr>



### variable TeamIndex 

```C++
int32 APlayerObject::TeamIndex;
```




<hr>



### variable ThrowInvulnerableTimer 

```C++
uint32 APlayerObject::ThrowInvulnerableTimer;
```




<hr>



### variable ThrowResistAfterWakeUp 

```C++
int32 APlayerObject::ThrowResistAfterWakeUp;
```




<hr>



### variable ThrowResistTimer 

```C++
uint32 APlayerObject::ThrowResistTimer;
```




<hr>



### variable ThrowTechWindow 

```C++
int32 APlayerObject::ThrowTechWindow;
```




<hr>



### variable TotalProration 

```C++
int32 APlayerObject::TotalProration;
```




<hr>



### variable VoiceData 

```C++
USoundData* APlayerObject::VoiceData;
```




<hr>



### variable WallTouchTimer 

```C++
int32 APlayerObject::WallTouchTimer;
```




<hr>



### variable WhiffCancelOptions 

```C++
TArray<int32> APlayerObject::WhiffCancelOptions;
```




<hr>



### variable bCrumpled 

```C++
bool APlayerObject::bCrumpled;
```




<hr>



### variable bIsCpu 

```C++
bool APlayerObject::bIsCpu;
```




<hr>



### variable bLimitCrumple 

```C++
bool APlayerObject::bLimitCrumple;
```




<hr>



### variable bMirrorWhenFlip 

```C++
bool APlayerObject::bMirrorWhenFlip;
```




<hr>
## Public Functions Documentation




### function APlayerObject 

```C++
APlayerObject::APlayerObject () 
```




<hr>



### function AddAirDash 

```C++
void APlayerObject::AddAirDash (
    int32 NewAirDash
) 
```




<hr>



### function AddAirJump 

```C++
void APlayerObject::AddAirJump (
    int32 NewAirJump
) 
```




<hr>



### function AddAutoComboCancel 

```C++
void APlayerObject::AddAutoComboCancel (
    FGameplayTag Option,
    EInputFlags Button
) 
```




<hr>



### function AddBattleObjectToStorage 

```C++
void APlayerObject::AddBattleObjectToStorage (
    ABattleObject * InActor,
    int Index
) 
```




<hr>



### function AddChainCancelOption 

```C++
void APlayerObject::AddChainCancelOption (
    FGameplayTag Option
) 
```




<hr>



### function AddHealth 

```C++
void APlayerObject::AddHealth (
    int Value
) 
```




<hr>



### function AddMeter 

```C++
void APlayerObject::AddMeter (
    int Meter
) 
```




<hr>



### function AddObjectState 

```C++
void APlayerObject::AddObjectState (
    FGameplayTag Name,
    UState * State,
    bool IsCommon
) 
```




<hr>



### function AddRecoverableHealth 

```C++
void APlayerObject::AddRecoverableHealth (
    int Value
) 
```




<hr>



### function AddState 

```C++
void APlayerObject::AddState (
    FGameplayTag Name,
    UState * State,
    FGameplayTag StateMachineName
) 
```




<hr>



### function AddSubroutine 

```C++
void APlayerObject::AddSubroutine (
    FGameplayTag Name,
    USubroutine * Subroutine,
    bool IsCommon
) 
```




<hr>



### function AddWhiffCancelOption 

```C++
void APlayerObject::AddWhiffCancelOption (
    FGameplayTag Option
) 
```




<hr>



### function BattleHudVisibility 

```C++
void APlayerObject::BattleHudVisibility (
    bool Visible
) 
```




<hr>



### function CallAssist 

```C++
APlayerObject * APlayerObject::CallAssist (
    int AssistIndex,
    FGameplayTag AssistName
) 
```




<hr>



### function CanEnterState 

```C++
bool APlayerObject::CanEnterState (
    UState * State,
    FGameplayTag StateMachineName
) 
```




<hr>



### function CheckEnemyInRange 

```C++
bool APlayerObject::CheckEnemyInRange (
    int32 XBegin,
    int32 XEnd,
    int32 YBegin,
    int32 YEnd
) const
```




<hr>



### function CheckHasHit 

```C++
bool APlayerObject::CheckHasHit () const
```




<hr>



### function CheckInput 

```C++
bool APlayerObject::CheckInput (
    const FInputCondition & Input
) 
```




<hr>



### function CheckIsAttacking 

```C++
bool APlayerObject::CheckIsAttacking () const
```




<hr>



### function CheckIsStunned 

```C++
bool APlayerObject::CheckIsStunned () const
```




<hr>



### function CheckStateEnabled 

```C++
bool APlayerObject::CheckStateEnabled (
    EStateType StateType,
    FGameplayTag CustomStateType,
    FGameplayTag StateMachineName
) 
```




<hr>



### function DisableAll 

```C++
void APlayerObject::DisableAll (
    FGameplayTag StateMachineName
) 
```




<hr>



### function DisableCustomState 

```C++
void APlayerObject::DisableCustomState (
    FGameplayTag CustomStateType,
    FGameplayTag StateMachineName
) 
```




<hr>



### function DisableState 

```C++
void APlayerObject::DisableState (
    UPARAM(meta=(Bitmask, BitmaskEnum="/Script/NightSkyEngine.EEnableFlags")) int32 Bitmask,
    FGameplayTag StateMachineName
) 
```




<hr>



### function EditorUpdate 

```C++
void APlayerObject::EditorUpdate () 
```




<hr>



### function EmptyStateMachine 

```C++
void APlayerObject::EmptyStateMachine () 
```




<hr>



### function EnableAll 

```C++
void APlayerObject::EnableAll (
    FGameplayTag StateMachineName
) 
```




<hr>



### function EnableAttacks 

```C++
void APlayerObject::EnableAttacks () 
```




<hr>



### function EnableCancelIntoSelf 

```C++
void APlayerObject::EnableCancelIntoSelf (
    bool Enable
) 
```




<hr>



### function EnableChainCancel 

```C++
void APlayerObject::EnableChainCancel (
    bool Enable
) 
```




<hr>



### function EnableCustomState 

```C++
void APlayerObject::EnableCustomState (
    FGameplayTag CustomStateType,
    FGameplayTag StateMachineName
) 
```




<hr>



### function EnableForwardAirdashCancel 

```C++
void APlayerObject::EnableForwardAirdashCancel (
    bool Enable
) 
```




<hr>



### function EnableJumpCancel 

```C++
void APlayerObject::EnableJumpCancel (
    bool Enable
) 
```




<hr>



### function EnableReverseBeat 

```C++
void APlayerObject::EnableReverseBeat (
    bool Enable
) 
```




<hr>



### function EnableSpecialCancel 

```C++
void APlayerObject::EnableSpecialCancel (
    bool Enable
) 
```




<hr>



### function EnableState 

```C++
void APlayerObject::EnableState (
    UPARAM(meta=(Bitmask, BitmaskEnum="/Script/NightSkyEngine.EEnableFlags")) int32 Bitmask,
    FGameplayTag StateMachineName
) 
```




<hr>



### function EnableSuperCancel 

```C++
void APlayerObject::EnableSuperCancel (
    bool Enable
) 
```




<hr>



### function EnableWhiffCancel 

```C++
void APlayerObject::EnableWhiffCancel (
    bool Enable
) 
```




<hr>



### function EndMatch 

```C++
void APlayerObject::EndMatch () const
```




<hr>



### function EndRound 

```C++
void APlayerObject::EndRound () const
```




<hr>



### function ForceEnableFarNormal 

```C++
void APlayerObject::ForceEnableFarNormal (
    bool Enable
) 
```




<hr>



### function GetAttackBlockType 

```C++
EBlockType APlayerObject::GetAttackBlockType () const
```




<hr>



### function GetCurrentStateName 

```C++
FGameplayTag APlayerObject::GetCurrentStateName (
    FGameplayTag StateMachineName
) 
```




<hr>



### function GetEnableFlags 

```C++
int32 APlayerObject::GetEnableFlags (
    FGameplayTag StateMachineName
) 
```




<hr>



### function GetLastStateName 

```C++
FGameplayTag APlayerObject::GetLastStateName () const
```




<hr>



### function GetStateEntryName 

```C++
FGameplayTag APlayerObject::GetStateEntryName () const
```




<hr>



### function GetStateMachine 

```C++
FStateMachine & APlayerObject::GetStateMachine (
    FGameplayTag StateMachineName
) 
```




<hr>



### function HandleAutoCombo 

```C++
bool APlayerObject::HandleAutoCombo (
    int32 StateIndex,
    FStateMachine & StateMachine
) 
```




<hr>



### function HandleBlockAction 

```C++
void APlayerObject::HandleBlockAction () 
```




<hr>



### function HandleBufferedState [1/2]

```C++
void APlayerObject::HandleBufferedState () 
```




<hr>



### function HandleBufferedState [2/2]

```C++
void APlayerObject::HandleBufferedState (
    FStateMachine & StateMachine
) 
```




<hr>



### function HandleEndCombo 

```C++
void APlayerObject::HandleEndCombo () 
```




<hr>



### function HandleFlipInput 

```C++
void APlayerObject::HandleFlipInput () 
```




<hr>



### function HandleHitAction 

```C++
void APlayerObject::HandleHitAction (
    EHitAction HACT
) 
```




<hr>



### function HandleProximityBlock 

```C++
void APlayerObject::HandleProximityBlock () 
```




<hr>



### function HandleStateInputs 

```C++
bool APlayerObject::HandleStateInputs (
    int32 StateIndex,
    bool Buffer,
    FStateMachine & StateMachine
) 
```




<hr>



### function HandleStateMachine 

```C++
void APlayerObject::HandleStateMachine (
    bool Buffer,
    FStateMachine & StateMachine
) 
```




<hr>



### function HandleStateTransition 

```C++
bool APlayerObject::HandleStateTransition (
    int32 StateIndex,
    bool Buffer,
    FStateMachine & StateMachine
) 
```




<hr>



### function InitBP 

```C++
void APlayerObject::InitBP () 
```




<hr>



### function InitPlayer 

```C++
void APlayerObject::InitPlayer () 
```




<hr>



### function IsCorrectBlock 

```C++
bool APlayerObject::IsCorrectBlock (
    EBlockType BlockType
) 
```




<hr>



### function IsEnemyAttackState 

```C++
bool APlayerObject::IsEnemyAttackState () const
```




<hr>



### function IsEnemyBlocking 

```C++
bool APlayerObject::IsEnemyBlocking () const
```




<hr>



### function IsEnemyThrow 

```C++
bool APlayerObject::IsEnemyThrow () const
```




<hr>



### function IsInvulnerable 

```C++
bool APlayerObject::IsInvulnerable (
    const ABattleObject * Attacker
) const
```




<hr>



### function IsInvulnerable\_BP 

```C++
bool APlayerObject::IsInvulnerable_BP () const
```




<hr>



### function IsMainPlayer 

```C++
bool APlayerObject::IsMainPlayer () const
```




<hr>



### function IsOnScreen 

```C++
bool APlayerObject::IsOnScreen () const
```




<hr>



### function IsTouchingWall 

```C++
bool APlayerObject::IsTouchingWall () const
```




<hr>



### function JumpToState 

```C++
bool APlayerObject::JumpToState (
    FGameplayTag NewName,
    FGameplayTag StateMachineName,
    bool IsLabel=false
) 
```




<hr>



### function JumpToStateByClass 

```C++
bool APlayerObject::JumpToStateByClass (
    TSubclassOf< UState > Class,
    FGameplayTag StateMachineName,
    bool IsLabel=false
) 
```




<hr>



### function JumpToStateByClassPrimary 

```C++
bool APlayerObject::JumpToStateByClassPrimary (
    TSubclassOf< UState > Class,
    bool IsLabel=false
) 
```




<hr>



### function JumpToStatePrimary 

```C++
bool APlayerObject::JumpToStatePrimary (
    FGameplayTag NewName,
    bool IsLabel=false
) 
```




<hr>



### function LoadForRollbackBP 

```C++
void APlayerObject::LoadForRollbackBP (
    TArray< uint8 > InBytes
) 
```




<hr>



### function LoadForRollbackPlayer 

```C++
void APlayerObject::LoadForRollbackPlayer (
    const unsigned char * Buffer
) 
```




<hr>



### function OnStateChange 

```C++
void APlayerObject::OnStateChange () 
```




<hr>



### function PauseRoundTimer 

```C++
void APlayerObject::PauseRoundTimer (
    bool Pause
) 
```




<hr>



### function PlayCommonLevelSequence 

```C++
void APlayerObject::PlayCommonLevelSequence (
    FGameplayTag Name
) 
```




<hr>



### function PlayLevelSequence 

```C++
void APlayerObject::PlayLevelSequence (
    FGameplayTag Name
) 
```




<hr>



### function PlayVoiceLine 

```C++
void APlayerObject::PlayVoiceLine (
    FGameplayTag Name
) 
```




<hr>



### function PostStateChange 

```C++
void APlayerObject::PostStateChange () 
```




<hr>



### function RecoverHealth 

```C++
void APlayerObject::RecoverHealth (
    int Value
) 
```




<hr>



### function RemoveAutoComboCancel 

```C++
void APlayerObject::RemoveAutoComboCancel (
    EInputFlags Button
) 
```




<hr>



### function RemoveChainCancelOption 

```C++
void APlayerObject::RemoveChainCancelOption (
    FGameplayTag Option
) 
```




<hr>



### function RemoveWhiffCancelOption 

```C++
void APlayerObject::RemoveWhiffCancelOption (
    FGameplayTag Option
) 
```




<hr>



### function ResetAirDash 

```C++
void APlayerObject::ResetAirDash () 
```




<hr>



### function ResetAirJump 

```C++
void APlayerObject::ResetAirJump () 
```




<hr>



### function RoundInit 

```C++
void APlayerObject::RoundInit (
    bool ResetHealth
) 
```




<hr>



### function RoundInit\_BP 

```C++
void APlayerObject::RoundInit_BP () 
```




<hr>



### function SaveForRollbackBP 

```C++
TArray< uint8 > APlayerObject::SaveForRollbackBP () 
```




<hr>



### function SaveForRollbackPlayer 

```C++
void APlayerObject::SaveForRollbackPlayer (
    unsigned char * Buffer
) const
```




<hr>



### function SetAirDashNoAttackTimer 

```C++
void APlayerObject::SetAirDashNoAttackTimer (
    bool IsForward
) 
```




<hr>



### function SetAirDashTimer 

```C++
void APlayerObject::SetAirDashTimer (
    bool IsForward
) 
```




<hr>



### function SetDamageReactionCel 

```C++
void APlayerObject::SetDamageReactionCel (
    FGameplayTag Type
) 
```




<hr>



### function SetDefaultComponentVisibility 

```C++
void APlayerObject::SetDefaultComponentVisibility () 
```




<hr>



### function SetDefaultLandingAction 

```C++
void APlayerObject::SetDefaultLandingAction (
    bool Enable
) 
```




<hr>



### function SetGuardValues 

```C++
void APlayerObject::SetGuardValues () 
```




<hr>



### function SetHeadAttribute 

```C++
void APlayerObject::SetHeadAttribute (
    bool Attribute
) 
```




<hr>



### function SetHeadInvulnerable 

```C++
void APlayerObject::SetHeadInvulnerable (
    bool Invulnerable
) 
```




<hr>



### function SetHealth 

```C++
void APlayerObject::SetHealth (
    int Value
) 
```




<hr>



### function SetHitValues 

```C++
void APlayerObject::SetHitValues (
    bool bCustomAir=false
) 
```




<hr>



### function SetHitValuesOverTime 

```C++
void APlayerObject::SetHitValuesOverTime () 
```




<hr>



### function SetHitgrabActive 

```C++
void APlayerObject::SetHitgrabActive (
    bool Active
) 
```




<hr>



### function SetKnockdownState 

```C++
void APlayerObject::SetKnockdownState () 
```




<hr>



### function SetMeterCooldownTimer 

```C++
void APlayerObject::SetMeterCooldownTimer (
    int Timer
) 
```




<hr>



### function SetOnScreen 

```C++
void APlayerObject::SetOnScreen (
    bool OnScreen
) 
```




<hr>



### function SetProjectileInvulnerable 

```C++
void APlayerObject::SetProjectileInvulnerable (
    bool Invulnerable
) 
```




<hr>



### function SetRecoverableHealth 

```C++
void APlayerObject::SetRecoverableHealth (
    int Value
) 
```




<hr>



### function SetStance 

```C++
void APlayerObject::SetStance (
    EActionStance InStance
) 
```




<hr>



### function SetStateForCPU 

```C++
void APlayerObject::SetStateForCPU (
    FGameplayTag StateName,
    FGameplayTag StateMachineName
) 
```




<hr>



### function SetStrikeInvulnerable 

```C++
void APlayerObject::SetStrikeInvulnerable (
    bool Invulnerable
) 
```




<hr>



### function SetStrikeInvulnerableForTime 

```C++
void APlayerObject::SetStrikeInvulnerableForTime (
    int32 Timer
) 
```




<hr>



### function SetStunTime 

```C++
void APlayerObject::SetStunTime (
    int32 NewTime
) 
```




<hr>



### function SetTeamCooldown 

```C++
void APlayerObject::SetTeamCooldown (
    int NewTeamIndex,
    int Cooldown
) 
```




<hr>



### function SetThrowActive 

```C++
void APlayerObject::SetThrowActive (
    bool Active
) 
```




<hr>



### function SetThrowExeState 

```C++
void APlayerObject::SetThrowExeState (
    FGameplayTag ExeState
) 
```




<hr>



### function SetThrowInvulnerable 

```C++
void APlayerObject::SetThrowInvulnerable (
    bool Invulnerable
) 
```




<hr>



### function SetThrowInvulnerableForTime 

```C++
void APlayerObject::SetThrowInvulnerableForTime (
    int32 Timer
) 
```




<hr>



### function SetThrowPosition 

```C++
void APlayerObject::SetThrowPosition (
    int32 ThrowPosX,
    int32 ThrowPosY
) 
```




<hr>



### function SetThrowRange 

```C++
void APlayerObject::SetThrowRange (
    int32 InThrowRange
) 
```




<hr>



### function SetThrowResistForTime 

```C++
void APlayerObject::SetThrowResistForTime (
    int32 Timer
) 
```




<hr>



### function StopLevelSequence 

```C++
void APlayerObject::StopLevelSequence () 
```




<hr>



### function SwitchMainPlayer 

```C++
APlayerObject * APlayerObject::SwitchMainPlayer (
    int NewTeamIndex,
    bool bForce=false,
    bool bEvenOnScreen=false
) 
```




<hr>



### function ThrowEnd 

```C++
void APlayerObject::ThrowEnd () 
```




<hr>



### function ThrowExe 

```C++
void APlayerObject::ThrowExe () 
```




<hr>



### function ToggleComponentVisibility 

```C++
void APlayerObject::ToggleComponentVisibility (
    FName ComponentName,
    bool Visible
) 
```




<hr>



### function Update 

```C++
virtual void APlayerObject::Update () override
```



Implements [*ABattleObject::Update*](class_a_battle_object.md#function-update)


<hr>



### function UpdateNotBattle 

```C++
void APlayerObject::UpdateNotBattle () 
```




<hr>



### function UseMeter 

```C++
void APlayerObject::UseMeter (
    int Use
) 
```




<hr>
## Public Static Functions Documentation




### function FlipInput 

```C++
static uint32 APlayerObject::FlipInput (
    uint32 Input
) 
```




<hr>
## Protected Attributes Documentation




### variable AirDashNoAttackTime 

```C++
uint32 APlayerObject::AirDashNoAttackTime;
```




<hr>



### variable AirDashTimerMax 

```C++
uint32 APlayerObject::AirDashTimerMax;
```




<hr>



### variable AutoComboCancels 

```C++
int32 APlayerObject::AutoComboCancels[8];
```




<hr>



### variable BufferedStateName 

```C++
FGameplayTag APlayerObject::BufferedStateName;
```




<hr>



### variable CancelFlags 

```C++
uint32 APlayerObject::CancelFlags;
```




<hr>



### variable CurrentAirDashCount 

```C++
uint32 APlayerObject::CurrentAirDashCount;
```




<hr>



### variable CurrentAirJumpCount 

```C++
uint32 APlayerObject::CurrentAirJumpCount;
```




<hr>



### variable ExeStateName 

```C++
FGameplayTag APlayerObject::ExeStateName;
```




<hr>



### variable InstantBlockLockoutTimer 

```C++
uint32 APlayerObject::InstantBlockLockoutTimer;
```




<hr>



### variable LastStateName 

```C++
FGameplayTag APlayerObject::LastStateName;
```




<hr>



### variable MeterCooldownTimer 

```C++
uint32 APlayerObject::MeterCooldownTimer;
```




<hr>



### variable ThrowRange 

```C++
int32 APlayerObject::ThrowRange;
```




<hr>



### variable ThrowTechTimer 

```C++
int32 APlayerObject::ThrowTechTimer;
```




<hr>



### variable bIsAutoCombo 

```C++
bool APlayerObject::bIsAutoCombo;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/NightSkyEngine/Battle/Objects/PlayerObject.h`

