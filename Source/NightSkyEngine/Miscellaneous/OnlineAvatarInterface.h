// Copyright June Rhodes. MIT Licensed.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Texture.h"
#include "OnlineDelegateMacros.h"
#include "OnlineSubsystem.h"

#define ONLINE_AVATAR_INTERFACE_NAME FName(TEXT("Avatar2"))

/**
 * The callback issued when GetAvatar has finished.
 */
DECLARE_DELEGATE_TwoParams(
    FOnGetAvatarComplete,
    bool /* bWasSuccessful */,
    TSoftObjectPtr<UTexture> /* ResultTexture */);

/**
 * The callback issued when GetAvatarUrl has finished.
 */
DECLARE_DELEGATE_TwoParams(FOnGetAvatarUrlComplete, bool /* bWasSuccessful */, FString /* ResultAvatarUrl */);

class IOnlineAvatar
{
    // WARNING: Functions can only be added to the *end* of this interface. Never remove or insert
    // them. Otherwise the virtual function table gets messed up between different binary versions
    // of IOnlineAvatar and breaks calls in subtle ways.

public:
    virtual ~IOnlineAvatar(){};

    /**
     * Fetches the avatar of the target user, falling back to the default texture if the user does not have an avatar
     * set.
     */
    virtual bool GetAvatar(
        const FUniqueNetId &LocalUserId,
        const FUniqueNetId &TargetUserId,
        TSoftObjectPtr<UTexture> DefaultTexture,
        FOnGetAvatarComplete OnComplete = FOnGetAvatarComplete()) = 0;

    /**
     * Fetches the avatar URL of the target user, falling back to the default avatar url if the user does not have an
     * avatar set.
     */
    virtual bool GetAvatarUrl(
        const FUniqueNetId &LocalUserId,
        const FUniqueNetId &TargetUserId,
        FString DefaultAvatarUrl,
        FOnGetAvatarUrlComplete OnComplete = FOnGetAvatarUrlComplete()) = 0;
};

namespace Online
{
/**
 * Returns the IOnlineAvatar interface from an online subsystem, if the online subsystem implements it.
 */
FORCEINLINE TSharedPtr<IOnlineAvatar, ESPMode::ThreadSafe> GetAvatarInterface(IOnlineSubsystem *Subsystem)
{
    if (Subsystem == nullptr)
    {
        return nullptr;
    }

    void *Ptr = (void *)Subsystem->GetNamedInterface(ONLINE_AVATAR_INTERFACE_NAME);
    if (Ptr == nullptr)
    {
        return nullptr;
    }

    TSharedPtr<IOnlineAvatar, ESPMode::ThreadSafe> SharedPtr = *(TSharedPtr<IOnlineAvatar, ESPMode::ThreadSafe> *)Ptr;
    return SharedPtr;
}
} // namespace Online

/*

To implement this interface in your own online subsystem, add a TSharedPtr<IOnlineAvatar, ESPMode::ThreadSafe> field
to your online subsystem class, then override/implement GetNamedInterface to look like the following:

class UObject *FYourSubsystem::GetNamedInterface(FName InterfaceName)
{
    if (InterfaceName.IsEqual(ONLINE_AVATAR_INTERFACE_NAME))
    {
        return (class UObject *)(void *)&this->LobbyImpl;
    }

    return nullptr;
}

It is expected that the return value of GetNamedInterface will be a *pointer* to the TSharedPtr<>
inside your online subsystem instance, not the TSharedPtr itself.

*/