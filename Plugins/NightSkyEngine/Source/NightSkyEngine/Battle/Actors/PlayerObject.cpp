﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerObject.h"

#include "NightSkyGameState.h"
#include "NightSkyEngine/Battle/Subroutine.h"
#include "NightSkyEngine/Data/LinkActorData.h"
#include "NightSkyEngine/Data/ParticleData.h"
#include "NightSkyEngine/Data/SubroutineData.h"
#include "NightSkyEngine/Miscellaneous/NightSkyGameInstance.h"
#include "Serialization/ObjectReader.h"
#include "Serialization/ObjectWriter.h"

UE_DEFINE_GAMEPLAY_TAG_COMMENT(State_Label_Blowback_1, "State.Label.Blowback.1", "Blowback Label 1");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(State_Label_Blowback_2, "State.Label.Blowback.2", "Blowback Label 2");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(State_Label_Blowback_3, "State.Label.Blowback.3", "Blowback Label 3");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(State_Label_Blowback_4, "State.Label.Blowback.4", "Blowback Label 4");

UE_DEFINE_GAMEPLAY_TAG_COMMENT(State_Label_Block_PreGuard, "State.Label.Block.PreGuard", "Block Label Pre Guard");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(State_Label_Block_Level1, "State.Label.Block.Level1", "Block Label Level 1");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(State_Label_Block_Level2, "State.Label.Block.Level2", "Block Label Level 2");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(State_Label_Block_Level3, "State.Label.Block.Level3", "Block Label Level 3");

UE_DEFINE_GAMEPLAY_TAG_COMMENT(Subroutine_IsCorrectBlock, "Subroutine.IsCorrectBlock", "Is Correct Block");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(Subroutine_HitCollision, "Subroutine.HitCollision", "Hit Collision");

APlayerObject::APlayerObject()
{
	PrimaryStateMachine.Parent = this;
	MiscFlags = MISC_PushCollisionActive | MISC_WallCollisionActive | MISC_FloorCollisionActive;
	CancelFlags = CNC_EnableKaraCancel | CNC_ChainCancelEnabled;
	PlayerFlags = PLF_DefaultLandingAction;
	FWalkSpeed = 7800;
	BWalkSpeed = 4800;
	FDashInitSpeed = 13000;
	FDashAccel = 600;
	FDashFriction = 95;
	FDashMaxSpeed = 38500;
	BDashSpeed = 14000;
	BDashHeight = 5200;
	BDashGravity = 700;
	JumpHeight = 35000;
	FJumpSpeed = 7900;
	BJumpSpeed = 5200;
	JumpGravity = 1900;
	SuperJumpHeight = 43700;
	FSuperJumpSpeed = 7900;
	BSuperJumpSpeed = 5200;
	SuperJumpGravity = 1900;
	AirDashMinimumHeight = 105000;
	FAirDashSpeed = 30000;
	BAirDashSpeed = 24500;
	FAirDashTime = 20;
	BAirDashTime = 12;
	FAirDashNoAttackTime = 5;
	BAirDashNoAttackTime = 5;
	AirJumpCount = 1;
	AirDashCount = 1;
	Stance = ACT_Standing;
	StandPushWidth = 110000;
	StandPushHeight = 240000;
	CrouchPushWidth = 120000;
	CrouchPushHeight = 180000;
	AirPushWidth = 100000;
	AirPushHeight = 275000;
	AirPushHeightLow = -135000;
	IsPlayer = true;
	IsActive = true;
	MaxHealth = 10000;
	ForwardWalkMeterGain = 12;
	ForwardJumpMeterGain = 10;
	ForwardDashMeterGain = 25;
	ForwardAirDashMeterGain = 25;
	AttackFlags = 0;
	for (bool& Visible : ComponentVisible)
		Visible = true;

	PrimaryStateMachine.bPrimary = true;
	PrimaryStateMachine.StateMachineName = StateMachine_Primary;
}

void APlayerObject::BeginPlay()
{
	Super::BeginPlay();

	if (CommonLinkActorData != nullptr)
	{
		for (FLinkActorStruct LinkedActorStruct : CommonLinkActorData->LinkedActorStructs)
		{
			for (int i = 0; i < LinkedActorStruct.MaxInstances; i++)
			{
				auto Actor = GetWorld()->SpawnActor(LinkedActorStruct.ActorClass);
				Actor->SetActorHiddenInGame(true);
				FLinkedActorContainer Container{Actor, LinkedActorStruct.Name, StoredLinkActors.Num(), false};
				StoredLinkActors.Add(Container);
			}
		}
	}

	if (LinkActorData != nullptr)
	{
		for (FLinkActorStruct LinkedActorStruct : LinkActorData->LinkedActorStructs)
		{
			for (int i = 0; i < LinkedActorStruct.MaxInstances; i++)
			{
				auto Actor = GetWorld()->SpawnActor(LinkedActorStruct.ActorClass);
				Actor->SetActorHiddenInGame(true);
				FLinkedActorContainer Container{Actor, LinkedActorStruct.Name, StoredLinkActors.Num(), false};
				StoredLinkActors.Add(Container);
			}
		}
	}

	if (!GameState) InitPlayer();
}

uint32 APlayerObject::FlipInput(uint32 Input)
{
	const unsigned int Bit1 = Input >> 2 & 1;
	const unsigned int Bit2 = Input >> 3 & 1;
	unsigned int x = Bit1 ^ Bit2;

	x = x << 2 | x << 3;

	return Input ^ x;
}

void APlayerObject::InitPlayer()
{
	Player = this;
	CurrentHealth = MaxHealth;
	EnableFlip(true);
	InitBP();
}

void APlayerObject::HandleStateMachine(bool Buffer, FStateMachine& StateMachine)
{
	for (int i = StateMachine.States.Num() - 1; i >= 0; i--)
	{
		if (CanEnterState(StateMachine.States[i], StateMachine.StateMachineName))
		{
			if (HandleAutoCombo(i, StateMachine)) return;
			if (HandleStateInputs(i, Buffer, StateMachine))
			{
				bIsAutoCombo = false;
				return;
			}
		}
	}
}

bool APlayerObject::HandleAutoCombo(int32 StateIndex, FStateMachine& StateMachine)
{
	if (!FindAutoComboCancelOption(StateMachine.States[StateIndex]->Name)) return false;

	bool AutoComboSuccess = false;
	for (int i = 0; i < 8; i++)
	{
		const auto AutoComboCancel = AutoComboCancels[i];
		if (AutoComboCancel != StateIndex) continue;

		EInputFlags Button;
		switch (i)
		{
		case 0:
			Button = INP_A;
			break;
		case 1:
			Button = INP_A;
			break;
		case 2:
			Button = INP_A;
			break;
		case 3:
			Button = INP_A;
			break;
		case 4:
			Button = INP_A;
			break;
		case 5:
			Button = INP_A;
			break;
		case 6:
			Button = INP_A;
			break;
		case 7:
			Button = INP_A;
			break;
		default:
			Button = INP_A;
			break;
		}

		FInputCondition AutoComboCondition;
		AutoComboCondition.Sequence.Add(FInputBitmask(Button));
		AutoComboCondition.Sequence.Last().Lenience = 0;
		AutoComboCondition.Method = EInputMethod::Once;

		if (CheckInput(AutoComboCondition))
		{
			AutoComboSuccess = true;
			break;
		}
	}

	if (!AutoComboSuccess) return false;

	bIsAutoCombo = HandleStateTransition(StateIndex, true, StateMachine);
	return bIsAutoCombo;
}

bool APlayerObject::HandleStateInputs(int32 StateIndex, bool Buffer, FStateMachine& StateMachine)
{
	for (FInputConditionList& List : StateMachine.States[StateIndex]->InputConditionLists)
	{
		for (int v = 0; v < List.InputConditions.Num(); v++) //iterate over input conditions
		{
			//check input condition against input buffer, if not met break.
			if (!StoredInputBuffer.CheckInputCondition(List.InputConditions[v],
			                                           (CancelFlags & CNC_EnableKaraCancel) == 0))
			{
				break;
			}
			if (v == List.InputConditions.Num() - 1) //have all conditions been met?
			{
				return HandleStateTransition(StateIndex, Buffer, StateMachine);
			}
		}
		if (List.InputConditions.Num() == 0) //if no input conditions, set state
		{
			return HandleStateTransition(StateIndex, Buffer, StateMachine);
		}
	}
	return false;
}

bool APlayerObject::HandleStateTransition(int32 StateIndex, bool Buffer, FStateMachine& StateMachine)
{
	if (FindChainCancelOption(StateMachine.States[StateIndex]->Name)
		|| FindAutoComboCancelOption(StateMachine.States[StateIndex]->Name)
		|| FindWhiffCancelOption(StateMachine.States[StateIndex]->Name)
		|| CancelFlags & CNC_CancelIntoSelf) //if cancel option, allow resetting state
	{
		if (Buffer)
		{
			BufferedStateName = StateMachine.States[StateIndex]->Name;
			return true; //don't try to enter another state
		}
		if (StateMachine.ForceSetState(StateMachine.States[StateIndex]->Name)) //if state set successful...
		{
			GotoLabelActive = false;
			switch (StateMachine.States[StateIndex]->EntryStance)
			{
			case EEntryStance::Standing:
				Stance = ACT_Standing;
				break;
			case EEntryStance::Crouching:
				Stance = ACT_Crouching;
				break;
			case EEntryStance::Jumping:
				Stance = ACT_Jumping;
				break;
			default:
				break;
			}
			return true; //don't try to enter another state
		}
	}
	else
	{
		if (Buffer)
		{
			BufferedStateName = StateMachine.States[StateIndex]->Name;
			return true; //don't try to enter another state
		}
		if (StateMachine.SetState(StateMachine.States[StateIndex]->Name)) //if state set successful...
		{
			GotoLabelActive = false;
			switch (StateMachine.States[StateIndex]->EntryStance)
			{
			case EEntryStance::Standing:
				Stance = ACT_Standing;
				break;
			case EEntryStance::Crouching:
				Stance = ACT_Crouching;
				break;
			case EEntryStance::Jumping:
				Stance = ACT_Jumping;
				break;
			default:
				break;
			}
			return true; //don't try to enter another state
		}
	}
	return false; //state couldn't be entered
}

