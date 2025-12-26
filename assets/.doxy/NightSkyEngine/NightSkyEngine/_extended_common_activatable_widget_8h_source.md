

# File ExtendedCommonActivatableWidget.h

[**File List**](files.md) **>** [**NightSkyEngine**](dir_01309b4faf1ec48651014f612e2b32bb.md) **>** [**Source**](dir_d32ee28216ed342fa25c01ae9dcd9cc4.md) **>** [**NightSkyEngine**](dir_a12a4fa09c295aab9e164f44221961f1.md) **>** [**UI**](dir_a40c408bd590fbad9d640bb5832ac49f.md) **>** [**ExtendedCommonActivatableWidget.h**](_extended_common_activatable_widget_8h.md)

[Go to the documentation of this file](_extended_common_activatable_widget_8h.md)


```C++
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
    
    UPROPERTY(EditDefaultsOnly, Category = Input)
    ENightSkyWidgetInputMode DefaultInputConfig = ENightSkyWidgetInputMode::Default;
    
    UPROPERTY(EditDefaultsOnly, Category = Input)
    EMouseCaptureMode GameMouseCaptureMode = EMouseCaptureMode::CapturePermanently;

private:
    TArray<FUIActionBindingHandle> BindingHandles;
};
```


