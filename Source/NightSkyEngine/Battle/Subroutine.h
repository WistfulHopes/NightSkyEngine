// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SerializableObj.h"
#include "UObject/Object.h"
#include "Subroutine.generated.h"

class ABattleObject;

/**
 * @brief A subroutine callable from any player or object state.
 *
 * Allows encapsulating commonly used code that can be reused in states.
 */
UCLASS(BlueprintType, Blueprintable)
class USubroutine : public USerializableObj
{
	GENERATED_BODY()
public:
	/**
	 * The object that currently owns this subroutine instance.
	 * The last object to use this subroutine will be the owner.
	 */
	UPROPERTY(BlueprintReadOnly)
	ABattleObject* Parent;
	/**
	 * The name of the subroutine.
	 * Used to call the subroutine.
	 */
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FString Name;

	/**
	 * The primary function of the subroutine.
	 */
	UFUNCTION(BlueprintNativeEvent)
	void Exec();
};
