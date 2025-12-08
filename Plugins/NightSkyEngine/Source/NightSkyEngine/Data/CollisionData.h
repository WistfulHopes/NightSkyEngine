// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "PaperFlipbook.h"
#include "NightSkyEngine/Battle/Misc/CollisionBox.h"
#include "CollisionData.generated.h"

class APlayerObject;

DECLARE_MULTICAST_DELEGATE(FOnCollisionFramesChanged);

USTRUCT()
struct FAnimStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FName PartName = "Body";
	UPROPERTY(EditAnywhere)
	UAnimSequenceBase* AnimSequence;
	UPROPERTY(EditAnywhere)
	UPaperFlipbook* Flipbook;
};

USTRUCT()
struct FCollisionStruct
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	FGameplayTag CelName;
	UPROPERTY(EditAnywhere)
	TArray<FAnimStruct> Anim;
	UPROPERTY(EditAnywhere)
	int32 AnimFrame = 0;
	UPROPERTY(EditAnywhere)
	float AnimBlendIn = 0.25;
	UPROPERTY(EditAnywhere)
	float AnimBlendOut = 0.25;
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

	FCollisionStruct GetByCelName(const FGameplayTag& CelName)
	{
		for (auto& CollisionFrame : CollisionFrames)
		{
			if (CollisionFrame.CelName == CelName) return CollisionFrame;
		}
		return FCollisionStruct();
	}

	int32 GetIndexByCelName(const FGameplayTag& CelName) const
	{
		for (int32 i = 0; i < CollisionFrames.Num(); ++i)
		{
			if (CollisionFrames[i].CelName == CelName) return i;
		}
		return INDEX_NONE;
	}

#if WITH_EDITORONLY_DATA
	// Transient selection state for editor - not saved with asset
	UPROPERTY(Transient)
	int32 EditorSelectedIndex = INDEX_NONE;
	
	/** TODO: Filter tags that can be selected based on character name */
	// UPROPERTY()
	// FGameplayTag SelectedCharacterTag = FGameplayTag::EmptyTag;
	
	/** TODO: Stored to automatically create the preview player object when opened */
	// UPROPERTY()
	// TSubclassOf<APlayerObject> SelectedPlayerObjectClass = nullptr;

	// Delegate broadcast when CollisionFrames array is modified
	FOnCollisionFramesChanged OnCollisionFramesChanged;

	void NotifyCollisionFramesChanged()
	{
		OnCollisionFramesChanged.Broadcast();
	}

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override
	{
		Super::PostEditChangeProperty(PropertyChangedEvent);
		for (auto& Collision : CollisionFrames)
		{
			for (auto& Box : Collision.Boxes)
			{
				Box.PostEditChangeProperty();
			}
		}
	}
#endif
	
#if WITH_EDITOR
	virtual EDataValidationResult IsDataValid(FDataValidationContext& Context) const override;
#endif
};
