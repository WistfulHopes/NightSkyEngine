

# File CollisionDataEditorToolkit.h



[**FileList**](files.md) **>** [**CollisionEditor**](dir_940e8f38acfe3acbe44a727b0224043a.md) **>** [**Public**](dir_56ac83e1ee3de8bf475f92dfdd96fd55.md) **>** [**CollisionDataEditorToolkit.h**](_collision_data_editor_toolkit_8h.md)

[Go to the source code of this file](_collision_data_editor_toolkit_8h_source.md)



* `#include "CoreMinimal.h"`
* `#include "Toolkits/AssetEditorToolkit.h"`
* `#include "Toolkits/IToolkitHost.h"`
* `#include "Widgets/Docking/SDockTab.h"`
* `#include "Widgets/Layout/SBorder.h"`
* `#include "Widgets/Text/STextBlock.h"`
* `#include "PropertyCustomizationHelpers.h"`
* `#include "Data/CollisionData.h"`















## Classes

| Type | Name |
| ---: | :--- |
| class | [**FCollisionDataEditorToolkit**](class_f_collision_data_editor_toolkit.md) <br> |


## Public Types

| Type | Name |
| ---: | :--- |
| enum  | [**EBoxEditMode**](#enum-eboxeditmode)  <br> |
| enum  | [**ESceneInteractionMode**](#enum-esceneinteractionmode)  <br> |
















































## Public Types Documentation




### enum EBoxEditMode 

```C++
enum EBoxEditMode {
    EditMode_None,
    EditMode_Add,
    EditMode_Move,
    EditMode_Delete
};
```



The different modes of editing collision boxes. 


        

<hr>



### enum ESceneInteractionMode 

```C++
enum ESceneInteractionMode {
    Interaction_CameraMove,
    Interaction_EditCollisionBoxes
};
```



The different modes of interaction in the Scene. 


        

<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/CollisionEditor/Public/CollisionDataEditorToolkit.h`

