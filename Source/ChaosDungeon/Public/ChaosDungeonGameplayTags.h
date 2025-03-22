#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

struct FChaosDungeonGameplayTags
{
public:
	static const FChaosDungeonGameplayTags& Get() { return GameplayTags; }

	static void InitializeNativeGameplayTags();

public:
	FGameplayTag Attributes_BasicAttributes_Intelligence;
	FGameplayTag Attributes_BasicAttributes_Stamina;
	FGameplayTag Attributes_BasicAttributes_Attack;
	FGameplayTag Attributes_BasicAttributes_PhysicalDEF;
	FGameplayTag Attributes_BasicAttributes_LegalDEF;
	FGameplayTag Attributes_BasicAttributes_Health;
	FGameplayTag Attributes_BasicAttributes_MaxHealth;
	FGameplayTag Attributes_BasicAttributes_Mana;
	FGameplayTag Attributes_BasicAttributes_MaxMana;

	FGameplayTag InputTag_Q;
	FGameplayTag InputTag_E;
	FGameplayTag InputTag_R;
	FGameplayTag InputTag_T;

private:
	static FChaosDungeonGameplayTags GameplayTags;
};