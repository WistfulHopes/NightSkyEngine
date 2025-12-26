

# Class RpcConnectionManager



[**ClassList**](annotated.md) **>** [**RpcConnectionManager**](class_rpc_connection_manager.md)








Inherits the following classes: ConnectionManager


















## Public Attributes

| Type | Name |
| ---: | :--- |
|  int | [**playerIndex**](#variable-playerindex)  <br> |
|  TDoubleLinkedList&lt; TArray&lt; int8 &gt; &gt; | [**receiveSchedule**](#variable-receiveschedule)  <br> |
|  TDoubleLinkedList&lt; TArray&lt; int8 &gt; &gt; | [**sendSchedule**](#variable-sendschedule)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
| virtual int | [**RecvFrom**](#function-recvfrom) (char \* buffer, int len, int flags, int \* connection\_id) <br> |
|   | [**RpcConnectionManager**](#function-rpcconnectionmanager) () <br> |
| virtual int | [**SendTo**](#function-sendto) (const char \* buffer, int len, int flags, int connection\_id) <br> |
| virtual  | [**~RpcConnectionManager**](#function-rpcconnectionmanager) () override<br> |




























## Public Attributes Documentation




### variable playerIndex 

```C++
int RpcConnectionManager::playerIndex;
```




<hr>



### variable receiveSchedule 

```C++
TDoubleLinkedList<TArray<int8> > RpcConnectionManager::receiveSchedule;
```




<hr>



### variable sendSchedule 

```C++
TDoubleLinkedList<TArray<int8> > RpcConnectionManager::sendSchedule;
```




<hr>
## Public Functions Documentation




### function RecvFrom 

```C++
virtual int RpcConnectionManager::RecvFrom (
    char * buffer,
    int len,
    int flags,
    int * connection_id
) 
```




<hr>



### function RpcConnectionManager 

```C++
RpcConnectionManager::RpcConnectionManager () 
```




<hr>



### function SendTo 

```C++
virtual int RpcConnectionManager::SendTo (
    const char * buffer,
    int len,
    int flags,
    int connection_id
) 
```




<hr>



### function ~RpcConnectionManager 

```C++
virtual RpcConnectionManager::~RpcConnectionManager () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/NightSkyEngine/Network/RpcConnectionManager.h`

