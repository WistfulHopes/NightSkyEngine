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