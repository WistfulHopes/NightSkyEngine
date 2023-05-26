// Copyright June Rhodes. MIT Licensed.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/OnlinePartyInterface.h"
#include "OnlineDelegateMacros.h"
#include "OnlineSubsystem.h"

#define ONLINE_LOBBY_INTERFACE_NAME FName(TEXT("Lobby2"))

/**
 * The lobby interface uses the party ID implementation for lobby IDs, as parties
 * will often be implemented on top of a more generic lobbies API.
 */
typedef FOnlinePartyId FOnlineLobbyId;

/**
 * Raised when the lobby data is updated. Should be fired for all members, including
 * the host that updated the lobby data.
 */
DECLARE_MULTICAST_DELEGATE_TwoParams(
    FOnLobbyUpdate,
    const FUniqueNetId & /* UserId */,
    const FOnlineLobbyId & /* LobbyId */);
typedef FOnLobbyUpdate::FDelegate FOnLobbyUpdateDelegate;

/**
 * Raised when the lobby is deleted via DeleteLobby. Should be fired for all members,
 * including the host that deleted the lobby. Members should not receive an OnMemberDisconnect
 * event when the lobby is deleted - they should just receive OnLobbyDelete instead.
 */
DECLARE_MULTICAST_DELEGATE_TwoParams(
    FOnLobbyDelete,
    const FUniqueNetId & /* UserId */,
    const FOnlineLobbyId & /* LobbyId */);
typedef FOnLobbyDelete::FDelegate FOnLobbyDeleteDelegate;

/**
 * Raised when a member connects to a lobby. Should be fired for all members, except for the
 * member that joined the lobby.
 */
DECLARE_MULTICAST_DELEGATE_ThreeParams(
    FOnMemberConnect,
    const FUniqueNetId & /* UserId */,
    const FOnlineLobbyId & /* LobbyId */,
    const FUniqueNetId & /* MemberId */);
typedef FOnMemberConnect::FDelegate FOnMemberConnectDelegate;

/**
 * Raised when a member's data is updated. Should be fired for all members, including the
 * member who updated their own data.
 */
DECLARE_MULTICAST_DELEGATE_ThreeParams(
    FOnMemberUpdate,
    const FUniqueNetId & /* UserId */,
    const FOnlineLobbyId & /* LobbyId */,
    const FUniqueNetId & /* MemberId */);
typedef FOnMemberUpdate::FDelegate FOnMemberUpdateDelegate;

#define ONLINE_INTERFACES_LOBBY_HAS_KICKED_PARAMETER 1

/**
 * Raised when a member disconnects from a lobby. Should be fired for all members, including
 * the member who disconnected, regardless of if they disconnected via DisconnectLobby or if
 * they were disconnected by some other mechanism such as a network timeout. The only exception is
 * if the lobby is deleted by the host; in that case, members should receive OnLobbyDelete instead.
 *
 * bWasKicked should be true if the host intentionally removed the member from the lobby.
 */
DECLARE_MULTICAST_DELEGATE_FourParams(
    FOnMemberDisconnect,
    const FUniqueNetId & /* UserId */,
    const FOnlineLobbyId & /* LobbyId */,
    const FUniqueNetId & /* MemberId */,
    bool /* bWasKicked */);
typedef FOnMemberDisconnect::FDelegate FOnMemberDisconnectDelegate;

DECLARE_DELEGATE_TwoParams(
    FOnLobbyOperationComplete,
    const FOnlineError & /* Error */,
    const FUniqueNetId & /* UserId */);
DECLARE_DELEGATE_ThreeParams(
    FOnLobbyCreateOrConnectComplete,
    const FOnlineError & /* Error */,
    const FUniqueNetId & /* UserId */,
    const TSharedPtr<class FOnlineLobby> & /* Lobby */);
DECLARE_DELEGATE_ThreeParams(
    FOnLobbySearchComplete,
    const FOnlineError & /* Error */,
    const FUniqueNetId & /* UserId */,
    const TArray<TSharedRef<const FOnlineLobbyId>> & /* Lobbies */);

/**
 * Represents an online lobby that was created or updated.
 */
class FOnlineLobby : public TSharedFromThis<FOnlineLobby>
{
protected:
    FOnlineLobby(){};

public:
    UE_NONCOPYABLE(FOnlineLobby);
    virtual ~FOnlineLobby(){};

    TSharedPtr<const FOnlineLobbyId> Id;
    TSharedPtr<const FUniqueNetId> OwnerId;
};

/**
 * Represents a transaction on a lobby. Implementations must subclass this and return
 * an instance of their subclass from IOnlineLobby::MakeCreateLobbyTransaction and
 * IOnlineLobby::MakeUpdateLobbyTransaction.
 */
class FOnlineLobbyTransaction : public TSharedFromThis<FOnlineLobbyTransaction>
{
protected:
    FOnlineLobbyTransaction(){};

public:
    UE_NONCOPYABLE(FOnlineLobbyTransaction);
    virtual ~FOnlineLobbyTransaction(){};

