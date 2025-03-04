#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UserInterface/WidgetController/ChaosDungeonWidgetController.h"
#include "ChaosDungeonHUD.generated.h"

class UChaosDungeonUserWidget;
class UOverlayWidgetController;

UCLASS()
class CHAOSDUNGEON_API AChaosDungeonHUD : public AHUD
{
	GENERATED_BODY()

public:
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& InWidgetControllerParams);

	void InitOverlay(APlayerController* InPlayerController,
		APlayerState* InPlayerState,
		UAbilitySystemComponent* InAbilitySystemComponent,
		UAttributeSet* InAttributeSet);

public:
	UPROPERTY()
	TObjectPtr<UChaosDungeonUserWidget> OverlayWidget;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UChaosDungeonUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
};
