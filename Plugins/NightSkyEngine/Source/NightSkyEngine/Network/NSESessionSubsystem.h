﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnlineSessionSettings.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "NSESessionSubsystem.generated.h"

USTRUCT(BlueprintType)
struct FNSESessionInfo
{
	GENERATED_BODY()

	FNSESessionInfo() = default;
	FNSESessionInfo(const FOnlineSessionSearchResult& Result, const FString& Name, int32 OpenPrivate, int32 OpenPublic);

	/** Session */
	FOnlineSessionSearchResult SessionSearchResult{};
	/** Owner name of the session */
	UPROPERTY(BlueprintReadOnly)
	FString OwningUserName;
	/** The number of private connections that are available (read only) */
	UPROPERTY(BlueprintReadOnly)
	int32 NumOpenPrivateConnections;
	/** The number of publicly available connections that are available (read only) */
	UPROPERTY(BlueprintReadOnly)
	int32 NumOpenPublicConnections;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNSEOnCreateSessionComplete, bool, bSuccess);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNSEOnUpdateSessionComplete, bool, bSuccess);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNSEOnStartSessionComplete, bool, bSuccess);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNSEOnDestroySessionComplete, bool, bSuccess);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FNSEOnFindSessionsComplete, const TArray<FNSESessionInfo>&, SessionResults, bool, bSuccess);
DECLARE_MULTICAST_DELEGATE_OneParam(FNSEOnJoinSessionComplete, EOnJoinSessionCompleteResult::Type Result);

/**
 * 
 */
UCLASS()
class NIGHTSKYENGINE_API UNSESessionSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UNSESessionSubsystem();

	UFUNCTION(BlueprintCallable)
	void CreateSession(int32 NumPublicConnections, bool bIsLANMatch);
	FNSEOnCreateSessionComplete OnCreateSessionCompleteDelegate;
	
	UFUNCTION(BlueprintCallable)
	void UpdateSession();
	FNSEOnUpdateSessionComplete OnUpdateSessionCompleteEvent;
	
	UFUNCTION(BlueprintCallable)
	void StartSession();
	FNSEOnStartSessionComplete OnStartSessionCompleteEvent;
	
	UFUNCTION(BlueprintCallable)
	void DestroySession();
	FNSEOnDestroySessionComplete OnDestroySessionCompleteEvent;
	
	UFUNCTION(BlueprintCallable)
	void FindSessions(int32 MaxSearchResults, bool IsLANQuery);
	UPROPERTY(BlueprintAssignable)
	FNSEOnFindSessionsComplete OnFindSessionsCompleteEvent;

	UFUNCTION(BlueprintCallable)
	void JoinGameSession_BP(FNSESessionInfo Info);
	
	void JoinGameSession(const FOnlineSessionSearchResult& SessionResult);
	FNSEOnJoinSessionComplete OnJoinGameSessionCompleteEvent;

protected:
	void OnCreateSessionComplete(FName SessionName, bool bSuccess);
	void OnUpdateSessionComplete(FName SessionName, bool bSuccess);
	void OnStartSessionComplete(FName SessionName, bool bSuccess);
	void OnDestroySessionComplete(FName SessionName, bool bSuccess);
	void OnFindSessionsComplete(bool bSuccess);
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	void OnSessionInviteAccepted(const bool bSuccess, const int32 ControllerId, FUniqueNetIdPtr UserId, const FOnlineSessionSearchResult& InviteResult);
	bool TryTravelToCurrentSession();

private:
	FOnCreateSessionCompleteDelegate CreateSessionCompleteDelegate;
	FDelegateHandle CreateSessionCompleteDelegateHandle;;
	
	FOnUpdateSessionCompleteDelegate UpdateSessionCompleteDelegate;
	FDelegateHandle UpdateSessionCompleteDelegateHandle;
	
	FOnStartSessionCompleteDelegate StartSessionCompleteDelegate;
	FDelegateHandle StartSessionCompleteDelegateHandle;

	FOnDestroySessionCompleteDelegate DestroySessionCompleteDelegate;
	FDelegateHandle DestroySessionCompleteDelegateHandle;

	FOnFindSessionsCompleteDelegate FindSessionsCompleteDelegate;
	FDelegateHandle FindSessionsCompleteDelegateHandle;
	TSharedPtr<FOnlineSessionSearch> LastSessionSearch;

	FOnJoinSessionCompleteDelegate JoinSessionCompleteDelegate;
	FDelegateHandle JoinSessionCompleteDelegateHandle;

	FOnSessionUserInviteAcceptedDelegate SessionUserInviteAcceptedDelegate;
	FDelegateHandle SessionUserInviteAcceptedDelegateHandle;

	TSharedPtr<FOnlineSessionSettings> LastSessionSettings;
};