void APlayerObject::Update()
{
	if ((PlayerFlags & PLF_IsOnScreen) == 0)
	{
		return;
	}

	if (Inputs != StoredInputBuffer.InputBufferInternal[InputBufferSize - 1])
	{
		IntroEndFlag = true;
		if (RoundWinTimer <= 0)
		{
			RoundEndFlag = true;
		}
	}

	Super::Update();
	CallSubroutine(Subroutine_Cmn_OnUpdate);
	CallSubroutine(Subroutine_OnUpdate);

	if (GameState->GameInstance->IsTraining)
	{
		if ((PlayerFlags & PLF_IsStunned) == 0)
		{
			CurrentHealth = MaxHealth;
			RecoverableHealth = 0;
		}
		if ((AttackFlags & ATK_IsAttacking) == 0 && ComboTimer <= 0)
		{
			GameState->BattleState.Meter[PlayerIndex] = GameState->BattleState.MaxMeter[PlayerIndex];
			for (int i = 0; i < GameState->BattleState.MaxGauge.Num(); i++)
			{
				if (PlayerIndex == 0) GameState->BattleState.GaugeP1[i] = GameState->BattleState.MaxGauge[i];
				else GameState->BattleState.GaugeP2[i] = GameState->BattleState.MaxGauge[i];
			}
		}
		if (PlayerIndex == 1)
		{
			if (CheckIsStunned())
				Inputs = INP_A | (Direction == DIR_Right ? INP_Left : INP_Right);
			else
				Inputs = INP_Neutral;
		}
	}

	if (GameState->BattleState.TimeUntilRoundStart > 0)
		Inputs = INP_Neutral;

	//run input buffer before checking hitstop
	if ((Direction == DIR_Left && !Player->FlipInputs) || (Player->FlipInputs && Direction == DIR_Right))
	//flip inputs with direction
	{
		Player->Inputs = FlipInput(Player->Inputs);
	}

	if ((PlayerFlags & PLF_IsStunned) == 0)
	{
		Enemy->ComboCounter = 0;
		Enemy->ComboTimer = 0;
		Enemy->CallSubroutine(Subroutine_Cmn_OnComboEnd);
		Enemy->CallSubroutine(Subroutine_OnComboEnd);
		TotalProration = 10000;
		OTGCount = 0;
		bCrumpled = false;
	}
	if (Inputs << 27 == 0) //if no direction, set neutral input
		Inputs |= INP_Neutral;
	else
		Inputs = Inputs & ~INP_Neutral; //remove neutral input if directional input

	if (PlayerFlags & PLF_IsThrowLock)
	{
		if (!bIsCpu) StoredInputBuffer.Update(Inputs);
		
		HandleStateMachine(true, PrimaryStateMachine); //handle state transitions
		PrimaryStateMachine.Update();
		
		for (auto& StateMachine : SubStateMachines)
		{
			HandleStateMachine(false, StateMachine);
			StateMachine.Update();
		}

		if (TimeUntilNextCel > 0)
			TimeUntilNextCel--;
		if (TimeUntilNextCel == 0)
			CelIndex++;

		if (ActionTime < ThrowTechTimer)
		{
			if (PrimaryStateMachine.GetStateIndex(State_Universal_Throw) != INDEX_NONE)
			{
				bool IsTech = true;
				if (!CanProximityThrow)
				{
					const auto ThrowState = PrimaryStateMachine.States[PrimaryStateMachine.GetStateIndex(
						State_Universal_Throw)];
					for (auto InputConditionList : ThrowState->InputConditionLists)
					{
						IsTech = true;
						for (auto InputCondition : InputConditionList.InputConditions)
						{
							if (!CheckInput(InputCondition))
							{
								IsTech = false;
								break;
							}
						}
						if (IsTech == true) break;
					}
				}
				else
				{
					FInputCondition Left;
					FInputBitmask BitmaskLeft;
					BitmaskLeft.InputFlag = INP_Left;
					BitmaskLeft.Lenience = 1;
					Left.Sequence.Add(BitmaskLeft);
					Left.Method = EInputMethod::Strict;
					FInputCondition Right;
					FInputBitmask BitmaskRight;
					BitmaskRight.InputFlag = INP_Right;
					BitmaskRight.Lenience = 1;
					Right.Sequence.Add(BitmaskRight);
					Right.Method = EInputMethod::Strict;
					if (!CheckInput(ProximityThrowInput) || (!CheckInput(Left) && !CheckInput(Right)))
					{
						IsTech = false;
					}
				}
				if (IsTech)
				{
					PlayerFlags &= ~PLF_IsThrowLock;
					FaceOpponent();
					if (Enemy->Stance != ACT_Jumping)
					{
						JumpToState(State_Universal_GuardBreakStand);
						Enemy->JumpToState(State_Universal_GuardBreakStand);
						InitEventHandler(EVT_Update, "ThrowTech", 0, FGameplayTag::EmptyTag);
						Enemy->InitEventHandler(EVT_Update, "ThrowTech", 0, FGameplayTag::EmptyTag);
					}
					else
					{
						JumpToState(State_Universal_GuardBreakAir);
						Enemy->JumpToState(State_Universal_GuardBreakAir);
						InitEventHandler(EVT_Update, "ThrowTechAir", 0, FGameplayTag::EmptyTag);
						Enemy->InitEventHandler(EVT_Update, "ThrowTechAir", 0, FGameplayTag::EmptyTag);
					}
					HitPosX = (PosX + Enemy->PosX) / 2;
					HitPosY = (PosY + Enemy->PosY) / 2 + 250000;
					CreateCommonParticle(Particle_ThrowTech, POS_Hit);
					return;
				}
			}
		}
		ActionTime++;
		return;
	}

	if (CurrentHealth <= 0 && (PlayerFlags & PLF_IsDead) == 0)
	{
		PlayerFlags |= PLF_IsDead;
		RecoverableHealth = 0;
		if (Enemy->CurrentHealth > 0 && !(PlayerFlags & PLF_DeathCamOverride) && IsMainPlayer())
		{
			if (ReceivedHitCommon.AttackLevel < 2)
			{
				AddCommonBattleObject(State_BattleObject_KO_S);
			}
			else if (ReceivedHitCommon.AttackLevel < 4)
			{
				AddCommonBattleObject(State_BattleObject_KO_M);
			}
			else
			{
				AddCommonBattleObject(State_BattleObject_KO_L);
			}
			Hitstop = 0;
			AttackOwner->Hitstop = 0;
		}
		if (Enemy->CurrentHealth == 0 && (Enemy->PlayerFlags & PLF_IsDead) == 0)
		{
			AddCommonBattleObject(State_BattleObject_KO_Draw);
			Hitstop = 0;
			AttackOwner->Hitstop = 0;
		}
		else if (!IsMainPlayer())
		{
			PlayerFlags &= ~PLF_IsOnScreen;
		}
	}

	if (Hitstop > 0)
	{
		if (PlayerFlags & PLF_IsStunned)
			HandleBufferedState();
		GetBoxes();
		if (!bIsCpu) StoredInputBuffer.Update(Inputs);
		HandleStateMachine(true, PrimaryStateMachine); //handle state transitions
		for (auto& StateMachine : SubStateMachines)
		{
			HandleStateMachine(false, StateMachine);
		}
		return;
	}

	//reset moves used in combo if not currently doing combo 
	if (PrimaryStateMachine.CurrentState->StateType != EStateType::NormalAttack
		&& PrimaryStateMachine.CurrentState->StateType != EStateType::SpecialAttack
		&& PrimaryStateMachine.CurrentState->StateType != EStateType::SuperAttack)
	{
		MovesUsedInCombo.Empty();
	}

	HandleBufferedState();

	if (!(AttackFlags & ATK_IsAttacking)) //enable kara cancel when not attacking
		CancelFlags |= CNC_EnableKaraCancel;

	if (StrikeInvulnerableTimer > 0)
		StrikeInvulnerableTimer--;
	if (ThrowInvulnerableTimer > 0)
		ThrowInvulnerableTimer--;
	if (ThrowResistTimer > 0)
		ThrowResistTimer--;

	if (PosY > GroundHeight) //set jumping if above ground
		Stance = ACT_Jumping;

	if (ComboCounter > 0)
		ComboTimer++;

	if (MeterCooldownTimer > 0)
		MeterCooldownTimer--;

	if (!bIsCpu)
	{
		if (IsMainPlayer() && ((PlayerFlags & PLF_RoundWinInputLock) == 0
			|| GameState->BattleState.BattleFormat == EBattleFormat::Tag))
		{
			StoredInputBuffer.Update(Inputs);
		}
		else StoredInputBuffer.Update(INP_Neutral);
	}

	if (AirDashTimer > 0)
		AirDashTimer--;
	if (AirDashTimer == 1)
		CallSubroutine(Subroutine_Cmn_AnyCancel_Air);

	if (AirDashNoAttackTime > 0)
		AirDashNoAttackTime--;
	if (AirDashNoAttackTime == 1)
		EnableAttacks();

	if (StunTime > 0)
		StunTime--;
	if (StunTime == 0 && !(PlayerFlags & PLF_IsDead) && CheckIsStunned())
	{
		if (PrimaryStateMachine.CurrentState->StateType == EStateType::Blockstun)
		{
			if (Stance == ACT_Standing)
			{
				JumpToState(State_Universal_StandBlockEnd);
			}
			else if (Stance == ACT_Crouching)
			{
				JumpToState(State_Universal_CrouchBlockEnd);
			}
			else
			{
				JumpToState(State_Universal_AirBlockEnd);
			}
		}
		else if (PosY == GroundHeight && GetCurrentStateName(StateMachine_Primary) != State_Universal_FaceDownWakeUp
			&& GetCurrentStateName(StateMachine_Primary) != State_Universal_FaceUpWakeUp && !(PlayerFlags & PLF_IsKnockedDown))
		{
			if (Stance == ACT_Standing)
			{
				JumpToState(State_Universal_Stand);
			}
			else if (Stance == ACT_Crouching)
			{
				JumpToState(State_Universal_Crouch);
			}
		}
		else
		{
			if (((PlayerFlags & PLF_IsKnockedDown) == 0 || (PlayerFlags & PLF_IsHardKnockedDown) == 0) && (PlayerFlags &
				PLF_IsDead) == 0)
				EnableState(ENB_Tech, StateMachine_Primary);
		}
	}

	if (PlayerFlags & PLF_TouchingWall && Enemy->PrimaryStateMachine.CurrentState->StateType != EStateType::Hitstun &&
		Pushback != 0)
	{
		if (IsValid(AttackOwner))
			AttackOwner->Pushback = Pushback;
		Pushback = 0;
	}

	if (PrimaryStateMachine.CurrentState->StateType != EStateType::Hitstun)
	{
		PlayerFlags &= ~PLF_IsKnockedDown;
	}

	if (PrimaryStateMachine.CurrentState->StateType != EStateType::Hitstun
		&& PrimaryStateMachine.CurrentState->StateType != EStateType::Blockstun)
	{
		if (Enemy->PrimaryStateMachine.CurrentState->StateType != EStateType::Hitstun
			&& Enemy->PrimaryStateMachine.CurrentState->StateType != EStateType::Blockstun)
			Pushback = 0;
		PlayerFlags &= ~PLF_IsStunned;
		DisableState(ENB_Tech, StateMachine_Primary);
	}

	if ((GetCurrentStateName(StateMachine_Primary) == State_Universal_FaceDownLoop || GetCurrentStateName(StateMachine_Primary) == State_Universal_FaceUpLoop)
		&& ActionTime >= ReceivedHit.KnockdownTime && (PlayerFlags & PLF_IsDead) == 0)
	{
		Enemy->ComboCounter = 0;
		Enemy->ComboTimer = 0;
		OTGCount = 0;
		if (PrimaryStateMachine.CurrentState->Name == State_Universal_FaceDownLoop)
			JumpToState(State_Universal_FaceDownWakeUp);
		else if (PrimaryStateMachine.CurrentState->Name == State_Universal_FaceUpLoop)
			JumpToState(State_Universal_FaceUpWakeUp);
		PlayerFlags &= ~PLF_IsKnockedDown;
		DisableState(ENB_Tech, StateMachine_Primary);
	}

	if (PlayerFlags & PLF_IsDead)
		DisableState(ENB_Tech, StateMachine_Primary);

	InstantBlockLockoutTimer--;

	if (PrimaryStateMachine.CurrentState->StateType == EStateType::Hitstun && ReceivedHit.WallBounce.WallBounceCount > 0
		&& PosY > GroundHeight)
		HandleWallBounce();

	if (PosY == GroundHeight && PrevPosY != GroundHeight) //reset air move counts on ground
	{
		CurrentAirJumpCount = AirJumpCount;
		CurrentAirDashCount = AirDashCount;
		if (PlayerFlags & PLF_DefaultLandingAction && PrimaryStateMachine.CurrentState->StateType != EStateType::Hitstun)
		{
			JumpToState(State_Universal_JumpLanding);
		}
		SetStance(ACT_Standing);
		TriggerEvent(EVT_Landing, StateMachine_Primary);
		CallSubroutine(Subroutine_Cmn_OnLanding);
		CallSubroutine(Subroutine_OnLanding);
		CreateCommonParticle(Particle_JumpSmoke_Land, POS_Player);
	}

	if (PosY <= GroundHeight && PrevPosY > GroundHeight && PrimaryStateMachine.CurrentState->StateType ==
		EStateType::Hitstun)
	{
		if (GetCurrentStateName(StateMachine_Primary) != State_Universal_FloatingCrumpleBody && GetCurrentStateName(StateMachine_Primary) !=
			State_Universal_FloatingCrumpleHead)
		{
			if (ReceivedHit.GroundBounce.GroundBounceCount > 0)
				HandleGroundBounce();
			else
			{
				StunTime = 0;
				StunTimeMax = 0;
				PlayerFlags |= PLF_IsKnockedDown;
				if ((PlayerFlags & PLF_IsHardKnockedDown) == 0 && !(PlayerFlags & PLF_IsDead))
					EnableState(ENB_Tech, StateMachine_Primary);
			}
		}
	}

	HandleProximityBlock();

	if (Stance == ACT_Standing) //set pushbox values based on stance
	{
		PushWidth = StandPushWidth;
		PushHeight = StandPushHeight;
		PushHeightLow = 0;
	}
	else if (Stance == ACT_Crouching)
	{
		PushWidth = CrouchPushWidth;
		PushHeight = CrouchPushHeight;
		PushHeightLow = 0;
	}
	else if (Stance == ACT_Jumping)
	{
		PushWidth = AirPushWidth;
		PushHeight = AirPushHeight;
		PushHeightLow = AirPushHeightLow;
	}

	HandleStateMachine(false, PrimaryStateMachine);
	Player->PrimaryStateMachine.Update();
	
	for (auto& StateMachine : SubStateMachines)
	{
		HandleStateMachine(false, StateMachine);
		StateMachine.Update();
	}

	TriggerEvent(EVT_Update, StateMachine_Primary);

	if (TimeUntilNextCel > 0)
		TimeUntilNextCel--;
	if (TimeUntilNextCel == 0)
		CelIndex++;

	GetBoxes();

	HandleThrowCollision();

	if (CurrentHealth > MaxHealth) CurrentHealth = MaxHealth;

	GameState->SetScreenBounds();
	ActionTime++;
}

void APlayerObject::UpdateNotBattle()
{
	Player->PrimaryStateMachine.Update();

	if (TimeUntilNextCel > 0)
		TimeUntilNextCel--;
	if (TimeUntilNextCel == 0)
		CelIndex++;
	GetBoxes();

	UpdateVisuals();
}

void APlayerObject::EditorUpdate_Implementation()
{
	Player = this;

	GetBoxes();
	UpdateVisuals();
}

