#include "UserInterface/WidgetController/AttributeMenuWidgetController.h"
#include "AbilitySystem/ChaosDungeonAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "ChaosDungeonGameplayTags.h"

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	Super::BroadcastInitialValues();

	check(AttributeInfo);

	UChaosDungeonAttributeSet* AS = CastChecked<UChaosDungeonAttributeSet>(AttributeSet);

	for (auto& Pair : AS->TagToAttributes)
	{
		BroadcastAttributesInfo(Pair.Key, Pair.Value());
	}
}

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	Super::BindCallbacksToDependencies();

	check(AttributeInfo);

	UChaosDungeonAttributeSet* AS = CastChecked<UChaosDungeonAttributeSet>(AttributeSet);

	for (auto& Pair : AS->TagToAttributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
			[this, Pair](const FOnAttributeChangeData& Data)
			{
				BroadcastAttributesInfo(Pair.Key, Pair.Value());
			}
		);
	}
}

void UAttributeMenuWidgetController::BroadcastAttributesInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute) const
{
	FChaosDungeonAttributeInfo Info = AttributeInfo->FindAttributeInfoByTag(AttributeTag);
	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(Info);
}
