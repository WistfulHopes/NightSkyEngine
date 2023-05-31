// Fill out your copyright notice in the Description page of Project Settings.


#include "NightSkyPlayerController.h"

#include "EngineUtils.h"
#include "NightSkyEngine/Battle/Bitflags.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "NightSkyGameState.h"
#include "FighterRunners/FighterMultiplayerRunner.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/GameplayStatics.h"
#include "NightSkyEngine/Miscellaneous/NetworkPawn.h"
#include "NightSkyEngine/Miscellaneous/NightSkyGameInstance.h"
#include "NightSkyEngine/Miscellaneous/RpcConnectionManager.h"

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
	
	NetworkPawn = Cast<ANetworkPawn>(GetPawn());
}

// Called every frame
void ANightSkyPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (NetworkPawn != nullptr)
	{
		const int PlayerIndex = Cast<UNightSkyGameInstance>(GetGameInstance())->PlayerIndex;
		TArray<ANetworkPawn*> NetworkPawns;
		for (TActorIterator<ANetworkPawn> It(GetWorld()); It; ++It)
		{
			NetworkPawns.Add(*It);
		}
		if (NetworkPawns.Num() > 1)
		{
			if (PlayerIndex == 0)
			{
				SendGgpo(NetworkPawns[1], true);
			}
			else
			{
				SendGgpo(NetworkPawns[0], false);
			}
		}
	}
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
		FString ActionName = Mapping.Action.Get()->GetName();
		if (ActionName == "PressUp")
		{
			Input->BindAction(Mapping.Action.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::PressUp);
		}
		else if (ActionName == "ReleaseUp")
		{
			Input->BindAction(Mapping.Action.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::ReleaseUp);
		}
		else if (ActionName == "PressDown")
		{
			Input->BindAction(Mapping.Action.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::PressDown);
		}
		else if (ActionName == "ReleaseDown")
		{
			Input->BindAction(Mapping.Action.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::ReleaseDown);
		}
		else if (ActionName == "PressLeft")
		{
			Input->BindAction(Mapping.Action.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::PressLeft);
		}
		else if (ActionName == "ReleaseLeft")
		{
			Input->BindAction(Mapping.Action.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::ReleaseLeft);
		}
		else if (ActionName == "PressRight")
		{
			Input->BindAction(Mapping.Action.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::PressRight);
		}
		else if (ActionName == "ReleaseRight")
		{
			Input->BindAction(Mapping.Action.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::ReleaseRight);
		}
		else if (ActionName == "PressA")
		{
			Input->BindAction(Mapping.Action.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::PressA);
		}
		else if (ActionName == "ReleaseA")
		{
			Input->BindAction(Mapping.Action.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::ReleaseA);
		}
		else if (ActionName == "PressB")
		{
			Input->BindAction(Mapping.Action.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::PressB);
		}
		else if (ActionName == "ReleaseB")
		{
			Input->BindAction(Mapping.Action.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::ReleaseB);
		}
		else if (ActionName == "PressC")
		{
			Input->BindAction(Mapping.Action.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::PressC);
		}
		else if (ActionName == "ReleaseC")
		{
			Input->BindAction(Mapping.Action.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::ReleaseC);
		}
		else if (ActionName == "PressD")
		{
			Input->BindAction(Mapping.Action.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::PressD);
		}
		else if (ActionName == "ReleaseD")
		{
			Input->BindAction(Mapping.Action.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::ReleaseD);
		}
		else if (ActionName == "PressE")
		{
			Input->BindAction(Mapping.Action.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::PressE);
		}
		else if (ActionName == "ReleaseE")
		{
			Input->BindAction(Mapping.Action.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::ReleaseE);
		}
		else if (ActionName == "PressF")
		{
			Input->BindAction(Mapping.Action.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::PressF);
		}
		else if (ActionName == "ReleaseF")
		{
			Input->BindAction(Mapping.Action.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::ReleaseF);
		}
		else if (ActionName == "PressG")
		{
			Input->BindAction(Mapping.Action.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::PressG);
		}
		else if (ActionName == "ReleaseG")
		{
			Input->BindAction(Mapping.Action.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::ReleaseG);
		}
		else if (ActionName == "PressH")
		{
			Input->BindAction(Mapping.Action.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::PressH);
		}
		else if (ActionName == "ReleaseH")
		{
			Input->BindAction(Mapping.Action.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::ReleaseH);
		}
		else if (ActionName == "PauseGame")
		{
			Input->BindAction(Mapping.Action.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::PauseGame);
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
	Inputs |= INP_A;
}

