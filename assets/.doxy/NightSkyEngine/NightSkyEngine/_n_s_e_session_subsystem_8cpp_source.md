

# File NSESessionSubsystem.cpp

[**File List**](files.md) **>** [**Network**](dir_261b7ff0e57c151ad26fd5c163777bbe.md) **>** [**NSESessionSubsystem.cpp**](_n_s_e_session_subsystem_8cpp.md)

[Go to the documentation of this file](_n_s_e_session_subsystem_8cpp.md)


```C++
// Fill out your copyright notice in the Description page of Project Settings.


#include "NSESessionSubsystem.h"

#include "OnlineSessionSettings.h"
#include "OnlineSubsystemUtils.h"
#include "NightSkyEngine/Miscellaneous/NightSkyGameInstance.h"
#include "Online/OnlineSessionNames.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(NSESessionSubsystem)

FNSESessionInfo::FNSESessionInfo(const FOnlineSessionSearchResult& Result, const FString& Name, int32 OpenPrivate, int32 OpenPublic)
    : SessionSearchResult(Result), OwningUserName(Name), NumOpenPrivateConnections(OpenPrivate),
      NumOpenPublicConnections(OpenPublic)
{
}

UNSESessionSubsystem::UNSESessionSubsystem() : CreateSessionCompleteDelegate(
                                                   FOnCreateSessionCompleteDelegate::CreateUObject(
                                                       this, &ThisClass::OnCreateSessionComplete)),
                                               UpdateSessionCompleteDelegate(
                                                   FOnUpdateSessionCompleteDelegate::CreateUObject(
                                                       this, &ThisClass::OnUpdateSessionComplete)),
                                               StartSessionCompleteDelegate(
                                                   FOnStartSessionCompleteDelegate::CreateUObject(
                                                       this, &ThisClass::OnStartSessionComplete)),
                                               DestroySessionCompleteDelegate(
                                                   FOnDestroySessionCompleteDelegate::CreateUObject(
                                                       this, &ThisClass::OnDestroySessionComplete)),
                                               FindSessionsCompleteDelegate(
                                                   FOnFindSessionsCompleteDelegate::CreateUObject(
                                                       this, &ThisClass::OnFindSessionsComplete)),
                                               JoinSessionCompleteDelegate(
                                                   FOnJoinSessionCompleteDelegate::CreateUObject(
                                                       this, &ThisClass::OnJoinSessionComplete)),
                                               SessionUserInviteAcceptedDelegate(
                                                   FOnSessionUserInviteAcceptedDelegate::CreateUObject(
                                                       this, &ThisClass::OnSessionInviteAccepted)
                                               )
{
    const IOnlineSessionPtr SessionInterface = Online::GetSessionInterface(GetWorld());
    if (!SessionInterface.IsValid()) return;

    SessionUserInviteAcceptedDelegateHandle = SessionInterface->AddOnSessionUserInviteAcceptedDelegate_Handle(SessionUserInviteAcceptedDelegate);
}

void UNSESessionSubsystem::Login()
{
    IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
    IOnlineIdentityPtr Identity = Subsystem->GetIdentityInterface(); // This is the generic OSS interface that will access the EOS OSS.
 
    // If you're logged in, don't try to login again.
    // This can happen if your player travels to a dedicated server or different maps as BeginPlay() will be called each time.
    
    FUniqueNetIdPtr NetId = Identity->GetUniquePlayerId(0);
 
    if (NetId != nullptr && Identity->GetLoginStatus(0) == ELoginStatus::LoggedIn)
    {
        return; 
    }
    
    LoginDelegateHandle = Identity->AddOnLoginCompleteDelegate_Handle(
        0,
        FOnLoginCompleteDelegate::CreateUObject(
            this,
            &ThisClass::OnLoginCompleted));
    
    FString AuthType; 
    FParse::Value(FCommandLine::Get(), TEXT("AUTH_TYPE="), AuthType);
 
    if (!AuthType.IsEmpty()) //If parameter is NOT empty we can autologin.
    {
        /* 
        In most situations you will want to automatically log a player in using the parameters passed via CLI.
        For example, using the exchange code for the Epic Games Store.
        */
        UE_LOG(LogTemp, Log, TEXT("Logging into EOS...")); // Log to the UE logs that we are trying to log in. 
      
        if (!Identity->AutoLogin(0))
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to login... ")); // Log to the UE logs that we are trying to log in.
            // Clear our handle and reset the delegate.
            Identity->ClearOnLoginCompleteDelegate_Handle(0, LoginDelegateHandle);
            LoginDelegateHandle.Reset();            
        }
    }
    else
    {
        /* 
        Fallback if the CLI parameters are empty.Useful for PIE.
        The type here could be developer if using the DevAuthTool, ExchangeCode if the game is launched via the Epic Games Launcher, etc...
        */
        FOnlineAccountCredentials Credentials("accountportal","", "SteamAppTicket");
 
        UE_LOG(LogTemp, Log, TEXT("Logging into EOS...")); // Log to the UE logs that we are trying to log in. 
        
        if (!Identity->Login(0, Credentials))
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to login... ")); // Log to the UE logs that we are trying to log in.
            // Clear our handle and reset the delegate. 
            Identity->ClearOnLoginCompleteDelegate_Handle(0, LoginDelegateHandle);
            LoginDelegateHandle.Reset();
        }        
    }
}

bool UNSESessionSubsystem::IsLoggedIn() const
{
    IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
    IOnlineIdentityPtr Identity = Subsystem->GetIdentityInterface(); // This is the generic OSS interface that will access the EOS OSS.
    
    FUniqueNetIdPtr NetId = Identity->GetUniquePlayerId(0);
 
    if (NetId != nullptr && Identity->GetLoginStatus(0) == ELoginStatus::LoggedIn)
    {
        return true; 
    }
    
    return false;
}

void UNSESessionSubsystem::CreateSession(int32 NumPublicConnections, bool bIsLANMatch)
{
    const IOnlineSessionPtr SessionInterface = Online::GetSessionInterface(GetWorld());
    if (!SessionInterface.IsValid())
    {
        OnCreateSessionCompleteDelegate.Broadcast(false);
        return;
    }

    LastSessionSettings = MakeShareable(new FOnlineSessionSettings());
    LastSessionSettings->NumPrivateConnections = 0;
    LastSessionSettings->NumPublicConnections = NumPublicConnections;
    LastSessionSettings->bAllowInvites = true;
    LastSessionSettings->bAllowJoinInProgress = true;
    LastSessionSettings->bAllowJoinViaPresence = true;
    LastSessionSettings->bAllowJoinViaPresenceFriendsOnly = false;
    LastSessionSettings->bIsDedicated = false;
    LastSessionSettings->bUsesPresence = true;
    LastSessionSettings->bUseLobbiesIfAvailable = true;
    LastSessionSettings->bIsLANMatch = bIsLANMatch;
    LastSessionSettings->bShouldAdvertise = true;

    LastSessionSettings->Set(SEARCH_LOBBIES, true, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

    CreateSessionCompleteDelegateHandle = SessionInterface->AddOnCreateSessionCompleteDelegate_Handle(
        CreateSessionCompleteDelegate);

    if (!SessionInterface->CreateSession(0, NAME_GameSession, *LastSessionSettings))
    {
        SessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegateHandle);

        OnCreateSessionCompleteDelegate.Broadcast(false);
    }
}

void UNSESessionSubsystem::UpdateSession()
{
    const IOnlineSessionPtr SessionInterface = Online::GetSessionInterface(GetWorld());
    if (!SessionInterface.IsValid())
    {
        OnUpdateSessionCompleteEvent.Broadcast(false);
        return;
    }

    const TSharedPtr<FOnlineSessionSettings> UpdatedSessionSettings = MakeShareable(
        new FOnlineSessionSettings(*LastSessionSettings));

    UpdateSessionCompleteDelegateHandle =
        SessionInterface->AddOnUpdateSessionCompleteDelegate_Handle(UpdateSessionCompleteDelegate);

    if (!SessionInterface->UpdateSession(NAME_GameSession, *UpdatedSessionSettings))
    {
        SessionInterface->ClearOnUpdateSessionCompleteDelegate_Handle(UpdateSessionCompleteDelegateHandle);

        OnUpdateSessionCompleteEvent.Broadcast(false);
    }
    else
    {
        LastSessionSettings = UpdatedSessionSettings;
    }
}

void UNSESessionSubsystem::StartSession()
{
    const IOnlineSessionPtr SessionInterface = Online::GetSessionInterface(GetWorld());
    if (!SessionInterface.IsValid())
    {
        OnStartSessionCompleteEvent.Broadcast(false);
        return;
    }

    StartSessionCompleteDelegateHandle =
        SessionInterface->AddOnStartSessionCompleteDelegate_Handle(StartSessionCompleteDelegate);

    if (!SessionInterface->StartSession(NAME_GameSession))
    {
        SessionInterface->ClearOnStartSessionCompleteDelegate_Handle(StartSessionCompleteDelegateHandle);

        OnStartSessionCompleteEvent.Broadcast(false);
    }
}

void UNSESessionSubsystem::DestroySession()
{
    const IOnlineSessionPtr SessionInterface = Online::GetSessionInterface(GetWorld());
    if (!SessionInterface.IsValid())
    {
        OnDestroySessionCompleteEvent.Broadcast(false);
        return;
    }

    DestroySessionCompleteDelegateHandle =
        SessionInterface->AddOnDestroySessionCompleteDelegate_Handle(DestroySessionCompleteDelegate);

    if (!SessionInterface->DestroySession(NAME_GameSession))
    {
        SessionInterface->ClearOnDestroySessionCompleteDelegate_Handle(DestroySessionCompleteDelegateHandle);

        OnDestroySessionCompleteEvent.Broadcast(false);
    }
}

void UNSESessionSubsystem::FindSessions(int32 MaxSearchResults, bool IsLANQuery)
{
    const IOnlineSessionPtr SessionInterface = Online::GetSessionInterface(GetWorld());
    if (!SessionInterface.IsValid())
    {
        OnFindSessionsCompleteEvent.Broadcast(TArray<FNSESessionInfo>(), false);
        return;
    }

    FindSessionsCompleteDelegateHandle =
        SessionInterface->AddOnFindSessionsCompleteDelegate_Handle(FindSessionsCompleteDelegate);

    LastSessionSearch = MakeShareable(new FOnlineSessionSearch());
    LastSessionSearch->MaxSearchResults = MaxSearchResults;
    LastSessionSearch->bIsLanQuery = IsLANQuery;

    LastSessionSearch->QuerySettings.Set(SEARCH_LOBBIES, true, EOnlineComparisonOp::Equals);

    if (!SessionInterface->FindSessions(0, LastSessionSearch.ToSharedRef()))
    {
        SessionInterface->ClearOnFindSessionsCompleteDelegate_Handle(FindSessionsCompleteDelegateHandle);

        OnFindSessionsCompleteEvent.Broadcast(TArray<FNSESessionInfo>(), false);
    }
}

void UNSESessionSubsystem::JoinGameSession_BP(FNSESessionInfo Info)
{
    JoinGameSession(Info.SessionSearchResult);
}

void UNSESessionSubsystem::JoinGameSession(const FOnlineSessionSearchResult& SessionResult)
{
    const IOnlineSessionPtr SessionInterface = Online::GetSessionInterface(GetWorld());
    if (!SessionInterface.IsValid())
    {
        OnJoinGameSessionCompleteEvent.Broadcast(EOnJoinSessionCompleteResult::UnknownError);
        return;
    }

    JoinSessionCompleteDelegateHandle =
        SessionInterface->AddOnJoinSessionCompleteDelegate_Handle(JoinSessionCompleteDelegate);

    auto ModResult = SessionResult;
    
    ModResult.Session.SessionSettings.bUsesPresence = true;
    ModResult.Session.SessionSettings.bUseLobbiesIfAvailable = true;
    if (!SessionInterface->JoinSession(0, NAME_GameSession, ModResult))
    {
        SessionInterface->ClearOnJoinSessionCompleteDelegate_Handle(JoinSessionCompleteDelegateHandle);

        OnJoinGameSessionCompleteEvent.Broadcast(EOnJoinSessionCompleteResult::UnknownError);
    }
}

void UNSESessionSubsystem::OnLoginCompleted(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId,
    const FString& Error)
{
    IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
    IOnlineIdentityPtr Identity = Subsystem->GetIdentityInterface();
    if (bWasSuccessful)
    {
        UE_LOG(LogTemp, Log, TEXT("Login callback completed!"));; 
    }
    else //Login failed
    {
        // TODO: set login failed message
        UE_LOGFMT(LogTemp, Error, "EOS login failed. Error: {0}", Error); //Print sign in failure in logs as an error
    }
 
    Identity->ClearOnLoginCompleteDelegate_Handle(LocalUserNum, LoginDelegateHandle);
    LoginDelegateHandle.Reset();
}

void UNSESessionSubsystem::OnCreateSessionComplete(FName SessionName, bool bSuccess)
{
    if (const IOnlineSessionPtr SessionInterface = Online::GetSessionInterface(GetWorld()))
    {
        SessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegateHandle);
    }

    OnCreateSessionCompleteDelegate.Broadcast(bSuccess);
}

void UNSESessionSubsystem::OnUpdateSessionComplete(FName SessionName, bool bSuccess)
{
    if (const IOnlineSessionPtr SessionInterface = Online::GetSessionInterface(GetWorld()))
    {
        SessionInterface->ClearOnUpdateSessionCompleteDelegate_Handle(UpdateSessionCompleteDelegateHandle);
    }

    OnUpdateSessionCompleteEvent.Broadcast(bSuccess);
}

void UNSESessionSubsystem::OnStartSessionComplete(FName SessionName, bool bSuccess)
{
    if (const IOnlineSessionPtr SessionInterface = Online::GetSessionInterface(GetWorld()))
    {
        SessionInterface->ClearOnStartSessionCompleteDelegate_Handle(StartSessionCompleteDelegateHandle);
    }

    OnStartSessionCompleteEvent.Broadcast(bSuccess);
}

void UNSESessionSubsystem::OnDestroySessionComplete(FName SessionName, bool bSuccess)
{
    if (const IOnlineSessionPtr SessionInterface = Online::GetSessionInterface(GetWorld()))
    {
        SessionInterface->ClearOnDestroySessionCompleteDelegate_Handle(DestroySessionCompleteDelegateHandle);
    }

    OnDestroySessionCompleteEvent.Broadcast(bSuccess);
}

void UNSESessionSubsystem::OnFindSessionsComplete(bool bSuccess)
{
    if (const IOnlineSessionPtr SessionInterface = Online::GetSessionInterface(GetWorld()))
    {
        SessionInterface->ClearOnFindSessionsCompleteDelegate_Handle(FindSessionsCompleteDelegateHandle);
    }

    if (LastSessionSearch->SearchResults.Num() <= 0)
    {
        OnFindSessionsCompleteEvent.Broadcast(TArray<FNSESessionInfo>(), bSuccess);
        return;
    }

    TArray<FNSESessionInfo> Sessions{};
    for (auto SearchResult : LastSessionSearch->SearchResults)
    {
        Sessions.Add(FNSESessionInfo(
            SearchResult, SearchResult.Session.OwningUserName, SearchResult.Session.NumOpenPrivateConnections,
            SearchResult.Session.NumOpenPublicConnections
        ));
    }

    OnFindSessionsCompleteEvent.Broadcast(Sessions, bSuccess);
}

void UNSESessionSubsystem::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
    if (const IOnlineSessionPtr SessionInterface = Online::GetSessionInterface(GetWorld()))
    {
        SessionInterface->ClearOnJoinSessionCompleteDelegate_Handle(JoinSessionCompleteDelegateHandle);
    }

    OnJoinGameSessionCompleteEvent.Broadcast(Result);

    TryTravelToCurrentSession();
}

void UNSESessionSubsystem::OnSessionInviteAccepted(const bool bSuccess, const int32 ControllerId,
                                                   FUniqueNetIdPtr UserId,
                                                   const FOnlineSessionSearchResult& InviteResult)
{
    const auto GameInstance = Cast<UNightSkyGameInstance>(GetGameInstance());
    if (!IsValid(GameInstance))
    {
        UE_LOG(LogTemp, Error, TEXT("OnSessionInviteAccepted: Invalid GameInstance"));
        return;
    }
    if (GameInstance->BattleData.PlayerListP2.IsEmpty()) return;
    
    JoinGameSession(InviteResult);
}

bool UNSESessionSubsystem::TryTravelToCurrentSession()
{
    const IOnlineSessionPtr SessionInterface = Online::GetSessionInterface(GetWorld());
    if (!SessionInterface.IsValid())
    {
        return false;
    }

    FString ConnectString;
    if (!SessionInterface->GetResolvedConnectString(NAME_GameSession, ConnectString))
    {
        return false;
    }

    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    PlayerController->ClientTravel(ConnectString, TRAVEL_Absolute);
    return true;
}
```


