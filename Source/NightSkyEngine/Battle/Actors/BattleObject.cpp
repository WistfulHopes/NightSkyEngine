// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleObject.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "NightSkyGameState.h"
#include "ParticleManager.h"
#include "PlayerObject.h"
#include "NightSkyEngine/Battle/Bitflags.h"
#include "NightSkyEngine/Battle/Globals.h"
#include "NightSkyEngine/Data/ParticleData.h"

// Sets default values
ABattleObject::ABattleObject()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = false;
}

// Called when the game starts or when spawned
void ABattleObject::BeginPlay()
{
	Super::BeginPlay();
	if (IsPlayer)
	{
		Player = Cast<APlayerObject>(this);
	}
}

void ABattleObject::Move()
{
	//Set previous pos values
	PrevPosX = PosX; 
	PrevPosY = PosY;

	SpeedX = SpeedX * SpeedXRatePerFrame / 100;
	SpeedY = SpeedY * SpeedYRatePerFrame / 100;
	SpeedZ = SpeedZ * SpeedZRatePerFrame / 100;
	const int32 FinalSpeedX = SpeedX * SpeedXRate / 100;
	const int32 FinalSpeedY = SpeedY * SpeedYRate / 100;
	const int32 FinalSpeedZ = SpeedZ * SpeedZRate / 100;

	if (MiscFlags & MISC_InertiaEnable) //only use inertia if enabled
	{
		if (PosY <= GroundHeight && MiscFlags & MISC_FloorCollisionActive) //only decrease inertia if grounded
		{
			Inertia = Inertia - Inertia / 10;
		}
		if (Inertia > -875 && Inertia < 875) //if inertia small enough, set to zero
		{
			Inertia = 0;
		}
		AddPosXWithDir(Inertia);
	}

	if (IsPlayer)
	{
		int32 ModifiedPushback;
		if (PosY > GroundHeight)
			ModifiedPushback = Player->Pushback * 84;
		else if (Player->Stance == ACT_Crouching)
			ModifiedPushback = Player->Pushback * 86;
		else
			ModifiedPushback = Player->Pushback * 88;

		Player->Pushback = ModifiedPushback / 100;

		if (PosY <= GroundHeight || !(Player->PlayerFlags & PLF_IsStunned))
			AddPosXWithDir(Player->Pushback);
	}

	AddPosXWithDir(FinalSpeedX); //apply speed

	if (IsPlayer && Player != nullptr)
	{
		if (Player->AirDashTimer == 0 || (SpeedY > 0 && ActionTime < 5)) // only set y speed if not airdashing/airdash startup not done
			{
			PosY += FinalSpeedY;
			if (PosY > GroundHeight || !(MiscFlags & MISC_FloorCollisionActive))
				SpeedY -= Gravity;
			}
		else
		{
			SpeedY = 0;
		}
	}
	else
	{
		PosY += FinalSpeedY;
		if (PosY > GroundHeight || !(MiscFlags & MISC_FloorCollisionActive))
			SpeedY -= Gravity;
	}
		
	if (PosY < GroundHeight && MiscFlags & MISC_FloorCollisionActive) //if on ground, force y values to zero
	{
		PosY = GroundHeight;
	}

	PosZ += FinalSpeedZ;
}

// Called every frame
void ABattleObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABattleObject::HandlePushCollision(const ABattleObject* OtherObj)
{
	if (MiscFlags & MISC_PushCollisionActive && OtherObj->MiscFlags & MISC_PushCollisionActive)
	{
		if (Hitstop <= 0 && ((!OtherObj->IsPlayer || OtherObj->Player->PlayerFlags & PLF_IsThrowLock) == 0 || (!IsPlayer || Player->PlayerFlags & PLF_IsThrowLock) == 0))
		{
			if (T >= OtherObj->B && B <= OtherObj->T && R >= OtherObj->L && L <= OtherObj->R)
			{
				bool IsPushLeft;
				int CollisionDepth;
				if(PosX == OtherObj->PosX)
				{
					if (PrevPosX == OtherObj->PrevPosX)
					{
						if (IsPlayer == OtherObj->IsPlayer)
						{
							IsPushLeft = Player->PlayerIndex > 0;
						}
						else
						{
							IsPushLeft = IsPlayer > OtherObj->IsPlayer;
						}
					}
					else
					{
						IsPushLeft = PrevPosX < OtherObj->PrevPosX;
					}
				}
				else
				{
					IsPushLeft = PosX < OtherObj->PosX;
				}
				if (IsPushLeft)
				{
					CollisionDepth = OtherObj->L - R;
				}
				else
				{
					CollisionDepth = OtherObj->R - L;
				}
				PosX += CollisionDepth;
			}
		}
	}
}

