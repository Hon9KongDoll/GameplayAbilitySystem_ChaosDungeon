#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "DoCAbilitySystemComponent.generated.h"

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
};
