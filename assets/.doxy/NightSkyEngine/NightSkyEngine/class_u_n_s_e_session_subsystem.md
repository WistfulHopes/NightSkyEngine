

# Class UNSESessionSubsystem



[**ClassList**](annotated.md) **>** [**UNSESessionSubsystem**](class_u_n_s_e_session_subsystem.md)








Inherits the following classes: UGameInstanceSubsystem


















## Public Attributes

| Type | Name |
| ---: | :--- |
|  FDelegateHandle | [**LoginDelegateHandle**](#variable-logindelegatehandle)  <br> |
|  FNSEOnCreateSessionComplete | [**OnCreateSessionCompleteDelegate**](#variable-oncreatesessioncompletedelegate)  <br> |
|  FNSEOnDestroySessionComplete | [**OnDestroySessionCompleteEvent**](#variable-ondestroysessioncompleteevent)  <br> |
|  FNSEOnFindSessionsComplete | [**OnFindSessionsCompleteEvent**](#variable-onfindsessionscompleteevent)  <br> |
|  FNSEOnJoinSessionComplete | [**OnJoinGameSessionCompleteEvent**](#variable-onjoingamesessioncompleteevent)  <br> |
|  FNSEOnStartSessionComplete | [**OnStartSessionCompleteEvent**](#variable-onstartsessioncompleteevent)  <br> |
|  FNSEOnUpdateSessionComplete | [**OnUpdateSessionCompleteEvent**](#variable-onupdatesessioncompleteevent)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**CreateSession**](#function-createsession) (int32 NumPublicConnections, bool bIsLANMatch) <br> |
|  void | [**DestroySession**](#function-destroysession) () <br> |
|  void | [**FindSessions**](#function-findsessions) (int32 MaxSearchResults, bool IsLANQuery) <br> |
|  bool | [**IsLoggedIn**](#function-isloggedin) () const<br> |
|  void | [**JoinGameSession**](#function-joingamesession) (const FOnlineSessionSearchResult & SessionResult) <br> |
|  void | [**JoinGameSession\_BP**](#function-joingamesession_bp) ([**FNSESessionInfo**](struct_f_n_s_e_session_info.md) Info) <br> |
|  void | [**Login**](#function-login) () <br> |
|  void | [**StartSession**](#function-startsession) () <br> |
|   | [**UNSESessionSubsystem**](#function-unsesessionsubsystem) () <br> |
|  void | [**UpdateSession**](#function-updatesession) () <br> |
























## Protected Functions

| Type | Name |
| ---: | :--- |
|  void | [**OnCreateSessionComplete**](#function-oncreatesessioncomplete) (FName SessionName, bool bSuccess) <br> |
|  void | [**OnDestroySessionComplete**](#function-ondestroysessioncomplete) (FName SessionName, bool bSuccess) <br> |
|  void | [**OnFindSessionsComplete**](#function-onfindsessionscomplete) (bool bSuccess) <br> |
|  void | [**OnJoinSessionComplete**](#function-onjoinsessioncomplete) (FName SessionName, EOnJoinSessionCompleteResult::Type Result) <br> |
|  void | [**OnLoginCompleted**](#function-onlogincompleted) (int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId & UserId, const FString & Error) <br> |
|  void | [**OnSessionInviteAccepted**](#function-onsessioninviteaccepted) (const bool bSuccess, const int32 ControllerId, FUniqueNetIdPtr UserId, const FOnlineSessionSearchResult & InviteResult) <br> |
|  void | [**OnStartSessionComplete**](#function-onstartsessioncomplete) (FName SessionName, bool bSuccess) <br> |
|  void | [**OnUpdateSessionComplete**](#function-onupdatesessioncomplete) (FName SessionName, bool bSuccess) <br> |
|  bool | [**TryTravelToCurrentSession**](#function-trytraveltocurrentsession) () <br> |




## Public Attributes Documentation




### variable LoginDelegateHandle 

```C++
FDelegateHandle UNSESessionSubsystem::LoginDelegateHandle;
```




<hr>



### variable OnCreateSessionCompleteDelegate 

```C++
FNSEOnCreateSessionComplete UNSESessionSubsystem::OnCreateSessionCompleteDelegate;
```




<hr>



### variable OnDestroySessionCompleteEvent 

```C++
FNSEOnDestroySessionComplete UNSESessionSubsystem::OnDestroySessionCompleteEvent;
```




<hr>



### variable OnFindSessionsCompleteEvent 

```C++
FNSEOnFindSessionsComplete UNSESessionSubsystem::OnFindSessionsCompleteEvent;
```




<hr>



### variable OnJoinGameSessionCompleteEvent 

```C++
FNSEOnJoinSessionComplete UNSESessionSubsystem::OnJoinGameSessionCompleteEvent;
```




<hr>



### variable OnStartSessionCompleteEvent 

```C++
FNSEOnStartSessionComplete UNSESessionSubsystem::OnStartSessionCompleteEvent;
```




<hr>



### variable OnUpdateSessionCompleteEvent 

```C++
FNSEOnUpdateSessionComplete UNSESessionSubsystem::OnUpdateSessionCompleteEvent;
```




<hr>
## Public Functions Documentation




### function CreateSession 

```C++
void UNSESessionSubsystem::CreateSession (
    int32 NumPublicConnections,
    bool bIsLANMatch
) 
```




<hr>



### function DestroySession 

```C++
void UNSESessionSubsystem::DestroySession () 
```




<hr>



### function FindSessions 

```C++
void UNSESessionSubsystem::FindSessions (
    int32 MaxSearchResults,
    bool IsLANQuery
) 
```




<hr>



### function IsLoggedIn 

```C++
bool UNSESessionSubsystem::IsLoggedIn () const
```




<hr>



### function JoinGameSession 

```C++
void UNSESessionSubsystem::JoinGameSession (
    const FOnlineSessionSearchResult & SessionResult
) 
```




<hr>



### function JoinGameSession\_BP 

```C++
void UNSESessionSubsystem::JoinGameSession_BP (
    FNSESessionInfo Info
) 
```




<hr>



### function Login 

```C++
void UNSESessionSubsystem::Login () 
```




<hr>



### function StartSession 

```C++
void UNSESessionSubsystem::StartSession () 
```




<hr>



### function UNSESessionSubsystem 

```C++
UNSESessionSubsystem::UNSESessionSubsystem () 
```




<hr>



### function UpdateSession 

```C++
void UNSESessionSubsystem::UpdateSession () 
```




<hr>
## Protected Functions Documentation




### function OnCreateSessionComplete 

```C++
void UNSESessionSubsystem::OnCreateSessionComplete (
    FName SessionName,
    bool bSuccess
) 
```




<hr>



### function OnDestroySessionComplete 

```C++
void UNSESessionSubsystem::OnDestroySessionComplete (
    FName SessionName,
    bool bSuccess
) 
```




<hr>



### function OnFindSessionsComplete 

```C++
void UNSESessionSubsystem::OnFindSessionsComplete (
    bool bSuccess
) 
```




<hr>



### function OnJoinSessionComplete 

```C++
void UNSESessionSubsystem::OnJoinSessionComplete (
    FName SessionName,
    EOnJoinSessionCompleteResult::Type Result
) 
```




<hr>



### function OnLoginCompleted 

```C++
void UNSESessionSubsystem::OnLoginCompleted (
    int32 LocalUserNum,
    bool bWasSuccessful,
    const FUniqueNetId & UserId,
    const FString & Error
) 
```




<hr>



### function OnSessionInviteAccepted 

```C++
void UNSESessionSubsystem::OnSessionInviteAccepted (
    const bool bSuccess,
    const int32 ControllerId,
    FUniqueNetIdPtr UserId,
    const FOnlineSessionSearchResult & InviteResult
) 
```




<hr>



### function OnStartSessionComplete 

```C++
void UNSESessionSubsystem::OnStartSessionComplete (
    FName SessionName,
    bool bSuccess
) 
```




<hr>



### function OnUpdateSessionComplete 

```C++
void UNSESessionSubsystem::OnUpdateSessionComplete (
    FName SessionName,
    bool bSuccess
) 
```




<hr>



### function TryTravelToCurrentSession 

```C++
bool UNSESessionSubsystem::TryTravelToCurrentSession () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/NightSkyEngine/Network/NSESessionSubsystem.h`

