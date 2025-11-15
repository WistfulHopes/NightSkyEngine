// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetUserData.h"
#include "NightSkyAnimSequenceUserData.generated.h"

USTRUCT(BlueprintType)
struct FAnimVector
{
	GENERATED_BODY()

	int32 X;
	int32 Y;
	int32 Z;
};

FORCEINLINE FArchive operator <<(FArchive& Ar, FAnimVector& InVal)
{
	Ar << InVal.X;
	Ar << InVal.Y;
	Ar << InVal.Z;
	return Ar;
}

USTRUCT(BlueprintType)
struct FAnimRotator
{
	GENERATED_BODY()

	int32 Pitch;
	int32 Yaw;
	int32 Roll;
};

FORCEINLINE FArchive operator <<(FArchive& Ar, FAnimRotator& InVal)
{
	Ar << InVal.Pitch;
	Ar << InVal.Yaw;
	Ar << InVal.Roll;
	return Ar;
}

USTRUCT(BlueprintType)
struct FAnimTransform
{
	GENERATED_BODY()

	FAnimVector Position;
	FAnimRotator Rotation;
	FAnimVector Scale;
};

FORCEINLINE FArchive operator <<(FArchive& Ar, FAnimTransform& InVal)
{
	Ar << InVal.Position;
	Ar << InVal.Rotation;
	Ar << InVal.Scale;
	return Ar;
}

/**
 * 
 */
UCLASS(EditInlineNew)
class NIGHTSKYENGINE_API UNightSkyAnimSequenceUserData : public UAssetUserData
{
	GENERATED_BODY()

private:
	UPROPERTY()
	int32 FrameCount;
	
	UPROPERTY()
	int32 FrameRate;

	TMap<FName, TMap<int32, FAnimTransform>> MeshSpaceBoneTransforms;
	TMap<int32, FAnimVector> RootTranslation;

	virtual void Serialize(FArchive& Ar) override;

public:
	virtual void PostEditChangeOwner(const FPropertyChangedEvent& PropertyChangedEvent) override;

	UFUNCTION(BlueprintPure)
	int32 GetFrameCount() const
	{
		return FrameCount;
	}

	UFUNCTION(BlueprintPure)
	int32 GetFrameRate() const
	{
		return FrameRate;
	}
	
	UFUNCTION(BlueprintPure)
	FAnimVector GetRootTranslationAtTime(int32 Time) const;

	UFUNCTION(BlueprintPure)
	FAnimTransform GetCachedBoneTransformAtTime(FName BoneName, int32 Time, bool bRelativeToRoot) const;
    
	UFUNCTION(BlueprintPure)
	FAnimVector GetCachedBoneLocationAtTime(FName BoneName, int32 Time, bool bRelativeToRoot) const;
};
