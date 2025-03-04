#include "AbilitySystem/ChaosDungeonAttributeSet.h"
#include "Net/UnrealNetwork.h"

UChaosDungeonAttributeSet::UChaosDungeonAttributeSet()
{
	InitHealth(50.f);
	InitMaxHealth(100.f);
	InitMana(50.f);
	InitMaxMana(100.f);
}

void UChaosDungeonAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UChaosDungeonAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UChaosDungeonAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UChaosDungeonAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UChaosDungeonAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
}

void UChaosDungeonAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UChaosDungeonAttributeSet, Health, OldHealth);
}

void UChaosDungeonAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UChaosDungeonAttributeSet, MaxHealth, OldMaxHealth);
}

void UChaosDungeonAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UChaosDungeonAttributeSet, Mana, OldMana);
}

void UChaosDungeonAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UChaosDungeonAttributeSet, MaxMana, OldMaxMana);
}
