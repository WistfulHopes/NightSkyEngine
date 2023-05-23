// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Subroutine.generated.h"

class ABattleObject;

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class USubroutine : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
	ABattleObject* Parent;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FString Name;

	UFUNCTION(BlueprintNativeEvent)
	void Exec();
};