void ABattleObject::HandleHitCollision(APlayerObject* OtherChar)
{
		if (AttackFlags & ATK_IsAttacking && AttackFlags & ATK_HitActive && !OtherChar->InvulnFlags & INV_StrikeInvulnerable && !OtherChar->StrikeInvulnerableTimer && OtherChar != Player)
	{
		if (!(AttackFlags & ATK_AttackHeadAttribute && OtherChar->InvulnFlags & INV_HeadInvulnerable) && !(AttackFlags & ATK_AttackProjectileAttribute && OtherChar->InvulnFlags & INV_ProjectileInvulnerable))
		{
			for (int i = 0; i < CollisionArraySize; i++)
			{
				if (Boxes[i].Type == BOX_Hit)
				{
					for (int j = 0; j < CollisionArraySize; j++)
					{
						if (OtherChar->Boxes[j].Type == BOX_Hurt)
						{
							FCollisionBox Hitbox = Boxes[i];

							FCollisionBox Hurtbox = OtherChar->Boxes[j];

							if (Direction == DIR_Right)
							{
								Hitbox.PosX += PosX;
							}
							else
							{
								Hitbox.PosX = -Hitbox.PosX + PosX;  
							}
							Hitbox.PosY += PosY;
							if (OtherChar->Direction == DIR_Right)
							{
								Hurtbox.PosX += OtherChar->PosX;
							}
							else
							{
								Hurtbox.PosX = -Hurtbox.PosX + OtherChar->PosX;  
							}
							Hurtbox.PosY += OtherChar->PosY;
							
							if (Hitbox.PosY + Hitbox.SizeY / 2 >= Hurtbox.PosY - Hurtbox.SizeY / 2
								&& Hitbox.PosY - Hitbox.SizeY / 2 <= Hurtbox.PosY + Hurtbox.SizeY / 2
								&& Hitbox.PosX + Hitbox.SizeX / 2 >= Hurtbox.PosX - Hurtbox.SizeX / 2
								&& Hitbox.PosX - Hitbox.SizeX / 2 <= Hurtbox.PosX + Hurtbox.SizeX / 2)
							{
								OtherChar->FaceOpponent();
								OtherChar->HaltMomentum();
								OtherChar->PlayerFlags |= PLF_IsStunned;
								AttackFlags &= ~ATK_HitActive;
								AttackFlags |= ATK_HasHit;
								int CollisionDepthX;
								if (Hitbox.PosX < Hurtbox.PosX)
									CollisionDepthX = Hurtbox.PosX - Hurtbox.SizeX / 2 - (Hitbox.PosX + Hitbox.SizeX / 2);
								else
									CollisionDepthX = Hitbox.PosX - Hitbox.SizeX / 2 - (Hurtbox.PosX + Hurtbox.SizeX / 2);
								int CollisionDepthY;
								if (Hitbox.PosY < Hurtbox.PosY)
									CollisionDepthY = Hurtbox.PosY - Hurtbox.SizeY / 2 - (Hitbox.PosY + Hitbox.SizeY / 2);
								else
									CollisionDepthY = Hitbox.PosY - Hitbox.SizeY / 2 - (Hurtbox.PosY + Hurtbox.SizeY / 2);
								HitPosX = Hitbox.PosX - CollisionDepthX / 2;
								HitPosY = Hitbox.PosY - CollisionDepthY / 2;
								
								TriggerEvent(EVT_HitOrBlock);

								const FHitData Data = InitHitDataByAttackLevel(false);
								const FHitData CounterData = InitHitDataByAttackLevel(true);
								OtherChar->ReceivedHitCommon = HitCommon;
								OtherChar->ReceivedHit = Data;
								
								if (OtherChar->IsCorrectBlock(HitCommon.BlockType)) //check blocking
								{

									CreateCommonParticle("cmn_guard", POS_Hit, FVector(0, 0, 0), FRotator(HitCommon.HitAngle, 0, 0));
									TriggerEvent(EVT_Block);
									
									OtherChar->StunTime = HitCommon.Blockstun;
									const int32 ChipDamage = NormalHit.Damage * HitCommon.ChipDamagePercent / 100;
									OtherChar->CurrentHealth -= ChipDamage;
									if (OtherChar->CurrentHealth <= 0)
									{
										EHitAction HACT;
										
										if (OtherChar->PosY == OtherChar->GroundHeight && !(OtherChar->PlayerFlags & PLF_IsKnockedDown))
											HACT = NormalHit.GroundHitAction;
										else
											HACT = NormalHit.AirHitAction;

										OtherChar->HandleHitAction(HACT);
									}
									else
									{
										OtherChar->HandleBlockAction();
										OtherChar->AirDashTimer = 0;
										if (OtherChar->PlayerFlags & PLF_TouchingWall)
										{
											Pushback = OtherChar->Pushback;
											OtherChar->Pushback = 0;
										}
									}
									// OtherChar->AddMeter(HitEffect.HitDamage * OtherChar->MeterPercentOnReceiveHitGuard / 100);
									// Player->AddMeter(HitEffect.HitDamage * Player->MeterPercentOnHitGuard / 100);
								}
								else if ((OtherChar->AttackFlags & ATK_IsAttacking) == 0)
								{
									CreateCommonParticle(HitCommon.HitVFXOverride.GetString(), POS_Hit, FVector(0, 0, 0), FRotator(HitCommon.HitAngle, 0, 0));
									TriggerEvent(EVT_Hit);
									EHitAction HACT;
										
									if (OtherChar->PosY == OtherChar->GroundHeight && !(OtherChar->PlayerFlags & PLF_IsKnockedDown))
										HACT = NormalHit.GroundHitAction;
									else
										HACT = NormalHit.AirHitAction;

									OtherChar->HandleHitAction(HACT);
								}
								else
								{
									CreateCommonParticle(HitCommon.HitVFXOverride.GetString(), POS_Hit, FVector(0, 0, 0), FRotator(HitCommon.HitAngle, 0, 0));
									OtherChar->ReceivedHit = CounterData;
									TriggerEvent(EVT_Hit);
									TriggerEvent(EVT_CounterHit);
									EHitAction HACT;
										
									if (OtherChar->PosY == OtherChar->GroundHeight && !(OtherChar->PlayerFlags & PLF_IsKnockedDown))
										HACT = CounterHit.GroundHitAction;
									else
										HACT = CounterHit.AirHitAction;
									
									OtherChar->HandleHitAction(HACT);
								}
								if (OtherChar->CurrentHealth <= 0 && (OtherChar->PlayerFlags & PLF_DeathCamOverride) == 0 && (OtherChar->PlayerFlags & PLF_IsDead) == 0)
								{
									if (Player->CurrentHealth == 0)
									{
										return;
									}
									/*Player->BattleHudVisibility(false);
									if (Player->Enemy->ReceivedAttackLevel < 2)
									{
										Player->StartSuperFreeze(40);
										Player->PlayCommonLevelSequence("KO_Shake");
									}
									else if (Player->Enemy->ReceivedAttackLevel < 4)
									{
										Player->StartSuperFreeze(70);
										Player->PlayCommonLevelSequence("KO_Zoom");
									}
									else
									{
										Player->StartSuperFreeze(110);
										Player->PlayCommonLevelSequence("KO_Turnaround");
									}*/
									Player->Hitstop = 0;
									Player->Enemy->Hitstop = 0;
								}
								return;
							}
						}
					}
				}
			}
		}
	}
}

