#include "ChaosDungeonGameplayTags.h"
#include "GameplayTagsManager.h"

FChaosDungeonGameplayTags FChaosDungeonGameplayTags::ChaosDungeonGameplayTags;

void FChaosDungeonGameplayTags::InitializeNativeGameplayTags()
{
	ChaosDungeonGameplayTags.Attributes_BasicAttributes_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.BasicAttributes.Intelligence"));

	ChaosDungeonGameplayTags.Attributes_BasicAttributes_Stamina = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.BasicAttributes.Stamina"));

	ChaosDungeonGameplayTags.Attributes_BasicAttributes_Attack = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.BasicAttributes.Attack"));

	ChaosDungeonGameplayTags.Attributes_BasicAttributes_PhysicalDEF = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.BasicAttributes.PhysicalDEF"));

	ChaosDungeonGameplayTags.Attributes_BasicAttributes_LegalDEF = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.BasicAttributes.LegalDEF"));

	ChaosDungeonGameplayTags.Attributes_BasicAttributes_Health = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.BasicAttributes.Health"));

	ChaosDungeonGameplayTags.Attributes_BasicAttributes_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.BasicAttributes.MaxHealth"));

	ChaosDungeonGameplayTags.Attributes_BasicAttributes_Mana = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.BasicAttributes.Mana"));

	ChaosDungeonGameplayTags.Attributes_BasicAttributes_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.BasicAttributes.MaxMana"));

}
