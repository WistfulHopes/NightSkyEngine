// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleObject.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NightSkyEngine/Battle/NightSkyBlueprintFunctionLibrary.h"
#include "NightSkyGameState.h"
#include "ParticleManager.h"
#include "PlayerObject.h"
#include "NightSkyEngine/Battle/Bitflags.h"
#include "NightSkyEngine/Battle/Globals.h"
#include "NightSkyEngine/Battle/Subroutine.h"
#include "NightSkyEngine/Data/CameraShakeData.h"
#include "NightSkyEngine/Data/ParticleData.h"
#include "NightSkyEngine/Battle/RandomManager.h"

// Sets default values
ABattleObject::ABattleObject()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");
	
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
	if (IsPlayer)
	{
		if (Player->PlayerFlags & PLF_IsThrowLock)
			return;
		Player->SetHitValuesOverTime();
	}
	else if (PositionLinkObj)
	{
		PrevPosX = PositionLinkObj->PrevPosX;
		PrevPosY = PositionLinkObj->PrevPosY;
		PosX = PositionLinkObj->PosX;
		PosY = PositionLinkObj->PosY;
		return;
	}
	
	// Set previous pos values
	PrevPosX = PosX;
	PrevPosY = PosY;
	CalculateHoming();
	
	if (BlendOffset && BlendCelName != FName("None") && MaxCelTime)
	{
		const int32 TmpOffsetX = (NextOffsetX - PrevOffsetX) * (MaxCelTime - TimeUntilNextCel) / MaxCelTime;
		const int32 TmpOffsetY = (NextOffsetY - PrevOffsetY) * (MaxCelTime - TimeUntilNextCel) / MaxCelTime;
		
		AddPosXWithDir(TmpOffsetX);
		PosY += TmpOffsetY;
	}
	
	SpeedX = SpeedX * SpeedXRatePerFrame / 100;
	SpeedY = SpeedY * SpeedYRatePerFrame / 100;
	SpeedZ = SpeedZ * SpeedZRatePerFrame / 100;
	SpeedX = SpeedX * SpeedXRate / 100;
	SpeedY = SpeedY * SpeedYRate / 100;
	SpeedZ = SpeedZ * SpeedZRate / 100;

	SpeedXRate = SpeedYRate = SpeedZRate = 100;
	
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

	AddPosXWithDir(SpeedX); //apply speed

	if (IsPlayer && Player != nullptr)
	{
		if (Player->AirDashTimer == 0 || (SpeedY > 0 && ActionTime < 5)) // only set y speed if not airdashing/airdash startup not done
		{
			PosY += SpeedY;
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
		PosY += SpeedY;
		if (PosY > GroundHeight || !(MiscFlags & MISC_FloorCollisionActive))
			SpeedY -= Gravity;
	}
		
	if (PosY < GroundHeight && MiscFlags & MISC_FloorCollisionActive) //if on ground, force y values to zero
	{
		PosY = GroundHeight;
	}

	PosZ += SpeedZ;
}

void ABattleObject::CalculateHoming()
{
	if (HomingParams.Target != OBJ_Null)
	{
		ABattleObject* Target = GetBattleObject(HomingParams.Target);

		if (Target != nullptr)
		{
			int32 TargetPosX = 0;
			int32 TargetPosY = 0;

			Target->PosTypeToPosition(HomingParams.Pos, &TargetPosX, &TargetPosY);

			const bool TargetFacingRight = Target->Direction == DIR_Right;
			int32 HomingOffsetX = -HomingParams.OffsetX;
			if (!TargetFacingRight)
				HomingOffsetX = HomingParams.OffsetX;
			
			if (HomingParams.Type == HOMING_DistanceAccel)
			{
				int32 TmpPosY = TargetPosY + HomingParams.OffsetY - PosY;
				int32 TmpPosX = TargetPosX + HomingOffsetX - PosX;
				SpeedXRatePerFrame = HomingParams.ParamB;
				SpeedYRatePerFrame = HomingParams.ParamB;
				AddSpeedXRaw(HomingParams.ParamA * TmpPosX / 100);
				SpeedY += HomingParams.ParamA * TmpPosY / 100;
			}
			else if (HomingParams.Type == HOMING_FixAccel)
			{
				int32 TmpPosY = TargetPosY + HomingParams.OffsetY - PosY;
				int32 TmpPosX = TargetPosX + HomingOffsetX - PosX;
				int32 Angle = UNightSkyBlueprintFunctionLibrary::Vec2Angle_x1000(TmpPosX, TmpPosY) / 100;
				SpeedXRate = HomingParams.ParamB;
				SpeedYRate = HomingParams.ParamB;
				int32 CosParamA = HomingParams.ParamA * UNightSkyBlueprintFunctionLibrary::Cos_x1000(Angle) / 1000; 
				int32 SinParamA = HomingParams.ParamA * UNightSkyBlueprintFunctionLibrary::Sin_x1000(Angle) / 1000; 
				AddSpeedXRaw(CosParamA);
				SpeedY += SinParamA;
			}
			else if (HomingParams.Type == HOMING_ToSpeed)
			{
				int32 TmpPosY = TargetPosY + HomingParams.OffsetY - PosY;
				int32 TmpPosX = TargetPosX + HomingOffsetX - PosX;
				int32 Angle = UNightSkyBlueprintFunctionLibrary::Vec2Angle_x1000(TmpPosX, TmpPosY) / 100;
				int32 CosParamA = (Direction == DIR_Right ? HomingParams.ParamA : -HomingParams.ParamA) * UNightSkyBlueprintFunctionLibrary::Cos_x1000(Angle) / 1000;
				int32 SinParamA = HomingParams.ParamA * UNightSkyBlueprintFunctionLibrary::Sin_x1000(Angle) / 1000;
				int32 TmpParamB = Direction == DIR_Right ? HomingParams.ParamB : -HomingParams.ParamB;
				int32 TmpSpeedX = Direction == DIR_Right ? SpeedX : -SpeedX;
				if (TmpParamB <= 0)
				{
					if (TmpParamB >= 0)
					{
						CosParamA = TmpSpeedX;
					}
					else if (TmpSpeedX < CosParamA && -TmpSpeedX > CosParamA)
					{
						CosParamA = TmpParamB + TmpSpeedX;
					}
					while (TmpSpeedX - CosParamA <= TmpParamB || -TmpSpeedX + CosParamA >= TmpParamB)
					{
						SetSpeedXRaw(-CosParamA);
						if (HomingParams.ParamB <= 0)
						{
							if (HomingParams.ParamB >= 0)
							{
								return;
							}
							if (SpeedY < SinParamA)
							{
								SinParamA = SpeedY + HomingParams.ParamB;
							}
							SpeedY = SinParamA;
							return;
						}
						if (SpeedY < SinParamA)
						{
							if (SinParamA - SpeedY > HomingParams.ParamB)
							{
								SinParamA = SpeedY + HomingParams.ParamB;
							}
						}
						if (SpeedY - SinParamA <= HomingParams.ParamB)
						{
							SpeedY = SinParamA;
							return;
						}
						SinParamA = SpeedY - HomingParams.ParamB;
						SpeedY = SinParamA;
						return;
					}
				}
				else
				{
					if (TmpSpeedX < CosParamA)
					{
						if (CosParamA - TmpSpeedX > TmpParamB)
						{
							CosParamA = TmpParamB + TmpSpeedX;
						}
						while (TmpSpeedX - CosParamA <= TmpParamB || -TmpSpeedX + CosParamA >= TmpParamB)
						{
							SetSpeedXRaw(CosParamA);
							if (HomingParams.ParamB <= 0)
							{
								if (HomingParams.ParamB >= 0)
								{
									SinParamA = SpeedY;
								}
								if (SpeedY < SinParamA)
								{
									SinParamA = SpeedY + HomingParams.ParamB;
								}
								SpeedY = SinParamA;
								return;
							}
							if (SpeedY < SinParamA)
							{
								if (SinParamA - SpeedY > HomingParams.ParamB)
								{
									SinParamA = SpeedY + HomingParams.ParamB;
								}
							}
							if (SpeedY - SinParamA <= HomingParams.ParamB)
							{
								SpeedY = SinParamA;
								return;
							}
							SinParamA = SpeedY - HomingParams.ParamB;
							SpeedY = SinParamA;
							return;
						}
					}
					if (TmpSpeedX - CosParamA <= TmpParamB)
					{
						while (TmpSpeedX - CosParamA <= TmpParamB || -TmpSpeedX + CosParamA >= TmpParamB)
						{
							SetSpeedXRaw(CosParamA);
							if (HomingParams.ParamB <= 0)
							{
								if (HomingParams.ParamB >= 0)
								{
									SinParamA = SpeedY;
								}
								if (SpeedY < SinParamA)
								{
									SinParamA = SpeedY + HomingParams.ParamB;
								}
								SpeedY = SinParamA;
								return;
							}
							if (SpeedY < SinParamA)
							{
								if (SinParamA - SpeedY > HomingParams.ParamB)
								{
									SinParamA = SpeedY + HomingParams.ParamB;
								}
							}
							if (SpeedY - SinParamA <= HomingParams.ParamB)
							{
								SpeedY = SinParamA;
								return;
							}
							SinParamA = SpeedY - HomingParams.ParamB;
							SpeedY = SinParamA;
							return;
						}
					}
				}
				while (TmpSpeedX - CosParamA <= TmpParamB || -TmpSpeedX + CosParamA >= TmpParamB)
				{
					SetSpeedXRaw(CosParamA);
					if (HomingParams.ParamB <= 0)
					{
						if (HomingParams.ParamB >= 0)
						{
							SinParamA = SpeedY;
						}
						if (SpeedY < SinParamA)
						{
							SinParamA = SpeedY + HomingParams.ParamB;
						}
						SpeedY = SinParamA;
						return;
					}
					if (SpeedY < SinParamA)
					{
						if (SinParamA - SpeedY > HomingParams.ParamB)
						{
							SinParamA = SpeedY + HomingParams.ParamB;
						}
					}
					if (SpeedY - SinParamA <= HomingParams.ParamB)
					{
						SpeedY = SinParamA;
						return;
					}
					SinParamA = SpeedY - HomingParams.ParamB;
					SpeedY = SinParamA;
					return;
				}
			}
		}
	}
}

