// Fill out your copyright notice in the Description page of Project Settings.


#include "NightSkyGameInstance.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "Kismet/GameplayStatics.h"
#include "NightSkyEngine/NightSkyEngineGameModeBase.h"


bool UNightSkyGameInstance::Login()
{
	IOnlineSubsystem *Subsystem = Online::GetSubsystem(this->GetWorld());
	IOnlineIdentityPtr Identity = Subsystem->GetIdentityInterface();

	this->LoginDelegateHandle = Identity->AddOnLoginCompleteDelegate_Handle(
	0,
	FOnLoginComplete::FDelegate::CreateUObject(
		this,
		&UNightSkyGameInstance::HandleLoginComplete));

	FOnlineAccountCredentials Credentials;
	Credentials.Id = "";
	Credentials.Token = "";
	Credentials.Type = "accountportal";
	
	if (!Identity->Login(0 /* LocalUserNum */, Credentials))
	{
		return false;
	}
	
	IOnlineSessionPtr Session = Subsystem->GetSessionInterface();
	Session->OnSessionUserInviteAcceptedDelegates.AddUObject(this, &UNightSkyGameInstance::OnSessionInviteAccepted);
	return true;
}

void UNightSkyGameInstance::OnSessionInviteAccepted(bool bArg, int I,
	TSharedPtr<const FUniqueNetId, ESPMode::ThreadSafe> UniqueNetId,
	const FOnlineSessionSearchResult& OnlineSessionSearchResult)
{
	InviteResult = OnlineSessionSearchResult;
	
	IOnlineSubsystem* Subsystem = Online::GetSubsystem(this->GetWorld());
	IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

	this->JoinSessionDelegateHandle =
		Session->AddOnJoinSessionCompleteDelegate_Handle(FOnJoinSessionComplete::FDelegate::CreateUObject(
				this,
				&UNightSkyGameInstance::HandleJoinInviteSessionComplete));

	// "MyLocalSessionName" is the local name of the session for this player. It doesn't have to match the name the server gave their session.
	Session->JoinSession(0, FName(TEXT("MyLocalSessionName")), OnlineSessionSearchResult);
}

void UNightSkyGameInstance::HandleLoginComplete(int I, bool bArg, const FUniqueNetId& UniqueNetId, const FString& String)
{
	IOnlineSubsystem *Subsystem = Online::GetSubsystem(this->GetWorld());
	IOnlineIdentityPtr Identity = Subsystem->GetIdentityInterface();
	Identity->ClearOnLoginCompleteDelegate_Handle(0, this->LoginDelegateHandle);
	this->LoginDelegateHandle.Reset();
}

bool UNightSkyGameInstance::GetFriendsList()
{
	IOnlineSubsystem *Subsystem = Online::GetSubsystem(this->GetWorld());
	IOnlineFriendsPtr Friends = Subsystem->GetFriendsInterface();
	
	return Friends->ReadFriendsList(
	0 /* LocalUserNum */,
	TEXT("") /* ListName, unused by EOS */,
	FOnReadFriendsListComplete::CreateUObject(this, &UNightSkyGameInstance::OnReadComplete)
	);
}

bool UNightSkyGameInstance::CreateSession()
{
	IOnlineSubsystem* Subsystem = Online::GetSubsystem(this->GetWorld());
	IOnlineSessionPtr Session = Subsystem->GetSessionInterface();
	
	this->CreateSessionDelegateHandle =
		Session->AddOnCreateSessionCompleteDelegate_Handle(FOnCreateSessionComplete::FDelegate::CreateUObject(
			this,
			&UNightSkyGameInstance::HandleCreateSessionComplete));
	TSharedRef<FOnlineSessionSettings> SessionSettings = MakeShared<FOnlineSessionSettings>();

	SessionSettings->NumPublicConnections = 2; // The number of players.
	SessionSettings->bShouldAdvertise = true;  // Set to true to make this session discoverable with FindSessions.
	SessionSettings->bUsesPresence = true;    // Set to true if you want this session to be discoverable by presence (Epic Social Overlay).
	SessionSettings->bAllowInvites = true;    // Set to true if you want this session to be allow invites.

	// You *must* set at least one setting value, because you can not run FindSessions without any filters.
	SessionSettings->Settings.Add(
		FName(TEXT("Version")),
		FOnlineSessionSetting(static_cast<int64>(FNetworkVersion::GetLocalNetworkVersion()), EOnlineDataAdvertisementType::ViaOnlineService));

	// Create a session and give the local name "MyLocalSessionName". This name is entirely local to the current player and isn't stored in EOS.
	if (!Session->CreateSession(0, FName(TEXT("MyLocalSessionName")), *SessionSettings))
	{
		return false;
	}
	return true;
}

