#include "UserInterface/Widgets/ChaosDungeonUserWidget.h"

void UChaosDungeonUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
