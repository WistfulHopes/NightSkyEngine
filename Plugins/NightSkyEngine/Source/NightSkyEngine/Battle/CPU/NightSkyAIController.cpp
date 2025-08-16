// Fill out your copyright notice in the Description page of Project Settings.


#include "NightSkyAIController.h"

#include "NightSkyEngine/Battle/Actors/NightSkyGameState.h"
#include "NightSkyEngine/Battle/Actors/PlayerObject.h"


// Sets default values
ANightSkyAIController::ANightSkyAIController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ANightSkyAIController::BeginPlay()
{
	Super::BeginPlay();

	GameState = Cast<ANightSkyGameState>(GetWorld()->GetGameState());
}

void ANightSkyAIController::Update()
{
	if (!Player) Player = GetPawn<APlayerObject>();
	
	if (GameState->BattleState.TimeUntilRoundStart || Player->PlayerFlags & PLF_RoundWinInputLock || !Player->IsOnScreen())
		return;

	if (Player->CurrentHealth <= 0) return;

	bBlock = false;
	
	bool bDefendOnly = false;
	
	if (Player->Enemy->CheckIsAttacking()
		&& Player->CheckEnemyInRange(
			Player->Enemy->PrimaryStateMachine.CurrentState->CPUData.AttackXBeginRange, 
			Player->Enemy->PrimaryStateMachine.CurrentState->CPUData.AttackXEndRange,
			Player->Enemy->PrimaryStateMachine.CurrentState->CPUData.AttackYBeginRange, 
			Player->Enemy->PrimaryStateMachine.CurrentState->CPUData.AttackYEndRange)
		&& WaitCount <= WaitLimit)
	{
		bDefendOnly = true;
	}
	else
	{
		WaitCount++;
		if (WaitCount <= WaitLimit) return;
	}
	
	TArray<UState*> AvailableStates{};
	for (auto State : Player->PrimaryStateMachine.States)
	{
		if (!Player->CanEnterState(State, StateMachine_Primary)) continue;
		AvailableStates.Add(State);
	}

	if (AvailableStates.Num() == 1)
	{
		ResetParams();
		TargetState = AvailableStates[0];
	}
	else
	{
		auto MaxWeight = 50;
		UState* CurState = nullptr;
		for (const auto State : AvailableStates)
		{
			int Weight;
			if (bDefendOnly)
			{
				if (!State->CPUData.bAttack)
				{
					Weight = CheckDefenseWeight(State);
					if (Weight > MaxWeight)
					{
						MaxWeight = Weight;
						CurState = State;
					}
				}
				else
				{
					Weight = CheckAttackWeight(State);
					if (Weight > MaxWeight)
					{
						MaxWeight = Weight;
						CurState = State;
					}
				}
			}
			else if (!State->CPUData.bAttack)
			{
				Weight = CheckBasicWeight(State);
				if (Weight > MaxWeight)
				{
					MaxWeight = Weight;
					CurState = State;
				}
			}
			else
			{
				Weight = CheckAttackWeight(State);
				if (Weight > MaxWeight)
				{
					MaxWeight = Weight;
					CurState = State;
				}
			}
		}
		if (TargetState != CurState)
		{
			ResetParams();
			TargetState = CurState;
		}
	}
	
	InputCount = FMath::Max(InputCount - InputCountLimit, 0);
	if (SetInputs()) ResetParams();
}

void ANightSkyAIController::ResetParams()
{
	WaitCount = 0;
	InputCount = 0;
	WaitLimit = 3;
	TargetState = nullptr;
}

bool ANightSkyAIController::SetInputs()
{
	if (!TargetState || TargetState->InputConditionLists.Num() == 0) return false;
	for (auto Condition : TargetState->InputConditionLists[0].InputConditions)
	{
		if (InputCount > InputCountLimit) return false;
		
		Player->StoredInputBuffer.WriteInputCondition(Condition);
		InputCount += Condition.Sequence.Num();
	}

	if (bBlock)
	{
		Player->StoredInputBuffer.InputBufferInternal[InputBufferSize - 1] |= INP_Left;
	}
	
	TargetState = nullptr;
	return true;
}

int32 ANightSkyAIController::GetEnemyDistanceX() const
{
	if (!IsValid(Player)) return 0;
	return Player->CalculateDistanceBetweenPoints(DIST_DistanceX, OBJ_Self, POS_Player, OBJ_Enemy, POS_Player);
}

int32 ANightSkyAIController::GetEnemyDistanceY() const
{
	if (!IsValid(Player)) return 0;
	return Player->CalculateDistanceBetweenPoints(DIST_DistanceY, OBJ_Self, POS_Player, OBJ_Enemy, POS_Player);
}

