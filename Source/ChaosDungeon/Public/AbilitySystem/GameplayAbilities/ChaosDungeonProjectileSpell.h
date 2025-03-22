#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/GameplayAbilities/ChaosDungeonGameplayAbility.h"
#include "ChaosDungeonProjectileSpell.generated.h"

class AChaosDungeonProjectile;

UCLASS()
class CHAOSDUNGEON_API UChaosDungeonProjectileSpell : public UChaosDungeonGameplayAbility
{
	GENERATED_BODY()
	
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AChaosDungeonProjectile> ProjectileClass;
};