bool ABattleObject::SuperArmorSuccess(const ABattleObject* Attacker) const
{
	if (SuperArmorData.Type == ARM_None) return false;
	if (SuperArmorData.ArmorHits == 0) return false;

	if (SuperArmorData.bArmorMid && Attacker->HitCommon.BlockType == BLK_Mid) return true;
	if (SuperArmorData.bArmorOverhead && Attacker->HitCommon.BlockType == BLK_High) return true;
	if (SuperArmorData.bArmorLow && Attacker->HitCommon.BlockType == BLK_Low) return true;
	if (SuperArmorData.bArmorStrike && Attacker->AttackFlags & ATK_HitActive && !(Attacker->AttackFlags &
		ATK_AttackProjectileAttribute)) return true;
	if (SuperArmorData.bArmorThrow && Attacker->IsPlayer && Attacker->Player->PlayerFlags & PLF_ThrowActive) return true;
	if (SuperArmorData.bArmorHead && Attacker->AttackFlags & ATK_HitActive && Attacker->AttackFlags &
		ATK_AttackHeadAttribute) return true;
	if (SuperArmorData.bArmorProjectile && Attacker->AttackFlags & ATK_HitActive && Attacker->AttackFlags &
		ATK_AttackProjectileAttribute) return true;
	
	return false;
}

// Called every frame
void ABattleObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!GameState)
	{
		ScreenSpaceDepthOffset = 0;
		OrthoBlendActive = 1;
	}
}

void ABattleObject::CalculatePushbox()
{
	L = PosX - (PushWidth + PushWidthExtend) / 2; 
	R = PosX + (PushWidth + PushWidthExtend) / 2;
	T = PosY + PushHeight;
	B = PosY - PushHeightLow;
}

void ABattleObject::HandlePushCollision(ABattleObject* OtherObj)
{
	if (MiscFlags & MISC_PushCollisionActive && OtherObj->MiscFlags & MISC_PushCollisionActive)
	{
		if (Hitstop <= 0 && ((!OtherObj->IsPlayer || OtherObj->Player->PlayerFlags & PLF_IsThrowLock) == 0 || (!IsPlayer || Player->PlayerFlags & PLF_IsThrowLock) == 0))
		{
			if (T >= OtherObj->B && B <= OtherObj->T && R >= OtherObj->L && L <= OtherObj->R)
			{
				bool IsPushLeft;
				int32 CollisionDepth;
				if (PrevPosX == OtherObj->PrevPosX)
				{
					if (PosX == OtherObj->PosX)
					{
						if (IsPlayer == OtherObj->IsPlayer)
						{
							if (Player->WallTouchTimer == OtherObj->Player->WallTouchTimer)
							{
								IsPushLeft = Player->PlayerIndex > 0;
							}
							else
							{
								IsPushLeft = Player->WallTouchTimer > OtherObj->Player->WallTouchTimer;
								if (PosX > 0)
								{
									IsPushLeft = Player->WallTouchTimer <= OtherObj->Player->WallTouchTimer;
								}
							}
						}
						else
						{
							IsPushLeft = IsPlayer > OtherObj->IsPlayer;
						}
					}
					else
					{
						IsPushLeft = PosX < OtherObj->PosX;
					}
				}
				else
				{
					IsPushLeft = PrevPosX < OtherObj->PrevPosX;
				}
				if (IsPushLeft)
				{
					CollisionDepth = OtherObj->L - R;
				}
				else
				{
					CollisionDepth = OtherObj->R - L;
				}
				
				if (OtherObj->PosX <= -(GameState->BattleState.StageBounds + GameState->BattleState.ScreenBounds)
					|| OtherObj->PosX >= GameState->BattleState.StageBounds + GameState->BattleState.ScreenBounds)
				{
					PosX += CollisionDepth;
				}
				else
				{
					OtherObj->PosX -= CollisionDepth / 2;
					PosX += CollisionDepth / 2;
				}
				
				CalculatePushbox();
				OtherObj->CalculatePushbox();
			}
		}
	}
}

