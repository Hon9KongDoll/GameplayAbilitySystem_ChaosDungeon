#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ChaosDungeonHUD.generated.h"

class UChaosDungeonUserWidget;

UCLASS()
class CHAOSDUNGEON_API AChaosDungeonHUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
public:
	UPROPERTY()
	TObjectPtr<UChaosDungeonUserWidget> OverlayWidget;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UChaosDungeonUserWidget> OverlayWidgetClass;
};