    /** Metadata to set for this lobby in this transaction. */
    TMap<FString, FVariantData> SetMetadata;

    /** Metadata keys to delete for this lobby in this transaction. */
    TArray<FString> DeleteMetadata;

    /** If this lobby is locked (prevents new members from joining). */
    TOptional<bool> Locked;

    /** The maximum number of members in this lobby. */
    TOptional<uint32> Capacity;

    /** The maximum number of members in this lobby. */
    TOptional<bool> Public;
};

/**
 * Represents a transaction on a lobby member. Implementations must subclass this and return
 * an instance of their subclass from IOnlineLobby::MakeUpdateLobbyMemberTransaction.
 */
class FOnlineLobbyMemberTransaction : public TSharedFromThis<FOnlineLobbyMemberTransaction>
{
protected:
    FOnlineLobbyMemberTransaction(){};

public:
    UE_NONCOPYABLE(FOnlineLobbyMemberTransaction);
    virtual ~FOnlineLobbyMemberTransaction(){};

    /** Metadata to set for this lobby member in this transaction. */
    TMap<FString, FVariantData> SetMetadata;

    /** Metadata keys to delete for this lobby member in this transaction. */
    TArray<FString> DeleteMetadata;
};

enum class EOnlineLobbySearchQueryFilterComparator
{
    Equal = 0,
    NotEqual,
    LessThan,
    LessThanOrEqual,
    GreaterThan,
    GreaterThanOrEqual,
    Distance,
};

/**
 * Represents a search query filter. Implementations are *not* expected to subclass this.
 */
class FOnlineLobbySearchQueryFilter
{
public:
    virtual ~FOnlineLobbySearchQueryFilter(){};

    FOnlineLobbySearchQueryFilter(
        const FString &InKey,
        const FVariantData &InValue,
        EOnlineLobbySearchQueryFilterComparator InComparison)
        : Key(InKey)
        , Value(InValue)
        , Comparison(InComparison){};
    FOnlineLobbySearchQueryFilter(const FOnlineLobbySearchQueryFilter &Other)
        : Key(Other.Key)
        , Value(Other.Value)
        , Comparison(Other.Comparison){};

    FString Key;
    FVariantData Value;
    EOnlineLobbySearchQueryFilterComparator Comparison;
};

/**
 * Represents a search query. Implementations are *not* expected to subclass this.
 */
class FOnlineLobbySearchQuery
{
public:
    FOnlineLobbySearchQuery(){};
    virtual ~FOnlineLobbySearchQuery(){};

    /* Filters to apply in this search query. */
    TArray<FOnlineLobbySearchQueryFilter> Filters;

    /* Limit on the number of results to return. */
    TOptional<uint32> Limit;
};

class IOnlineLobby
{
    // WARNING: Functions can only be added to the *end* of this interface. Never remove or insert
    // them. Otherwise the virtual function table gets messed up between different binary versions
    // of IOnlineLobby and breaks calls in subtle ways.

public:
    virtual ~IOnlineLobby(){};

    DEFINE_ONLINE_DELEGATE_TWO_PARAM(
        OnLobbyUpdate,
        const FUniqueNetId & /* UserId */,
        const FOnlineLobbyId & /* LobbyId */);
    DEFINE_ONLINE_DELEGATE_TWO_PARAM(
        OnLobbyDelete,
        const FUniqueNetId & /* UserId */,
        const FOnlineLobbyId & /* LobbyId */);
    DEFINE_ONLINE_DELEGATE_THREE_PARAM(
        OnMemberConnect,
        const FUniqueNetId & /* UserId */,
        const FOnlineLobbyId & /* LobbyId */,
        const FUniqueNetId & /* MemberId */);
    DEFINE_ONLINE_DELEGATE_THREE_PARAM(
        OnMemberUpdate,
        const FUniqueNetId & /* UserId */,
        const FOnlineLobbyId & /* LobbyId */,
        const FUniqueNetId & /* MemberId */);
    DEFINE_ONLINE_DELEGATE_FOUR_PARAM(
        OnMemberDisconnect,
        const FUniqueNetId & /* UserId */,
        const FOnlineLobbyId & /* LobbyId */,
        const FUniqueNetId & /* MemberId */,
        bool /* bWasKicked */);

    virtual FDateTime GetUtcNow() = 0;

    virtual TSharedPtr<FOnlineLobbyTransaction> MakeCreateLobbyTransaction(const FUniqueNetId &UserId) = 0;
    virtual TSharedPtr<FOnlineLobbyTransaction> MakeUpdateLobbyTransaction(
        const FUniqueNetId &UserId,
        const FOnlineLobbyId &LobbyId) = 0;
    virtual TSharedPtr<FOnlineLobbyMemberTransaction> MakeUpdateLobbyMemberTransaction(
        const FUniqueNetId &UserId,
        const FOnlineLobbyId &LobbyId,
        const FUniqueNetId &MemberId) = 0;