bool UNightSkyGameInstance::CreateLobby()
{
	IOnlineSubsystem* Subsystem = Online::GetSubsystem(this->GetWorld());
	IOnlineIdentityPtr Identity = Subsystem->GetIdentityInterface();
	TSharedPtr<IOnlineLobby, ESPMode::ThreadSafe> Lobby = Online::GetLobbyInterface(Subsystem);

	TSharedPtr<const FUniqueNetId> LocalUserId = Identity->GetUniquePlayerId(0);
	
	if (!LocalUserId.Get())
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get unique net id!"))
		return false;
	}
	
	TSharedPtr<FOnlineLobbyTransaction> Txn = Lobby->MakeCreateLobbyTransaction(*LocalUserId.Get());
	Txn->SetMetadata.Add(TEXT("LobbySetting"), TEXT("SettingValue"));

	// To allow clients connecting to the listen server to join the lobby based on just the ID, we need
	// to set it to public.
	Txn->Public = true;

	// Here you can adjust the capacity of the lobby. 
	Txn->Capacity = 2;

	// Setting a lobby as locked prevents players from joining it.
	Txn->Locked = false;

	if (!Lobby->CreateLobby(
	*LocalUserId.Get(),
	*Txn,
	FOnLobbyCreateOrConnectComplete::CreateLambda([&](
		const FOnlineError & Error,
		const FUniqueNetId & UserId,
		const TSharedPtr<class FOnlineLobby> & CreatedLobby)
	{
		if (Error.WasSuccessful())
		{
			// The lobby was created successfully and is now in CreatedLobby.
			LobbyID = CreatedLobby->Id;
			UE_LOG(LogTemp, Display, TEXT("Successfully created lobby! %s"), *LobbyID->ToString())
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to create lobby! %s"), *Error.ErrorRaw);
			LobbyID = nullptr;
		}
	})))
	{
		LobbyID = nullptr;
	}
	return LobbyID != nullptr;
}

void UNightSkyGameInstance::OnReadComplete(int I, bool bArg, const FString& String, const FString& String1)
{
	FriendInfos.Empty();
	
	IOnlineSubsystem *Subsystem = Online::GetSubsystem(this->GetWorld());
	IOnlineFriendsPtr Friends = Subsystem->GetFriendsInterface();
	
	TArray<TSharedRef<FOnlineFriend>> FriendsArr;
	Friends->GetFriendsList(
		0 /* LocalUserNum */,
		TEXT("") /* ListName, unused by EOS */,
		FriendsArr /* OutFriends */
	);
	for (const auto& Friend : FriendsArr)
	{
		FFriendInfo FriendInfo;
		FriendInfo.DisplayName = Friend->GetDisplayName();
		FriendInfo.NetId = Friend->GetUserId();
		FriendInfos.Add(FriendInfo);
	}
}

bool UNightSkyGameInstance::SearchForServer()
{
	IOnlineSubsystem* Subsystem = Online::GetSubsystem(this->GetWorld());
	IOnlineSessionPtr Session = Subsystem->GetSessionInterface();
	
	TSharedRef<FOnlineSessionSearch> Search = MakeShared<FOnlineSessionSearch>();
	// Remove the default search parameters that FOnlineSessionSearch sets up.
	Search->QuerySettings.SearchParams.Empty();
	
	Search->QuerySettings.SearchParams.Add(
		FName(TEXT("Version")), 
		FOnlineSessionSearchParam(
			static_cast<int64>(FNetworkVersion::GetLocalNetworkVersion()),
			EOnlineComparisonOp::Equals));

	this->FindSessionsDelegateHandle =
	Session->AddOnFindSessionsCompleteDelegate_Handle(FOnFindSessionsComplete::FDelegate::CreateUObject(
		this,
		&UNightSkyGameInstance::HandleFindSessionsComplete,
		Search));
	
	if (!Session->FindSessions(0, Search))
	{
		return false;
	}
	
	return true;
}