void ABattleObject::HandleHitCollision(ABattleObject* AttackedObj)
{
	if (AttackFlags & ATK_IsAttacking && AttackFlags & ATK_HitActive && AttackedObj->ObjectsToIgnoreHitsFrom.Find(this) == INDEX_NONE)
	{
		// refactor this mess into a function
		if (AttackedObj->IsPlayer && AttackedObj->Player->InvulnFlags & INV_StrikeInvulnerable && !AttackedObj->Player->
			StrikeInvulnerableTimer && AttackedObj != Player && (!(AttackFlags & ATK_AttackHeadAttribute &&
			AttackedObj->Player->InvulnFlags & INV_HeadInvulnerable) && !(AttackFlags & ATK_AttackProjectileAttribute
			&& AttackedObj->Player->InvulnFlags & INV_ProjectileInvulnerable))) return;

		auto AttackedPlayer = Cast<APlayerObject>(AttackedObj);
		if (!AttackedPlayer) return;
		for (int i = 0; i < CollisionArraySize; i++)
		{
			if (Boxes[i].Type == BOX_Hit)
			{
				for (int j = 0; j < CollisionArraySize; j++)
				{
					if (AttackedPlayer->Boxes[j].Type == BOX_Hurt)
					{
						FCollisionBox Hitbox = Boxes[i];

						FCollisionBox Hurtbox = AttackedPlayer->Boxes[j];

						if (Direction == DIR_Right)
						{
							Hitbox.PosX += PosX;
						}
						else
						{
							Hitbox.PosX = -Hitbox.PosX + PosX;  
						}
						Hitbox.PosY += PosY;
						if (AttackedPlayer->Direction == DIR_Right)
						{
							Hurtbox.PosX += AttackedPlayer->PosX;
						}
						else
						{
							Hurtbox.PosX = -Hurtbox.PosX + AttackedPlayer->PosX;  
						}
						Hurtbox.PosY += AttackedPlayer->PosY;
							
						if (Hitbox.PosY + Hitbox.SizeY / 2 >= Hurtbox.PosY - Hurtbox.SizeY / 2
							&& Hitbox.PosY - Hitbox.SizeY / 2 <= Hurtbox.PosY + Hurtbox.SizeY / 2
							&& Hitbox.PosX + Hitbox.SizeX / 2 >= Hurtbox.PosX - Hurtbox.SizeX / 2
							&& Hitbox.PosX - Hitbox.SizeX / 2 <= Hurtbox.PosX + Hurtbox.SizeX / 2)
						{
							AttackedPlayer->AttackOwner = this;
							AttackedPlayer->ObjectsToIgnoreHitsFrom.AddUnique(this);
							AttackedPlayer->StunTime = 2147483647;
							AttackedPlayer->FaceOpponent();
							AttackedPlayer->HaltMomentum();
							AttackedPlayer->PlayerFlags |= PLF_IsStunned;
							AttackFlags |= ATK_HasHit;
							AttackTarget = AttackedPlayer;
								
							int CollisionDepthX;
							if (Hitbox.PosX < AttackedPlayer->PosX)
							{
								CollisionDepthX = AttackedPlayer->PosX - (Hitbox.PosX + Hitbox.SizeX / 2);
								HitPosX = Hitbox.PosX + CollisionDepthX / 2;
							}
							else
							{
								CollisionDepthX = Hitbox.PosX - Hitbox.SizeX / 2 - AttackedPlayer->PosX;
								HitPosX = Hitbox.PosX - CollisionDepthX / 2;
							}
							int CollisionDepthY;
							int32 CenterPosY = AttackedPlayer->GetPosYCenter();
							if (Hitbox.PosY < CenterPosY)
							{
								CollisionDepthY = CenterPosY - (Hitbox.PosY + Hitbox.SizeY / 2);
								HitPosY = Hitbox.PosY + CollisionDepthY / 2;
							}
							else
							{
								CollisionDepthY = Hitbox.PosY - Hitbox.SizeY / 2 - CenterPosY;
								HitPosY = Hitbox.PosY - CollisionDepthY / 2;
							}
								
							TriggerEvent(EVT_HitOrBlock);
							if (AttackedPlayer->IsMainPlayer())
							{
								TriggerEvent(EVT_HitOrBlockMainPlayer);
							}
								
							if (AttackedPlayer->IsCorrectBlock(HitCommon.BlockType)) //check blocking
							{
								CreateCommonParticle("cmn_guard", POS_Enemy,
								                     FVector(0, 100, 0),
								                     FRotator(HitCommon.HitAngle, 0, 0));
								TriggerEvent(EVT_Block);
								if (AttackedPlayer->IsMainPlayer())
								{
									TriggerEvent(EVT_BlockMainPlayer);
								}

								const int32 ChipDamage = NormalHit.Damage * HitCommon.ChipDamagePercent / 100;
								AttackedPlayer->CurrentHealth -= ChipDamage;
									
								const FHitData Data = InitHitDataByAttackLevel(false);
								AttackedPlayer->ReceivedHitCommon = HitCommon;
								AttackedPlayer->ReceivedHit = Data;
									
								if (AttackedPlayer->CurrentHealth <= 0)
								{
									EHitAction HACT;
										
									if (AttackedPlayer->PosY == AttackedPlayer->GroundHeight && !(AttackedPlayer->PlayerFlags & PLF_IsKnockedDown))
										HACT = NormalHit.GroundHitAction;
									else
										HACT = NormalHit.AirHitAction;
										
									AttackedPlayer->HandleHitAction(HACT);
								}
								else
								{
									AttackedPlayer->HandleBlockAction();
									AttackedPlayer->AirDashTimer = 0;
									if (AttackedPlayer->PlayerFlags & PLF_TouchingWall)
									{
										Pushback = AttackedPlayer->Pushback;
										AttackedPlayer->Pushback = 0;
									}
								}
								AttackedPlayer->AddMeter(NormalHit.Damage * AttackedPlayer->MeterPercentOnReceiveHitGuard / 100);
								Player->AddMeter(NormalHit.Damage * Player->MeterPercentOnHitGuard / 100);
							}
							else if (AttackedPlayer->SuperArmorSuccess(this))
							{
								TriggerEvent(EVT_Hit);
								if (AttackedPlayer->IsMainPlayer())
								{
									TriggerEvent(EVT_HitMainPlayer);
								}
								
								if (AttackedPlayer->SuperArmorData.ArmorHits > 0) AttackedPlayer->SuperArmorData.ArmorHits--;
								switch (AttackedPlayer->SuperArmorData.Type)
								{
								case ARM_Guard:
									{
										if (AttackedPlayer->SuperArmorData.bArmorTakeChipDamage)
										{
											const int32 ChipDamage = NormalHit.Damage * HitCommon.ChipDamagePercent / 100;
											AttackedPlayer->CurrentHealth -= ChipDamage;
											AttackedPlayer->AddMeter(NormalHit.Damage * AttackedPlayer->MeterPercentOnReceiveHitGuard / 100);
											Player->AddMeter(NormalHit.Damage * Player->MeterPercentOnHitGuard / 100);
										}
										if (AttackedPlayer->SuperArmorData.ArmorDamagePercent)
										{
											const int32 ArmorDamage = NormalHit.Damage * AttackedPlayer->SuperArmorData.ArmorDamagePercent / 100;
											AttackedPlayer->CurrentHealth -= ArmorDamage;
											AttackedPlayer->AddMeter(
												NormalHit.Damage * AttackedPlayer->MeterPercentOnReceiveHit * AttackedPlayer->
												SuperArmorData.ArmorDamagePercent / 10000);
											Player->AddMeter(
												NormalHit.Damage * Player->MeterPercentOnHit * AttackedPlayer->
												SuperArmorData.ArmorDamagePercent / 10000);
										}
										else
										{
											CreateCommonParticle("cmn_guard", POS_Enemy,
										 FVector(0, 100, 0),
										 FRotator(HitCommon.HitAngle, 0, 0));
										}
									
										const FHitData Data = InitHitDataByAttackLevel(false);
										AttackedPlayer->ReceivedHitCommon = HitCommon;
										AttackedPlayer->ReceivedHit = Data;
											
										if (AttackedPlayer->CurrentHealth <= 0)
										{
											EHitAction HACT;
										
											if (AttackedPlayer->PosY == AttackedPlayer->GroundHeight && !(AttackedPlayer->PlayerFlags & PLF_IsKnockedDown))
												HACT = NormalHit.GroundHitAction;
											else
												HACT = NormalHit.AirHitAction;
										
											AttackedPlayer->HandleHitAction(HACT);
										}
										else
										{
											Hitstop = Data.Hitstop;
											AttackedPlayer->Hitstop = Data.Hitstop;
										}
									}
									break;
								case ARM_Dodge:
								default:
									break;
								}
							}
							else if ((AttackedPlayer->AttackFlags & ATK_IsAttacking) == 0)
							{
								TriggerEvent(EVT_Hit);
								if (AttackedPlayer->IsMainPlayer())
								{
									TriggerEvent(EVT_HitMainPlayer);
								}
									
								if (IsPlayer && Player->PlayerFlags & PLF_HitgrabActive)
								{
									AttackedPlayer->JumpToState(AttackedPlayer->CharaStateData->DefaultThrowLock);
									AttackedPlayer->PlayerFlags |= PLF_IsThrowLock;
									AttackedPlayer->AttackOwner = Player;
									Player->ThrowExe();
									return;
								}
									
								const FHitData Data = InitHitDataByAttackLevel(false);
								CreateCommonParticle(HitCommon.HitVFXOverride.ToString(), POS_Hit,
								                     FVector(0, 100, 0),
								                     FRotator(HitCommon.HitAngle, 0, 0));
								PlayCommonSound(HitCommon.HitSFXOverride.ToString());
								AttackedPlayer->ReceivedHitCommon = HitCommon;
								AttackedPlayer->ReceivedHit = Data;
								EHitAction HACT;
										
								if (AttackedPlayer->PosY == AttackedPlayer->GroundHeight && !(AttackedPlayer->PlayerFlags & PLF_IsKnockedDown))
									HACT = NormalHit.GroundHitAction;
								else
									HACT = NormalHit.AirHitAction;

								AttackedPlayer->HandleHitAction(HACT);
							}
							else
							{
								TriggerEvent(EVT_Hit);
								TriggerEvent(EVT_CounterHit);
								if (AttackedPlayer->IsMainPlayer())
								{
									TriggerEvent(EVT_HitMainPlayer);
									TriggerEvent(EVT_CounterHitMainPlayer);
								}

								AttackedPlayer->AddColor = FLinearColor(5,0.2,0.2,1);
								AttackedPlayer->MulColor = FLinearColor(1,0.1,0.1,1);
								AttackedPlayer->AddFadeSpeed = 0.1;
								AttackedPlayer->MulFadeSpeed = 0.1;
									
								if (IsPlayer && Player->PlayerFlags & PLF_HitgrabActive)
								{
									AttackedPlayer->JumpToState(AttackedPlayer->CharaStateData->DefaultThrowLock);
									AttackedPlayer->PlayerFlags |= PLF_IsThrowLock;
									AttackedPlayer->AttackOwner = Player;
									Player->ThrowExe();
									return;
								}

								const FHitData CounterData = InitHitDataByAttackLevel(true);
								CreateCommonParticle(HitCommon.HitVFXOverride.ToString(), POS_Hit, FVector(0, 100, 0), FRotator(HitCommon.HitAngle, 0, 0));
								PlayCommonSound(HitCommon.HitSFXOverride.ToString());
								AttackedPlayer->ReceivedHitCommon = HitCommon;
								AttackedPlayer->ReceivedHit = CounterData;
								AttackedPlayer->ReceivedHit = CounterData;
								EHitAction HACT;
										
								if (AttackedPlayer->PosY == AttackedPlayer->GroundHeight && !(AttackedPlayer->PlayerFlags & PLF_IsKnockedDown))
									HACT = CounterHit.GroundHitAction;
								else
									HACT = CounterHit.AirHitAction;
									
								AttackedPlayer->HandleHitAction(HACT);
							}
							return;
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
	if (HitCommon.AttackLevel > 5)
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
			HitCommon.HitVFXOverride = FName("cmn_hit_s");
			break;
		case EHitVFXType::VFX_Special:
			HitCommon.HitVFXOverride = FName("cmn_hit_sp");
			break;
		}
		switch (HitCommon.SFXType)
		{
		case EHitSFXType::SFX_Punch:
			HitCommon.HitSFXOverride = FName("HitPunchS");
			break;
		case EHitSFXType::SFX_Kick:
			HitCommon.HitSFXOverride = FName("HitKickS");
			break;
		case EHitSFXType::SFX_Slash:
			HitCommon.HitSFXOverride = FName("HitSlashS");
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
			HitCommon.HitVFXOverride = FName("cmn_hit_s");
			break;
		case EHitVFXType::VFX_Special:
			HitCommon.HitVFXOverride = FName("cmn_hit_sp");
			break;
		}
		switch (HitCommon.SFXType)
		{
		case EHitSFXType::SFX_Punch:
			HitCommon.HitSFXOverride = FName("HitPunchS");
			break;
		case EHitSFXType::SFX_Kick:
			HitCommon.HitSFXOverride = FName("HitKickS");
			break;
		case EHitSFXType::SFX_Slash:
			HitCommon.HitSFXOverride = FName("HitSlashS");
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
			HitCommon.HitVFXOverride = FName("cmn_hit_m");
			break;
		case EHitVFXType::VFX_Special:
			HitCommon.HitVFXOverride = FName("cmn_hit_sp");
			break;
		}
		switch (HitCommon.SFXType)
		{
		case EHitSFXType::SFX_Punch:
			HitCommon.HitSFXOverride = FName("HitPunchM");
			break;
		case EHitSFXType::SFX_Kick:
			HitCommon.HitSFXOverride = FName("HitKickM");
			break;
		case EHitSFXType::SFX_Slash:
			HitCommon.HitSFXOverride = FName("HitSlashM");
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
			HitCommon.HitVFXOverride = FName("cmn_hit_m");
			break;
		case EHitVFXType::VFX_Special:
			HitCommon.HitVFXOverride = FName("cmn_hit_sp");
			break;
		}
		switch (HitCommon.SFXType)
		{
		case EHitSFXType::SFX_Punch:
			HitCommon.HitSFXOverride = FName("HitPunchM");
			break;
		case EHitSFXType::SFX_Kick:
			HitCommon.HitSFXOverride = FName("HitKickM");
			break;
		case EHitSFXType::SFX_Slash:
			HitCommon.HitSFXOverride = FName("HitSlashM");
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
			HitCommon.HitVFXOverride = FName("cmn_hit_l");
			break;
		case EHitVFXType::VFX_Special:
			HitCommon.HitVFXOverride = FName("cmn_hit_sp");
			break;
		}
		switch (HitCommon.SFXType)
		{
		case EHitSFXType::SFX_Punch:
			HitCommon.HitSFXOverride = FName("HitPunchL");
			break;
		case EHitSFXType::SFX_Kick:
			HitCommon.HitSFXOverride = FName("HitKickL");
			break;
		case EHitSFXType::SFX_Slash:
			HitCommon.HitSFXOverride = FName("HitSlashL");
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
			NormalHit.Gravity = 1900;
		if (CounterHit.Hitstop == -1)
			CounterHit.Hitstop = NormalHit.Hitstop + 16;
		switch (HitCommon.VFXType)
		{
		case EHitVFXType::VFX_Strike:
		case EHitVFXType::VFX_Slash:
			HitCommon.HitVFXOverride = FName("cmn_hit_l");
			break;
		case EHitVFXType::VFX_Special:
			HitCommon.HitVFXOverride = FName("cmn_hit_sp");
			break;
		}
		switch (HitCommon.SFXType)
		{
		case EHitSFXType::SFX_Punch:
			HitCommon.HitSFXOverride = FName("HitPunchL");
			break;
		case EHitSFXType::SFX_Kick:
			HitCommon.HitSFXOverride = FName("HitKickL");
			break;
		case EHitSFXType::SFX_Slash:
			HitCommon.HitSFXOverride = FName("HitSlashL");
			break;
		}
		break;
	}

	if (NormalHit.EnemyHitstopModifier == -1)
		NormalHit.EnemyHitstopModifier = 0;
	if (NormalHit.RecoverableDamagePercent == -1)
		NormalHit.RecoverableDamagePercent = 40;
	if (NormalHit.MinimumDamagePercent == -1)
		NormalHit.MinimumDamagePercent = 0;
	if (NormalHit.InitialProration == -1)
		NormalHit.InitialProration = 100;
	if (NormalHit.ForcedProration == -1)
		NormalHit.ForcedProration = 90;
	
	if (CounterHit.EnemyHitstopModifier == -1)
		CounterHit.EnemyHitstopModifier = NormalHit.EnemyHitstopModifier;
	if (CounterHit.MinimumDamagePercent == -1)
		CounterHit.MinimumDamagePercent = NormalHit.MinimumDamagePercent;
	if (CounterHit.InitialProration == -1)
		CounterHit.InitialProration = NormalHit.InitialProration;
	if (CounterHit.ForcedProration == -1)
		CounterHit.ForcedProration = NormalHit.ForcedProration;
	
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
	if (CounterHit.AirPushbackXOverTime.Value == -1)
		CounterHit.AirPushbackXOverTime.Value = NormalHit.AirPushbackXOverTime.Value;
	if (CounterHit.AirPushbackXOverTime.BeginFrame == -1)
		CounterHit.AirPushbackXOverTime.BeginFrame = NormalHit.AirPushbackXOverTime.BeginFrame;
	if (CounterHit.AirPushbackXOverTime.EndFrame == -1)
		CounterHit.AirPushbackXOverTime.EndFrame = NormalHit.AirPushbackXOverTime.EndFrame;
	if (CounterHit.AirPushbackYOverTime.Value == -1)
		CounterHit.AirPushbackYOverTime.Value = NormalHit.AirPushbackYOverTime.Value;
	if (CounterHit.AirPushbackYOverTime.BeginFrame == -1)
		CounterHit.AirPushbackYOverTime.BeginFrame = NormalHit.AirPushbackYOverTime.BeginFrame;
	if (CounterHit.AirPushbackYOverTime.EndFrame == -1)
		CounterHit.AirPushbackYOverTime.EndFrame = NormalHit.AirPushbackYOverTime.EndFrame;
	if (CounterHit.GravityOverTime.Value == -1)
		CounterHit.GravityOverTime.Value = NormalHit.GravityOverTime.Value;
	if (CounterHit.GravityOverTime.BeginFrame == -1)
		CounterHit.GravityOverTime.BeginFrame = NormalHit.GravityOverTime.BeginFrame;
	if (CounterHit.GravityOverTime.EndFrame == -1)
		CounterHit.GravityOverTime.EndFrame = NormalHit.GravityOverTime.EndFrame;
	if (CounterHit.BlowbackLevel == -1)
		CounterHit.BlowbackLevel = NormalHit.BlowbackLevel;
	if (CounterHit.FloatingCrumpleType == FLT_None)
		CounterHit.FloatingCrumpleType = NormalHit.FloatingCrumpleType;

	if (CounterHit.Position.Type == HPT_Non)
		CounterHit.Position.Type = NormalHit.Position.Type;
	if (CounterHit.Position.PosX == -1)
		CounterHit.Position.PosX = NormalHit.Position.PosX;
	if (CounterHit.Position.PosY == -1)
		CounterHit.Position.PosY = NormalHit.Position.PosY;

	if (CounterHit.GroundHitAction == HACT_GroundNormal)
		CounterHit.GroundHitAction = NormalHit.GroundHitAction;
	if (CounterHit.AirHitAction == HACT_AirNormal)
		CounterHit.AirHitAction = NormalHit.AirHitAction;

	if (NormalHit.KnockdownTime == -1)
		NormalHit.KnockdownTime = 12;
	if (CounterHit.KnockdownTime == -1)
		CounterHit.KnockdownTime = NormalHit.KnockdownTime;
	
	if (NormalHit.HardKnockdown == -1)
		NormalHit.HardKnockdown = 0;
	if (CounterHit.HardKnockdown == -1)
		CounterHit.HardKnockdown = NormalHit.HardKnockdown;
	
	if (NormalHit.WallBounce.WallBounceStop == -1)
		NormalHit.WallBounce.WallBounceStop = NormalHit.Hitstop;
	if (NormalHit.WallBounce.WallBounceXSpeed == -1)
		NormalHit.WallBounce.WallBounceXSpeed = NormalHit.AirPushbackX;
	if (NormalHit.WallBounce.WallBounceXRate == -1)
		NormalHit.WallBounce.WallBounceXRate = 33;
	if (NormalHit.WallBounce.WallBounceYSpeed == -1)
		NormalHit.WallBounce.WallBounceYSpeed = NormalHit.AirPushbackY;
	if (NormalHit.WallBounce.WallBounceYRate == -1)
		NormalHit.WallBounce.WallBounceYRate = 100;
	if (NormalHit.WallBounce.WallBounceGravity == -1)
		NormalHit.WallBounce.WallBounceGravity = NormalHit.Gravity;

	if (CounterHit.WallBounce.WallBounceStop == -1)
		CounterHit.WallBounce.WallBounceStop = NormalHit.WallBounce.WallBounceStop;
	if (CounterHit.WallBounce.WallBounceCount == -1)
		CounterHit.WallBounce.WallBounceCount = NormalHit.WallBounce.WallBounceCount;
	if (CounterHit.WallBounce.WallBounceXSpeed == -1)
		CounterHit.WallBounce.WallBounceXSpeed = NormalHit.WallBounce.WallBounceXSpeed;
	if (CounterHit.WallBounce.WallBounceXRate == -1)
		CounterHit.WallBounce.WallBounceXRate = NormalHit.WallBounce.WallBounceXRate;
	if (CounterHit.WallBounce.WallBounceYSpeed == -1)
		CounterHit.WallBounce.WallBounceYSpeed = NormalHit.WallBounce.WallBounceYSpeed;
	if (CounterHit.WallBounce.WallBounceYRate == -1)
		CounterHit.WallBounce.WallBounceYRate = NormalHit.WallBounce.WallBounceYRate;
	if (CounterHit.WallBounce.WallBounceGravity == -1)
		CounterHit.WallBounce.WallBounceGravity = NormalHit.WallBounce.WallBounceGravity;

	if (NormalHit.GroundBounce.GroundBounceStop == -1)
		NormalHit.GroundBounce.GroundBounceStop = NormalHit.Hitstop;
	if (NormalHit.GroundBounce.GroundBounceXSpeed == -1)
		NormalHit.GroundBounce.GroundBounceXSpeed = NormalHit.AirPushbackX;
	if (NormalHit.GroundBounce.GroundBounceXRate == -1)
		NormalHit.GroundBounce.GroundBounceXRate = 100;
	if (NormalHit.GroundBounce.GroundBounceYSpeed == -1)
		NormalHit.GroundBounce.GroundBounceYSpeed = NormalHit.AirPushbackY;
	if (NormalHit.GroundBounce.GroundBounceYRate == -1)
		NormalHit.GroundBounce.GroundBounceYRate = 100;
	if (NormalHit.GroundBounce.GroundBounceGravity == -1)
		NormalHit.GroundBounce.GroundBounceGravity = NormalHit.Gravity;

	if (CounterHit.GroundBounce.GroundBounceStop == -1)
		CounterHit.GroundBounce.GroundBounceStop = NormalHit.GroundBounce.GroundBounceStop;
	if (CounterHit.GroundBounce.GroundBounceCount == -1)
		CounterHit.GroundBounce.GroundBounceCount = NormalHit.GroundBounce.GroundBounceCount;
	if (CounterHit.GroundBounce.GroundBounceXSpeed == -1)
		CounterHit.GroundBounce.GroundBounceXSpeed = NormalHit.GroundBounce.GroundBounceXSpeed;
	if (CounterHit.GroundBounce.GroundBounceXRate == -1)
		CounterHit.GroundBounce.GroundBounceXRate = NormalHit.GroundBounce.GroundBounceXRate;
	if (CounterHit.GroundBounce.GroundBounceYSpeed == -1)
		CounterHit.GroundBounce.GroundBounceYSpeed = NormalHit.GroundBounce.GroundBounceYSpeed;
	if (CounterHit.GroundBounce.GroundBounceYRate == -1)
		CounterHit.GroundBounce.GroundBounceYRate = NormalHit.GroundBounce.GroundBounceYRate;
	if (CounterHit.GroundBounce.GroundBounceGravity == -1)
		CounterHit.GroundBounce.GroundBounceGravity = NormalHit.GroundBounce.GroundBounceGravity;
	
	FHitData Data;
	if (!IsCounter)
		Data = NormalHit;
	else
		Data = CounterHit;
	
	return Data;
}

void ABattleObject::HandleClashCollision(ABattleObject* OtherObj)
{
	if (AttackFlags & ATK_IsAttacking && AttackFlags & ATK_HitActive && OtherObj->Player->PlayerIndex != Player->PlayerIndex
		&& OtherObj->AttackFlags & ATK_IsAttacking && OtherObj->AttackFlags & ATK_HitActive)
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
							{
								CollisionDepthX = OtherHitbox.PosX - OtherHitbox.SizeX / 2 - (Hitbox.PosX + Hitbox.SizeX / 2);
								HitPosX = Hitbox.PosX - CollisionDepthX;
							}
							else
							{
								CollisionDepthX = Hitbox.PosX - Hitbox.SizeX / 2 - (OtherHitbox.PosX + OtherHitbox.SizeX / 2);
								HitPosX = Hitbox.PosX + CollisionDepthX;
							}
							int CollisionDepthY;
							if (Hitbox.PosY < OtherHitbox.PosY)
							{
								CollisionDepthY = OtherHitbox.PosY - OtherHitbox.SizeY / 2 - (Hitbox.PosY + Hitbox.SizeY / 2);
								HitPosY = Hitbox.PosY - CollisionDepthY;
							}
							else
							{
								CollisionDepthY = Hitbox.PosY - Hitbox.SizeY / 2 - (OtherHitbox.PosY + OtherHitbox.SizeY / 2);
								HitPosY = Hitbox.PosY + CollisionDepthY;
							}
							
							if (IsPlayer && OtherObj->IsPlayer)
							{
								Hitstop = 16;
								OtherObj->Hitstop = 16;
								AttackFlags &= ~ATK_HitActive;
								OtherObj->AttackFlags &= ~ATK_HitActive;
								OtherObj->HitPosX = HitPosX;
								OtherObj->HitPosY = HitPosY;
								Player->EnableAttacks();
								Player->EnableCancelIntoSelf(true);
								Player->EnableState(ENB_ForwardDash);
								OtherObj->Player->EnableAttacks();
								OtherObj->Player->EnableCancelIntoSelf(true);
								OtherObj->Player->EnableState(ENB_ForwardDash);
								TriggerEvent(EVT_HitOrBlock);
								OtherObj->TriggerEvent(EVT_HitOrBlock);
								CreateCommonParticle("cmn_hit_clash", POS_Hit, FVector(0, 100, 0));
                                PlayCommonSound("HitClash");
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
								TriggerEvent(EVT_HitOrBlock);
								OtherObj->TriggerEvent(EVT_HitOrBlock);
								CreateCommonParticle("cmn_hit_clash", POS_Hit, FVector(0, 100, 0));
                                PlayCommonSound("HitClash");
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
				Player->JumpToState(Player->CharaStateData->DefaultStandFlip);
			else if (Player->Stance == ACT_Crouching && Player->EnableFlags & ENB_Standing)
				Player->JumpToState(Player->CharaStateData->DefaultCrouchFlip);
			else if (Player->Stance == ACT_Jumping && Player->EnableFlags & ENB_Jumping)
				Player->JumpToState(Player->CharaStateData->DefaultJumpFlip);
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
		if (!IsPlayer)
		{
			*OutPosY = PosY;
			break;
		}
		{
			int32 CenterPosY = PosY;
			switch (Player->Stance)
			{
			case ACT_Standing:
			case ACT_Jumping:
			default:
				CenterPosY += 200000;
				break;
			case ACT_Crouching:
				CenterPosY += 90000;
				break;
			}
			*OutPosY = CenterPosY;
		}
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
	if (EventType == EVT_Update) UpdateTime++;
	if (const auto SubroutineName = EventHandlers[EventType].SubroutineName; SubroutineName != FName("None"))
	{
		USubroutine* Subroutine = nullptr;
		
		if (const auto CommonIndex = Player->CommonSubroutineNames.Find(SubroutineName); CommonIndex != INDEX_NONE)
			Subroutine = Player->CommonSubroutines[CommonIndex];

		else if (const auto Index = Player->SubroutineNames.Find(SubroutineName); Index != INDEX_NONE)
			Subroutine = Player->Subroutines[Index];

		if (!Subroutine) return;

		UFunction* const Func = Subroutine->FindFunction(FName(EventHandlers[EventType].FunctionName.ToString()));
		if (IsValid(Func) && Func->ParmsSize == 0)
		{
			Subroutine->Parent = this;
			Subroutine->ProcessEvent(Func, nullptr);
		}
		return;
	}
	
	UState* State = ObjectState;
	if (IsPlayer)
		State = Player->StoredStateMachine.CurrentState;
	if (!IsValid(State))
		return;
	UFunction* const Func = State->FindFunction(FName(EventHandlers[EventType].FunctionName.ToString()));
	if (IsValid(Func) && Func->ParmsSize == 0)
	{
		State->ProcessEvent(Func, nullptr);
	}
}

//for collision viewer

template<typename T>
constexpr auto min(T a, T b)
{
	return a < b ? a : b;
}

template<typename T>
constexpr auto max(T a, T b)
{
	return a > b ? a : b;
}
static void clip_line_y(
	const FVector2D &line_a, const FVector2D &line_b,
	float min_x, float max_x,
	float *min_y, float *max_y)
{
	const auto delta = line_b - line_a;

	if (abs(delta.X) > FLT_EPSILON) {
		const auto slope = delta.Y / delta.X;
		const auto intercept = line_a.Y - slope * line_a.X;
		*min_y = slope * min_x + intercept;
		*max_y = slope * max_x + intercept;
	} else {
		*min_y = line_a.Y;
		*max_y = line_b.Y;
	}

	if (*min_y > *max_y)
		std::swap(*min_y, *max_y);
}

bool line_box_intersection(
	const FVector2D &box_min, const FVector2D &box_max,
	const FVector2D &line_a, const FVector2D &line_b,
	float *entry_fraction, float *exit_fraction)
{
	// No intersection if line runs along the edge of the box
	if (line_a.X == line_b.X && (line_a.X == box_min.X || line_a.X == box_max.X))
		return false;

	if (line_a.Y == line_b.Y && (line_a.Y == box_min.Y || line_a.Y == box_max.Y))
		return false;

	// Clip X values to segment within box_min.X and box_max.X
	const auto min_x = max(min(line_a.X, line_b.X), box_min.X);
	const auto max_x = min(max(line_a.X, line_b.X), box_max.X);

	// Check if the line is in the bounds of the box on the X axis
	if (min_x > max_x)
		return false;

	// Clip Y values to segment within min_x and max_x
	float min_y, max_y;
	clip_line_y(line_a, line_b, min_x, max_x, &min_y, &max_y);

	// Clip Y values to segment within box_min.Y and box_max.Y
	min_y = max(min_y, (float)box_min.Y);
	max_y = min(max_y, (float)box_max.Y);

	// Check if the clipped line is in the bounds of the box on the Y axis
	if (min_y > max_y)
		return false;

	const FVector2D entry(
		line_a.X < line_b.X ? min_x : max_x,
		line_a.Y < line_b.Y ? min_y : max_y);

	const FVector2D exit(
		line_a.X > line_b.X ? min_x : max_x,
		line_a.Y > line_b.Y ? min_y : max_y);

	const auto length = (line_b - line_a).Size();
	*entry_fraction = (entry - line_a).Size() / length;
	*exit_fraction = (exit - line_a).Size() / length;

	return true;
}

void ABattleObject::CollisionView()
{
	TArray<TArray<FVector2D>> Corners;
	TArray<TArray<TArray<FVector2D>>> Lines; 
	for (auto Box : Boxes)
	{
		TArray<FVector2D> CurrentCorners;
		if (Direction == DIR_Right)
		{
			CurrentCorners.Add(FVector2D(float(Box.PosX + PosX) / COORD_SCALE - float(Box.SizeX) / COORD_SCALE / 2,
				float(Box.PosY + PosY) / COORD_SCALE -  float(Box.SizeY) / COORD_SCALE / 2));
			CurrentCorners.Add(FVector2D(float(Box.PosX + PosX) / COORD_SCALE + float(Box.SizeX) / COORD_SCALE / 2,
				float(Box.PosY + PosY) / COORD_SCALE -  float(Box.SizeY) / COORD_SCALE / 2));
			CurrentCorners.Add(FVector2D(float(Box.PosX + PosX) / COORD_SCALE + float(Box.SizeX) / COORD_SCALE / 2,
				float(Box.PosY + PosY) / COORD_SCALE + float(Box.SizeY) / COORD_SCALE / 2));
			CurrentCorners.Add(FVector2D(float(Box.PosX + PosX) / COORD_SCALE - float(Box.SizeX) / COORD_SCALE / 2,
				float(Box.PosY + PosY) / COORD_SCALE + float(Box.SizeY) / COORD_SCALE / 2));
		}
		else
		{
			CurrentCorners.Add(FVector2D(float(-Box.PosX + PosX) / COORD_SCALE - float(Box.SizeX) / COORD_SCALE / 2,
				float(Box.PosY + PosY) / COORD_SCALE -  float(Box.SizeY) / COORD_SCALE / 2));
			CurrentCorners.Add(FVector2D(float(-Box.PosX + PosX) / COORD_SCALE + float(Box.SizeX) / COORD_SCALE / 2,
				float(Box.PosY + PosY) / COORD_SCALE -  float(Box.SizeY) / COORD_SCALE / 2));
			CurrentCorners.Add(FVector2D(float(-Box.PosX + PosX) / COORD_SCALE + float(Box.SizeX) / COORD_SCALE / 2,
				float(Box.PosY + PosY) / COORD_SCALE + float(Box.SizeY) / COORD_SCALE / 2));
			CurrentCorners.Add(FVector2D(float(-Box.PosX + PosX) / COORD_SCALE - float(Box.SizeX) / COORD_SCALE / 2,
				float(Box.PosY + PosY) / COORD_SCALE + float(Box.SizeY) / COORD_SCALE / 2));
		}
		Corners.Add(CurrentCorners);
		TArray<TArray<FVector2D>> CurrentLines;
		for (int j = 0; j < 4; j++)
		{
			CurrentLines.Add(TArray { CurrentCorners[j] , CurrentCorners[(j + 1) % 4] } );
		}
		Lines.Add(CurrentLines);
		FLinearColor color;
		if (Box.Type == BOX_Hit)
			color = FLinearColor(1.f, 0.f, 0.f, .25f);
		else if (AttackFlags & ATK_IsAttacking)
			color = FLinearColor(0.f, 1.f, 1.f, .25f);
		else
			color = FLinearColor(0.f, 1.f, 0.f, .25f);
		for (const auto& LineSet : Lines.Last())
		{
			auto start = LineSet[0];
			auto end = LineSet[1];
			DrawDebugLine(GetWorld(), FVector(start.X, 0, start.Y), FVector(end.X, 0, end.Y), color.ToFColor(false), false, 1 / 60, 255, 2.f);
		}
	}
	TArray<FVector2D> CurrentCorners;
	CurrentCorners.Add(FVector2D(L / COORD_SCALE, B / COORD_SCALE));
	CurrentCorners.Add(FVector2D(R / COORD_SCALE, B / COORD_SCALE));
	CurrentCorners.Add(FVector2D(R / COORD_SCALE, T / COORD_SCALE));
	CurrentCorners.Add(FVector2D(L / COORD_SCALE, T / COORD_SCALE));
	TArray<TArray<FVector2D>> CurrentLines;
	for (int j = 0; j < 4; j++)
	{
		CurrentLines.Add(TArray { CurrentCorners[j] , CurrentCorners[(j + 1) % 4] } );
	}
	FLinearColor color = FLinearColor(1.f, 1.f, 0.f, .2f);

	for (const auto& LineSet : CurrentLines)
	{
		auto start = LineSet[0];
		auto end = LineSet[1];
		DrawDebugLine(GetWorld(), FVector(start.X, 0, start.Y), FVector(end.X, 0, end.Y), color.ToFColor(false), false,1 / 60, 255, 2.f);
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
		const int StateIndex = Player->ObjectStateNames.Find(ObjectStateName);
		if (StateIndex != INDEX_NONE)
		{
			ObjectState = DuplicateObject(Player->ObjectStates[StateIndex], this);
			ObjectState->Parent = this;
		}
	}
}

void ABattleObject::LogForSyncTestFile(std::ofstream& file)
{
	if(file)
	{
		file << "BattleObject:\n";
		file << "\tPosX: " << PosX << std::endl;
		file << "\tPosY: " << PosY << std::endl;
		file << "\tPosZ: " << PosZ << std::endl;
		file << "\tPrevPosX: " << PrevPosX << std::endl;
		file << "\tPrevPosY: " << PrevPosY << std::endl;
		file << "\tPrevPosZ: " << PrevPosZ << std::endl;
		file << "\tSpeedX: " << SpeedX << std::endl;
		file << "\tSpeedY: " << SpeedY << std::endl;
		file << "\tSpeedZ: " << SpeedZ << std::endl;
		file << "\tGravity: " << Gravity << std::endl;
		file << "\tInertia: " << Inertia << std::endl;
		file << "\tActionTime: " << ActionTime << std::endl;
		file << "\tPushHeight: " << PushHeight << std::endl;
		file << "\tPushHeightLow: " << PushHeightLow << std::endl;
		file << "\tPushWidth: " << PushWidth << std::endl;
		file << "\tStunTime: " << StunTime << std::endl;
		file << "\tStunTimeMax: " << StunTimeMax << std::endl;
		file << "\tHitstop: " << Hitstop << std::endl;
		file << "\tCelName: " << TCHAR_TO_ANSI(*CelName.ToString()) << std::endl;
		file << "\tAttackFlags: " << AttackFlags << std::endl;
		file << "\tDirection: " << Direction << std::endl;
		file << "\tMiscFlags: " << MiscFlags << std::endl;
		file << "\tCelIndex: " << CelIndex << std::endl;
		file << "\tTimeUntilNextCel: " << TimeUntilNextCel << std::endl;
		file << "\tAnimFrame: " << AnimFrame << std::endl;
	}
}

void ABattleObject::UpdateVisuals()
{
	if (IsPlayer)
	{
		if (Player->PlayerFlags & PLF_IsOnScreen) SetActorHiddenInGame(false);
		else SetActorHiddenInGame(true);
	}
	FRotator FlipRotation = FRotator::ZeroRotator;
	if (Direction == DIR_Left)
	{
		if (Player->bMirrorWhenFlip && IsPlayer)
		{
			FlipRotation = FRotator(0, 180, 0);
			SetActorScale3D(FVector(1, 1, 1) * ObjectScale);
			if (!GameState) SetActorRotation(FlipRotation);	
		}
		else
			SetActorScale3D(FVector(-1, 1, 1) * ObjectScale);
	}
	else
	{
		SetActorScale3D(FVector(1, 1, 1) * ObjectScale);
	}
	if (IsValid(GameState))
	{
		if (SocketName == FName("None")) //only set visual location if not attached to socket
		{
			SetActorRotation(GameState->BattleSceneTransform.GetRotation() * (ObjectRotation.Quaternion() * FlipRotation.Quaternion()));
			FVector Location = FVector(static_cast<float>(PosX) / COORD_SCALE, static_cast<float>(PosZ) / COORD_SCALE, static_cast<float>(PosY) / COORD_SCALE) + ObjectOffset;
			Location = GameState->BattleSceneTransform.GetRotation().RotateVector(Location) + GameState->BattleSceneTransform.GetLocation();
			SetActorLocation(Location);
		}
		else
		{
			FVector FinalSocketOffset = SocketOffset;
			if (Direction != DIR_Right)
				FinalSocketOffset.Y = -SocketOffset.Y;
			const auto Obj = GetBattleObject(SocketObj);
			TArray<USkeletalMeshComponent*> SkeletalMeshComponents;
			Obj->GetComponents(USkeletalMeshComponent::StaticClass(), SkeletalMeshComponents);
			for (const auto Component : SkeletalMeshComponents)
			{
				if (!Component->DoesSocketExist(SocketName)) continue;
				FVector SocketLocation;
				FRotator SocketRotation;
				Component->GetSocketWorldLocationAndRotation(SocketName, SocketLocation, SocketRotation);
				SetActorLocation(FinalSocketOffset + SocketLocation);
				SetActorRotation(SocketRotation);
			}
		}
		if (GameState->BattleState.CurrentSequenceTime >= 0)
		{
			ScreenSpaceDepthOffset = 0;
			OrthoBlendActive = FMath::Lerp(OrthoBlendActive, 0, 0.2);
		}
		else
		{
			if (IsPlayer)
				ScreenSpaceDepthOffset = (MaxPlayerObjects - DrawPriority) * 25;
			else
				ScreenSpaceDepthOffset = (MaxBattleObjects - DrawPriority) * 15;
			OrthoBlendActive = FMath::Lerp(OrthoBlendActive, 1, 0.2);
		}
	}
	else
	{
		ScreenSpaceDepthOffset = 0;
		OrthoBlendActive = 1;
	}
	
	if (LinkedActor)
	{
		LinkedActor->SetActorScale3D(GetActorScale3D());
		LinkedActor->SetActorRotation(GetActorRotation());
		LinkedActor->SetActorLocation(GetActorLocation());
	}
	
	AddColor = FMath::Lerp(AddColor, AddFadeColor, AddFadeSpeed);
	MulColor = FMath::Lerp(MulColor, MulFadeColor, MulFadeSpeed);

	TInlineComponentArray<UPrimitiveComponent*> Components(this);
	GetComponents(Components);
	for (const auto Component : Components)
	{
		for (int64 i = 0; i < Component->GetNumMaterials(); i++)
		{
			if (const auto MIDynamic = Cast<UMaterialInstanceDynamic>(Component->GetMaterial(i)); IsValid(MIDynamic))
			{
				MIDynamic->SetScalarParameterValue(FName(TEXT("ScreenSpaceDepthOffset")), ScreenSpaceDepthOffset);
				MIDynamic->SetScalarParameterValue(FName(TEXT("OrthoBlendActive")), OrthoBlendActive);
				MIDynamic->SetVectorParameterValue(FName(TEXT("AddColor")), AddColor);
				MIDynamic->SetVectorParameterValue(FName(TEXT("MulColor")), MulColor);
			}
		}
		if (const auto Mesh = Cast<USkeletalMeshComponent>(Component); IsValid(Mesh))
		{
			if (const auto MIDynamic = Cast<UMaterialInstanceDynamic>(Mesh->OverlayMaterial); IsValid(MIDynamic))
			{
				MIDynamic->SetScalarParameterValue(FName(TEXT("ScreenSpaceDepthOffset")), ScreenSpaceDepthOffset);
				MIDynamic->SetScalarParameterValue(FName(TEXT("OrthoBlendActive")), OrthoBlendActive);
				MIDynamic->SetVectorParameterValue(FName(TEXT("AddColor")), AddColor);
				MIDynamic->SetVectorParameterValue(FName(TEXT("MulColor")), MulColor);
			}
		}
	}
	FrameBlendPosition = static_cast<float>(MaxCelTime - TimeUntilNextCel) / static_cast<float>(MaxCelTime);
}

void ABattleObject::FuncCall(const FName& FuncName) const
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
	for (int j = 0; j < CollisionArraySize; j++)
	{
		Boxes[j].Type = BOX_Hurt;
		Boxes[j].PosX = -10000000;
		Boxes[j].PosY = -10000000;
		Boxes[j].SizeX = 0;
		Boxes[j].SizeY = 0;
	}
	if (Player->CommonCollisionData != nullptr)
	{
		for (int i = 0; i < Player->CommonCollisionData->CollisionFrames.Num(); i++)
		{
			if (Player->CommonCollisionData->CollisionFrames[i].CelName == CelName.ToString())
			{
				AnimName = FName(Player->CommonCollisionData->CollisionFrames[i].AnimName);
				AnimSequence = Player->CommonCollisionData->CollisionFrames[i].AnimSequence;
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
			}
			if (Player->CommonCollisionData->CollisionFrames[i].CelName == BlendCelName.ToString())
			{
				BlendAnimName = FName(Player->CommonCollisionData->CollisionFrames[i].AnimName);
				BlendAnimSequence = Player->CommonCollisionData->CollisionFrames[i].AnimSequence;
				BlendAnimFrame = Player->CommonCollisionData->CollisionFrames[i].AnimFrame;
				for (int j = 0; j < CollisionArraySize; j++)
				{
					if (j < Player->CommonCollisionData->CollisionFrames[i].Boxes.Num())
					{
						if (Player->CommonCollisionData->CollisionFrames[i].Boxes[j].Type != BOX_Offset) continue;

						NextOffsetX = Player->CommonCollisionData->CollisionFrames[i].Boxes[j].PosX;
						NextOffsetY = Player->CommonCollisionData->CollisionFrames[i].Boxes[j].PosY;
					}
				}
			}
		}
	}
	if (Player->CollisionData != nullptr)
	{
		for (int i = 0; i < Player->CollisionData->CollisionFrames.Num(); i++)
		{
			if (Player->CollisionData->CollisionFrames[i].CelName == CelName.ToString())
			{
				AnimName = FName(Player->CollisionData->CollisionFrames[i].AnimName);
				AnimSequence = Player->CollisionData->CollisionFrames[i].AnimSequence;
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
			}
			if (Player->CollisionData->CollisionFrames[i].CelName == BlendCelName.ToString())
			{
				BlendAnimName = FName(Player->CollisionData->CollisionFrames[i].AnimName);
				BlendAnimSequence = Player->CollisionData->CollisionFrames[i].AnimSequence;
				BlendAnimFrame = Player->CollisionData->CollisionFrames[i].AnimFrame;
				for (int j = 0; j < CollisionArraySize; j++)
				{
					if (j < Player->CollisionData->CollisionFrames[i].Boxes.Num())
					{
						if (Player->CollisionData->CollisionFrames[i].Boxes[j].Type != BOX_Offset) continue;

						NextOffsetX = Player->CollisionData->CollisionFrames[i].Boxes[j].PosX;
						NextOffsetY = Player->CollisionData->CollisionFrames[i].Boxes[j].PosY;
					}
				}
			}
		}
	}
}

void ABattleObject::InitObject()
{
	if (IsPlayer)
		return;
	if (IsValid(LinkedParticle))
	{
		LinkedParticle->Deactivate();
	}
	ObjectState->Parent = this;
	TriggerEvent(EVT_Enter);
	FVector Location = FVector(static_cast<float>(PosX) / COORD_SCALE, static_cast<float>(PosZ) / COORD_SCALE, static_cast<float>(PosY) / COORD_SCALE);
	Location = GameState->BattleSceneTransform.GetRotation().RotateVector(Location) + GameState->BattleSceneTransform.GetLocation();
	SetActorLocation(Location);
	SetActorRotation(GameState->BattleSceneTransform.GetRotation());
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
	CalculatePushbox();

	if (!IsPlayer && StopLinkObj)
	{
		Hitstop = StopLinkObj->Hitstop;
	}
	
	if (Hitstop > 0) //break if hitstop active.
	{
		Hitstop--;
		return;
	}
	
	if (!IsPlayer && MiscFlags & MISC_DeactivateOnNextUpdate)
	{
		ResetObject();
		return;
	}

	if (IsPlayer)
		if (Player->PlayerFlags & PLF_IsThrowLock)
			return;
	
	if (Timer0 > 0)
	{
		--Timer0;
		if (Timer0 == 0) TriggerEvent(EVT_Timer0);
	}
	if (Timer1 > 0)
	{
		--Timer1;
		if (Timer1 == 0) TriggerEvent(EVT_Timer1);
	}

	if (MiscFlags & MISC_FlipEnable)
		HandleFlip();
		
	Move();
	
	GameState->SetScreenBounds();
	GameState->SetStageBounds();
	
	if (PosY == GroundHeight && PrevPosY != GroundHeight)
	{
		if (!IsPlayer)
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
		TriggerEvent(EVT_Update);
		TimeUntilNextCel--;
		if (TimeUntilNextCel == 0)
			CelIndex++;
		
		GameState->SetScreenBounds();
		GameState->SetStageBounds();
		ActionTime++;

		if (MiscFlags & MISC_DeactivateIfBeyondBounds)
		{
			if (PosX > GameState->BattleState.ScreenBounds + 360000 + GameState->BattleState.StageBounds
				|| PosX < -GameState->BattleState.ScreenBounds - 360000 - GameState->BattleState.StageBounds)
				DeactivateObject();
		}
	}
}

void ABattleObject::ResetObject()
{
	if (IsPlayer)
		return;
	
	if (IsValid(LinkedParticle))
	{
		LinkedParticle->Deactivate();
	}
	RemoveLinkActor();
	IsActive = false;
	PosX = 0;
	PosY = 0;
	PosZ = 0;
	PrevPosX = 0;
	PrevPosY = 0;
	PrevPosZ = 0;
	PrevOffsetX = 0;
	PrevOffsetY = 0;
	NextOffsetX = 0;
	NextOffsetY = 0;
	SpeedX = 0;
	SpeedY = 0;
	SpeedZ = 0;
	Gravity = 0;
	Inertia = 0;
	ActionTime = 0;
	PushHeight = 0;
	PushHeightLow = 0;
	PushWidth = 0;
	PushWidthExtend  = 0;
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
	StunTimeMax = 0;
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
	Timer0 = 0;
	Timer1 = 0;
	DrawPriority = MaxBattleObjects;
	HomingParams = FHomingParams();
	CelName = FName();
	BlendCelName = FName();
	AnimName = FName();
	AnimFrame = 0;
	BlendAnimFrame = 0;
	FrameBlendPosition = 0;
	CelIndex = 0;
	TimeUntilNextCel = 0;
	MaxCelTime = 0;
	for (auto& Handler : EventHandlers)
		Handler = FEventHandler();
	EventHandlers[EVT_Enter].FunctionName = FName("Init");	
	HitPosX = 0;
	HitPosY = 0;
	for (auto& Box : Boxes)
	{
		Box = FCollisionBox();
	}
	ObjectStateName = FName();
	ObjectID = 0;
	Player = nullptr;
	AttackTarget = nullptr;
	StopLinkObj = nullptr;
	PositionLinkObj = nullptr;
	MaterialLinkObj = nullptr;
	SocketName = FName();
	SocketObj = OBJ_Self;
	SocketOffset = FVector::ZeroVector;
	ObjectScale = FVector::OneVector;
	AddColor = FLinearColor(0,0,0,1);
	MulColor = FLinearColor(1,1,1,1);
	AddFadeColor = FLinearColor(0,0,0,1);
	MulFadeColor = FLinearColor(1,1,1,1);
	AddFadeSpeed = 0;
	MulFadeSpeed = 0;
	ObjectsToIgnoreHitsFrom.Empty();
	for (const auto Object : GameState->SortedObjects)
	{
		Object->ObjectsToIgnoreHitsFrom.Remove(this);
	}
}

bool ABattleObject::IsStopped() const
{
	if (!GameState) return false;
	if (!IsPlayer && IsValid(StopLinkObj) && StopLinkObj->IsStopped()) return true;
	if (GameState->BattleState.SuperFreezeDuration && this != GameState->BattleState.SuperFreezeCaller) return true;
	if (GameState->BattleState.SuperFreezeSelfDuration && this == GameState->BattleState.SuperFreezeCaller) return true;
	return Hitstop > 0 || (IsPlayer && Player->PlayerFlags & PLF_IsThrowLock);
}

bool ABattleObject::IsTimerPaused() const
{
	if (!GameState) return false;
	return GameState->BattleState.PauseTimer;
}

void ABattleObject::CallSubroutine(FString Name)
{
	if (Player->CommonSubroutineNames.Find(FName(Name)) != INDEX_NONE)
	{
		Player->CommonSubroutines[Player->CommonSubroutineNames.Find(FName(Name))]->Parent = this;
		Player->CommonSubroutines[Player->CommonSubroutineNames.Find(FName(Name))]->Exec();
		return;
	}

	if (Player->SubroutineNames.Find(FName(Name)) != INDEX_NONE)
	{
		Player->Subroutines[Player->SubroutineNames.Find(FName(Name))]->Parent = this;
		Player->Subroutines[Player->SubroutineNames.Find(FName(Name))]->Exec();
	}
}

void ABattleObject::CallSubroutineWithArgs(FString Name, int32 Arg1, int32 Arg2, int32 Arg3, int32 Arg4)
{
	SubroutineReg1 = Arg1;
	SubroutineReg2 = Arg2;
	SubroutineReg3 = Arg3;
	SubroutineReg4 = Arg4;
	CallSubroutine(Name);
}

void ABattleObject::InitEventHandler(EEventType EventType, FName FuncName, int32 Value, FString SubroutineName)
{
	switch (EventType)
	{
	case EVT_Timer0:
		Timer0 = Value;
		break;
	case EVT_Timer1:
		Timer1 = Value;
		break;
	case EVT_Update:
		UpdateTime = 0;
	default: break;
	}
	EventHandlers[EventType].FunctionName = FName(FuncName.ToString());
	EventHandlers[EventType].SubroutineName = FName(SubroutineName);
}

void ABattleObject::RemoveEventHandler(EEventType EventType)
{
	EventHandlers[EventType].FunctionName = FName();
	EventHandlers[EventType].SubroutineName = FName();
	if (EventType == EVT_Update)
		UpdateTime = 0;
}

FString ABattleObject::GetCelName() const
{
	return CelName.ToString();
}

FString ABattleObject::GetAnimName() const
{
	return AnimName.ToString();
}

FString ABattleObject::GetBlendAnimName() const
{
	return BlendAnimName.ToString();
}

FString ABattleObject::GetLabelName() const
{
	return LabelName.ToString();
}

void ABattleObject::SetCelName(FString InName)
{
	CelName = FName(InName);
	SetBlendCelName("");

	GetBoxes();

	// Get position offset from boxes
	for (auto Box : Boxes)
	{
		if (Box.Type == BOX_Offset)
		{
			PosY += Box.PosY - PrevOffsetY;
			AddPosXWithDir(Box.PosX - PrevOffsetX);

			PrevOffsetX = Box.PosX;
			PrevOffsetY = Box.PosY;
		}
	}
}

void ABattleObject::SetBlendCelName(FString InName)
{
	BlendCelName = FName(InName);
	FrameBlendPosition = 0;
	
	GetBoxes();
}

void ABattleObject::GotoLabel(FString InName, bool ResetState)
{
	if (!GameState && !CharaSelectGameState) return;
	LabelName = FName(InName);
	if (IsPlayer && ResetState)
		Player->JumpToState(Player->GetCurrentStateName(), true);
	else
		GotoLabelActive = true;
}

void ABattleObject::SetTimeUntilNextCel(int32 InTime)
{
	TimeUntilNextCel = MaxCelTime = InTime;
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

int32 ABattleObject::GetPosYCenter() const
{
	int32 CenterPosY = PosY;
	if (IsPlayer)
	{
		switch (Player->Stance)
		{
		case ACT_Standing:
		case ACT_Jumping:
		default:
			CenterPosY += 200000;
			break;
		case ACT_Crouching:
			CenterPosY += 90000;
			break;
		}
	}
	return CenterPosY;
}

int32 ABattleObject::CalculateDistanceBetweenPoints(EDistanceType Type, EObjType Obj1, EPosType Pos1, EObjType Obj2,
                                                    EPosType Pos2)
{
	const ABattleObject* Actor1 = GetBattleObject(Obj1);
	const ABattleObject* Actor2 = GetBattleObject(Obj2);
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
				ObjDist = (PosX2 - PosX1) * DirFlag;
			}
			break;
		default:
			return 0;
		}
		return ObjDist;
	}
	return 0;
}

int32 ABattleObject::CalculateAngleBetweenPoints(EObjType Obj1, EPosType Pos1, EObjType Obj2, EPosType Pos2)
{
	const ABattleObject* Actor1 = GetBattleObject(Obj1);
	const ABattleObject* Actor2 = GetBattleObject(Obj2);
	if (IsValid(Actor1) && IsValid(Actor2))
	{
		int32 PosX1 = 0;
		int32 PosX2 = 0;
		int32 PosY1 = 0;
		int32 PosY2 = 0;

		Actor1->PosTypeToPosition(Pos1, &PosX1, &PosY1);
		Actor2->PosTypeToPosition(Pos2, &PosX2, &PosY2);
		
		const auto X = abs(PosX2 - PosX1);
		const auto Y = PosY2 - PosY1;

		return UNightSkyBlueprintFunctionLibrary::Vec2Angle_x1000(X, Y);
	}
	return 0;
}

void ABattleObject::SetFacing(EObjDir NewDir)
{
	Direction = NewDir;
}

void ABattleObject::FlipObject()
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

bool ABattleObject::CheckIsGrounded() const
{
	return PosY <= GroundHeight;
}

void ABattleObject::EnableHit(bool Enabled)
{
	if (Enabled)
	{
		AttackFlags |= ATK_HitActive;

		if (GameState)
		{
			for (const auto Object : GameState->SortedObjects)
			{
				Object->ObjectsToIgnoreHitsFrom.Remove(this);
			}
		}
	}
	else
	{
		AttackFlags &= ~ATK_HitActive;
	}
	AttackFlags &= ~ATK_HasHit;
	
	if (!IsPlayer)
	{
		SetProjectileAttribute(true);
	}
	else if (Player->StoredStateMachine.CurrentState->EntryStance == EEntryStance::Jumping)
	{
		Player->SetHeadAttribute(true);
	}
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
	AttackFlags &= ~ATK_HitActive;
}

void ABattleObject::SetProjectileAttribute(bool Attribute)
{
	if (Attribute)
		AttackFlags |= ATK_AttackProjectileAttribute;
	else
		AttackFlags &= ~ATK_AttackProjectileAttribute;
}

void ABattleObject::SetProrateOnce(bool Once)
{
	if (Once)
		AttackFlags |= ATK_ProrateOnce;
	else
		AttackFlags &= ~ATK_ProrateOnce;
}

void ABattleObject::SetIgnoreOTG(bool Ignore)
{
	if (Ignore)
		AttackFlags |= ATK_IgnoreOTG;
	else
		AttackFlags &= ~ATK_IgnoreOTG;
}

void ABattleObject::SetIgnorePushbackScaling(bool Ignore)
{
	if (Ignore)
		AttackFlags |= ATK_IgnorePushbackScaling;
	else
		AttackFlags &= ~ATK_IgnorePushbackScaling;
}

void ABattleObject::SetIgnoreHitstunScaling(bool Ignore)
{
	if (Ignore)
		AttackFlags |= ATK_IgnoreHitstunScaling;
	else
		AttackFlags &= ~ATK_IgnoreHitstunScaling;
}

void ABattleObject::DeactivateObject()
{
	if (IsPlayer) // Don't use on players
		return;
	// Remove from player cache
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

void ABattleObject::SetWallCollisionActive(bool Active)
{
	if (Active)
		MiscFlags |= MISC_WallCollisionActive;
	else
		MiscFlags &= ~MISC_WallCollisionActive;
}

void ABattleObject::SetPushCollisionActive(bool Active)
{
	if (Active)
		MiscFlags |= MISC_PushCollisionActive;
	else
		MiscFlags &= ~MISC_PushCollisionActive;
}

void ABattleObject::SetPushWidthExtend(int32 Extend)
{
	PushWidthExtend = Extend;
}

void ABattleObject::CreateCommonParticle(FString Name, EPosType PosType, FVector Offset, FRotator Rotation)
{
	if (!GameState) return;
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
				Rotation += GameState->BattleSceneTransform.GetRotation().Rotator();
				int32 TmpPosX;
				int32 TmpPosY;
				PosTypeToPosition(PosType, &TmpPosX, &TmpPosY);
				FVector FinalLocation = Offset + FVector(TmpPosX / COORD_SCALE, 0, TmpPosY / COORD_SCALE);
				FinalLocation = GameState->BattleSceneTransform.GetRotation().RotateVector(FinalLocation) + GameState->BattleSceneTransform.GetLocation();
				UNiagaraComponent* NiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ParticleStruct.ParticleSystem, FinalLocation, Rotation, GetActorScale());
				GameState->ParticleManager->BattleParticles.Add(FBattleParticle(NiagaraComponent, nullptr));
				NiagaraComponent->SetAgeUpdateMode(ENiagaraAgeUpdateMode::DesiredAge);
				NiagaraComponent->SetDesiredAge(0);
				NiagaraComponent->SetVariableFloat(FName("SpriteRotate"), -Rotation.Pitch);
				if (Direction == DIR_Left)
				{
					NiagaraComponent->SetVariableVec2(FName("UVScale"), FVector2D(-1, 1));
					NiagaraComponent->SetVariableVec2(FName("PivotOffset"), FVector2D(0, 0.5));
				}
				break;
			}
		}
	}
}

