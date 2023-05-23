#pragma once

#include "CollisionBox.generated.h"

UENUM()
enum EBoxType
{
	BOX_Push,
	BOX_Hurt,
	BOX_Hit,
};

USTRUCT()
struct FCollisionBox
{
	GENERATED_BODY()

	TEnumAsByte<EBoxType> Type;
	int32 PosX;
	int32 PosY;
	int32 SizeX;
	int32 SizeY;

	bool operator!=(const FCollisionBox& OtherBox)
	{
		return this->Type != OtherBox.Type || this->PosX != OtherBox.PosX || this->PosY != OtherBox.PosY
			|| this->SizeX != OtherBox.SizeX || this->SizeY != OtherBox.SizeY;
	}
};
