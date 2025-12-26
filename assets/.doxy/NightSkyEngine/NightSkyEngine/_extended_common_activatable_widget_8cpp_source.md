

# File ExtendedCommonActivatableWidget.cpp

[**File List**](files.md) **>** [**NightSkyEngine**](dir_01309b4faf1ec48651014f612e2b32bb.md) **>** [**Source**](dir_d32ee28216ed342fa25c01ae9dcd9cc4.md) **>** [**NightSkyEngine**](dir_a12a4fa09c295aab9e164f44221961f1.md) **>** [**UI**](dir_a40c408bd590fbad9d640bb5832ac49f.md) **>** [**ExtendedCommonActivatableWidget.cpp**](_extended_common_activatable_widget_8cpp.md)

[Go to the documentation of this file](_extended_common_activatable_widget_8cpp.md)


```C++
#include "ExtendedCommonActivatableWidget.h"

#include "Editor/WidgetCompilerLog.h"
#include "Input/CommonUIInputTypes.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ExtendedCommonActivatableWidget)

#define LOCTEXT_NAMESPACE "NightSkyEngine"

UExtendedCommonActivatableWidget::UExtendedCommonActivatableWidget(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

TOptional<FUIInputConfig> UExtendedCommonActivatableWidget::GetDesiredInputConfig() const
{
    const auto Result = Super::GetDesiredInputConfig();
    
    if (Result.IsSet())
    {
        return Result;
    }
    
    switch (DefaultInputConfig)
    {
    case ENightSkyWidgetInputMode::GameAndMenu:
        return FUIInputConfig(ECommonInputMode::All, GameMouseCaptureMode);
    case ENightSkyWidgetInputMode::Game:
        return FUIInputConfig(ECommonInputMode::Game, GameMouseCaptureMode);
    case ENightSkyWidgetInputMode::Menu:
        return FUIInputConfig(ECommonInputMode::Menu, EMouseCaptureMode::NoCapture);
    case ENightSkyWidgetInputMode::Default:
    default:
        return TOptional<FUIInputConfig>();
    }
}

void UExtendedCommonActivatableWidget::NativeDestruct()
{
    for (FUIActionBindingHandle Handle : BindingHandles)
    {
        if (Handle.IsValid())
        {
            Handle.Unregister();
        }
    }
    BindingHandles.Empty();

    Super::NativeDestruct();
}

void UExtendedCommonActivatableWidget::RegisterBinding(FDataTableRowHandle InputAction, const FInputActionExecutedDelegate& Callback, FInputActionBindingHandle& BindingHandle)
{
    FBindUIActionArgs BindArgs(InputAction, FSimpleDelegate::CreateLambda([InputAction, Callback]()
    {
        Callback.ExecuteIfBound(InputAction.RowName);
    }));
    BindArgs.bDisplayInActionBar = true;
    
    BindingHandle.Handle = RegisterUIActionBinding(BindArgs);
    BindingHandles.Add(BindingHandle.Handle);
}

void UExtendedCommonActivatableWidget::UnregisterBinding(FInputActionBindingHandle BindingHandle)
{
    if (BindingHandle.Handle.IsValid())
    {
        BindingHandle.Handle.Unregister();
        BindingHandles.Remove(BindingHandle.Handle);
    }
}

void UExtendedCommonActivatableWidget::UnregisterAllBindings()
{
    for (FUIActionBindingHandle Handle : BindingHandles)
    {
        Handle.Unregister();
    }
    BindingHandles.Empty();
}

#if WITH_EDITOR

void UExtendedCommonActivatableWidget::ValidateCompiledWidgetTree(const UWidgetTree& BlueprintWidgetTree, IWidgetCompilerLog& CompileLog) const
{
    Super::ValidateCompiledWidgetTree(BlueprintWidgetTree, CompileLog);

    if (!GetClass()->IsFunctionImplementedInScript(GET_FUNCTION_NAME_CHECKED(UExtendedCommonActivatableWidget, BP_GetDesiredFocusTarget)))
    {
        if (GetParentNativeClass(GetClass()) == UExtendedCommonActivatableWidget::StaticClass())
        {
            CompileLog.Warning(LOCTEXT("ValidateGetDesiredFocusTarget_Warning", "GetDesiredFocusTarget wasn't implemented, you're going to have trouble using gamepads on this screen."));
        }
        else
        {
            // We can't guarantee it isn't implemented in a native subclass of this one.
            // Native subclasses should override ValidateCompiledWidgetTree, skipping this and invoking the base UUserWidget version
            CompileLog.Note(LOCTEXT("ValidateGetDesiredFocusTarget_Note", "GetDesiredFocusTarget wasn't implemented in Blueprint, you will have issues with gamepads if a native subclass did not implement it."));
        }
    }
}

#endif

#undef LOCTEXT_NAMESPACE
```


