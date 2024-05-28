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
#include "NightSkyEngine/Miscellaneous/NightSkySettingsInfo.h"
#include "NightSkyEngine/Miscellaneous/RpcConnectionManager.h"

// Sets default values
ANightSkyPlayerController::ANightSkyPlayerController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Inputs = 0;
	Frame = 0;
	NetworkPawn = nullptr;
}

// Called when the game starts or when spawned
void ANightSkyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	NetworkPawn = Cast<ANetworkPawn>(GetPawn());
	RemapKeys();
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
		if (NetworkPawn->bRematchAccepted && bRematch)
		{
			NetworkPawn->bRematchAccepted = false;
			bRematch = false;
			Cast<ANightSkyGameState>(GetWorld()->GetGameState())->MatchInit();
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
	
	if (IsValid(InputActions.PressUp))
		Input->BindAction(InputActions.PressUp.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::PressUp);
	if (IsValid(InputActions.ReleaseUp))
		Input->BindAction(InputActions.ReleaseUp.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::ReleaseUp);
	if (IsValid(InputActions.PressDown))
		Input->BindAction(InputActions.PressDown.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::PressDown);
	if (IsValid(InputActions.ReleaseDown))
		Input->BindAction(InputActions.ReleaseDown.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::ReleaseDown);
	if (IsValid(InputActions.PressLeft))
		Input->BindAction(InputActions.PressLeft.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::PressLeft);
	if (IsValid(InputActions.ReleaseLeft))
		Input->BindAction(InputActions.ReleaseLeft.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::ReleaseLeft);
	if (IsValid(InputActions.PressRight))
		Input->BindAction(InputActions.PressRight.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::PressRight);
	if (IsValid(InputActions.ReleaseRight))
		Input->BindAction(InputActions.ReleaseRight.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::ReleaseRight);
	if (IsValid(InputActions.PressA))
		Input->BindAction(InputActions.PressA.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::PressA);
	if (IsValid(InputActions.ReleaseA))
		Input->BindAction(InputActions.ReleaseA.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::ReleaseA);
	if (IsValid(InputActions.PressA))
		Input->BindAction(InputActions.PressB.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::PressB);
	if (IsValid(InputActions.ReleaseB))
		Input->BindAction(InputActions.ReleaseB.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::ReleaseB);
	if (IsValid(InputActions.PressC))
		Input->BindAction(InputActions.PressC.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::PressC);
	if (IsValid(InputActions.ReleaseC))
		Input->BindAction(InputActions.ReleaseC.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::ReleaseC);
	if (IsValid(InputActions.PressD))
		Input->BindAction(InputActions.PressD.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::PressD);
	if (IsValid(InputActions.ReleaseD))
		Input->BindAction(InputActions.ReleaseD.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::ReleaseD);
	if (IsValid(InputActions.PressE))
		Input->BindAction(InputActions.PressE.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::PressE);
	if (IsValid(InputActions.ReleaseE))
		Input->BindAction(InputActions.ReleaseE.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::ReleaseE);
	if (IsValid(InputActions.PressF))
		Input->BindAction(InputActions.PressF.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::PressF);
	if (IsValid(InputActions.ReleaseF))
		Input->BindAction(InputActions.ReleaseF.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::ReleaseF);
	if (IsValid(InputActions.PressG))
		Input->BindAction(InputActions.PressG.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::PressG);
	if (IsValid(InputActions.ReleaseG))
		Input->BindAction(InputActions.ReleaseG.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::ReleaseG);
	if (IsValid(InputActions.PressH))
		Input->BindAction(InputActions.PressH.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::PressH);
	if (IsValid(InputActions.ReleaseH))
		Input->BindAction(InputActions.ReleaseH.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::ReleaseH);
	if (IsValid(InputActions.PauseGame))
		Input->BindAction(InputActions.PauseGame.Get(), ETriggerEvent::Triggered, this, &ANightSkyPlayerController::PauseGame);
}

void ANightSkyPlayerController::RemapKeys() const
{
	const auto SettingsInfo = Cast<UNightSkyGameInstance>(GetGameInstance())->SettingsInfo;
	if (SettingsInfo->RemappedBattleKeys.Num() <= 0) return;

	for (auto MappedKey : SettingsInfo->RemappedBattleKeys)
	{
		for (auto Mapping : InputMapping->GetMappings())
		{
			if (Mapping.Action != MappedKey.Key) continue;
			InputMapping->UnmapKey(Mapping.Action, Mapping.Key);
			InputMapping->MapKey(Mapping.Action, MappedKey.Value);
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

void ANightSkyPlayerController::SendGgpo(ANetworkPawn* InNetworkPawn, bool Client) const
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
			const auto SendVal = InNetworkPawn->FighterMultiplayerRunner->connectionManager->sendSchedule.GetTail();
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

void ANightSkyPlayerController::SendBattleData()
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
		const UNightSkyGameInstance* GameInstance = Cast<UNightSkyGameInstance>(GetGameInstance());
		if (PlayerIndex == 0)
		{
			NetworkPawns[1]->ClientGetBattleData(GameInstance->BattleData);
		}
		else
		{
			NetworkPawns[0]->ServerGetBattleData(GameInstance->BattleData);
		}
	}
}

void ANightSkyPlayerController::Rematch()
{
	bRematch = true;
	if (const UNightSkyGameInstance* GameInstance = Cast<UNightSkyGameInstance>(GetGameInstance()); GameInstance->
		FighterRunner != Multiplayer)
	{
		Cast<ANightSkyGameState>(GetWorld()->GetGameState())->MatchInit();
		bRematch = false;
	}
	else
	{	
		if (GetWorld()->GetNetMode() == NM_Client) NetworkPawn->SendRematchToServer();
		else NetworkPawn->SendRematchToClient();
	}
}