void APlayerObject::HandleHitAction(EHitAction HACT)
{
	int32 FinalHitstop = ReceivedHit.Hitstop + ReceivedHit.EnemyHitstopModifier;

	AttackOwner->Hitstop = ReceivedHit.Hitstop;
	Hitstop = FinalHitstop;

	int32 Proration = ReceivedHit.ForcedProration;
	if (Enemy->ComboCounter == 0)
		Proration *= ReceivedHit.InitialProration;
	else
		Proration *= 100;
	if (Enemy->ComboCounter == 0)
		TotalProration = 10000;
	Proration = Proration * TotalProration / 10000;

	if ((AttackFlags & ATK_ProrateOnce) == 0 || (AttackFlags & ATK_ProrateOnce && Enemy->ComboCounter == 0))
		TotalProration = Proration;
	else
		Proration = TotalProration;

	Enemy->ComboCounter++;

	if (ReceivedHitCommon.DeathCamOverride)
		PlayerFlags |= PLF_DeathCamOverride;

	else
		PlayerFlags &= ~PLF_DeathCamOverride;

	if (PlayerFlags & PLF_IsKnockedDown)
	{
		if (PosY <= GroundHeight)
			PosY = GroundHeight + 1;

		if (!(AttackOwner->AttackFlags & ATK_IgnoreOTG))
			OTGCount++;
		PlayerFlags &= ~PLF_IsKnockedDown;
	}

	int FinalDamage;
	if (Enemy->ComboCounter == 1)
		FinalDamage = ReceivedHit.Damage;
	else
		FinalDamage = ReceivedHit.Damage * Proration * Enemy->ComboRate / 1000000;

	if (FinalDamage < ReceivedHit.MinimumDamagePercent * ReceivedHit.Damage / 100)
		FinalDamage = ReceivedHit.Damage * ReceivedHit.MinimumDamagePercent / 100;

	if (OTGCount > MaxOTGCount && !(AttackOwner->AttackFlags & ATK_IgnoreOTG))
		FinalDamage = FinalDamage * OtgProration / 100;

	CurrentHealth -= FinalDamage;
	if (!(PlayerFlags & PLF_IsDead))
	{
		if (IsMainPlayer())
		{
			RecoverableHealth += FinalDamage * ReceivedHit.RecoverableDamagePercent / 100;
		}
		else
		{
			RecoverableHealth += FinalDamage;
		}
	}

	if (GameState->GameInstance->IsTraining && CurrentHealth < 1)
		CurrentHealth = 1;

	AddMeter(FinalDamage * MeterPercentOnReceiveHit / 100);
	Enemy->AddMeter(FinalDamage * Enemy->MeterPercentOnHit / 100);

	EnableCancelIntoSelf(true);

	switch (ReceivedHit.Position.Type)
	{
	case HPT_Rel:
		AddPosXWithDir(ReceivedHit.Position.PosX);
		PosY += ReceivedHit.Position.PosY;
		if (PosY < GroundHeight)
			PosY = GroundHeight;
		break;
	case HPT_Abs:
		PosX = ReceivedHit.Position.PosX;
		PosY = ReceivedHit.Position.PosY;
		break;
	case HPT_Add:
		PosX += ReceivedHit.Position.PosX;
		PosY += ReceivedHit.Position.PosY;
		if (PosY < GroundHeight)
			PosY = GroundHeight;
		break;
	default:
		break;
	}

	for (int i = GameState->Players.Num(); i < GameState->BattleState.ActiveObjectCount; i++)
	{
		if (GameState->SortedObjects[i]->Player == this && GameState->SortedObjects[i]->MiscFlags &
			MISC_DeactivateOnReceiveHit)
			GameState->SortedObjects[i]->DeactivateObject();
	}
	if (CurrentHealth <= 0)
	{
		if (!(PlayerFlags & PLF_IsDead))
			StartSuperFreeze(0);

		CurrentHealth = 0;
		if (PosY <= GroundHeight && !(PlayerFlags & PLF_IsKnockedDown))
		{
			if (HACT == HACT_AirFaceUp || HACT == HACT_AirNormal || HACT == HACT_FloatingCrumple)
				BufferedStateName = State_Universal_Launch_B;
			else if (HACT == HACT_AirVertical)
				BufferedStateName = State_Universal_Launch_V;
			else if (HACT == HACT_AirFaceDown)
				BufferedStateName = State_Universal_Launch_F;
			else if (HACT == HACT_Blowback)
				BufferedStateName = State_Universal_Blowback;
			else if (HACT == HACT_Tailspin)
				BufferedStateName = State_Universal_Tailspin;
			else
			{
				BufferedStateName = State_Universal_Crumple;
			}
		}
		else
		{
			if (PosY <= GroundHeight)
				PosY = GroundHeight + 1;
			if (HACT == HACT_AirFaceUp || HACT == HACT_AirNormal)
				BufferedStateName = State_Universal_Launch_B;
			else if (HACT == HACT_AirVertical)
				BufferedStateName = State_Universal_Launch_V;
			else if (HACT == HACT_AirFaceDown)
				BufferedStateName = State_Universal_Launch_F;
			else if (HACT == HACT_Blowback)
				BufferedStateName = State_Universal_Blowback;
			else if (HACT == HACT_Tailspin)
				BufferedStateName = State_Universal_Tailspin;
			else
				BufferedStateName = State_Universal_Launch_B;
		}
		return;
	}
	if (bLimitCrumple && bCrumpled && HACT == HACT_Crumple)
	{
		HACT = HACT_AirNormal;
	}
	switch (HACT)
	{
	case HACT_GroundNormal:
		switch (Stance)
		{
		case ACT_Standing:
		default:
			if (ReceivedHitCommon.AttackLevel == 0)
				BufferedStateName = FGameplayTag(State_Universal_Hitstun_0);
			else if (ReceivedHitCommon.AttackLevel == 1)
				BufferedStateName = FGameplayTag(State_Universal_Hitstun_1);
			else if (ReceivedHitCommon.AttackLevel == 2)
				BufferedStateName = FGameplayTag(State_Universal_Hitstun_2);
			else if (ReceivedHitCommon.AttackLevel == 3)
				BufferedStateName = FGameplayTag(State_Universal_Hitstun_3);
			else if (ReceivedHitCommon.AttackLevel == 4)
				BufferedStateName = FGameplayTag(State_Universal_Hitstun_4);
			else if (ReceivedHitCommon.AttackLevel == 5)
				BufferedStateName = FGameplayTag(State_Universal_Hitstun_5);
			break;
		case ACT_Crouching:
			if (ReceivedHitCommon.AttackLevel == 0)
				BufferedStateName = FGameplayTag(State_Universal_CrouchHitstun_0);
			else if (ReceivedHitCommon.AttackLevel == 1)
				BufferedStateName = FGameplayTag(State_Universal_CrouchHitstun_1);
			else if (ReceivedHitCommon.AttackLevel == 2)
				BufferedStateName = FGameplayTag(State_Universal_CrouchHitstun_2);
			else if (ReceivedHitCommon.AttackLevel == 3)
				BufferedStateName = FGameplayTag(State_Universal_CrouchHitstun_3);
			else if (ReceivedHitCommon.AttackLevel == 4)
				BufferedStateName = FGameplayTag(State_Universal_CrouchHitstun_4);
			else if (ReceivedHitCommon.AttackLevel == 5)
				BufferedStateName = FGameplayTag(State_Universal_CrouchHitstun_5);
			StunTime += 1;
			StunTimeMax += 1;
		}
		break;
	case HACT_Crumple:
		BufferedStateName = FGameplayTag(State_Universal_Crumple);
		break;
	case HACT_ForceCrouch:
		Stance = ACT_Crouching;
		if (ReceivedHitCommon.AttackLevel == 0)
			BufferedStateName = FGameplayTag(State_Universal_CrouchHitstun_0);
		else if (ReceivedHitCommon.AttackLevel == 1)
			BufferedStateName = FGameplayTag(State_Universal_CrouchHitstun_1);
		else if (ReceivedHitCommon.AttackLevel == 2)
			BufferedStateName = FGameplayTag(State_Universal_CrouchHitstun_2);
		else if (ReceivedHitCommon.AttackLevel == 3)
			BufferedStateName = FGameplayTag(State_Universal_CrouchHitstun_3);
		else if (ReceivedHitCommon.AttackLevel == 4)
			BufferedStateName = FGameplayTag(State_Universal_CrouchHitstun_4);
		else if (ReceivedHitCommon.AttackLevel == 5)
			BufferedStateName = FGameplayTag(State_Universal_CrouchHitstun_5);
		StunTime += 1;
		StunTimeMax += 1;
		break;
	case HACT_ForceStand:
		Stance = ACT_Standing;
		if (ReceivedHitCommon.AttackLevel == 0)
			BufferedStateName = FGameplayTag(State_Universal_Hitstun_0);
		else if (ReceivedHitCommon.AttackLevel == 1)
			BufferedStateName = FGameplayTag(State_Universal_Hitstun_1);
		else if (ReceivedHitCommon.AttackLevel == 2)
			BufferedStateName = FGameplayTag(State_Universal_Hitstun_2);
		else if (ReceivedHitCommon.AttackLevel == 3)
			BufferedStateName = FGameplayTag(State_Universal_Hitstun_3);
		else if (ReceivedHitCommon.AttackLevel == 4)
			BufferedStateName = FGameplayTag(State_Universal_Hitstun_4);
		else if (ReceivedHitCommon.AttackLevel == 5)
			BufferedStateName = FGameplayTag(State_Universal_Hitstun_5);
		break;
	case HACT_GuardBreakCrouch:
		BufferedStateName = State_Universal_GuardBreakCrouch;
		break;
	case HACT_GuardBreakStand:
		BufferedStateName = State_Universal_GuardBreakStand;
		break;
	case HACT_AirNormal:
	case HACT_AirFaceUp:
		BufferedStateName = State_Universal_Launch_B;
		break;
	case HACT_AirVertical:
		BufferedStateName = State_Universal_Launch_V;
		break;
	case HACT_AirFaceDown:
		BufferedStateName = State_Universal_Launch_F;
		break;
	case HACT_Blowback:
		BufferedStateName = State_Universal_Blowback;
		break;
	case HACT_Tailspin:
		BufferedStateName = State_Universal_Tailspin;
		break;
	case HACT_FloatingCrumple:
		if (ReceivedHit.FloatingCrumpleType == FLT_Body)
			BufferedStateName = State_Universal_FloatingCrumpleBody;
		else
			BufferedStateName = State_Universal_FloatingCrumpleHead;
		break;
	case HACT_None: break;
	default: ;
	}
	DisableAll(StateMachine_Primary);
}

void APlayerObject::SetHitValuesOverTime()
{
	if (PrimaryStateMachine.CurrentState->StateType == EStateType::Hitstun && PosY > GroundHeight
		&& GetCurrentStateName(StateMachine_Primary) != State_Universal_FloatingCrumpleBody && GetCurrentStateName(StateMachine_Primary) !=
		State_Universal_FloatingCrumpleHead)
	{
		const int32 CurrentStunTime = StunTimeMax - StunTime;
		if (ReceivedHit.AirPushbackXOverTime.BeginFrame <= CurrentStunTime
			&& ReceivedHit.AirPushbackXOverTime.EndFrame > CurrentStunTime)
		{
			SpeedX = SpeedX * ReceivedHit.AirPushbackXOverTime.Value / 100;
		}
		if (ReceivedHit.AirPushbackYOverTime.BeginFrame <= CurrentStunTime
			&& ReceivedHit.AirPushbackYOverTime.EndFrame > CurrentStunTime
			&& SpeedY > 0)
		{
			SpeedY = SpeedY * ReceivedHit.AirPushbackYOverTime.Value / 100;
		}
		if (ReceivedHit.GravityOverTime.BeginFrame <= CurrentStunTime
			&& ReceivedHit.GravityOverTime.EndFrame > CurrentStunTime)
		{
			Gravity += ReceivedHit.GravityOverTime.Value;
		}
	}
}

void APlayerObject::SetHitValues()
{
	if (!GameState) return;
	if (!Enemy->CheckIsStunned())
		GameState->SetDrawPriorityFront(Enemy);

	int32 FinalHitPushbackX;
	int32 FinalAirHitPushbackX;
	int32 FinalAirHitPushbackY;
	int32 FinalGravity;

	if (!(AttackFlags & ATK_IgnorePushbackScaling))
	{
		FinalHitPushbackX = ReceivedHit.GroundPushbackX + MovesUsedInCombo.Num() * 500;
		FinalAirHitPushbackX = ReceivedHit.AirPushbackX + MovesUsedInCombo.Num() * 150;
		FinalAirHitPushbackY = ReceivedHit.AirPushbackY - MovesUsedInCombo.Num() * 150;
		FinalGravity = ReceivedHit.Gravity + MovesUsedInCombo.Num() * 10;
	}
	else
	{
		FinalHitPushbackX = ReceivedHit.GroundPushbackX;
		FinalAirHitPushbackX = ReceivedHit.AirPushbackX;
		FinalAirHitPushbackY = ReceivedHit.AirPushbackY;
		FinalGravity = ReceivedHit.Gravity;
	}

	EHitAction HACT;

	if (PosY == GroundHeight && !(PlayerFlags & PLF_IsKnockedDown))
		HACT = ReceivedHit.GroundHitAction;
	else
		HACT = ReceivedHit.AirHitAction;

	if (FinalHitPushbackX != -1)
		Pushback = -FinalHitPushbackX;
	else
		Pushback = 0;

	switch (ReceivedHit.Position.Type)
	{
	case HPT_RelNextFrame:
		AddPosXWithDir(ReceivedHit.Position.PosX);
		PosY += ReceivedHit.Position.PosY;
		if (PosY < GroundHeight)
			PosY = GroundHeight;
		break;
	case HPT_AbsNextFrame:
		PosX = ReceivedHit.Position.PosX;
		PosY = ReceivedHit.Position.PosY;
		break;
	case HPT_AddNextFrame:
		AddPosXWithDir(ReceivedHit.Position.PosX);
		PosY += ReceivedHit.Position.PosY;
		if (PosY < GroundHeight)
			PosY = GroundHeight;
		break;
	default:
		break;
	}

	int32 FinalHitstun = ReceivedHit.Hitstun;
	int32 FinalUntech = ReceivedHit.Untech;
	if (!(AttackFlags & ATK_IgnoreHitstunScaling))
	{
		if (Enemy->ComboTimer >= 14 * 60)
		{
			FinalHitstun = FinalHitstun * 50 / 100;
			FinalUntech = FinalUntech * 70 / 100;
		}
		else if (Enemy->ComboTimer >= 10 * 60)
		{
			FinalHitstun = FinalHitstun * 60 / 100;
			FinalUntech = FinalUntech * 80 / 100;
		}
		else if (Enemy->ComboTimer >= 7 * 60)
		{
			FinalHitstun = FinalHitstun * 70 / 100;
			FinalUntech = FinalUntech * 90 / 100;
		}
		else if (Enemy->ComboTimer >= 5 * 60)
		{
			FinalHitstun = FinalHitstun * 80 / 100;
		}
		else if (Enemy->ComboTimer >= 3 * 60)
		{
			FinalHitstun = FinalHitstun * 90 / 100;
		}
	}

	if (bLimitCrumple && bCrumpled && HACT == HACT_Crumple)
	{
		HACT = HACT_AirNormal;
	}
	switch (HACT)
	{
	case HACT_GroundNormal:
	case HACT_ForceCrouch:
	case HACT_ForceStand:
		StunTime = FinalHitstun;
		StunTimeMax = FinalHitstun;
		if (PlayerFlags & PLF_TouchingWall && FinalHitPushbackX != -1)
		{
			AttackOwner->Pushback = -FinalHitPushbackX;
			Pushback = 0;
		}
		break;
	case HACT_FloatingCrumple:
		if (CurrentHealth <= 0)
		{
			if (PosY <= GroundHeight)
				PosY = GroundHeight + 1;
			StunTime = FinalUntech;
			StunTimeMax = FinalUntech;
			SpeedX = -FinalAirHitPushbackX;
			SpeedY = FinalAirHitPushbackY;
			Gravity = FinalGravity;
			if (PlayerFlags & PLF_TouchingWall && FinalHitPushbackX != -1)
			{
				AttackOwner->Pushback = -FinalHitPushbackX;
				Pushback = 0;
			}
			break;
		}
		StunTime = FinalUntech;
		StunTimeMax = FinalUntech;
		if (PlayerFlags & PLF_TouchingWall && FinalHitPushbackX != -1)
		{
			AttackOwner->Pushback = -FinalHitPushbackX;
			Pushback = 0;
		}
		break;
	case HACT_AirNormal:
	case HACT_AirFaceUp:
	case HACT_AirVertical:
	case HACT_AirFaceDown:
	case HACT_Tailspin:
		if (PosY <= GroundHeight)
			PosY = GroundHeight + 1;
		StunTime = FinalUntech;
		StunTimeMax = FinalUntech;
		SpeedX = -FinalAirHitPushbackX;
		SpeedY = FinalAirHitPushbackY;
		Gravity = FinalGravity;
		if (PlayerFlags & PLF_TouchingWall && FinalHitPushbackX != -1)
		{
			AttackOwner->Pushback = -FinalHitPushbackX;
			Pushback = 0;
		}
		break;
	case HACT_Crumple:
		StunTime = FinalUntech;
		StunTimeMax = FinalUntech;
		if (PlayerFlags & PLF_TouchingWall && FinalHitPushbackX != -1)
		{
			AttackOwner->Pushback = -FinalHitPushbackX;
			Pushback = 0;
		}
		bCrumpled = true;
		break;
	case HACT_Blowback:
		switch (ReceivedHit.BlowbackLevel)
		{
		case 0:
		default:
			break;
		case 1:
			GotoLabel(State_Label_Blowback_1);
			break;
		case 2:
			GotoLabel(State_Label_Blowback_2);
			break;
		case 3:
			GotoLabel(State_Label_Blowback_3);
			break;
		case 4:
			GotoLabel(State_Label_Blowback_4);
			break;
		}
		if (PosY <= GroundHeight)
			PosY = GroundHeight + 1;
		StunTime = FinalUntech;
		StunTimeMax = FinalUntech;
		SpeedX = -FinalAirHitPushbackX;
		SpeedY = FinalAirHitPushbackY;
		Gravity = FinalGravity;
		if (PlayerFlags & PLF_TouchingWall && FinalHitPushbackX != -1)
		{
			AttackOwner->Pushback = -FinalHitPushbackX;
			Pushback = 0;
		}
	default:
		break;
	}
	AirDashTimer = 0;
	AirDashNoAttackTime = 0;

	if (ReceivedHit.HardKnockdown)
		PlayerFlags |= PLF_IsHardKnockedDown;
	else
		PlayerFlags &= ~PLF_IsHardKnockedDown;

	if (OTGCount > MaxOTGCount && !(AttackOwner->AttackFlags & ATK_IgnoreOTG))
	{
		SpeedX = -30000;
		SpeedY = 8000;
		Gravity = 3500;
		StunTime = 5;
		ReceivedHit.AirPushbackXOverTime = FHitValueOverTime();
		ReceivedHit.AirPushbackYOverTime = FHitValueOverTime();
		ReceivedHit.GravityOverTime = FHitValueOverTime();
		ReceivedHit.KnockdownTime = 0;
		PlayerFlags &= ~PLF_IsHardKnockedDown;
	}
}

