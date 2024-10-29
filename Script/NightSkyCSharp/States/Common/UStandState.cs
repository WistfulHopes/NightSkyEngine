using UnrealSharp.Attributes;
using UnrealSharp.GameplayTags;
using UnrealSharp.NightSkyEngine;

namespace NightSkyCSharp.States.Common;

public class UStandState : UState
{
    public UStandState()
    {
        Name = new FGameplayTag("State.Universal.Stand");
    }
    
    [UFunction(FunctionFlags.BlueprintCallable)]
    public override void Init()
    {
        if (Parent.Player.IsMainPlayer())
        {
            Parent.SpeedX = 0;
            Parent.Player.EnableAll();
            Parent.Player.EnableFlip(true);
        }
        else
        {
            Parent.Player.JumpToState(new FGameplayTag("State.Universal.AssistExit"));
        }
    }
}