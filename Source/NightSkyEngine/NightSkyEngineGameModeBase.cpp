// Copyright Epic Games, Inc. All Rights Reserved.


#include "NightSkyEngineGameModeBase.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Miscellaneous/NightSkyGameInstance.h"

void ANightSkyEngineGameModeBase::RegisterExistingPlayers()
{
	for (auto It = this->GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		APlayerController* PlayerController = It->Get();
        
		FUniqueNetIdRepl UniqueNetIdRepl;
		if (PlayerController->IsLocalPlayerController())
		{
			ULocalPlayer *LocalPlayer = PlayerController->GetLocalPlayer();
			if (IsValid(LocalPlayer))
			{
				UniqueNetIdRepl = LocalPlayer->GetPreferredUniqueNetId();
			}
			else
			{
				UNetConnection *RemoteNetConnection = Cast<UNetConnection>(PlayerController->Player);
				check(IsValid(RemoteNetConnection));
				UniqueNetIdRepl = RemoteNetConnection->PlayerId;
			}
		}
		else
		{
			UNetConnection *RemoteNetConnection = Cast<UNetConnection>(PlayerController->Player);
			check(IsValid(RemoteNetConnection));
			UniqueNetIdRepl = RemoteNetConnection->PlayerId;
		}

		// Get the unique player ID.
		TSharedPtr<const FUniqueNetId> UniqueNetId = UniqueNetIdRepl.GetUniqueNetId();
		check(UniqueNetId != nullptr);

		// Get the online session interface.
		IOnlineSubsystem *Subsystem = Online::GetSubsystem(PlayerController->GetWorld());
		IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

		// Register the player with the "MyLocalSessionName" session; this name should match the name you provided in CreateSession.
		if (!Session->RegisterPlayer(FName(TEXT("MyLocalSessionName")), *UniqueNetId, false))
		{
			// The player could not be registered; typically you will want to kick the player from the server in this situation.
		}
	}

	this->bAllExistingPlayersRegistered = true;
}

void ANightSkyEngineGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	if (!this->bAllExistingPlayersRegistered)
	{
		// RegisterExistingPlayers has not run yet. When it does, it will register this incoming player
		// controller.
		Super::PostLogin(NewPlayer);
		return;
	}

	check(IsValid(NewPlayer));

	// This code handles logins for both the local player (listen server) and remote players (net connection).
	FUniqueNetIdRepl UniqueNetIdRepl;
	if (NewPlayer->IsLocalPlayerController())
	{
		ULocalPlayer *LocalPlayer = NewPlayer->GetLocalPlayer();
		if (IsValid(LocalPlayer))
		{
			UniqueNetIdRepl = LocalPlayer->GetPreferredUniqueNetId();
		}
		else
		{
			UNetConnection *RemoteNetConnection = Cast<UNetConnection>(NewPlayer->Player);
			check(IsValid(RemoteNetConnection));
			UniqueNetIdRepl = RemoteNetConnection->PlayerId;
		}
	}
	else
	{
		UNetConnection *RemoteNetConnection = Cast<UNetConnection>(NewPlayer->Player);
		check(IsValid(RemoteNetConnection));
		UniqueNetIdRepl = RemoteNetConnection->PlayerId;
	}

	// Get the unique player ID.
	TSharedPtr<const FUniqueNetId> UniqueNetId = UniqueNetIdRepl.GetUniqueNetId();
	check(UniqueNetId != nullptr);

	// Get the online session interface.
	IOnlineSubsystem *Subsystem = Online::GetSubsystem(NewPlayer->GetWorld());
	IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

	// Register the player with the "MyLocalSessionName" session; this name should match the name you provided in CreateSession.
	if (!Session->RegisterPlayer(FName(TEXT("MyLocalSessionName")), *UniqueNetId, false))
	{
		// The player could not be registered; typically you will want to kick the player from the server in this situation.
	}

	Super::PostLogin(NewPlayer);
}

void ANightSkyEngineGameModeBase::PreLogout(APlayerController* InPlayerController)
{
	check(IsValid(InPlayerController));

	// This code handles logins for both the local player (listen server) and remote players (net connection).
	FUniqueNetIdRepl UniqueNetIdRepl;
	if (InPlayerController->IsLocalPlayerController())
	{
		ULocalPlayer *LocalPlayer = InPlayerController->GetLocalPlayer();
		if (IsValid(LocalPlayer))
		{
			UniqueNetIdRepl = LocalPlayer->GetPreferredUniqueNetId();
		}
		else
		{
			UNetConnection *RemoteNetConnection = Cast<UNetConnection>(InPlayerController->Player);
			check(IsValid(RemoteNetConnection));
			UniqueNetIdRepl = RemoteNetConnection->PlayerId;
		}
	}
	else
	{
		UNetConnection *RemoteNetConnection = Cast<UNetConnection>(InPlayerController->Player);
		check(IsValid(RemoteNetConnection));
		UniqueNetIdRepl = RemoteNetConnection->PlayerId;
	}

	// Get the unique player ID.
	TSharedPtr<const FUniqueNetId> UniqueNetId = UniqueNetIdRepl.GetUniqueNetId();
	check(UniqueNetId != nullptr);

	// Get the online session interface.
	IOnlineSubsystem *Subsystem = Online::GetSubsystem(InPlayerController->GetWorld());
	IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

	// Unregister the player with the "MyLocalSessionName" session; this name should match the name you provided in CreateSession.
	if (!Session->UnregisterPlayer(FName(TEXT("MyLocalSessionName")), *UniqueNetId))
	{
		// The player could not be unregistered.
	}

	UNightSkyGameInstance* GameInstance = Cast<UNightSkyGameInstance>(GetGameInstance());
	if (IsValid(GameInstance))
	{
		GameInstance->DestroySession();
		UGameplayStatics::OpenLevel(this, FName(TEXT("Title"), true));
	}
}