void APlayerObject::ForceEnableFarNormal(bool Enable)
{
	if (Enable)
	{
		PlayerFlags |= PLF_ForceEnableFarNormal;
	}
	else
	{
		PlayerFlags &= ~PLF_ForceEnableFarNormal;
	}
}

void APlayerObject::SetHeadAttribute(bool Attribute)
{
	if (Attribute)
		AttackFlags |= ATK_AttackHeadAttribute;
	else
		AttackFlags &= ~ATK_AttackHeadAttribute;
}

void APlayerObject::SetThrowActive(bool Active)
{
	if (Active)
	{
		PlayerFlags |= PLF_ThrowActive;
	}
	else
	{
		PlayerFlags &= ~PLF_ThrowActive;
	}
}

void APlayerObject::ThrowEnd()
{
	if (!Enemy) return;
	Enemy->PlayerFlags &= ~PLF_IsThrowLock;
}

void APlayerObject::SetThrowRange(int32 InThrowRange)
{
	ThrowRange = InThrowRange;
}

void APlayerObject::SetThrowExeState(FGameplayTag ExeState)
{
	ExeStateName = ExeState;
}

void APlayerObject::SetThrowPosition(int32 ThrowPosX, int32 ThrowPosY)
{
	if (!Enemy) return;
	if (Direction == DIR_Right)
		Enemy->PosX = R + ThrowPosX;
	else
		Enemy->PosX = L - ThrowPosX;
	Enemy->PosY = PosY + ThrowPosY;
}

void APlayerObject::SetDamageReactionCel(int32 Index)
{
	if (Index < Enemy->DamageReactionCels.Num())
	{
		Enemy->SetCelName(Enemy->DamageReactionCels[Index]);
	}
}

void APlayerObject::SetHitgrabActive(bool Active)
{
	if (Active)
	{
		PlayerFlags |= PLF_HitgrabActive;
	}
	else
	{
		PlayerFlags &= ~PLF_HitgrabActive;
	}
}

void APlayerObject::PlayVoiceLine(FGameplayTag Name)
{
	if (!IsValid(GameState))
		return;
	if (VoiceData != nullptr)
	{
		for (FSoundStruct SoundStruct : VoiceData->SoundDatas)
		{
			if (SoundStruct.Name == Name)
			{
				GameState->PlayVoiceLine(SoundStruct.SoundWave, SoundStruct.MaxDuration, ObjNumber - 400);
				break;
			}
		}
	}
}

void APlayerObject::PlayCommonLevelSequence(FGameplayTag Name)
{
	if (!GameState) return;
	if (CommonSequenceData != nullptr)
	{
		for (FSequenceStruct SequenceStruct : CommonSequenceData->SequenceStructs)
		{
			if (SequenceStruct.Name == Name)
			{
				GameState->PlayLevelSequence(this, Enemy, SequenceStruct.Sequence);
			}
		}
	}
}

void APlayerObject::PlayLevelSequence(FGameplayTag Name)
{
	if (!GameState) return;
	if (SequenceData != nullptr)
	{
		for (FSequenceStruct SequenceStruct : SequenceData->SequenceStructs)
		{
			if (SequenceStruct.Name == Name)
			{
				GameState->PlayLevelSequence(this, Enemy, SequenceStruct.Sequence);
			}
		}
	}
}

void APlayerObject::BattleHudVisibility(bool Visible)
{
	if (!GameState) return;
	GameState->BattleHudVisibility(Visible);
}

void APlayerObject::EndRound() const
{
	if (!GameState) return;
	GameState->RoundInit();
}

void APlayerObject::EndMatch() const
{
	if (!GameState) return;
	GameState->EndMatch_BP();
}

void APlayerObject::PauseRoundTimer(bool Pause)
{
	if (!GameState) return;
	GameState->BattleState.PauseTimer = Pause;
}

void APlayerObject::AddBattleObjectToStorage(ABattleObject* InActor, int Index)
{
	if (Index < 16)
	{
		StoredBattleObjects[Index] = InActor;
	}
}

APlayerObject* APlayerObject::CallAssist(const int AssistIndex, const FGameplayTag AssistName)
{
	if (!GameState) return nullptr;
	return GameState->CallAssist(PlayerIndex == 0, AssistIndex, AssistName);
}

APlayerObject* APlayerObject::SwitchMainPlayer(int NewTeamIndex)
{
	if (!GameState) return nullptr;
	return GameState->SwitchMainPlayer(this, NewTeamIndex);
}

bool APlayerObject::IsMainPlayer() const
{
	if (!GameState) return true;
	return this == GameState->GetMainPlayer(PlayerIndex == 0);
}

bool APlayerObject::IsOnScreen() const
{
	return (PlayerFlags & PLF_IsOnScreen) == PLF_IsOnScreen;
}

void APlayerObject::SetOnScreen(bool OnScreen)
{
	if (OnScreen)
		PlayerFlags |= PLF_IsOnScreen;
	else
		PlayerFlags &= ~PLF_IsOnScreen;
}

void APlayerObject::ToggleComponentVisibility(FName ComponentName, bool Visible)
{
	TInlineComponentArray<UPrimitiveComponent*> Components;
	GetComponents(Components);
	for (int i = 0; i < Components.Num(); i++)
	{
		if (const auto Component = Components[i]; Component->GetName() == ComponentName)
		{
			ComponentVisible[i] = Visible;
		}
	}
}

bool APlayerObject::CanEnterState(UState* State, FGameplayTag StateMachineName)
{
	FStateMachine& StateMachine = GetStateMachine(StateMachineName);
	const FGameplayTag MoveChainName = State->ShareChainName != FGameplayTag::EmptyTag
		                                   ? State->ShareChainName
		                                   : State->Name;
	if (!CheckMovesUsedInChain(MoveChainName) ||
		!((CheckStateEnabled(State->StateType, State->CustomStateType, StateMachineName) && !State->IsFollowupState)
			|| FindChainCancelOption(State->Name)
			|| FindAutoComboCancelOption(State->Name)
			|| FindWhiffCancelOption(State->Name)
			|| (CheckKaraCancel(State->StateType)
				&& !State->IsFollowupState
				&& StateMachine.GetStateIndex(State->Name) > StateMachine.GetStateIndex(
					GetCurrentStateName(StateMachine_Primary)))
		)) //check if the state is enabled
	{
		return false;
	}
	if (CheckObjectPreventingState(State->ObjectID)) //check if an object is preventing state entry
	{
		return false;
	}
	//check current character state against entry stance condition
	if (!StateMachine.CheckStateStanceCondition(State->EntryStance, Stance))
	{
		return false;
	}
	if (State->StateConditions.Num() != 0) //only check state conditions if there are any
	{
		for (int j = 0; j < State->StateConditions.Num(); j++) //iterate over state conditions
		{
			if (!HandleStateCondition(State->StateConditions[j])) //check state condition
			{
				return false;
			}
		}
	}
	if (!State->CanEnterState()) //check bp state condition
	{
		return false;
	}

	return true;
}

void APlayerObject::SetStateForCPU(FGameplayTag StateName)
{
	HandleStateTransition(PrimaryStateMachine.GetStateIndex(StateName), false, PrimaryStateMachine);
}

bool APlayerObject::CheckEnemyInRange(int32 XBegin, int32 XEnd, int32 YBegin, int32 YEnd) const
{
	// force x range to current direction
	XBegin *= Direction == DIR_Right ? 1 : -1;
	XEnd *= Direction == DIR_Right ? 1 : -1;

	XBegin += PosX;
	XEnd += PosX;
	YBegin += PosY;
	YEnd += PosY;

	if (Direction == DIR_Right)
	{
		return XBegin < Enemy->PosX && XEnd > Enemy->PosX && YBegin < Enemy->GetPosYCenter() && YEnd > Enemy->
			GetPosYCenter();
	}
	return XEnd < Enemy->PosX && XBegin > Enemy->PosX && YBegin < Enemy->GetPosYCenter() && YEnd > Enemy->
		GetPosYCenter();
}

bool APlayerObject::IsEnemyAttackState() const
{
	return Enemy->PrimaryStateMachine.CurrentState->StateType >= EStateType::NormalAttack
		&& Enemy->PrimaryStateMachine.CurrentState->StateType <= EStateType::SuperAttack;
}

bool APlayerObject::IsEnemyThrow() const
{
	return Enemy->PlayerFlags & PLF_ThrowActive;
}

bool APlayerObject::IsEnemyBlocking() const
{
	return Enemy->GetCurrentStateName(StateMachine_Primary) == State_Universal_StandBlock || Enemy->GetCurrentStateName(StateMachine_Primary) ==
		State_Universal_CrouchBlock || Enemy->GetCurrentStateName(StateMachine_Primary) == State_Universal_AirBlock;
}

EBlockType APlayerObject::GetAttackBlockType() const
{
	return HitCommon.BlockType;
}

bool APlayerObject::IsCorrectBlock(EBlockType BlockType)
{
	CallSubroutine(Subroutine_IsCorrectBlock);
	if (SubroutineReturnVal2) return SubroutineReturnVal1;
	
	if (BlockType != BLK_None && GetEnableFlags(StateMachine_Primary) & ENB_Block)
	{
		FInputCondition Left;
		FInputBitmask BitmaskLeft;
		BitmaskLeft.InputFlag = INP_Left;
		BitmaskLeft.Lenience = 10;
		Left.Sequence.Add(BitmaskLeft);
		Left.bInputAllowDisable = false;
		FInputCondition Right;
		FInputBitmask BitmaskRight;
		BitmaskRight.InputFlag = INP_Right;
		Right.Sequence.Add(BitmaskRight);
		if ((CheckInput(Left) && !CheckInput(Right) && PosY > GroundHeight) || GetCurrentStateName(StateMachine_Primary) ==
			State_Universal_AirBlock)
		{
			Left.Method = EInputMethod::Once;
			if (CheckInput(Left) && InstantBlockLockoutTimer == 0)
			{
				AddMeter(800);
			}
			return true;
		}
		FInputCondition Input1;
		FInputBitmask BitmaskDownLeft;
		BitmaskDownLeft.InputFlag = INP_DownLeft;
		BitmaskDownLeft.Lenience = 12;
		Input1.Sequence.Add(BitmaskDownLeft);
		Input1.Method = EInputMethod::Strict;
		Input1.bInputAllowDisable = false;
		if ((CheckInput(Input1) || GetCurrentStateName(StateMachine_Primary) == State_Universal_CrouchBlock) && BlockType != BLK_High && !
			CheckInput(Right))
		{
			Input1.Method = EInputMethod::OnceStrict;
			if (CheckInput(Input1) && InstantBlockLockoutTimer == 0)
			{
				AddMeter(800);
			}
			return true;
		}
		FInputCondition Input4;
		Input4.Sequence.Add(BitmaskLeft);
		Input4.Method = EInputMethod::Strict;
		Input4.bInputAllowDisable = false;
		if ((CheckInput(Input4) || GetCurrentStateName(StateMachine_Primary) == State_Universal_StandBlock) && BlockType != BLK_Low && !
			CheckInput(Right))
		{
			Input4.Method = EInputMethod::OnceStrict;
			if (CheckInput(Input4) && InstantBlockLockoutTimer == 0)
			{
				AddMeter(800);
			}
			return true;
		}
	}
	return false;
}

