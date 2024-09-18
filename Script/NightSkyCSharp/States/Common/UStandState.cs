using UnrealSharp.Attributes;
using UnrealSharp.NightSkyEngine;

namespace NightSkyCSharp.States.Common;

public class UStandState : UState
{
    [UFunction(FunctionFlags.BlueprintCallable)]
    public void Init()
    {
        if (Parent.Player.IsMainPlayer())
        {
            Parent.SpeedX = 0;
            Parent.Player.EnableAll();
            Parent.Player.EnableFlip(true);
        }
        else
        {
            Parent.Player.JumpToStateByName("AssistExit");
        }
    }
}