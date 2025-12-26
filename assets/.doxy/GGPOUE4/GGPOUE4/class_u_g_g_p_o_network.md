

# Class UGGPONetwork



[**ClassList**](annotated.md) **>** [**UGGPONetwork**](class_u_g_g_p_o_network.md)



[More...](#detailed-description)

* `#include <ggponet.h>`



Inherits the following classes: UObject


































## Public Functions

| Type | Name |
| ---: | :--- |
|  bool | [**AllUniqueAddresses**](#function-alluniqueaddresses) () const<br> |
|  bool | [**AllValidAddresses**](#function-allvalidaddresses) () const<br> |
|  [**UGGPONetworkAddress**](class_u_g_g_p_o_network_address.md) \* | [**GetAddress**](#function-getaddress) (int32 Index) const<br> |
|  int32 | [**GetLocalPort**](#function-getlocalport) () const<br> |
|  int32 | [**GetPlayerIndex**](#function-getplayerindex) () const<br> |
|  int32 | [**NumPlayers**](#function-numplayers) () const<br> |
|   | [**UGGPONetwork**](#function-uggponetwork) () <br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**UGGPONetwork**](class_u_g_g_p_o_network.md) \* | [**CreateNetwork**](#function-createnetwork) (UObject \* Outer, const FName Name, int32 NumPlayers, int32 PlayerIndex, int32 LocalPort, TArray&lt; FString &gt; RemoteAddresses) <br> |


























## Detailed Description


A collection of network addresses. 


    
## Public Functions Documentation




### function AllUniqueAddresses 

```C++
bool UGGPONetwork::AllUniqueAddresses () const
```



Returns whether all addresses are unique. 


        

<hr>



### function AllValidAddresses 

```C++
bool UGGPONetwork::AllValidAddresses () const
```



Returns whether all addresses are valid. 


        

<hr>



### function GetAddress 

```C++
UGGPONetworkAddress * UGGPONetwork::GetAddress (
    int32 Index
) const
```



Gets one network address. 


        

<hr>



### function GetLocalPort 

```C++
int32 UGGPONetwork::GetLocalPort () const
```



Gets the local port. 


        

<hr>



### function GetPlayerIndex 

```C++
int32 UGGPONetwork::GetPlayerIndex () const
```



Gets the local player index. 


        

<hr>



### function NumPlayers 

```C++
int32 UGGPONetwork::NumPlayers () const
```



Gets the total number of players on the network. 


        

<hr>



### function UGGPONetwork 

```C++
inline UGGPONetwork::UGGPONetwork () 
```




<hr>
## Public Static Functions Documentation




### function CreateNetwork 

```C++
static UGGPONetwork * UGGPONetwork::CreateNetwork (
    UObject * Outer,
    const FName Name,
    int32 NumPlayers,
    int32 PlayerIndex,
    int32 LocalPort,
    TArray< FString > RemoteAddresses
) 
```



Creates a collection of network addresses. 


        

<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/GGPOUE4/Public/include/ggponet.h`