void APlayerObject::HandleBlockAction()
{
	AttackOwner->Hitstop = ReceivedHit.Hitstop;
	Hitstop = ReceivedHit.Hitstop + ReceivedHitCommon.EnemyBlockstopModifier;
	StunTime = ReceivedHitCommon.Blockstun;
	StunTimeMax = ReceivedHitCommon.Blockstun;

	Pushback = -ReceivedHitCommon.GroundGuardPushbackX;

	FInputCondition Input1;
	FInputBitmask BitmaskDownLeft;
	BitmaskDownLeft.InputFlag = INP_DownLeft;
	Input1.Sequence.Add(BitmaskDownLeft);
	Input1.Method = EInputMethod::Strict;
	Input1.bInputAllowDisable = false;
	switch (ReceivedHitCommon.AttackLevel)
	{
	case 0:
	default:
		GotoLabel(State_Label_Block_Level1);
		break;
	case 1:
		GotoLabel(State_Label_Block_Level1);
		break;
	case 2:
		GotoLabel(State_Label_Block_Level2);
		break;
	case 3:
		GotoLabel(State_Label_Block_Level2);
		break;
	case 4:
		GotoLabel(State_Label_Block_Level3);
		break;
	case 5:
		GotoLabel(State_Label_Block_Level3);
		break;
	}
	if (Stance == ACT_Jumping || GetCurrentStateName(StateMachine_Primary) == State_Universal_AirBlock)
	{
		JumpToState(State_Universal_AirBlock, true);
		Stance = ACT_Jumping;
	}
	else if (CheckInput(Input1) || GetCurrentStateName(StateMachine_Primary) == State_Universal_CrouchBlock)
	{
		PosY = 0;
		JumpToState(State_Universal_CrouchBlock, true);
		Stance = ACT_Crouching;
	}
	else
	{
		PosY = 0;
		JumpToState(State_Universal_StandBlock, true);
		Stance = ACT_Standing;
	}
	if (Stance == ACT_Jumping)
	{
		SpeedX = -ReceivedHitCommon.AirGuardPushbackX;
		SpeedY = ReceivedHitCommon.AirGuardPushbackY;
		Gravity = ReceivedHitCommon.GuardGravity;
	}
}

void APlayerObject::HandleProximityBlock()
{
	if (!(Enemy->AttackFlags & ATK_HitActive) || !IsCorrectBlock(Enemy->HitCommon.BlockType)
		|| (CalculateDistanceBetweenPoints(DIST_DistanceX, OBJ_Self, POS_Self, OBJ_Enemy, POS_Self) > Enemy->HitCommon.
			ProximityBlockDistanceX
			|| CalculateDistanceBetweenPoints(DIST_DistanceY, OBJ_Self, POS_Self, OBJ_Enemy, POS_Self) > Enemy->
			HitCommon.ProximityBlockDistanceY))
	{
		if (PrimaryStateMachine.CurrentState->StateType == EStateType::Blockstun && StunTime == 0)
		{
			if (Stance == ACT_Standing)
			{
				JumpToState(State_Universal_StandBlockEnd);
			}
			else if (Stance == ACT_Crouching)
			{
				JumpToState(State_Universal_CrouchBlockEnd);
			}
			else
			{
				JumpToState(State_Universal_AirBlockEnd);
			}
		}
		return;
	}
	if (!(GetEnableFlags(StateMachine_Primary) & ENB_ProximityBlock))
		return;

	FInputCondition Input1;
	FInputBitmask BitmaskDownLeft;
	BitmaskDownLeft.InputFlag = INP_DownLeft;
	Input1.Sequence.Add(BitmaskDownLeft);
	Input1.Method = EInputMethod::Strict;
	Input1.bInputAllowDisable = false;
	GotoLabel(State_Label_Block_PreGuard);
	if (PosY > GroundHeight)
	{
		JumpToState(State_Universal_AirBlock, true);
		Stance = ACT_Jumping;
	}
	else if (CheckInput(Input1))
	{
		JumpToState(State_Universal_CrouchBlock, true);
		Stance = ACT_Crouching;
	}
	else
	{
		JumpToState(State_Universal_StandBlock, true);
		Stance = ACT_Standing;
	}
}

void APlayerObject::EmptyStateMachine()
{
	PrimaryStateMachine.States.Empty();
	PrimaryStateMachine.StateNames.Empty();
	PrimaryStateMachine.CurrentState = nullptr;
	for (auto& StateMachine : SubStateMachines) 
	{
		StateMachine.States.Empty();
		StateMachine.StateNames.Empty();
		StateMachine.CurrentState = nullptr;
	}
}

void APlayerObject::HandleBufferedState()
{
	if (BufferedStateName != FGameplayTag())
	{
		if (FindChainCancelOption(BufferedStateName)
			|| FindAutoComboCancelOption(BufferedStateName)
			|| FindWhiffCancelOption(BufferedStateName)
			|| CancelFlags & CNC_CancelIntoSelf) //if cancel option, allow resetting state
		{
			if (PrimaryStateMachine.ForceSetState(BufferedStateName))
			{
				GotoLabelActive = false;
				switch (PrimaryStateMachine.CurrentState->EntryStance)
				{
				case EEntryStance::Standing:
					Stance = ACT_Standing;
					break;
				case EEntryStance::Crouching:
					Stance = ACT_Crouching;
					break;
				case EEntryStance::Jumping:
					Stance = ACT_Jumping;
					break;
				default:
					break;
				}
			}
			BufferedStateName = FGameplayTag();
		}
		else
		{
			if (PrimaryStateMachine.SetState(BufferedStateName))
			{
				GotoLabelActive = false;
				switch (PrimaryStateMachine.CurrentState->EntryStance)
				{
				case EEntryStance::Standing:
					Stance = ACT_Standing;
					break;
				case EEntryStance::Crouching:
					Stance = ACT_Crouching;
					break;
				case EEntryStance::Jumping:
					Stance = ACT_Jumping;
					break;
				default:
					break;
				}
			}
			BufferedStateName = FGameplayTag();
		}
	}
}

bool APlayerObject::HandleStateCondition(EStateCondition StateCondition)
{
	ReturnReg = false;
	switch (StateCondition)
	{
	case EStateCondition::None:
		ReturnReg = true;
		break;
	case EStateCondition::AirJumpOk:
		if (CurrentAirJumpCount > 0)
			ReturnReg = true;
		break;
	case EStateCondition::AirJumpMinimumHeight:
		if (SpeedY <= 0 || PosY >= 122500)
			ReturnReg = true;
		break;
	case EStateCondition::AirDashOk:
		if (CurrentAirDashCount > 0)
			ReturnReg = true;
		break;
	case EStateCondition::AirDashMinimumHeight:
		if (PosY > AirDashMinimumHeight && SpeedY > 0)
			ReturnReg = true;
		if (PosY > 70000 && SpeedY <= 0)
			ReturnReg = true;
		break;
	case EStateCondition::IsAttacking:
		ReturnReg = AttackFlags & ATK_IsAttacking;
		break;
	case EStateCondition::HitstopCancel:
		ReturnReg = Hitstop == 1 && AttackFlags & ATK_IsAttacking;
		break;
	case EStateCondition::IsStunned:
		ReturnReg = PlayerFlags & PLF_IsStunned;
		break;
	case EStateCondition::CloseNormal:
		if (abs(PosX - Enemy->PosX) < CloseNormalRange && (PlayerFlags & PLF_ForceEnableFarNormal) == 0)
			ReturnReg = true;
		break;
	case EStateCondition::FarNormal:
		if (abs(PosX - Enemy->PosX) > CloseNormalRange || PlayerFlags & PLF_ForceEnableFarNormal)
			ReturnReg = true;
		break;
	case EStateCondition::CanTag2nd:
		if (GameState->CanTag(this, 1))
			ReturnReg = true;
		break;
	case EStateCondition::CanTag3rd:
		if (GameState->CanTag(this, 2))
			ReturnReg = true;
		break;
	case EStateCondition::MeterNotZero:
		if (GameState->BattleState.Meter[PlayerIndex] > 0)
			ReturnReg = true;
		break;
	case EStateCondition::MeterQuarterBar:
		if (GameState->BattleState.Meter[PlayerIndex] >= 2500)
			ReturnReg = true;
		break;
	case EStateCondition::MeterHalfBar:
		if (GameState->BattleState.Meter[PlayerIndex] >= 5000)
			ReturnReg = true;
		break;
	case EStateCondition::MeterOneBar:
		if (GameState->BattleState.Meter[PlayerIndex] >= 10000)
			ReturnReg = true;
		break;
	case EStateCondition::MeterTwoBars:
		if (GameState->BattleState.Meter[PlayerIndex] >= 20000)
			ReturnReg = true;
		break;
	case EStateCondition::MeterThreeBars:
		if (GameState->BattleState.Meter[PlayerIndex] >= 30000)
			ReturnReg = true;
		break;
	case EStateCondition::MeterFourBars:
		if (GameState->BattleState.Meter[PlayerIndex] >= 40000)
			ReturnReg = true;
		break;
	case EStateCondition::MeterFiveBars:
		if (GameState->BattleState.Meter[PlayerIndex] >= 50000)
			ReturnReg = true;
		break;
	case EStateCondition::PlayerReg1True:
		ReturnReg = PlayerReg1 != 0;
		break;
	case EStateCondition::PlayerReg2True:
		ReturnReg = PlayerReg2 != 0;
		break;
	case EStateCondition::PlayerReg3True:
		ReturnReg = PlayerReg3 != 0;
		break;
	case EStateCondition::PlayerReg4True:
		ReturnReg = PlayerReg4 != 0;
		break;
	case EStateCondition::PlayerReg5True:
		ReturnReg = PlayerReg5 != 0;
		break;
	case EStateCondition::PlayerReg6True:
		ReturnReg = PlayerReg6 != 0;
		break;
	case EStateCondition::PlayerReg7True:
		ReturnReg = PlayerReg7 != 0;
		break;
	case EStateCondition::PlayerReg8True:
		ReturnReg = PlayerReg8 != 0;
		break;
	case EStateCondition::PlayerReg1False:
		ReturnReg = PlayerReg1 == 0;
		break;
	case EStateCondition::PlayerReg2False:
		ReturnReg = PlayerReg2 == 0;
		break;
	case EStateCondition::PlayerReg3False:
		ReturnReg = PlayerReg3 == 0;
		break;
	case EStateCondition::PlayerReg4False:
		ReturnReg = PlayerReg4 == 0;
		break;
	case EStateCondition::PlayerReg5False:
		ReturnReg = PlayerReg5 == 0;
		break;
	case EStateCondition::PlayerReg6False:
		ReturnReg = PlayerReg6 == 0;
		break;
	case EStateCondition::PlayerReg7False:
		ReturnReg = PlayerReg7 == 0;
		break;
	case EStateCondition::PlayerReg8False:
		ReturnReg = PlayerReg8 == 0;
		break;
	default:
		ReturnReg = false;
		break;
	}
	return ReturnReg;
}

bool APlayerObject::FindChainCancelOption(const FGameplayTag Name)
{
	ReturnReg = false;
	if (AttackFlags & ATK_HasHit && AttackFlags & ATK_IsAttacking && CancelFlags & CNC_ChainCancelEnabled)
	{
		if (CheckReverseBeat(Name))
			return ReturnReg;
		for (int i = 0; i < ChainCancelOptions.Num(); i++)
		{
			if (ChainCancelOptions[i] == PrimaryStateMachine.GetStateIndex(Name) && ChainCancelOptions[i] != INDEX_NONE)
			{
				ReturnReg = true;
				CheckMovesUsedInChain(Name);
				break;
			}
		}
	}
	return ReturnReg;
}

bool APlayerObject::FindAutoComboCancelOption(const FGameplayTag Name)
{
	ReturnReg = false;
	if (AttackFlags & ATK_HasHit && CancelFlags & CNC_ChainCancelEnabled)
	{
		for (int i = 0; i < 8; i++)
		{
			if (AutoComboCancels[i] == PrimaryStateMachine.GetStateIndex(Name) && AutoComboCancels[i] != INDEX_NONE)
			{
				ReturnReg = true;
				CheckMovesUsedInChain(Name);
				break;
			}
		}
	}
	return ReturnReg;
}

bool APlayerObject::FindWhiffCancelOption(const FGameplayTag Name)
{
	ReturnReg = false;
	if (CancelFlags & CNC_WhiffCancelEnabled)
	{
		if (CheckReverseBeat(Name))
			return ReturnReg;
		for (int i = 0; i < WhiffCancelOptions.Num(); i++)
		{
			if (WhiffCancelOptions[i] == PrimaryStateMachine.GetStateIndex(Name) && WhiffCancelOptions[i] != INDEX_NONE)
			{
				ReturnReg = true;
				CheckMovesUsedInChain(Name);
				break;
			}
		}
	}
	return ReturnReg;
}

bool APlayerObject::CheckReverseBeat(const FGameplayTag Name)
{
	ReturnReg = false;
	if (!CanReverseBeat)
		return ReturnReg;

	const int32 Index = PrimaryStateMachine.GetStateIndex(Name);
	if (PrimaryStateMachine.CurrentState->StateType == EStateType::NormalAttack
		&& Index != INDEX_NONE && PrimaryStateMachine.States[Index]->StateType == EStateType::NormalAttack)
	{
		CheckMovesUsedInChain(Name);
	}
	return ReturnReg;
}

bool APlayerObject::CheckMovesUsedInChain(const FGameplayTag Name)
{
	ReturnReg = false;
	int32 Usages = 0;
	for (const int32 Index : MovesUsedInChain)
	{
		if (Index == PrimaryStateMachine.GetStateIndex(Name) && Index != INDEX_NONE)
			Usages++;
	}
	if (Usages < PrimaryStateMachine.States[PrimaryStateMachine.GetStateIndex(Name)]->MaxChain
		|| PrimaryStateMachine.States[PrimaryStateMachine.GetStateIndex(Name)]->MaxChain == -1)
		ReturnReg = true;
	return ReturnReg;
}

void APlayerObject::ThrowExe()
{
	JumpToState(ExeStateName);
	PlayerFlags &= ~PLF_ThrowActive;
}

