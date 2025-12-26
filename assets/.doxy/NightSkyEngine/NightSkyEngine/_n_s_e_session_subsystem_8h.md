

# File NSESessionSubsystem.h



[**FileList**](files.md) **>** [**Network**](dir_261b7ff0e57c151ad26fd5c163777bbe.md) **>** [**NSESessionSubsystem.h**](_n_s_e_session_subsystem_8h.md)

[Go to the source code of this file](_n_s_e_session_subsystem_8h_source.md)



* `#include "CoreMinimal.h"`
* `#include "OnlineSessionSettings.h"`
* `#include "Subsystems/GameInstanceSubsystem.h"`
* `#include "Interfaces/OnlineSessionInterface.h"`
* `#include "NSESessionSubsystem.generated.h"`















## Classes

| Type | Name |
| ---: | :--- |
| struct | [**FNSESessionInfo**](struct_f_n_s_e_session_info.md) <br> |
| class | [**UNSESessionSubsystem**](class_u_n_s_e_session_subsystem.md) <br> |






















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**DECLARE\_DYNAMIC\_MULTICAST\_DELEGATE\_OneParam**](#function-declare_dynamic_multicast_delegate_oneparam) (FNSEOnCreateSessionComplete, bool, bSuccess) <br> |
|   | [**DECLARE\_DYNAMIC\_MULTICAST\_DELEGATE\_OneParam**](#function-declare_dynamic_multicast_delegate_oneparam) (FNSEOnUpdateSessionComplete, bool, bSuccess) <br> |
|   | [**DECLARE\_DYNAMIC\_MULTICAST\_DELEGATE\_OneParam**](#function-declare_dynamic_multicast_delegate_oneparam) (FNSEOnStartSessionComplete, bool, bSuccess) <br> |
|   | [**DECLARE\_DYNAMIC\_MULTICAST\_DELEGATE\_OneParam**](#function-declare_dynamic_multicast_delegate_oneparam) (FNSEOnDestroySessionComplete, bool, bSuccess) <br> |
|   | [**DECLARE\_DYNAMIC\_MULTICAST\_DELEGATE\_TwoParams**](#function-declare_dynamic_multicast_delegate_twoparams) (FNSEOnFindSessionsComplete, const TArray&lt; [**FNSESessionInfo**](struct_f_n_s_e_session_info.md) &gt; &, SessionResults, bool, bSuccess) <br> |
|   | [**DECLARE\_MULTICAST\_DELEGATE\_OneParam**](#function-declare_multicast_delegate_oneparam) (FNSEOnJoinSessionComplete, EOnJoinSessionCompleteResult::Type Result) <br> |




























## Public Functions Documentation




### function DECLARE\_DYNAMIC\_MULTICAST\_DELEGATE\_OneParam 

```C++
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam (
    FNSEOnCreateSessionComplete,
    bool,
    bSuccess
) 
```




<hr>



### function DECLARE\_DYNAMIC\_MULTICAST\_DELEGATE\_OneParam 

```C++
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam (
    FNSEOnUpdateSessionComplete,
    bool,
    bSuccess
) 
```




<hr>



### function DECLARE\_DYNAMIC\_MULTICAST\_DELEGATE\_OneParam 

```C++
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam (
    FNSEOnStartSessionComplete,
    bool,
    bSuccess
) 
```




<hr>



### function DECLARE\_DYNAMIC\_MULTICAST\_DELEGATE\_OneParam 

```C++
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam (
    FNSEOnDestroySessionComplete,
    bool,
    bSuccess
) 
```




<hr>



### function DECLARE\_DYNAMIC\_MULTICAST\_DELEGATE\_TwoParams 

```C++
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams (
    FNSEOnFindSessionsComplete,
    const TArray< FNSESessionInfo > &,
    SessionResults,
    bool,
    bSuccess
) 
```




<hr>



### function DECLARE\_MULTICAST\_DELEGATE\_OneParam 

```C++
DECLARE_MULTICAST_DELEGATE_OneParam (
    FNSEOnJoinSessionComplete,
    EOnJoinSessionCompleteResult::Type Result
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/NightSkyEngine/Network/NSESessionSubsystem.h`

