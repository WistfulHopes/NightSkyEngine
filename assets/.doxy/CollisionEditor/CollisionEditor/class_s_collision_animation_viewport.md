

# Class SCollisionAnimationViewport



[**ClassList**](annotated.md) **>** [**SCollisionAnimationViewport**](class_s_collision_animation_viewport.md)








Inherits the following classes: SEditorViewport,  FGCObject,  ICommonEditorViewportToolbarInfoProvider


















## Public Attributes

| Type | Name |
| ---: | :--- |
|  TSharedPtr&lt; [**FCollisionAnimationPreviewScene**](class_f_collision_animation_preview_scene.md) &gt; | [**PreviewScene**](#variable-previewscene)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
| virtual void | [**AddReferencedObjects**](#function-addreferencedobjects) (FReferenceCollector & Collector) override<br> |
|  void | [**Construct**](#function-construct) (const FArguments & InArgs, TSharedPtr&lt; [**FCollisionDataEditorToolkit**](class_f_collision_data_editor_toolkit.md) &gt; InEditorToolkit, TSharedPtr&lt; [**FCollisionAnimationPreviewScene**](class_f_collision_animation_preview_scene.md) &gt; InPreviewScene) <br> |
| virtual TSharedPtr&lt; FExtender &gt; | [**GetExtenders**](#function-getextenders) () override const<br> |
| virtual FString | [**GetReferencerName**](#function-getreferencername) () override const<br> |
| virtual TSharedRef&lt; SEditorViewport &gt; | [**GetViewportWidget**](#function-getviewportwidget) () override<br> |
| virtual TSharedRef&lt; FEditorViewportClient &gt; | [**MakeEditorViewportClient**](#function-makeeditorviewportclient) () override<br> |
| virtual void | [**OnFloatingButtonClicked**](#function-onfloatingbuttonclicked) () override<br> |
| virtual void | [**OnFocusViewportToSelection**](#function-onfocusviewporttoselection) () override<br> |
|   | [**SLATE\_BEGIN\_ARGS**](#function-slate_begin_args) ([**SCollisionAnimationViewport**](class_s_collision_animation_viewport.md)) <br> |
| virtual  | [**~SCollisionAnimationViewport**](#function-scollisionanimationviewport) () override<br> |




























## Public Attributes Documentation




### variable PreviewScene 

```C++
TSharedPtr<FCollisionAnimationPreviewScene> SCollisionAnimationViewport::PreviewScene;
```




<hr>
## Public Functions Documentation




### function AddReferencedObjects 

```C++
inline virtual void SCollisionAnimationViewport::AddReferencedObjects (
    FReferenceCollector & Collector
) override
```




<hr>



### function Construct 

```C++
void SCollisionAnimationViewport::Construct (
    const FArguments & InArgs,
    TSharedPtr< FCollisionDataEditorToolkit > InEditorToolkit,
    TSharedPtr< FCollisionAnimationPreviewScene > InPreviewScene
) 
```




<hr>



### function GetExtenders 

```C++
virtual TSharedPtr< FExtender > SCollisionAnimationViewport::GetExtenders () override const
```




<hr>



### function GetReferencerName 

```C++
virtual FString SCollisionAnimationViewport::GetReferencerName () override const
```




<hr>



### function GetViewportWidget 

```C++
virtual TSharedRef< SEditorViewport > SCollisionAnimationViewport::GetViewportWidget () override
```




<hr>



### function MakeEditorViewportClient 

```C++
virtual TSharedRef< FEditorViewportClient > SCollisionAnimationViewport::MakeEditorViewportClient () override
```




<hr>



### function OnFloatingButtonClicked 

```C++
virtual void SCollisionAnimationViewport::OnFloatingButtonClicked () override
```




<hr>



### function OnFocusViewportToSelection 

```C++
virtual void SCollisionAnimationViewport::OnFocusViewportToSelection () override
```




<hr>



### function SLATE\_BEGIN\_ARGS 

```C++
inline SCollisionAnimationViewport::SLATE_BEGIN_ARGS (
    SCollisionAnimationViewport
) 
```




<hr>



### function ~SCollisionAnimationViewport 

```C++
virtual SCollisionAnimationViewport::~SCollisionAnimationViewport () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/CollisionEditor/Public/Viewport/CollisionAnimationViewport.h`