void ABattleObject::CreateCharaParticle(FString Name, EPosType PosType, FVector Offset, FRotator Rotation)
{
	if (!GameState) return;
	if (Player->CharaParticleData != nullptr)
	{
		for (FParticleStruct ParticleStruct : Player->CharaParticleData->ParticleStructs)
		{
			if (ParticleStruct.Name == Name)
			{
				if (Direction == DIR_Left)
					Offset = FVector(-Offset.X, Offset.Y, Offset.Z);
				Rotation += GameState->BattleSceneTransform.GetRotation().Rotator();
				int32 TmpPosX;
				int32 TmpPosY;
				PosTypeToPosition(PosType, &TmpPosX, &TmpPosY);
				FVector FinalLocation = Offset + FVector(TmpPosX / COORD_SCALE, 0, TmpPosY / COORD_SCALE);
				FinalLocation = GameState->BattleSceneTransform.GetRotation().RotateVector(FinalLocation) + GameState->BattleSceneTransform.GetLocation();
				UNiagaraComponent* NiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ParticleStruct.ParticleSystem, FinalLocation, Rotation, GetActorScale());
				GameState->ParticleManager->BattleParticles.Add(FBattleParticle(NiagaraComponent, nullptr));
				NiagaraComponent->SetAgeUpdateMode(ENiagaraAgeUpdateMode::DesiredAge);
				NiagaraComponent->SetDesiredAge(0);
				NiagaraComponent->SetVariableFloat(FName("SpriteRotate"), -Rotation.Pitch);
				if (Direction == DIR_Left)
				{
					NiagaraComponent->SetVariableVec2(FName("UVScale"), FVector2D(-1, 1));
					NiagaraComponent->SetVariableVec2(FName("PivotOffset"), FVector2D(0, 0.5));
				}
				break;
			}
		}
	}
}

