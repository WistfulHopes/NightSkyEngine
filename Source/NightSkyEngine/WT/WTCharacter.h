// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WTCharacter.generated.h"

class ANightSkyWTGameState;
class APlayerObject;

UCLASS()
class NIGHTSKYENGINE_API AWTCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWTCharacter();

	UPROPERTY(BlueprintReadOnly)
	ANightSkyWTGameState* GameState;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<APlayerObject> BattlePlayerClass;
	
	UPROPERTY(BlueprintReadOnly)
	APlayerObject* BattlePlayer;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void StartBattle(AWTCharacter* Opponent);

	UFUNCTION()
	void EndBattle();

	UFUNCTION(BlueprintImplementableEvent)
	void EndBattle_BP();
};
