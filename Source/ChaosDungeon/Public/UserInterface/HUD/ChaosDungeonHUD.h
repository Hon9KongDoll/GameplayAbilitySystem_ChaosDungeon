#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UserInterface/WidgetController/ChaosDungeonWidgetController.h"
#include "ChaosDungeonHUD.generated.h"

class UChaosDungeonUserWidget;
class UOverlayWidgetController;
class UAttributeMenuWidgetController;

UCLASS()
class CHAOSDUNGEON_API AChaosDungeonHUD : public AHUD
{
	GENERATED_BODY()

public:
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& InWidgetControllerParams);

	UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const FWidgetControllerParams& InWidgetControllerParams);

	void InitOverlay(APlayerController* InPlayerController,
		APlayerState* InPlayerState,
		UAbilitySystemComponent* InAbilitySystemComponent,
		UAttributeSet* InAttributeSet);

private:
	UPROPERTY()
	TObjectPtr<UChaosDungeonUserWidget> OverlayWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UChaosDungeonUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<UAttributeMenuWidgetController> AttributeMenuWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAttributeMenuWidgetController> AttributeMenuWidgetControllerClass;
};
