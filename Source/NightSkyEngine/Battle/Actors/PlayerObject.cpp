// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerObject.h"

#include "NightSkyGameState.h"
#include "NightSkyEngine/Battle/Subroutine.h"
#include "NightSkyEngine/Miscellaneous/NightSkyGameInstance.h"
#include "Serialization/ObjectReader.h"
#include "Serialization/ObjectWriter.h"

APlayerObject::APlayerObject()
{
	Player = this;
	StoredStateMachine.Parent = this;
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
}

void APlayerObject::BeginPlay()
{
	Super::BeginPlay();
	InitPlayer();
}

void APlayerObject::InitPlayer()
{
	CurrentHealth = MaxHealth;
	EnableFlip(true);
	InitBP();
}

void APlayerObject::HandleStateMachine(bool Buffer)
{
	for (int i = StoredStateMachine.States.Num() - 1; i >= 0; i--)
	{
        if (!((CheckStateEnabled(StoredStateMachine.States[i]->StateType) && !StoredStateMachine.States[i]->IsFollowupState)
            || FindChainCancelOption(FName(StoredStateMachine.States[i]->Name))
            || FindAutoComboCancelOption(FName(StoredStateMachine.States[i]->Name))
            || FindWhiffCancelOption(FName(StoredStateMachine.States[i]->Name))
            || (CheckKaraCancel(StoredStateMachine.States[i]->StateType) && 
				CheckMovesUsedInCombo(FName(StoredStateMachine.States[i]->Name))
				&& !StoredStateMachine.States[i]->IsFollowupState
            	&& i > StoredStateMachine.GetStateIndex(FName(GetCurrentStateName()))) 
            )) //check if the state is enabled, continue if not
        {
            continue;
        }
		if (CheckObjectPreventingState(StoredStateMachine.States[i]->ObjectID)) //check if an object is preventing state entry, continue if so
		{
			continue;
		}
        //check current character state against entry state condition, continue if not entry state
		if (!StoredStateMachine.CheckStateStanceCondition(StoredStateMachine.States[i]->EntryStance, Stance))
        {
            continue;
        }
		if (StoredStateMachine.States[i]->StateConditions.Num() != 0) //only check state conditions if there are any
		{
			for (int j = 0; j < StoredStateMachine.States[i]->StateConditions.Num(); j++) //iterate over state conditions
			{
                if (!HandleStateCondition(StoredStateMachine.States[i]->StateConditions[j])) //check state condition
                {
                    break;
                }
                if (j != StoredStateMachine.States[i]->StateConditions.Num() - 1) //have all conditions been met?
                {
                    continue;
                }
				if (HandleAutoCombo(i)) return;
				if (HandleStateInputs(i, Buffer))
				{
					bIsAutoCombo = false;
					return;
				}
			}
		}
		else
		{
			if (HandleAutoCombo(i)) return;
			if (HandleStateInputs(i, Buffer))
			{
				bIsAutoCombo = false;
				return;
			}
		}
	}
}

bool APlayerObject::HandleAutoCombo(int32 StateIndex)
{
	if (!FindAutoComboCancelOption(FName(StoredStateMachine.States[StateIndex]->Name))) return false;

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
	
	bIsAutoCombo = HandleStateTransition(StateIndex, true);
	return bIsAutoCombo;
}

bool APlayerObject::HandleStateInputs(int32 StateIndex, bool Buffer)
{
	for (FInputConditionList& List : StoredStateMachine.States[StateIndex]->InputConditionLists)
	{
		for (int v = 0; v < List.InputConditions.Num(); v++) //iterate over input conditions
		{
			//check input condition against input buffer, if not met break.
			if (!StoredInputBuffer.CheckInputCondition(List.InputConditions[v], (CancelFlags & CNC_EnableKaraCancel) == 0))
			{
				break;
			}
			if (v == List.InputConditions.Num() - 1) //have all conditions been met?
			{
				return HandleStateTransition(StateIndex, Buffer);
			}
		}
		if (List.InputConditions.Num() == 0) //if no input conditions, set state
		{
			return HandleStateTransition(StateIndex, Buffer);
		}
	}
	return false;
}

