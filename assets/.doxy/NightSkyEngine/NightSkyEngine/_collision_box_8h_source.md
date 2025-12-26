

# File CollisionBox.h

[**File List**](files.md) **>** [**Battle**](dir_59b3558fc0091a3111c9e7dd8d94b2ea.md) **>** [**Misc**](dir_4fd921e402b7a240656c31e280e3875c.md) **>** [**CollisionBox.h**](_collision_box_8h.md)

[Go to the documentation of this file](_collision_box_8h.md)


```C++
#pragma once
#include "Globals.h"

#include "CollisionBox.generated.h"

UENUM(BlueprintType)
enum EBoxType
{
    BOX_Push UMETA(DisplayName="Pushbox"),
    BOX_Hurt UMETA(DisplayName="Hurtbox"),
    BOX_Hit UMETA(DisplayName="Hitbox"),
    BOX_Offset UMETA(DisplayName="Offset"),
    BOX_Custom UMETA(DisplayName="Custom"),
};

USTRUCT(BlueprintType)
struct FCollisionBox
{
    GENERATED_BODY()

    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, SaveGame)
    TEnumAsByte<EBoxType> Type = BOX_Hurt;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, SaveGame)
    FGameplayTag CustomType;
    UPROPERTY(BlueprintReadOnly, SaveGame)
    int32 PosX = 0;
    UPROPERTY(BlueprintReadOnly, SaveGame)
    int32 PosY = 0;
    UPROPERTY(BlueprintReadOnly, SaveGame)
    int32 SizeX = 0;
    UPROPERTY(BlueprintReadOnly, SaveGame)
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
    
    bool operator!=(const FCollisionBox& OtherBox) const
    {
        return this->Type != OtherBox.Type || this->CustomType != OtherBox.CustomType || this->PosX != OtherBox.PosX
            || this->PosY != OtherBox.PosY || this->SizeX != OtherBox.SizeX || this->SizeY != OtherBox.SizeY;
    }
};
```


