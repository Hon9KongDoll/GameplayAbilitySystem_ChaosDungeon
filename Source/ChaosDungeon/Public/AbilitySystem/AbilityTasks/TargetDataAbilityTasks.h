#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "TargetDataAbilityTasks.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMouseSelectTargetDataSignature, const FVector&, Data);

UCLASS()
class CHAOSDUNGEON_API UTargetDataAbilityTasks : public UAbilityTask
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true"))
	static UTargetDataAbilityTasks* CreateUTargetDataAbilityTasks(UGameplayAbility* OwningAbility);

private:
	virtual void Activate() override;

	void SendMouseSelectData();

public:
	UPROPERTY(BlueprintAssignable)
	FMouseSelectTargetDataSignature ValidData;
};