void ANightSkyPlayerController::ReleaseA()
{
	Inputs = Inputs & ~INP_A;
}

void ANightSkyPlayerController::PressB()
{
	Inputs |= INP_B;
}

void ANightSkyPlayerController::ReleaseB()
{
	Inputs = Inputs & ~INP_B;
}

void ANightSkyPlayerController::PressC()
{
	Inputs |= INP_C;
}

void ANightSkyPlayerController::ReleaseC()
{
	Inputs = Inputs & ~INP_C;
}

void ANightSkyPlayerController::PressD()
{
	Inputs |= INP_D;
}

void ANightSkyPlayerController::ReleaseD()
{
	Inputs = Inputs & ~INP_D;
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

void ANightSkyPlayerController::PauseGame()
{
	const auto GameState = Cast<ANightSkyGameState>(GetWorld()->GetGameState());
	if (!GameState->bPauseGame)
	{
		GameState->bPauseGame = true;
		OpenPauseMenu();
	}
}

void ANightSkyPlayerController::UpdateInput(int Input[], int32 InFrame) const
{
	const int PlayerIndex = Cast<UNightSkyGameInstance>(GetGameInstance())->PlayerIndex;
	TArray<ANetworkPawn*> NetworkPawns;
	for (TActorIterator<ANetworkPawn> It(GetWorld()); It; ++It)
	{
		NetworkPawns.Add(*It);
	}
	TArray<int32> SendInputs;
	for (int i = 0; i < MaxRollbackFrames; i++)
	{
		SendInputs.Add(Input[i]);
	}
	if (NetworkPawns.Num() > 1)
	{
		if (PlayerIndex == 0)
		{
			for (int i = 0; i < MaxRollbackFrames; i++)
			{
				NetworkPawns[1]->SendToClient(SendInputs, InFrame);
			}
		}
		else
		{
			for (int i = 0; i < MaxRollbackFrames; i++)
			{
				NetworkPawns[0]->SendToServer(SendInputs, InFrame);
			}
		}
	}
}

void ANightSkyPlayerController::SendGgpo(ANetworkPawn* InNetworkPawn, bool Client)
{
	if(InNetworkPawn->FighterMultiplayerRunner==nullptr)//TODO: CHECK IF MULTIPLAYERRUNNER IS SPAWNED BEFORE THIS, IF SO DO THIS IN BEGINPLAY
	{
		TArray<AActor*> FoundFighterGameStates;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFighterMultiplayerRunner::StaticClass(), FoundFighterGameStates);
		if(FoundFighterGameStates.Num()>0)
		{
			InNetworkPawn->FighterMultiplayerRunner = Cast<AFighterMultiplayerRunner>(FoundFighterGameStates[0]);
		}
	}

	if (InNetworkPawn->FighterMultiplayerRunner && InNetworkPawn->FighterMultiplayerRunner->connectionManager)
	{
		while(InNetworkPawn->FighterMultiplayerRunner->connectionManager->sendSchedule.Num()>0)
		{
			auto SendVal = InNetworkPawn->FighterMultiplayerRunner->connectionManager->sendSchedule.GetTail();
			if(Client)
			{
				InNetworkPawn->SendGgpoToClient(SendVal->GetValue());
			}
			else
			{
				InNetworkPawn->SendGgpoToServer(SendVal->GetValue());
			}
			InNetworkPawn->FighterMultiplayerRunner->connectionManager->sendSchedule.Empty();
			//InNetworkPawn->FighterMultiplayerRunner->connectionManager->sendSchedule.RemoveNode(SendVal);
		}
	}
}

void ANightSkyPlayerController::SendCharaData()
{
	int PlayerIndex = 0;
	if (GetWorld()->GetNetMode() == NM_Client)
		PlayerIndex = Cast<UNightSkyGameInstance>(GetGameInstance())->PlayerIndex = 1;
	TArray<ANetworkPawn*> NetworkPawns;
	for (TActorIterator<ANetworkPawn> It(GetWorld()); It; ++It)
	{
		NetworkPawns.Add(*It);
	}
	if (NetworkPawns.Num() > 1)
	{
		UNightSkyGameInstance* GameInstance = Cast<UNightSkyGameInstance>(GetGameInstance());
		if (PlayerIndex == 0)
		{
			NetworkPawns[1]->ClientGetCharaData(GameInstance->PlayerList[0], GameInstance->RoundFormat, GameInstance->StartRoundTimer);
		}
		else
		{
			NetworkPawns[0]->ServerGetCharaData(GameInstance->PlayerList[3]);
		}
	}
}
