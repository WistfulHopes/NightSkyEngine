

# File ExtendedCommonActivatableWidget.h



[**FileList**](files.md) **>** [**NightSkyEngine**](dir_01309b4faf1ec48651014f612e2b32bb.md) **>** [**Source**](dir_d32ee28216ed342fa25c01ae9dcd9cc4.md) **>** [**NightSkyEngine**](dir_a12a4fa09c295aab9e164f44221961f1.md) **>** [**UI**](dir_a40c408bd590fbad9d640bb5832ac49f.md) **>** [**ExtendedCommonActivatableWidget.h**](_extended_common_activatable_widget_8h.md)

[Go to the source code of this file](_extended_common_activatable_widget_8h_source.md)



* `#include "CoreMinimal.h"`
* `#include "CommonActivatableWidget.h"`
* `#include "ExtendedCommonActivatableWidget.generated.h"`















## Classes

| Type | Name |
| ---: | :--- |
| struct | [**FInputActionBindingHandle**](struct_f_input_action_binding_handle.md) <br> |
| class | [**UExtendedCommonActivatableWidget**](class_u_extended_common_activatable_widget.md) <br> |


## Public Types

| Type | Name |
| ---: | :--- |
| enum uint8 | [**ENightSkyWidgetInputMode**](#enum-enightskywidgetinputmode)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**DECLARE\_DYNAMIC\_DELEGATE\_OneParam**](#function-declare_dynamic_delegate_oneparam) (FInputActionExecutedDelegate, FName, ActionName) <br> |




























## Public Types Documentation




### enum ENightSkyWidgetInputMode 

```C++
enum ENightSkyWidgetInputMode {
    Default,
    GameAndMenu,
    Game,
    Menu
};
```




<hr>
## Public Functions Documentation




### function DECLARE\_DYNAMIC\_DELEGATE\_OneParam 

```C++
DECLARE_DYNAMIC_DELEGATE_OneParam (
    FInputActionExecutedDelegate,
    FName,
    ActionName
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/NightSkyEngine/UI/ExtendedCommonActivatableWidget.h`

