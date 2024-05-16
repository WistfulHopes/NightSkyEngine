#include "HitboxHandler.h"


void FHitboxHandler::Init()
{
  NumericEntryBox_XPos = SNew(SNumericEntryBox<int32>)
    .AllowSpin(true)
    .AllowWheel(true)
    .Value(this, &FHitboxHandler::GetCurrent_XPos)
  .MinSliderValue(-1000000)
  .MaxSliderValue(1000000)
    .OnValueChanged(this, &FHitboxHandler::OnNumericEntryBox_XPos_Changed);

  NumericEntryBox_YPos = SNew(SNumericEntryBox<int32>)
  .AllowSpin(true)
  .AllowWheel(true)
  .MinSliderValue(-1000000)
  .MaxSliderValue(1000000)
  .Value(this, &FHitboxHandler::GetCurrent_YPos)

  .OnValueChanged(this, &FHitboxHandler::OnNumericEntryBox_YPos_Changed);

  NumericEntryBox_XSize = SNew(SNumericEntryBox<int32>)
  .AllowSpin(true)
  .AllowWheel(true)
  .MinSliderValue(-1000000)
  .MaxSliderValue(1000000)
  .Value(this, &FHitboxHandler::GetCurrent_XSize)
  .OnValueChanged(this, &FHitboxHandler::OnNumericEntryBox_XSize_Changed);

  NumericEntryBox_YSize = SNew(SNumericEntryBox<int32>)
  .AllowSpin(true)
  .AllowWheel(true)
  .MinSliderValue(-1000000)
  .MaxSliderValue(1000000)
  .Value(this, &FHitboxHandler::GetCurrent_YSize)
  .OnValueChanged(this, &FHitboxHandler::OnNumericEntryBox_YSize_Changed);


  IncreaseIndexButton = SNew(SButton)
  .OnClicked(this, &FHitboxHandler::IncreaseIndex)
  .Text(FText::FromString("+"))
  .ToolTipText(FText::FromString("Increase Hitbox Index"));

  DecreaseIndexButton = SNew(SButton)
  .OnClicked(this, &FHitboxHandler::DecreaseIndex)
  .Text(FText::FromString("-"))
  .ToolTipText(FText::FromString("Decrease Hitbox Index"));

}

void FHitboxHandler::SetHitboxData(TArray<FCollisionBox> InBoxes)
{
  Boxes = InBoxes;
  CurrentHitboxIndex = 0;
}

void FHitboxHandler::SetCurrentHitbox(int32 Index)
{
  const int32 OldIndex = CurrentHitboxIndex;

  CurrentHitboxIndex = Index;
  if(!IsCurrentHitboxValid())
  {
    CurrentHitboxIndex = OldIndex;
    return;
  }
}

bool FHitboxHandler::IsCurrentHitboxValid() const
{

  if(Boxes.IsEmpty()) return false;
  return CurrentHitboxIndex >= 0 && CurrentHitboxIndex < Boxes.Num();

}

void FHitboxHandler::OnNumericEntryBox_XPos_Changed(int i)
{
  if (!IsCurrentHitboxValid()) return;
  FCollisionBox& Box = Boxes[CurrentHitboxIndex];
  Box.PosX = i;
}

void FHitboxHandler::OnNumericEntryBox_YPos_Changed(int i)
{
  if (!IsCurrentHitboxValid()) return;
  FCollisionBox& Box = Boxes[CurrentHitboxIndex];
  Box.PosY = i;
}

void FHitboxHandler::OnNumericEntryBox_XSize_Changed(int i)
{
  if(!IsCurrentHitboxValid()) return;
  FCollisionBox& Box = Boxes[CurrentHitboxIndex];
  Box.SizeX = i;
}

void FHitboxHandler::OnNumericEntryBox_YSize_Changed(int i)
{
  if(!IsCurrentHitboxValid()) return;
  FCollisionBox& Box = Boxes[CurrentHitboxIndex];
  Box.SizeY = i;
}

TOptional<int32> FHitboxHandler::GetCurrent_XPos() const
{
  if(!IsCurrentHitboxValid()) return TOptional<int32>();
  const FCollisionBox& Box = Boxes[CurrentHitboxIndex];
  return Box.PosX;
}

TOptional<int32> FHitboxHandler::GetCurrent_YPos() const
{
  if(!IsCurrentHitboxValid()) return TOptional<int32>();
  const FCollisionBox& Box = Boxes[CurrentHitboxIndex];
  return Box.PosY;
}

TOptional<int32> FHitboxHandler::GetCurrent_XSize() const
{
  if(!IsCurrentHitboxValid()) return TOptional<int32>();
  const FCollisionBox& Box = Boxes[CurrentHitboxIndex];
  return Box.SizeX;
}

TOptional<int32> FHitboxHandler::GetCurrent_YSize() const
{
  if(!IsCurrentHitboxValid()) return TOptional<int32>();
  const FCollisionBox& Box = Boxes[CurrentHitboxIndex];
  return Box.SizeY;
}

FReply FHitboxHandler::IncreaseIndex()
{
  SetCurrentHitbox(CurrentHitboxIndex + 1);
  return FReply::Handled();
}

FReply FHitboxHandler::DecreaseIndex()
{
  SetCurrentHitbox(CurrentHitboxIndex - 1);
  return FReply::Handled();
}
