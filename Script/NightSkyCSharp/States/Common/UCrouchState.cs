using UnrealSharp.ControlRig;
using UnrealSharp.GameplayTags;
using UnrealSharp.NightSkyEngine;

namespace NightSkyCSharp.States.Common;

public class UCrouchState : UState
{
    public UCrouchState()
    {
        Name = new FGameplayTag("State.Universal.Crouch");
    }
    
    public override void Exec()
    {
        base.Exec();
        FInputCondition downCond = new FInputCondition();
        {
            FInputBitmask down = new FInputBitmask();
            down.InputFlag = (int)EInputFlags.INP_Down;
            down.Lenience = 0;
            downCond.Sequence.Add(down);
        }
        var isHoldingDown = Parent.Player.CheckInput(downCond);

        if (!isHoldingDown)
        {
            Parent.Player.JumpToState(new FGameplayTag("State.Universal.CrouchToStand"));
        }
    }
}