void ABattleObject::LinkCommonParticle(FString Name)
{
	if (!GameState) return;
	if (IsPlayer)
		return;
	if (Player->CommonParticleData != nullptr)
	{
		for (FParticleStruct ParticleStruct : Player->CommonParticleData->ParticleStructs)
		{
			if (ParticleStruct.Name == Name)
			{
				if (IsValid(LinkedParticle))
					LinkedParticle->Deactivate();
				LinkedParticle = UNiagaraFunctionLibrary::SpawnSystemAttached(
					ParticleStruct.ParticleSystem, RootComponent, FName(), FVector(), FRotator(),
					EAttachLocation::SnapToTargetIncludingScale, true);
				LinkedParticle->SetAgeUpdateMode(ENiagaraAgeUpdateMode::DesiredAge);
				LinkedParticle->SetDesiredAge(0);
				GameState->ParticleManager->BattleParticles.Add(FBattleParticle(LinkedParticle, this));
				if (Direction == DIR_Left)
					LinkedParticle->SetVariableVec2(FName("UVScale"), FVector2D(-1, 1));
				break;
			}
		}
	}
}

void ABattleObject::LinkCharaParticle(FString Name)
{
	if (!GameState) return;
	if (IsPlayer)
		return;
	if (Player->CharaParticleData != nullptr)
	{
		for (FParticleStruct ParticleStruct : Player->CharaParticleData->ParticleStructs)
		{
			if (ParticleStruct.Name == Name)
			{
				if (IsValid(LinkedParticle))
					LinkedParticle->Deactivate();
				LinkedParticle = UNiagaraFunctionLibrary::SpawnSystemAttached(
					ParticleStruct.ParticleSystem, RootComponent, FName(), FVector(), FRotator(),
					EAttachLocation::SnapToTargetIncludingScale, true);
				LinkedParticle->SetAgeUpdateMode(ENiagaraAgeUpdateMode::DesiredAge);
				GameState->ParticleManager->BattleParticles.Add(FBattleParticle(LinkedParticle, this));
				if (Direction == DIR_Left)
					LinkedParticle->SetVariableVec2(FName("UVScale"), FVector2D(-1, 1));
				break;
			}
		}
	}
}

