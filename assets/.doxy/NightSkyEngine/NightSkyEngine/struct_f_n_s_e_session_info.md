

# Struct FNSESessionInfo



[**ClassList**](annotated.md) **>** [**FNSESessionInfo**](struct_f_n_s_e_session_info.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  int32 | [**NumOpenPrivateConnections**](#variable-numopenprivateconnections)  <br> |
|  int32 | [**NumOpenPublicConnections**](#variable-numopenpublicconnections)  <br> |
|  FString | [**OwningUserName**](#variable-owningusername)  <br> |
|  FOnlineSessionSearchResult | [**SessionSearchResult**](#variable-sessionsearchresult)   = `{}`<br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**FNSESessionInfo**](#function-fnsesessioninfo-12) () = default<br> |
|   | [**FNSESessionInfo**](#function-fnsesessioninfo-22) (const FOnlineSessionSearchResult & Result, const FString & Name, int32 OpenPrivate, int32 OpenPublic) <br> |




























## Public Attributes Documentation




### variable NumOpenPrivateConnections 

```C++
int32 FNSESessionInfo::NumOpenPrivateConnections;
```



The number of private connections that are available (read only) 


        

<hr>



### variable NumOpenPublicConnections 

```C++
int32 FNSESessionInfo::NumOpenPublicConnections;
```



The number of publicly available connections that are available (read only) 


        

<hr>



### variable OwningUserName 

```C++
FString FNSESessionInfo::OwningUserName;
```



Owner name of the session 


        

<hr>



### variable SessionSearchResult 

```C++
FOnlineSessionSearchResult FNSESessionInfo::SessionSearchResult;
```



Session 


        

<hr>
## Public Functions Documentation




### function FNSESessionInfo [1/2]

```C++
FNSESessionInfo::FNSESessionInfo () = default
```




<hr>



### function FNSESessionInfo [2/2]

```C++
FNSESessionInfo::FNSESessionInfo (
    const FOnlineSessionSearchResult & Result,
    const FString & Name,
    int32 OpenPrivate,
    int32 OpenPublic
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/NightSkyEngine/Network/NSESessionSubsystem.h`

