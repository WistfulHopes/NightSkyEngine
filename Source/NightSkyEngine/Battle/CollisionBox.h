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

	UPROPERTY(EditAnywhere)
	TEnumAsByte<EBoxType> Type;
	UPROPERTY(EditAnywhere)
	int32 PosX;
	UPROPERTY(EditAnywhere)
	int32 PosY;
	UPROPERTY(EditAnywhere)
	int32 SizeX;
	UPROPERTY(EditAnywhere)
	int32 SizeY;

	bool operator!=(const FCollisionBox& OtherBox) const
	{
		return this->Type != OtherBox.Type || this->PosX != OtherBox.PosX || this->PosY != OtherBox.PosY
			|| this->SizeX != OtherBox.SizeX || this->SizeY != OtherBox.SizeY;
	}
};
