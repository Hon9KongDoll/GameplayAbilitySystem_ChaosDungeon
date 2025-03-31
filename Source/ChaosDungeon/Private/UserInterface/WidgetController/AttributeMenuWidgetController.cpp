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
		FChaosDungeonAttributeInfo Info = AttributeInfo->FindAttributeInfoByTag(Pair.Key);

		Info.AttributeValue = Pair.Value().GetNumericValue(AS);

		AttributeInfoDelegate.Broadcast(Info);
	}
}

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	Super::BindCallbacksToDependencies();
}
