// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NightSkyEngine/Battle/NightSkyGameState.h"
#include "NightSkyWTGameState.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBattleEndDelegate);

UCLASS()
class NIGHTSKYENGINE_API ANightSkyWTGameState : public ANightSkyGameState
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ANightSkyWTGameState();

	UPROPERTY(BlueprintReadWrite)
	bool bIsMatchEnd;
	
	UPROPERTY(BlueprintReadOnly)
	bool bIsBattling;

	UPROPERTY()
	FOnBattleEndDelegate OnBattleEndDelegate;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	void Init(APlayerObject* P1, APlayerObject* P2);
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
