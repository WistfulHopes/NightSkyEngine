// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NightSkyPlayerController.generated.h"

class UInputAction;
class UInputMappingContext;
class ANetworkPawn;

USTRUCT()
struct FBattleInputActions
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TObjectPtr<const UInputAction> PressUp;
	UPROPERTY(EditAnywhere)
	TObjectPtr<const UInputAction> ReleaseUp;
	UPROPERTY(EditAnywhere)
	TObjectPtr<const UInputAction> PressDown;
	UPROPERTY(EditAnywhere)
	TObjectPtr<const UInputAction> ReleaseDown;
	UPROPERTY(EditAnywhere)
	TObjectPtr<const UInputAction> PressLeft;
	UPROPERTY(EditAnywhere)
	TObjectPtr<const UInputAction> ReleaseLeft;
	UPROPERTY(EditAnywhere)
	TObjectPtr<const UInputAction> PressRight;
	UPROPERTY(EditAnywhere)
	TObjectPtr<const UInputAction> ReleaseRight;
	UPROPERTY(EditAnywhere)
	TObjectPtr<const UInputAction> PressA;
	UPROPERTY(EditAnywhere)
	TObjectPtr<const UInputAction> ReleaseA;
	UPROPERTY(EditAnywhere)
	TObjectPtr<const UInputAction> PressB;
	UPROPERTY(EditAnywhere)
	TObjectPtr<const UInputAction> ReleaseB;
	UPROPERTY(EditAnywhere)
	TObjectPtr<const UInputAction> PressC;
	UPROPERTY(EditAnywhere)
	TObjectPtr<const UInputAction> ReleaseC;
	UPROPERTY(EditAnywhere)
	TObjectPtr<const UInputAction> PressD;
	UPROPERTY(EditAnywhere)
	TObjectPtr<const UInputAction> ReleaseD;
	UPROPERTY(EditAnywhere)
	TObjectPtr<const UInputAction> PressE;
	UPROPERTY(EditAnywhere)
	TObjectPtr<const UInputAction> ReleaseE;
	UPROPERTY(EditAnywhere)
	TObjectPtr<const UInputAction> PressF;
	UPROPERTY(EditAnywhere)
	TObjectPtr<const UInputAction> ReleaseF;
	UPROPERTY(EditAnywhere)
	TObjectPtr<const UInputAction> PressG;
	UPROPERTY(EditAnywhere)
	TObjectPtr<const UInputAction> ReleaseG;
	UPROPERTY(EditAnywhere)
	TObjectPtr<const UInputAction> PressH;
	UPROPERTY(EditAnywhere)
	TObjectPtr<const UInputAction> ReleaseH;
	UPROPERTY(EditAnywhere)
	TObjectPtr<const UInputAction> PauseGame;
};

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
	bool bRematch;

	UPROPERTY(EditAnywhere, Category="Input")
	TSoftObjectPtr<UInputMappingContext> InputMapping;
	UPROPERTY(EditAnywhere, Category="Input")
	FBattleInputActions InputActions;

	void RemapKeys() const;
	
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
	
	void SendGgpo(ANetworkPawn* InNetworkPawn, bool Client) const;
	
	UFUNCTION(BlueprintCallable)
	void SendBattleData();
	UFUNCTION(BlueprintCallable)
	void Rematch();

	UPROPERTY(BlueprintReadOnly)
	ANetworkPawn* NetworkPawn;

	UFUNCTION(BlueprintImplementableEvent)
	void OpenPauseMenu();

	UFUNCTION(BlueprintImplementableEvent)
	void ClosePauseMenu();
};