int32 ANightSkyAIController::CheckBasicWeight(const UState* State) const
{
	if (!IsValid(Player)) return 0;

	int Weight = 25;
	
	switch (State->StateType)
	{
	case EStateType::Standing:
	case EStateType::Crouching:
		break;
	case EStateType::NeutralJump:
	case EStateType::ForwardJump:
		if (GetEnemyDistanceY() > 105000 && Player->PosY < Player->Enemy->PosY)
		{
			Weight += GameState->BattleState.RandomManager.RandRange(10, 25);
		}
		break;
	case EStateType::ForwardAirDash:
		if (GetEnemyDistanceX() > 360000)
		{
			Weight += GameState->BattleState.RandomManager.RandRange(25, 50);
		}
		break;
	case EStateType::BackwardJump:
	case EStateType::BackwardAirDash:
		Weight = GameState->BattleState.RandomManager.RandRange(10, 15);
		if (Player->Enemy->CheckIsAttacking() && GetEnemyDistanceX() < 360000)
		{
			Weight += GameState->BattleState.RandomManager.RandRange(25, 50);
		}
		break;
	case EStateType::ForwardWalk:
		Weight += GameState->BattleState.RandomManager.RandRange(25, 80);
		if (GetEnemyDistanceX() > 420000)
		{
			Weight += GameState->BattleState.RandomManager.RandRange(30, 50);
		}
		if (Player->Enemy->CheckIsStunned())
		{
			Weight += GameState->BattleState.RandomManager.RandRange(15, 30);
		}
		break;
	case EStateType::ForwardDash:
		Weight += GameState->BattleState.RandomManager.RandRange(50, 100);
		if (GetEnemyDistanceX() > 640000)
		{
			Weight += GameState->BattleState.RandomManager.RandRange(15, 30);
		}
		if (Player->Enemy->CheckIsAttacking() && GetEnemyDistanceX() < 480000)
		{
			Weight -= GameState->BattleState.RandomManager.RandRange(25, 50);
		}
		if (Player->Enemy->CheckIsStunned())
		{
			Weight += GameState->BattleState.RandomManager.RandRange(15, 30);
		}
		if (Player->Direction == Player->Enemy->Direction)
		{
			Weight = 0;
		}
		break;
	case EStateType::BackwardWalk:
		Weight += GameState->BattleState.RandomManager.RandRange(10, 65);
		if (Player->Enemy->CheckIsAttacking() && GetEnemyDistanceX() < 540000)
		{
			Weight += GameState->BattleState.RandomManager.RandRange(15, 35);
		}
		if (Player->Enemy->CheckIsStunned())
		{
			Weight -= GameState->BattleState.RandomManager.RandRange(10, 20);
		}
		break;
	case EStateType::BackwardDash:
		Weight += GameState->BattleState.RandomManager.RandRange(20, 40);
		if (Player->Enemy->CheckIsAttacking() && GetEnemyDistanceX() < 540000)
		{
			Weight += GameState->BattleState.RandomManager.RandRange(10, 20);
		}
		if (Player->Enemy->CheckIsStunned())
		{
			Weight -= GameState->BattleState.RandomManager.RandRange(25, 50);
		}
		break;
	case EStateType::Tech:
		// TODO tech weight
		Weight = 250;
		break;
	default:
		break;
	}

	Weight += GameState->BattleState.RandomManager.RandRange(-50, 50);
	
	return Weight;
}