bool UNightSkyGameInstance::SearchForLobby()
{
	IOnlineSubsystem* Subsystem = Online::GetSubsystem(this->GetWorld());
	TSharedPtr<IOnlineLobby, ESPMode::ThreadSafe> Lobby = Online::GetLobbyInterface(Subsystem);
	IOnlineIdentityPtr Identity = Subsystem->GetIdentityInterface();

	TSharedPtr<const FUniqueNetId> LocalUserId = Identity->GetUniquePlayerId(0);
	TSharedRef<FOnlineLobbySearchQuery> Search = MakeShared<FOnlineLobbySearchQuery>();

	// To search by settings, add a LobbySetting and SettingValue to search for:
	Search->Filters.Add(
		FOnlineLobbySearchQueryFilter(
		FString(TEXT("LobbySetting")),
		FString(TEXT("SettingValue")),
		EOnlineLobbySearchQueryFilterComparator::Equal));

	if (!LocalUserId.Get())
		return false;
	
	if (!Lobby->Search(
		*LocalUserId.Get(),
		*Search,
		FOnLobbySearchComplete::CreateLambda([&](const FOnlineError &Error,
			const FUniqueNetId &UserId,
		    const TArray<TSharedRef<const FOnlineLobbyId>> &Lobbies)
		{
			if (Error.WasSuccessful())
			{
				// The search was successful, access the results
				// via the "Lobbies" parameter.
				LobbyInfos = Lobbies;
				LobbyIDs.Empty();
				UE_LOG(LogTemp, Display, TEXT("%d lobbies found."), Lobbies.Num());
				for (auto Info : LobbyInfos)
				{
					LobbyIDs.Add(Info.Get().ToString());
				}
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Failed to find lobbies! %s"), *Error.ErrorRaw);
				LobbyIDs.Empty();
				LobbyInfos.Empty();
			}
		}
	)))
	{
		LobbyIDs.Empty();
		LobbyInfos.Empty();
	}
	
	return !LobbyInfos.IsEmpty();;
}

