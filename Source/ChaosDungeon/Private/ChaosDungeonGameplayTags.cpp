#include "ChaosDungeonGameplayTags.h"
#include "GameplayTagsManager.h"

FChaosDungeonGameplayTags FChaosDungeonGameplayTags::GameplayTags;

void FChaosDungeonGameplayTags::InitializeNativeGameplayTags()
{
	GameplayTags.Attributes_BasicAttributes_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.BasicAttributes.Intelligence"));

	GameplayTags.Attributes_BasicAttributes_Stamina = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.BasicAttributes.Stamina"));

	GameplayTags.Attributes_BasicAttributes_Attack = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.BasicAttributes.Attack"));

	GameplayTags.Attributes_BasicAttributes_PhysicalDEF = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.BasicAttributes.PhysicalDEF"));

	GameplayTags.Attributes_BasicAttributes_LegalDEF = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.BasicAttributes.LegalDEF"));

	GameplayTags.Attributes_BasicAttributes_Health = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.BasicAttributes.Health"));

	GameplayTags.Attributes_BasicAttributes_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.BasicAttributes.MaxHealth"));

	GameplayTags.Attributes_BasicAttributes_Mana = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.BasicAttributes.Mana"));

	GameplayTags.Attributes_BasicAttributes_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.BasicAttributes.MaxMana"));


	/*
	* Input Tags
	*/

	GameplayTags.InputTag_Q = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.Q"));

	GameplayTags.InputTag_E = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.E"));

	GameplayTags.InputTag_R = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.R"));

	GameplayTags.InputTag_T = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.T"));

}
