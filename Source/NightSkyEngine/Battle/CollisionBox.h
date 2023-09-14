#pragma once

#include "CollisionBox.generated.h"

UENUM()
enum EBoxType
{
	BOX_Push,
	BOX_Hurt,
	BOX_Hit,
	BOX_Offset,
};

USTRUCT()
struct FCollisionBox
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TEnumAsByte<EBoxType> Type = BOX_Hurt;
	UPROPERTY(EditAnywhere)
	int32 PosX = 0;
	UPROPERTY(EditAnywhere)
	int32 PosY = 0;
	UPROPERTY(EditAnywhere)
	int32 SizeX = 0;
	UPROPERTY(EditAnywhere)
	int32 SizeY = 0;

	bool operator!=(const FCollisionBox& OtherBox) const
	{
		return this->Type != OtherBox.Type || this->PosX != OtherBox.PosX || this->PosY != OtherBox.PosY
			|| this->SizeX != OtherBox.SizeX || this->SizeY != OtherBox.SizeY;
	}
};
