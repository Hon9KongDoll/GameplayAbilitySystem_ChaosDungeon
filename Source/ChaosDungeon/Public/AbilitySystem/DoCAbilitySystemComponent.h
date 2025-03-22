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

	void AddCharacterAbilities(const TArray <TSubclassOf<UGameplayAbility>>& StartupAbilities);

	void AbilityInputTagHeld(const FGameplayTag& InputTag);
	void AbilityInputTagReleased(const FGameplayTag& InputTag);

protected:
	void EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
		const FGameplayEffectSpec& GameplayEffectSpec,
		FActiveGameplayEffectHandle ActiveGameplayEffectHandle);

public:
	FEffectAssetTags EffectAssetTags;
};
