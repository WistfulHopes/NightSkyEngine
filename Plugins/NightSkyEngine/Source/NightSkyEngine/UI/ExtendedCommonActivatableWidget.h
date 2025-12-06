// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "ExtendedCommonActivatableWidget.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FInputActionExecutedDelegate, FName, ActionName);

UENUM(BlueprintType)
enum class ENightSkyWidgetInputMode : uint8
{
	Default,
	GameAndMenu,
	Game,
	Menu
};

USTRUCT(BlueprintType)
struct FInputActionBindingHandle
{
	GENERATED_BODY()
	
public:
	FUIActionBindingHandle Handle;
};

/**
 * Extends UCommonActivatableWidget with Blueprint-visible functions for registering additional input action bindings.
 */
UCLASS(Abstract, Blueprintable, meta = (DisableNativeTick))
class UExtendedCommonActivatableWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:
	UExtendedCommonActivatableWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	//~UCommonActivatableWidget interface
	virtual TOptional<FUIInputConfig> GetDesiredInputConfig() const override;
	//~End of UCommonActivatableWidget interface
	
#if WITH_EDITOR
	virtual void ValidateCompiledWidgetTree(const UWidgetTree& BlueprintWidgetTree, IWidgetCompilerLog& CompileLog) const override;
#endif

protected:
	virtual void NativeDestruct() override;

	UFUNCTION(BlueprintCallable, Category = ExtendedActivatableWidget)
	void RegisterBinding(FDataTableRowHandle InputAction, const FInputActionExecutedDelegate& Callback, FInputActionBindingHandle& BindingHandle);

	UFUNCTION(BlueprintCallable, Category = ExtendedActivatableWidget)
	void UnregisterBinding(FInputActionBindingHandle BindingHandle);

	UFUNCTION(BlueprintCallable, Category = ExtendedActivatableWidget)
	void UnregisterAllBindings();
	
	/** The desired input mode to use while this UI is activated, for example do you want key presses to still reach the game/player controller? */
	UPROPERTY(EditDefaultsOnly, Category = Input)
	ENightSkyWidgetInputMode DefaultInputConfig = ENightSkyWidgetInputMode::Default;
	
	/** The desired mouse behavior when the game gets input. */
	UPROPERTY(EditDefaultsOnly, Category = Input)
	EMouseCaptureMode GameMouseCaptureMode = EMouseCaptureMode::CapturePermanently;

private:
	TArray<FUIActionBindingHandle> BindingHandles;
};
