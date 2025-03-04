#include "UserInterface/HUD/ChaosDungeonHUD.h"
#include "UserInterface/Widgets/ChaosDungeonUserWidget.h"
#include "UserInterface/WidgetController/OverlayWidgetController.h"

// Engine
#include "Blueprint/UserWidget.h"

UOverlayWidgetController* AChaosDungeonHUD::GetOverlayWidgetController(
	const FWidgetControllerParams& InWidgetControllerParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(InWidgetControllerParams);

		return OverlayWidgetController;
	}
	
	return OverlayWidgetController;
}

void AChaosDungeonHUD::InitOverlay(APlayerController* InPlayerController, APlayerState* InPlayerState,
	UAbilitySystemComponent* InAbilitySystemComponent, UAttributeSet* InAttributeSet)
{
	checkf(OverlayWidgetClass, TEXT("OverlayWidgetClass uninitialize"));
	checkf(OverlayWidgetControllerClass, TEXT("OverlayWidgetControllerClass uninitialize"));
	
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UChaosDungeonUserWidget>(Widget);

	FWidgetControllerParams WidgetControllerParams(InPlayerController, InPlayerState, InAbilitySystemComponent, InAttributeSet);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);

	OverlayWidget->SetWidgetController(WidgetController);

	WidgetController->BroadcastInitialValues();
	
	OverlayWidget->AddToViewport();
}