AActor* ABattleObject::LinkActor(FString Name)
{
	if (!GameState) return nullptr;
	if (IsPlayer)
		return nullptr;
	
	RemoveLinkActor();
	for (auto& Container : Player->StoredLinkActors)
	{
		if (Container.Name == Name && !Container.bIsActive)
		{
			Container.bIsActive = true;
			LinkedActor = Container.StoredActor;
			return LinkedActor;
		}
	}
	return nullptr;
}

void ABattleObject::RemoveLinkActor()
{
	if (!LinkedActor) return;

	for (auto& Container : Player->StoredLinkActors)
	{
		if (Container.StoredActor == LinkedActor)
		{
			Container.bIsActive = false;
			LinkedActor = nullptr;
		}
	}
}

void ABattleObject::PlayCommonSound(FString Name)
{
	if (!IsValid(GameState))
		return;
	if (Player->CommonSoundData != nullptr)
	{
		for (FSoundStruct SoundStruct : Player->CommonSoundData->SoundDatas)
		{
			if (SoundStruct.Name == Name)
			{
				GameState->PlayCommonAudio(SoundStruct.SoundWave, SoundStruct.MaxDuration);
				break;
			}
		}
	}
}

void ABattleObject::PlayCharaSound(FString Name)
{
	if (!IsValid(GameState))
		return;
	if (Player->SoundData != nullptr)
	{
		for (FSoundStruct SoundStruct : Player->SoundData->SoundDatas)
		{
			if (SoundStruct.Name == Name)
			{
				GameState->PlayCharaAudio(SoundStruct.SoundWave, SoundStruct.MaxDuration);
				break;
			}
		}
	}
}