FHitData ABattleObject::InitHitDataByAttackLevel(bool IsCounter)
{
	if (HitCommon.AttackLevel < 0)
		HitCommon.AttackLevel = 0;
	if (HitCommon.AttackLevel > 4)
		HitCommon.AttackLevel = 5;
	
	switch (HitCommon.AttackLevel)
	{
	case 0:
	default:
		if (HitCommon.BlockstopModifier == -1)
			HitCommon.BlockstopModifier = 0;
		if (HitCommon.Blockstun == -1)
			HitCommon.Blockstun = 9;
		if (HitCommon.GroundGuardPushbackX == -1)
			HitCommon.GroundGuardPushbackX = 20000;
		if (HitCommon.AirGuardPushbackX == -1)
			HitCommon.AirGuardPushbackX = 7500;
		if (HitCommon.AirGuardPushbackY == -1)
			HitCommon.AirGuardPushbackY = 15000;
		if (HitCommon.GuardGravity == -1)
			HitCommon.GuardGravity = 1900;
		if (NormalHit.Hitstop == -1)
			NormalHit.Hitstop = 11;
		if (NormalHit.Hitstun == -1)
			NormalHit.Hitstun = 10;
		if (NormalHit.Untech == -1)
			NormalHit.Untech = 10;
		if (NormalHit.Damage == -1)
			NormalHit.Damage = 300;
		if (NormalHit.GroundPushbackX == -1)
			NormalHit.GroundPushbackX = 25000;
		if (NormalHit.AirPushbackX == -1)
			NormalHit.AirPushbackX = 15000;
		if (NormalHit.AirPushbackY == -1)
			NormalHit.AirPushbackY = 30000;
		if (NormalHit.Gravity == -1)
			NormalHit.Gravity = 1900;
		if (CounterHit.Hitstop == -1)
			CounterHit.Hitstop = NormalHit.Hitstop;
		switch (HitCommon.VFXType)
		{
		case EHitVFXType::VFX_Strike:
		case EHitVFXType::VFX_Slash:
			HitCommon.HitVFXOverride.SetString("cmn_hit_s");
			break;
		case EHitVFXType::VFX_Special:
			HitCommon.HitVFXOverride.SetString("cmn_hit_sp");
			break;
		}
		break;
	case 1:
		if (HitCommon.BlockstopModifier == -1)
			HitCommon.BlockstopModifier = 0;
		if (HitCommon.Blockstun == -1)
			HitCommon.Blockstun = 11;
		if (HitCommon.GroundGuardPushbackX == -1)
			HitCommon.GroundGuardPushbackX = 22500;
		if (HitCommon.AirGuardPushbackX == -1)
			HitCommon.AirGuardPushbackX = 7500;
		if (HitCommon.AirGuardPushbackY == -1)
			HitCommon.AirGuardPushbackY = 15025;
		if (HitCommon.GuardGravity == -1)
			HitCommon.GuardGravity = 1900;
		if (NormalHit.Hitstop == -1)
			NormalHit.Hitstop = 12;
		if (NormalHit.Hitstun == -1)
			NormalHit.Hitstun = 12;
		if (NormalHit.Untech == -1)
			NormalHit.Untech = 12;
		if (NormalHit.Damage == -1)
			NormalHit.Damage = 400;
		if (NormalHit.GroundPushbackX == -1)
			NormalHit.GroundPushbackX = 27500;
		if (NormalHit.AirPushbackX == -1)
			NormalHit.AirPushbackX = 15000;
		if (NormalHit.AirPushbackY == -1)
			NormalHit.AirPushbackY = 30050;
		if (NormalHit.Gravity == -1)
			NormalHit.Gravity = 1900;
		if (CounterHit.Hitstop == -1)
			CounterHit.Hitstop = NormalHit.Hitstop + 2;
		switch (HitCommon.VFXType)
		{
		case EHitVFXType::VFX_Strike:
		case EHitVFXType::VFX_Slash:
			HitCommon.HitVFXOverride.SetString("cmn_hit_s");
			break;
		case EHitVFXType::VFX_Special:
			HitCommon.HitVFXOverride.SetString("cmn_hit_sp");
			break;
		}
		break;
	case 2:
		if (HitCommon.BlockstopModifier == -1)
			HitCommon.BlockstopModifier = 0;
		if (HitCommon.Blockstun == -1)
			HitCommon.Blockstun = 13;
		if (HitCommon.GroundGuardPushbackX == -1)
			HitCommon.GroundGuardPushbackX = 27000;
		if (HitCommon.AirGuardPushbackX == -1)
			HitCommon.AirGuardPushbackX = 7500;
		if (HitCommon.AirGuardPushbackY == -1)
			HitCommon.AirGuardPushbackY = 15050;
		if (HitCommon.GuardGravity == -1)
			HitCommon.GuardGravity = 1900;
		if (NormalHit.Hitstop == -1)
			NormalHit.Hitstop = 13;
		if (NormalHit.Hitstun == -1)
			NormalHit.Hitstun = 14;
		if (NormalHit.Untech == -1)
			NormalHit.Untech = 14;
		if (NormalHit.Damage == -1)
			NormalHit.Damage = 600;
		if (NormalHit.GroundPushbackX == -1)
			NormalHit.GroundPushbackX = 30000;
		if (NormalHit.AirPushbackX == -1)
			NormalHit.AirPushbackX = 15000;
		if (NormalHit.AirPushbackY == -1)
			NormalHit.AirPushbackY = 30100;
		if (NormalHit.Gravity == -1)
			NormalHit.Gravity = 1900;
		if (CounterHit.Hitstop == -1)
			CounterHit.Hitstop = NormalHit.Hitstop + 4;
		switch (HitCommon.VFXType)
		{
		case EHitVFXType::VFX_Strike:
		case EHitVFXType::VFX_Slash:
			HitCommon.HitVFXOverride.SetString("cmn_hit_m");
			break;
		case EHitVFXType::VFX_Special:
			HitCommon.HitVFXOverride.SetString("cmn_hit_sp");
			break;
		}
		break;
	case 3:
		if (HitCommon.BlockstopModifier == -1)
			HitCommon.BlockstopModifier = 0;
		if (HitCommon.Blockstun == -1)
			HitCommon.Blockstun = 16;
		if (HitCommon.GroundGuardPushbackX == -1)
			HitCommon.GroundGuardPushbackX = 30000;
		if (HitCommon.AirGuardPushbackX == -1)
			HitCommon.AirGuardPushbackX = 7500;
		if (HitCommon.AirGuardPushbackY == -1)
			HitCommon.AirGuardPushbackY = 15075;
		if (HitCommon.GuardGravity == -1)
			HitCommon.GuardGravity = 1900;
		if (NormalHit.Hitstop == -1)
			NormalHit.Hitstop = 14;
		if (NormalHit.Hitstun == -1)
			NormalHit.Hitstun = 17;
		if (NormalHit.Untech == -1)
			NormalHit.Untech = 16;
		if (NormalHit.Damage == -1)
			NormalHit.Damage = 800;
		if (NormalHit.GroundPushbackX == -1)
			NormalHit.GroundPushbackX = 35000;
		if (NormalHit.AirPushbackX == -1)
			NormalHit.AirPushbackX = 15000;
		if (NormalHit.AirPushbackY == -1)
			NormalHit.AirPushbackY = 30150;
		if (NormalHit.Gravity == -1)
			NormalHit.Gravity = 1900;
		if (CounterHit.Hitstop == -1)
			CounterHit.Hitstop = NormalHit.Hitstop + 8;
		switch (HitCommon.VFXType)
		{
		case EHitVFXType::VFX_Strike:
		case EHitVFXType::VFX_Slash:
			HitCommon.HitVFXOverride.SetString("cmn_hit_m");
			break;
		case EHitVFXType::VFX_Special:
			HitCommon.HitVFXOverride.SetString("cmn_hit_sp");
			break;
		}
		break;
	case 4:
		if (HitCommon.BlockstopModifier == -1)
			HitCommon.BlockstopModifier = 0;
		if (HitCommon.Blockstun == -1)
			HitCommon.Blockstun = 18;
		if (HitCommon.GroundGuardPushbackX == -1)
			HitCommon.GroundGuardPushbackX = 35000;
		if (HitCommon.AirGuardPushbackX == -1)
			HitCommon.AirGuardPushbackX = 7500;
		if (HitCommon.AirGuardPushbackY == -1)
			HitCommon.AirGuardPushbackY = 15100;
		if (HitCommon.GuardGravity == -1)
			HitCommon.GuardGravity = 1900;
		if (NormalHit.Hitstop == -1)
			NormalHit.Hitstop = 15;
		if (NormalHit.Hitstun == -1)
			NormalHit.Hitstun = 19;
		if (NormalHit.Untech == -1)
			NormalHit.Untech = 18;
		if (NormalHit.Damage == -1)
			NormalHit.Damage = 1000;
		if (NormalHit.GroundPushbackX == -1)
			NormalHit.GroundPushbackX = 40000;
		if (NormalHit.AirPushbackX == -1)
			NormalHit.AirPushbackX = 15000;
		if (NormalHit.AirPushbackY == -1)
			NormalHit.AirPushbackY = 30200;
		if (NormalHit.Gravity == -1)
			NormalHit.Gravity = 1900;
		if (CounterHit.Hitstop == -1)
			CounterHit.Hitstop = NormalHit.Hitstop + 12;
		switch (HitCommon.VFXType)
		{
		case EHitVFXType::VFX_Strike:
		case EHitVFXType::VFX_Slash:
			HitCommon.HitVFXOverride.SetString("cmn_hit_l");
			break;
		case EHitVFXType::VFX_Special:
			HitCommon.HitVFXOverride.SetString("cmn_hit_sp");
			break;
		}
		break;
	case 5:
		if (HitCommon.BlockstopModifier == -1)
			HitCommon.BlockstopModifier = 0;
		if (HitCommon.Blockstun == -1)
			HitCommon.Blockstun = 20;
		if (HitCommon.GroundGuardPushbackX == -1)
			HitCommon.GroundGuardPushbackX = 45000;
		if (HitCommon.AirGuardPushbackX == -1)
			HitCommon.AirGuardPushbackX = 7500;
		if (HitCommon.AirGuardPushbackY == -1)
			HitCommon.AirGuardPushbackY = 15125;
		if (HitCommon.GuardGravity == -1)
			HitCommon.GuardGravity = 1900;
		if (NormalHit.Hitstop == -1)
			NormalHit.Hitstop = 18;
		if (NormalHit.Hitstun == -1)
			NormalHit.Hitstun = 22;
		if (NormalHit.Untech == -1)
			NormalHit.Untech = 21;
		if (NormalHit.Damage == -1)
			NormalHit.Damage = 1250;
		if (NormalHit.GroundPushbackX == -1)
			NormalHit.GroundPushbackX = 50000;
		if (NormalHit.AirPushbackX == -1)
			NormalHit.AirPushbackX = 15000;
		if (NormalHit.AirPushbackY == -1)
			NormalHit.AirPushbackY = 30200;
		if (NormalHit.Gravity == -1)
			NormalHit.Gravity = 30250;
		if (CounterHit.Hitstop == -1)
			CounterHit.Hitstop = NormalHit.Hitstop + 16;
		switch (HitCommon.VFXType)
		{
		case EHitVFXType::VFX_Strike:
		case EHitVFXType::VFX_Slash:
			HitCommon.HitVFXOverride.SetString("cmn_hit_l");
			break;
		case EHitVFXType::VFX_Special:
			HitCommon.HitVFXOverride.SetString("cmn_hit_sp");
			break;
		}
		break;
	}
	
	if (CounterHit.Hitstun == -1)
		CounterHit.Hitstun = NormalHit.Hitstun;
	if (CounterHit.Untech == -1)
		CounterHit.Untech = NormalHit.Untech * 2;
	if (CounterHit.Damage == -1)
		CounterHit.Damage = NormalHit.Damage * 110 / 100;
	if (CounterHit.GroundPushbackX == -1)
		CounterHit.GroundPushbackX = NormalHit.GroundPushbackX;
	if (CounterHit.AirPushbackX == -1)
		CounterHit.AirPushbackX = NormalHit.AirPushbackX;
	if (CounterHit.AirPushbackY == -1)
		CounterHit.AirPushbackY = NormalHit.AirPushbackY;
	if (CounterHit.Gravity == -1)
		CounterHit.Gravity = NormalHit.Gravity;
	
	FHitData Data;
	if (!IsCounter)
		Data = NormalHit;
	else
		Data = CounterHit;
	
	return Data;
}

