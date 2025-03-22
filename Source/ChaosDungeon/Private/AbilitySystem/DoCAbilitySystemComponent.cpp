#include "AbilitySystem/DoCAbilitySystemComponent.h"
#include "AbilitySystem/GameplayAbilities/ChaosDungeonGameplayAbility.h"

void UDoCAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &ThisClass::EffectApplied);
}

void UDoCAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities)
{
	for (const TSubclassOf<UGameplayAbility> GameplayAbility : StartupAbilities)
	{
		FGameplayAbilitySpec GameplayAbilitySpec(GameplayAbility, 1);

		if (const UChaosDungeonGameplayAbility* ChaosDungeonGameplayAbility = Cast<UChaosDungeonGameplayAbility>(GameplayAbilitySpec.Ability))
		{
			GameplayAbilitySpec.DynamicAbilityTags.AddTag(ChaosDungeonGameplayAbility->StartupTag);
			//GiveAbilityAndActivateOnce(GameplayAbilitySpec);
			GiveAbility(GameplayAbilitySpec);
		}
	}
}

void UDoCAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputPressed(AbilitySpec);

			if (!AbilitySpec.IsActive())
			{
				TryActivateAbility(AbilitySpec.Handle);
			}

		}
	}
}

void UDoCAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputReleased(AbilitySpec);
		}
	}
}

void UDoCAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
	const FGameplayEffectSpec& GameplayEffectSpec,
	FActiveGameplayEffectHandle ActiveGameplayEffectHandle)
{
	FGameplayTagContainer GameplayTagContainer;
	GameplayEffectSpec.GetAllAssetTags(GameplayTagContainer);

	EffectAssetTags.Broadcast(GameplayTagContainer);
}
