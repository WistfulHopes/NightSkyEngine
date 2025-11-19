// Fill out your copyright notice in the Description page of Project Settings.


#include "NightSkyAnimSequenceUserData.h"

#include "NightSkyAnimMetaData.h"
#include "NightSkyEngine/Battle/Misc/Globals.h"

void UNightSkyAnimSequenceUserData::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);

	Ar << MeshSpaceBoneTransforms;
	Ar << RootTranslation;
}

void UNightSkyAnimSequenceUserData::PostEditChangeOwner(const FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeOwner(PropertyChangedEvent);
	
	// We can't call blueprint implemented functions while routing post load
	if (FUObjectThreadContext::Get().IsRoutingPostLoad)
	{
		return;
	}

	// Skip interactive changes
	if (PropertyChangedEvent.ChangeType == EPropertyChangeType::Interactive)
	{
		return;
	}

	MeshSpaceBoneTransforms.Empty();
	RootTranslation.Empty();

	auto AnimSequence = Cast<UAnimSequence>(GetOuter());
	if (!IsValid(AnimSequence)) return;
	
	UNightSkyAnimMetaData* AnimMetaData = nullptr;

	for (auto& MetaData : AnimSequence->GetMetaData())
	{
		AnimMetaData = Cast<UNightSkyAnimMetaData>(MetaData);
		if (IsValid(MetaData)) break;
	}

	if (!IsValid(AnimMetaData))
	{
		ConditionalBeginDestroy();
		return;
	}

	FrameCount = AnimSequence->GetPlayLength() * AnimSequence->GetSamplingFrameRate().AsDecimal();
	FrameRate = AnimSequence->GetSamplingFrameRate().AsDecimal();

	auto ReferenceSkeleton = AnimSequence->GetSkeleton()->GetReferenceSkeleton();

	for (auto& BoneName : AnimMetaData->CachedBoneNames)
	{
		if (ReferenceSkeleton.FindBoneIndex(BoneName) == INDEX_NONE) continue;
		TMap<int32, FAnimTransform> BoneTransforms;

		for (int i = 0; i < FrameCount; i++)
		{
			FTransform Transform;
			FAnimExtractContext Context{
				static_cast<double>(i) / AnimSequence->GetSamplingFrameRate().AsDecimal()
			};
			AnimSequence->GetBoneTransform(
				Transform, FSkeletonPoseBoneIndex(ReferenceSkeleton.FindBoneIndex(BoneName)),
				Context, true);

			FAnimTransform AnimTransform;
			AnimTransform.Position.X = Transform.GetTranslation().X * COORD_SCALE;
			AnimTransform.Position.Y = Transform.GetTranslation().Y * COORD_SCALE;
			AnimTransform.Position.Z = Transform.GetTranslation().Z * COORD_SCALE;

			auto Rotation = Transform.GetRotation().Rotator();
			AnimTransform.Rotation.Pitch = Rotation.Pitch * 1000;
			AnimTransform.Rotation.Yaw = Rotation.Yaw * 1000;
			AnimTransform.Rotation.Roll = Rotation.Roll * 1000;

			AnimTransform.Scale.X = Transform.GetScale3D().X * 1000;
			AnimTransform.Scale.Y = Transform.GetScale3D().Y * 1000;
			AnimTransform.Scale.Z = Transform.GetScale3D().Z * 1000;

			BoneTransforms.Add(i, AnimTransform);
		}

		MeshSpaceBoneTransforms.Add(BoneName, BoneTransforms);
	}

	for (int i = 0; i < FrameCount; i++)
	{
		FAnimExtractContext Context{
			static_cast<double>(i) / AnimSequence->GetSamplingFrameRate().AsDecimal(),
			true,
		};

		FVector Translation = AnimSequence->ExtractRootTrackTransform(Context, nullptr).GetTranslation();
		FAnimVector AnimTranslation;

		AnimTranslation.X = Translation.X * COORD_SCALE;
		AnimTranslation.Y = Translation.Y * COORD_SCALE;
		AnimTranslation.Z = Translation.Z * COORD_SCALE;

		RootTranslation.Add(i, AnimTranslation);
	}
}

FAnimVector UNightSkyAnimSequenceUserData::GetRootTranslationAtTime(int32 Time) const
{
	if (!RootTranslation.Contains(Time)) return FAnimVector{};
	return RootTranslation[Time];
}

FAnimTransform UNightSkyAnimSequenceUserData::GetCachedBoneTransformAtTime(FName BoneName, int32 Time,
                                                                           bool bRelativeToRoot) const
{
	if (!MeshSpaceBoneTransforms.Contains(BoneName)) return FAnimTransform{};
	if (!MeshSpaceBoneTransforms[BoneName].Contains(Time)) return FAnimTransform{};
	auto Transform = MeshSpaceBoneTransforms[BoneName][Time];

	if (!bRelativeToRoot) return Transform;
	if (!RootTranslation.Contains(Time)) return Transform;

	auto Root = RootTranslation[Time];
	Transform.Position.X += Root.X;
	Transform.Position.Y += Root.Y;
	Transform.Position.Z += Root.Z;
	return Transform;
}

FAnimVector UNightSkyAnimSequenceUserData::GetCachedBoneLocationAtTime(FName BoneName, int32 Time,
	bool bRelativeToRoot) const
{
	if (!MeshSpaceBoneTransforms.Contains(BoneName)) return FAnimVector{};
	if (!MeshSpaceBoneTransforms[BoneName].Contains(Time)) return FAnimVector{};
	auto Transform = MeshSpaceBoneTransforms[BoneName][Time];

	if (!bRelativeToRoot) return Transform.Position;
	if (!RootTranslation.Contains(Time)) return Transform.Position;

	auto Root = RootTranslation[Time];
	Transform.Position.X += Root.X;
	Transform.Position.Y += Root.Y;
	Transform.Position.Z += Root.Z;
	return Transform.Position;
}