void ABattleObject::AttachToSocketOfObject(FString InSocketName, FVector Offset, EObjType ObjType)
{
	SocketName = FName(InSocketName);
	SocketObj = ObjType;
	SocketOffset = Offset;
}

void ABattleObject::DetachFromSocket()
{
	SocketName = FName();
	SocketObj = OBJ_Self;
	SocketOffset = FVector::ZeroVector;
}

void ABattleObject::CameraShake(FString PatternName, int32 Scale)
{
	if (!GameState) return;
	if (IsValid(Player->CameraShakeData))
	{
		for (auto [Name, CameraShake] : Player->CameraShakeData->CamerShakeStructs)
		{
			if (Name == PatternName)
				GameState->CameraShake(CameraShake, static_cast<float>(Scale) / 1000);
		}
	}
}

int32 ABattleObject::GenerateRandomNumber(int32 Min, int32 Max) const
{
	if (Min > Max)
	{
		const int32 Temp = Max;
		Max = Min;
		Min = Temp;
	}
	int32 Result = GameState->BattleState.RandomManager.Rand();
	Result = Result % (Max - Min + 1) + Min;
	return Result;
}

void ABattleObject::StartSuperFreeze(int Duration, int SelfDuration)
{
	if (!GameState) return;
	GameState->StartSuperFreeze(Duration, SelfDuration, this);
	if (Duration > 0) TriggerEvent(EVT_SuperFreeze);
}

