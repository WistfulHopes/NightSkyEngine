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
	if (!IsValid(Player)) return 0;
	return Player->CalculateDistanceBetweenPoints(DIST_DistanceX, OBJ_Self, POS_Player, OBJ_Enemy, POS_Player);
}

int32 ANightSkyAIController::GetEnemyDistanceY() const
{
	if (!IsValid(Player)) return 0;
	return Player->CalculateDistanceBetweenPoints(DIST_DistanceY, OBJ_Self, POS_Player, OBJ_Enemy, POS_Player);
}

int32 ANightSkyAIController::CheckAttackWeight(const UState* State) const
{
	if (!IsValid(Player)) return 0;

	if (!Player->CheckEnemyInRange(State->CPUData.AttackXBeginRange, State->CPUData.AttackXEndRange,
	                               State->CPUData.AttackYBeginRange, State->CPUData.AttackYEndRange)
									&& !State->CPUData.bProjectile)
		return 0;

	int32 Weight = FMath::RandRange(50, 100);

	if (Player->PosY < Player->Enemy->PosY && State->CPUData.bAntiAir) Weight += FMath::RandRange(15, 40);

	if (State->CPUData.bUsesResource) Weight -= FMath::RandRange(15, 40);
	if (State->CPUData.bBigDamage) Weight += FMath::RandRange(15, 40);
	if (State->CPUData.bNoCombo && Player->ComboCounter > 2) Weight -= FMath::RandRange(15, 40);

	if (Player->Enemy->StoredStateMachine.CurrentState->StateType == EStateType::Hitstun)
	{
		if (State->CPUData.bThrow) Weight = 0;
		if (State->CPUData.bCombo) Weight += FMath::RandRange(35, 60);
	}
	else if (Player->IsEnemyBlocking())
	{
		if (State->CPUData.bBlockstring) Weight += FMath::RandRange(15, 40);
		if (Player->Enemy->GetCurrentStateName() == State_Universal_StandBlock)
		{
			if (State->CPUData.BlockType == BLK_Low) Weight += FMath::RandRange(15, 40);
		}
		else if (Player->Enemy->GetCurrentStateName() == State_Universal_CrouchBlock)
		{
			if (State->CPUData.BlockType == BLK_High) Weight += FMath::RandRange(15, 40);
		}
		else if (State->CPUData.BlockType == BLK_None) Weight += FMath::RandRange(15, 40);

		if (State->CPUData.bThrow)
		{
			if (Player->Enemy->CheckIsStunned()) Weight = 0;
			else Weight += FMath::RandRange(15, 40);
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

			Weight += bInPunishRange ? FMath::RandRange(15, 40) : 0;
		}

		switch (State->CPUData.AttackSpeed)
		{
		case ASPD_Fast:
			Weight += FMath::RandRange(15, 40);
			break;
		case ASPD_Medium:
			break;
		case ASPD_Slow:
			Weight -= FMath::RandRange(15, 40);
			break;
		default: break;
		}

		if (State->CPUData.bInvuln) Weight += FMath::RandRange(15, 40);
	}
	
	return Weight;
}

int32 ANightSkyAIController::CheckBurstWeight() const
{
	if (!IsValid(Player)) return 0;

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

	if (!IsValid(Player)) Player = GetPawn<APlayerObject>();
	if (GameState->BattleState.TimeUntilRoundStart || Player->PlayerFlags & PLF_RoundWinInputLock)
		bCanUpdateInput =
			false;
	else bCanUpdateInput = true;
}
