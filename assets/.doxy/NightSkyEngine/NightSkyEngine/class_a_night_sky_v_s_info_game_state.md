

# Class ANightSkyVSInfoGameState



[**ClassList**](annotated.md) **>** [**ANightSkyVSInfoGameState**](class_a_night_sky_v_s_info_game_state.md)








Inherits the following classes: AGameStateBase


















## Public Attributes

| Type | Name |
| ---: | :--- |
|  double | [**MaxVSInfoTime**](#variable-maxvsinfotime)   = `6`<br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**ANightSkyVSInfoGameState**](#function-anightskyvsinfogamestate) () <br> |
| virtual void | [**BeginPlay**](#function-beginplay) () override<br> |
|  void | [**OnCharaPackageLoaded**](#function-oncharapackageloaded) (const FName & PackageName, UPackage \* LoadedPackage, EAsyncLoadingResult::Type Result) <br> |
|  void | [**OnMapPackageLoaded**](#function-onmappackageloaded) (const FName & PackageName, UPackage \* LoadedPackage, EAsyncLoadingResult::Type Result) <br> |
| virtual void | [**Tick**](#function-tick) (float DeltaSeconds) override<br> |




























## Public Attributes Documentation




### variable MaxVSInfoTime 

```C++
double ANightSkyVSInfoGameState::MaxVSInfoTime;
```




<hr>
## Public Functions Documentation




### function ANightSkyVSInfoGameState 

```C++
ANightSkyVSInfoGameState::ANightSkyVSInfoGameState () 
```




<hr>



### function BeginPlay 

```C++
virtual void ANightSkyVSInfoGameState::BeginPlay () override
```




<hr>



### function OnCharaPackageLoaded 

```C++
void ANightSkyVSInfoGameState::OnCharaPackageLoaded (
    const FName & PackageName,
    UPackage * LoadedPackage,
    EAsyncLoadingResult::Type Result
) 
```




<hr>



### function OnMapPackageLoaded 

```C++
void ANightSkyVSInfoGameState::OnMapPackageLoaded (
    const FName & PackageName,
    UPackage * LoadedPackage,
    EAsyncLoadingResult::Type Result
) 
```




<hr>



### function Tick 

```C++
virtual void ANightSkyVSInfoGameState::Tick (
    float DeltaSeconds
) override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/NightSkyEngine/VSInfo/NightSkyVSInfoGameState.h`