void APlayerObject::HandleThrowCollision()
{
	if ((Enemy->InvulnFlags & INV_ThrowInvulnerable) == 0 && !Enemy->ThrowInvulnerableTimer
		&& !Enemy->ThrowResistTimer && !Enemy->CheckIsStunned()
		&& ((Enemy->PosY <= GroundHeight && PosY <= GroundHeight)
			|| (Enemy->PosY > GroundHeight && PosY > GroundHeight)))
	{
		FInputCondition Left;
		FInputBitmask BitmaskLeft;
		BitmaskLeft.InputFlag = INP_Left;
		BitmaskLeft.Lenience = 1;
		Left.Sequence.Add(BitmaskLeft);
		Left.Method = EInputMethod::Strict;
		Left.bInputAllowDisable = false;

		if (CanProximityThrow)
		{
			if (ActionTime == 0 && PrimaryStateMachine.CurrentState->StateType == EStateType::NormalAttack)
			{
				FInputCondition Right;
				FInputBitmask BitmaskRight;
				BitmaskRight.InputFlag = INP_Right;
				BitmaskRight.Lenience = 1;
				Right.Sequence.Add(BitmaskRight);
				Right.Method = EInputMethod::Strict;
				Right.bInputAllowDisable = false;

				if (CheckInput(ProximityThrowInput) && (CheckInput(Left) || CheckInput(Right)))
				{
					if (PosY <= GroundHeight)
						CallSubroutine(Subroutine_ThrowParam_Ground);
					else
						CallSubroutine(Subroutine_ThrowParam_Air);
				}
			}
			else
			{
				SetThrowActive(false);
			}
		}

		int ThrowPosX;
		if (Direction == DIR_Right)
			ThrowPosX = R + ThrowRange;
		else
			ThrowPosX = L - ThrowRange;
		if (AttackFlags & ATK_IsAttacking && PlayerFlags & PLF_ThrowActive
			&& ((PosX <= Enemy->PosX && ThrowPosX >= Enemy->L)
				|| (PosX > Enemy->PosX && ThrowPosX <= Enemy->R))
			&& T >= Enemy->B && B <= Enemy->T)
		{
			if (CheckInput(Left))
				FlipObject();
			Enemy->JumpToState(State_Universal_ThrowLock);
			Enemy->PlayerFlags |= PLF_IsThrowLock;
			Enemy->ThrowTechTimer = ThrowTechWindow;
			Enemy->AttackOwner = this;
			ThrowExe();
		}
	}
}

bool APlayerObject::CheckKaraCancel(EStateType InStateType)
{
	ReturnReg = false;
	if ((CancelFlags & CNC_EnableKaraCancel) == 0 || AttackFlags & ATK_HasHit)
	{
		return ReturnReg;
	}

	if (ActionTime >= 3)
		return ReturnReg;

	//two checks: if it's an attack, and if the given state type has a higher or equal priority to the current state
	if (InStateType == EStateType::NormalAttack && PrimaryStateMachine.CurrentState->StateType ==
		EStateType::NormalAttack)
	{
		ReturnReg = true;
	}
	if (InStateType == EStateType::SpecialAttack && PrimaryStateMachine.CurrentState->StateType >
		EStateType::NormalAttack && PrimaryStateMachine.CurrentState->StateType < EStateType::SpecialAttack)
	{
		ReturnReg = true;
	}
	if (InStateType == EStateType::SuperAttack && PrimaryStateMachine.CurrentState->StateType >
		EStateType::NormalAttack && PrimaryStateMachine.CurrentState->StateType < EStateType::SuperAttack)
	{
		ReturnReg = true;
	}

	return ReturnReg;
}

bool APlayerObject::CheckObjectPreventingState(int InObjectID)
{
	ReturnReg = false;
	if (InObjectID != 0)
	{
		for (int i = GameState->Players.Num(); i < GameState->BattleState.ActiveObjectCount; i++)
		{
			if (GameState->SortedObjects[i]->Player == this && GameState->SortedObjects[i]->ObjectID == InObjectID)
				return true;
		}
	}
	return ReturnReg;
}

void APlayerObject::HandleWallBounce()
{
	if (ReceivedHit.WallBounce.WallBounceInCornerOnly)
	{
		if (PosX - R + PosX >= GameState->BattleState.ScreenData.StageBoundsRight * 1000 || PosX - L + PosX <= GameState
			->BattleState.ScreenData.StageBoundsLeft * 1000)
		{
			if (ReceivedHit.WallBounce.WallBounceCount > 0)
			{
				ReceivedHit.GroundBounce.GroundBounceCount = 0;
				PlayerFlags &= ~PLF_TouchingWall;
				ReceivedHit.WallBounce.WallBounceCount--;
				ReceivedHit.GroundPushbackX = -1;
				ReceivedHit.AirPushbackX = SpeedX * ReceivedHit.WallBounce.WallBounceXRate / 100;
				ReceivedHit.AirPushbackY = ReceivedHit.WallBounce.WallBounceYSpeed * ReceivedHit.WallBounce.
					WallBounceYRate / 100;
				ReceivedHit.Gravity = ReceivedHit.WallBounce.WallBounceGravity;
				if (ReceivedHit.WallBounce.WallBounceUntech > 0)
					ReceivedHit.Untech = ReceivedHit.WallBounce.WallBounceUntech;
				else
					ReceivedHit.Untech = StunTime;
				ReceivedHit.Hitstop = ReceivedHit.WallBounce.WallBounceStop;
				ReceivedHit.AirPushbackXOverTime = FHitValueOverTime();
				ReceivedHit.AirPushbackYOverTime = FHitValueOverTime();
				ReceivedHit.GravityOverTime = FHitValueOverTime();
				HaltMomentum();
				BufferedStateName = State_Universal_WallBounce;

				int32 FinalHitstop = ReceivedHit.Hitstop + ReceivedHit.EnemyHitstopModifier;

				AttackOwner->Hitstop = ReceivedHit.Hitstop;
				Hitstop = FinalHitstop;
			}
		}
		return;
	}
	if (PlayerFlags & PLF_TouchingWall)
	{
		if (ReceivedHit.WallBounce.WallBounceCount > 0)
		{
			ReceivedHit.GroundBounce.GroundBounceCount = 0;
			PlayerFlags &= ~PLF_TouchingWall;
			ReceivedHit.WallBounce.WallBounceCount--;
			ReceivedHit.GroundPushbackX = -1;
			ReceivedHit.AirPushbackX = SpeedX * ReceivedHit.WallBounce.WallBounceXRate / 100;
			ReceivedHit.AirPushbackY = ReceivedHit.WallBounce.WallBounceYSpeed * ReceivedHit.WallBounce.WallBounceYRate
				/ 100;
			ReceivedHit.Gravity = ReceivedHit.WallBounce.WallBounceGravity;
			if (ReceivedHit.WallBounce.WallBounceUntech > 0)
				ReceivedHit.Untech = ReceivedHit.WallBounce.WallBounceUntech;
			else
				ReceivedHit.Untech = StunTime;
			ReceivedHit.Hitstop = ReceivedHit.WallBounce.WallBounceStop;
			ReceivedHit.AirPushbackXOverTime = FHitValueOverTime();
			ReceivedHit.AirPushbackYOverTime = FHitValueOverTime();
			ReceivedHit.GravityOverTime = FHitValueOverTime();
			HaltMomentum();
			BufferedStateName = State_Universal_WallBounce;

			int32 FinalHitstop = ReceivedHit.Hitstop + ReceivedHit.EnemyHitstopModifier;

			AttackOwner->Hitstop = ReceivedHit.Hitstop;
			Hitstop = FinalHitstop;
		}
	}
}

void APlayerObject::HandleGroundBounce()
{
	CreateCommonParticle(Particle_JumpSmoke_Land, POS_Player);
	ReceivedHit.GroundBounce.GroundBounceCount--;
	ReceivedHit.GroundPushbackX = -1;
	if (SpeedX > 0)
		ReceivedHit.AirPushbackX = -ReceivedHit.GroundBounce.GroundBounceXSpeed * ReceivedHit.GroundBounce.
			GroundBounceXRate / 100;
	else
		ReceivedHit.AirPushbackX = ReceivedHit.GroundBounce.GroundBounceXSpeed * ReceivedHit.GroundBounce.
			GroundBounceXRate / 100;
	ReceivedHit.AirPushbackY = -SpeedY * ReceivedHit.GroundBounce.GroundBounceYRate / 100;
	ReceivedHit.Gravity = ReceivedHit.GroundBounce.GroundBounceGravity;
	if (ReceivedHit.GroundBounce.GroundBounceUntech > 0)
		ReceivedHit.Untech = ReceivedHit.GroundBounce.GroundBounceUntech;
	else
		ReceivedHit.Untech = StunTime;
	ReceivedHit.Hitstop = ReceivedHit.GroundBounce.GroundBounceStop;
	ReceivedHit.GroundHitAction = HACT_AirFaceUp;
	EnableCancelIntoSelf(true);
	PosY = GroundHeight + 1;
	BufferedStateName = State_Universal_Launch_B;

	int32 FinalHitstop = ReceivedHit.Hitstop + ReceivedHit.EnemyHitstopModifier;

	AttackOwner->Hitstop = ReceivedHit.Hitstop;
	Hitstop = FinalHitstop;
}

void APlayerObject::SetComponentVisibility() const
{
	TInlineComponentArray<UPrimitiveComponent*> Components;
	GetComponents(Components);
	for (int i = 0; i < Components.Num(); i++)
	{
		UPrimitiveComponent* Component = Components[i];
		Component->SetVisibility(ComponentVisible[i]);
	}
}

void APlayerObject::UpdateVisuals()
{
	Super::UpdateVisuals();

	for (const auto& LinkActor : StoredLinkActors)
	{
		LinkActor.StoredActor->SetActorHiddenInGame(!LinkActor.bIsActive);
	}
	SetComponentVisibility();
}

void APlayerObject::AddState(FGameplayTag Name, UState* State, FGameplayTag StateMachineName)
{
	auto& StateMachine = GetStateMachine(StateMachineName);
	
	StateMachine.Parent = this;
	StateMachine.AddState(Name, State);
}

void APlayerObject::AddObjectState(FGameplayTag Name, UState* State, bool IsCommon)
{
	State->Parent = this;
	if (IsCommon)
	{
		CommonObjectStates.Add(State);
		CommonObjectStateNames.Add(Name);
	}
	else
	{
		ObjectStates.Add(State);
		ObjectStateNames.Add(Name);
	}
}

void APlayerObject::AddSubroutine(FGameplayTag Name, USubroutine* Subroutine, bool IsCommon)
{
	Subroutine->Parent = this;
	if (IsCommon)
	{
		CommonSubroutines.Add(Subroutine);
		CommonSubroutineNames.Add(Name);
	}
	else
	{
		Subroutines.Add(Subroutine);
		SubroutineNames.Add(Name);
	}
}

void APlayerObject::SetHealth(int Value)
{
	CurrentHealth = Value;
}

void APlayerObject::AddHealth(int Value)
{
	CurrentHealth += Value;
}

void APlayerObject::SetRecoverableHealth(int Value)
{
	RecoverableHealth = Value;
}

void APlayerObject::AddRecoverableHealth(int Value)
{
	RecoverableHealth += Value;
}

void APlayerObject::RecoverHealth(int Value)
{
	if (Value <= RecoverableHealth)
	{
		CurrentHealth += Value;
		RecoverableHealth -= Value;
	}
	else
	{
		CurrentHealth += RecoverableHealth;
		RecoverableHealth = 0;
	}
}

void APlayerObject::UseMeter(int Use)
{
	if (!GameState) return;
	GameState->BattleState.Meter[PlayerIndex] -= Use;
}

void APlayerObject::AddMeter(int Meter)
{
	if (!GameState) return;
	if (MeterCooldownTimer > 0)
		Meter /= 10;
	GameState->BattleState.Meter[PlayerIndex] += Meter;
}

void APlayerObject::SetMeterCooldownTimer(int Timer)
{
	MeterCooldownTimer = Timer;
}

int32 APlayerObject::GetGauge(int32 Index) const
{
	if (!GameState) return 0;
	return GameState->GetGauge(PlayerIndex == 0, Index);
}

void APlayerObject::SetGauge(int32 Index, int Value)
{
	if (!GameState) return;
	GameState->SetGauge(PlayerIndex == 0, Index, Value);
}

void APlayerObject::UseGauge(int32 Index, int Use)
{
	if (!GameState) return;
	GameState->UseGauge(PlayerIndex == 0, Index, Use);
}

void APlayerObject::SetStance(EActionStance InStance)
{
	Stance = InStance;
}

bool APlayerObject::JumpToState(FGameplayTag NewName, bool IsLabel)
{
	if (!GameState && !CharaSelectGameState) return false;
	GotoLabelActive = IsLabel;
	if (PrimaryStateMachine.ForceSetState(NewName) && PrimaryStateMachine.CurrentState != nullptr)
	{
		switch (PrimaryStateMachine.CurrentState->EntryStance)
		{
		case EEntryStance::Standing:
			Stance = ACT_Standing;
			break;
		case EEntryStance::Crouching:
			Stance = ACT_Crouching;
			break;
		case EEntryStance::Jumping:
			Stance = ACT_Jumping;
			break;
		default:
			break;
		}
		return true;
	}
	return false;
}

bool APlayerObject::JumpToStateByClass(TSubclassOf<UState> Class, bool IsLabel)
{
	if (!GameState && !CharaSelectGameState) return false;
	GotoLabelActive = IsLabel;
	if (PrimaryStateMachine.ForceSetState(Class) && PrimaryStateMachine.CurrentState != nullptr)
	{
		switch (PrimaryStateMachine.CurrentState->EntryStance)
		{
		case EEntryStance::Standing:
			Stance = ACT_Standing;
			break;
		case EEntryStance::Crouching:
			Stance = ACT_Crouching;
			break;
		case EEntryStance::Jumping:
			Stance = ACT_Jumping;
			break;
		default:
			break;
		}
		return true;
	}
	return false;
}

FGameplayTag APlayerObject::GetCurrentStateName(FGameplayTag StateMachineName)
{
	if (!GetStateMachine(StateMachineName).CurrentState) return FGameplayTag::EmptyTag;
	return GetStateMachine(StateMachineName).CurrentState->Name;
}

FGameplayTag APlayerObject::GetLastStateName() const
{
	return LastStateName;
}

FGameplayTag APlayerObject::GetStateEntryName() const
{
	return StateEntryName;
}

FStateMachine& APlayerObject::GetStateMachine(FGameplayTag StateMachineName)
{
	for (auto& StateMachine : SubStateMachines)
	{
		if (StateMachineName == StateMachine.StateMachineName)
		{
			return StateMachine;
		}
	}
	
	return PrimaryStateMachine;
}

