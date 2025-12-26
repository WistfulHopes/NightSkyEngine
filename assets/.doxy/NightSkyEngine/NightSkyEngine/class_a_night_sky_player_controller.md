

# Class ANightSkyPlayerController



[**ClassList**](annotated.md) **>** [**ANightSkyPlayerController**](class_a_night_sky_player_controller.md)








Inherits the following classes: APlayerController


Inherited by the following classes: [ANightSkyWTPlayerController](class_a_night_sky_w_t_player_controller.md)
















## Public Attributes

| Type | Name |
| ---: | :--- |
|  int | [**Frame**](#variable-frame)  <br> |
|  [**FBattleInputActions**](struct_f_battle_input_actions.md) | [**InputActions**](#variable-inputactions)  <br> |
|  TSoftObjectPtr&lt; UInputMappingContext &gt; | [**InputMapping**](#variable-inputmapping)  <br> |
|  int | [**Inputs**](#variable-inputs)  <br> |
|  [**ANetworkPawn**](class_a_network_pawn.md) \* | [**NetworkPawn**](#variable-networkpawn)  <br> |
|  bool | [**bRematch**](#variable-brematch)  <br> |
|  bool | [**bRematchAccepted**](#variable-brematchaccepted)  <br> |
|  bool | [**bSentCharaData**](#variable-bsentcharadata)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**ANightSkyPlayerController**](#function-anightskyplayercontroller) () <br> |
|  void | [**ClosePauseMenu**](#function-closepausemenu) () <br> |
|  void | [**OpenPauseMenu**](#function-openpausemenu) () <br> |
|  void | [**PauseGame**](#function-pausegame) () <br> |
|  void | [**PostRematch**](#function-postrematch) () <br> |
|  void | [**PressA**](#function-pressa) () <br> |
|  void | [**PressB**](#function-pressb) () <br> |
|  void | [**PressC**](#function-pressc) () <br> |
|  void | [**PressD**](#function-pressd) () <br> |
|  void | [**PressDown**](#function-pressdown) () <br> |
|  void | [**PressE**](#function-presse) () <br> |
|  void | [**PressF**](#function-pressf) () <br> |
|  void | [**PressG**](#function-pressg) () <br> |
|  void | [**PressH**](#function-pressh) () <br> |
|  void | [**PressLeft**](#function-pressleft) () <br> |
|  void | [**PressRight**](#function-pressright) () <br> |
|  void | [**PressUp**](#function-pressup) () <br> |
|  void | [**ReleaseA**](#function-releasea) () <br> |
|  void | [**ReleaseB**](#function-releaseb) () <br> |
|  void | [**ReleaseC**](#function-releasec) () <br> |
|  void | [**ReleaseD**](#function-released) () <br> |
|  void | [**ReleaseDown**](#function-releasedown) () <br> |
|  void | [**ReleaseE**](#function-releasee) () <br> |
|  void | [**ReleaseF**](#function-releasef) () <br> |
|  void | [**ReleaseG**](#function-releaseg) () <br> |
|  void | [**ReleaseH**](#function-releaseh) () <br> |
|  void | [**ReleaseLeft**](#function-releaseleft) () <br> |
|  void | [**ReleaseRight**](#function-releaseright) () <br> |
|  void | [**ReleaseUp**](#function-releaseup) () <br> |
|  void | [**Rematch**](#function-rematch) () <br> |
|  void | [**ResetTraining**](#function-resettraining) () <br> |
|  void | [**SendBattleData**](#function-sendbattledata) () <br> |
|  void | [**SendGgpo**](#function-sendggpo) ([**ANetworkPawn**](class_a_network_pawn.md) \* InNetworkPawn, bool Client) const<br> |
| virtual void | [**SetupInputComponent**](#function-setupinputcomponent) () override<br> |
| virtual void | [**Tick**](#function-tick) (float DeltaTime) override<br> |
























## Protected Functions

| Type | Name |
| ---: | :--- |
| virtual void | [**BeginPlay**](#function-beginplay) () override<br> |




## Public Attributes Documentation




### variable Frame 

```C++
int ANightSkyPlayerController::Frame;
```




<hr>



### variable InputActions 

```C++
FBattleInputActions ANightSkyPlayerController::InputActions;
```




<hr>



### variable InputMapping 

```C++
TSoftObjectPtr<UInputMappingContext> ANightSkyPlayerController::InputMapping;
```




<hr>



### variable Inputs 

```C++
int ANightSkyPlayerController::Inputs;
```




<hr>



### variable NetworkPawn 

```C++
ANetworkPawn* ANightSkyPlayerController::NetworkPawn;
```




<hr>



### variable bRematch 

```C++
bool ANightSkyPlayerController::bRematch;
```




<hr>



### variable bRematchAccepted 

```C++
bool ANightSkyPlayerController::bRematchAccepted;
```




<hr>



### variable bSentCharaData 

```C++
bool ANightSkyPlayerController::bSentCharaData;
```




<hr>
## Public Functions Documentation




### function ANightSkyPlayerController 

```C++
ANightSkyPlayerController::ANightSkyPlayerController () 
```




<hr>



### function ClosePauseMenu 

```C++
void ANightSkyPlayerController::ClosePauseMenu () 
```




<hr>



### function OpenPauseMenu 

```C++
void ANightSkyPlayerController::OpenPauseMenu () 
```




<hr>



### function PauseGame 

```C++
void ANightSkyPlayerController::PauseGame () 
```




<hr>



### function PostRematch 

```C++
void ANightSkyPlayerController::PostRematch () 
```




<hr>



### function PressA 

```C++
void ANightSkyPlayerController::PressA () 
```




<hr>



### function PressB 

```C++
void ANightSkyPlayerController::PressB () 
```




<hr>



### function PressC 

```C++
void ANightSkyPlayerController::PressC () 
```




<hr>



### function PressD 

```C++
void ANightSkyPlayerController::PressD () 
```




<hr>



### function PressDown 

```C++
void ANightSkyPlayerController::PressDown () 
```




<hr>



### function PressE 

```C++
void ANightSkyPlayerController::PressE () 
```




<hr>



### function PressF 

```C++
void ANightSkyPlayerController::PressF () 
```




<hr>



### function PressG 

```C++
void ANightSkyPlayerController::PressG () 
```




<hr>



### function PressH 

```C++
void ANightSkyPlayerController::PressH () 
```




<hr>



### function PressLeft 

```C++
void ANightSkyPlayerController::PressLeft () 
```




<hr>



### function PressRight 

```C++
void ANightSkyPlayerController::PressRight () 
```




<hr>



### function PressUp 

```C++
void ANightSkyPlayerController::PressUp () 
```




<hr>



### function ReleaseA 

```C++
void ANightSkyPlayerController::ReleaseA () 
```




<hr>



### function ReleaseB 

```C++
void ANightSkyPlayerController::ReleaseB () 
```




<hr>



### function ReleaseC 

```C++
void ANightSkyPlayerController::ReleaseC () 
```




<hr>



### function ReleaseD 

```C++
void ANightSkyPlayerController::ReleaseD () 
```




<hr>



### function ReleaseDown 

```C++
void ANightSkyPlayerController::ReleaseDown () 
```




<hr>



### function ReleaseE 

```C++
void ANightSkyPlayerController::ReleaseE () 
```




<hr>



### function ReleaseF 

```C++
void ANightSkyPlayerController::ReleaseF () 
```




<hr>



### function ReleaseG 

```C++
void ANightSkyPlayerController::ReleaseG () 
```




<hr>



### function ReleaseH 

```C++
void ANightSkyPlayerController::ReleaseH () 
```




<hr>



### function ReleaseLeft 

```C++
void ANightSkyPlayerController::ReleaseLeft () 
```




<hr>



### function ReleaseRight 

```C++
void ANightSkyPlayerController::ReleaseRight () 
```




<hr>



### function ReleaseUp 

```C++
void ANightSkyPlayerController::ReleaseUp () 
```




<hr>



### function Rematch 

```C++
void ANightSkyPlayerController::Rematch () 
```




<hr>



### function ResetTraining 

```C++
void ANightSkyPlayerController::ResetTraining () 
```




<hr>



### function SendBattleData 

```C++
void ANightSkyPlayerController::SendBattleData () 
```




<hr>



### function SendGgpo 

```C++
void ANightSkyPlayerController::SendGgpo (
    ANetworkPawn * InNetworkPawn,
    bool Client
) const
```




<hr>



### function SetupInputComponent 

```C++
virtual void ANightSkyPlayerController::SetupInputComponent () override
```




<hr>



### function Tick 

```C++
virtual void ANightSkyPlayerController::Tick (
    float DeltaTime
) override
```




<hr>
## Protected Functions Documentation




### function BeginPlay 

```C++
virtual void ANightSkyPlayerController::BeginPlay () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/NightSkyEngine/Battle/NightSkyPlayerController.h`

