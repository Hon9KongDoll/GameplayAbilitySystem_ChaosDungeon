#pragma once

#include "CoreMinimal.h"
#include "UserInterface/WidgetController/ChaosDungeonWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"

class UAttributeInfo;
struct FChaosDungeonAttributeInfo;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoSignature, const FChaosDungeonAttributeInfo&, Info);

UCLASS(BlueprintType, Blueprintable)
class CHAOSDUNGEON_API UAttributeMenuWidgetController : public UChaosDungeonWidgetController
{
	GENERATED_BODY()
	
public:
	virtual void BroadcastInitialValues() override;

	virtual void BindCallbacksToDependencies() override;

public:
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FAttributeInfoSignature AttributeInfoDelegate;

protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAttributeInfo> AttributeInfo;
};
