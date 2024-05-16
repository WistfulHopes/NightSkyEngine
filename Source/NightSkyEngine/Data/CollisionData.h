// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "NightSkyEngine/Battle/CollisionBox.h"
#include "CollisionData.generated.h"

USTRUCT()
struct FCollisionStruct
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	FString CelName;
	UPROPERTY(EditAnywhere)
	FString AnimName;
	UPROPERTY(EditAnywhere)
	UAnimSequenceBase* AnimSequence;
	UPROPERTY(EditAnywhere)
	int32 AnimFrame = 0;
	UPROPERTY(EditAnywhere)
	TArray<FCollisionBox> Boxes;
};

/**
 * 
 */
UCLASS()
class NIGHTSKYENGINE_API UCollisionData : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	TArray<FCollisionStruct> CollisionFrames;

	FCollisionStruct GetByCelName(const FString& CelName)
	{
		for (auto& CollisionFrame : CollisionFrames)
		{
			if (CollisionFrame.CelName == CelName) return CollisionFrame;
		}
		return FCollisionStruct();
	}
};
