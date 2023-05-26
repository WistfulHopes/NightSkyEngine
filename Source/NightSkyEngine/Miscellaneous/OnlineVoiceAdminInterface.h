// Copyright June Rhodes. MIT Licensed.

#pragma once

#include "Containers/UnrealString.h"
#include "CoreMinimal.h"
#include "OnlineDelegateMacros.h"
#include "OnlineError.h"
#include "OnlineSubsystem.h"

#define ONLINE_VOICE_ADMIN_INTERFACE_NAME FName(TEXT("VoiceAdmin"))

/**
 * Represents credentials that a target user can use to connect to a voice channel.
 */
struct FVoiceAdminChannelCredentials
{
public:
    /** The user that this credential is for. */
    TSharedPtr<const FUniqueNetId> TargetUserId;

    /** The player name that the target user should pass to IVoiceChatUser::Login. */
    FString PlayerName;

    /** The channel credentials that the target user should pass to IVoiceChatUser::Login. */
    FString ChannelCredentials;
};

DECLARE_DELEGATE_ThreeParams(
    FOnVoiceAdminCreateChannelCredentialsComplete,
    const FOnlineError & /* Result */,
    const FUniqueNetId & /* LocalUserId */,
    const TArray<FVoiceAdminChannelCredentials> & /* Credentials */);
DECLARE_DELEGATE_ThreeParams(
    FOnVoiceAdminKickParticipantComplete,
    const FOnlineError & /* Result */,
    const FUniqueNetId & /* LocalUserId */,
    const FUniqueNetId & /* TargetUserId */);
DECLARE_DELEGATE_FourParams(
    FOnVoiceAdminSetParticipantHardMuteComplete,
    const FOnlineError & /* Result */,
    const FUniqueNetId & /* LocalUserId */,
    const FUniqueNetId & /* TargetUserId */,
    bool /* bIsNowMuted */);

/**
 * Allows dedicated servers to issue credentials for voice chat. After issuance, the credentials need to be sent as RPCs
 * to clients, where the clients will then use the credentials with IVoiceChatUser::Login.
 */
class IOnlineVoiceAdmin
{
    // WARNING: Functions can only be added to the *end* of this interface. Never remove or insert
    // them. Otherwise the virtual function table gets messed up between different binary versions
    // of IOnlineVoiceAdmin and breaks calls in subtle ways.

public:
    virtual ~IOnlineVoiceAdmin(){};

    /**
     * Creates credentials that a set of users can use to connect to the specified voice channel. You don't need to
     * explicitly create channels; instead you just issue credentials for whatever channel name you want to pick, and
     * clients will be able to connect to it using the specified credentials.
     */
    virtual bool CreateChannelCredentials(
        const FUniqueNetId &LocalUserId,
        const FString &ChannelName,
        const TArray<TSharedRef<const FUniqueNetId>> &TargetUserIds,
        FOnVoiceAdminCreateChannelCredentialsComplete OnComplete = FOnVoiceAdminCreateChannelCredentialsComplete()) = 0;

    /**
     * Forcibly kicks a target user from a voice channel. They will also not be able to use previously issued
     * credentials to reconnect to the voice channel.
     */
    virtual bool KickParticipant(
        const FUniqueNetId &LocalUserId,
        const FString &ChannelName,
        const FUniqueNetId &TargetUserId,
        FOnVoiceAdminKickParticipantComplete OnComplete = FOnVoiceAdminKickParticipantComplete()) = 0;

    /**
     * Sets whether a participant in a voice channel is "hard muted". When a participant is hard muted their input audio
     * will never be sent to other participants in the voice channel.
     */
    virtual bool SetParticipantHardMute(
        const FUniqueNetId &LocalUserId,
        const FString &ChannelName,
        const FUniqueNetId &TargetUserId,
        bool bMuted,
        FOnVoiceAdminSetParticipantHardMuteComplete OnComplete = FOnVoiceAdminSetParticipantHardMuteComplete()) = 0;
};

namespace Online
{
/**
 * Returns the IOnlineVoiceAdmin interface from an online subsystem, if the online subsystem implements it.
 */
FORCEINLINE TSharedPtr<IOnlineVoiceAdmin, ESPMode::ThreadSafe> GetVoiceAdminInterface(IOnlineSubsystem *Subsystem)
{
    if (Subsystem == nullptr)
    {
        return nullptr;
    }

    void *Ptr = (void *)Subsystem->GetNamedInterface(ONLINE_VOICE_ADMIN_INTERFACE_NAME);
    if (Ptr == nullptr)
    {
        return nullptr;
    }

    TSharedPtr<IOnlineVoiceAdmin, ESPMode::ThreadSafe> SharedPtr =
        *(TSharedPtr<IOnlineVoiceAdmin, ESPMode::ThreadSafe> *)Ptr;
    return SharedPtr;
}
} // namespace Online

/*

To implement this interface in your own online subsystem, add a TSharedPtr<IOnlineVoiceAdmin, ESPMode::ThreadSafe> field
to your online subsystem class, then override/implement GetNamedInterface to look like the following:

class UObject *FYourSubsystem::GetNamedInterface(FName InterfaceName)
{
    if (InterfaceName.IsEqual(ONLINE_VOICE_ADMIN_INTERFACE_NAME))
    {
        return (class UObject *)(void *)&this->VoiceAdminImpl;
    }

    return nullptr;
}

It is expected that the return value of GetNamedInterface will be a *pointer* to the TSharedPtr<>
inside your online subsystem instance, not the TSharedPtr itself.

*/