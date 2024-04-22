#pragma once

#include "CollisionBox.generated.h"

/**
 * The type of collision box.
 */
UENUM(BlueprintType)
enum EBoxType
{
	/**
	 * Pushbox. Currently unimplmeneted.
	 */
	BOX_Push UMETA(DisplayName="Pushbox"),
	/**
	 * Hurtbox.
	 */
	BOX_Hurt UMETA(DisplayName="Hurtbox"),
	/**
	 * Hitbox.
	 */
	BOX_Hit UMETA(DisplayName="Hitbox"),
	/**
	 * Offset. The X and Y positions are used as a semi-root motion system.
	 */
	BOX_Offset UMETA(DisplayName="Offset"),
};

/**
 * @brief  A collision box.
 *
 * Primarily used for push and hit collision, but some box types are used for specific operations.
 */
USTRUCT()
struct FCollisionBox
{
	GENERATED_BODY()

	/**
	 * The type of box.
	 */
	UPROPERTY(EditAnywhere)
	TEnumAsByte<EBoxType> Type = BOX_Hurt;
	/**
	 * X position.
	 */
	UPROPERTY(EditAnywhere)
	int32 PosX = 0;
	/**
	 * Y position.
	 */
	UPROPERTY(EditAnywhere)
	int32 PosY = 0;
	/**
	 * X size.
	 */
	UPROPERTY(EditAnywhere)
	int32 SizeX = 0;
	/**
	 * Y size.
	 */
	UPROPERTY(EditAnywhere)
	int32 SizeY = 0;

	/**
	 * Compares against another collision box for inequality.
	 * 
	 * @param OtherBox The box to compare against.
	 * @return If any of the fields of the other box are different, return true. Otherwise return false.
	 */
	bool operator!=(const FCollisionBox& OtherBox) const
	{
		return this->Type != OtherBox.Type || this->PosX != OtherBox.PosX || this->PosY != OtherBox.PosY
			|| this->SizeX != OtherBox.SizeX || this->SizeY != OtherBox.SizeY;
	}
};
