#include "AbilitySystem/DoCAbilitySystemComponent.h"

void UDoCAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &ThisClass::EffectApplied);
}

void UDoCAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
	const FGameplayEffectSpec& GameplayEffectSpec,
	FActiveGameplayEffectHandle ActiveGameplayEffectHandle)
{
	FGameplayTagContainer GameplayTagContainer;
	GameplayEffectSpec.GetAllAssetTags(GameplayTagContainer);

	EffectAssetTags.Broadcast(GameplayTagContainer);
}
