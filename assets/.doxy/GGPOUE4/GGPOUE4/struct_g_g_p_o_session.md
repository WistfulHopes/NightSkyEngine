

# Struct GGPOSession



[**ClassList**](annotated.md) **>** [**GGPOSession**](struct_g_g_p_o_session.md)










Inherited by the following classes: [Peer2PeerBackend](class_peer2_peer_backend.md),  [SpectatorBackend](class_spectator_backend.md),  [SyncTestBackend](class_sync_test_backend.md)
































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual GGPOErrorCode | [**AddLocalInput**](#function-addlocalinput) (GGPOPlayerHandle player, void \* values, int size) = 0<br> |
| virtual GGPOErrorCode | [**AddPlayer**](#function-addplayer) ([**GGPOPlayer**](struct_g_g_p_o_player.md) \* player, GGPOPlayerHandle \* handle) = 0<br> |
| virtual GGPOErrorCode | [**Chat**](#function-chat) (char \* text) <br> |
| virtual GGPOErrorCode | [**DisconnectPlayer**](#function-disconnectplayer) (GGPOPlayerHandle handle) <br> |
| virtual GGPOErrorCode | [**DoPoll**](#function-dopoll) (int timeout) <br> |
| virtual GGPOErrorCode | [**GetNetworkStats**](#function-getnetworkstats) ([**FGGPONetworkStats**](struct_f_g_g_p_o_network_stats.md) \* stats, GGPOPlayerHandle handle) <br> |
| virtual GGPOErrorCode | [**IncrementFrame**](#function-incrementframe) (void) <br> |
| virtual GGPOErrorCode | [**Logv**](#function-logv) (const char \* fmt, va\_list list) <br> |
| virtual GGPOErrorCode | [**SetDisconnectNotifyStart**](#function-setdisconnectnotifystart) (int timeout) <br> |
| virtual GGPOErrorCode | [**SetDisconnectTimeout**](#function-setdisconnecttimeout) (int timeout) <br> |
| virtual GGPOErrorCode | [**SetFrameDelay**](#function-setframedelay) (GGPOPlayerHandle player, int delay) <br> |
| virtual GGPOErrorCode | [**SyncInput**](#function-syncinput) (void \* values, int size, int \* disconnect\_flags) = 0<br> |
| virtual GGPOErrorCode | [**TrySynchronizeLocal**](#function-trysynchronizelocal) () <br> |
| virtual  | [**~GGPOSession**](#function-ggposession) () <br> |




























## Public Functions Documentation




### function AddLocalInput 

```C++
virtual GGPOErrorCode GGPOSession::AddLocalInput (
    GGPOPlayerHandle player,
    void * values,
    int size
) = 0
```




<hr>



### function AddPlayer 

```C++
virtual GGPOErrorCode GGPOSession::AddPlayer (
    GGPOPlayer * player,
    GGPOPlayerHandle * handle
) = 0
```




<hr>



### function Chat 

```C++
inline virtual GGPOErrorCode GGPOSession::Chat (
    char * text
) 
```




<hr>



### function DisconnectPlayer 

```C++
inline virtual GGPOErrorCode GGPOSession::DisconnectPlayer (
    GGPOPlayerHandle handle
) 
```




<hr>



### function DoPoll 

```C++
inline virtual GGPOErrorCode GGPOSession::DoPoll (
    int timeout
) 
```




<hr>



### function GetNetworkStats 

```C++
inline virtual GGPOErrorCode GGPOSession::GetNetworkStats (
    FGGPONetworkStats * stats,
    GGPOPlayerHandle handle
) 
```




<hr>



### function IncrementFrame 

```C++
inline virtual GGPOErrorCode GGPOSession::IncrementFrame (
    void
) 
```




<hr>



### function Logv 

```C++
inline virtual GGPOErrorCode GGPOSession::Logv (
    const char * fmt,
    va_list list
) 
```




<hr>



### function SetDisconnectNotifyStart 

```C++
inline virtual GGPOErrorCode GGPOSession::SetDisconnectNotifyStart (
    int timeout
) 
```




<hr>



### function SetDisconnectTimeout 

```C++
inline virtual GGPOErrorCode GGPOSession::SetDisconnectTimeout (
    int timeout
) 
```




<hr>



### function SetFrameDelay 

```C++
inline virtual GGPOErrorCode GGPOSession::SetFrameDelay (
    GGPOPlayerHandle player,
    int delay
) 
```




<hr>



### function SyncInput 

```C++
virtual GGPOErrorCode GGPOSession::SyncInput (
    void * values,
    int size,
    int * disconnect_flags
) = 0
```




<hr>



### function TrySynchronizeLocal 

```C++
inline virtual GGPOErrorCode GGPOSession::TrySynchronizeLocal () 
```




<hr>



### function ~GGPOSession 

```C++
inline virtual GGPOSession::~GGPOSession () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/GGPOUE4/Private/backends/backend.h`

