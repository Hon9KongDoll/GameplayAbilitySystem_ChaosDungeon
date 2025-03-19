#include "UserInterface/HUD/ChaosDungeonHUD.h"
#include "UserInterface/Widgets/ChaosDungeonUserWidget.h"
#include "UserInterface/WidgetController/OverlayWidgetController.h"
#include "UserInterface/WidgetController/AttributeMenuWidgetController.h"

// Engine
#include "Blueprint/UserWidget.h"

UOverlayWidgetController* AChaosDungeonHUD::GetOverlayWidgetController(
	const FWidgetControllerParams& InWidgetControllerParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(InWidgetControllerParams);

		// 绑定委托,监听 GameplayAttribute 属性值变化
		OverlayWidgetController->BindCallbacksToDependencies();
		
		return OverlayWidgetController;
	}
	
	return OverlayWidgetController;
}

UAttributeMenuWidgetController* AChaosDungeonHUD::GetAttributeMenuWidgetController(const FWidgetControllerParams& InWidgetControllerParams)
{
	if (AttributeMenuWidgetController == nullptr)
	{
		AttributeMenuWidgetController = NewObject<UAttributeMenuWidgetController>(this, AttributeMenuWidgetControllerClass);
		AttributeMenuWidgetController->SetWidgetControllerParams(InWidgetControllerParams);

		// 绑定委托,监听 GameplayAttribute 属性值变化
		AttributeMenuWidgetController->BindCallbacksToDependencies();

		return AttributeMenuWidgetController;
	}

	return AttributeMenuWidgetController;
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
