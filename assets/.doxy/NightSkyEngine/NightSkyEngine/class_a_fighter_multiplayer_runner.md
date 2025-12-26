

# Class AFighterMultiplayerRunner



[**ClassList**](annotated.md) **>** [**AFighterMultiplayerRunner**](class_a_fighter_multiplayer_runner.md)








Inherits the following classes: [AFighterLocalRunner](class_a_fighter_local_runner.md)


Inherited by the following classes: [AFighterSynctestRunner](class_a_fighter_synctest_runner.md)




















## Public Attributes

| Type | Name |
| ---: | :--- |
|  TArray&lt; GGPOPlayerHandle &gt; | [**PlayerHandles**](#variable-playerhandles)  <br> |
|  TArray&lt; GGPOPlayer \* &gt; | [**Players**](#variable-players)  <br> |
|  class [**RpcConnectionManager**](class_rpc_connection_manager.md) \* | [**connectionManager**](#variable-connectionmanager)  <br> |
|  GGPOSession \* | [**ggpo**](#variable-ggpo)   = `nullptr`<br> |
































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**AFighterMultiplayerRunner**](#function-afightermultiplayerrunner) () <br> |
| virtual void | [**Update**](#function-update) (float DeltaTime) override<br> |


## Public Functions inherited from AFighterLocalRunner

See [AFighterLocalRunner](class_a_fighter_local_runner.md)

| Type | Name |
| ---: | :--- |
|   | [**AFighterLocalRunner**](class_a_fighter_local_runner.md#function-afighterlocalrunner) () <br> |
| virtual void | [**Update**](class_a_fighter_local_runner.md#function-update) (float DeltaTime) <br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  int | [**fletcher32\_checksum**](#function-fletcher32_checksum) (short \* data, size\_t len) <br> |












## Protected Attributes

| Type | Name |
| ---: | :--- |
|  int | [**MultipliedFramesAhead**](#variable-multipliedframesahead)   = `0`<br> |
|  int | [**MultipliedFramesBehind**](#variable-multipliedframesbehind)   = `0`<br> |
|  TArray&lt; int &gt; | [**PlayerInputIndex**](#variable-playerinputindex)  <br> |


## Protected Attributes inherited from AFighterLocalRunner

See [AFighterLocalRunner](class_a_fighter_local_runner.md)

| Type | Name |
| ---: | :--- |
|  float | [**ElapsedTime**](class_a_fighter_local_runner.md#variable-elapsedtime)   = `0`<br> |
|  class [**ANightSkyGameState**](class_a_night_sky_game_state.md) \* | [**GameState**](class_a_fighter_local_runner.md#variable-gamestate)  <br> |






























## Protected Functions

| Type | Name |
| ---: | :--- |
|  bool \_\_cdecl | [**AdvanceFrameCallback**](#function-advanceframecallback) (int32) <br> |
|  bool \_\_cdecl | [**BeginGameCallback**](#function-begingamecallback) (const char \*) <br> |
| virtual void | [**BeginPlay**](#function-beginplay) () override<br> |
|  GGPOSessionCallbacks | [**CreateCallbacks**](#function-createcallbacks) () <br> |
| virtual void | [**EndPlay**](#function-endplay) (const EEndPlayReason::Type EndPlayReason) override<br> |
|  void \_\_cdecl | [**FreeBuffer**](#function-freebuffer) (void \* buffer) <br> |
|  void | [**GgpoUpdate**](#function-ggpoupdate) () <br> |
|  bool \_\_cdecl | [**LoadGameStateCallback**](#function-loadgamestatecallback) (unsigned char \* buffer, int32 len) <br> |
|  bool \_\_cdecl | [**LogGameState**](#function-loggamestate) (const char \* filename, unsigned char \* buffer, int len) <br> |
|  bool \_\_cdecl | [**OnEventCallback**](#function-oneventcallback) (GGPOEvent \* info) <br> |
|  bool \_\_cdecl | [**SaveGameStateCallback**](#function-savegamestatecallback) (unsigned char \*\* buffer, int32 \* len, int32 \* checksum, int32) <br> |


## Protected Functions inherited from AFighterLocalRunner

See [AFighterLocalRunner](class_a_fighter_local_runner.md)

| Type | Name |
| ---: | :--- |
| virtual void | [**BeginPlay**](class_a_fighter_local_runner.md#function-beginplay) () override<br> |






## Public Attributes Documentation




### variable PlayerHandles 

```C++
TArray<GGPOPlayerHandle> AFighterMultiplayerRunner::PlayerHandles;
```




<hr>



### variable Players 

```C++
TArray<GGPOPlayer*> AFighterMultiplayerRunner::Players;
```




<hr>



### variable connectionManager 

```C++
class RpcConnectionManager* AFighterMultiplayerRunner::connectionManager;
```




<hr>



### variable ggpo 

```C++
GGPOSession* AFighterMultiplayerRunner::ggpo;
```




<hr>
## Public Functions Documentation




### function AFighterMultiplayerRunner 

```C++
AFighterMultiplayerRunner::AFighterMultiplayerRunner () 
```




<hr>



### function Update 

```C++
virtual void AFighterMultiplayerRunner::Update (
    float DeltaTime
) override
```



Implements [*AFighterLocalRunner::Update*](class_a_fighter_local_runner.md#function-update)


<hr>
## Public Static Functions Documentation




### function fletcher32\_checksum 

```C++
static int AFighterMultiplayerRunner::fletcher32_checksum (
    short * data,
    size_t len
) 
```




<hr>
## Protected Attributes Documentation




### variable MultipliedFramesAhead 

```C++
int AFighterMultiplayerRunner::MultipliedFramesAhead;
```




<hr>



### variable MultipliedFramesBehind 

```C++
int AFighterMultiplayerRunner::MultipliedFramesBehind;
```




<hr>



### variable PlayerInputIndex 

```C++
TArray<int> AFighterMultiplayerRunner::PlayerInputIndex;
```




<hr>
## Protected Functions Documentation




### function AdvanceFrameCallback 

```C++
bool __cdecl AFighterMultiplayerRunner::AdvanceFrameCallback (
    int32
) 
```




<hr>



### function BeginGameCallback 

```C++
bool __cdecl AFighterMultiplayerRunner::BeginGameCallback (
    const char *
) 
```




<hr>



### function BeginPlay 

```C++
virtual void AFighterMultiplayerRunner::BeginPlay () override
```



Implements [*AFighterLocalRunner::BeginPlay*](class_a_fighter_local_runner.md#function-beginplay)


<hr>



### function CreateCallbacks 

```C++
GGPOSessionCallbacks AFighterMultiplayerRunner::CreateCallbacks () 
```




<hr>



### function EndPlay 

```C++
virtual void AFighterMultiplayerRunner::EndPlay (
    const EEndPlayReason::Type EndPlayReason
) override
```




<hr>



### function FreeBuffer 

```C++
void __cdecl AFighterMultiplayerRunner::FreeBuffer (
    void * buffer
) 
```




<hr>



### function GgpoUpdate 

```C++
void AFighterMultiplayerRunner::GgpoUpdate () 
```




<hr>



### function LoadGameStateCallback 

```C++
bool __cdecl AFighterMultiplayerRunner::LoadGameStateCallback (
    unsigned char * buffer,
    int32 len
) 
```




<hr>



### function LogGameState 

```C++
bool __cdecl AFighterMultiplayerRunner::LogGameState (
    const char * filename,
    unsigned char * buffer,
    int len
) 
```




<hr>



### function OnEventCallback 

```C++
bool __cdecl AFighterMultiplayerRunner::OnEventCallback (
    GGPOEvent * info
) 
```




<hr>



### function SaveGameStateCallback 

```C++
bool __cdecl AFighterMultiplayerRunner::SaveGameStateCallback (
    unsigned char ** buffer,
    int32 * len,
    int32 * checksum,
    int32
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/NightSkyEngine/Battle/FighterRunners/FighterMultiplayerRunner.h`

