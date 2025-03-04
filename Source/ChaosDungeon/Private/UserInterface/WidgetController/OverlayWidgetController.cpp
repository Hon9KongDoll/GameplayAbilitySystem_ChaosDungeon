#include "UserInterface/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/ChaosDungeonAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	Super::BroadcastInitialValues();

	if (const UChaosDungeonAttributeSet* ChaosDungeonAttributeSet = Cast<UChaosDungeonAttributeSet>(AttributeSet))
	{
		OnHealthChanged.Broadcast(ChaosDungeonAttributeSet->GetHealth());
		OnMaxHealthChanged.Broadcast(ChaosDungeonAttributeSet->GetMaxHealth());
		OnManaChanged.Broadcast(ChaosDungeonAttributeSet->GetMana());
		OnMaxManaChanged.Broadcast(ChaosDungeonAttributeSet->GetMaxMana());
	}
}