    virtual bool CreateLobby(
        const FUniqueNetId &UserId,
        const FOnlineLobbyTransaction &Transaction,
        FOnLobbyCreateOrConnectComplete OnComplete = FOnLobbyCreateOrConnectComplete()) = 0;
    virtual bool UpdateLobby(
        const FUniqueNetId &UserId,
        const FOnlineLobbyId &LobbyId,
        const FOnlineLobbyTransaction &Transaction,
        FOnLobbyOperationComplete OnComplete = FOnLobbyOperationComplete()) = 0;
    virtual bool DeleteLobby(
        const FUniqueNetId &UserId,
        const FOnlineLobbyId &LobbyId,
        FOnLobbyOperationComplete OnComplete = FOnLobbyOperationComplete()) = 0;

    virtual bool ConnectLobby(
        const FUniqueNetId &UserId,
        const FOnlineLobbyId &LobbyId,
        FOnLobbyCreateOrConnectComplete OnComplete = FOnLobbyCreateOrConnectComplete()) = 0;
    virtual bool DisconnectLobby(
        const FUniqueNetId &UserId,
        const FOnlineLobbyId &LobbyId,
        FOnLobbyOperationComplete OnComplete = FOnLobbyOperationComplete()) = 0;

    virtual bool UpdateMemberSelf(
        const FUniqueNetId &UserId,
        const FOnlineLobbyId &LobbyId,
        const FOnlineLobbyMemberTransaction &Transaction,
        FOnLobbyOperationComplete OnComplete = FOnLobbyOperationComplete()) = 0;

    virtual bool GetMemberCount(const FUniqueNetId &UserId, const FOnlineLobbyId &LobbyId, int32 &OutMemberCount) = 0;
    virtual bool GetMemberUserId(
        const FUniqueNetId &UserId,
        const FOnlineLobbyId &LobbyId,
        int32 MemberIndex,
        TSharedPtr<const FUniqueNetId> &OutMemberId) = 0;

    virtual bool GetMemberMetadataValue(
        const FUniqueNetId &UserId,
        const FOnlineLobbyId &LobbyId,
        const FUniqueNetId &MemberId,
        const FString &MetadataKey,
        FVariantData &OutMetadataValue) = 0;

    virtual bool Search(
        const FUniqueNetId &UserId,
        const FOnlineLobbySearchQuery &Query,
        FOnLobbySearchComplete OnComplete = FOnLobbySearchComplete()) = 0;

    virtual bool GetLobbyMetadataValue(
        const FUniqueNetId &UserId,
        const FOnlineLobbyId &LobbyId,
        const FString &MetadataKey,
        FVariantData &OutMetadataValue) = 0;

    /**
     * Returns the FOnlineLobbyId instance from a serialized lobby ID. Lobby IDs are serialized by calling
     * FOnlineLobbyId::ToString(), so you should ensure that you can convert ToString() back into the full lobby value
     * through this function.
     */
    virtual TSharedPtr<FOnlineLobbyId> ParseSerializedLobbyId(const FString &InLobbyId) = 0;

    virtual bool KickMember(
        const FUniqueNetId &UserId,
        const FOnlineLobbyId &LobbyId,
        const FUniqueNetId &MemberId,
        // NOLINTNEXTLINE(performance-unnecessary-value-param)
        FOnLobbyOperationComplete OnComplete = FOnLobbyOperationComplete())
    {
        return false;
    }
};

namespace Online
{
/**
 * Returns the IOnlineLobby interface from an online subsystem, if the online subsystem implements it.
 */
FORCEINLINE TSharedPtr<IOnlineLobby, ESPMode::ThreadSafe> GetLobbyInterface(IOnlineSubsystem *Subsystem)
{
    if (Subsystem == nullptr)
    {
        return nullptr;
    }

    void *Ptr = (void *)Subsystem->GetNamedInterface(ONLINE_LOBBY_INTERFACE_NAME);
    if (Ptr == nullptr)
    {
        return nullptr;
    }

    TSharedPtr<IOnlineLobby, ESPMode::ThreadSafe> SharedPtr = *(TSharedPtr<IOnlineLobby, ESPMode::ThreadSafe> *)Ptr;
    return SharedPtr;
}
} // namespace Online

/*

To implement this interface in your own online subsystem, add a TSharedPtr<IOnlineLobby, ESPMode::ThreadSafe> field
to your online subsystem class, then override/implement GetNamedInterface to look like the following:

class UObject *FYourSubsystem::GetNamedInterface(FName InterfaceName)
{
    if (InterfaceName.IsEqual(ONLINE_LOBBY_INTERFACE_NAME))
    {
        return (class UObject *)(void *)&this->LobbyImpl;
    }

    return nullptr;
}

It is expected that the return value of GetNamedInterface will be a *pointer* to the TSharedPtr<>
inside your online subsystem instance, not the TSharedPtr itself.

*/
