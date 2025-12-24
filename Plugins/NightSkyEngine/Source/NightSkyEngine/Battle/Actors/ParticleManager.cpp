// Fill out your copyright notice in the Description page of Project Settings.


#include "ParticleManager.h"
#include "NiagaraComponent.h"
#include "NightSkyEngine/Battle/NightSkyGameState.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ParticleManager)

// Sets default values
AParticleManager::AParticleManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AParticleManager::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AParticleManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AParticleManager::UpdateParticles()
{
	BattleParticles.RemoveAll([=](const FBattleParticle& Particle)
	{
		return !IsValid(Particle.NiagaraComponent);
	});
	for (const auto [NiagaraComponent, ParticleOwner] : BattleParticles)
	{
		if (IsValid(ParticleOwner) && ParticleOwner->IsStopped())
		{
			NiagaraComponent->SetPaused(false);
			NiagaraComponent->AdvanceSimulation(1, OneFrame / 1000);
			NiagaraComponent->SetDesiredAge(NiagaraComponent->GetDesiredAge());
			if (NiagaraComponent->IsComplete())
				NiagaraComponent->Deactivate();
			continue;
		}
		NiagaraComponent->SetPaused(false);
		NiagaraComponent->AdvanceSimulation(1, OneFrame);
		NiagaraComponent->SetDesiredAge(NiagaraComponent->GetDesiredAge() + OneFrame);
		if (NiagaraComponent->IsComplete())
			NiagaraComponent->Deactivate();
	}
}

void AParticleManager::PauseParticles()
{
	BattleParticles.RemoveAll([=](const FBattleParticle& Particle)
	{
		return !IsValid(Particle.NiagaraComponent);
	});
	for (const auto BattleParticle : BattleParticles)
	{
		BattleParticle.NiagaraComponent->SetPaused(true);
	}
}

void AParticleManager::RollbackParticles(int RollbackFrames)
{
	for (const auto BattleParticle : BattleParticles)
	{
		const auto NiagaraComponent = BattleParticle.NiagaraComponent;
		const int32 RollbackTime = NiagaraComponent->GetDesiredAge() * (1 / OneFrame) - RollbackFrames;
		if (RollbackTime < 0)
		{
			NiagaraComponent->Deactivate();
			continue;
		}
		NiagaraComponent->ResetSystem();
		NiagaraComponent->AdvanceSimulation(RollbackTime, OneFrame);
	}
}
