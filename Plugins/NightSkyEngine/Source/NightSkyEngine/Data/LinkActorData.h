// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "LinkActorData.generated.h"

USTRUCT(BlueprintType)
struct FLinkActorStruct
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	FGameplayTag Name;
	UPROPERTY(EditAnywhere)
	TSubclassOf<ALinkActor> ActorClass;
	UPROPERTY(EditAnywhere)
	int32 MaxInstances = 1;
};

/**
 * 
 */
UCLASS()
class NIGHTSKYENGINE_API ULinkActorData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	TArray<FLinkActorStruct> LinkedActorStructs;
};