bool APlayerObject::CheckStateEnabled(EStateType StateType, FGameplayTag CustomStateType, FGameplayTag StateMachineName)
{
	ReturnReg = false;
	switch (StateType)
	{
	case EStateType::Standing:
		if (GetEnableFlags(StateMachineName) & ENB_Standing)
			ReturnReg = true;
		break;
	case EStateType::Crouching:
		if (GetEnableFlags(StateMachineName) & ENB_Crouching)
			ReturnReg = true;
		break;
	case EStateType::NeutralJump:
	case EStateType::ForwardJump:
	case EStateType::BackwardJump:
		if (GetEnableFlags(StateMachineName) & ENB_Jumping || (CancelFlags & CNC_JumpCancel && AttackFlags & ATK_HasHit && AttackFlags &
			ATK_IsAttacking))
			ReturnReg = true;
		break;
	case EStateType::ForwardWalk:
		if (GetEnableFlags(StateMachineName) & ENB_ForwardWalk)
			ReturnReg = true;
		break;
	case EStateType::BackwardWalk:
		if (GetEnableFlags(StateMachineName) & ENB_BackWalk)
			ReturnReg = true;
		break;
	case EStateType::ForwardDash:
		if (GetEnableFlags(StateMachineName) & ENB_ForwardDash)
			ReturnReg = true;
		break;
	case EStateType::BackwardDash:
		if (GetEnableFlags(StateMachineName) & ENB_BackDash)
			ReturnReg = true;
		break;
	case EStateType::ForwardAirDash:
		if (GetEnableFlags(StateMachineName) & ENB_ForwardAirDash || (CancelFlags & CNC_FAirDashCancel && AttackFlags & ATK_HasHit &&
			AttackFlags & ATK_IsAttacking))
			ReturnReg = true;
		break;
	case EStateType::BackwardAirDash:
		if (GetEnableFlags(StateMachineName) & ENB_BackAirDash || (CancelFlags & CNC_BAirDashCancel && AttackFlags & ATK_HasHit &&
			AttackFlags & ATK_IsAttacking))
			ReturnReg = true;
		break;
	case EStateType::NormalAttack:
		if (GetEnableFlags(StateMachineName) & ENB_NormalAttack)
			ReturnReg = true;
		break;
	case EStateType::SpecialAttack:
		if (GetEnableFlags(StateMachineName) & ENB_SpecialAttack || (CancelFlags & CNC_SpecialCancel && AttackFlags & ATK_HasHit &&
			AttackFlags & ATK_IsAttacking))
			ReturnReg = true;
		break;
	case EStateType::SuperAttack:
		if (GetEnableFlags(StateMachineName) & ENB_SuperAttack || (CancelFlags & CNC_SuperCancel && AttackFlags & ATK_HasHit && AttackFlags &
			ATK_IsAttacking))
			ReturnReg = true;
		break;
	case EStateType::Tech:
		if (GetEnableFlags(StateMachineName) & ENB_Tech && CheckIsStunned())
			ReturnReg = true;
		break;
	case EStateType::Burst:
		if (GetEnableFlags(StateMachineName) & ENB_Burst && (Enemy->Player->PlayerFlags & PLF_LockOpponentBurst) == 0
			&& (PlayerFlags & PLF_IsDead) == 0)
			ReturnReg = true;
		break;
	case EStateType::Tag:
		if (GetEnableFlags(StateMachineName) & ENB_Tag)
			ReturnReg = true;
		break;
	case EStateType::Assist:
		if (GetEnableFlags(StateMachineName) & ENB_Assist)
			ReturnReg = true;
		break;
	case EStateType::Custom:
		if (GetStateMachine(StateMachineName).EnabledCustomStateTypes.Contains(CustomStateType))
			ReturnReg = true;
		break;
	default:
		ReturnReg = false;
	}
	return ReturnReg;
}

void APlayerObject::OnStateChange()
{
	if (!GameState) return;
	
	CallSubroutine(Subroutine_Cmn_OnStateChange);
	CallSubroutine(Subroutine_OnStateChange);

	// Deactivate all objects that need to be destroyed on state change.
	for (int i = GameState->Players.Num(); i < GameState->BattleState.ActiveObjectCount; i++)
	{
		if (GameState->SortedObjects[i]->Player == this && GameState->SortedObjects[i]->MiscFlags &
			MISC_DeactivateOnStateChange)
			GameState->SortedObjects[i]->DeactivateObject();
	}

	DisableLastInput();
	DisableAll(StateMachine_Primary);

	// Reset flags
	CancelFlags = CNC_EnableKaraCancel | CNC_ChainCancelEnabled;
	PlayerFlags &= ~PLF_ThrowActive;
	PlayerFlags &= ~PLF_HitgrabActive;
	PlayerFlags &= ~PLF_DeathCamOverride;
	PlayerFlags &= ~PLF_LockOpponentBurst;
	PlayerFlags &= ~PLF_ForceEnableFarNormal;
	PlayerFlags |= PLF_DefaultLandingAction;
	AttackFlags = 0;
	MiscFlags = 0;
	MiscFlags |= MISC_PushCollisionActive;
	MiscFlags |= MISC_WallCollisionActive;
	MiscFlags |= MISC_FloorCollisionActive;
	MiscFlags |= MISC_InertiaEnable;
	InvulnFlags = 0;
	GetStateMachine(StateMachine_Primary).EnableFlags = 0;

	// Reset offset, as the offset should be applied
	PrevOffsetX = 0;
	PrevOffsetY = 0;
	NextOffsetX = 0;
	NextOffsetY = 0;

	PosZ = 0;

	// Reset speed modifiers
	Gravity = JumpGravity;
	SpeedXRate = 100;
	SpeedXRatePerFrame = 100;
	SpeedYRate = 100;
	SpeedYRatePerFrame = 100;

	// Reset action data
	ActionTime = 0;
	AnimFrame = 0;
	BlendAnimFrame = 0;
	CelIndex = 0;
	TimeUntilNextCel = 0;
	for (auto& Handler : EventHandlers)
		Handler = FEventHandler();

	// Reset action registers
	ActionReg1 = 0;
	ActionReg2 = 0;
	ActionReg3 = 0;
	ActionReg4 = 0;
	ActionReg5 = 0;
	ActionReg6 = 0;
	ActionReg7 = 0;
	ActionReg8 = 0;

	// Miscellaneous resets
	PushWidthExtend = 0;
	FlipInputs = false;
	for (int32& CancelOption : AutoComboCancels)
	{
		CancelOption = -1;
	}
	GetStateMachine(StateMachine_Primary).EnabledCustomStateTypes.Empty();
	for (auto& StateMachine : SubStateMachines)
	{
		StateMachine.EnabledCustomStateTypes.Empty();
	}
	ChainCancelOptions.Empty();
	WhiffCancelOptions.Empty();
	HitCommon = FHitDataCommon();
	NormalHit = FHitData();
	CounterHit = FHitData();
	CelName = FGameplayTag();
	BlendCelName = FGameplayTag();
	LastStateName = GetCurrentStateName(StateMachine_Primary);
	HomingParams = FHomingParams();
}

void APlayerObject::PostStateChange()
{
	MovesUsedInCombo.Add(PrimaryStateMachine.GetStateIndex(GetCurrentStateName(StateMachine_Primary)));
	if (PrimaryStateMachine.CurrentState->StateType >= EStateType::NormalAttack
		&& PrimaryStateMachine.CurrentState->StateType <= EStateType::SuperAttack)
	{
		const FGameplayTag MoveChainName = PrimaryStateMachine.CurrentState->ShareChainName != FGameplayTag::EmptyTag
			                                   ? PrimaryStateMachine.CurrentState->ShareChainName
			                                   : PrimaryStateMachine.CurrentState->Name;
		MovesUsedInChain.Add(PrimaryStateMachine.GetStateIndex(MoveChainName));
	}
	else
	{
		MovesUsedInChain.Empty();
	}
	PrimaryStateMachine.CurrentState->ResetToCDO();
}

void APlayerObject::RoundInit(bool ResetHealth)
{
	CallSubroutine(Subroutine_Cmn_RoundInit);
	CallSubroutine(Subroutine_RoundInit);
	if (PlayerIndex == 0)
	{
		PosX = -GameState->BattleState.RoundStartPos;
	}
	else
	{
		PosX = GameState->BattleState.RoundStartPos;
	}
	PosY = 0;
	PosZ = 0;
	PrevPosX = 0;
	PrevPosY = 0;
	PrevPosZ = 0;
	SpeedX = 0;
	SpeedY = 0;
	SpeedZ = 0;
	Gravity = JumpGravity;
	Inertia = 0;
	Pushback = 0;
	ActionTime = 0;
	PushHeight = 0;
	PushHeightLow = 0;
	PushWidth = 0;
	PushWidthExtend = 0;
	Hitstop = 0;
	L = 0;
	R = 0;
	T = 0;
	B = 0;
	HitCommon = FHitDataCommon();
	NormalHit = FHitData();
	CounterHit = FHitData();
	ReceivedHitCommon = FHitDataCommon();
	ReceivedHit = FHitData();
	AttackFlags = 0;
	StunTime = 0;
	StunTimeMax = 0;
	Hitstop = 0;
	MiscFlags = 0;
	MiscFlags |= MISC_PushCollisionActive;
	MiscFlags |= MISC_WallCollisionActive;
	MiscFlags |= MISC_FloorCollisionActive;
	MiscFlags |= MISC_InertiaEnable;
	Direction = DIR_Right;
	SpeedXRate = 100;
	SpeedXRatePerFrame = 100;
	SpeedYRate = 100;
	SpeedYRatePerFrame = 100;
	SpeedZRate = 100;
	SpeedZRatePerFrame = 100;
	GroundHeight = 0;
	ReturnReg = false;
	ActionReg1 = 0;
	ActionReg2 = 0;
	ActionReg3 = 0;
	ActionReg4 = 0;
	ActionReg5 = 0;
	ActionReg6 = 0;
	ActionReg7 = 0;
	ActionReg8 = 0;
	ObjectReg1 = 0;
	ObjectReg2 = 0;
	ObjectReg3 = 0;
	ObjectReg4 = 0;
	ObjectReg5 = 0;
	ObjectReg6 = 0;
	ObjectReg7 = 0;
	ObjectReg8 = 0;
	SubroutineReg1 = 0;
	SubroutineReg2 = 0;
	SubroutineReg3 = 0;
	SubroutineReg4 = 0;
	SubroutineReturnVal1 = 0;
	SubroutineReturnVal2 = 0;
	SubroutineReturnVal3 = 0;
	SubroutineReturnVal4 = 0;
	IsPlayer = true;
	AttackTarget = nullptr;
	AttackOwner = nullptr;
	StopLinkObj = nullptr;
	PositionLinkObj = nullptr;
	MaterialLinkObj = nullptr;
	Timer0 = 0;
	Timer1 = 0;
	HomingParams = FHomingParams();
	CelName = FGameplayTag();
	BlendCelName = FGameplayTag();
	AnimFrame = 0;
	BlendAnimFrame = 0;
	FrameBlendPosition = 0;
	CelIndex = 0;
	TimeUntilNextCel = 0;
	for (auto& Handler : EventHandlers)
		Handler = FEventHandler();
	SocketName = FName();
	SocketObj = OBJ_Self;
	SocketOffset = FVector::ZeroVector;
	ObjectScale = FVector::OneVector;
	AddColor = FLinearColor(0, 0, 0, 1);
	MulColor = FLinearColor(1, 1, 1, 1);
	AddFadeColor = FLinearColor(0, 0, 0, 1);
	MulFadeColor = FLinearColor(1, 1, 1, 1);
	AddFadeSpeed = 0;
	MulFadeSpeed = 0;
	ObjectsToIgnoreHitsFrom.Empty();
	HitPosX = 0;
	HitPosY = 0;
	for (auto& Box : Boxes)
	{
		Box = FCollisionBox();
	}
	PlayerReg1 = 0;
	PlayerReg2 = 0;
	PlayerReg3 = 0;
	PlayerReg4 = 0;
	PlayerReg5 = 0;
	PlayerReg6 = 0;
	PlayerReg7 = 0;
	PlayerReg8 = 0;
	CmnPlayerReg1 = 0;
	CmnPlayerReg2 = 0;
	CmnPlayerReg3 = 0;
	CmnPlayerReg4 = 0;
	CmnPlayerReg5 = 0;
	CmnPlayerReg6 = 0;
	CmnPlayerReg7 = 0;
	CmnPlayerReg8 = 0;
	IntroEndFlag = false;
	RoundEndFlag = false;
	SubroutineReg1 = 0;
	SubroutineReg2 = 0;
	SubroutineReg3 = 0;
	SubroutineReg4 = 0;
	Inputs = 0;
	FlipInputs = false;
	Stance = ACT_Standing;
	if (ResetHealth)
	{
		CurrentHealth = MaxHealth;
		RecoverableHealth = 0;
	}
	TotalProration = 10000;
	ComboCounter = 0;
	ComboTimer = 0;
	ThrowTechWindow = 6;
	InvulnFlags = 0;
	PlayerFlags &= ~PLF_IsDead;
	PlayerFlags &= ~PLF_ThrowActive;
	PlayerFlags &= ~PLF_HitgrabActive;
	PlayerFlags &= ~PLF_IsStunned;
	PlayerFlags &= ~PLF_IsThrowLock;
	PlayerFlags &= ~PLF_DeathCamOverride;
	PlayerFlags &= ~PLF_IsKnockedDown;
	PlayerFlags &= ~PLF_RoundWinInputLock;
	PlayerFlags &= ~PLF_LockOpponentBurst;
	PlayerFlags &= ~PLF_ForceEnableFarNormal;
	PlayerFlags |= PLF_DefaultLandingAction;
	StrikeInvulnerableTimer = 0;
	ThrowInvulnerableTimer = 0;
	ThrowResistTimer = 0;
	for (auto& Gauge : ExtraGauges)
		Gauge.Value = Gauge.InitialValue;
	AirDashTimer = 0;
	OTGCount = 0;
	RoundWinTimer = 300;
	for (auto& StoredObj : StoredBattleObjects)
		StoredObj = nullptr;
	CurrentAirJumpCount = 0;
	CurrentAirDashCount = 0;
	AirDashTimerMax = 0;
	CancelFlags = 0;
	GetStateMachine(StateMachine_Primary).EnableFlags = 0;
	for (auto& StateMachine : SubStateMachines)
	{
		if (!StateMachine.States.IsEmpty()) 
			StateMachine.CurrentState = StateMachine.States[0];
		StateMachine.EnableFlags = 0;
	}
	AirDashNoAttackTime = 0;
	InstantBlockLockoutTimer = 0;
	MeterCooldownTimer = 0;
	for (auto& LinkActor : StoredLinkActors)
	{
		LinkActor.bIsActive = false;
		LinkActor.StoredActor->SetActorHiddenInGame(true);
	}
	for (int32& CancelOption : AutoComboCancels)
	{
		CancelOption = -1;
	}
	GetStateMachine(StateMachine_Primary).EnabledCustomStateTypes.Empty();
	for (auto& StateMachine : SubStateMachines)
	{
		StateMachine.EnabledCustomStateTypes.Empty();
	}
	ChainCancelOptions.Empty();
	WhiffCancelOptions.Empty();
	MovesUsedInCombo.Empty();
	LastStateName = FGameplayTag();
	ExeStateName = FGameplayTag();
	BufferedStateName = FGameplayTag();
	WallTouchTimer = 0;
	GameState->BattleState.MaxMeter[PlayerIndex] = MaxMeter;
	SetDefaultComponentVisibility();
	if (PlayerIndex == 1)
	{
		SetFacing(DIR_Left);
	}
	RoundInit_BP();
}

