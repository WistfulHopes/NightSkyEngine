

# Class UNightSkyBattleWidget



[**ClassList**](annotated.md) **>** [**UNightSkyBattleWidget**](class_u_night_sky_battle_widget.md)








Inherits the following classes: UUserWidget


















## Public Attributes

| Type | Name |
| ---: | :--- |
|  int | [**P1ComboCounter**](#variable-p1combocounter)  <br> |
|  TArray&lt; float &gt; | [**P1Gauge**](#variable-p1gauge)  <br> |
|  TArray&lt; float &gt; | [**P1Health**](#variable-p1health)  <br> |
|  float | [**P1Meter**](#variable-p1meter)  <br> |
|  TArray&lt; float &gt; | [**P1RecoverableHealth**](#variable-p1recoverablehealth)  <br> |
|  int | [**P1RoundsWon**](#variable-p1roundswon)  <br> |
|  int | [**P2ComboCounter**](#variable-p2combocounter)  <br> |
|  TArray&lt; float &gt; | [**P2Gauge**](#variable-p2gauge)  <br> |
|  TArray&lt; float &gt; | [**P2Health**](#variable-p2health)  <br> |
|  float | [**P2Meter**](#variable-p2meter)  <br> |
|  TArray&lt; float &gt; | [**P2RecoverableHealth**](#variable-p2recoverablehealth)  <br> |
|  int | [**P2RoundsWon**](#variable-p2roundswon)  <br> |
|  int | [**Ping**](#variable-ping)  <br> |
|  int | [**RollbackFrames**](#variable-rollbackframes)  <br> |
|  float | [**Timer**](#variable-timer)  <br> |
|  TArray&lt; [**FRollbackAnimation**](struct_f_rollback_animation.md) &gt; | [**WidgetAnimationRollback**](#variable-widgetanimationrollback)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**LoadForRollback**](#function-loadforrollback) (const TArray&lt; uint8 &gt; & InBytes) <br> |
|  void | [**PlayComboCounterAnim**](#function-playcombocounteranim) () <br> |
|  void | [**PlayFadeAnim**](#function-playfadeanim) () <br> |
|  void | [**PlayFadeOutAnim**](#function-playfadeoutanim) () <br> |
|  void | [**PlayGaugeAnim**](#function-playgaugeanim) () <br> |
|  void | [**PlayHealthAnim**](#function-playhealthanim) () <br> |
|  void | [**PlayMatchWinAnim**](#function-playmatchwinanim) (bool bIsP1) <br> |
|  void | [**PlayMeterAnim**](#function-playmeteranim) () <br> |
|  void | [**PlayRecoverableHealthAnim**](#function-playrecoverablehealthanim) () <br> |
|  void | [**PlayRoundInitAnim**](#function-playroundinitanim) () <br> |
|  void | [**PlayRoundWinAnim**](#function-playroundwinanim) (bool bIsP1) <br> |
|  void | [**PlayStandardAnimations**](#function-playstandardanimations) () <br> |
|  void | [**PlayTimerAnim**](#function-playtimeranim) () <br> |
|  void | [**RegisterAnimationsForRollback**](#function-registeranimationsforrollback) () <br> |
|  void | [**RollbackAnimations**](#function-rollbackanimations) () <br> |
|  TArray&lt; uint8 &gt; | [**SaveForRollback**](#function-saveforrollback) () <br> |
|  void | [**SetAnimationRollbackData**](#function-setanimationrollbackdata) () <br> |




























## Public Attributes Documentation




### variable P1ComboCounter 

```C++
int UNightSkyBattleWidget::P1ComboCounter;
```




<hr>



### variable P1Gauge 

```C++
TArray<float> UNightSkyBattleWidget::P1Gauge;
```




<hr>



### variable P1Health 

```C++
TArray<float> UNightSkyBattleWidget::P1Health;
```




<hr>



### variable P1Meter 

```C++
float UNightSkyBattleWidget::P1Meter;
```




<hr>



### variable P1RecoverableHealth 

```C++
TArray<float> UNightSkyBattleWidget::P1RecoverableHealth;
```




<hr>



### variable P1RoundsWon 

```C++
int UNightSkyBattleWidget::P1RoundsWon;
```




<hr>



### variable P2ComboCounter 

```C++
int UNightSkyBattleWidget::P2ComboCounter;
```




<hr>



### variable P2Gauge 

```C++
TArray<float> UNightSkyBattleWidget::P2Gauge;
```




<hr>



### variable P2Health 

```C++
TArray<float> UNightSkyBattleWidget::P2Health;
```




<hr>



### variable P2Meter 

```C++
float UNightSkyBattleWidget::P2Meter;
```




<hr>



### variable P2RecoverableHealth 

```C++
TArray<float> UNightSkyBattleWidget::P2RecoverableHealth;
```




<hr>



### variable P2RoundsWon 

```C++
int UNightSkyBattleWidget::P2RoundsWon;
```




<hr>



### variable Ping 

```C++
int UNightSkyBattleWidget::Ping;
```




<hr>



### variable RollbackFrames 

```C++
int UNightSkyBattleWidget::RollbackFrames;
```




<hr>



### variable Timer 

```C++
float UNightSkyBattleWidget::Timer;
```




<hr>



### variable WidgetAnimationRollback 

```C++
TArray<FRollbackAnimation> UNightSkyBattleWidget::WidgetAnimationRollback;
```




<hr>
## Public Functions Documentation




### function LoadForRollback 

```C++
void UNightSkyBattleWidget::LoadForRollback (
    const TArray< uint8 > & InBytes
) 
```




<hr>



### function PlayComboCounterAnim 

```C++
void UNightSkyBattleWidget::PlayComboCounterAnim () 
```




<hr>



### function PlayFadeAnim 

```C++
void UNightSkyBattleWidget::PlayFadeAnim () 
```




<hr>



### function PlayFadeOutAnim 

```C++
void UNightSkyBattleWidget::PlayFadeOutAnim () 
```




<hr>



### function PlayGaugeAnim 

```C++
void UNightSkyBattleWidget::PlayGaugeAnim () 
```




<hr>



### function PlayHealthAnim 

```C++
void UNightSkyBattleWidget::PlayHealthAnim () 
```




<hr>



### function PlayMatchWinAnim 

```C++
void UNightSkyBattleWidget::PlayMatchWinAnim (
    bool bIsP1
) 
```




<hr>



### function PlayMeterAnim 

```C++
void UNightSkyBattleWidget::PlayMeterAnim () 
```




<hr>



### function PlayRecoverableHealthAnim 

```C++
void UNightSkyBattleWidget::PlayRecoverableHealthAnim () 
```




<hr>



### function PlayRoundInitAnim 

```C++
void UNightSkyBattleWidget::PlayRoundInitAnim () 
```




<hr>



### function PlayRoundWinAnim 

```C++
void UNightSkyBattleWidget::PlayRoundWinAnim (
    bool bIsP1
) 
```




<hr>



### function PlayStandardAnimations 

```C++
void UNightSkyBattleWidget::PlayStandardAnimations () 
```




<hr>



### function PlayTimerAnim 

```C++
void UNightSkyBattleWidget::PlayTimerAnim () 
```




<hr>



### function RegisterAnimationsForRollback 

```C++
void UNightSkyBattleWidget::RegisterAnimationsForRollback () 
```




<hr>



### function RollbackAnimations 

```C++
void UNightSkyBattleWidget::RollbackAnimations () 
```




<hr>



### function SaveForRollback 

```C++
TArray< uint8 > UNightSkyBattleWidget::SaveForRollback () 
```




<hr>



### function SetAnimationRollbackData 

```C++
void UNightSkyBattleWidget::SetAnimationRollbackData () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/NightSkyEngine/UI/NightSkyBattleWidget.h`

