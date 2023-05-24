// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleObject.h"

#include "PlayerObject.h"
#include "NightSkyEngine/Battle/Bitflags.h"
#include "NightSkyEngine/Battle/Globals.h"

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
		if (Player->Stance == ACT_Crouching)
			ModifiedPushback = Player->Pushback * 86;
		else
			ModifiedPushback = Player->Pushback * 88;

		Player->Pushback = ModifiedPushback / 100;
		
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
		SpeedY = 0;
	}
	if (MiscFlags & MISC_WallCollisionActive)
	{
		if (PosX < -1800000)
		{
			PosX = -1800000;
		}
		else if (PosX > 1800000)
		{
			PosX = 1800000;
		}
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
				const int PosXOffset = CollisionDepth / 2;
				PosX += PosXOffset;
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
								OtherChar->HandleFlip();
								OtherChar->PlayerFlags |= PLF_IsStunned;
								OtherChar->HaltMomentum();
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

								if ((OtherChar->EnableFlags & ENB_Block || OtherChar->StoredStateMachine.CurrentState->StateType == EStateType::Blockstun)
									&& OtherChar->IsCorrectBlock(HitCommon.BlockType)) //check blocking
								{
									/* CreateCommonParticle("cmn_guard", POS_Hit, FVector(-50, 0, 0), FRotator(-HitEffect.HitAngle, 0, 0));
									if (HitEffect.AttackLevel < 1)
									{
										switch (HitEffect.SFXType)
										{
										case EHitSFXType::SFX_Kick:
											PlayCommonSound("GuardMeleeAltS");
											break;
										case EHitSFXType::SFX_Slash:
											PlayCommonSound("GuardSlashS");
											break;
										case EHitSFXType::SFX_Punch:
										default:
											PlayCommonSound("GuardMeleeS");
											break;
										}
									}
									else if (HitEffect.AttackLevel < 3)
									{
										switch (HitEffect.SFXType)
										{
										case EHitSFXType::SFX_Kick:
											PlayCommonSound("GuardMeleeAltM");
											break;
										case EHitSFXType::SFX_Slash:
											PlayCommonSound("GuardSlashM");
											break;
										case EHitSFXType::SFX_Punch:
										default:
											PlayCommonSound("GuardMeleeM");
											break;
										}
									}
									else
									{
										switch (HitEffect.SFXType)
										{
										case EHitSFXType::SFX_Kick:
											PlayCommonSound("GuardMeleeAltL");
											break;
										case EHitSFXType::SFX_Slash:
											PlayCommonSound("GuardSlashL");
											break;
										case EHitSFXType::SFX_Punch:
										default:
											PlayCommonSound("GuardMeleeL");
											break;
										}
									}*/
									TriggerEvent(EVT_Block);
									
									OtherChar->Hitstop = HitCommon.Hitstop;
									OtherChar->StunTime = HitCommon.Blockstun;
									Hitstop = HitCommon.Hitstop;
									const int32 ChipDamage = NormalHit.Damage * HitCommon.ChipDamagePercent / 100;
									OtherChar->CurrentHealth -= ChipDamage;
									if (OtherChar->CurrentHealth <= 0)
									{
										EHitAction HACT;
										
										if (OtherChar->PosY == OtherChar->GroundHeight && !(OtherChar->PlayerFlags & PLF_IsKnockedDown))
											HACT = NormalHit.GroundHitAction;
										else
											HACT = NormalHit.AirHitAction;

										const FHitData Data = InitHitDataByAttackLevel(false);
										OtherChar->ReceivedHitCommon = HitCommon;
										OtherChar->ReceivedHit = Data;
										OtherChar->HandleHitAction(HACT);
									}
									else
									{
										if (OtherChar->PosY <= OtherChar->GroundHeight)
										{
											OtherChar->Pushback = -HitCommon.GroundGuardPushbackX;
											if (OtherChar->PlayerFlags & PLF_TouchingWall)
											{
												Pushback = OtherChar->Pushback;
												OtherChar->Pushback = 0;
											}
										}
										else
										{
											OtherChar->SpeedX = -HitCommon.AirGuardPushbackX;
											OtherChar->SpeedY = HitCommon.AirGuardPushbackY;
											OtherChar->Gravity = HitCommon.GuardGravity;
											if (OtherChar->PlayerFlags & PLF_TouchingWall)
											{
												Pushback = OtherChar->Pushback;
												OtherChar->Pushback = 0;
											}
											OtherChar->AirDashTimer = 0;
										}
										OtherChar->HandleBlockAction(HitCommon.BlockType);
									}
									// OtherChar->AddMeter(HitEffect.HitDamage * OtherChar->MeterPercentOnReceiveHitGuard / 100);
									// Player->AddMeter(HitEffect.HitDamage * Player->MeterPercentOnHitGuard / 100);
								}
								else if ((OtherChar->AttackFlags & ATK_IsAttacking) == 0)
								{
									TriggerEvent(EVT_Hit);
									EHitAction HACT;
										
									if (OtherChar->PosY == OtherChar->GroundHeight && !(OtherChar->PlayerFlags & PLF_IsKnockedDown))
										HACT = NormalHit.GroundHitAction;
									else
										HACT = NormalHit.AirHitAction;

									const FHitData Data = InitHitDataByAttackLevel(false);
									OtherChar->ReceivedHitCommon = HitCommon;
									OtherChar->ReceivedHit = Data;
									OtherChar->HandleHitAction(HACT);
								}
								else
								{
									TriggerEvent(EVT_Hit);
									TriggerEvent(EVT_CounterHit);
									EHitAction HACT;
										
									if (OtherChar->PosY == OtherChar->GroundHeight && !(OtherChar->PlayerFlags & PLF_IsKnockedDown))
										HACT = CounterHit.GroundHitAction;
									else
										HACT = CounterHit.AirHitAction;
									
									const FHitData Data = InitHitDataByAttackLevel(true);
									OtherChar->ReceivedHitCommon = HitCommon;
									OtherChar->ReceivedHit = Data;
									OtherChar->HandleHitAction(HACT);
								}
								if (OtherChar->PosX < PosX)
								{
									OtherChar->SetFacing(DIR_Right);
								}
								else if (OtherChar->PosX > PosX)
								{
									OtherChar->SetFacing(DIR_Left);
								}
								OtherChar->Move();
								OtherChar->DisableAll();
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
	FHitData Data;
	if (!IsCounter)
		Data = CounterHit;
	else
		Data = NormalHit;

	if (HitCommon.AttackLevel < 0)
		HitCommon.AttackLevel = 0;
	if (HitCommon.AttackLevel > 4)
		HitCommon.AttackLevel = 5;
	
	switch (HitCommon.AttackLevel)
	{
	case 0:
	default:
		if (HitCommon.Hitstop == -1)
			HitCommon.Hitstop = 11;
		if (HitCommon.BlockstopModifier == -1)
			HitCommon.BlockstopModifier = 0;
		if (HitCommon.Blockstun == -1)
			HitCommon.Blockstun = 9;
		if (HitCommon.GroundGuardPushbackX == -1)
			HitCommon.GroundGuardPushbackX = 10000;
		if (HitCommon.AirGuardPushbackX == -1)
			HitCommon.AirGuardPushbackX = 15000;
		if (HitCommon.AirGuardPushbackY == -1)
			HitCommon.AirGuardPushbackY = 30000;
		if (HitCommon.GuardGravity == -1)
			HitCommon.GuardGravity = 1900;
		if (Data.Hitstun == -1)
			Data.Hitstun = 10;
		if (Data.Untech == -1)
			Data.Untech = 10;
		if (Data.Damage == -1)
			Data.Damage = 300;
		if (Data.GroundPushbackX == -1)
			Data.GroundPushbackX = 12500;
		if (Data.AirPushbackX == -1)
			Data.AirPushbackX = 15000;
		if (Data.AirPushbackY == -1)
			Data.AirPushbackY = 30000;
		if (Data.Gravity == -1)
			Data.Gravity = 1900;
		break;
	case 1:
		if (HitCommon.Hitstop == -1)
			HitCommon.Hitstop = 12;
		if (HitCommon.BlockstopModifier == -1)
			HitCommon.BlockstopModifier = 0;
		if (HitCommon.Blockstun == -1)
			HitCommon.Blockstun = 11;
		if (HitCommon.GroundGuardPushbackX == -1)
			HitCommon.GroundGuardPushbackX = 11250;
		if (HitCommon.AirGuardPushbackX == -1)
			HitCommon.AirGuardPushbackX = 15000;
		if (HitCommon.AirGuardPushbackY == -1)
			HitCommon.AirGuardPushbackY = 30050;
		if (HitCommon.GuardGravity == -1)
			HitCommon.GuardGravity = 1900;
		if (Data.Hitstun == -1)
			Data.Hitstun = 12;
		if (Data.Untech == -1)
			Data.Untech = 12;
		if (Data.Damage == -1)
			Data.Damage = 400;
		if (Data.GroundPushbackX == -1)
			Data.GroundPushbackX = 13750;
		if (Data.AirPushbackX == -1)
			Data.AirPushbackX = 15000;
		if (Data.AirPushbackY == -1)
			Data.AirPushbackY = 30050;
		if (Data.Gravity == -1)
			Data.Gravity = 1900;
		break;
	case 2:
		if (HitCommon.Hitstop == -1)
			HitCommon.Hitstop = 13;
		if (HitCommon.BlockstopModifier == -1)
			HitCommon.BlockstopModifier = 0;
		if (HitCommon.Blockstun == -1)
			HitCommon.Blockstun = 13;
		if (HitCommon.GroundGuardPushbackX == -1)
			HitCommon.GroundGuardPushbackX = 13500;
		if (HitCommon.AirGuardPushbackX == -1)
			HitCommon.AirGuardPushbackX = 15000;
		if (HitCommon.AirGuardPushbackY == -1)
			HitCommon.AirGuardPushbackY = 30100;
		if (HitCommon.GuardGravity == -1)
			HitCommon.GuardGravity = 1900;
		if (Data.Hitstun == -1)
			Data.Hitstun = 14;
		if (Data.Untech == -1)
			Data.Untech = 14;
		if (Data.Damage == -1)
			Data.Damage = 600;
		if (Data.GroundPushbackX == -1)
			Data.GroundPushbackX = 15000;
		if (Data.AirPushbackX == -1)
			Data.AirPushbackX = 15000;
		if (Data.AirPushbackY == -1)
			Data.AirPushbackY = 30100;
		if (Data.Gravity == -1)
			Data.Gravity = 1900;
		break;
	case 3:
		if (HitCommon.Hitstop == -1)
			HitCommon.Hitstop = 14;
		if (HitCommon.BlockstopModifier == -1)
			HitCommon.BlockstopModifier = 0;
		if (HitCommon.Blockstun == -1)
			HitCommon.Blockstun = 16;
		if (HitCommon.GroundGuardPushbackX == -1)
			HitCommon.GroundGuardPushbackX = 15000;
		if (HitCommon.AirGuardPushbackX == -1)
			HitCommon.AirGuardPushbackX = 15000;
		if (HitCommon.AirGuardPushbackY == -1)
			HitCommon.AirGuardPushbackY = 30150;
		if (HitCommon.GuardGravity == -1)
			HitCommon.GuardGravity = 1900;
		if (Data.Hitstun == -1)
			Data.Hitstun = 17;
		if (Data.Untech == -1)
			Data.Untech = 16;
		if (Data.Damage == -1)
			Data.Damage = 800;
		if (Data.GroundPushbackX == -1)
			Data.GroundPushbackX = 17500;
		if (Data.AirPushbackX == -1)
			Data.AirPushbackX = 15000;
		if (Data.AirPushbackY == -1)
			Data.AirPushbackY = 30150;
		if (Data.Gravity == -1)
			Data.Gravity = 1900;
		break;
	case 4:
		if (HitCommon.Hitstop == -1)
			HitCommon.Hitstop = 15;
		if (HitCommon.BlockstopModifier == -1)
			HitCommon.BlockstopModifier = 0;
		if (HitCommon.Blockstun == -1)
			HitCommon.Blockstun = 18;
		if (HitCommon.GroundGuardPushbackX == -1)
			HitCommon.GroundGuardPushbackX = 17500;
		if (HitCommon.AirGuardPushbackX == -1)
			HitCommon.AirGuardPushbackX = 15000;
		if (HitCommon.AirGuardPushbackY == -1)
			HitCommon.AirGuardPushbackY = 30200;
		if (HitCommon.GuardGravity == -1)
			HitCommon.GuardGravity = 1900;
		if (Data.Hitstun == -1)
			Data.Hitstun = 19;
		if (Data.Untech == -1)
			Data.Untech = 18;
		if (Data.Damage == -1)
			Data.Damage = 1000;
		if (Data.GroundPushbackX == -1)
			Data.GroundPushbackX = 20000;
		if (Data.AirPushbackX == -1)
			Data.AirPushbackX = 15000;
		if (Data.AirPushbackY == -1)
			Data.AirPushbackY = 30200;
		if (Data.Gravity == -1)
			Data.Gravity = 1900;
		break;
	case 5:
		if (HitCommon.Hitstop == -1)
			HitCommon.Hitstop = 18;
		if (HitCommon.BlockstopModifier == -1)
			HitCommon.BlockstopModifier = 0;
		if (HitCommon.Blockstun == -1)
			HitCommon.Blockstun = 20;
		if (HitCommon.GroundGuardPushbackX == -1)
			HitCommon.GroundGuardPushbackX = 22500;
		if (HitCommon.AirGuardPushbackX == -1)
			HitCommon.AirGuardPushbackX = 15000;
		if (HitCommon.AirGuardPushbackY == -1)
			HitCommon.AirGuardPushbackY = 30250;
		if (HitCommon.GuardGravity == -1)
			HitCommon.GuardGravity = 1900;
		if (Data.Hitstun == -1)
			Data.Hitstun = 22;
		if (Data.Untech == -1)
			Data.Untech = 21;
		if (Data.Damage == -1)
			Data.Damage = 1250;
		if (Data.GroundPushbackX == -1)
			Data.GroundPushbackX = 25000;
		if (Data.AirPushbackX == -1)
			Data.AirPushbackX = 15000;
		if (Data.AirPushbackY == -1)
			Data.AirPushbackY = 30200;
		if (Data.Gravity == -1)
			Data.Gravity = 30250;
		break;
	}

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
								// CreateCommonParticle("cmn_hit_clash", POS_Hit, FVector(-50, 0, 0));
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
								//CreateCommonParticle("cmn_hit_clash", POS_Hit, FVector(-50, 0, 0));
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
	EObjDir CurrentDir = Direction;
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
	
	GetBoxes();
	
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
	ReturnReg = 0;
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
	GotoLabelActive = true;
	if (IsPlayer && ResetState)
		Player->JumpToState(Player->GetCurrentStateName());
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
	EObjDir CurrentDir = Direction;
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
