// Fill out your copyright notice in the Description page of Project Settings.


#include "NightSkyPlayerController.h"
#include "NightSkyEngine/Battle/Bitflags.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values
ANightSkyPlayerController::ANightSkyPlayerController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ANightSkyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANightSkyPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ANightSkyPlayerController::SetupInputComponent()
{
	if (GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (!InputMapping.IsNull())
			{
				InputSystem->AddMappingContext(InputMapping.LoadSynchronous(), 0);
			}
		}
	}
	
	if (InputComponent == NULL)
	{
		InputComponent = NewObject<UEnhancedInputComponent>(this, UInputSettings::GetDefaultInputComponentClass(), TEXT("PC_InputComponent0"));
		InputComponent->RegisterComponent();
	}

	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(InputComponent);

	
	for (auto Mapping : InputMapping.Get()->GetMappings())
	{
		FString ActionName = Mapping.Action.Get()->ActionDescription.ToString();
		if (ActionName == "Press Up")
		{
			Input->BindAction(Mapping.Action.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::PressUp);
		}
		else if (ActionName == "Release Up")
		{
			Input->BindAction(Mapping.Action.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::ReleaseUp);
		}
		else if (ActionName == "Press Down")
		{
			Input->BindAction(Mapping.Action.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::PressDown);
		}
		else if (ActionName == "Release Down")
		{
			Input->BindAction(Mapping.Action.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::ReleaseDown);
		}
		else if (ActionName == "Press Left")
		{
			Input->BindAction(Mapping.Action.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::PressLeft);
		}
		else if (ActionName == "Release Left")
		{
			Input->BindAction(Mapping.Action.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::ReleaseLeft);
		}
		else if (ActionName == "Press Right")
		{
			Input->BindAction(Mapping.Action.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::PressRight);
		}
		else if (ActionName == "Release Right")
		{
			Input->BindAction(Mapping.Action.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::ReleaseRight);
		}
		else if (ActionName == "Press A")
		{
			Input->BindAction(Mapping.Action.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::PressA);
		}
		else if (ActionName == "Release A")
		{
			Input->BindAction(Mapping.Action.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::ReleaseA);
		}
		else if (ActionName == "Press B")
		{
			Input->BindAction(Mapping.Action.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::PressB);
		}
		else if (ActionName == "Release B")
		{
			Input->BindAction(Mapping.Action.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::ReleaseB);
		}
		else if (ActionName == "Press C")
		{
			Input->BindAction(Mapping.Action.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::PressC);
		}
		else if (ActionName == "Release C")
		{
			Input->BindAction(Mapping.Action.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::ReleaseC);
		}
		else if (ActionName == "Press D")
		{
			Input->BindAction(Mapping.Action.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::PressD);
		}
		else if (ActionName == "Release D")
		{
			Input->BindAction(Mapping.Action.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::ReleaseD);
		}
		else if (ActionName == "Press E")
		{
			Input->BindAction(Mapping.Action.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::PressE);
		}
		else if (ActionName == "Release E")
		{
			Input->BindAction(Mapping.Action.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::ReleaseE);
		}
		else if (ActionName == "Press F")
		{
			Input->BindAction(Mapping.Action.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::PressF);
		}
		else if (ActionName == "Release F")
		{
			Input->BindAction(Mapping.Action.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::ReleaseF);
		}
		else if (ActionName == "Press G")
		{
			Input->BindAction(Mapping.Action.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::PressG);
		}
		else if (ActionName == "Release G")
		{
			Input->BindAction(Mapping.Action.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::ReleaseG);
		}
		else if (ActionName == "Press H")
		{
			Input->BindAction(Mapping.Action.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::PressH);
		}
		else if (ActionName == "Release H")
		{
			Input->BindAction(Mapping.Action.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::ReleaseH);
		}
	}
}

void ANightSkyPlayerController::PressUp()
{
	Inputs |= INP_Up;
}

void ANightSkyPlayerController::ReleaseUp()
{
	Inputs = Inputs & ~INP_Up;
}

void ANightSkyPlayerController::PressDown()
{
	Inputs |= INP_Down;
}

void ANightSkyPlayerController::ReleaseDown()
{
	Inputs = Inputs & ~INP_Down;
}

void ANightSkyPlayerController::PressLeft()
{
	Inputs |= INP_Left;
}

void ANightSkyPlayerController::ReleaseLeft()
{
	Inputs = Inputs & ~INP_Left;
}

void ANightSkyPlayerController::PressRight()
{
	Inputs |= INP_Right;
}

void ANightSkyPlayerController::ReleaseRight()
{
	Inputs = Inputs & ~INP_Right;
}

void ANightSkyPlayerController::PressA()
{
	Inputs |= INP_L;
}

void ANightSkyPlayerController::ReleaseA()
{
	Inputs = Inputs & ~INP_L;
}

void ANightSkyPlayerController::PressB()
{
	Inputs |= INP_M;
}

void ANightSkyPlayerController::ReleaseB()
{
	Inputs = Inputs & ~INP_M;
}

void ANightSkyPlayerController::PressC()
{
	Inputs |= INP_H;
}

void ANightSkyPlayerController::ReleaseC()
{
	Inputs = Inputs & ~INP_H;
}

void ANightSkyPlayerController::PressD()
{
	Inputs |= INP_S;
}

void ANightSkyPlayerController::ReleaseD()
{
	Inputs = Inputs & ~INP_S;
}

void ANightSkyPlayerController::PressE()
{
	Inputs |= INP_E;	
}

void ANightSkyPlayerController::ReleaseE()
{
	Inputs = Inputs & ~INP_E;
}

void ANightSkyPlayerController::PressF()
{
	Inputs |= INP_F;	
}

void ANightSkyPlayerController::ReleaseF()
{
	Inputs = Inputs & ~INP_F;
}

void ANightSkyPlayerController::PressG()
{
	Inputs |= INP_G;
}

void ANightSkyPlayerController::ReleaseG()
{
	Inputs = Inputs & ~INP_G;
}


void ANightSkyPlayerController::PressH()
{
	Inputs |= INP_H;
}

void ANightSkyPlayerController::ReleaseH()
{
	Inputs = Inputs & ~INP_H;
}
