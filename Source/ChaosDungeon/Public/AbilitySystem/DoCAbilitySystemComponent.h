#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "DoCAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, const FGameplayTagContainer& /*AssetTags*/);

UCLASS()
class CHAOSDUNGEON_API UDoCAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	void AbilityActorInfoSet();

protected:
	void EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
		const FGameplayEffectSpec& GameplayEffectSpec,
		FActiveGameplayEffectHandle ActiveGameplayEffectHandle);

public:
	FEffectAssetTags EffectAssetTags;
};
