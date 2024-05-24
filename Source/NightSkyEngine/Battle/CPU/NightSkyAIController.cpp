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

int32 ANightSkyAIController::GetEnemyDistanceX() const
{
	return Player->CalculateDistanceBetweenPoints(DIST_DistanceX, OBJ_Self, POS_Player, OBJ_Enemy, POS_Player);
}

int32 ANightSkyAIController::GetEnemyDistanceY() const
{
	return Player->CalculateDistanceBetweenPoints(DIST_DistanceY, OBJ_Self, POS_Player, OBJ_Enemy, POS_Player);
}

int32 ANightSkyAIController::CheckFWalkWeight() const
{
	if (GetEnemyDistanceX() <= 480000 && GetEnemyDistanceX() > 210000) return 25;
	
	return 0;
}

int32 ANightSkyAIController::CheckBWalkWeight() const
{
	if (GetEnemyDistanceX() <= 480000)
	{
		int32 Weight = 10;
		if (Player->Enemy->CheckIsAttacking()) Weight += 25;

		return Weight;
	}
	
	return 0;
}

int32 ANightSkyAIController::CheckFDashWeight() const
{
	if (GetEnemyDistanceX() > 480000) return 50;
	if (GetEnemyDistanceX() > 390000) return 25;
	
	return 0;
}

int32 ANightSkyAIController::CheckBDashWeight() const
{
	if (GetEnemyDistanceX() <= 390000)
	{
		int32 Weight = 10;
		if (Player->Enemy->CheckIsAttacking()) Weight += 15;
		if (Player->IsEnemyThrow()) Weight += 50;

		return Weight;
	}
	
	return 0;
}

int32 ANightSkyAIController::CheckAttackWeight(const UState* State) const
{
	const int32 AttackXBeginRange = State->CPUData.AttackXBeginRange;
	const int32 AttackXEndRange = State->CPUData.AttackXEndRange;
	const int32 AttackYBeginRange = State->CPUData.AttackYBeginRange;
	const int32 AttackYEndRange = State->CPUData.AttackYEndRange;

	if (!Player->CheckEnemyInRange(AttackXBeginRange, AttackXEndRange, AttackYBeginRange, AttackYEndRange)) return 0;

	int32 Weight = 75;
	
	if (State->CPUData.bPunish)
	{
		bool bInPunishRange = false;
		switch (State->CPUData.PunishRange)
		{
		case RAN_Near:
			bInPunishRange = GetEnemyDistanceX() <= 360000;
			break;
		case RAN_Mid:
			bInPunishRange = GetEnemyDistanceX() > 360000 && GetEnemyDistanceX() <= 1080000;
			break;
		case RAN_Far:
			bInPunishRange = GetEnemyDistanceX() > 720000;
			break;
		default:
			break;
		}

		Weight += bInPunishRange ? 25 : 0;
	}

	if (Player->Enemy->StoredStateMachine.CurrentState->StateType == EStateType::Hitstun)
	{
		if (State->CPUData.bThrow) Weight = 0;
		if (State->CPUData.bCombo) Weight += 25;
	}
	else if (Player->IsEnemyBlocking())
	{
		if (State->CPUData.bBlockstring) Weight += 25;
		if (Player->Enemy->GetCurrentStateName() == Player->Enemy->CharaStateData->DefaultStandBlock)
		{
			if (State->CPUData.BlockType == BLK_Low) Weight += 25;
		}
		else if (Player->Enemy->GetCurrentStateName() == Player->Enemy->CharaStateData->DefaultCrouchBlock)
		{
			if (State->CPUData.BlockType == BLK_High) Weight += 25;
		}
		else if (State->CPUData.BlockType == BLK_None) Weight += 25;
		
		if (State->CPUData.bThrow)
		{
			if (Player->Enemy->CheckIsStunned()) Weight = 0;
			else Weight += 25;
		}
	}
	else
	{
		if (Player->Enemy->CheckIsAttacking())
		{
			switch (State->CPUData.AttackSpeed)
			{
			case ASPD_Fast:
				Weight += 25;
				break;
			case ASPD_Medium:
				break;
			case ASPD_Slow:
				Weight -= 25;
				break;
			default: break;
			}
			if (State->CPUData.bInvuln) Weight += 25;
		}
		else if (Player->Enemy->IsEnemyAttackState() && State->CPUData.bPunish) Weight += 25;
	}

	if (Player->PosY < Player->Enemy->PosY && State->CPUData.bAntiAir) Weight += 25;
	
	if (State->CPUData.bUsesResource) Weight -= 25;
	if (State->CPUData.bBigDamage) Weight += 25;
	
	return Weight;
}

int32 ANightSkyAIController::CheckBurstWeight() const
{
	if (Player->CheckIsStunned())
	{
		return 1 / (static_cast<float>(Player->CurrentHealth) / static_cast<float>(Player->MaxHealth) * 251) - 1;
	}
	return 0;
}

// Called every frame
void ANightSkyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!Player) Player = GetPawn<APlayerObject>();
	if (GameState->BattleState.TimeUntilRoundStart) return;
	if (Player->PlayerFlags & PLF_RoundWinInputLock) return;
	
	if (Player->StoredStateMachine.CurrentState->StateType == EStateType::ForwardWalk || Player->StoredStateMachine.
		CurrentState->StateType == EStateType::ForwardDash)
	{
		Player->Inputs = INP_Right;
		if (Player->Direction == DIR_Left) Player->Inputs = INP_Left;
	}
	else if (Player->StoredStateMachine.CurrentState->StateType == EStateType::BackwardWalk)
	{
		Player->Inputs = INP_Left;
		if (Player->Direction == DIR_Left) Player->Inputs = INP_Right;
	}
	
	TArray<UState*> AvailableStates = {};

	for (auto State : Player->StoredStateMachine.States)
	{
		if (Player->CanEnterState(State)) AvailableStates.Add(State);
	}

	TMap<UState*, int32> StateWeights;
	for (auto State : AvailableStates)
	{
		int32 Weight = 0;
		switch (State->StateType)
		{
		case EStateType::Standing:
			break;
		case EStateType::Crouching:
			break;
		case EStateType::NeutralJump:
			break;
		case EStateType::ForwardJump:
			break;
		case EStateType::BackwardJump:
			break;
		case EStateType::ForwardWalk:
			Weight = CheckFWalkWeight();
			break;
		case EStateType::BackwardWalk:
			Weight = CheckBWalkWeight();
			break;
		case EStateType::ForwardDash:
			Weight = CheckFDashWeight();
			break;
		case EStateType::BackwardDash:
			break;
		case EStateType::ForwardAirDash:
			break;
		case EStateType::BackwardAirDash:
			break;
		case EStateType::NormalAttack:
		case EStateType::SpecialAttack:
		case EStateType::SuperAttack:
			Weight = CheckAttackWeight(State);
			break;
		case EStateType::Hitstun:
			break;
		case EStateType::Blockstun:
			break;
		case EStateType::Tech:
			Weight = 250;
			break;
		case EStateType::Burst:
			Weight = CheckBurstWeight();
			break;
		case EStateType::Tag:
			break;
		case EStateType::Custom:
			break;
		}

		if (Weight > 250) Weight = 250;
		if (Weight < 0) Weight = 0;

		if (Weight == 0) continue;
		StateWeights.Add(State, Weight);
	}

	StateWeights.ValueSort([](const int32 A, const int32 B)
	{
		return A > B;
	});

	TArray<UState*> Keys;
	StateWeights.GetKeys(Keys);

	if (Keys.Num())
	{
		Player->SetStateForCPU(FName(Keys[0]->Name));
	}
}
