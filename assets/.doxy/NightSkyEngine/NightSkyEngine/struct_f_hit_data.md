

# Struct FHitData



[**ClassList**](annotated.md) **>** [**FHitData**](struct_f_hit_data.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  TEnumAsByte&lt; EHitAction &gt; | [**AirHitAction**](#variable-airhitaction)   = `HACT\_AirNormal`<br> |
|  int32 | [**AirPushbackX**](#variable-airpushbackx)   = `INT\_MAX`<br> |
|  [**FHitValueOverTime**](struct_f_hit_value_over_time.md) | [**AirPushbackXOverTime**](#variable-airpushbackxovertime)  <br> |
|  int32 | [**AirPushbackY**](#variable-airpushbacky)   = `INT\_MAX`<br> |
|  [**FHitValueOverTime**](struct_f_hit_value_over_time.md) | [**AirPushbackYOverTime**](#variable-airpushbackyovertime)  <br> |
|  int32 | [**BlowbackLevel**](#variable-blowbacklevel)   = `INT\_MAX`<br> |
|  FGameplayTag | [**CustomHitAction**](#variable-customhitaction)  <br> |
|  int32 | [**Damage**](#variable-damage)   = `INT\_MAX`<br> |
|  int32 | [**EnemyHitstopModifier**](#variable-enemyhitstopmodifier)   = `INT\_MAX`<br> |
|  TEnumAsByte&lt; EFloatingCrumpleType &gt; | [**FloatingCrumpleType**](#variable-floatingcrumpletype)  <br> |
|  int32 | [**ForcedProration**](#variable-forcedproration)   = `INT\_MAX`<br> |
|  int32 | [**Gravity**](#variable-gravity)   = `INT\_MAX`<br> |
|  [**FHitValueOverTime**](struct_f_hit_value_over_time.md) | [**GravityOverTime**](#variable-gravityovertime)  <br> |
|  [**FGroundBounceData**](struct_f_ground_bounce_data.md) | [**GroundBounce**](#variable-groundbounce)  <br> |
|  TEnumAsByte&lt; EHitAction &gt; | [**GroundHitAction**](#variable-groundhitaction)   = `HACT\_GroundNormal`<br> |
|  int32 | [**GroundPushbackX**](#variable-groundpushbackx)   = `INT\_MAX`<br> |
|  int32 | [**HardKnockdown**](#variable-hardknockdown)   = `INT\_MAX`<br> |
|  int32 | [**Hitstop**](#variable-hitstop)   = `INT\_MAX`<br> |
|  int32 | [**Hitstun**](#variable-hitstun)   = `INT\_MAX`<br> |
|  int32 | [**InitialProration**](#variable-initialproration)   = `INT\_MAX`<br> |
|  int32 | [**KnockdownTime**](#variable-knockdowntime)   = `INT\_MAX`<br> |
|  int32 | [**MinimumDamagePercent**](#variable-minimumdamagepercent)   = `INT\_MAX`<br> |
|  [**FHitPosition**](struct_f_hit_position.md) | [**Position**](#variable-position)  <br> |
|  int32 | [**RecoverableDamagePercent**](#variable-recoverabledamagepercent)   = `INT\_MAX`<br> |
|  int32 | [**Untech**](#variable-untech)   = `INT\_MAX`<br> |
|  [**FWallBounceData**](struct_f_wall_bounce_data.md) | [**WallBounce**](#variable-wallbounce)  <br> |












































## Public Attributes Documentation




### variable AirHitAction 

```C++
TEnumAsByte<EHitAction> FHitData::AirHitAction;
```




<hr>



### variable AirPushbackX 

```C++
int32 FHitData::AirPushbackX;
```




<hr>



### variable AirPushbackXOverTime 

```C++
FHitValueOverTime FHitData::AirPushbackXOverTime;
```




<hr>



### variable AirPushbackY 

```C++
int32 FHitData::AirPushbackY;
```




<hr>



### variable AirPushbackYOverTime 

```C++
FHitValueOverTime FHitData::AirPushbackYOverTime;
```




<hr>



### variable BlowbackLevel 

```C++
int32 FHitData::BlowbackLevel;
```




<hr>



### variable CustomHitAction 

```C++
FGameplayTag FHitData::CustomHitAction;
```




<hr>



### variable Damage 

```C++
int32 FHitData::Damage;
```




<hr>



### variable EnemyHitstopModifier 

```C++
int32 FHitData::EnemyHitstopModifier;
```




<hr>



### variable FloatingCrumpleType 

```C++
TEnumAsByte<EFloatingCrumpleType> FHitData::FloatingCrumpleType;
```




<hr>



### variable ForcedProration 

```C++
int32 FHitData::ForcedProration;
```




<hr>



### variable Gravity 

```C++
int32 FHitData::Gravity;
```




<hr>



### variable GravityOverTime 

```C++
FHitValueOverTime FHitData::GravityOverTime;
```




<hr>



### variable GroundBounce 

```C++
FGroundBounceData FHitData::GroundBounce;
```




<hr>



### variable GroundHitAction 

```C++
TEnumAsByte<EHitAction> FHitData::GroundHitAction;
```




<hr>



### variable GroundPushbackX 

```C++
int32 FHitData::GroundPushbackX;
```




<hr>



### variable HardKnockdown 

```C++
int32 FHitData::HardKnockdown;
```




<hr>



### variable Hitstop 

```C++
int32 FHitData::Hitstop;
```




<hr>



### variable Hitstun 

```C++
int32 FHitData::Hitstun;
```




<hr>



### variable InitialProration 

```C++
int32 FHitData::InitialProration;
```




<hr>



### variable KnockdownTime 

```C++
int32 FHitData::KnockdownTime;
```




<hr>



### variable MinimumDamagePercent 

```C++
int32 FHitData::MinimumDamagePercent;
```




<hr>



### variable Position 

```C++
FHitPosition FHitData::Position;
```




<hr>



### variable RecoverableDamagePercent 

```C++
int32 FHitData::RecoverableDamagePercent;
```




<hr>



### variable Untech 

```C++
int32 FHitData::Untech;
```




<hr>



### variable WallBounce 

```C++
FWallBounceData FHitData::WallBounce;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/NightSkyEngine/Battle/Objects/BattleObject.h`

