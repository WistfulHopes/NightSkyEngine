

# Class ConnectionManager



[**ClassList**](annotated.md) **>** [**ConnectionManager**](class_connection_manager.md)



[More...](#detailed-description)

* `#include <connection_manager.h>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**ConnectionManager**](#function-connectionmanager) () <br> |
|  void | [**Log**](#function-log) (const char \* fmt, ...) <br> |
| virtual int | [**RecvFrom**](#function-recvfrom) (char \* buffer, int len, int flags, int \* connection\_id) = 0<br> |
| virtual int | [**ResetManager**](#function-resetmanager) () <br> |
| virtual int | [**SendTo**](#function-sendto) (const char \* buffer, int len, int flags, int connection\_id) = 0<br> |
| virtual std::string | [**ToString**](#function-tostring) (int connection\_id) <br> |
| virtual  | [**~ConnectionManager**](#function-connectionmanager) () <br> |








## Protected Attributes

| Type | Name |
| ---: | :--- |
|  std::map&lt; int, std::shared\_ptr&lt; [**ConnectionInfo**](class_connection_info.md) &gt; &gt; | [**\_connection\_map**](#variable-_connection_map)  <br>_A map of connection IDs and smart pointers to their respective info objects._  |
|  int | [**\_id\_to\_issue**](#variable-_id_to_issue)  <br>_The current ID value to be issued to the next connection added._  |
















## Protected Functions

| Type | Name |
| ---: | :--- |
|  int | [**AddConnection**](#function-addconnection) (std::shared\_ptr&lt; [**ConnectionInfo**](class_connection_info.md) &gt; info) <br> |




## Detailed Description


Abstract class to define a connection manager interface


This is a class whos purpose is to provide an abstraction from underlying network system calls. It must provide a non-blocking upd style send recv interface. When adding a connection it should return a unique int ID for the connection to be referred to by in future interactions with the manager. 


    
## Public Functions Documentation




### function ConnectionManager 

```C++
inline ConnectionManager::ConnectionManager () 
```




<hr>



### function Log 

```C++
void ConnectionManager::Log (
    const char * fmt,
    ...
) 
```




<hr>



### function RecvFrom 

```C++
virtual int ConnectionManager::RecvFrom (
    char * buffer,
    int len,
    int flags,
    int * connection_id
) = 0
```



RecvFrom is a recvfrom upd style interface


This function is expected to function similar to a standard upd socket style recvfrom. Return values are as follows: greater than 0 values indicate data length. 0 indicates a disconnect. -1 indicates no data or some other error. 


        

<hr>



### function ResetManager 

```C++
inline virtual int ConnectionManager::ResetManager () 
```



ResetManager is a reset function to clear the connection\_map


This should be called if there is a need to clear all existing connections without creating a new connection manager. 


        

<hr>



### function SendTo 

```C++
virtual int ConnectionManager::SendTo (
    const char * buffer,
    int len,
    int flags,
    int connection_id
) = 0
```



SendTo is a sendto upd style interface


This function is expected to function similar to a standard upd socket style send. 


        

<hr>



### function ToString 

```C++
virtual std::string ConnectionManager::ToString (
    int connection_id
) 
```



ToString converts relevant information to a string


This function should convert relevant information from the connection info object identified by connection\_id to a string. The default implementation should be valid for most use cases. Overload the ToString function in the derived [**ConnectionInfo**](class_connection_info.md) definition. 


        

<hr>



### function ~ConnectionManager 

```C++
virtual ConnectionManager::~ConnectionManager () 
```




<hr>
## Protected Attributes Documentation




### variable \_connection\_map 

_A map of connection IDs and smart pointers to their respective info objects._ 
```C++
std::map<int, std::shared_ptr<ConnectionInfo> > ConnectionManager::_connection_map;
```




<hr>



### variable \_id\_to\_issue 

_The current ID value to be issued to the next connection added._ 
```C++
int ConnectionManager::_id_to_issue;
```




<hr>
## Protected Functions Documentation




### function AddConnection 

```C++
inline int ConnectionManager::AddConnection (
    std::shared_ptr< ConnectionInfo > info
) 
```



AddConnection adds a connection to the manager and returns the ID.


This function takes in a [**ConnectionInfo**](class_connection_info.md) smartpointer to an object that implicitly must be a defined type that inheriteds from [**ConnectionInfo**](class_connection_info.md). Derived ConnectionManagers should define their own AddConnection functions with args that provide the relevant information for the specific connection desired. This function should then be called to add a derived [**ConnectionInfo**](class_connection_info.md) object to the \_connection\_map and it will return the connection id. Having monotonically increasing IDs is fine for this use case. It is up to the user to correctly manage IDs to ensure they are only used with the [**ConnectionManager**](class_connection_manager.md) that issued them as the same IDs will likely be valid in multiple ConnectionManagers on the same process. 


        

<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/GGPOUE4/Public/include/connection_manager.h`

