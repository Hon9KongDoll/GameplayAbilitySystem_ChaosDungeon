#include "UserInterface/WidgetController/AttributeMenuWidgetController.h"
#include "AbilitySystem/ChaosDungeonAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "ChaosDungeonGameplayTags.h"

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	Super::BroadcastInitialValues();

	check(AttributeInfo);

	UChaosDungeonAttributeSet* AS = CastChecked<UChaosDungeonAttributeSet>(AttributeSet);

	FChaosDungeonAttributeInfo Info = AttributeInfo->FindAttributeInfoByTag(FChaosDungeonGameplayTags::Get().Attributes_BasicAttributes_Intelligence);

	Info.AttributeValue = AS->GetIntelligence();

	AttributeInfoDelegate.Broadcast(Info);
}

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	Super::BindCallbacksToDependencies();
}
