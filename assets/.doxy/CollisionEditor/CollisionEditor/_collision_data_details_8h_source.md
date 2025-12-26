

# File CollisionDataDetails.h

[**File List**](files.md) **>** [**CollisionEditor**](dir_940e8f38acfe3acbe44a727b0224043a.md) **>** [**Public**](dir_56ac83e1ee3de8bf475f92dfdd96fd55.md) **>** [**CollisionDataDetails.h**](_collision_data_details_8h.md)

[Go to the documentation of this file](_collision_data_details_8h.md)


```C++
#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"
#include "GameplayTagContainer.h"
#include "Input/Reply.h"

class UCollisionData;
class IDetailCategoryBuilder;


class FCollisionDataDetails : public IDetailCustomization
{
public:
    static TSharedRef<IDetailCustomization> MakeInstance();

    virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

private:
    void BuildSelectedCelView(IDetailLayoutBuilder& DetailBuilder, IDetailCategoryBuilder& Category);
    void OnCelSelected(const FGameplayTag& CelName);

    FReply OnAddNewCel();
    FReply OnDeleteSelectedCel();
    FReply OnTemplateSelectedCel();
    FReply OnRefreshTree();

    bool CanDeleteSelectedCel() const;
    bool CanTemplateSelectedCel() const;

    TWeakObjectPtr<UCollisionData> CollisionDataPtr;
    TSharedPtr<IPropertyHandle> CollisionFramesHandle;
    IDetailLayoutBuilder* CachedDetailBuilder = nullptr;
    FGameplayTag SelectedCelName;
};
```