void ABattleObject::HandleClashCollision(ABattleObject* OtherObj)
{
	if (AttackFlags & ATK_IsAttacking && AttackFlags & ATK_HitActive && OtherObj != Player && OtherObj->AttackFlags & ATK_IsAttacking && OtherObj->AttackFlags & ATK_HitActive)
	{
		for (int i = 0; i < CollisionArraySize; i++)
		{
			if (Boxes[i].Type == BOX_Hit)
			{
				for (int j = 0; j < CollisionArraySize; j++)
				{
					if (OtherObj->Boxes[j].Type == BOX_Hit)
					{
						FCollisionBox Hitbox = Boxes[i];

						FCollisionBox OtherHitbox = OtherObj->Boxes[j];

						if (Direction == DIR_Right)
						{
							Hitbox.PosX += PosX;
						}
						else
						{
							Hitbox.PosX = -Hitbox.PosX + PosX;  
						}
						Hitbox.PosY += PosY;
						if (OtherObj->Direction == DIR_Right)
						{
							OtherHitbox.PosX += OtherObj->PosX;
						}
						else
						{
							OtherHitbox.PosX = -OtherHitbox.PosX + OtherObj->PosX;  
						}
						OtherHitbox.PosY += OtherObj->PosY;
							
						if (Hitbox.PosY + Hitbox.SizeY / 2 >= OtherHitbox.PosY - OtherHitbox.SizeY / 2
							&& Hitbox.PosY - Hitbox.SizeY / 2 <= OtherHitbox.PosY + OtherHitbox.SizeY / 2
							&& Hitbox.PosX + Hitbox.SizeX / 2 >= OtherHitbox.PosX - OtherHitbox.SizeX / 2
							&& Hitbox.PosX - Hitbox.SizeX / 2 <= OtherHitbox.PosX + OtherHitbox.SizeX / 2)
						{
							int CollisionDepthX;
							if (Hitbox.PosX < OtherHitbox.PosX)
								CollisionDepthX = OtherHitbox.PosX - OtherHitbox.SizeX / 2 - (Hitbox.PosX + Hitbox.SizeX / 2);
							else
								CollisionDepthX = Hitbox.PosX - Hitbox.SizeX / 2 - (OtherHitbox.PosX + OtherHitbox.SizeX / 2);
							int CollisionDepthY;
							if (Hitbox.PosY < OtherHitbox.PosY)
								CollisionDepthY = OtherHitbox.PosY - OtherHitbox.SizeY / 2 - (Hitbox.PosY + Hitbox.SizeY / 2);
							else
								CollisionDepthY = Hitbox.PosY - Hitbox.SizeY / 2 - (OtherHitbox.PosY + OtherHitbox.SizeY / 2);
							HitPosX = Hitbox.PosX - CollisionDepthX / 2;
							HitPosY = Hitbox.PosY - CollisionDepthY / 2;
							
							if (IsPlayer && OtherObj->IsPlayer)
							{
								Hitstop = 16;
								OtherObj->Hitstop = 16;
								AttackFlags &= ~ATK_HitActive;
								OtherObj->AttackFlags &= ~ATK_HitActive;
								OtherObj->HitPosX = HitPosX;
								OtherObj->HitPosY = HitPosY;
								Player->EnableAttacks();
								// Player->AddWhiffCancelOption(Player->GetCurrentStateName());
                                // Player->EnableWhiffCancel(true);
								TriggerEvent(EVT_HitOrBlock);
								OtherObj->Player->EnableAttacks();
								// OtherObj->Player->AddWhiffCancelOption(OtherObj->Player->GetCurrentStateName());
                                // OtherObj->Player->EnableWhiffCancel(true);
								OtherObj->TriggerEvent(EVT_HitOrBlock);
								CreateCommonParticle("cmn_hit_clash", POS_Hit, FVector(0, 0, 0));
                                // PlayCommonSound("HitClash");
								return;
							}
							if (!IsPlayer && !OtherObj->IsPlayer)
							{
								OtherObj->Hitstop = 16;
								Hitstop = 16;
								AttackFlags &= ~ATK_HitActive;
								OtherObj->AttackFlags &= ~ATK_HitActive;
								OtherObj->HitPosX = HitPosX;
								OtherObj->HitPosY = HitPosY;
								OtherObj->TriggerEvent(EVT_HitOrBlock);
								TriggerEvent(EVT_HitOrBlock);
								CreateCommonParticle("cmn_hit_clash", POS_Hit, FVector(0, 0, 0));
                                //PlayCommonSound("HitClash");
								return;
							}
							return;
						}
					}
				}
			}
		}
	}
}

