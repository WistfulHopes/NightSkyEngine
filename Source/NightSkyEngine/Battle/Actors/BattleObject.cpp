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

	SpeedX *= SpeedXRatePerFrame;
	SpeedY *= SpeedYRatePerFrame;
	SpeedZ *= SpeedZRatePerFrame;
	const int32 FinalSpeedX = SpeedX * SpeedXRate / 100;;
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

	Pushback = Pushback - Pushback / 10;
	if (Pushback > -875 && Pushback < 875) //if inertia small enough, set to zero
	{
		Pushback = 0;
	}
	AddPosXWithDir(Pushback);

	AddPosXWithDir(FinalSpeedX); //apply speed

	if (IsPlayer && Player != nullptr)
	{
		if (Player->AirDashTimer <= 0 || (SpeedY > 0 && ActionTime < 5)) // only set y speed if not airdashing/airdash startup not done
		{
			PosY += FinalSpeedY;
			if (PosY > 0)
				SpeedY -= Gravity;
		}
		else
			SpeedY = 0;
	}
	else
	{
		PosY += FinalSpeedY;
		if (PosY > 0)
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
		if (Hitstop <= 0 && (!OtherObj->IsPlayer || (OtherObj->Player->PlayerFlags & PLF_IsThrowLock) == 0) || (!IsPlayer || Player->PlayerFlags & PLF_IsThrowLock) == 0)
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
				AddPosXWithDir(PosXOffset);
			}
		}
	}
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
	SetActorLocation(FVector(static_cast<float>(PosX) / COORD_SCALE, static_cast<float>(PosY) / COORD_SCALE, static_cast<float>(PosZ) / COORD_SCALE)); //set visual location and scale in unreal
	if (Direction == DIR_Left)
	{
		SetActorScale3D(FVector(1, -1, 1));
	}
	else
	{
		SetActorScale3D(FVector(1, 1, 1));
	}
}

void ABattleObject::Update()
{
	//run input buffer before checking hitstop
	if (IsPlayer && IsValid(Player))
	{
		if (!Direction == DIR_Left && !Player->FlipInputs || Player->FlipInputs && Direction == DIR_Right) //flip inputs with direction
			{
			const unsigned int Bit1 = Player->Inputs >> 2 & 1;
			const unsigned int Bit2 = Player->Inputs >> 3 & 1;
			unsigned int x = Bit1 ^ Bit2;

			x = x << 2 | x << 3;

			Player->Inputs = Player->Inputs ^ x;
		}
	}

	if (Direction == DIR_Left)
	{
		SetActorScale3D(FVector(1, -1, 1));
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
		SuperFreezeTimer--;
		return;
	}
		
	if (Hitstop > 0) //break if hitstop active.
	{
		Hitstop--;
		return;
	}

	GetBoxes();
	Move();

	if (!IsPlayer)
		ObjectState->Exec();

	ActionTime++;
	
	TimeUntilNextCel--;
	if (TimeUntilNextCel == 0)
		CelIndex++;
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
	Pushback = 0;
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
	SpeedXRatePerFrame = false;
	SpeedYRate = 100;
	SpeedYRatePerFrame = false;
	SpeedZRate = 100;
	SpeedZRatePerFrame = false;
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
	MiscFlags = 0;
	IsPlayer = false;
	SuperFreezeTimer = 0;
	CelName.SetString("");
	AnimName.SetString("");
	AnimFrame = 0;
	CelIndex = 0;
	TimeUntilNextCel = 0;
	for (auto& Handler : EventHandlers)
		Handler = FEventHandler();
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

void ABattleObject::HaltMomentum()
{
	SpeedX = 0;
	SpeedY = 0;
	SpeedZ = 0;
	Gravity = 0;
	Inertia = 0;
	Pushback = 0;
}
