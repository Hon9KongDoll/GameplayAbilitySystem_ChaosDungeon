#pragma once

#include "CoreMinimal.h"
#include "UserInterface/WidgetController/ChaosDungeonWidgetController.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "AttributeSet.h"
#include "GameplayTagContainer.h"
#include "AttributeMenuWidgetController.generated.h"

class UAttributeInfo;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoSignature, const FChaosDungeonAttributeInfo&, Info);

UCLASS(BlueprintType, Blueprintable)
class CHAOSDUNGEON_API UAttributeMenuWidgetController : public UChaosDungeonWidgetController
{
	GENERATED_BODY()
	
public:
	virtual void BroadcastInitialValues() override;

	virtual void BindCallbacksToDependencies() override;

private:
	void BroadcastAttributesInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute) const;

public:
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FAttributeInfoSignature AttributeInfoDelegate;

protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAttributeInfo> AttributeInfo;
};