void ABattleObject::IgnoreSuperFreeze(bool Ignore)
{
	if (Ignore)
		MiscFlags |= MISC_IgnoreSuperFreeze;
	else
		MiscFlags &= ~MISC_IgnoreSuperFreeze;
}

void ABattleObject::SetObjectID(int InObjectID)
{
	ObjectID = InObjectID;
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

ABattleObject* ABattleObject::AddCommonBattleObject(FString InStateName, int32 PosXOffset, int32 PosYOffset,
	EPosType PosType)
{
	if (!GameState) return nullptr;
	int StateIndex = Player->CommonObjectStateNames.Find(FName(InStateName));
	if (StateIndex != INDEX_NONE)
	{		
		int32 FinalPosX, FinalPosY;
		if (Direction == DIR_Left)
			PosXOffset = -PosXOffset;

		PosTypeToPosition(PosType, &FinalPosX, &FinalPosY);
		FinalPosX += PosXOffset;
		FinalPosY += PosYOffset;
		return GameState->AddBattleObject(Player->CommonObjectStates[StateIndex],
			FinalPosX, FinalPosY, Direction, StateIndex, true, Player);
	}
	return nullptr;
}

ABattleObject* ABattleObject::AddBattleObject(FString InStateName, int32 PosXOffset, int32 PosYOffset, EPosType PosType)
{
	if (!GameState) return nullptr;
	const int StateIndex = Player->ObjectStateNames.Find(FName(InStateName));
	if (StateIndex != INDEX_NONE)
	{
		int32 FinalPosX, FinalPosY;
		if (Direction == DIR_Left)
			PosXOffset = -PosXOffset;

		PosTypeToPosition(PosType, &FinalPosX, &FinalPosY);
		FinalPosX += PosXOffset;
		FinalPosY += PosYOffset;
		return GameState->AddBattleObject(Player->ObjectStates[StateIndex],
			FinalPosX, FinalPosY, Direction, StateIndex, false, Player);
	}
	return nullptr;
}

void ABattleObject::EnableDeactivateIfBeyondBounds(bool Enable)
{
	if (Enable)
	{
		MiscFlags |= MISC_DeactivateIfBeyondBounds;
	}
	else
	{
		MiscFlags &= ~MISC_DeactivateIfBeyondBounds;
	}
}

void ABattleObject::EnableDeactivateOnStateChange(bool Enable)
{
	if (Enable)
	{
		MiscFlags |= MISC_DeactivateOnStateChange;
	}
	else
	{
		MiscFlags &= ~MISC_DeactivateOnStateChange;
	}
}

void ABattleObject::EnableDeactivateOnReceiveHit(bool Enable)
{
	if (Enable)
	{
		MiscFlags |= MISC_DeactivateOnReceiveHit;
	}
	else
	{
		MiscFlags &= ~MISC_DeactivateOnReceiveHit;
	}
}