void ABattleObject::HandleFlip()
{
	const EObjDir CurrentDir = Direction;
	if (!Player->Enemy) return;
	if (PosX < Player->Enemy->PosX)
	{
		SetFacing(DIR_Right);
	}
	else if (PosX > Player->Enemy->PosX)
	{
		SetFacing(DIR_Left);
	}
	if (CurrentDir != Direction)
	{
		SpeedX = -SpeedX;
		Inertia = -Inertia;
		if (IsPlayer)
		{
			Player->StoredInputBuffer.FlipInputsInBuffer();
			if (Player->Stance == ACT_Standing && Player->EnableFlags & ENB_Standing)
				Player->JumpToState("StandFlip");
			else if (Player->Stance == ACT_Crouching && Player->EnableFlags & ENB_Crouching)
				Player->JumpToState("CrouchFlip");
			else if (Player->EnableFlags & ENB_Jumping)
				Player->JumpToState("JumpFlip");
		}
	}
}

void ABattleObject::PosTypeToPosition(EPosType Type, int32* OutPosX, int32* OutPosY) const
{
	switch (Type)
	{
	case POS_Self:
		*OutPosX = PosX;
		*OutPosY = PosY;
		break;
	case POS_Player:
		*OutPosX = Player->PosX;
		*OutPosY = Player->PosY;
		break;
	case POS_Center:
		*OutPosX = PosX;
		*OutPosY = PosY + PushHeight;
		break;
	case POS_Enemy:
		*OutPosX = Player->Enemy->PosX;
		*OutPosY = Player->Enemy->PosY;
		break;
	case POS_Hit:
		*OutPosX = HitPosX;
		*OutPosY = HitPosY;
		break;
	default:
		break;
	}
}

void ABattleObject::TriggerEvent(EEventType EventType)
{
	UState* State = ObjectState;
	if (IsPlayer)
		State = Player->StoredStateMachine.CurrentState;
	UFunction* const Func = State->FindFunction(FName(EventHandlers[EventType].FunctionName.GetString()));
	if (IsValid(Func) && Func->ParmsSize == 0)
	{
		State->ProcessEvent(Func, nullptr);
	}
}

void ABattleObject::SaveForRollback(unsigned char* Buffer) const
{
	FMemory::Memcpy(Buffer, &ObjSync, SizeOfBattleObject);
}

void ABattleObject::LoadForRollback(const unsigned char* Buffer)
{
	FMemory::Memcpy(&ObjSync, Buffer, SizeOfBattleObject);
	if (!IsPlayer)
	{
		const int StateIndex = Player->ObjectStateNames.Find(ObjectStateName.GetString());
		if (StateIndex != INDEX_NONE)
		{
			ObjectState = DuplicateObject(Player->ObjectStates[StateIndex], this);
			ObjectState->Parent = this;
		}
	}
}

void ABattleObject::LogForSyncTestFile(FILE* file)
{
	if(file)
	{
		fprintf(file,"BattleActor:\n");
		fprintf(file,"\tPosX: %d\n", PosX);
		fprintf(file,"\tPosY: %d\n", PosY);
		fprintf(file,"\tPrevPosX: %d\n", PrevPosX);
		fprintf(file,"\tPrevPosY: %d\n", PrevPosY);
		fprintf(file,"\tSpeedX: %d\n", SpeedX);
		fprintf(file,"\tSpeedY: %d\n", SpeedY);
		fprintf(file,"\tGravity: %d\n", Gravity);
		fprintf(file,"\tInertia: %d\n", Inertia);
		fprintf(file,"\tActionTime: %d\n", ActionTime);
		fprintf(file,"\tPushHeight: %d\n", PushHeight);
		fprintf(file,"\tPushHeightLow: %d\n", PushHeightLow);
		fprintf(file,"\tPushWidth: %d\n", PushWidth);
		fprintf(file,"\tStunTime: %d\n", StunTime);
		fprintf(file,"\tHitstop: %d\n", Hitstop);
		fprintf(file,"\tCelName: %s\n", CelName.GetString());
		fprintf(file,"\tFacingRight: %d\n", AttackFlags);
		fprintf(file,"\tDirection: %d\n", static_cast<int>(Direction));
		fprintf(file,"\tMiscFlags: %d\n", MiscFlags);
		fprintf(file,"\tCelIndex: %d\n", CelIndex);
		fprintf(file,"\tTimeUntilNextCel: %d\n", TimeUntilNextCel);
		fprintf(file,"\tAnimFrame: %d\n", AnimFrame);
	}
}

void ABattleObject::UpdateVisualLocation()
{
	SetActorLocation(FVector(static_cast<float>(PosX) / COORD_SCALE, static_cast<float>(PosZ) / COORD_SCALE, static_cast<float>(PosY) / COORD_SCALE));
}

void ABattleObject::FuncCall(FName FuncName) const
{
	UState* CurrentState = ObjectState;
	if (IsPlayer)
		CurrentState = Player->StoredStateMachine.CurrentState;

	UFunction* const Func = CurrentState->FindFunction(FuncName);
	if (IsValid(Func) && Func->ParmsSize == 0)
	{
		CurrentState->ProcessEvent(Func, nullptr);
	}
}