int32 ANightSkyAIController::CheckAttackWeight(const UState* State) const
{
	if (!IsValid(Player)) return 0;

	if (!Player->CheckEnemyInRange(State->CPUData.AttackXBeginRange, State->CPUData.AttackXEndRange,
	                               State->CPUData.AttackYBeginRange, State->CPUData.AttackYEndRange))
		return 0;

	int32 Weight = GameState->BattleState.RandomManager.RandRange(60, 100);

	if (Player->PosY < Player->Enemy->PosY && State->CPUData.bAntiAir) Weight += GameState->BattleState.RandomManager.RandRange(15, 40);

	if (State->CPUData.bUsesResource) Weight -= GameState->BattleState.RandomManager.RandRange(15, 40);
	if (State->CPUData.bBigDamage) Weight += GameState->BattleState.RandomManager.RandRange(15, 40);
	if (State->CPUData.bNoCombo && Player->ComboCounter > 2) Weight -= GameState->BattleState.RandomManager.RandRange(15, 40);
	
	switch (State->CPUData.AttackSpeed)
	{
	case ASPD_Fast:
		Weight += GameState->BattleState.RandomManager.RandRange(25, 50);
		break;
	case ASPD_Medium:
		break;
	case ASPD_Slow:
		Weight -= GameState->BattleState.RandomManager.RandRange(15, 30);
		break;
	default: break;
	}

	if (Player->Enemy->PrimaryStateMachine.CurrentState->StateType == EStateType::Hitstun)
	{
		if (State->CPUData.bThrow && !State->CPUData.bCombo) Weight = 0;
		if (State->CPUData.bCombo) Weight += GameState->BattleState.RandomManager.RandRange(35, 60);
	}
	else if (Player->IsEnemyBlocking())
	{
		if (State->CPUData.bBlockstring) Weight += GameState->BattleState.RandomManager.RandRange(15, 40);
		if (Player->Enemy->GetCurrentStateName(StateMachine_Primary) == State_Universal_StandBlock)
		{
			if (State->CPUData.BlockType == BLK_Low) Weight += GameState->BattleState.RandomManager.RandRange(15, 40);
		}
		else if (Player->Enemy->GetCurrentStateName(StateMachine_Primary) == State_Universal_CrouchBlock)
		{
			if (State->CPUData.BlockType == BLK_High) Weight += GameState->BattleState.RandomManager.RandRange(15, 40);
		}
		else if (State->CPUData.BlockType == BLK_None) Weight += GameState->BattleState.RandomManager.RandRange(15, 40);

		if (State->CPUData.bThrow)
		{
			if (Player->Enemy->CheckIsStunned()) Weight = 0;
			else Weight += GameState->BattleState.RandomManager.RandRange(15, 40);
		}
	}
	else
	{
		if (Player->Enemy->IsEnemyAttackState() && State->CPUData.bPunish)
		{
			bool bInPunishRange = false;
			switch (State->CPUData.PunishRange)
			{
			case RAN_Near:
				bInPunishRange = GetEnemyDistanceX() <= 420000;
				break;
			case RAN_Mid:
				bInPunishRange = GetEnemyDistanceX() > 420000 && GetEnemyDistanceX() <= 840000;
				break;
			case RAN_Far:
				bInPunishRange = GetEnemyDistanceX() > 840000;
				break;
			default:
				break;
			}

			Weight += bInPunishRange ? GameState->BattleState.RandomManager.RandRange(15, 40) : 0;
		}

		if (State->CPUData.bInvuln) Weight += GameState->BattleState.RandomManager.RandRange(15, 40);
	}
	Weight += GameState->BattleState.RandomManager.RandRange(-50, 50);
	
	return Weight;
}

int32 ANightSkyAIController::CheckDefenseWeight(const UState* State)
{
	if (!IsValid(Player)) return 0;

	int Weight = 0;
	
	switch (State->StateType)
	{
	case EStateType::Crouching:
		Weight += GameState->BattleState.RandomManager.RandRange(50, 80);
		if (Player->Enemy->GetAttackBlockType() == BLK_High)
		{
			Weight += GameState->BattleState.RandomManager.RandRange(25, 50);
		}
		break;
	case EStateType::BackwardJump:
	case EStateType::BackwardAirDash:
		Weight += GameState->BattleState.RandomManager.RandRange(25, 50);
		if (Player->Enemy->CheckIsAttacking() && GetEnemyDistanceX() < 360000)
		{
			Weight += GameState->BattleState.RandomManager.RandRange(25, 50);
		}
		break;
	case EStateType::BackwardWalk:
		Weight += GameState->BattleState.RandomManager.RandRange(25, 100);
		if (Player->Enemy->CheckIsAttacking() && GetEnemyDistanceX() < 360000)
		{
			Weight += GameState->BattleState.RandomManager.RandRange(15, 35);
		}
		if (Player->Enemy->GetAttackBlockType() == BLK_Low)
		{
			Weight -= GameState->BattleState.RandomManager.RandRange(25, 50);
		}
		break;
	case EStateType::BackwardDash:
		Weight += GameState->BattleState.RandomManager.RandRange(50, 80);
		if (Player->Enemy->CheckIsAttacking() && GetEnemyDistanceX() < 360000)
		{
			Weight += GameState->BattleState.RandomManager.RandRange(10, 20);
		}
		if (Player->Enemy->CheckIsStunned())
		{
			Weight -= GameState->BattleState.RandomManager.RandRange(25, 50);
		}
		break;
	case EStateType::Tech:
		// TODO tech weight
		Weight = 250;
		break;
	default:
		break;
	}
	
	bBlock = true;
	
	Weight += GameState->BattleState.RandomManager.RandRange(-25, 50);
	
	return Weight;
}
