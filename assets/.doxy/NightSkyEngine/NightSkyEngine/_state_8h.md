

# File State.h



[**FileList**](files.md) **>** [**Battle**](dir_59b3558fc0091a3111c9e7dd8d94b2ea.md) **>** [**Script**](dir_0ca77fec7001245ae32841da8dbaa106.md) **>** [**State.h**](_state_8h.md)

[Go to the source code of this file](_state_8h_source.md)



* `#include "CoreMinimal.h"`
* `#include "NightSkyEngine/Battle/Misc/Bitflags.h"`
* `#include "GameplayTagContainer.h"`
* `#include "NightSkyEngine/Battle/Misc/SerializableObj.h"`
* `#include "NightSkyEngine/Battle/Objects/BattleObject.h"`
* `#include "State.generated.h"`















## Classes

| Type | Name |
| ---: | :--- |
| struct | [**FInputBitmask**](struct_f_input_bitmask.md) <br> |
| struct | [**FInputCondition**](struct_f_input_condition.md) <br> |
| struct | [**FInputConditionList**](struct_f_input_condition_list.md) <br> |
| struct | [**FStateCPUData**](struct_f_state_c_p_u_data.md) <br> |
| class | [**UState**](class_u_state.md) <br>_A character state that determines behavior._  |


## Public Types

| Type | Name |
| ---: | :--- |
| enum  | [**EAttackSpeed**](#enum-eattackspeed)  <br> |
| enum uint8 | [**EEntryStance**](#enum-eentrystance)  <br> |
| enum uint8 | [**EInputMethod**](#enum-einputmethod)  <br> |
| enum  | [**ERangeType**](#enum-erangetype)  <br> |
| enum uint8 | [**EStateCondition**](#enum-estatecondition)  <br> |
| enum uint8 | [**EStateType**](#enum-estatetype)  <br> |
















































## Public Types Documentation




### enum EAttackSpeed 

```C++
enum EAttackSpeed {
    ASPD_Fast,
    ASPD_Medium,
    ASPD_Slow
};
```



Attack speed used for CPU behavior. 


        

<hr>



### enum EEntryStance 

```C++
enum EEntryStance {
    None,
    Standing,
    Crouching,
    Jumping
};
```



What stance the character must be in to enter this state. Upon entering the state, the character will take this stance. 


        

<hr>



### enum EInputMethod 

```C++
enum EInputMethod {
    Normal,
    Strict,
    Once,
    OnceStrict,
    PressAndRelease,
    PressAndReleaseStrict,
    Negative,
    NegativeStrict
};
```



Determines the method of which the input will be read. 


        

<hr>



### enum ERangeType 

```C++
enum ERangeType {
    RAN_Near,
    RAN_Mid,
    RAN_Far
};
```



A range used for CPU behavior. 


        

<hr>



### enum EStateCondition 

```C++
enum EStateCondition {
    None,
    AirJumpOk,
    AirJumpMinimumHeight,
    AirDashOk,
    AirDashMinimumHeight,
    IsAttacking,
    HitstopCancel,
    IsStunned,
    CloseNormal,
    FarNormal,
    CanTag2nd,
    CanTag3rd,
    MeterNotZero,
    MeterQuarterBar,
    MeterHalfBar,
    MeterOneBar,
    MeterTwoBars,
    MeterThreeBars,
    MeterFourBars,
    MeterFiveBars,
    PlayerReg1True,
    PlayerReg2True,
    PlayerReg3True,
    PlayerReg4True,
    PlayerReg5True,
    PlayerReg6True,
    PlayerReg7True,
    PlayerReg8True,
    PlayerReg1False,
    PlayerReg2False,
    PlayerReg3False,
    PlayerReg4False,
    PlayerReg5False,
    PlayerReg6False,
    PlayerReg7False,
    PlayerReg8False
};
```



A condition to enter the state.




**See also:** APlayerObject::HandleStateCondition 



        

<hr>



### enum EStateType 

```C++
enum EStateType {
    Standing,
    Crouching,
    NeutralJump,
    ForwardJump,
    BackwardJump,
    ForwardWalk,
    BackwardWalk,
    ForwardDash,
    BackwardDash,
    ForwardAirDash,
    BackwardAirDash,
    NormalAttack,
    SpecialAttack,
    SuperAttack,
    Hitstun,
    Blockstun,
    Tech,
    Burst,
    Tag,
    Assist,
    Custom
};
```



The type of state. State types can have the ability to enter them toggled on and off. 


        

<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/NightSkyEngine/Battle/Script/State.h`

