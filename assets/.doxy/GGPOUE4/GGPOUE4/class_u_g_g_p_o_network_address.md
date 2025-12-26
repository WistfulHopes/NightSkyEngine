

# Class UGGPONetworkAddress



[**ClassList**](annotated.md) **>** [**UGGPONetworkAddress**](class_u_g_g_p_o_network_address.md)



[More...](#detailed-description)

* `#include <ggponet.h>`



Inherits the following classes: UObject


































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**GetIpAddress**](#function-getipaddress) (char OutAddress) const<br> |
|  FString | [**GetIpAddressString**](#function-getipaddressstring) () const<br> |
|  int32 | [**GetPort**](#function-getport) () const<br> |
|  bool | [**IsSameAddress**](#function-issameaddress) (const [**UGGPONetworkAddress**](class_u_g_g_p_o_network_address.md) \* Other) const<br> |
|  bool | [**IsValidAddress**](#function-isvalidaddress) () const<br> |
|   | [**UGGPONetworkAddress**](#function-uggponetworkaddress) () <br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**UGGPONetworkAddress**](class_u_g_g_p_o_network_address.md) \* | [**CreateLocalAddress**](#function-createlocaladdress) (UObject \* Outer, const FName Name, int32 LocalPort) <br> |
|  [**UGGPONetworkAddress**](class_u_g_g_p_o_network_address.md) \* | [**CreateNetworkAddress**](#function-createnetworkaddress) (UObject \* Outer, const FName Name, const FString Address) <br> |


























## Detailed Description


A network address object. Composed of an ip address and a port. 


    
## Public Functions Documentation




### function GetIpAddress 

```C++
void UGGPONetworkAddress::GetIpAddress (
    char OutAddress
) const
```



Outputs the ip address array to the passed pointer. 


        

<hr>



### function GetIpAddressString 

```C++
FString UGGPONetworkAddress::GetIpAddressString () const
```



Gets the ip address as a string. 


        

<hr>



### function GetPort 

```C++
int32 UGGPONetworkAddress::GetPort () const
```



Gets the port. 


        

<hr>



### function IsSameAddress 

```C++
bool UGGPONetworkAddress::IsSameAddress (
    const UGGPONetworkAddress * Other
) const
```



Gets the port. 


        

<hr>



### function IsValidAddress 

```C++
bool UGGPONetworkAddress::IsValidAddress () const
```



Returns whether the address is valid. 


        

<hr>



### function UGGPONetworkAddress 

```C++
inline UGGPONetworkAddress::UGGPONetworkAddress () 
```




<hr>
## Public Static Functions Documentation




### function CreateLocalAddress 

```C++
static UGGPONetworkAddress * UGGPONetworkAddress::CreateLocalAddress (
    UObject * Outer,
    const FName Name,
    int32 LocalPort
) 
```



Creates a GGPO local address. 


        

<hr>



### function CreateNetworkAddress 

```C++
static UGGPONetworkAddress * UGGPONetworkAddress::CreateNetworkAddress (
    UObject * Outer,
    const FName Name,
    const FString Address
) 
```



Creates a GGPO network address. 


        

<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/GGPOUE4/Public/include/ggponet.h`

