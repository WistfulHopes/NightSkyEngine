#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"
#include "GameplayTagContainer.h"
#include "Input/Reply.h"

class UCollisionData;
class IDetailCategoryBuilder;


/**
 * Detail customization for UCollisionData that displays CollisionFrames
 * in a hierarchical tree organized by GameplayTag.
 */
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
	FReply OnRefreshTree();
	
	bool CanDeleteSelectedCel() const;

	TWeakObjectPtr<UCollisionData> CollisionDataPtr;
	TSharedPtr<IPropertyHandle> CollisionFramesHandle;
	IDetailLayoutBuilder* CachedDetailBuilder = nullptr;
	FGameplayTag SelectedCelName;
};
