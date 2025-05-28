#pragma once
#include "Globals.h"

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
	UPROPERTY()
	int32 PosX = 0;
	/**
	 * Y position.
	 */
	UPROPERTY()
	int32 PosY = 0;
	/**
	 * X size.
	 */
	UPROPERTY()
	int32 SizeX = 0;
	/**
	 * Y size.
	 */
	UPROPERTY()
	int32 SizeY = 0;

#if WITH_EDITORONLY_DATA
	// Values for editor only, used for easy editing/display
	
	UPROPERTY(EditAnywhere, meta=(DisplayName="X Position"))
	float PosXEdit = 0;
	UPROPERTY(EditAnywhere, meta=(DisplayName="Y Position"))
	float PosYEdit = 0;
	UPROPERTY(EditAnywhere, meta=(DisplayName="X Size"))
	float SizeXEdit = 0;
	UPROPERTY(EditAnywhere, meta=(DisplayName="Y Size"))
	float SizeYEdit = 0;
	UPROPERTY(EditAnywhere, meta=(DisplayName="X Position (Unreal)", Units = "cm"))
	float UEPosX = 0;
	UPROPERTY(EditAnywhere, meta=(DisplayName="Y Position (Unreal)", Units = "cm"))
	float UEPosY = 0;
	UPROPERTY(EditAnywhere, meta=(DisplayName="X Size (Unreal)", Units = "cm"))
	float UESizeX = 0;
	UPROPERTY(EditAnywhere, meta=(DisplayName="Y Size (Unreal)", Units = "cm"))
	float UESizeY = 0;

	void EditorInit()
	{
		PosXEdit = static_cast<float>(PosX) / 1000;
		PosYEdit = static_cast<float>(PosY) / 1000;
		SizeXEdit = static_cast<float>(SizeX) / 1000;
		SizeYEdit = static_cast<float>(SizeY) / 1000;
		UEPosX = static_cast<float>(PosX) / COORD_SCALE;
		UEPosY = static_cast<float>(PosY) / COORD_SCALE;
		UESizeX = static_cast<float>(SizeX) / COORD_SCALE;
		UESizeY = static_cast<float>(SizeY) / COORD_SCALE;
	}
	
	void PostEditChangeProperty()
	{
		if (static_cast<float>(PosX) / 1000 != PosXEdit)
		{
			PosX = PosXEdit * 1000;
			UEPosX = static_cast<float>(PosX) / COORD_SCALE;
		}
		if (static_cast<float>(PosY) / 1000 != PosYEdit)
		{
			PosY = PosYEdit * 1000;
			UEPosY = static_cast<float>(PosY) / COORD_SCALE;
		}
		if (static_cast<float>(SizeX) / 1000 != SizeXEdit)
		{
			SizeX = SizeXEdit * 1000;
			UESizeX = static_cast<float>(SizeX) / COORD_SCALE;
		}
		if (static_cast<float>(SizeY) / 1000 != SizeYEdit)
		{
			SizeY = SizeYEdit * 1000;
			UESizeY = static_cast<float>(SizeY) / COORD_SCALE;
		}
		if (static_cast<float>(PosX) / COORD_SCALE != UEPosX)
		{
			PosX = UEPosX * COORD_SCALE;
			PosXEdit = static_cast<float>(PosX) / 1000;
		}
		if (static_cast<float>(PosY) / COORD_SCALE != UEPosY)
		{
			PosY = UEPosY * COORD_SCALE;
			PosYEdit = static_cast<float>(PosY) / 1000;
		}
		if (static_cast<float>(SizeX) / COORD_SCALE != UESizeX)
		{
			SizeX = UESizeX * COORD_SCALE;
			SizeXEdit = static_cast<float>(SizeX) / 1000;
		}
		if (static_cast<float>(SizeY) / COORD_SCALE != UESizeY)
		{
			SizeY = UESizeY * COORD_SCALE;
			SizeYEdit = static_cast<float>(SizeY) / 1000;
		}
	}
#endif
	
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
