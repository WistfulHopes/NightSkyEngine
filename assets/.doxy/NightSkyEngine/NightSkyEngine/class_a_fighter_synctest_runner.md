

# Class AFighterSynctestRunner



[**ClassList**](annotated.md) **>** [**AFighterSynctestRunner**](class_a_fighter_synctest_runner.md)








Inherits the following classes: [AFighterMultiplayerRunner](class_a_fighter_multiplayer_runner.md)




























## Public Attributes inherited from AFighterMultiplayerRunner

See [AFighterMultiplayerRunner](class_a_fighter_multiplayer_runner.md)

| Type | Name |
| ---: | :--- |
|  TArray&lt; GGPOPlayerHandle &gt; | [**PlayerHandles**](class_a_fighter_multiplayer_runner.md#variable-playerhandles)  <br> |
|  TArray&lt; GGPOPlayer \* &gt; | [**Players**](class_a_fighter_multiplayer_runner.md#variable-players)  <br> |
|  class [**RpcConnectionManager**](class_rpc_connection_manager.md) \* | [**connectionManager**](class_a_fighter_multiplayer_runner.md#variable-connectionmanager)  <br> |
|  GGPOSession \* | [**ggpo**](class_a_fighter_multiplayer_runner.md#variable-ggpo)   = `nullptr`<br> |














































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**AFighterSynctestRunner**](#function-afightersynctestrunner) () <br> |
| virtual void | [**Update**](#function-update) (float DeltaTime) override<br> |


## Public Functions inherited from AFighterMultiplayerRunner

See [AFighterMultiplayerRunner](class_a_fighter_multiplayer_runner.md)

| Type | Name |
| ---: | :--- |
|   | [**AFighterMultiplayerRunner**](class_a_fighter_multiplayer_runner.md#function-afightermultiplayerrunner) () <br> |
| virtual void | [**Update**](class_a_fighter_multiplayer_runner.md#function-update) (float DeltaTime) override<br> |


## Public Functions inherited from AFighterLocalRunner

See [AFighterLocalRunner](class_a_fighter_local_runner.md)

| Type | Name |
| ---: | :--- |
|   | [**AFighterLocalRunner**](class_a_fighter_local_runner.md#function-afighterlocalrunner) () <br> |
| virtual void | [**Update**](class_a_fighter_local_runner.md#function-update) (float DeltaTime) <br> |




## Public Static Functions inherited from AFighterMultiplayerRunner

See [AFighterMultiplayerRunner](class_a_fighter_multiplayer_runner.md)

| Type | Name |
| ---: | :--- |
|  int | [**fletcher32\_checksum**](class_a_fighter_multiplayer_runner.md#function-fletcher32_checksum) (short \* data, size\_t len) <br> |


















## Protected Attributes inherited from AFighterMultiplayerRunner

See [AFighterMultiplayerRunner](class_a_fighter_multiplayer_runner.md)

| Type | Name |
| ---: | :--- |
|  int | [**MultipliedFramesAhead**](class_a_fighter_multiplayer_runner.md#variable-multipliedframesahead)   = `0`<br> |
|  int | [**MultipliedFramesBehind**](class_a_fighter_multiplayer_runner.md#variable-multipliedframesbehind)   = `0`<br> |
|  TArray&lt; int &gt; | [**PlayerInputIndex**](class_a_fighter_multiplayer_runner.md#variable-playerinputindex)  <br> |


## Protected Attributes inherited from AFighterLocalRunner

See [AFighterLocalRunner](class_a_fighter_local_runner.md)

| Type | Name |
| ---: | :--- |
|  float | [**ElapsedTime**](class_a_fighter_local_runner.md#variable-elapsedtime)   = `0`<br> |
|  class [**ANightSkyGameState**](class_a_night_sky_game_state.md) \* | [**GameState**](class_a_fighter_local_runner.md#variable-gamestate)  <br> |












































## Protected Functions

| Type | Name |
| ---: | :--- |
| virtual void | [**BeginPlay**](#function-beginplay) () override<br> |


## Protected Functions inherited from AFighterMultiplayerRunner

See [AFighterMultiplayerRunner](class_a_fighter_multiplayer_runner.md)

| Type | Name |
| ---: | :--- |
|  bool \_\_cdecl | [**AdvanceFrameCallback**](class_a_fighter_multiplayer_runner.md#function-advanceframecallback) (int32) <br> |
|  bool \_\_cdecl | [**BeginGameCallback**](class_a_fighter_multiplayer_runner.md#function-begingamecallback) (const char \*) <br> |
| virtual void | [**BeginPlay**](class_a_fighter_multiplayer_runner.md#function-beginplay) () override<br> |
|  GGPOSessionCallbacks | [**CreateCallbacks**](class_a_fighter_multiplayer_runner.md#function-createcallbacks) () <br> |
| virtual void | [**EndPlay**](class_a_fighter_multiplayer_runner.md#function-endplay) (const EEndPlayReason::Type EndPlayReason) override<br> |
|  void \_\_cdecl | [**FreeBuffer**](class_a_fighter_multiplayer_runner.md#function-freebuffer) (void \* buffer) <br> |
|  void | [**GgpoUpdate**](class_a_fighter_multiplayer_runner.md#function-ggpoupdate) () <br> |
|  bool \_\_cdecl | [**LoadGameStateCallback**](class_a_fighter_multiplayer_runner.md#function-loadgamestatecallback) (unsigned char \* buffer, int32 len) <br> |
|  bool \_\_cdecl | [**LogGameState**](class_a_fighter_multiplayer_runner.md#function-loggamestate) (const char \* filename, unsigned char \* buffer, int len) <br> |
|  bool \_\_cdecl | [**OnEventCallback**](class_a_fighter_multiplayer_runner.md#function-oneventcallback) (GGPOEvent \* info) <br> |
|  bool \_\_cdecl | [**SaveGameStateCallback**](class_a_fighter_multiplayer_runner.md#function-savegamestatecallback) (unsigned char \*\* buffer, int32 \* len, int32 \* checksum, int32) <br> |


## Protected Functions inherited from AFighterLocalRunner

See [AFighterLocalRunner](class_a_fighter_local_runner.md)

| Type | Name |
| ---: | :--- |
| virtual void | [**BeginPlay**](class_a_fighter_local_runner.md#function-beginplay) () override<br> |








## Public Functions Documentation




### function AFighterSynctestRunner 

```C++
AFighterSynctestRunner::AFighterSynctestRunner () 
```




<hr>



### function Update 

```C++
virtual void AFighterSynctestRunner::Update (
    float DeltaTime
) override
```



Implements [*AFighterMultiplayerRunner::Update*](class_a_fighter_multiplayer_runner.md#function-update)


<hr>
## Protected Functions Documentation




### function BeginPlay 

```C++
virtual void AFighterSynctestRunner::BeginPlay () override
```



Implements [*AFighterMultiplayerRunner::BeginPlay*](class_a_fighter_multiplayer_runner.md#function-beginplay)


<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/NightSkyEngine/Battle/FighterRunners/FighterSynctestRunner.h`

