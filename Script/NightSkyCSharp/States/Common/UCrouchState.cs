using UnrealSharp.ControlRig;
using UnrealSharp.NightSkyEngine;

namespace NightSkyCSharp.States.Common;

public class UCrouchState : UState
{
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
            Parent.Player.JumpToStateByName("CrouchToStand");
        }
    }
}