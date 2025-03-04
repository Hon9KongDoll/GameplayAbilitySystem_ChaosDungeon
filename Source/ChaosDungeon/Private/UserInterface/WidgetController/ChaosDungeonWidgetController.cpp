#include "UserInterface/WidgetController/ChaosDungeonWidgetController.h"

void UChaosDungeonWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& InWidgetControllerParams)
{
	PlayerController = InWidgetControllerParams.PlayerController;
	PlayerState = InWidgetControllerParams.PlayerState;
	AbilitySystemComponent = InWidgetControllerParams.AbilitySystemComponent;
	AttributeSet = InWidgetControllerParams.AttributeSet;
}

void UChaosDungeonWidgetController::BroadcastInitialValues()
{
}
