#include "UserInterface/HUD/ChaosDungeonHUD.h"
#include "UserInterface/Widgets/ChaosDungeonUserWidget.h"

// Engine
#include "Blueprint/UserWidget.h"

void AChaosDungeonHUD::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	Widget->AddToViewport();
}
