// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NightSkyPlayerController.generated.h"

class UInputMappingContext;
class ANetworkPawn;

UCLASS()
class NIGHTSKYENGINE_API ANightSkyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ANightSkyPlayerController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SetupInputComponent() override;
	
	int Inputs;
	int Frame;

	UPROPERTY(EditAnywhere, Category="Input")
	TSoftObjectPtr<UInputMappingContext> InputMapping;
	
	void PressUp();
	void ReleaseUp();
	void PressDown();
	void ReleaseDown();
	void PressLeft();
	void ReleaseLeft();
	void PressRight();
	void ReleaseRight();
	void PressA();
	void ReleaseA();
	void PressB();
	void ReleaseB();
	void PressC();
	void ReleaseC();
	void PressD();
	void ReleaseD();
	void PressE();
	void ReleaseE();
	void PressF();
	void ReleaseF();
	void PressG();
	void ReleaseG();
	void PressH();
	void ReleaseH();

	void PauseGame();
	
	void UpdateInput(int Input[], int32 InFrame) const;
	void SendGgpo(ANetworkPawn* InNetworkPawn, bool Client);
	
	UFUNCTION(BlueprintCallable)
	void SendBattleData();

	UPROPERTY(BlueprintReadOnly)
	ANetworkPawn* NetworkPawn;

	UFUNCTION(BlueprintImplementableEvent)
	void OpenPauseMenu();

	UFUNCTION(BlueprintImplementableEvent)
	void ClosePauseMenu();
};
