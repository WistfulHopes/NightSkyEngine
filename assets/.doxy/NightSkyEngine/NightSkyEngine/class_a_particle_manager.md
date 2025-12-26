

# Class AParticleManager



[**ClassList**](annotated.md) **>** [**AParticleManager**](class_a_particle_manager.md)








Inherits the following classes: AActor


















## Public Attributes

| Type | Name |
| ---: | :--- |
|  TArray&lt; [**FBattleParticle**](struct_f_battle_particle.md) &gt; | [**BattleParticles**](#variable-battleparticles)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**AParticleManager**](#function-aparticlemanager) () <br> |
|  void | [**PauseParticles**](#function-pauseparticles) () <br> |
|  void | [**RollbackParticles**](#function-rollbackparticles) (int RollbackFrames) <br> |
| virtual void | [**Tick**](#function-tick) (float DeltaTime) override<br> |
|  void | [**UpdateParticles**](#function-updateparticles) () <br> |
























## Protected Functions

| Type | Name |
| ---: | :--- |
| virtual void | [**BeginPlay**](#function-beginplay) () override<br> |




## Public Attributes Documentation




### variable BattleParticles 

```C++
TArray<FBattleParticle> AParticleManager::BattleParticles;
```




<hr>
## Public Functions Documentation




### function AParticleManager 

```C++
AParticleManager::AParticleManager () 
```




<hr>



### function PauseParticles 

```C++
void AParticleManager::PauseParticles () 
```




<hr>



### function RollbackParticles 

```C++
void AParticleManager::RollbackParticles (
    int RollbackFrames
) 
```




<hr>



### function Tick 

```C++
virtual void AParticleManager::Tick (
    float DeltaTime
) override
```




<hr>



### function UpdateParticles 

```C++
void AParticleManager::UpdateParticles () 
```




<hr>
## Protected Functions Documentation




### function BeginPlay 

```C++
virtual void AParticleManager::BeginPlay () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/NightSkyEngine/Battle/Actors/ParticleManager.h`