void ABattleObject::GetBoxes()
{
	if (Player->CommonCollisionData != nullptr)
	{
		for (int i = 0; i < Player->CommonCollisionData->CollisionFrames.Num(); i++)
		{
			if (Player->CommonCollisionData->CollisionFrames[i].CelName == CelName.GetString())
			{
				AnimName.SetString(Player->CommonCollisionData->CollisionFrames[i].AnimName);
				AnimFrame = Player->CommonCollisionData->CollisionFrames[i].AnimFrame;
				for (int j = 0; j < CollisionArraySize; j++)
				{
					if (j < Player->CommonCollisionData->CollisionFrames[i].Boxes.Num())
					{
						FCollisionBox CollisionBoxInternal;
						CollisionBoxInternal.Type = Player->CommonCollisionData->CollisionFrames[i].Boxes[j].Type;
						CollisionBoxInternal.PosX = Player->CommonCollisionData->CollisionFrames[i].Boxes[j].PosX;
						CollisionBoxInternal.PosY = Player->CommonCollisionData->CollisionFrames[i].Boxes[j].PosY;
						CollisionBoxInternal.SizeX = Player->CommonCollisionData->CollisionFrames[i].Boxes[j].SizeX;
						CollisionBoxInternal.SizeY = Player->CommonCollisionData->CollisionFrames[i].Boxes[j].SizeY;
						Boxes[j] = CollisionBoxInternal;
					}
					else
					{
						Boxes[j].Type = BOX_Hurt;
						Boxes[j].PosX = -10000000;
						Boxes[j].PosY = -10000000;
						Boxes[j].SizeX = 0;
						Boxes[j].SizeY = 0;
					}
				}
				return;
			}
		}
		for (int j = 0; j < CollisionArraySize; j++)
		{
			Boxes[j].Type = BOX_Hurt;
			Boxes[j].PosX = -10000000;
			Boxes[j].PosY = -10000000;
			Boxes[j].SizeX = 0;
			Boxes[j].SizeY = 0;
		}
	}
	if (Player->CollisionData != nullptr)
	{
		for (int i = 0; i < Player->CollisionData->CollisionFrames.Num(); i++)
		{
			if (Player->CollisionData->CollisionFrames[i].CelName == CelName.GetString())
			{
				AnimName.SetString(Player->CollisionData->CollisionFrames[i].AnimName);
				AnimFrame = Player->CollisionData->CollisionFrames[i].AnimFrame;
				for (int j = 0; j < CollisionArraySize; j++)
				{
					if (j < Player->CollisionData->CollisionFrames[i].Boxes.Num())
					{
						FCollisionBox CollisionBoxInternal;
						CollisionBoxInternal.Type = Player->CollisionData->CollisionFrames[i].Boxes[j].Type;
						CollisionBoxInternal.PosX = Player->CollisionData->CollisionFrames[i].Boxes[j].PosX;
						CollisionBoxInternal.PosY = Player->CollisionData->CollisionFrames[i].Boxes[j].PosY;
						CollisionBoxInternal.SizeX = Player->CollisionData->CollisionFrames[i].Boxes[j].SizeX;
						CollisionBoxInternal.SizeY = Player->CollisionData->CollisionFrames[i].Boxes[j].SizeY;
						Boxes[j] = CollisionBoxInternal;
					}
					else
					{
						Boxes[j].Type = BOX_Hurt;
						Boxes[j].PosX = -10000000;
						Boxes[j].PosY = -10000000;
						Boxes[j].SizeX = 0;
						Boxes[j].SizeY = 0;
					}
				}
				return;
			}
		}
		for (int j = 0; j < CollisionArraySize; j++)
		{
			Boxes[j].Type = BOX_Hurt;
			Boxes[j].PosX = -10000000;
			Boxes[j].PosY = -10000000;
			Boxes[j].SizeX = 0;
			Boxes[j].SizeY = 0;
		}
	}
}

void ABattleObject::InitObject()
{
	if (IsPlayer)
		return;
	ObjectState->Parent = this;
	SetActorLocation(FVector(static_cast<float>(PosX) / COORD_SCALE, static_cast<float>(PosZ) / COORD_SCALE, static_cast<float>(PosY) / COORD_SCALE)); //set visual location and scale in unreal
	if (Direction == DIR_Left)
	{
		SetActorScale3D(FVector(-1, 1, 1));
	}
	else
	{
		SetActorScale3D(FVector(1, 1, 1));
	}
}

void ABattleObject::Update()
{
	if (Direction == DIR_Left)
	{
		SetActorScale3D(FVector(-1, 1, 1));
	}
	else
	{
		SetActorScale3D(FVector(1, 1, 1));
	}

	L = PosX - PushWidth / 2; //sets pushboxes
	R = PosX + PushWidth / 2;
	if (Direction == DIR_Right)
		R += PushWidthFront;
	else
		L -= PushWidthFront;
	T = PosY + PushHeight;
	B = PosY - PushHeightLow;
	
	if (SuperFreezeTimer > 0)
	{
		if (SuperFreezeTimer == 1)
		{
			TriggerEvent(EVT_SuperFreezeEnd);
		}
		SuperFreezeTimer--;
		return;
	}
		
	if (Hitstop > 0) //break if hitstop active.
	{
		Hitstop--;
		return;
	}
	
	if (MiscFlags & MISC_FlipEnable)
		HandleFlip();

	TriggerEvent(EVT_Update);
	Move();
	
	if (PosY == GroundHeight && PrevPosY != GroundHeight)
	{
		TriggerEvent(EVT_Landing);
		SpeedX = 0;
	}

	if (!IsPlayer)
	{
		if (ActionTime == 0)
		{
			TriggerEvent(EVT_Enter);
		}
		
		ObjectState->CallExec();
		TimeUntilNextCel--;
		if (TimeUntilNextCel == 0)
			CelIndex++;
		
		GetBoxes();
	}

	ActionTime++;
	
	UpdateVisualLocation();
}

void ABattleObject::ResetObject()
{
	if (IsPlayer)
		return;
	IsActive = false;
	PosX = 0;
	PosY = 0;
	PosZ = 0;
	PrevPosX = 0;
	PrevPosY = 0;
	PrevPosZ = 0;
	SpeedX = 0;
	SpeedY = 0;
	SpeedZ = 0;
	Gravity = 1900;
	Inertia = 0;
	ActionTime = 0;
	PushHeight = 0;
	PushHeightLow = 0;
	PushWidth = 0;
	PushWidthFront  = 0;
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
	AttackFlags = ATK_AttackProjectileAttribute;
	StunTime = 0;
	Hitstop = 0;
	MiscFlags = 0;
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
	IsPlayer = false;
	SuperFreezeTimer = 0;
	CelName.SetString("");
	AnimName.SetString("");
	AnimFrame = 0;
	CelIndex = 0;
	TimeUntilNextCel = 0;
	for (auto& Handler : EventHandlers)
		Handler = FEventHandler();
	EventHandlers[EVT_Enter].FunctionName.SetString("Init");	
	HitPosX = 0;
	HitPosY = 0;
	for (auto& Box : Boxes)
	{
		Box = FCollisionBox();
	}
	ObjectStateName.SetString("");
	ObjectID = 0;
	Player = nullptr;
}

