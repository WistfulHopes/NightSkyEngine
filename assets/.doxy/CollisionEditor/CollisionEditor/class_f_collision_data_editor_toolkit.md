

# Class FCollisionDataEditorToolkit



[**ClassList**](annotated.md) **>** [**FCollisionDataEditorToolkit**](class_f_collision_data_editor_toolkit.md)



[More...](#detailed-description)

* `#include <CollisionDataEditorToolkit.h>`



Inherits the following classes: FAssetEditorToolkit


































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**FCollisionDataEditorToolkit**](#function-fcollisiondataeditortoolkit) () <br> |
| virtual FText | [**GetBaseToolkitName**](#function-getbasetoolkitname) () override const<br> |
|  FText | [**GetSelectedState**](#function-getselectedstate) () const<br> |
| virtual FName | [**GetToolkitFName**](#function-gettoolkitfname) () override const<br> |
| virtual FText | [**GetToolkitName**](#function-gettoolkitname) () override const<br> |
| virtual FLinearColor | [**GetWorldCentricTabColorScale**](#function-getworldcentrictabcolorscale) () override const<br> |
| virtual FString | [**GetWorldCentricTabPrefix**](#function-getworldcentrictabprefix) () override const<br> |
|  void | [**Initialize**](#function-initialize) (UCollisionData \* InCollisionData, const EToolkitMode::Type Mode, const TSharedPtr&lt; IToolkitHost &gt; & InitToolkitHost) <br> |
|  void | [**InitializePreviewScene**](#function-initializepreviewscene) () <br> |
| virtual void | [**RegisterTabSpawners**](#function-registertabspawners) (const TSharedRef&lt; FTabManager &gt; & InTabManager) override<br> |
|  TSharedRef&lt; SDockTab &gt; | [**SpawnTab\_CollisionDataDetails**](#function-spawntab_collisiondatadetails) (const FSpawnTabArgs & Args) <br> |
|  TSharedRef&lt; SDockTab &gt; | [**SpawnTab\_PlayerObjectSelector**](#function-spawntab_playerobjectselector) (const FSpawnTabArgs & Args) <br> |
|  TSharedRef&lt; SDockTab &gt; | [**SpawnTab\_ViewportTab**](#function-spawntab_viewporttab) (const FSpawnTabArgs & Args) <br> |
| virtual void | [**UnregisterTabSpawners**](#function-unregistertabspawners) (const TSharedRef&lt; FTabManager &gt; & InTabManager) override<br> |
| virtual  | [**~FCollisionDataEditorToolkit**](#function-fcollisiondataeditortoolkit) () override<br> |
























## Protected Functions

| Type | Name |
| ---: | :--- |
| virtual void | [**OnClose**](#function-onclose) () override<br> |




## Detailed Description


Toolkit for editing collision data assets for Night Sky. 


    
## Public Functions Documentation




### function FCollisionDataEditorToolkit 

```C++
FCollisionDataEditorToolkit::FCollisionDataEditorToolkit () 
```




<hr>



### function GetBaseToolkitName 

```C++
virtual FText FCollisionDataEditorToolkit::GetBaseToolkitName () override const
```




<hr>



### function GetSelectedState 

```C++
FText FCollisionDataEditorToolkit::GetSelectedState () const
```




<hr>



### function GetToolkitFName 

```C++
virtual FName FCollisionDataEditorToolkit::GetToolkitFName () override const
```




<hr>



### function GetToolkitName 

```C++
virtual FText FCollisionDataEditorToolkit::GetToolkitName () override const
```




<hr>



### function GetWorldCentricTabColorScale 

```C++
virtual FLinearColor FCollisionDataEditorToolkit::GetWorldCentricTabColorScale () override const
```




<hr>



### function GetWorldCentricTabPrefix 

```C++
virtual FString FCollisionDataEditorToolkit::GetWorldCentricTabPrefix () override const
```




<hr>



### function Initialize 

```C++
void FCollisionDataEditorToolkit::Initialize (
    UCollisionData * InCollisionData,
    const EToolkitMode::Type Mode,
    const TSharedPtr< IToolkitHost > & InitToolkitHost
) 
```




<hr>



### function InitializePreviewScene 

```C++
void FCollisionDataEditorToolkit::InitializePreviewScene () 
```




<hr>



### function RegisterTabSpawners 

```C++
virtual void FCollisionDataEditorToolkit::RegisterTabSpawners (
    const TSharedRef< FTabManager > & InTabManager
) override
```




<hr>



### function SpawnTab\_CollisionDataDetails 

```C++
TSharedRef< SDockTab > FCollisionDataEditorToolkit::SpawnTab_CollisionDataDetails (
    const FSpawnTabArgs & Args
) 
```




<hr>



### function SpawnTab\_PlayerObjectSelector 

```C++
TSharedRef< SDockTab > FCollisionDataEditorToolkit::SpawnTab_PlayerObjectSelector (
    const FSpawnTabArgs & Args
) 
```




<hr>



### function SpawnTab\_ViewportTab 

```C++
TSharedRef< SDockTab > FCollisionDataEditorToolkit::SpawnTab_ViewportTab (
    const FSpawnTabArgs & Args
) 
```




<hr>



### function UnregisterTabSpawners 

```C++
virtual void FCollisionDataEditorToolkit::UnregisterTabSpawners (
    const TSharedRef< FTabManager > & InTabManager
) override
```




<hr>



### function ~FCollisionDataEditorToolkit 

```C++
virtual FCollisionDataEditorToolkit::~FCollisionDataEditorToolkit () override
```




<hr>
## Protected Functions Documentation




### function OnClose 

```C++
virtual void FCollisionDataEditorToolkit::OnClose () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/CollisionEditor/Public/CollisionDataEditorToolkit.h`