bool APlayerObject::HandleStateTransition(int32 StateIndex, bool Buffer)
{
	if (FindChainCancelOption(FName(StoredStateMachine.States[StateIndex]->Name))
	|| FindAutoComboCancelOption(FName(StoredStateMachine.States[StateIndex]->Name))
	|| FindWhiffCancelOption(FName(StoredStateMachine.States[StateIndex]->Name))
	|| CancelFlags & CNC_CancelIntoSelf) //if cancel option, allow resetting state
	{
		if (Buffer)
		{
			BufferedStateName = FName(StoredStateMachine.States[StateIndex]->Name);
			return true; //don't try to enter another state
		}
		if (StoredStateMachine.ForceSetState(FName(StoredStateMachine.States[StateIndex]->Name))) //if state set successful...
		{
			GotoLabelActive = false;
			switch (StoredStateMachine.States[StateIndex]->EntryStance)
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
			BufferedStateName = FName(StoredStateMachine.States[StateIndex]->Name);
			return true; //don't try to enter another state
		}
		if (StoredStateMachine.SetState(FName(StoredStateMachine.States[StateIndex]->Name))) //if state set successful...
		{
			GotoLabelActive = false;
			switch (StoredStateMachine.States[StateIndex]->EntryStance)
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
		UpdateVisuals();
		return;
	}
	
	Super::Update();
	CallSubroutine("CmnOnUpdate");
	CallSubroutine("OnUpdate");

	if (GameState->GameInstance->IsTraining)
	{
		if ((PlayerFlags & PLF_IsStunned) == 0)
			CurrentHealth = MaxHealth;
		if ((AttackFlags & ATK_IsAttacking) == 0 && ComboTimer <= 0)
		{
			GameState->BattleState.Meter[PlayerIndex] = GameState->BattleState.MaxMeter[PlayerIndex];
		}
		if (PlayerIndex == 1)
		{
			if (CheckIsStunned())
				Inputs = INP_A | INP_Left;
			else
				Inputs = INP_Neutral;
		}
	}
	
	if (GameState->BattleState.TimeUntilRoundStart > 0)
		Inputs = INP_Neutral;

	//run input buffer before checking hitstop
	if ((Direction == DIR_Left && !Player->FlipInputs) || (Player->FlipInputs && Direction == DIR_Right)) //flip inputs with direction
	{
		const unsigned int Bit1 = Player->Inputs >> 2 & 1;
		const unsigned int Bit2 = Player->Inputs >> 3 & 1;
		unsigned int x = Bit1 ^ Bit2;

		x = x << 2 | x << 3;

		Player->Inputs = Player->Inputs ^ x;
	}

	if ((PlayerFlags & PLF_IsStunned) == 0)
	{
		Enemy->ComboCounter = 0;
		Enemy->ComboTimer = 0;
		Enemy->CallSubroutine("CmnOnComboEnd");
		Enemy->CallSubroutine("OnComboEnd");
		TotalProration = 10000;
	}
	if (Inputs << 27 == 0) //if no direction, set neutral input
		Inputs |= INP_Neutral;
	else
		Inputs = Inputs & ~INP_Neutral; //remove neutral input if directional input
	
	if (PlayerFlags & PLF_IsThrowLock)
	{
		StoredInputBuffer.Tick(Inputs);
		HandleStateMachine(true); //handle state transitions
		Player->StoredStateMachine.Update();
	
		if (TimeUntilNextCel > 0)
			TimeUntilNextCel--;
		if (TimeUntilNextCel == 0)
			CelIndex++;
		
		if (ActionTime < ThrowTechTimer)
		{
			if (StoredStateMachine.GetStateIndex("Throw") != INDEX_NONE)
			{
				bool IsTech = true;
				if (!CanProximityThrow)
				{
					const auto ThrowState = StoredStateMachine.States[StoredStateMachine.GetStateIndex("Throw")];
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
						JumpToState("GuardBreakStand");
						Enemy->JumpToState("GuardBreakStand");
						InitEventHandler(EVT_Update, "ThrowTech");
						Enemy->InitEventHandler(EVT_Update, "ThrowTech");
					}
					else
					{
						JumpToState("GuardBreakAir");
						Enemy->JumpToState("GuardBreakAir");
						InitEventHandler(EVT_Update, "ThrowTechAir");
						Enemy->InitEventHandler(EVT_Update, "ThrowTechAir");
					}
					HitPosX = (PosX + Enemy->PosX) / 2;
					HitPosY = (PosY + Enemy->PosY) / 2 + 250000;
					CreateCommonParticle("cmn_throwtech", POS_Hit);
					return;
				}
			}
		}
		UpdateVisuals();
		ActionTime++;
		return;
	}
	
	if (CurrentHealth <= 0 && (PlayerFlags & PLF_IsDead) == 0)
	{
		PlayerFlags |= PLF_IsDead;
		if (Enemy->CurrentHealth > 0 && !(PlayerFlags & PLF_DeathCamOverride))
		{
			if (ReceivedHitCommon.AttackLevel < 2)
			{
			    AddCommonBattleObject("cmn_ko_s");
			}
			else if (ReceivedHitCommon.AttackLevel < 4)
			{
			    AddCommonBattleObject("cmn_ko_m");
			}
			else
			{
			    AddCommonBattleObject("cmn_ko_l");
			}
			Hitstop = 0;
			AttackOwner->Hitstop = 0;
		}
	}

	if (Hitstop > 0)
	{
		if (PlayerFlags & PLF_IsStunned)
			HandleBufferedState();
		GetBoxes();
		StoredInputBuffer.Tick(Inputs);
		HandleStateMachine(true); //handle state transitions
		return;
	}

	//reset moves used in combo if not currently doing combo 
	if (StoredStateMachine.CurrentState->StateType != EStateType::NormalAttack
		&& StoredStateMachine.CurrentState->StateType != EStateType::SpecialAttack
		&& StoredStateMachine.CurrentState->StateType != EStateType::SuperAttack)
	{
		for (int32& Index : MovesUsedInCombo)
			Index = -1;
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

	if ((PlayerFlags & PLF_RoundWinInputLock) == 0 || (GameState->BattleState.RoundFormat >= ERoundFormat::TwoVsTwo &&
		GameState->BattleState.RoundFormat <= ERoundFormat::ThreeVsThree))
		StoredInputBuffer.Tick(Inputs);
	else
		StoredInputBuffer.Tick(INP_Neutral);

	if (AirDashTimer > 0)
		AirDashTimer--;
	if (AirDashTimer == 1)
		CallSubroutine("CmnAnyCancelAir");

	if (AirDashNoAttackTime > 0)
		AirDashNoAttackTime--;
	if (AirDashNoAttackTime == 1)
		EnableAttacks();
	
	if (PosY <= GroundHeight && PrevPosY > GroundHeight && StoredStateMachine.CurrentState->StateType == EStateType::Hitstun)
	{
		if (GetCurrentStateName() != "FloatingCrumpleBody" && GetCurrentStateName() != "FloatingCrumpleHead")
		{
			if (ReceivedHit.GroundBounce.GroundBounceCount > 0)
        		HandleGroundBounce();
			else
			{
				StunTime = 0;
				StunTimeMax = 0;
				PlayerFlags |= PLF_IsKnockedDown;
				if (!(PlayerFlags & PLF_IsHardKnockedDown))
					EnableState(ENB_Tech);
        	}
		}
	}
	
	if (StunTime > 0)
		StunTime--;
	if (StunTime == 0 && !(PlayerFlags & PLF_IsDead) && CheckIsStunned())
	{
		if (StoredStateMachine.CurrentState->StateType == EStateType::Blockstun)
		{
			if (Stance == ACT_Standing)
			{
				JumpToState("StandBlockEnd");
			}
			else if (Stance == ACT_Crouching)
			{
				JumpToState("CrouchBlockEnd");
			}
			else
			{
				JumpToState("AirBlockEnd");
			}
		}
		else if (PosY == GroundHeight && GetCurrentStateName() != "FaceDownWakeUp"
			&& GetCurrentStateName() != "FaceUpWakeUp" && !(PlayerFlags & PLF_IsKnockedDown))
		{
			if (Stance == ACT_Standing)
			{
				JumpToState("Stand");
			}
			else if (Stance == ACT_Crouching)
			{
				JumpToState("Crouch");
			}
			TotalProration = 10000;
		}
		else
		{
			if ((PlayerFlags & PLF_IsKnockedDown) == 0 && (PlayerFlags & PLF_IsHardKnockedDown) == 0 && (PlayerFlags & PLF_IsDead) == 0)
				EnableState(ENB_Tech);
		}
	}
	
	if (StoredStateMachine.CurrentState->StateType != EStateType::Hitstun)
	{
		OTGCount = 0;
	}

	if (PlayerFlags & PLF_TouchingWall && Enemy->StoredStateMachine.CurrentState->StateType != EStateType::Hitstun && Pushback != 0)
	{
		if (IsValid(AttackOwner))
			AttackOwner->Pushback = Pushback;
		Pushback = 0;
	}
		
	if (StoredStateMachine.CurrentState->StateType != EStateType::Hitstun)
	{
		PlayerFlags &= ~PLF_IsKnockedDown;
	}
	
	if (StoredStateMachine.CurrentState->StateType != EStateType::Hitstun
		&& StoredStateMachine.CurrentState->StateType != EStateType::Blockstun)
	{
		if (Enemy->StoredStateMachine.CurrentState->StateType != EStateType::Hitstun
			&& Enemy->StoredStateMachine.CurrentState->StateType != EStateType::Blockstun)
			Pushback = 0;
		PlayerFlags &= ~PLF_IsStunned;
		DisableState(ENB_Tech);
	}

	if ((GetCurrentStateName() == "FaceDownLoop" || GetCurrentStateName() == "FaceUpLoop") && ActionTime >= ReceivedHit.KnockdownTime && (PlayerFlags & PLF_IsDead) == 0)
	{
		Enemy->ComboCounter = 0;
		Enemy->ComboTimer = 0;
		OTGCount = 0;
		if (StoredStateMachine.CurrentState->Name == "FaceDownLoop")
			JumpToState("FaceDownWakeUp");
		else if (StoredStateMachine.CurrentState->Name == "FaceUpLoop")
			JumpToState("FaceUpWakeUp");
		TotalProration = 10000;
		PlayerFlags &= ~PLF_IsKnockedDown;
		DisableState(ENB_Tech);
	}

	if (PlayerFlags & PLF_IsDead)
		DisableState(ENB_Tech);

	InstantBlockLockoutTimer--;

	if (StoredStateMachine.CurrentState->StateType == EStateType::Hitstun && ReceivedHit.WallBounce.WallBounceCount > 0 && PosY > GroundHeight)
		HandleWallBounce();
	
	if (PosY == GroundHeight && PrevPosY != GroundHeight) //reset air move counts on ground
	{
		CurrentAirJumpCount = AirJumpCount;
		CurrentAirDashCount = AirDashCount;
		if (PlayerFlags & PLF_DefaultLandingAction && StoredStateMachine.CurrentState->StateType != EStateType::Hitstun)
		{
			JumpToState("JumpLanding");
		}
		SetStance(ACT_Standing);
		TriggerEvent(EVT_Landing);
		CallSubroutine("CmnOnLanding");
		CallSubroutine("OnLanding");
		CreateCommonParticle("cmn_jumpland_smoke", POS_Player);
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

	HandleStateMachine(false);
	
	Player->StoredStateMachine.Update();
	TriggerEvent(EVT_Update);
	
	if (TimeUntilNextCel > 0)
		TimeUntilNextCel--;
	if (TimeUntilNextCel == 0)
		CelIndex++;
	
	GetBoxes();
	
	HandleThrowCollision();
	
	GameState->SetScreenBounds();
	GameState->SetStageBounds();
	ActionTime++;
	
	UpdateVisuals();
}

void APlayerObject::UpdateNotBattle()
{
	Player->StoredStateMachine.Update();
	
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
	
	for (int i = 0; i < 32; i++)
	{
		if (IsValid(ChildBattleObjects[i]))
		{
			if (ChildBattleObjects[i]->MiscFlags & MISC_DeactivateOnReceiveHit)
			{
				ChildBattleObjects[i]->DeactivateObject();
			}
		}
	}
	if (CurrentHealth <= 0)
	{
		if (!(PlayerFlags & PLF_IsDead))
			StartSuperFreeze(0);
		
		CurrentHealth = 0;
		if (PosY <= GroundHeight && !(PlayerFlags & PLF_IsKnockedDown))
		{
			if (HACT == HACT_AirFaceUp || HACT == HACT_AirNormal || HACT == HACT_FloatingCrumple)
				BufferedStateName = FName("BLaunch");
			else if (HACT == HACT_AirVertical)
				BufferedStateName = FName("VLaunch");
			else if (HACT == HACT_AirFaceDown)
				BufferedStateName = FName("FLaunch");
			else if (HACT == HACT_Blowback)
				BufferedStateName = FName("Blowback");
			else if (HACT == HACT_Tailspin)
				BufferedStateName = FName("Tailspin");
			else
			{
				BufferedStateName = FName("Crumple");
			}
		}
		else
		{
			if (PosY <= GroundHeight)
				PosY = GroundHeight + 1;
			if (HACT == HACT_AirFaceUp || HACT == HACT_AirNormal)
				BufferedStateName = FName("BLaunch");
			else if (HACT == HACT_AirVertical)
				BufferedStateName = FName("VLaunch");
			else if (HACT == HACT_AirFaceDown)
				BufferedStateName = FName("FLaunch");
			else if (HACT == HACT_Blowback)
				BufferedStateName = FName("Blowback");
			else if (HACT == HACT_Tailspin)
				BufferedStateName = FName("Tailspin");
			else
				BufferedStateName = FName("BLaunch");
		}
		return;
	}
	switch (HACT)
	{
	case HACT_GroundNormal:
		switch (Stance)
		{
		case ACT_Standing:
		default:
			if (ReceivedHitCommon.AttackLevel == 0)
				BufferedStateName = FName("Hitstun0");
			else if (ReceivedHitCommon.AttackLevel == 1)
				BufferedStateName = FName("Hitstun1");
			else if (ReceivedHitCommon.AttackLevel == 2)
				BufferedStateName = FName("Hitstun2");
			else if (ReceivedHitCommon.AttackLevel == 3)
				BufferedStateName = FName("Hitstun3");
			else if (ReceivedHitCommon.AttackLevel == 4)
				BufferedStateName = FName("Hitstun4");
			else if (ReceivedHitCommon.AttackLevel == 5)
				BufferedStateName = FName("Hitstun5");
			break;
		case ACT_Crouching:
			if (ReceivedHitCommon.AttackLevel == 0)
				BufferedStateName = FName("CrouchHitstun0");
			else if (ReceivedHitCommon.AttackLevel == 1)
				BufferedStateName = FName("CrouchHitstun1");
			else if (ReceivedHitCommon.AttackLevel == 2)
				BufferedStateName = FName("CrouchHitstun2");
			else if (ReceivedHitCommon.AttackLevel == 3)
				BufferedStateName = FName("CrouchHitstun3");
			else if (ReceivedHitCommon.AttackLevel == 4)
				BufferedStateName = FName("CrouchHitstun4");
			else if (ReceivedHitCommon.AttackLevel == 5)
				BufferedStateName = FName("CrouchHitstun5");
			StunTime += 1;
			StunTimeMax += 1;
		}
		break;
	case HACT_Crumple:
		BufferedStateName = FName("Crumple");
		break;
	case HACT_ForceCrouch:
		Stance = ACT_Crouching;
		if (ReceivedHitCommon.AttackLevel == 0)
			BufferedStateName = FName("CrouchHitstun0");
		else if (ReceivedHitCommon.AttackLevel == 1)
			BufferedStateName = FName("CrouchHitstun1");
		else if (ReceivedHitCommon.AttackLevel == 2)
			BufferedStateName = FName("CrouchHitstun2");
		else if (ReceivedHitCommon.AttackLevel == 3)
			BufferedStateName = FName("CrouchHitstun3");
		else if (ReceivedHitCommon.AttackLevel == 4)
			BufferedStateName = FName("CrouchHitstun4");
		else if (ReceivedHitCommon.AttackLevel == 5)
			BufferedStateName = FName("CrouchHitstun5");
		StunTime += 1;
		StunTimeMax += 1;
		break;
	case HACT_ForceStand:
		Stance = ACT_Standing;
		if (ReceivedHitCommon.AttackLevel == 0)
			BufferedStateName = FName("Hitstun0");
		else if (ReceivedHitCommon.AttackLevel == 1)
			BufferedStateName = FName("Hitstun1");
		else if (ReceivedHitCommon.AttackLevel == 2)
			BufferedStateName = FName("Hitstun2");
		else if (ReceivedHitCommon.AttackLevel == 3)
			BufferedStateName = FName("Hitstun3");
		else if (ReceivedHitCommon.AttackLevel == 4)
			BufferedStateName = FName("Hitstun4");
		else if (ReceivedHitCommon.AttackLevel == 5)
			BufferedStateName = FName("Hitstun5");
		break;
	case HACT_GuardBreakCrouch:
		BufferedStateName = FName("GuardBreakCrouch");
		break;
	case HACT_GuardBreakStand:
		BufferedStateName = FName("GuardBreak");
		break;
	case HACT_AirNormal:
	case HACT_AirFaceUp:
		BufferedStateName = FName("BLaunch");
		break;
	case HACT_AirVertical:
		BufferedStateName = FName("VLaunch");
		break;
	case HACT_AirFaceDown:
		BufferedStateName = FName("FLaunch");
		break;
	case HACT_Blowback:
		BufferedStateName = FName("Blowback");
		break;
	case HACT_Tailspin:
		BufferedStateName = FName("Tailspin");
		break;
	case HACT_FloatingCrumple:
		if (ReceivedHit.FloatingCrumpleType == FLT_Body)
			BufferedStateName = FName("FloatingCrumpleBody");
		else
			BufferedStateName = FName("FloatingCrumpleHead");
		break;
	case HACT_None: break;
	default: ;
	}
	DisableAll();
}

void APlayerObject::SetHitValuesOverTime()
{
	if (StoredStateMachine.CurrentState->StateType == EStateType::Hitstun && PosY > GroundHeight
		&& GetCurrentStateName() != "FloatingCrumpleBody" && GetCurrentStateName() != "FloatingCrumpleHead")
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
	
	if (!(AttackFlags & ATK_IgnorePushbackScaling) && Enemy->ComboCounter > 5)
	{
		FinalHitPushbackX = ReceivedHit.GroundPushbackX + (Enemy->ComboCounter - 5) * 700;
		FinalAirHitPushbackX = ReceivedHit.AirPushbackX + (Enemy->ComboCounter - 5) * 350;
		FinalAirHitPushbackY = ReceivedHit.AirPushbackY - (Enemy->ComboCounter - 5) * 350;
		FinalGravity = ReceivedHit.Gravity + (Enemy->ComboCounter - 5) * 25;
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
	case HACT_Blowback:
		switch (ReceivedHit.BlowbackLevel)
		{
		case 0:
		default:
			break;
		case 1:
			GotoLabel("1", false);
			break;;
		case 2:
			GotoLabel("2", false);
			break;
		case 3:
			GotoLabel("3", false);
			break;
		case 4:
			GotoLabel("4", false);
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

void APlayerObject::SetThrowExeState(FString ExeState)
{
	ExeStateName = FName(ExeState);
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

void APlayerObject::PlayVoiceLine(FString Name)
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

void APlayerObject::PlayCommonLevelSequence(FString Name)
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

void APlayerObject::PlayLevelSequence(FString Name)
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

void APlayerObject::StartSuperFreeze(int Duration, int SelfDuration)
{
	if (!GameState) return;
	GameState->StartSuperFreeze(Duration, SelfDuration, this);
	if (Duration > 0) TriggerEvent(EVT_SuperFreeze);
}

void APlayerObject::BattleHudVisibility(bool Visible)
{
	if (!GameState) return;
	GameState->BattleHudVisibility(Visible);
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

APlayerObject* APlayerObject::SwitchMainPlayer(int NewTeamIndex)
{
	if (!GameState) return nullptr;
	return GameState->SwitchMainPlayer(this, NewTeamIndex);
}

void APlayerObject::SetOnScreen(bool OnScreen)
{
	if (OnScreen)
		PlayerFlags |= PLF_IsOnScreen;
	else
		PlayerFlags &= ~PLF_IsOnScreen;
}

void APlayerObject::ToggleComponentVisibility(FString ComponentName, bool Visible)
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

bool APlayerObject::IsCorrectBlock(EBlockType BlockType)
{
	if (BlockType != BLK_None && EnableFlags & ENB_Block)
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
		if ((CheckInput(Left) && !CheckInput(Right) && PosY > GroundHeight) || GetCurrentStateName() == "AirBlock")
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
		if ((CheckInput(Input1) || GetCurrentStateName() == "CrouchBlock") && BlockType != BLK_High && !CheckInput(Right))
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
		if ((CheckInput(Input4) || GetCurrentStateName() == "StandBlock") && BlockType != BLK_Low && !CheckInput(Right))
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
		GotoLabel("Lv1");
		break;
	case 1:
		GotoLabel("Lv1");
		break;
	case 2:
		GotoLabel("Lv2");
		break;
	case 3:
		GotoLabel("Lv2");
		break;
	case 4:
		GotoLabel("Lv3");
		break;
	case 5:
		GotoLabel("Lv3");
		break;
	}
	if (Stance == ACT_Jumping || GetCurrentStateName() == "AirBlock")
	{
		JumpToState("AirBlock", true);
		Stance = ACT_Jumping;
	}
	else if (CheckInput(Input1) || GetCurrentStateName() == "CrouchBlock")
	{
		PosY = 0;
		JumpToState("CrouchBlock", true);
		Stance = ACT_Crouching;
	}
	else 
	{
		PosY = 0;
		JumpToState("StandBlock", true);
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
		|| CalculateDistanceBetweenPoints(DIST_Distance, OBJ_Self, POS_Self, OBJ_Enemy, POS_Self) > 240000)
	{
		if (StoredStateMachine.CurrentState->StateType == EStateType::Blockstun && StunTime == 0)
		{
			if (Stance == ACT_Standing)
			{
				JumpToState("StandBlockEnd");
			}
			else if (Stance == ACT_Crouching)
			{
				JumpToState("CrouchBlockEnd");
			}
			else
			{
				JumpToState("AirBlockEnd");
			}
		}
		return;
	}
	if (!(EnableFlags & ENB_ProximityBlock))
		return;

	FInputCondition Input1;
	FInputBitmask BitmaskDownLeft;
	BitmaskDownLeft.InputFlag = INP_DownLeft;
	Input1.Sequence.Add(BitmaskDownLeft);
	Input1.Method = EInputMethod::Strict;
	Input1.bInputAllowDisable = false;
	GotoLabel("Pre");
	if (PosY > GroundHeight)
	{
		JumpToState("AirBlock", true);
		Stance = ACT_Jumping;
	}
	else if (CheckInput(Input1))
	{
		JumpToState("CrouchBlock", true);
		Stance = ACT_Crouching;
	}
	else 
	{
		JumpToState("StandBlock", true);
		Stance = ACT_Standing;
	}
}

void APlayerObject::EmptyStateMachine()
{
	StoredStateMachine.States.Empty();
	StoredStateMachine.StateNames.Empty();
	StoredStateMachine.CurrentState = nullptr;
}

void APlayerObject::HandleBufferedState()
{
	if (BufferedStateName != FName())
	{
		if (FindChainCancelOption(BufferedStateName)
			|| FindAutoComboCancelOption(BufferedStateName)
			|| FindWhiffCancelOption(BufferedStateName)
			|| CancelFlags & CNC_CancelIntoSelf) //if cancel option, allow resetting state
		{
			if (StoredStateMachine.ForceSetState(BufferedStateName))
			{
				GotoLabelActive = false;
				switch (StoredStateMachine.CurrentState->EntryStance)
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
			BufferedStateName = FName();
		}
		else
		{
			if (StoredStateMachine.SetState(BufferedStateName))
			{
				GotoLabelActive = false;
				switch (StoredStateMachine.CurrentState->EntryStance)
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
			BufferedStateName = FName();
		}
	}
}

bool APlayerObject::HandleStateCondition(EStateCondition StateCondition)
{
	ReturnReg = false;
	switch(StateCondition)
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
	case EStateCondition::FirstGaugeOneBar:
		if (GameState->BattleState.Gauge[PlayerIndex][0] >= 10000)
			ReturnReg = true;
		break;
	case EStateCondition::FirstGaugeTwoBars:
		if (GameState->BattleState.Gauge[PlayerIndex][0] >= 20000)
			ReturnReg = true;
		break;
	case EStateCondition::FirstGaugeThreeBars:
		if (GameState->BattleState.Gauge[PlayerIndex][0] >= 30000)
			ReturnReg = true;
		break;
	case EStateCondition::FirstGaugeFourBars:
		if (GameState->BattleState.Gauge[PlayerIndex][0] >= 40000)
			ReturnReg = true;
		break;
	case EStateCondition::FirstGaugeFiveBars:
		if (GameState->BattleState.Gauge[PlayerIndex][0] >= 50000)
			ReturnReg = true;
		break;
	case EStateCondition::FirstGaugeSixBars:
		if (GameState->BattleState.Gauge[PlayerIndex][0] >= 60000)
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

bool APlayerObject::FindChainCancelOption(const FName Name)
{
	ReturnReg = false;
	if (AttackFlags & ATK_HasHit && AttackFlags & ATK_IsAttacking && CancelFlags & CNC_ChainCancelEnabled)
	{
		if (CheckReverseBeat(Name))
			return ReturnReg;
		for (int i = 0; i < CancelArraySize; i++)
		{
			if (ChainCancelOptionsInternal[i] == StoredStateMachine.GetStateIndex(Name) && ChainCancelOptionsInternal[i] != INDEX_NONE)
			{
				ReturnReg = true;
				CheckMovesUsedInCombo(Name);
				break;
			}
		}
	}
	return ReturnReg;
}

bool APlayerObject::FindAutoComboCancelOption(const FName Name)
{
	ReturnReg = false;
	if (AttackFlags & ATK_HasHit && CancelFlags & CNC_ChainCancelEnabled)
	{
		for (int i = 0; i < 8; i++)
		{
			if (AutoComboCancels[i] == StoredStateMachine.GetStateIndex(Name) && AutoComboCancels[i] != INDEX_NONE)
			{
				ReturnReg = true;
				CheckMovesUsedInCombo(Name);
				break;
			}
		}
	}
	return ReturnReg;
}

bool APlayerObject::FindWhiffCancelOption(const FName Name)
{
	ReturnReg = false;
	if (CancelFlags & CNC_WhiffCancelEnabled)
	{
		if (CheckReverseBeat(Name))
			return ReturnReg;
		for (int i = 0; i < CancelArraySize; i++)
		{
			if (WhiffCancelOptionsInternal[i] == StoredStateMachine.GetStateIndex(Name) && WhiffCancelOptionsInternal[i] != INDEX_NONE)
			{
				ReturnReg = true;
				CheckMovesUsedInCombo(Name);
				break;
			}
		}
	}
	return ReturnReg;
}

bool APlayerObject::CheckReverseBeat(const FName Name)
{
	ReturnReg = false;
	if (!CanReverseBeat)
		return ReturnReg;
	
	const int32 Index = StoredStateMachine.GetStateIndex(Name);
	if (StoredStateMachine.CurrentState->StateType == EStateType::NormalAttack
		&& Index != INDEX_NONE && StoredStateMachine.States[Index]->StateType == EStateType::NormalAttack)
	{
		CheckMovesUsedInCombo(Name);
	}
	return ReturnReg;
}

bool APlayerObject::CheckMovesUsedInCombo(const FName Name)
{
	ReturnReg = false;
	int32 Usages = 0;
	for (const int32 Index : MovesUsedInCombo)
	{
		if (Index == StoredStateMachine.GetStateIndex(Name) && Index != INDEX_NONE)
			Usages++;
	}
	if (Usages < StoredStateMachine.States[StoredStateMachine.GetStateIndex(Name)]->MaxChain
		|| StoredStateMachine.States[StoredStateMachine.GetStateIndex(Name)]->MaxChain == -1)
		ReturnReg = true;
	return ReturnReg;
}

void APlayerObject::ThrowExe()
{
	JumpToState(ExeStateName.ToString());
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
			if (ActionTime == 0 && StoredStateMachine.CurrentState->StateType == EStateType::NormalAttack)
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
						CallSubroutine("ThrowParamGround");
					else
						CallSubroutine("ThrowParamAir");
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
			Enemy->JumpToState("ThrowLock");
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
	if (InStateType == EStateType::NormalAttack && StoredStateMachine.CurrentState->StateType == EStateType::NormalAttack)
	{
		ReturnReg = true;
	}
	if (InStateType == EStateType::SpecialAttack && StoredStateMachine.CurrentState->StateType >
		EStateType::NormalAttack && StoredStateMachine.CurrentState->StateType < EStateType::SpecialAttack)
	{
		ReturnReg = true;
	}
	if (InStateType == EStateType::SuperAttack && StoredStateMachine.CurrentState->StateType >
		EStateType::NormalAttack && StoredStateMachine.CurrentState->StateType < EStateType::SuperAttack)
	{
		ReturnReg = true;
	}
	
	return ReturnReg;
}

bool APlayerObject::CheckObjectPreventingState(int InObjectID)
{
	ReturnReg = false;
	for (int i = 0; i < 32; i++)
	{
		if (IsValid(ChildBattleObjects[i]))
		{
			if (ChildBattleObjects[i]->IsActive)
			{
				if (ChildBattleObjects[i]->ObjectID == InObjectID && ChildBattleObjects[i]->ObjectID != 0)
				{
					ReturnReg = true;
					break;
				}
			}
		}
	}
	return ReturnReg;
}

void APlayerObject::HandleWallBounce()
{
	if (ReceivedHit.WallBounce.WallBounceInCornerOnly)
	{
		if (PosX >= 2520000 || PosX <= -2520000)
		{
			if (ReceivedHit.WallBounce.WallBounceCount > 0)
			{
				ReceivedHit.GroundBounce.GroundBounceCount = 0;
				PlayerFlags &= ~PLF_TouchingWall;
				ReceivedHit.WallBounce.WallBounceCount--;
				ReceivedHit.GroundPushbackX = -1;
				ReceivedHit.AirPushbackX = SpeedX * ReceivedHit.WallBounce.WallBounceXRate / 100;
				ReceivedHit.AirPushbackY = ReceivedHit.WallBounce.WallBounceYSpeed * ReceivedHit.WallBounce.WallBounceYRate / 100;
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
				BufferedStateName = FName("WallBounce");
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
			ReceivedHit.AirPushbackY = ReceivedHit.WallBounce.WallBounceYSpeed * ReceivedHit.WallBounce.WallBounceYRate / 100;
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
			BufferedStateName = FName("WallBounce");
		}
	}
}

void APlayerObject::HandleGroundBounce()
{
	CreateCommonParticle("cmn_jumpland_smoke", POS_Player);
	ReceivedHit.GroundBounce.GroundBounceCount--;
	ReceivedHit.GroundPushbackX = -1;
	if (SpeedX > 0)
		ReceivedHit.AirPushbackX = -ReceivedHit.GroundBounce.GroundBounceXSpeed * ReceivedHit.GroundBounce.GroundBounceXRate / 100;
	else
		ReceivedHit.AirPushbackX = ReceivedHit.GroundBounce.GroundBounceXSpeed * ReceivedHit.GroundBounce.GroundBounceXRate / 100;
	ReceivedHit.AirPushbackY = -SpeedY * ReceivedHit.GroundBounce.GroundBounceYRate / 100;
	ReceivedHit.Gravity = ReceivedHit.GroundBounce.GroundBounceGravity;
	if (ReceivedHit.GroundBounce.GroundBounceUntech > 0)
		ReceivedHit.Untech = ReceivedHit.GroundBounce.GroundBounceUntech;
	else
		ReceivedHit.Untech = StunTime;
	ReceivedHit.Hitstop = ReceivedHit.GroundBounce.GroundBounceStop;
	ReceivedHit.GroundHitAction = HACT_AirFaceUp;
	EnableCancelIntoSelf(true);
	BufferedStateName = FName("BLaunch");
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

	SetComponentVisibility();
}

void APlayerObject::AddState(FString Name, UState* State)
{
	StoredStateMachine.Parent = this;
	StoredStateMachine.AddState(FName(Name), State);
}

void APlayerObject::AddObjectState(FString Name, UState* State, bool IsCommon)
{
	State->Parent = this;
	if (IsCommon)
	{
		CommonObjectStates.Add(State);
		CommonObjectStateNames.Add(FName(Name));
		CommonObjectStateUsed.Add(false);
	}
	else
	{
		ObjectStates.Add(State);
		ObjectStateNames.Add(FName(Name));
		ObjectStateUsed.Add(false);
	}
}

void APlayerObject::AddSubroutine(FString Name, USubroutine* Subroutine, bool IsCommon)
{
	Subroutine->Parent = this;
	if (IsCommon)
	{
		CommonSubroutines.Add(Subroutine);
		CommonSubroutineNames.Add(FName(Name));
	}
	else
	{
		Subroutines.Add(Subroutine);
		SubroutineNames.Add(FName(Name));
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

void APlayerObject::JumpToState(FString NewName, bool IsLabel)
{
	if (!GameState && !CharaSelectGameState) return;
	GotoLabelActive = IsLabel;
	if (StoredStateMachine.ForceSetState(FName(NewName)) && StoredStateMachine.CurrentState != nullptr)
	{
		switch (StoredStateMachine.CurrentState->EntryStance)
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
}

FString APlayerObject::GetCurrentStateName() const
{
	return StoredStateMachine.CurrentState->Name;
}

FString APlayerObject::GetLastStateName()
{
	return FString(LastStateName.ToString());
}

bool APlayerObject::CheckStateEnabled(EStateType StateType)
{
	ReturnReg = false;
	switch (StateType)
	{
	case EStateType::Standing:
		if (EnableFlags & ENB_Standing)
			ReturnReg = true;
		break;
	case EStateType::Crouching:
		if (EnableFlags & ENB_Crouching)
			ReturnReg = true;
		break;
	case EStateType::NeutralJump:
	case EStateType::ForwardJump:
	case EStateType::BackwardJump:
		if (EnableFlags & ENB_Jumping || (CancelFlags & CNC_JumpCancel && AttackFlags & ATK_HasHit && AttackFlags & ATK_IsAttacking))
			ReturnReg = true;
		break;
	case EStateType::ForwardWalk:
		if (EnableFlags & ENB_ForwardWalk)
			ReturnReg = true;
		break;
	case EStateType::BackwardWalk:
		if (EnableFlags & ENB_BackWalk)
			ReturnReg = true;
		break;
	case EStateType::ForwardDash:
		if (EnableFlags & ENB_ForwardDash)
			ReturnReg = true;
		break;
	case EStateType::BackwardDash:
		if (EnableFlags & ENB_BackDash)
			ReturnReg = true;
		break;
	case EStateType::ForwardAirDash:
		if (EnableFlags & ENB_ForwardAirDash || (CancelFlags & CNC_FAirDashCancel && AttackFlags & ATK_HasHit && AttackFlags & ATK_IsAttacking))
			ReturnReg = true;
		break;
	case EStateType::BackwardAirDash:
		if (EnableFlags & ENB_BackAirDash || (CancelFlags & CNC_BAirDashCancel && AttackFlags & ATK_HasHit && AttackFlags & ATK_IsAttacking))
			ReturnReg = true;
		break;
	case EStateType::NormalAttack:
		if (EnableFlags & ENB_NormalAttack)
			ReturnReg = true;
		break;
	case EStateType::SpecialAttack:
		if (EnableFlags & ENB_SpecialAttack || (CancelFlags & CNC_SpecialCancel && AttackFlags & ATK_HasHit && AttackFlags & ATK_IsAttacking))
			ReturnReg = true;
		break;
	case EStateType::SuperAttack:
		if (EnableFlags & ENB_SuperAttack || (CancelFlags & CNC_SuperCancel && AttackFlags & ATK_HasHit && AttackFlags & ATK_IsAttacking))
			ReturnReg = true;
		break;
	case EStateType::Tech:
		if (EnableFlags & ENB_Tech && CheckIsStunned())
			ReturnReg = true;
		break;
	case EStateType::Burst:
		if (EnableFlags & ENB_Burst && Enemy->Player->PlayerFlags & PLF_LockOpponentBurst && (PlayerFlags & PLF_IsDead) == 0)
			ReturnReg = true;
		break;
	case EStateType::SuperDash:
		if (EnableFlags & ENB_SuperDash)
			ReturnReg = true;
		break;
	default:
		ReturnReg = false;
	}
	return ReturnReg;
}

void APlayerObject::OnStateChange()
{
	// Deactivate all objects that need to be destroyed on state change.
	for (int i = 0; i < 32; i++)
	{
		if (IsValid(ChildBattleObjects[i]))
		{
			if (ChildBattleObjects[i]->MiscFlags & MISC_DeactivateOnStateChange)
			{
				ChildBattleObjects[i]->DeactivateObject();
			}
		}
	}
	
	DisableLastInput();
	DisableAll();
	
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

	// Reset offset, as the offset should be applied
	PrevOffsetX = 0;
	PrevOffsetY = 0;
	NextOffsetX = 0;
	NextOffsetY = 0;

	PosZ = 0;
	
	// Reset speed modifiers
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
	EventHandlers[EVT_Enter].FunctionName = FName("Init");	

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
	ChainCancelOptions.Empty();
	WhiffCancelOptions.Empty();
	for (int32& CancelOption : AutoComboCancels)
		CancelOption = -1;
	for (int32& CancelOption : ChainCancelOptionsInternal)
		CancelOption = -1;
	for (int32& CancelOption : WhiffCancelOptionsInternal)
		CancelOption = -1;
	HitCommon = FHitDataCommon();
	NormalHit = FHitData();
	CounterHit = FHitData();
	AnimName = FName();
	CelName = FName();
	BlendAnimName = FName();
	BlendCelName = FName();
	LastStateName = FName(GetCurrentStateName());
	HomingParams = FHomingParams();
}

void APlayerObject::PostStateChange()
{
	for (int i = 0; i < CancelArraySize; i++)
	{
		if (MovesUsedInCombo[i] == INDEX_NONE)
		{
			MovesUsedInCombo[i] = StoredStateMachine.GetStateIndex(FName(GetCurrentStateName()));
			break;
		}
	}
	StoredStateMachine.CurrentState->ResetToCDO();
}

void APlayerObject::ResetForRound(bool ResetHealth)
{
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
	IsPlayer = true;
	AttackTarget = nullptr;
	AttackOwner = nullptr;
	StopLinkObj = nullptr;
	PositionLinkObj = nullptr;
	MaterialLinkObj = nullptr;
	Timer0 = 0;
	Timer1 = 0;
	HomingParams = FHomingParams();
	CelName = FName();
	BlendCelName = FName();
	AnimName = FName();
	AnimFrame = 0;
	BlendAnimFrame = 0;
	FrameBlendPosition = 0;
	CelIndex = 0;
	TimeUntilNextCel = 0;
	for (auto& Handler : EventHandlers)
		Handler = FEventHandler();
	EventHandlers[EVT_Enter].FunctionName = FName("Init");
	SocketName = FName();
	SocketObj = OBJ_Self;
	SocketOffset = FVector::ZeroVector;
	ScaleForLink = FVector::OneVector;
	AddColor = FLinearColor(0,0,0,1);
	MulColor = FLinearColor(1,1,1,1);
	AddFadeColor = FLinearColor(0,0,0,1);
	MulFadeColor = FLinearColor(1,1,1,1);
	AddFadeSpeed = 0;
	MulFadeSpeed = 0;
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
	SubroutineReg1 = 0;
	SubroutineReg2 = 0;
	SubroutineReg3 = 0;
	SubroutineReg4 = 0;
	Inputs = 0;
	FlipInputs = false;
	Stance = ACT_Standing;
	if (ResetHealth) 
		CurrentHealth = MaxHealth;
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
	for (auto& ChildObj : ChildBattleObjects)
		ChildObj = nullptr;
	for (auto& StoredObj : StoredBattleObjects)
		StoredObj = nullptr;
	SavedInputCondition = FSavedInputCondition();
	CurrentAirJumpCount = 0;
	CurrentAirDashCount = 0;
	AirDashTimerMax = 0;
	CancelFlags = 0;
	EnableFlags = 0;
	AirDashNoAttackTime = 0;
	InstantBlockLockoutTimer = 0;
	MeterCooldownTimer = 0;
	for (int32& CancelOption : ChainCancelOptionsInternal)
		CancelOption = -1;
	for (int32& CancelOption : WhiffCancelOptionsInternal)
		CancelOption = -1;
	ChainCancelOptions.Empty();
	WhiffCancelOptions.Empty();
	LastStateName = FName();
	ExeStateName = FName();
	BufferedStateName = FName();
	WallTouchTimer = 0;
	JumpToState("Stand");
	GameState->BattleState.MaxMeter[PlayerIndex] = MaxMeter;
	SetDefaultComponentVisibility();
}

void APlayerObject::DisableLastInput()
{
	StoredInputBuffer.InputDisabled[89] = StoredInputBuffer.InputBufferInternal[89];
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
	for (int i = 0; i < CancelArraySize; i++) //reload TArrays with rolled back data
	{
		ChainCancelOptions.Empty();
		WhiffCancelOptions.Empty();
		if (StoredStateMachine.StateNames.Num() > 0)
		{
			if (ChainCancelOptionsInternal[i] != -1)
			{
				ChainCancelOptions.Add(StoredStateMachine.GetStateName(ChainCancelOptionsInternal[i]));
			}
			if (WhiffCancelOptionsInternal[i] != -1)
			{
				WhiffCancelOptions.Add(StoredStateMachine.GetStateName(WhiffCancelOptionsInternal[i]));
			}
		}
	}
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
	if(file)
	{
		file << "PlayerObject:\n";
		file << "\tEnableFlags: " << EnableFlags << std::endl;
		file << "\tCurrentAirJumpCount: " << CurrentAirJumpCount << std::endl;
		file << "\tCurrentAirDashCount: " << CurrentAirDashCount << std::endl;
		file << "\tAirDashTimer: " << AirDashTimer << std::endl;
		file << "\tAirDashTimerMax: " << AirDashTimerMax << std::endl;
		file << "\tCurrentHealth: " << CurrentHealth << std::endl;
		file << "\tCancelFlags: " << CancelFlags << std::endl;
		file << "\tPlayerFlags: " << PlayerFlags << std::endl;
		file << "\tInputs: " << StoredInputBuffer.InputBufferInternal[89] << std::endl;
		file << "\tStance: " << Stance.GetValue() << std::endl;
	}
}

void APlayerObject::EnableState(int32 EnableType)
{
	EnableFlags |= EnableType;
}

void APlayerObject::DisableState(int32 EnableType)
{
	EnableFlags = EnableFlags & ~EnableType;
}

void APlayerObject::EnableAttacks()
{
	EnableState(ENB_NormalAttack);
	EnableState(ENB_SpecialAttack);
	EnableState(ENB_SuperAttack);
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

void APlayerObject::EnableAll()
{
	EnableState(ENB_Standing);
	EnableState(ENB_Crouching);
	EnableState(ENB_Jumping);
	EnableState(ENB_ForwardWalk);
	EnableState(ENB_BackWalk);
	EnableState(ENB_ForwardDash);
	EnableState(ENB_BackDash);
	EnableState(ENB_ForwardAirDash);
	EnableState(ENB_BackAirDash);
	EnableState(ENB_NormalAttack);
	EnableState(ENB_SpecialAttack);
	EnableState(ENB_SuperAttack);
	EnableState(ENB_Block);
	EnableState(ENB_ProximityBlock);
	EnableState(ENB_Burst);
	EnableState(ENB_SuperDash);
}

void APlayerObject::DisableAll()
{
	DisableState(ENB_Standing);
	DisableState(ENB_Crouching);
	DisableState(ENB_Jumping);
	DisableState(ENB_ForwardWalk);
	DisableState(ENB_BackWalk);
	DisableState(ENB_ForwardDash);
	DisableState(ENB_BackDash);
	DisableState(ENB_ForwardAirDash);
	DisableState(ENB_BackAirDash);
	DisableState(ENB_NormalAttack);
	DisableState(ENB_SpecialAttack);
	DisableState(ENB_SuperAttack);
	DisableState(ENB_Block);
	DisableState(ENB_ProximityBlock);
	DisableState(ENB_Burst);
	DisableState(ENB_SuperDash);
}

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

void APlayerObject::AddChainCancelOption(FString Option)
{
	if (ChainCancelOptions.Find(FName(Option)) != INDEX_NONE) return;
	ChainCancelOptions.Add(FName(Option));
	if (ChainCancelOptions.Num() > 0)
	{
		ChainCancelOptionsInternal[ChainCancelOptions.Num() - 1] = StoredStateMachine.GetStateIndex(FName(Option));
	}
}

void APlayerObject::AddAutoComboCancel(FString Option, EInputFlags Button)
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
	
	AutoComboCancels[Index] = StoredStateMachine.GetStateIndex(FName(Option));
}

void APlayerObject::AddWhiffCancelOption(FString Option)
{
	if (WhiffCancelOptions.Find(FName(Option)) != INDEX_NONE) return;
	WhiffCancelOptions.Add(FName(Option));
	if (WhiffCancelOptions.Num() > 0)
	{
		WhiffCancelOptionsInternal[WhiffCancelOptions.Num() - 1] = StoredStateMachine.GetStateIndex(FName(Option));
	}
}

void APlayerObject::RemoveChainCancelOption(FString Option)
{
	if (const auto Index = ChainCancelOptions.Find(FName(Option)); Index != INDEX_NONE)
	{
		ChainCancelOptions[Index] = "";
		ChainCancelOptionsInternal[Index] = -1;
	}
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

void APlayerObject::RemoveWhiffCancelOption(FString Option)
{
	if (const auto Index = WhiffCancelOptions.Find(FName(Option)); Index != INDEX_NONE)
	{
		WhiffCancelOptions[Index] = "";
		WhiffCancelOptionsInternal[Index] = -1;
	}
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