void ABattleObject::InitEventHandler(EEventType EventType, FName FuncName)
{
	EventHandlers[EventType].FunctionName.SetString(FuncName.ToString());
}

void ABattleObject::RemoveEventHandler(EEventType EventType)
{
	EventHandlers[EventType].FunctionName.SetString("");
}

FString ABattleObject::GetCelName()
{
	return CelName.GetString();
}

FString ABattleObject::GetAnimName()
{
	return AnimName.GetString();
}

FString ABattleObject::GetLabelName()
{
	return LabelName.GetString();
}

void ABattleObject::SetCelName(FString InName)
{
	CelName.SetString(InName);
}

void ABattleObject::GotoLabel(FString InName, bool ResetState)
{
	LabelName.SetString(InName);
	if (IsPlayer && ResetState)
		Player->JumpToState(Player->GetCurrentStateName(), true);
	else
		GotoLabelActive = true;
}

void ABattleObject::AddPosXWithDir(int InPosX)
{
	if (Direction == DIR_Right)
	{
		PosX += InPosX;
	}
	else
	{
		PosX -= InPosX;
	}
}

void ABattleObject::SetSpeedXRaw(int InSpeedX)
{
	if (Direction == DIR_Right)
	{
		SpeedX = InSpeedX;
	}
	else
	{
		SpeedX = -InSpeedX;
	}
}

void ABattleObject::AddSpeedXRaw(int InSpeedX)
{
	if (Direction == DIR_Right)
	{
		SpeedX += InSpeedX;
	}
	else
	{
		SpeedX -= InSpeedX;
	}
}

int32 ABattleObject::CalculateDistanceBetweenPoints(EDistanceType Type, EObjType Obj1, EPosType Pos1, EObjType Obj2,
	EPosType Pos2)
{
	ABattleObject* Actor1 = GetBattleObject(Obj1);
	ABattleObject* Actor2 = GetBattleObject(Obj2);
	if (IsValid(Actor1) && IsValid(Actor2))
	{
		int32 PosX1 = 0;
		int32 PosX2 = 0;
		int32 PosY1 = 0;
		int32 PosY2 = 0;

		Actor1->PosTypeToPosition(Pos1, &PosX1, &PosY1);
		Actor2->PosTypeToPosition(Pos2, &PosX2, &PosY2);

		int32 ObjDist;
		
		switch (Type)
		{
		case DIST_Distance:
			ObjDist = isqrt(static_cast<int64>(PosX2 - PosX1) * static_cast<int64>(PosX2 - PosX1) + static_cast<int64>(PosY2 - PosY1) * static_cast<int64>(PosY2 - PosY1));
			break;
		case DIST_DistanceX:
			ObjDist = abs(PosX2 - PosX1);
			break;
		case DIST_DistanceY:
			ObjDist = abs(PosY2 - PosY1);
			break;
		case DIST_FrontDistanceX:
			{
				int DirFlag = 1;
				if (Actor1->Direction == DIR_Left)
				{
					DirFlag = -1;
				}
				ObjDist = abs(PosX2 - PosX1) * DirFlag;
			}
			break;
		default:
			return 0;
		}
		return ObjDist;
	}
	return 0;
}

void ABattleObject::SetFacing(EObjDir NewDir)
{
	Direction = NewDir;
}

void ABattleObject::FlipCharacter()
{
	if (Direction == DIR_Right)
		Direction = DIR_Left;
	else
		Direction = DIR_Right;
}

void ABattleObject::FaceOpponent()
{
	const EObjDir CurrentDir = Direction;
	if (!Player->Enemy) return;
	if (PosX < Player->Enemy->PosX)
	{
		SetFacing(DIR_Right);
	}
	else if (PosX > Player->Enemy->PosX)
	{
		SetFacing(DIR_Left);
	}
	if (CurrentDir != Direction)
	{
		SpeedX = -SpeedX;
		Inertia = -Inertia;
	}
}

void ABattleObject::EnableHit(bool Enabled)
{
	if (Enabled)
	{
		AttackFlags |= ATK_HitActive;
	}
	else
	{
		AttackFlags &= ~ATK_HitActive;
	}
	AttackFlags &= ~ATK_HasHit;
}

void ABattleObject::SetAttacking(bool Attacking)
{
	if (Attacking)
	{
		AttackFlags |= ATK_IsAttacking;
	}
	else
	{
		AttackFlags &= ~ATK_IsAttacking;
	}
	AttackFlags &= ~ATK_HasHit;
}

void ABattleObject::DeactivateObject()
{
	if (IsPlayer) // Don't use on players
		return;
	// Remove from player cache
	for (int i = 0; i < 32; i++)
	{
		if (this == Player->ChildBattleObjects[i])
		{
			Player->ChildBattleObjects[i] = nullptr;
			break;
		}
	}
	for (int i = 0; i < 16; i++)
	{
		if (this == Player->StoredBattleObjects[i])
		{
			Player->StoredBattleObjects[i] = nullptr;
			break;
		}
	}

	// Wait until the next frame to complete
	MiscFlags |= MISC_DeactivateOnNextUpdate;
}

void ABattleObject::EnableFlip(bool Enabled)
{
	if (Enabled)
	{
		MiscFlags |= MISC_FlipEnable;
	}
	else
	{
		MiscFlags = MiscFlags & ~MISC_FlipEnable;
	}
}

void ABattleObject::EnableInertia()
{
	MiscFlags |= MISC_InertiaEnable;
}

void ABattleObject::DisableInertia()
{
	MiscFlags = MiscFlags & ~MISC_InertiaEnable;
}

void ABattleObject::HaltMomentum()
{
	SpeedX = 0;
	SpeedY = 0;
	SpeedZ = 0;
	Gravity = 0;
	Inertia = 0;
}

