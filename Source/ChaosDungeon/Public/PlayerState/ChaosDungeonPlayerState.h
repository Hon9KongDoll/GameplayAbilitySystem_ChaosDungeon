#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "ChaosDungeonPlayerState.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

UCLASS()
class CHAOSDUNGEON_API AChaosDungeonPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AChaosDungeonPlayerState();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	FORCEINLINE virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }

	FORCEINLINE UAttributeSet* GetAttributeSet() const { return AttributeSet; }

	FORCEINLINE virtual int32 GetPlayerLevel() const { return PlayerLevel; }

private:
	UFUNCTION()
	void Rep_PlayerLevel(int32 OldPlayerLevel);

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

private:
	UPROPERTY(VisibleAnywhere, ReplicatedUsing = Rep_PlayerLevel)
	int32 PlayerLevel = 1;
};
