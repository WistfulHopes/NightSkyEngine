

# Class UExtendedCommonActivatableWidget



[**ClassList**](annotated.md) **>** [**UExtendedCommonActivatableWidget**](class_u_extended_common_activatable_widget.md)



[More...](#detailed-description)

* `#include <ExtendedCommonActivatableWidget.h>`



Inherits the following classes: UCommonActivatableWidget


































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual TOptional&lt; FUIInputConfig &gt; | [**GetDesiredInputConfig**](#function-getdesiredinputconfig) () override const<br> |
|   | [**UExtendedCommonActivatableWidget**](#function-uextendedcommonactivatablewidget) (const FObjectInitializer & ObjectInitializer=FObjectInitializer::Get()) <br> |








## Protected Attributes

| Type | Name |
| ---: | :--- |
|  ENightSkyWidgetInputMode | [**DefaultInputConfig**](#variable-defaultinputconfig)   = `ENightSkyWidgetInputMode::Default`<br> |
|  EMouseCaptureMode | [**GameMouseCaptureMode**](#variable-gamemousecapturemode)   = `EMouseCaptureMode::CapturePermanently`<br> |
















## Protected Functions

| Type | Name |
| ---: | :--- |
| virtual void | [**NativeDestruct**](#function-nativedestruct) () override<br> |
|  void | [**RegisterBinding**](#function-registerbinding) (FDataTableRowHandle InputAction, const FInputActionExecutedDelegate & Callback, [**FInputActionBindingHandle**](struct_f_input_action_binding_handle.md) & BindingHandle) <br> |
|  void | [**UnregisterAllBindings**](#function-unregisterallbindings) () <br> |
|  void | [**UnregisterBinding**](#function-unregisterbinding) ([**FInputActionBindingHandle**](struct_f_input_action_binding_handle.md) BindingHandle) <br> |




## Detailed Description


Extends UCommonActivatableWidget with Blueprint-visible functions for registering additional input action bindings. 


    
## Public Functions Documentation




### function GetDesiredInputConfig 

```C++
virtual TOptional< FUIInputConfig > UExtendedCommonActivatableWidget::GetDesiredInputConfig () override const
```




<hr>



### function UExtendedCommonActivatableWidget 

```C++
UExtendedCommonActivatableWidget::UExtendedCommonActivatableWidget (
    const FObjectInitializer & ObjectInitializer=FObjectInitializer::Get()
) 
```




<hr>
## Protected Attributes Documentation




### variable DefaultInputConfig 

```C++
ENightSkyWidgetInputMode UExtendedCommonActivatableWidget::DefaultInputConfig;
```



The desired input mode to use while this UI is activated, for example do you want key presses to still reach the game/player controller? 


        

<hr>



### variable GameMouseCaptureMode 

```C++
EMouseCaptureMode UExtendedCommonActivatableWidget::GameMouseCaptureMode;
```



The desired mouse behavior when the game gets input. 


        

<hr>
## Protected Functions Documentation




### function NativeDestruct 

```C++
virtual void UExtendedCommonActivatableWidget::NativeDestruct () override
```




<hr>



### function RegisterBinding 

```C++
void UExtendedCommonActivatableWidget::RegisterBinding (
    FDataTableRowHandle InputAction,
    const FInputActionExecutedDelegate & Callback,
    FInputActionBindingHandle & BindingHandle
) 
```




<hr>



### function UnregisterAllBindings 

```C++
void UExtendedCommonActivatableWidget::UnregisterAllBindings () 
```




<hr>



### function UnregisterBinding 

```C++
void UExtendedCommonActivatableWidget::UnregisterBinding (
    FInputActionBindingHandle BindingHandle
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/NightSkyEngine/UI/ExtendedCommonActivatableWidget.h`