void ABattleObject::CreateCommonParticle(FString Name, EPosType PosType, FVector Offset, FRotator Rotation)
{
	if (Player->CommonParticleData != nullptr)
	{
		for (FParticleStruct ParticleStruct : Player->CommonParticleData->ParticleStructs)
		{
			if (ParticleStruct.Name == Name)
			{
				if (Direction == DIR_Left)
				{
					Rotation.Pitch = -Rotation.Pitch;
					Offset = FVector(-Offset.X, Offset.Y, Offset.Z);
				}
				int32 TmpPosX;
				int32 TmpPosY;
				PosTypeToPosition(PosType, &TmpPosX, &TmpPosY);
				const FVector FinalLocation = Offset + FVector(TmpPosX / COORD_SCALE, 0, TmpPosY / COORD_SCALE);
				if (UNiagaraSystem* NiagaraSystem = Cast<UNiagaraSystem>(ParticleStruct.ParticleSystem); IsValid(NiagaraSystem))
				{
					GameState->ParticleManager->NiagaraComponents.Add(UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, NiagaraSystem, FinalLocation, Rotation, GetActorScale()));
					UNiagaraComponent* NiagaraComponent = Cast<UNiagaraComponent>(GameState->ParticleManager->NiagaraComponents.Last());
					NiagaraComponent->SetAgeUpdateMode(ENiagaraAgeUpdateMode::DesiredAge);
					NiagaraComponent->SetNiagaraVariableFloat("SpriteRotate", -Rotation.Pitch);
					if (Direction == DIR_Left)
					{
						NiagaraComponent->SetNiagaraVariableVec2("UVScale", FVector2D(-1, 1));
						NiagaraComponent->SetNiagaraVariableVec2("PivotOffset", FVector2D(0, 0.5));
					}
				}
				break;
			}
		}
	}
}

void ABattleObject::CreateCharaParticle(FString Name, EPosType PosType, FVector Offset, FRotator Rotation)
{
	if (Player->CharaParticleData != nullptr)
	{
		for (FParticleStruct ParticleStruct : Player->CharaParticleData->ParticleStructs)
		{
			if (ParticleStruct.Name == Name)
			{
				if (Direction == DIR_Left)
					Offset = FVector(-Offset.X, Offset.Y, Offset.Z);
				int32 TmpPosX;
				int32 TmpPosY;
				PosTypeToPosition(PosType, &TmpPosX, &TmpPosY);
				const FVector FinalLocation = Offset + FVector(TmpPosX / COORD_SCALE, 0, TmpPosY / COORD_SCALE);
				if (UNiagaraSystem* NiagaraSystem = Cast<UNiagaraSystem>(ParticleStruct.ParticleSystem); IsValid(NiagaraSystem))
				{
					GameState->ParticleManager->NiagaraComponents.Add(UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, NiagaraSystem, FinalLocation, Rotation, GetActorScale()));
					UNiagaraComponent* NiagaraComponent = Cast<UNiagaraComponent>(GameState->ParticleManager->NiagaraComponents.Last());
					NiagaraComponent->SetAgeUpdateMode(ENiagaraAgeUpdateMode::DesiredAge);
					NiagaraComponent->SetNiagaraVariableFloat("SpriteRotate", Rotation.Pitch);
					if (Direction == DIR_Left)
					{
						NiagaraComponent->SetNiagaraVariableVec2("UVScale", FVector2D(-1, 1));
						NiagaraComponent->SetNiagaraVariableVec2("PivotOffset", FVector2D(0, 0.5));
						NiagaraComponent->SetNiagaraVariableFloat("SpriteRotate", -Rotation.Pitch);
					}
				}
				break;
			}
		}
	}
}

ABattleObject* ABattleObject::GetBattleObject(EObjType Type)
{
	switch (Type)
	{
	case OBJ_Self:
		return this;
	case OBJ_Enemy:
		return Player->Enemy;
	case OBJ_Parent:
		return Player;
	case OBJ_Child0:
		if (IsPlayer && Player->StoredBattleObjects[0])
			if (Player->StoredBattleObjects[0]->IsActive)
				return Player->StoredBattleObjects[0];
		return nullptr;
	case OBJ_Child1:
		if (IsPlayer && Player->StoredBattleObjects[1])
			if (Player->StoredBattleObjects[1]->IsActive)
				return Player->StoredBattleObjects[1];
		return nullptr;
	case OBJ_Child2:
		if (IsPlayer && Player->StoredBattleObjects[2])
			if (Player->StoredBattleObjects[2]->IsActive)
				return Player->StoredBattleObjects[2];
		return nullptr;
	case OBJ_Child3:
		if (IsPlayer && Player->StoredBattleObjects[3])
			if (Player->StoredBattleObjects[3]->IsActive)
				return Player->StoredBattleObjects[3];
		return nullptr;
	case OBJ_Child4:
		if (IsPlayer && Player->StoredBattleObjects[4])
			if (Player->StoredBattleObjects[4]->IsActive)
				return Player->StoredBattleObjects[4];
		return nullptr;
	case OBJ_Child5:
		if (IsPlayer && Player->StoredBattleObjects[5])
			if (Player->StoredBattleObjects[5]->IsActive)
				return Player->StoredBattleObjects[5];
		return nullptr;
	case OBJ_Child6:
		if (IsPlayer && Player->StoredBattleObjects[6])
			if (Player->StoredBattleObjects[6]->IsActive)
				return Player->StoredBattleObjects[6];
		return nullptr;
	case OBJ_Child7:
		if (IsPlayer && Player->StoredBattleObjects[7])
			if (Player->StoredBattleObjects[7]->IsActive)
				return Player->StoredBattleObjects[7];
		return nullptr;
	case OBJ_Child8:
		if (IsPlayer && Player->StoredBattleObjects[8])
			if (Player->StoredBattleObjects[8]->IsActive)
				return Player->StoredBattleObjects[8];
		return nullptr;
	case OBJ_Child9:
		if (IsPlayer && Player->StoredBattleObjects[9])
			if (Player->StoredBattleObjects[9]->IsActive)
				return Player->StoredBattleObjects[9];
		return nullptr;
	case OBJ_Child10:
		if (IsPlayer && Player->StoredBattleObjects[10])
			if (Player->StoredBattleObjects[10]->IsActive)
				return Player->StoredBattleObjects[10];
		return nullptr;
	case OBJ_Child11:
		if (IsPlayer && Player->StoredBattleObjects[11])
			if (Player->StoredBattleObjects[11]->IsActive)
				return Player->StoredBattleObjects[11];
		return nullptr;
	case OBJ_Child12:
		if (IsPlayer && Player->StoredBattleObjects[12])
			if (Player->StoredBattleObjects[12]->IsActive)
				return Player->StoredBattleObjects[12];
		return nullptr;
	case OBJ_Child13:
		if (IsPlayer && Player->StoredBattleObjects[13])
			if (Player->StoredBattleObjects[13]->IsActive)
				return Player->StoredBattleObjects[13];
		return nullptr;
	case OBJ_Child14:
		if (IsPlayer && Player->StoredBattleObjects[14])
			if (Player->StoredBattleObjects[14]->IsActive)
				return Player->StoredBattleObjects[14];
		return nullptr;
	case OBJ_Child15:
		if (IsPlayer && Player->StoredBattleObjects[15])
			if (Player->StoredBattleObjects[15]->IsActive)
				return Player->StoredBattleObjects[15];
		return nullptr;
	default:
		return nullptr;
	}
}
