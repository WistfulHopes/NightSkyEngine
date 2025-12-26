

# Class ConnectionInfo



[**ClassList**](annotated.md) **>** [**ConnectionInfo**](class_connection_info.md)



[More...](#detailed-description)

* `#include <connection_manager.h>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**ConnectionInfo**](#function-connectioninfo) () <br> |
| virtual std::string | [**ToString**](#function-tostring) () = 0<br> |
| virtual  | [**~ConnectionInfo**](#function-connectioninfo) () <br> |




























## Detailed Description


[**ConnectionInfo**](class_connection_info.md) is an abstract base class for defining connections.


Derived classes from this class must provide a ToString function that provides a useful string for logging purposes about the details of the given connection. 


    
## Public Functions Documentation




### function ConnectionInfo 

```C++
inline ConnectionInfo::ConnectionInfo () 
```




<hr>



### function ToString 

```C++
virtual std::string ConnectionInfo::ToString () = 0
```




<hr>



### function ~ConnectionInfo 

```C++
inline virtual ConnectionInfo::~ConnectionInfo () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/GGPOUE4/Public/include/connection_manager.h`

