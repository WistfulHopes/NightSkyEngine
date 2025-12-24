#include "CollisionData.h"

#include "Misc/DataValidation.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CollisionData)

#define LOCTEXT_NAMESPACE "NightSkyEngine"

#if WITH_EDITOR

EDataValidationResult UCollisionData::IsDataValid(FDataValidationContext& Context) const
{
	EDataValidationResult Result = CombineDataValidationResults(Super::IsDataValid(Context), EDataValidationResult::Valid);
	if (Result == EDataValidationResult::Valid)
	{
		// Check for duplicates and empty names
		TSet<FGameplayTag> CelNames;
		for (const auto& CollisionFrame : CollisionFrames)
		{
			if (!CollisionFrame.CelName.IsValid())
			{
				Context.AddError(LOCTEXT("InvalidCelName", "Invalid Cel name found (not named)"));
				Result = EDataValidationResult::Invalid;
			}
			else
			{
				bool bIsDuplicate = false;
				CelNames.Add(CollisionFrame.CelName, &bIsDuplicate);
				if (bIsDuplicate)
				{
					Context.AddError(LOCTEXT("DuplicateCelName", "Duplicate Cel name found"));
					Result = EDataValidationResult::Invalid;
				}
			}
		}
	}
	return Result;
}

#endif // WITH_EDITOR

#undef LOCTEXT_NAMESPACE
