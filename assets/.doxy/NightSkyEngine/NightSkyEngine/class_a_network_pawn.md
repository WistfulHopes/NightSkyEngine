

# Class ANetworkPawn



[**ClassList**](annotated.md) **>** [**ANetworkPawn**](class_a_network_pawn.md)








Inherits the following classes: APawn


















## Public Attributes

| Type | Name |
| ---: | :--- |
|  bool | [**CharaDataReceived**](#variable-charadatareceived)   = `false`<br> |
|  class [**AFighterMultiplayerRunner**](class_a_fighter_multiplayer_runner.md) \* | [**FighterMultiplayerRunner**](#variable-fightermultiplayerrunner)   = `nullptr`<br> |
|  bool | [**bRematchAccepted**](#variable-brematchaccepted)   = `false`<br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**ANetworkPawn**](#function-anetworkpawn) () <br> |
|  void | [**ClientChecksumCheck**](#function-clientchecksumcheck) (uint32 Checksum, int32 InFrame) <br> |
|  void | [**ClientGetBattleData**](#function-clientgetbattledata) ([**FBattleData**](struct_f_battle_data.md) InBattleData, [**FNetworkMirror**](struct_f_network_mirror.md) Mirror) <br> |
|  void | [**ClientGetCharaData**](#function-clientgetcharadata) (TArray&lt; FPrimaryAssetId &gt; Assets) <br> |
| virtual void | [**GetLifetimeReplicatedProps**](#function-getlifetimereplicatedprops) (TArray&lt; FLifetimeProperty &gt; & OutLifetimeProps) override const<br> |
|  void | [**SendGgpoToClient**](#function-sendggpotoclient) (const TArray&lt; int8 &gt; & GgpoMessage) <br> |
|  void | [**SendGgpoToServer**](#function-sendggpotoserver) (const TArray&lt; int8 &gt; & GgpoMessage) <br> |
|  void | [**SendRematchToServer**](#function-sendrematchtoserver) () <br> |
|  void | [**ServerChecksumCheck**](#function-serverchecksumcheck) (uint32 Checksum, int32 InFrame) <br> |
|  void | [**ServerGetBattleData**](#function-servergetbattledata) ([**FBattleData**](struct_f_battle_data.md) InBattleData, [**FNetworkMirror**](struct_f_network_mirror.md) Mirror) <br> |
|  void | [**ServerGetCharaData**](#function-servergetcharadata) (TArray&lt; FPrimaryAssetId &gt; Assets) <br> |
|  void | [**ServerGetFinishedLoading**](#function-servergetfinishedloading) (bool Finished) <br> |
























## Protected Functions

| Type | Name |
| ---: | :--- |
| virtual void | [**BeginPlay**](#function-beginplay) () override<br> |




## Public Attributes Documentation




### variable CharaDataReceived 

```C++
bool ANetworkPawn::CharaDataReceived;
```




<hr>



### variable FighterMultiplayerRunner 

```C++
class AFighterMultiplayerRunner* ANetworkPawn::FighterMultiplayerRunner;
```




<hr>



### variable bRematchAccepted 

```C++
bool ANetworkPawn::bRematchAccepted;
```




<hr>
## Public Functions Documentation




### function ANetworkPawn 

```C++
ANetworkPawn::ANetworkPawn () 
```




<hr>



### function ClientChecksumCheck 

```C++
void ANetworkPawn::ClientChecksumCheck (
    uint32 Checksum,
    int32 InFrame
) 
```




<hr>



### function ClientGetBattleData 

```C++
void ANetworkPawn::ClientGetBattleData (
    FBattleData InBattleData,
    FNetworkMirror Mirror
) 
```




<hr>



### function ClientGetCharaData 

```C++
void ANetworkPawn::ClientGetCharaData (
    TArray< FPrimaryAssetId > Assets
) 
```




<hr>



### function GetLifetimeReplicatedProps 

```C++
virtual void ANetworkPawn::GetLifetimeReplicatedProps (
    TArray< FLifetimeProperty > & OutLifetimeProps
) override const
```




<hr>



### function SendGgpoToClient 

```C++
void ANetworkPawn::SendGgpoToClient (
    const TArray< int8 > & GgpoMessage
) 
```




<hr>



### function SendGgpoToServer 

```C++
void ANetworkPawn::SendGgpoToServer (
    const TArray< int8 > & GgpoMessage
) 
```




<hr>



### function SendRematchToServer 

```C++
void ANetworkPawn::SendRematchToServer () 
```




<hr>



### function ServerChecksumCheck 

```C++
void ANetworkPawn::ServerChecksumCheck (
    uint32 Checksum,
    int32 InFrame
) 
```




<hr>



### function ServerGetBattleData 

```C++
void ANetworkPawn::ServerGetBattleData (
    FBattleData InBattleData,
    FNetworkMirror Mirror
) 
```




<hr>



### function ServerGetCharaData 

```C++
void ANetworkPawn::ServerGetCharaData (
    TArray< FPrimaryAssetId > Assets
) 
```




<hr>



### function ServerGetFinishedLoading 

```C++
void ANetworkPawn::ServerGetFinishedLoading (
    bool Finished
) 
```




<hr>
## Protected Functions Documentation




### function BeginPlay 

```C++
virtual void ANetworkPawn::BeginPlay () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/NightSkyEngine/Network/NetworkPawn.h`

