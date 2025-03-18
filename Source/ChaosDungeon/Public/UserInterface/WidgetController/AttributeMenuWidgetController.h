#pragma once

#include "CoreMinimal.h"
#include "UserInterface/WidgetController/ChaosDungeonWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"

UCLASS()
class CHAOSDUNGEON_API UAttributeMenuWidgetController : public UChaosDungeonWidgetController
{
	GENERATED_BODY()
	
public:
	virtual void BroadcastInitialValues() override;

	virtual void BindCallbacksToDependencies() override;
};
