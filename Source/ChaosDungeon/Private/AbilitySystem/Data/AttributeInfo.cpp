#include "AbilitySystem/Data/AttributeInfo.h"

FChaosDungeonAttributeInfo UAttributeInfo::FindAttributeInfoByTag(const FGameplayTag& AttributeTag)
{
	for (const FChaosDungeonAttributeInfo& ChaosDungeonAttributeInfo : AttributeInformation)
	{
		// MatchesTag ºÏ≤È±Í«© «∑Ò∆•≈‰
		if (ChaosDungeonAttributeInfo.AttributeTag.MatchesTag(AttributeTag))
		{
			return ChaosDungeonAttributeInfo;
		}
	}

	return FChaosDungeonAttributeInfo();
}