void APlayerObject::DisableLastInput()
{
	StoredInputBuffer.InputDisabled[InputBufferSize - 1] = StoredInputBuffer.InputBufferInternal[InputBufferSize - 1];
}

void APlayerObject::SaveForRollbackPlayer(unsigned char* Buffer) const
{
	FMemory::Memcpy(Buffer, &PlayerSync, SizeOfPlayerObject);
}

TArray<uint8> APlayerObject::SaveForRollbackBP()
{
	TArray<uint8> SaveData;
	FObjectWriter Writer(SaveData);
	Writer.ArIsSaveGame = true;
	GetClass()->SerializeBin(Writer, this);
	return SaveData;
}

void APlayerObject::LoadForRollbackPlayer(const unsigned char* Buffer)
{
	FMemory::Memcpy(&PlayerSync, Buffer, SizeOfPlayerObject);
}

void APlayerObject::LoadForRollbackBP(TArray<uint8> InBytes)
{
	FObjectReader Reader(InBytes);
	Reader.ArIsSaveGame = true;
	GetClass()->SerializeBin(Reader, this);
}

void APlayerObject::LogForSyncTestFile(std::ofstream& file)
{
	Super::LogForSyncTestFile(file);
	if (file)
	{
		file << "PlayerObject:\n";
		file << "\tEnableFlags: " << GetStateMachine(StateMachine_Primary).EnableFlags << std::endl;
		file << "\tCurrentAirJumpCount: " << CurrentAirJumpCount << std::endl;
		file << "\tCurrentAirDashCount: " << CurrentAirDashCount << std::endl;
		file << "\tAirDashTimer: " << AirDashTimer << std::endl;
		file << "\tAirDashTimerMax: " << AirDashTimerMax << std::endl;
		file << "\tCurrentHealth: " << CurrentHealth << std::endl;
		file << "\tCancelFlags: " << CancelFlags << std::endl;
		file << "\tPlayerFlags: " << PlayerFlags << std::endl;
		file << "\tInputs: " << StoredInputBuffer.InputBufferInternal[InputBufferSize - 1] << std::endl;
		file << "\tStance: " << Stance.GetValue() << std::endl;
	}
}

void APlayerObject::EnableState(int32 EnableType, FGameplayTag StateMachineName)
{
	GetStateMachine(StateMachineName).EnableFlags |= EnableType;
}

void APlayerObject::DisableState(int32 EnableType, FGameplayTag StateMachineName)
{
	GetStateMachine(StateMachineName).EnableFlags = GetStateMachine(StateMachineName).EnableFlags & ~EnableType;
}

int32 APlayerObject::GetEnableFlags(FGameplayTag StateMachineName)
{
	return GetStateMachine(StateMachineName).EnableFlags;
}

void APlayerObject::EnableCustomState(FGameplayTag CustomStateType, FGameplayTag StateMachineName)
{
	GetStateMachine(StateMachineName).EnabledCustomStateTypes.AddUnique(CustomStateType);
}

void APlayerObject::DisableCustomState(FGameplayTag CustomStateType, FGameplayTag StateMachineName)
{
	GetStateMachine(StateMachineName).EnabledCustomStateTypes.Remove(CustomStateType);
}

void APlayerObject::EnableAttacks()
{
	EnableState(ENB_NormalAttack, StateMachine_Primary);
	EnableState(ENB_SpecialAttack, StateMachine_Primary);
	EnableState(ENB_SuperAttack, StateMachine_Primary);
}

void APlayerObject::EnableCancelIntoSelf(bool Enable)
{
	if (Enable)
	{
		CancelFlags |= CNC_CancelIntoSelf;
	}
	else
	{
		CancelFlags &= ~CNC_CancelIntoSelf;
	}
}

void APlayerObject::EnableAll(FGameplayTag StateMachineName)
{
	EnableState(ENB_Standing, StateMachineName);
	EnableState(ENB_Crouching, StateMachineName);
	EnableState(ENB_Jumping, StateMachineName);
	EnableState(ENB_ForwardWalk, StateMachineName);
	EnableState(ENB_BackWalk, StateMachineName);
	EnableState(ENB_ForwardDash, StateMachineName);
	EnableState(ENB_BackDash, StateMachineName);
	EnableState(ENB_ForwardAirDash, StateMachineName);
	EnableState(ENB_BackAirDash, StateMachineName);
	EnableState(ENB_NormalAttack, StateMachineName);
	EnableState(ENB_SpecialAttack, StateMachineName);
	EnableState(ENB_SuperAttack, StateMachineName);
	EnableState(ENB_Block, StateMachineName);
	EnableState(ENB_ProximityBlock, StateMachineName);
	EnableState(ENB_Tech, StateMachineName);
	EnableState(ENB_Burst, StateMachineName);
	EnableState(ENB_Tag, StateMachineName);
	EnableState(ENB_Assist, StateMachineName);
}

void APlayerObject::DisableAll(FGameplayTag StateMachineName)
{
	DisableState(ENB_Standing, StateMachineName);
	DisableState(ENB_Crouching, StateMachineName);
	DisableState(ENB_Jumping, StateMachineName);
	DisableState(ENB_ForwardWalk, StateMachineName);
	DisableState(ENB_BackWalk, StateMachineName);
	DisableState(ENB_ForwardDash, StateMachineName);
	DisableState(ENB_BackDash, StateMachineName);
	DisableState(ENB_ForwardAirDash, StateMachineName);
	DisableState(ENB_BackAirDash, StateMachineName);
	DisableState(ENB_NormalAttack, StateMachineName);
	DisableState(ENB_SpecialAttack, StateMachineName);
	DisableState(ENB_SuperAttack, StateMachineName);
	DisableState(ENB_Block, StateMachineName);
	DisableState(ENB_ProximityBlock, StateMachineName);
	DisableState(ENB_Tech, StateMachineName);
	DisableState(ENB_Burst, StateMachineName);
	DisableState(ENB_Tag, StateMachineName);
	DisableState(ENB_Assist, StateMachineName);}

bool APlayerObject::CheckInput(const FInputCondition& Input)
{
	ReturnReg = StoredInputBuffer.CheckInputCondition(Input);
	return ReturnReg;
}

bool APlayerObject::CheckIsAttacking() const
{
	return AttackFlags & ATK_IsAttacking;
}

bool APlayerObject::CheckIsStunned() const
{
	return PlayerFlags & PLF_IsStunned || PlayerFlags & PLF_IsThrowLock;
}

void APlayerObject::AddAirJump(int32 NewAirJump)
{
	CurrentAirJumpCount += NewAirJump;
}

void APlayerObject::AddAirDash(int32 NewAirDash)
{
	CurrentAirDashCount += NewAirDash;
}

void APlayerObject::SetAirDashTimer(bool IsForward)
{
	if (IsForward)
		AirDashTimer = FAirDashTime + 1;
	else
		AirDashTimer = BAirDashTime + 1;
}

void APlayerObject::SetAirDashNoAttackTimer(bool IsForward)
{
	if (IsForward)
		AirDashNoAttackTime = FAirDashNoAttackTime + 1;
	else
		AirDashNoAttackTime = BAirDashNoAttackTime + 1;
}

void APlayerObject::AddChainCancelOption(FGameplayTag Option)
{
	ChainCancelOptions.AddUnique(PrimaryStateMachine.GetStateIndex(Option));
}

void APlayerObject::AddAutoComboCancel(FGameplayTag Option, EInputFlags Button)
{
	int32 Index;
	switch (Button)
	{
	case INP_A:
		Index = 0;
		break;
	case INP_B:
		Index = 1;
		break;
	case INP_C:
		Index = 2;
		break;
	case INP_D:
		Index = 3;
		break;
	case INP_E:
		Index = 4;
		break;
	case INP_F:
		Index = 5;
		break;
	case INP_G:
		Index = 6;
		break;
	case INP_H:
		Index = 7;
		break;
	default: return;
	}

	AutoComboCancels[Index] = PrimaryStateMachine.GetStateIndex(Option);
}

void APlayerObject::AddWhiffCancelOption(FGameplayTag Option)
{
	WhiffCancelOptions.AddUnique(PrimaryStateMachine.GetStateIndex(Option));
}

void APlayerObject::RemoveChainCancelOption(FGameplayTag Option)
{
	ChainCancelOptions.Remove(PrimaryStateMachine.GetStateIndex(Option));
}

void APlayerObject::RemoveAutoComboCancel(EInputFlags Button)
{
	int32 Index;
	switch (Button)
	{
	case INP_A:
		Index = 0;
		break;
	case INP_B:
		Index = 1;
		break;
	case INP_C:
		Index = 2;
		break;
	case INP_D:
		Index = 3;
		break;
	case INP_E:
		Index = 4;
		break;
	case INP_F:
		Index = 5;
		break;
	case INP_G:
		Index = 6;
		break;
	case INP_H:
		Index = 7;
		break;
	default: return;
	}

	AutoComboCancels[Index] = -1;
}

void APlayerObject::RemoveWhiffCancelOption(FGameplayTag Option)
{
	WhiffCancelOptions.Remove(PrimaryStateMachine.GetStateIndex(Option));
}

void APlayerObject::EnableChainCancel(bool Enable)
{
	if (Enable)
	{
		CancelFlags |= CNC_ChainCancelEnabled;
	}
	else
	{
		CancelFlags &= ~CNC_ChainCancelEnabled;
	}
}

void APlayerObject::EnableWhiffCancel(bool Enable)
{
	if (Enable)
	{
		CancelFlags |= CNC_WhiffCancelEnabled;
	}
	else
	{
		CancelFlags &= ~CNC_WhiffCancelEnabled;
	}
}

void APlayerObject::EnableJumpCancel(bool Enable)
{
	if (Enable)
	{
		CancelFlags |= CNC_JumpCancel;
	}
	else
	{
		CancelFlags &= ~CNC_JumpCancel;
	}
}

void APlayerObject::EnableSpecialCancel(bool Enable)
{
	if (Enable)
	{
		CancelFlags |= CNC_SpecialCancel;
		CancelFlags |= CNC_SuperCancel;
	}
	else
	{
		CancelFlags &= ~CNC_SpecialCancel;
		CancelFlags &= ~CNC_SuperCancel;
	}
}

void APlayerObject::EnableSuperCancel(bool Enable)
{
	if (Enable)
	{
		CancelFlags |= CNC_SuperCancel;
	}
	else
	{
		CancelFlags &= ~CNC_SuperCancel;
	}
}

void APlayerObject::EnableForwardAirdashCancel(bool Enable)
{
	if (Enable)
	{
		CancelFlags |= CNC_FAirDashCancel;
	}
	else
	{
		CancelFlags &= ~CNC_FAirDashCancel;
	}
}

void APlayerObject::SetDefaultLandingAction(bool Enable)
{
	if (Enable)
	{
		PlayerFlags |= PLF_DefaultLandingAction;
	}
	else
	{
		PlayerFlags &= ~PLF_DefaultLandingAction;
	}
}

bool APlayerObject::IsInvulnerable() const
{
	if (IsInvulnerable_BP()) return true;
	
	return InvulnFlags & INV_StrikeInvulnerable || StrikeInvulnerableTimer || (Enemy->AttackFlags & ATK_AttackHeadAttribute
		&& InvulnFlags & INV_HeadInvulnerable) || (Enemy->AttackFlags & ATK_AttackProjectileAttribute && InvulnFlags &
		INV_ProjectileInvulnerable);
}

void APlayerObject::SetStrikeInvulnerable(bool Invulnerable)
{
	if (Invulnerable)
	{
		InvulnFlags |= INV_StrikeInvulnerable;
	}
	else
	{
		InvulnFlags &= ~INV_StrikeInvulnerable;
	}
}

void APlayerObject::SetThrowInvulnerable(bool Invulnerable)
{
	if (Invulnerable)
	{
		InvulnFlags |= INV_ThrowInvulnerable;
	}
	else
	{
		InvulnFlags &= ~INV_ThrowInvulnerable;
	}
}

void APlayerObject::SetHeadInvulnerable(bool Invulnerable)
{
	if (Invulnerable)
	{
		InvulnFlags |= INV_HeadInvulnerable;
	}
	else
	{
		InvulnFlags &= ~INV_HeadInvulnerable;
	}
}

void APlayerObject::SetProjectileInvulnerable(bool Invulnerable)
{
	if (Invulnerable)
	{
		InvulnFlags |= INV_ProjectileInvulnerable;
	}
	else
	{
		InvulnFlags &= ~INV_ProjectileInvulnerable;
	}
}

void APlayerObject::SetStrikeInvulnerableForTime(int32 Timer)
{
	StrikeInvulnerableTimer = Timer;
}

void APlayerObject::SetThrowInvulnerableForTime(int32 Timer)
{
	ThrowInvulnerableTimer = Timer;
}

void APlayerObject::SetThrowResistForTime(int32 Timer)
{
	ThrowResistTimer = Timer;
}

void APlayerObject::SetStunTime(int32 NewTime)
{
	StunTime = NewTime;
}
