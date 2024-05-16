#pragma once

#include "CoreMinimal.h"
#include "Battle/CollisionBox.h"
#include "Widgets/Input/SNumericEntryBox.h"
//#include "HitboxHandler.generated.h"


class HITBOXEDITOR_API FHitboxHandler : public TSharedFromThis<FHitboxHandler>
{

public:
  FHitboxHandler() = default;

  void Init();

  void SetHitboxData(TArray<FCollisionBox> InBoxes);
  void SetCurrentHitbox(int32 Index);

  TSharedPtr<SNumericEntryBox<int32>> NumericEntryBox_XPos;
  TSharedPtr<SNumericEntryBox<int32>> NumericEntryBox_YPos;
  TSharedPtr<SNumericEntryBox<int32>> NumericEntryBox_XSize;
  TSharedPtr<SNumericEntryBox<int32>> NumericEntryBox_YSize;

  TSharedPtr<SButton> IncreaseIndexButton;
  TSharedPtr<SButton> DecreaseIndexButton;
  int32 CurrentHitboxIndex = 0;
private:
  bool IsCurrentHitboxValid() const;

  void OnNumericEntryBox_XPos_Changed(int i);
  void OnNumericEntryBox_YPos_Changed(int i);
  void OnNumericEntryBox_XSize_Changed(int i);
  void OnNumericEntryBox_YSize_Changed(int i);

  TOptional<int32> GetCurrent_XPos() const;
  TOptional<int32> GetCurrent_YPos() const;
  TOptional<int32> GetCurrent_XSize() const;
  TOptional<int32> GetCurrent_YSize() const;

  FReply IncreaseIndex();
  FReply DecreaseIndex();

  TArray<FCollisionBox> Boxes = {};

};