void UNightSkyGameInstance::HandleFindSessionsComplete(bool bArg, TSharedRef<FOnlineSessionSearch, ESPMode::ThreadSafe> Shared)
{
	IOnlineSubsystem *Subsystem = Online::GetSubsystem(GetWorld());
	IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

	if (bArg)
	{
		for (auto RawResult : Shared->SearchResults)
		{
			if (RawResult.IsValid())
			{
				FString ConnectInfo;
				if (Session->GetResolvedConnectString(RawResult, NAME_GamePort, ConnectInfo))
				{
					FSessionInfo SessionInfo;
					SessionInfo.Result = RawResult;
					SessionInfo.ConnectInfo = ConnectInfo;

					bool Duplicate = false;
					
					for (auto StoredSession : SessionInfos)
					{
						if (StoredSession.ConnectInfo == ConnectInfo)
						{
							Duplicate = true;
							break;
						}
					}

					if (!Duplicate)
						SessionInfos.Add(SessionInfo);
				}
			}
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Session count: %d"), SessionInfos.Num())
	
	Session->ClearOnFindSessionsCompleteDelegate_Handle(this->FindSessionsDelegateHandle);
	this->FindSessionsDelegateHandle.Reset();
}

bool UNightSkyGameInstance::JoinServer(FString ConnectInfo)
{
	FOnlineSessionSearchResult SearchResult;

	for (int i = 0; i < SessionInfos.Num(); i++)
	{
		if (ConnectInfo == SessionInfos[i].ConnectInfo)
		{
			SearchResult = SessionInfos[i].Result;
			SessionIndex = i;
			break;
		}
		if (i == i < SessionInfos.Num() - 1)
			return false;
	}
	
	IOnlineSubsystem* Subsystem = Online::GetSubsystem(this->GetWorld());
	IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

	this->JoinSessionDelegateHandle =
		Session->AddOnJoinSessionCompleteDelegate_Handle(FOnJoinSessionComplete::FDelegate::CreateUObject(
				this,
				&UNightSkyGameInstance::HandleJoinSessionComplete));

		// "MyLocalSessionName" is the local name of the session for this player. It doesn't have to match the name the server gave their session.
	if (!Session->JoinSession(0, FName(TEXT("MyLocalSessionName")), SearchResult))
	{
		return false;
	}
	return true;
}

bool UNightSkyGameInstance::JoinLobby(FString InLobbyID)
{
	IOnlineSubsystem* Subsystem = Online::GetSubsystem(this->GetWorld());
	TSharedPtr<IOnlineLobby, ESPMode::ThreadSafe> Lobby = Online::GetLobbyInterface(Subsystem);
	IOnlineIdentityPtr Identity = Subsystem->GetIdentityInterface();
	TSharedPtr<const FUniqueNetId> LocalUserId = Identity->GetUniquePlayerId(0);

	if (!LocalUserId.Get())
		return false;
	
	for (FString ID : LobbyIDs)
	{
		if (!Lobby->ConnectLobby(
			*LocalUserId.Get(),
			*LobbyInfos[LobbyIDs.Find(ID)],
			FOnLobbyCreateOrConnectComplete::CreateLambda([&, ID](
				const FOnlineError & Error,
				const FUniqueNetId & UserId,
				const TSharedPtr<class FOnlineLobby> & CreatedLobby)
			{
				if (Error.WasSuccessful())
				{
					LobbyID = LobbyInfos[LobbyIDs.Find(ID)];
				}
				else
				{
					UE_LOG(LogTemp, Error, TEXT("Failed to join lobby! %s"), *Error.ErrorRaw);
					LobbyID = nullptr;
				}
			})))
		{
			LobbyID = nullptr;
		}
	}
	return LobbyID != nullptr;
}

bool UNightSkyGameInstance::DestroySession()
{
	IOnlineSubsystem* Subsystem = Online::GetSubsystem(this->GetWorld());
	IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

	this->DestroySessionDelegateHandle =
	Session->AddOnDestroySessionCompleteDelegate_Handle(FOnDestroySessionComplete::FDelegate::CreateUObject(
			this,
			&UNightSkyGameInstance::HandleDestroySessionComplete));

	if (!Session->DestroySession(FName(TEXT("MyLocalSessionName"))))
	{
		return false;
	}
	return true;
}

bool UNightSkyGameInstance::DestroyLobby()
{
	if (LobbyID == nullptr)
		return false;
	
	IOnlineSubsystem* Subsystem = Online::GetSubsystem(this->GetWorld());
	IOnlineIdentityPtr Identity = Subsystem->GetIdentityInterface();
	TSharedPtr<IOnlineLobby, ESPMode::ThreadSafe> Lobby = Online::GetLobbyInterface(Subsystem);
	TSharedPtr<const FUniqueNetId> LocalUserId = Identity->GetUniquePlayerId(0);
	
	if (!LocalUserId.Get())
		return false;
	
	if (!Lobby->DeleteLobby(
	*LocalUserId.Get(),
	*LobbyID,
	FOnLobbyOperationComplete::CreateLambda([&](
		const FOnlineError & Error,
		const FUniqueNetId & UserId)
	{
		if (Error.WasSuccessful())
		{
			LobbyID = nullptr;
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to destroy lobby! %s"), *Error.ErrorRaw);
		}
	})))
	{
	}

	return LobbyID == nullptr;	
}

void UNightSkyGameInstance::SeamlessTravel()
{
	UGameplayStatics::OpenLevel(this, *StageURL, true, "listen");
	//this->GetWorld()->ServerTravel(StageURL);
}

void UNightSkyGameInstance::HandleJoinSessionComplete(FName Name, EOnJoinSessionCompleteResult::Type Arg)
{
	if (Arg == EOnJoinSessionCompleteResult::Success ||
		Arg == EOnJoinSessionCompleteResult::AlreadyInSession)
	{
		if (GEngine != nullptr)
		{
			FURL NewURL(nullptr, *SessionInfos[SessionIndex].ConnectInfo, ETravelType::TRAVEL_Absolute);
			FString BrowseError;
			if (GEngine->Browse(GEngine->GetWorldContextFromWorldChecked(this->GetWorld()), NewURL, BrowseError) ==
				EBrowseReturnVal::Failure)
			{
				UE_LOG(LogTemp, Error, TEXT("Failed to start browse: %s"), *BrowseError);
			}
		}
		// Use the connection string that you got from FindSessions in order
		// to connect to the server.
		//
		// Refer to "Connecting to a game server" under the "Networking & Anti-Cheat"
		// section of the documentation for more information on how to do this.
		//
		// NOTE: You can also call GetResolvedConnectString at this point instead
		// of in FindSessions, but it's recommended that you call it in
		// FindSessions so you know the result is valid.
	}

	IOnlineSubsystem *Subsystem = Online::GetSubsystem(GetWorld());
	IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

	Session->ClearOnJoinSessionCompleteDelegate_Handle(this->JoinSessionDelegateHandle);
	this->JoinSessionDelegateHandle.Reset();
}

void UNightSkyGameInstance::HandleJoinInviteSessionComplete(FName Name, EOnJoinSessionCompleteResult::Type Arg)
{
	IOnlineSubsystem *Subsystem = Online::GetSubsystem(GetWorld());
	IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

	if (Arg == EOnJoinSessionCompleteResult::Success ||
		Arg == EOnJoinSessionCompleteResult::AlreadyInSession)
	{
		if (GEngine != nullptr)
		{
			FString ConnectInfo;
			if (Session->GetResolvedConnectString(InviteResult, NAME_GamePort, ConnectInfo))
			{
				FSessionInfo SessionInfo;
				SessionInfo.Result = InviteResult;
				SessionInfo.ConnectInfo = ConnectInfo;

				FURL NewURL(nullptr, *SessionInfo.ConnectInfo, ETravelType::TRAVEL_Absolute);
				FString BrowseError;
				if (GEngine->Browse(GEngine->GetWorldContextFromWorldChecked(this->GetWorld()), NewURL, BrowseError) ==
					EBrowseReturnVal::Failure)
				{
					UE_LOG(LogTemp, Error, TEXT("Failed to start browse: %s"), *BrowseError);
				}
			}
		}
		// Use the connection string that you got from FindSessions in order
		// to connect to the server.
		//
		// Refer to "Connecting to a game server" under the "Networking & Anti-Cheat"
		// section of the documentation for more information on how to do this.
		//
		// NOTE: You can also call GetResolvedConnectString at this point instead
		// of in FindSessions, but it's recommended that you call it in
		// FindSessions so you know the result is valid.
	}

	Session->ClearOnJoinSessionCompleteDelegate_Handle(this->JoinSessionDelegateHandle);
	this->JoinSessionDelegateHandle.Reset();
}

void UNightSkyGameInstance::HandleDestroySessionComplete(FName Name, bool bArg)
{
	IOnlineSubsystem *Subsystem = Online::GetSubsystem(this->GetWorld());
	IOnlineSessionPtr Session = Subsystem->GetSessionInterface();
	Session->ClearOnDestroySessionCompleteDelegate_Handle(this->DestroySessionDelegateHandle);
	this->DestroySessionDelegateHandle.Reset();
}

void UNightSkyGameInstance::HandleCreateSessionComplete(FName Name, bool bArg)
{
	IOnlineSubsystem *Subsystem = Online::GetSubsystem(this->GetWorld());
	IOnlineSessionPtr Session = Subsystem->GetSessionInterface();
	Session->ClearOnCreateSessionCompleteDelegate_Handle(this->CreateSessionDelegateHandle);
	this->CreateSessionDelegateHandle.Reset();
}