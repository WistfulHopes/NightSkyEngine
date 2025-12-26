

# Class FCelAssetTreeNode



[**ClassList**](annotated.md) **>** [**FCelAssetTreeNode**](class_f_cel_asset_tree_node.md)



[More...](#detailed-description)

* `#include <CelAssetTreeNode.h>`



Inherits the following classes: TSharedFromThis< FCelAssetTreeNode >


















## Public Attributes

| Type | Name |
| ---: | :--- |
|  TArray&lt; TSharedPtr&lt; [**FCelAssetTreeNode**](class_f_cel_asset_tree_node.md) &gt; &gt; | [**Children**](#variable-children)  <br> |
|  TWeakPtr&lt; [**FCelAssetTreeNode**](class_f_cel_asset_tree_node.md) &gt; | [**Parent**](#variable-parent)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**FCelAssetTreeNode**](#function-fcelassettreenode-12) (const FString & InDisplayName, int32 InCelIndex=INDEX\_NONE) <br> |
|   | [**FCelAssetTreeNode**](#function-fcelassettreenode-22) (int32 InCelIndex, const FString & InDisplayName, bool bInHasProblem=false) <br> |
|  TSharedPtr&lt; [**FCelAssetTreeNode**](class_f_cel_asset_tree_node.md) &gt; | [**FindOrCreateChild**](#function-findorcreatechild) (const FString & ChildName, int32 ChildCelIndex=INDEX\_NONE) <br> |
|  int32 | [**GetCelIndex**](#function-getcelindex) () const<br> |
|  FString | [**GetDisplayName**](#function-getdisplayname) () const<br> |
|  bool | [**IsCategory**](#function-iscategory) () const<br> |
|  bool | [**IsCel**](#function-iscel) () const<br> |
|  bool | [**IsValid**](#function-isvalid) () const<br> |
|  void | [**SetCelIndex**](#function-setcelindex) (int32 InCelIndex) <br> |




























## Detailed Description


Node for the cel asset tree view. Can represent either a category (intermediate node) or a cel (leaf node). 


    
## Public Attributes Documentation




### variable Children 

```C++
TArray<TSharedPtr<FCelAssetTreeNode> > FCelAssetTreeNode::Children;
```




<hr>



### variable Parent 

```C++
TWeakPtr<FCelAssetTreeNode> FCelAssetTreeNode::Parent;
```




<hr>
## Public Functions Documentation




### function FCelAssetTreeNode [1/2]

```C++
inline FCelAssetTreeNode::FCelAssetTreeNode (
    const FString & InDisplayName,
    int32 InCelIndex=INDEX_NONE
) 
```



Category constructor 


        

<hr>



### function FCelAssetTreeNode [2/2]

```C++
inline FCelAssetTreeNode::FCelAssetTreeNode (
    int32 InCelIndex,
    const FString & InDisplayName,
    bool bInHasProblem=false
) 
```



Cel node constructor, requires an index 


        

<hr>



### function FindOrCreateChild 

```C++
TSharedPtr< FCelAssetTreeNode > FCelAssetTreeNode::FindOrCreateChild (
    const FString & ChildName,
    int32 ChildCelIndex=INDEX_NONE
) 
```




<hr>



### function GetCelIndex 

```C++
inline int32 FCelAssetTreeNode::GetCelIndex () const
```




<hr>



### function GetDisplayName 

```C++
inline FString FCelAssetTreeNode::GetDisplayName () const
```




<hr>



### function IsCategory 

```C++
inline bool FCelAssetTreeNode::IsCategory () const
```




<hr>



### function IsCel 

```C++
inline bool FCelAssetTreeNode::IsCel () const
```




<hr>



### function IsValid 

```C++
inline bool FCelAssetTreeNode::IsValid () const
```




<hr>



### function SetCelIndex 

```C++
inline void FCelAssetTreeNode::SetCelIndex (
    int32 InCelIndex
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `C:/Users/wistf/Unreal Projects/NightSkyEngine/Plugins/NightSkyEngine/Source/CollisionEditor/Public/CelAssetTreeNode.h`

